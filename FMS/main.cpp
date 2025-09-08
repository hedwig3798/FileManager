#include <iostream>
#include "FileStorage.h"

int main()
{
	FileStorage fms;

	fms.SetOutputFileName(L"comTest_");
	fms.SetCompressExtension(L".rcom");
	fms.SetCompressFilePath(L"E:\\FMS\\CompressTest");

	fms.CompressAll(L"E:\\FMS\\CompressTestOrigin");

	std::istream* testFile;
	testFile = fms.OpenFile(L"AlphaBlend.h");

	std::wstring content((std::istreambuf_iterator<char>(*testFile)), std::istreambuf_iterator<char>());

	std::wcout << content;

	return 0;
}