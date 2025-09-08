#include <iostream>
#include "FileStorage.h"

int main()
{
	FileStorage fms;

	fms.SetOutputFileName(L"comTest_");
	fms.SetCompressExtension(L".rcom");
	fms.SetCompressFilePath(L"E:\\FMS\\CompressTest");

	if (false == fms.CompressAll(L"E:\\FMS\\CompressTestOrigin"))
	{
		return 0;
	}

	std::istream* testFile;
	testFile = fms.OpenFile(L"AlphaBlend.h");
	if (!testFile)
	{
		return 0;
	}
	std::wstring content((std::istreambuf_iterator<char>(*testFile)), std::istreambuf_iterator<char>());

	std::wcout << content;

	return 0;
}