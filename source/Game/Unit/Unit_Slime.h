#pragma once
#include "Unit_SmallMog.h"
#include "../System/DxLibMath.h"

class Unit_Slime :
	public Unit_SmallMog
{
protected:
	void Shot(float x, float y, bool isEnemy, bool blockHit = false);
public:
	Unit_Slime(void);
	virtual ~Unit_Slime(void);
};

// ê∂ê¨ä÷êî
UnitBase* Slime_CreateUnit(void);