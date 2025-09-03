#include "pch.h"
#include "Texture.h"

Texture::Texture(HDC _dc)
	:m_memdc(nullptr)	///
	,m_hbit(nullptr)	///
	,m_bitInfo()
{
	m_memdc = CreateCompatibleDC(_dc);	/// _dc값과 호환이 되는 dc값을 하나 만들어서 m_memdc에 저장한다. 
										///(m_memdc는 HDC이다(HDC는 DC의 handle값. handle이 DC를 가리킴). handle이 가리키는 값(DC)은 소멸자가 사라질 때 함께 사라지지 않는다
}										///handle인 m_memdc는 소멸자가 실행될 때 같이 사라진다

Texture::~Texture()
{
	//소멸할 때 클래스 내부에 있는 멤버변수는 굳이 소멸자 안에 적지 않더라도, 클래스가 소멸될 때 같이 소멸된다
	//하지만 클래스 외부에 있는 변수(예를 들어 _dc)는 소멸되지 않는다
	//주로 동적할당할때 동적할당된 변수는 소멸자에 적지 않으면 사라지지 않는다. 
	//소멸자에 delete 써줘야 사라진다

	//리팩토링 전에는 클래스의 함수에서 memdc를 새로 생성했기 때문에, 그 값을 소멸자에 써서 삭제했어야하지만
	//리팩토링 후에는 _dc값을 그대로 받아오기때문에, 삭제하면 안된다. (_dc를 공유하는 모든 함수들에 문제가 생긴다)
	
	//클래스에 새로 추가된 것만 소멸자에 써서 같이 없애야한다. 비트맵 이미지만 추가되었으니, 이를 삭제한다
	DeleteObject(m_hbit);
	DeleteDC(m_memdc);	///DeleteDC는 m_memdc가 가리키는 값인 DC를 삭제한다(위에서 언급했듯이, DC는 소멸자가 실행되어도 사라지지 않기때문)
						///m_memdc는 HDC이므로, DC의 handle값이다. handle이 가리키는 DC값을 삭제하는거다

	//텍스쳐 클래스에 HBITMAP이 저장된다
	//텍스쳐 클래스는 TextureManager에 저장되어 TextManager에서 관리한다
	//프로그램이 "종료"될 때 소멸자가 실행되어 비트맵이미지가 삭제된다
}



void Texture::Load(const wstring& _strFilePath)
{
	//윈도우에 저장된 함수인 LoadImage 함수로 비트맵 불러온다
	m_hbit = (HBITMAP)LoadImage(nullptr, _strFilePath.c_str(), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	assert(m_hbit);

	//기존의 것은 비트맵과 연결할 DC를 만들었지만, 리팩토링 후에는 Texture가 _dc를 이미 받아와서 한 클래스 안에 _dc와 비트맵이 같이 있어서 이 과정이 필요가 없다

	//DC와 비트맵을 연결만 하면 된다. 이때 SelectObject 함수 쓴다
	SelectObject(m_memdc, m_hbit);

	//비트맵 정보는 GetObject함수 쓴다
	GetObject(m_hbit, sizeof(BITMAP), &m_bitInfo);
}
