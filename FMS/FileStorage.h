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
/// �ټ��� ������ �����ϰ� �ҷ����� ���� Ŭ����
/// </summary>
class FileStorage
{
private:
	/// <summary>
	/// ���� ���� ����ü
	/// </summary>
	struct FileEntry 
	{
		std::wstring name;			// ���� ���� �̸�
		std::wstring partPath;		// ���� ��Ʈ ���
		uint64_t offset;			// ���� ��Ʈ�� ���� ��ġ
		uint64_t compressedSize;	// ����� ���� ������
		uint64_t originalSize;		// ���� ���� ������
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
	/// ������ ���� ���� ��� ���� ���� ���� ��� �ε�
	/// </summary>
	void LoadCompressedFile();

	/// <summary>
	/// ��� ���� ��Ʈ�� �ʱ�ȭ
	/// </summary>
	void ClearFilestream();

	/// <summary>
	/// ��� ������ �̸��� ���
	/// </summary>
	void ShowAllFilename();

	/// <summary>
	/// ��Ʈ ���丮 ��������
	/// </summary>
	/// <returns>��Ʈ ���丮</returns>
	std::wstring GetRootDirectory() { return m_rootDir; };

	/// <summary>
	/// �ε� �� ��� ���� ����
	/// </summary>
	/// <returns>���� ����</returns>
	bool CompressAll();

	/// <summary>
	/// ������ ������ �ִ� ��� ���Ͽ� ���� ���� ����
	/// </summary>
	/// <returns>���� ����</returns>
	bool DecompressAll();

	/// <summary>
	/// �ε�� ��� ������ ������ ��ο� ����
	/// </summary>
	/// <param name="_path">���</param>
	void WriteAllFile(const std::wstring& _path);


private:
	/// <summary>
	/// ��� �Ʒ��� ��� ������ ���� �� ��Ʈ���� �����Ѵ�.
	/// </summary>
	/// <param name="_path">���</param>
	void LoadAll(const std::wstring& _path);

	/// <summary>
	/// ���丮 ����
	/// </summary>
	/// <param name="_path">�ش� ����� ���丮 ����</param>
	/// <returns>���� ����</returns>
	bool CreateDirectory(const std::wstring& _path);
};

