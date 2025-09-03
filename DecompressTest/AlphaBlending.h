#pragma once
///alt + c는 클래스에 하는 게 아니라, 함수에 하는 것이다

class AlphaBlending
{
public:
 //	void _AlphaBlend(HDC hdc, HINSTANCE hInst, int x, int y, int BitMap, unsigned char _Alpha);
	Texture* m_memdc;			//HDC는 DC의 handle값이다, 그 값을 저장하는 memdc
	Texture* m_hbit;			//HBITMAP은 옷(옷 자체)의 주소값
	Texture* m_bitInfo;			//BITMAP은 옷에 달린 태그(옷의 정보를 설명)

public:




public:
	AlphaBlending();
	~AlphaBlending();
};