#pragma once
#include "Unit_SmallMog.h"
#include "../System/DxLibMath.h"

class Unit_BombBox :
	public Unit_SmallMog
{
protected:
	void Shot(float x, float y, bool isEnemy, bool blockHit = false);
public:
	Unit_BombBox(void);
	virtual ~Unit_BombBox(void);
};

// ê∂ê¨ä÷êî
UnitBase* BombBox_CreateUnit(void);