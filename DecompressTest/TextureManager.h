#pragma once

class Texture;

class TextureManager
{
	//싱글턴 문법 모아
public:
	///싱글턴 하는 이유: data영역에 생성된 mgr객체의 주소값을 GetInst함수로 가져와서, 
	/// Animal클래스의 유일한 객체인 mgr의 a값을 10으로 수정(싱글턴을 써서 객체의 변수의 값 수정하는 방법)
	/// mgr는 실행부터 종료까지 무조건 1개만 존재해야한다. 그래서 싱글턴으로 만드는것이다.
	///싱글턴은 헤더파일에 구현한다
	static TextureManager* GetInstance()
	{
		static TextureManager TextureManagerSingleton;
		return &TextureManagerSingleton;
	}
	///객체가 1개만 생성되어야 하므로 private
private:
	TextureManager();
	~TextureManager();

	//public 함수들만 모았다
public:
	//비트맵 이미지를 불러온다
	//필요한 것: 비트맵 이미지의 상대경로 
	Texture* LoadTexture(const wstring& _strKey, const wstring& _strRelativePath);
	//비트맵 이미지를 1번만 불러왔는지 확인한다
	Texture* FindTexture(const wstring& _strkey);

	//public 변수들만 모았다
public:
	map<wstring, Texture* > m_mapTexture;	//map에 저장할 Texture
	HDC m_hDC;	///DC의 핸들값. 
				///쓰는 이유:  CGameProcess에서 만든 m_hDC값을 대입하기 위해서이다
};


