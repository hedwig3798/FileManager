#include "pch.h"
#include "TextureManager.h"
#include "CPathManager.h"
#include "Texture.h"


TextureManager::TextureManager()
	:m_hDC(0)	//m_hDC를 처음 만들때 0으로 만든다
				//그리고 CGameProcess에서 만든 m_hDC값을 대입할 것이다
{
	
}

TextureManager::~TextureManager()
{
	Safe_Delete_map(m_mapTexture);
}

///오브젝트들에서 텍스처 파일을 로드할 때 해당 텍스처를 저장할 map의 key의 이름과
///_strRelativePath: content 폴더의 다음 경로와 파일 이름
Texture* TextureManager::LoadTexture(const wstring& _strKey, const wstring& _strRelativePath)
{
	//현재 map에서 해당 텍스쳐 파일이 이미 로드된 상태라면 헤당 텍스쳐 파일 반환
	Texture* pTexture = FindTexture(_strKey);
	if (nullptr != pTexture)
	{
		return pTexture;
	}

	//없으면 텍스쳐 파일 불러와야한다
	//CPathManager에서 경로를 찾아온다. strFilePath=L "Output\\bin\\contest"
	wstring strFilePath = CPathManager::GetInstance()->GetContentPath();

	//strFilePath에서 다음 경로와 가져올 텍스쳐 파일의 이름을 매개변수로 받아왔기 때문에 추가해주면 된다
	strFilePath += _strRelativePath;

	//텍스처 객체의 메모리를 할당받고
	//Texture의 Load() 함수에서 이미지 파일 가져오고 Key와 상대경로 세팅
	pTexture = new Texture(m_hDC);
	pTexture->Load(strFilePath);

	//map에 Key와 해당 Texture의 주소 입력
	m_mapTexture.insert(make_pair(_strKey, pTexture));

	//로드받은 Texture를 반환
	return pTexture;
}

///map에 지정된 키에 Texture가 있는지 확인
Texture* TextureManager::FindTexture(const wstring& _strkey)
{
	map<wstring, Texture*>::iterator iter = m_mapTexture.find(_strkey);

	if (iter == m_mapTexture.end())
	{
		return nullptr;
	}
	return (Texture*)iter->second;
}





