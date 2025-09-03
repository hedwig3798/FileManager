#pragma once


// 펜과 브러쉬를 만들고 세팅하고 쓰고 난 다음에 기본 펜과 브러쉬로 되돌려보내기 위한 클래스
// 지역 변수로 생성하고 쓰고 해당 함수가 종료되면 지역 변수여서 없어지면서 소멸자가 발생하면서 소멸자에서 기본 세팅으로 전환 후 삭제된다.
class SelectGDI
{
private:
	HDC		m_hDC;
	HPEN	m_hDefaultPen;
	HBRUSH	m_hDefaultBrush;

public:
	

public:
	~SelectGDI();
};