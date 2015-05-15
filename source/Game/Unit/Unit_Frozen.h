#pragma once
#include "Unit_SmallMog.h"
#include "../System/DxLibMath.h"

class Unit_Frozen :
	public Unit_SmallMog
{
protected:
	void Shot(float x, float y, bool isEnemy, bool blockHit = false);
public:
	Unit_Frozen(void);
	virtual ~Unit_Frozen(void);
};

// ê∂ê¨ä÷êî
UnitBase* Frozen_CreateUnit(void);