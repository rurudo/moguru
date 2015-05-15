#pragma once
#include "Unit_SmallMog.h"
#include "../System/DxLibMath.h"

class Unit_Mud :
	public Unit_SmallMog
{
protected:
	void Shot(float x, float y, bool isEnemy, bool blockHit = false);
public:
	Unit_Mud(void);
	virtual ~Unit_Mud(void);
};

// ê∂ê¨ä÷êî
UnitBase* Mud_CreateUnit(void);