#pragma once

class CObject;
class CTile;
class CLever;

void CreateObject(CObject* _pObj, GROUP_TYPE _eGroup);
void DeleteObject(CObject* _pObj);
void ChangeScene(SCENE_TYPE _eNext);
void TriggerOn(CTile* _ptile);
void LeverTriggerOn(CLever* _ptile);

// 
template<typename T>
void Safe_Delete_Vec(vector<T>& _vec)
{
	for (size_t i = 0; i < _vec.size(); i++)
	{
		if (_vec[i] != nullptr)
		{
			delete _vec[i];
		}
	}
	_vec.clear();
}

// map에서 T2는 포인터를 참고하고 있는 경우에 사용
// iter.second주소들의 메모리를 해제시키고
// map 클리어
template<typename T1, typename T2>
void Safe_Delete_map(map<T1, T2>& _map)
{
	typename map<T1, T2>::iterator iter = _map.begin();

	for (; iter != _map.end(); iter++)
	{
		if (nullptr != iter->second)
			delete iter->second;
	}
	_map.clear();
}