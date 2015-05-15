#pragma once
#include "Unit_SmallMog.h"
#include "../System/DxLibMath.h"

class Unit_FrozenEX :
	public Unit_SmallMog
{
protected:
	void Shot(float x, float y, bool isEnemy, bool blockHit = false);
public:
	Unit_FrozenEX(void);
	virtual ~Unit_FrozenEX(void);
};

// ê∂ê¨ä÷êî
UnitBase* FrozenEX_CreateUnit(void);