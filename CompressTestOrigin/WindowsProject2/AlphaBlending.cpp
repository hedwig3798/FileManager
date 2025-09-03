///fade in, out할 때 alphablend 쓰자 (추가사항, 안되더라도 함수 구현까지만 해보자)
#include "pch.h"
#include "AlphaBlending.h"
#include <wingdi.h>
#include "Texture.h"


/// 알파블랜딩
/// 주의! Per-Pixel Alpha Blending을 하려면,
/// 1. 알파채널이 있어야 함. (32비트)
/// 2. Pre-Multiplied Alpha Image이어야 함.


AlphaBlending::AlphaBlending()
	:m_memdc(nullptr)
	, m_hbit(nullptr)
	, m_bitInfo(0)
{	
}





AlphaBlending::~AlphaBlending()
{

}



