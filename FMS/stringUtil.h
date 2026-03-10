#pragma once

#include <string>
#include <windows.h>

uint32_t WstringByteSize(const std::wstring& str);
std::string WstrToStr(const std::wstring& wstr, UINT codePage = CP_UTF8);
