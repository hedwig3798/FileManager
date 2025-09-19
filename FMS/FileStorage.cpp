#include "FileStorage.h"
#include "stringUtil.h"
#include "SecureCodec.h"

#include <iostream>

FileStorage::FileStorage()
	: m_compressInfoMap{}
	, m_comExtension(L"")
	, m_compressPath(L"")
	, m_decompressPath(L"")
	, m_blockSize(0)
	, m_maxPartSize(0)
	, m_threadCount(0)
{
}

FileStorage::~FileStorage()
{
}


bool FileStorage::CreateDirectory(const std::wstring& _path)
{
	bool result = ::CreateDirectory(_path.c_str(), nullptr);
	// 디렉토리 생성 실패
	if (false == result)
	{
		// 단 이미 있어서 실패한 경우는 성공과 같다.
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

bool FileStorage::CompressDirectory(
	const std::wstring& _path
	, std::ofstream& outFile
	, size_t& currentSize
	, size_t& partIndex
)
{
	// 입력받은 디렉토리 열기
	WIN32_FIND_DATAW fd;
	HANDLE hFind = FindFirstFileW((_path + L"\\*").c_str(), &fd);

	// 실패
	if (INVALID_HANDLE_VALUE == hFind)
	{
		return false;
	}

	// 디렉토리 순회
	do
	{
		std::wstring name = fd.cFileName;

		// 특수 디렉토리 제외
		if (name == L"." || name == L"..")
		{
			continue;
		}

		// 파일의 전체 경로
		std::wstring fullPath = _path + L"\\" + name;

		// 디렉토리라면 재귀
		if (FILE_ATTRIBUTE_DIRECTORY & fd.dwFileAttributes)
		{
			CompressDirectory(fullPath,
				outFile,
				currentSize,
				partIndex
			);
		}
		// 파일만 압축
		else
		{
			// 원본 파일 데이터 버퍼
			std::vector<unsigned char> oriBuffer(m_blockSize);

			// 파일 스트림
			std::ifstream oriFile(fullPath, std::ios::binary);

			// 파일 열기 실패
			if (!oriFile)
			{
				return false;
			}

			// 압축 데이터
			CompressInfo comInfo;

			// 파일 크기 구하기
			oriFile.seekg(0, std::ios::end);
			uint64_t fileSize = oriFile.tellg();
			oriFile.seekg(0, std::ios::beg);

			comInfo.m_totalOriginalSize = fileSize;

			// 파일 분할 시작
			uint64_t remaining = fileSize;
			while (remaining > 0)
			{
				if (0 == m_threadCount)
				{
					// 읽을 크기 구하기 ( 남아있는 크기와, 한 블록의 크기 중 작은것 )
					size_t toRead = std::min<uint64_t>(m_blockSize, remaining);

					// 파일 읽기
					oriFile.read(reinterpret_cast<char*>(oriBuffer.data()), toRead);

					CompressWithNonThread(
						fullPath
						, name
						, outFile
						, currentSize
						, partIndex
						, comInfo
						, oriBuffer
						, toRead
					);
					// 남은 파일 크기
					remaining -= toRead;
				}
			}

			// 모든 파일의 인덱스를 위한 기록
			// 근데 이거 필요한건가? 흠...
			m_compressInfoMap[name] = comInfo;

		}
	} while (FindNextFileW(hFind, &fd));

	FindClose(hFind);
	return true;
}

bool FileStorage::CompressWithThread()
{
	return false;
}

bool FileStorage::CompressWithNonThread(
	const std::wstring& _path
	, const std::wstring& _name
	, std::ofstream& _outFile
	, size_t& _currentSize
	, size_t& _partIndex
	, CompressInfo& _comInfo
	, std::vector<unsigned char>& _oriBuffer
	, size_t _dataSize
)
{
	// 압축 데이터 버퍼
	std::vector<unsigned char> outBuffer(::LZ4_compressBound(static_cast<int>(m_blockSize)));

	// 읽은 부분 압축
	int compressedSize =
		::LZ4_compress_HC(
			reinterpret_cast<char*>(_oriBuffer.data())
			, reinterpret_cast<char*>(outBuffer.data())
			, static_cast<int>(_dataSize)
			, static_cast<int>(outBuffer.size())
			, 9
		);

	// 압축된 크기가 0 이하면 문제가 있다.
	if (compressedSize <= 0)
	{
		return false;
	}

	BlockInfo bInfo;

	// 암호화를 위한 데이터 생성
	::RAND_bytes(bInfo.m_key, sizeof(bInfo.m_key));
	::RAND_bytes(bInfo.m_iv, sizeof(bInfo.m_iv));

	std::vector<unsigned char> encrypted;
	if (false == AES::CryptCTR(outBuffer, encrypted, bInfo.m_key, bInfo.m_iv))
	{
		return false;
	}

	// 현재 파트 파일이 꽉 찼으면 새로 생성
	if (_currentSize + sizeof(uint32_t) + compressedSize > m_maxPartSize)
	{
		// 현재 파트 파일을 닫는다
		if (_outFile.is_open())
		{
			_outFile.close();
		}

		// 새 파트 파일을 생성하고 연다
		std::wstring currentPartPath =
			m_compressPath + L"\\part_"
			+ std::to_wstring(_partIndex++)
			+ m_comExtension;

		_outFile.open(currentPartPath, std::ios::binary);
		_currentSize = 0;
	}

	// 압축 데이터 기록
	uint32_t compSize32 = static_cast<uint32_t>(compressedSize);
	_outFile.write(reinterpret_cast<char*>(&compSize32), sizeof(compSize32));

	// 압축 및 암호화 된 데이터 기록
	uint64_t offset = _outFile.tellp();
	_outFile.write(reinterpret_cast<char*>(encrypted.data()), compressedSize);

	// 블록 메타데이터 작성
	bInfo.m_partIndex = _partIndex - 1;
	bInfo.m_offset = offset;
	bInfo.m_compressedSize = compSize32;
	bInfo.m_originalSize = _dataSize;

	// 압축 정보에 블록 정보를 넣는다
	_comInfo.m_blocks.push_back(bInfo);

	// 현재 파트 크기 증가
	_currentSize += sizeof(uint32_t) + compressedSize;

	return true;
}

void FileStorage::ShowAllFilename()
{
	for (const auto& itr : m_compressInfoMap)
	{
		std::wcout << itr.first << std::endl;
	}
}

bool FileStorage::CompressAll(const std::wstring& _path)
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
	size_t partIndex = 0;
	size_t currentSize = 0;
	std::ofstream partFile;

	// 현재 파트의 위치
	std::wstring currentPartPath = m_compressPath + L"\\part_" + std::to_wstring(partIndex++) + m_comExtension;
	// 현재 파트 파일 생성 및 열기
	partFile.open(currentPartPath, std::ios::binary);

	// 압축
	bool isCompressSuccess = CompressDirectory(
		_path
		, partFile
		, currentSize
		, partIndex
	);

	if (false == isCompressSuccess)
	{
		return false;
	}

	// 파트 파일 닫기
	if (partFile.is_open())
	{
		partFile.close();
	}

	// 인덱스 파일 생성
	std::ofstream indexFile(m_compressPath + L"\\.index", std::ios::binary);

	// 압축을 진행 할 전체 파일 갯수 기록
	uint32_t fileCount = static_cast<uint32_t>(m_compressInfoMap.size());
	indexFile.write(reinterpret_cast<char*>(&fileCount), sizeof(fileCount));

	// 모든 파일에 대한 인덱스 기록
	for (auto& fileInfo : m_compressInfoMap)
	{
		// 압축 파일 정보
		const CompressInfo& comFileInfo = fileInfo.second;
		std::wstring name = fileInfo.first;

		// 파일 이름
		uint32_t nameLen = static_cast<uint32_t>(name.size() * sizeof(wchar_t));
		indexFile.write(reinterpret_cast<char*>(&nameLen), sizeof(nameLen));
		indexFile.write(reinterpret_cast<const char*>(name.data()), nameLen);

		// 파일 원본 크기
		indexFile.write(reinterpret_cast<const char*>(&comFileInfo.m_totalOriginalSize), sizeof(comFileInfo.m_totalOriginalSize));

		// 블록 갯수
		uint32_t blockCount = static_cast<uint32_t>(comFileInfo.m_blocks.size());
		indexFile.write(reinterpret_cast<char*>(&blockCount), sizeof(blockCount));

		// 블록 정보
		for (auto& block : comFileInfo.m_blocks)
		{
			// 해당 블록이 있는 파트 번호
			indexFile.write(reinterpret_cast<const char*>(&block.m_partIndex), sizeof(block.m_partIndex));
			// 블록이 어느 위치에 있는지
			indexFile.write(reinterpret_cast<const char*>(&block.m_offset), sizeof(block.m_offset));
			// 블록의 크기
			indexFile.write(reinterpret_cast<const char*>(&block.m_compressedSize), sizeof(block.m_compressedSize));
			// 압축 해제 후 원본 크기
			indexFile.write(reinterpret_cast<const char*>(&block.m_originalSize), sizeof(block.m_originalSize));

			// 암호화 정보 기록
			indexFile.write(reinterpret_cast<const char*>(block.m_key), sizeof(block.m_key));
			indexFile.write(reinterpret_cast<const char*>(block.m_iv), sizeof(block.m_iv));
		}
	}

	m_compressInfoMap.clear();
	return true;
}

std::istream* FileStorage::OpenFile(const std::wstring& _filename)
{
	if (true == m_compressInfoMap.empty())
	{
		ResetCompressInfoMap();
	}

	// 캐시 확인
	auto cache = m_fileChace.find(_filename);
	if (cache != m_fileChace.end())
	{
		return cache->second.get();
	}

	// 있는 파일인지 확인
	auto it = m_compressInfoMap.find(_filename);
	if (it == m_compressInfoMap.end())
	{
		return nullptr;
	}

	// 압축 정보
	const CompressInfo& fileInfo = it->second;

	// 전체 파일 데이터
	std::vector<unsigned char> fileData;
	// 원본 크기 만큼 확장
	fileData.reserve(fileInfo.m_totalOriginalSize);

	// 블록 순서대로 해제
	for (const auto& block : fileInfo.m_blocks)
	{
		// 압축 파일 경로
		std::wstring currentPartPath = m_compressPath + L"\\part_" + std::to_wstring(block.m_partIndex) + m_comExtension;

		// 압축 파일 읽기 모드로 열기
		std::ifstream comFile(currentPartPath, std::ios::binary);

		// 파일 열기 실패
		if (!comFile)
		{
			return nullptr;
		}

		// 압축 파일의 오프셋 위치 부터 읽기 블록 데이터 읽기
		comFile.seekg(block.m_offset, std::ios::beg);
		std::vector<unsigned char> compBuf(block.m_compressedSize);
		comFile.read(reinterpret_cast<char*>(compBuf.data()), block.m_compressedSize);

		std::vector<unsigned char> decryptFile;
		// 블록 데이터 복호화
		if (false == AES::CryptCTR(compBuf, decryptFile, block.m_key, block.m_iv))
		{
			return nullptr;
		}

		// 블록 압축 해제
		std::vector<unsigned char> decomFile(block.m_originalSize);
		int decSize =
			LZ4_decompress_safe(
				reinterpret_cast<char*>(decryptFile.data())
				, reinterpret_cast<char*>(decomFile.data())
				, static_cast<int>(decryptFile.size())
				, static_cast<int>(decomFile.size())
			);

		// 압축 해제 실패
		if (decSize <= 0)
		{
			return nullptr;
		}

		// 파일 데이터 이어붙이기
		fileData.insert(fileData.end(), decomFile.begin(), decomFile.begin() + decSize);
	}


	// 메모리 파일 스트림을 이동
	m_fileChace[_filename] = std::make_unique<MemoryFileStream>(std::move(fileData));

	// 만들어진 파일 스트림 리턴
	return m_fileChace[_filename].get();
}

bool FileStorage::ResetCompressInfoMap()
{
	// 인덱스 파일 읽기
	std::ifstream indexFile(m_compressPath + L"\\.index", std::ios::binary);
	if (!indexFile)
	{
		return false;
	}

	// 전체 파일 갯수
	int fileCount = 0;
	indexFile.read(reinterpret_cast<char*>(&fileCount), sizeof(uint32_t));
	if (fileCount < 0)
	{
		return false;
	}

	// 모든 파일에 대한 데이터 읽기
	for (int i = 0; i < fileCount; i++)
	{
		// 압축 파일 정보
		uint32_t nameLen = 0;
		std::wstring name;

		// 파일 이름
		indexFile.read(reinterpret_cast<char*>(&nameLen), sizeof(uint32_t));
		name.resize(nameLen / sizeof(wchar_t));
		indexFile.read(reinterpret_cast<char*>(&name[0]), nameLen);

		// 파일 맵 생성
		m_compressInfoMap[name] = CompressInfo();
		CompressInfo& comFileInfo = m_compressInfoMap[name];

		// 파일 원본 크기
		indexFile.read(reinterpret_cast<char*>(&comFileInfo.m_totalOriginalSize), sizeof(comFileInfo.m_totalOriginalSize));

		// 블록 갯수
		uint32_t blockCount;
		indexFile.read(reinterpret_cast<char*>(&blockCount), sizeof(blockCount));

		// 블록 정보
		for (uint32_t j = 0; j < blockCount; j++)
		{
			BlockInfo block;

			// 해당 블록이 있는 파트 번호
			indexFile.read(reinterpret_cast<char*>(&block.m_partIndex), sizeof(block.m_partIndex));
			// 블록이 어느 위치에 있는지
			indexFile.read(reinterpret_cast<char*>(&block.m_offset), sizeof(block.m_offset));
			// 블록의 크기
			indexFile.read(reinterpret_cast<char*>(&block.m_compressedSize), sizeof(block.m_compressedSize));
			// 압축 해제 후 원본 크기
			indexFile.read(reinterpret_cast<char*>(&block.m_originalSize), sizeof(block.m_originalSize));
			// 암호화 정보
			indexFile.read(reinterpret_cast<char*>(block.m_key), sizeof(block.m_key));
			indexFile.read(reinterpret_cast<char*>(block.m_iv), sizeof(block.m_iv));

			comFileInfo.m_blocks.push_back(block);
		}
	}

	return true;
}

