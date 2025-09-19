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
/// �ټ��� ������ �����ϰ� �ҷ����� ���� Ŭ����
/// </summary>
class FileStorage
{
private:
	/// <summary>
	/// ���� ��� ���� ����ü
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
	/// ���� ���� ����ü
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
	/// ��� ������ �̸��� ���
	/// </summary>
	void ShowAllFilename();

	/// <summary>
	/// ��ο� �ִ� ��� ���� ����
	/// </summary>
	/// <returns>���� ����</returns>
	bool CompressAll(const std::wstring& _path);

	/// <summary>
	/// ���� ����
	/// </summary>
	/// <param name="_filename">���� �̸�.Ȯ����</param>
	/// <returns>���� ��Ʈ��</returns>
	std::istream* OpenFile(const std::wstring& _filename);

	/// <summary>
	/// �ε��� ���� �б�
	/// </summary>
	/// <returns>���� ����</returns>
	bool ResetCompressInfoMap();

private:

	/// <summary>
	/// ���丮 ����
	/// </summary>
	/// <param name="_path">�ش� ����� ���丮 ����</param>
	/// <returns>���� ����</returns>
	bool CreateDirectory(const std::wstring& _path);

	/// <summary>
	/// ���丮 ���� ��� ���� ����
	/// </summary>
	/// <param name="_path">���丮</param>
	/// <param name="outFile">���� ����</param>
	/// <param name="currentPartPath">���� ���� ���� ���</param>
	/// <param name="currentSize">���� ���� ���� ũ��</param>
	/// <param name="partIndex">��Ʈ ��ȣ</param>
	/// <param name="inBuffer">�Է� ����</param>
	/// <param name="outBuffer">��� ����</param>
	bool CompressDirectory(
		const std::wstring& _path
		, std::ofstream& outFile
		, size_t& currentSize
		, size_t& partIndex
		, std::vector<unsigned char>& inBuffer
		, std::vector<unsigned char>& outBuffer
	);
};

