#include "pch.h"
#include "CBoard.h"

CBoard::CBoard()
{
}

CBoard::~CBoard()
{

}

void CBoard::Update()
{

}

void CBoard::render(HDC _dc)
{
	Vector2 curPos = GetPos();
	Vector2 curScale = GetScale();
	Rectangle(_dc, (int)curPos.x, (int)curPos.y, (int)curPos.x + (int)curScale.x, (int)curPos.y + (int)curScale.y);
}