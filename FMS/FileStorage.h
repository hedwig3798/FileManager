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

/// <summary>
/// File Management System
/// 다수의 파일을 저장하고 불러오기 위한 클래스
/// </summary>
class FileStorage
{
private:
	/// <summary>
	/// 파일 정보 구조체
	/// </summary>
	struct FileEntry 
	{
		std::wstring name;			// 파일 원본 이름
		std::wstring partPath;		// 압축 파트 경로
		uint64_t offset;			// 압축 파트의 시작 위치
		uint64_t compressedSize;	// 압축된 파일 사이즈
		uint64_t originalSize;		// 원본 파일 사이즈
	};

	std::map<std::wstring, std::unique_ptr<std::ifstream>> m_filemap;
	std::map<std::wstring, FileEntry> m_fileEntrymap;
	std::wstring m_rootDir;

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
	std::ifstream* GetFileStream(const std::wstring& _fileName);

	void SetRootDirectory(const std::wstring& _root) { m_rootDir = _root; };
	void SetCompressExtension(const std::wstring& _extension) { m_comExtension = _extension; };
	void SetDecompressOutputPath(const std::wstring& _path) { m_decompressPath = _path; };
	void SetCompressOutputPath(const std::wstring& _path) { m_compressPath = _path; };
	void SetOutputFileName(const std::wstring& _name) { m_comFilename = _name; };

	/// <summary>
	/// 설정된 압축 파일 경로 내의 압축 파일 모든 로드
	/// </summary>
	void LoadCompressedFile();

	/// <summary>
	/// 모든 파일 스트림 초기화
	/// </summary>
	void ClearFilestream();

	/// <summary>
	/// 모든 파일의 이름을 출력
	/// </summary>
	void ShowAllFilename();

	/// <summary>
	/// 루트 디렉토리 가져오기
	/// </summary>
	/// <returns>루트 디렉토리</returns>
	std::wstring GetRootDirectory() { return m_rootDir; };

	/// <summary>
	/// 로드 된 모든 파일 압축
	/// </summary>
	/// <returns>성공 여부</returns>
	bool CompressAll();

	/// <summary>
	/// 지정된 폴더에 있는 모든 파일에 대해 압축 해제
	/// </summary>
	/// <returns>성공 여부</returns>
	bool DecompressAll();

	/// <summary>
	/// 로드된 모든 파일을 지정된 경로에 쓰기
	/// </summary>
	/// <param name="_path">경로</param>
	void WriteAllFile(const std::wstring& _path);


private:
	/// <summary>
	/// 경로 아래의 모든 파일을 읽은 후 스트림을 저장한다.
	/// </summary>
	/// <param name="_path">경로</param>
	void LoadAll(const std::wstring& _path);

	/// <summary>
	/// 디렉토리 생성
	/// </summary>
	/// <param name="_path">해당 경로의 디렉토리 생성</param>
	/// <returns>성공 여부</returns>
	bool CreateDirectory(const std::wstring& _path);
};

