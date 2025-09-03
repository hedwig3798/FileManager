#pragma once

class TextureManager;
//class CResMgr;	//TextureManager 만들고 지운다

class Texture		//texture 파일을 저장하는 클래스, :는 부모, 자식클래스 나타낼때만 쓴다 ( class 자식: public 부모)
{
	//public 쓰지않는 이유: 다른 사람들이 변수 마음대로 접근 못하게 하려고
private:
	HBITMAP		m_hbit;				//HBITMAP은 옷(옷 자체)의 주소값
	BITMAP		m_bitInfo;			//BITMAP은 옷에 달린 태그(옷의 정보를 설명)
	HDC			m_memdc;			//HDC는 DC의 handle값이다, 그 값을 저장하는 memdc

public:
	void Load(const wstring& _strFilePath);

	///정말 간단한 함수 (구현부분(정의)이 한줄짜리 인 함수)는 h파일에 쓰는 것이 더 효율적이다
	UINT Width() { return m_bitInfo.bmWidth; }
	UINT Height() { return m_bitInfo.bmHeight; }

	HDC GetDC() { return m_memdc; }		///쓰고싶지 않았지만 쓰게 되었다

public:
	Texture(HDC _dc);		//정의할 때 받았던 인자는 선언할때 자료형 똑같이 받는다(함수랑 비슷해)
	~Texture();
	//상속이 없으니 virtual은 안써도 된다

	///friend class로 지정된 클래스는 private에 접근 가능하다
	friend class TextureManager;
	//friend class CResMgr;	//TextureManager 만들고 지운다
};

