#pragma once
#include "CObject.h"
#include "Texture.h"


class Texture;

class CutSceneObject: public CObject	///CObject의 상속을 받았으므로, Object가 아닌 다른 곳에서 만든 함수 쓸 수 없다. 그래서 CScene_Start에 있는 Exit함수 못쓴다
{
private:
	Texture* pTextureCutScene[4];		//다른 클래스에서 참조할 필요 없으므로 private에 둔다
	int index;
	float m_cutscenetime;

public:
	virtual void Update();
	virtual void Render(HDC _dc);
	
	virtual CutSceneObject* Clone() {return this;}
	///오브젝트 복사할 때 필요한 함수 ( 순수 가상 함수, 자식 클래스에서 구현 필요 )	virtual CObject* Clone() = 0; 
	///부모클래스의 함수 중에 순수가상함수가 있는 경우, 그것들 전부 다 구현을 해줘야 자식클래스가 순수가상클래스(아니면, 추상클래스)가 되지 않는다.
	/// 만약 순수가상함수를 구현안하면, 자식클래스가 순수가상클래스가 되는데 순수가상클래스는 객체를 만들 수 없어서 
	/// CCutScene.cpp의	CutSceneObject* pCutSceneObject = new CutSceneObject; 에서 오류가 났던것이다


public:
	CutSceneObject();
	~CutSceneObject();

};

