#pragma once
#pragma once
#include <string>
#include <map>
#include <set>
#include <fstream>
#include <windows.h>
#include <memory>
#include <sstream>
#include <vector>
#include <algorithm>
#include "lz4.h"
#include "MemoryFileStream.h"

/// <summary>
/// File Management System
/// 다수의 파일을 저장하고 불러오기 위한 클래스
/// </summary>
class FileStorage
{
private:
	/// <summary>
	/// 압축 블록 정보 구조체
	/// </summary>
	struct BlockInfo
	{
		uint64_t m_partIndex;
		uint64_t m_offset;
		uint64_t m_compressedSize;
		uint64_t m_originalSize;
		unsigned char m_key[32];
		unsigned char m_iv[16];
	};

	/// <summary>
	/// 압축 정보 구조체
	/// </summary>
	struct CompressInfo 
	{
		uint64_t m_totalOriginalSize = 0;
		std::vector<BlockInfo> m_blocks;
	};

	std::map<std::wstring, CompressInfo> m_compressInfoMap;
	std::map<std::wstring, std::unique_ptr<MemoryFileStream>> m_fileChace;

	std::wstring m_compressPath;
	std::wstring m_decompressPath;
	std::wstring m_comExtension;
	std::wstring m_comFilename;

	size_t m_blockSize;
	size_t m_maxPartSize;
public:
	FileStorage();
	virtual ~FileStorage();

public:

	void SetCompressExtension(const std::wstring& _extension) { m_comExtension = _extension; };
	void SetDecompressOutputPath(const std::wstring& _path) { m_decompressPath = _path; };
	void SetCompressFilePath(const std::wstring& _path) { m_compressPath = _path; };
	void SetOutputFileName(const std::wstring& _name) { m_comFilename = _name; };

	/// <summary>
	/// 모든 파일의 이름을 출력
	/// </summary>
	void ShowAllFilename();

	/// <summary>
	/// 경로에 있는 모든 파일 압축
	/// </summary>
	/// <returns>성공 여부</returns>
	bool CompressAll(const std::wstring& _path);

	/// <summary>
	/// 파일 열기
	/// </summary>
	/// <param name="_filename">파일 이름.확장자</param>
	/// <returns>파일 스트림</returns>
	std::istream* OpenFile(const std::wstring& _filename);

	/// <summary>
	/// 인덱스 파일 읽기
	/// </summary>
	/// <returns>성공 여부</returns>
	bool ResetCompressInfoMap();

private:

	/// <summary>
	/// 디렉토리 생성
	/// </summary>
	/// <param name="_path">해당 경로의 디렉토리 생성</param>
	/// <returns>성공 여부</returns>
	bool CreateDirectory(const std::wstring& _path);

	/// <summary>
	/// 디렉토리 내의 모든 파일 압축
	/// </summary>
	/// <param name="_path">디렉토리</param>
	/// <param name="outFile">압축 파일</param>
	/// <param name="currentPartPath">현재 압축 파일 경로</param>
	/// <param name="currentSize">현재 압축 파일 크기</param>
	/// <param name="partIndex">파트 번호</param>
	/// <param name="inBuffer">입력 버퍼</param>
	/// <param name="outBuffer">출력 버퍼</param>
	bool CompressDirectory(
		const std::wstring& _path
		, std::ofstream& outFile
		, size_t& currentSize
		, size_t& partIndex
		, std::vector<unsigned char>& inBuffer
		, std::vector<unsigned char>& outBuffer
	);
};

