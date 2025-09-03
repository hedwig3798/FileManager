///fade in, out할 때 alphablend 쓰자 (추가사항, 안되더라도 함수 구현까지만 해보자)
#include "pch.h"
//#include "AlphaBlend.h"
//
//AlphaBlenD::AlphaBlenD()
//{
//	BITMAP BitmapInfo;
//	HDC MemDC;
//	HBITMAP MyBitmap, OldBitmap;
//	BLENDFUNCTION bf;
//	MemDC = CreateCompatibleDC(hdc);
//}
//
////_AlphaBlend: hdc에서 BitMap으로 지정된 비트맵을 반투명하게 출력합니다. _Alpha 매개변수는 출력의 투명도를 지정하는데 사용됩니다.
//void AlphaBlenD::_AlphaBlend(HDC hdc, HINSTANCE hInst, int x, int y, int BitMap, unsigned char _Alpha)
//{
//	MyBitmap = LoadBitmap(hInst, MAKEINTRESOURCE(BitMap));// pre-multiplied alpha
//	OldBitmap = (HBITMAP)SelectObject(MemDC, MyBitmap);
//	GetObject(MyBitmap, sizeof(BITMAP), &BitmapInfo);
//	BitBlt(hdc, x, y, BitmapInfo.bmWidth, BitmapInfo.bmHeight, MemDC, 0, 0, SRCCOPY);
//
//
//	// Blend Function
//	bf.BlendOp = AC_SRC_OVER;
//	bf.BlendFlags = 0;
//	bf.AlphaFormat = AC_SRC_ALPHA;
//	bf.SourceConstantAlpha = (BYTE)_Alpha;	// 전체 알파값을 조절하며, pre-multiplied에 반영된다.
//
//	AlphaBlend(hdc, x, y, BitmapInfo.bmWidth, BitmapInfo.bmHeight, MemDC, 0, 0, BitmapInfo.bmWidth, BitmapInfo.bmHeight, bf); // blend function
//
//	SelectObject(MemDC, OldBitmap);
//	//DeleteObject(MyBitmap);
//	//DeleteDC(MemDC);
//
//}
//
//
//
//AlphaBlenD::~AlphaBlenD()
//{
//	DeleteObject(MyBitmap);
//	DeleteDC(MemDC);
//}
#include "AlphaBlend.h"
