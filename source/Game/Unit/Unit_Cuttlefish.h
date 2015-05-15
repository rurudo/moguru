#pragma once
#include "Unit_SmallMog.h"
#include "../System/DxLibMath.h"

class Unit_Cuttlefish :
	public Unit_SmallMog
{
protected:
	void Shot(float x, float y, bool isEnemy, bool blockHit = false);
public:
	Unit_Cuttlefish(void);
	virtual ~Unit_Cuttlefish(void);
};

// �����֐�
UnitBase* Cuttlefish_CreateUnit(void);