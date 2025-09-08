#include "MemoryFileStream.h"

MemoryFileStreamBuf::MemoryFileStreamBuf(const std::vector<char>& _data)
{
	// ������ ������
	char* base = const_cast<char*>(_data.data());
	// ���� ���� ����
	setg(base, base, base + _data.size());
}

MemoryFileStream::MemoryFileStream(std::vector<char>&& _data)
	: std::istream(&m_buf)
	, m_data(_data)
	, m_buf(m_data)
{
}
