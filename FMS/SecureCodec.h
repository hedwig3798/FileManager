#pragma once
#define OUT
#include <vector>

#include <openssl/evp.h>
#include <openssl/rand.h>

namespace AES
{
	/// <summary>
	/// 암호호 및 복호화 함수
	/// </summary>
	/// <param name="_data">암복호화 할 데이터</param>
	/// <param name="_output">암복호화 한 데이터</param>
	/// <param name="_key">암호화 키</param>
	/// <param name="_initVector">CTR 시작 벡터</param>
	/// <returns>성공 여부</returns>
	bool CryptCTR(
		const std::vector<unsigned char>& _data
		, OUT std::vector<unsigned char>& _output
		, const unsigned char* _key
		, const unsigned char* _initVector);
};