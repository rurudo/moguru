#pragma once
#include "Unit_SmallMog.h"
#include "../System/DxLibMath.h"

class Unit_Thunder :
	public Unit_SmallMog
{
protected:
	void Shot(float x, float y, bool isEnemy, bool blockHit = false);
public:
	Unit_Thunder(void);
	virtual ~Unit_Thunder(void);
};

// ê∂ê¨ä÷êî
UnitBase* Thunder_CreateUnit(void);