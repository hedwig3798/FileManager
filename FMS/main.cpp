#include <iostream>
#include "FileStorage.h"

int main()
{
	FileStorage fms;

	fms.SetRootDirectory(L"E:\\FMS\\CompressTestOrigin");
	fms.SetCompressExtension(L".rcom");
	fms.SetCompressOutputPath(L"E:\\FMS\\CompressTest");
	fms.SetDecompressOutputPath(L"E:\\FMS\\DecompressTest");

	// fms.ShowAllFilename();

	fms.CompressAll();
	fms.DecompressAll();
	return 0;
}