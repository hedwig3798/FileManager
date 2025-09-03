#pragma once
#include "CObject.h"
class CDoor :
    public CObject
{
private:
	bool IsOpen;
	Vector2 Pos;
	bool Once;

public:
	virtual void Update();
	virtual void Render(HDC _dc);

	void SetDoor()
	{
		if (IsOpen)
		{
			IsOpen = false;
		}
		else
		{
			IsOpen = true;
		}
	}
	bool GetDoorState() { return IsOpen; }


public:
	virtual CDoor* Clone() { return this; }

public:
	CDoor();
	~CDoor();
};

