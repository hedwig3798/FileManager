#include "pch.h"
#include "CCollisionManager.h"

#include "CScene.h"
#include "CSceneManager.h"
#include "CObject.h"
#include "CCollider.h"

CCollisionManager::CCollisionManager()
	:m_arrCheck{}
{

}
CCollisionManager::~CCollisionManager()
{

}

void CCollisionManager::Initialize()
{
}

// 
void CCollisionManager::Update()
{
	for (UINT iRow = 0; iRow < (UINT)GROUP_TYPE::END; ++iRow)
	{
		for (UINT iCol = 0; iCol < (UINT)GROUP_TYPE::END; ++iCol)
		{
			if (m_arrCheck[iRow] & (1 << iCol))
			{
				CollisionGroupUpdate((GROUP_TYPE)iRow, (GROUP_TYPE)iCol);
			}
		}
	}
}

// 서로 충돌되는 오브젝트 확인
void CCollisionManager::CollisionGroupUpdate(GROUP_TYPE e_Left, GROUP_TYPE _eRight)
{
	CScene* pCurScene = CSceneManager::GetInstance()->GetCurScene();
	map<ULONGLONG, bool>::iterator iter;

	vector<CObject*> vecLeft = pCurScene->GetGroupObject(e_Left);
	vector<CObject*> vecRight = pCurScene->GetGroupObject(_eRight);
	
	for (size_t i = 0; i < vecLeft.size(); i++)
	{
		// 충돌체를 보유하지 않는 경우
		if (nullptr == vecLeft[i]->GetCollider())
			continue;

		for (size_t j = 0; j < vecRight.size(); j++)
		{
			// 충돌체가 없거나, 자기 자신과의 충돌인 경우
			if (nullptr == vecRight[j]->GetCollider()
				|| vecLeft[i] == vecRight[j])
				continue;

			CCollider* pLeftCol = vecLeft[i]->GetCollider();
			CCollider* pRightCol = vecRight[j]->GetCollider();


			// 두 충돌체 조합 아이디 생성
			COLLIDER_ID ID;
			ID.Left_id = pLeftCol->GetID();
			ID.Right_id = pRightCol->GetID();

			iter =  m_mapColInfo.find(ID.ID);

			// 충돌 정보가 미 등록 상태인 경우 등록 (초기 상태 : 충돌하지 않았다)
			if (m_mapColInfo.end() == iter)
			{
				m_mapColInfo.insert(make_pair(ID.ID, false));
				iter = m_mapColInfo.find(ID.ID);
			}

			// 두 충돌체가 충돌하고 있나?
			if (IsCollision(pLeftCol, pRightCol))
			{
				// 현재 충돌 중이다.
				if (iter->second)
				{
					// 이전에도 충돌 하고 있었다.
					if (vecLeft[i]->IsDead() || vecRight[j]->IsDead())
					{
						// 둘 중 하나가 삭제 예정이라면, 충돌 해제시켜준다.
						pLeftCol->OnCollisionExit(pRightCol);
						pRightCol->OnCollisionExit(pLeftCol);
						iter->second = false;
					}
					else
					{
						pLeftCol->OnCollision(pRightCol);
						pRightCol->OnCollision(pLeftCol);
						iter->second = true;
					}
				}
				else
				{
					// 이전에는 충돌하지 않았다. ( 처음 충돌한 상태 )
					// 둘 중 하나가 삭제 예정이라면, 충돌하지 않은 것으로 취급
					if (!vecLeft[i]->IsDead() && !vecRight[j]->IsDead())
					{
						pLeftCol->OnCollisionEnter(pRightCol);
						pRightCol->OnCollisionEnter(pLeftCol);
						iter->second = true;
					}
				}
			}
			else
			{
				// 현재 충돌하고 있지 않다.
				if (iter->second)
				{
					// 이전에는 충돌하고 있었다.
					pLeftCol->OnCollisionExit(pRightCol);
					pRightCol->OnCollisionExit(pLeftCol);
					iter->second = false;
				}

			}
		}
	}
}

// 두 충돌체에 대한 충돌 검사
bool CCollisionManager::IsCollision(CCollider* _pLeftCol, CCollider* _pRightCol)
{
	// 둘 중 하나라도 활성 오브젝트가 아니면 충돌 처리 안함
	if (!_pLeftCol->GetObj()->m_bActive || !_pRightCol->GetObj()->m_bActive)
	{
		return false;
	}
	Vector2 vLeftPos = _pLeftCol->GetFinalPos();
	Vector2 vLeftScale = _pLeftCol->GetScale();
	
	Vector2 vRightPos = _pRightCol->GetFinalPos();
	Vector2 vRightScale = _pRightCol->GetScale();

	// 두 콜리전이 겹쳤을 때 true
	if (abs(vRightPos.x - vLeftPos.x) < (vLeftScale.x + vRightScale.x) / 2.f
		&& abs(vRightPos.y - vLeftPos.y) < (vLeftScale.y + vRightScale.y) / 2.f)
	{
		return true;
	}

	return false;
}

void CCollisionManager::CheckGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight)
{
	// 비트 연산자를 사용
	// 더 작은 값의 그룹 타입을 행으로,
	// 큰 값을 열(비트) 로 사용

	UINT iRow = (UINT)_eLeft;
	UINT iCol = (UINT)_eRight;

	if (iCol < iRow)
	{
		iRow = (UINT)_eRight;
		iCol = (UINT)_eLeft;
	}

	// 만약 충돌 상태를 체크한 상태에서 다시 선택하면 체크 아웃
	if (m_arrCheck[iRow] & (1 << iCol))
	{
		m_arrCheck[iRow] &= ~(1 << iCol);
	}
	else
	{
		m_arrCheck[iRow] |= (1 << iCol);
	}

}
