#include "FileStorage.h"
#include "stringUtil.h"
#include <iostream>

FileStorage::FileStorage()
	: m_rootDir(L"")
	, m_filemap{}
	, m_comExtension(L"")
	, m_compressPath(L"")
	, m_decompressPath(L"")
	, m_blockSize(0)
	, m_maxPartSize(0)
{
}

FileStorage::~FileStorage()
{
	ClearFilestream();
}

void FileStorage::LoadCompressedFile()
{
	ClearFilestream();

	// 확장자 없다면 만들기
	if (0 == m_comExtension.length())
	{
		m_comExtension = L".rcom";
	}

	// 1 MB 단위 블록
	if (0 == m_blockSize)
	{
		m_blockSize = 1024 * 1024;
	}

	// 최악의 압축률인 경우의 입력 버퍼
	std::vector<char> inBuffer(LZ4_compressBound(static_cast<int>(m_blockSize)));
	// 블록 크기의 출력 버퍼
	std::vector<char> outBuffer(m_blockSize);

	// 읽을 파트들
	std::vector<std::wstring> parts;

	// 지정된 폴더에 있는 모든 파일 읽기
	WIN32_FIND_DATAW fileData;
	HANDLE h = FindFirstFileW((m_compressPath + L"\\*").c_str(), &fileData);

	// 읽기 실패
	if (h == INVALID_HANDLE_VALUE)
	{
		return;
	}

	do
	{
		// 디렉토리인 경우 무시한다
		if (true == (fileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
		{
			continue;
		}

		// 파일 이름
		std::wstring fname = fileData.cFileName;

		// 정해진 확장자가 아니면 무시
		if (fname.size() > m_comExtension.size()
			&& fname.substr(fname.size() - m_comExtension.size()) == m_comExtension)
		{
			parts.push_back(m_compressPath + L"\\" + fname);
		}

	} while (FindNextFileW(h, &fileData));

	// 파일 핸들러 닫기
	FindClose(h);

	// 파일을 이름순으로 정렬
	// 저장할 때 0번 부터 저장했으므로
	std::sort(parts.begin(), parts.end());

	// 이어 붙여야 하는 파일인 경우
	bool pending = false;
	std::wstring pendingName;
	uint64_t pendingOriginal = 0;
	uint64_t pendingWritten = 0;

	// 출력 파일
	std::ofstream out;

	// 특정 파이트 까지 문자열 읽는 함수
	auto ReadWstring = [](std::ifstream* _inputFile, uint32_t _byteLen) -> std::wstring
		{
			if (_byteLen % sizeof(wchar_t) != 0)
			{
				return L"";
			}

			std::wstring result(_byteLen / sizeof(wchar_t), L'\0');
			_inputFile->read(reinterpret_cast<char*>(&result[0]), _byteLen);
			return result;
		};

	// 모든 파트 파일에 대해 압축 해제 시작
	for (const auto& partPath : parts)
	{
		// 인풋 파일 생성
		std::ifstream inputFile(partPath, std::ios::binary);

		// 생성 실패
		if (!inputFile)
		{
			continue;
		}

		// 파일을 다 읽을 때 까지 반복
		while (true)
		{
			// 만일 새 파일인 경우
			if (false == pending)
			{
				// 헤더 읽기
				uint32_t nameLen = 0;
				inputFile.read(reinterpret_cast<char*>(&nameLen), sizeof(nameLen));
				if (!inputFile)
				{
					break;
				}

				// 파일 이름의 길이가 이상하다!
				if (nameLen == 0
					|| nameLen > 8 * 1024)
				{
					return;
				}

				// 파일 이름 읽기
				std::wstring wname = ReadWstring(&inputFile, nameLen);
				if (!inputFile)
				{
					return;
				}

				// 헤더에 있는 파일의 원래 크기를 읽기
				uint64_t originalSize = 0;
				inputFile.read(reinterpret_cast<char*>(&originalSize), sizeof(originalSize));
				if (!inputFile)
				{
					return;
				}

				// 압축 해제 파일을 저장 할 위치
				std::wstring outPath = m_decompressPath + L"\\" + wname;
				out.close();
				out.open(outPath.c_str(), std::ios::binary);
				if (!out)
				{
					return;
				}

				// 이번 파일에 남은 정보가 있을 수 있다
				pending = true;
				pendingName = wname;
				pendingOriginal = originalSize;
				pendingWritten = 0;
			}

			// 이번 파일에 남은 데이터가 있는경우
			while (pending
				&& pendingWritten < pendingOriginal)
			{
				// 압축된 블록 크기를 읽는다.
				uint32_t compSize = 0;
				inputFile.read(reinterpret_cast<char*>(&compSize), sizeof(compSize));
				if (!inputFile)
				{
					break;
				}

				// 있을수 없는 크기
				if (compSize == 0
					|| compSize > inBuffer.size())
				{
					return;
				}

				// 크기만큼 데이터를 읽는다
				inputFile.read(inBuffer.data(), compSize);
				if (!inputFile)
				{
					return;
				}

				// 압축 해제
				int decSize = LZ4_decompress_safe(
					inBuffer.data()
					, outBuffer.data()
					, compSize
					, static_cast<int>(outBuffer.size())
				);

				// 해제된 크기가 이상하다
				if (decSize < 0)
				{
					return;
				}

				// 앞으로 읽어야 할 크기
				size_t toWrite = static_cast<size_t>(
					std::min<uint64_t>(
						static_cast<uint64_t>(decSize)
						, pendingOriginal - pendingWritten)
					);

				// 출력 파일에 압축 해제 내용을 적는다
				out.write(outBuffer.data(), toWrite);
				pendingWritten += toWrite;

				// 이 파일 데이터를 다 읽었으면 다음 파일로
				if (pendingWritten == pendingOriginal)
				{
					out.close();
					pending = false;
					break;
				}
			}

			// 파트의 끝에 다다른 경우 다음 파트로
			if (!inputFile
				|| inputFile.peek() == EOF)
			{
				break;
			}
		}
	}

	// 뭔가 잘못 읽었다?
	if (pending
		&& pendingWritten < pendingOriginal)
	{
		return;
	}

	return;
}

bool FileStorage::CreateDirectory(const std::wstring& _path)
{
	bool result = ::CreateDirectory(_path.c_str(), nullptr);
	if (false == result)
	{
		if (GetLastError() == ERROR_ALREADY_EXISTS)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	return true;
}

void FileStorage::ClearFilestream()
{
	for (auto& mit : m_filemap)
	{
		if (true == mit.second->is_open())
		{
			mit.second->close();
		}
	}
	m_filemap.clear();
}

void FileStorage::ShowAllFilename()
{
	for (const auto& itr : m_filemap)
	{
		std::wcout << itr.first << std::endl;
	}
}

std::ifstream* FileStorage::GetFileStream(const std::wstring& _fileName)
{
	// map 에 없는 파일 이름이면 무시한다.
	auto mit = m_filemap.find(_fileName);
	if (mit == m_filemap.end())
	{
		return nullptr;
	}

	// 리턴
	return mit->second.get();
}

bool FileStorage::CompressAll()
{
	// 출력 디렉토리가 없다면 현재 디렉토리에 폴더 하나 만들어서 넣기
	if (0 == m_compressPath.length())
	{
		m_compressPath = L"./compress";
	}

	// 확장자 없다면 만들기
	if (0 == m_comExtension.length())
	{
		m_comExtension = L".rcom";
	}

	// 1 MB 단위 블록
	if (0 == m_blockSize)
	{
		m_blockSize = 1024 * 1024;
	}

	// 50 MB 단위 파트 사이즈
	if (0 == m_maxPartSize)
	{
		m_maxPartSize = 50 * 1024 * 1024;
	}

	// 출력 디렉토리 생성
	if (false == CreateDirectory(m_compressPath))
	{
		return false;
	}

	// 초기 설정
	// 1. 현재 파일 번호
	// 2. 현재 압축 파일의 크기
	// 3. 현재 압축 파일 스트림
	size_t fileIndex = 0;
	size_t currentSize = 0;
	std::ofstream outputFile;

	// 새 압축 파일을 만드는 함수
	auto CreateNewFile = [&]()
		{
			// 현재 파일을 닫고
			if (outputFile.is_open())
			{
				outputFile.close();
			}

			// 새 파일을 만든다.
			std::ostringstream oss;
			oss << ::WstrToStr(m_compressPath)
				<< "\\"
				<< ::WstrToStr(m_comFilename)
				<< fileIndex++
				<< ::WstrToStr(m_comExtension);

			// 만든 파일 열기
			outputFile.open(oss.str(), std::ios::binary);

			// 새로 열었으니 사이즈가 없다.
			currentSize = 0;
		};

	// 첫 파일 만들기
	CreateNewFile();

	// 블록 크기 만큼의 입력 버퍼
	std::vector<char> inBuffer(m_blockSize);
	// 압축률이 최악의 경우인 크기
	std::vector<char> outBuffer(::LZ4_compressBound(static_cast<int>(m_blockSize)));

	// 로드 된 모든 파일 순회하면서 압축 시작
	for (auto& mit : m_filemap)
	{
		// 파일 정보
		const std::wstring& name = mit.first;
		std::ifstream* inputFile = mit.second.get();

		// 파일의 전체 크기
		inputFile->seekg(0, std::ios::end);
		uint64_t fileSize = inputFile->tellg();
		inputFile->seekg(0, std::ios::beg);

		// 남은 크기 초기화
		uint64_t remainSize = fileSize;

		// 아직 압축 할 내용이 남아있다면
		while (0 < remainSize)
		{
			// 파일 읽기
			size_t toRead = std::min<uint64_t>(remainSize, m_blockSize);
			inputFile->read(inBuffer.data(), toRead);

			// 읽은 부분 만큼 LZ4 압축
			int compressedSize = ::LZ4_compress_default(
				inBuffer.data()
				, outBuffer.data()
				, static_cast<int>(toRead)
				, static_cast<int>(outBuffer.size())
			);

			// 압축된 사이즈가 0 보다 작다면 문제 있는거다
			if (0 >= compressedSize)
			{
				return false;
			}

			// 만들어진 블록이 들어갈 자리가 있는지 확인한다
			size_t checkSize = currentSize + sizeof(uint32_t) + compressedSize + sizeof(uint32_t) + sizeof(uint64_t);
			if (checkSize > m_maxPartSize)
			{
				CreateNewFile();
			}

			// 헤더 정보를 기록한다
			uint32_t nameLen = ::WstringByteSize(name);
			uint64_t segSize = toRead;
			outputFile.write(reinterpret_cast<char*>(&nameLen), sizeof(nameLen));
			outputFile.write(reinterpret_cast<const char*>(name.data()), nameLen);
			outputFile.write(reinterpret_cast<char*>(&segSize), sizeof(segSize));

			// 현재 크기를 늘린다.
			currentSize += sizeof(nameLen) + nameLen + sizeof(segSize);

			// 블록 정보를 기록한다.
			uint32_t compSize32 = static_cast<uint32_t>(compressedSize);
			outputFile.write(reinterpret_cast<char*>(&compSize32), sizeof(compSize32));
			outputFile.write(outBuffer.data(), compressedSize);

			// 현재 크기를 늘린다.
			currentSize += sizeof(compSize32) + compressedSize;

			// 읽은 만큼 남은 사이즈를 줄인다.
			remainSize -= toRead;
		}
	}

	// 만약 파일이 열려있다면 닫는다.
	if (outputFile.is_open())
	{
		outputFile.close();
	}

	return true;
}

bool FileStorage::DecompressAll()
{
	// 출력 디렉토리가 없다면 현재 디렉토리에 폴더 하나 만들어서 넣기
	if (0 == m_decompressPath.length())
	{
		m_decompressPath = L"./decompress";
	}

	// 확장자 없다면 만들기
	if (0 == m_comExtension.length())
	{
		m_comExtension = L".rcom";
	}

	// 1 MB 단위 블록
	if (0 == m_blockSize)
	{
		m_blockSize = 1024 * 1024;
	}

	// 출력 디렉토리 생성
	if (false == CreateDirectory(m_decompressPath))
	{
		return false;
	}

	// 최악의 압축률인 경우의 입력 버퍼
	std::vector<char> inBuffer(LZ4_compressBound(static_cast<int>(m_blockSize)));
	// 블록 크기의 출력 버퍼
	std::vector<char> outBuffer(m_blockSize);

	// 읽을 파트들
	std::vector<std::wstring> parts;

	// 지정된 폴더에 있는 모든 파일 읽기
	WIN32_FIND_DATAW fileData;
	HANDLE h = FindFirstFileW((m_compressPath + L"\\*").c_str(), &fileData);

	// 읽기 실패
	if (h == INVALID_HANDLE_VALUE)
	{
		return false;
	}

	do
	{
		// 디렉토리인 경우 무시한다
		if (true == (fileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
		{
			continue;
		}

		// 파일 이름
		std::wstring fname = fileData.cFileName;

		// 정해진 확장자가 아니면 무시
		if (fname.size() > m_comExtension.size()
			&& fname.substr(fname.size() - m_comExtension.size()) == m_comExtension)
		{
			parts.push_back(m_compressPath + L"\\" + fname);
		}

	} while (FindNextFileW(h, &fileData));

	// 파일 핸들러 닫기
	FindClose(h);

	// 파일을 이름순으로 정렬
	// 저장할 때 0번 부터 저장했으므로
	std::sort(parts.begin(), parts.end());

	// 이어 붙여야 하는 파일인 경우
	bool pending = false;
	std::wstring pendingName;
	uint64_t pendingOriginal = 0;
	uint64_t pendingWritten = 0;

	// 출력 파일
	std::ofstream out;

	// 특정 파이트 까지 문자열 읽는 함수
	auto ReadWstring = [](std::ifstream* _inputFile, uint32_t _byteLen) -> std::wstring
		{
			if (_byteLen % sizeof(wchar_t) != 0)
			{
				return L"";
			}

			std::wstring result(_byteLen / sizeof(wchar_t), L'\0');
			_inputFile->read(reinterpret_cast<char*>(&result[0]), _byteLen);
			return result;
		};

	// 모든 파트 파일에 대해 압축 해제 시작
	for (const auto& partPath : parts)
	{
		// 인풋 파일 생성
		std::ifstream inputFile(partPath, std::ios::binary);

		// 생성 실패
		if (!inputFile)
		{
			continue;
		}

		// 파일을 다 읽을 때 까지 반복
		while (true)
		{
			// 만일 새 파일인 경우
			if (false == pending)
			{
				// 헤더 읽기
				uint32_t nameLen = 0;
				inputFile.read(reinterpret_cast<char*>(&nameLen), sizeof(nameLen));
				if (!inputFile)
				{
					break;
				}

				// 파일 이름의 길이가 이상하다!
				if (nameLen == 0
					|| nameLen > 8 * 1024)
				{
					return false;
				}

				// 파일 이름 읽기
				std::wstring wname = ReadWstring(&inputFile, nameLen);
				if (!inputFile)
				{
					return false;
				}

				// 헤더에 있는 파일의 원래 크기를 읽기
				uint64_t originalSize = 0;
				inputFile.read(reinterpret_cast<char*>(&originalSize), sizeof(originalSize));
				if (!inputFile)
				{
					return false;
				}

				// 압축 해제 파일을 저장 할 위치
				std::wstring outPath = m_decompressPath + L"\\" + wname;
				out.close();
				out.open(outPath.c_str(), std::ios::binary);
				if (!out)
				{
					return false;
				}

				// 이번 파일에 남은 정보가 있을 수 있다
				pending = true;
				pendingName = wname;
				pendingOriginal = originalSize;
				pendingWritten = 0;
			}

			// 이번 파일에 남은 데이터가 있는경우
			while (pending
				&& pendingWritten < pendingOriginal)
			{
				// 압축된 블록 크기를 읽는다.
				uint32_t compSize = 0;
				inputFile.read(reinterpret_cast<char*>(&compSize), sizeof(compSize));
				if (!inputFile)
				{
					break;
				}

				// 있을수 없는 크기
				if (compSize == 0
					|| compSize > inBuffer.size())
				{
					return false;
				}

				// 크기만큼 데이터를 읽는다
				inputFile.read(inBuffer.data(), compSize);
				if (!inputFile)
				{
					return false;
				}

				// 압축 해제
				int decSize = LZ4_decompress_safe(
					inBuffer.data()
					, outBuffer.data()
					, compSize
					, static_cast<int>(outBuffer.size())
				);

				// 해제된 크기가 이상하다
				if (decSize < 0)
				{
					return false;
				}

				// 앞으로 읽어야 할 크기
				size_t toWrite = static_cast<size_t>(
					std::min<uint64_t>(
						static_cast<uint64_t>(decSize)
						, pendingOriginal - pendingWritten)
					);

				// 출력 파일에 압축 해제 내용을 적는다
				out.write(outBuffer.data(), toWrite);
				pendingWritten += toWrite;

				// 이 파일 데이터를 다 읽었으면 다음 파일로
				if (pendingWritten == pendingOriginal)
				{
					out.close();
					pending = false;
					break;
				}
			}

			// 파트의 끝에 다다른 경우 다음 파트로
			if (!inputFile
				|| inputFile.peek() == EOF)
			{
				break;
			}
		}
	}

	// 뭔가 잘못 읽었다?
	if (pending
		&& pendingWritten < pendingOriginal)
	{
		return false;
	}

	return true;
}

void FileStorage::WriteAllFile(const std::wstring& _path)
{

}

void FileStorage::LoadAll(const std::wstring& _path)
{
	// 윈도우 파일 api
	WIN32_FIND_DATAW findData;
	HANDLE hFind = FindFirstFileW((_path + L"\\*").c_str(), &findData);

	// 파일 핸들 가져오기 실패
	if (INVALID_HANDLE_VALUE == hFind)
	{
		return;
	}

	// 모든 파일 순회
	do
	{
		// 특수 파일 무시
		std::wstring fileName = findData.cFileName;
		if (L"." == fileName || L".." == fileName)
		{
			continue;
		}

		// 전체 경로
		std::wstring fullPath = _path + L"\\" + fileName;

		// 현 파일이 디렉토리인경우
		if (FILE_ATTRIBUTE_DIRECTORY & findData.dwFileAttributes)
		{
			// 하위 파일을 가져온다.
			LoadAll(fullPath);
		}
		// 현 파일이 디렉토리가 아닌경우
		else
		{
			// fstream 만들어서 저장
			auto fileStream = std::make_unique<std::ifstream>(fullPath, std::ios::binary);
			if (fileStream->is_open())
			{
				m_filemap[fileName] = std::move(fileStream);
			}
		}
	} while (::FindNextFile(hFind, &findData));

	FindClose(hFind);
}
