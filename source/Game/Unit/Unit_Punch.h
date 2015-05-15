#pragma once
#include "Unit_SmallMog.h"
#include "../System/DxLibMath.h"

class Unit_Punch :
	public Unit_SmallMog
{
protected:
	void Shot(float x, float y, bool isEnemy, bool blockHit = false);
public:
	Unit_Punch(void);
	virtual ~Unit_Punch(void);
};

// ê∂ê¨ä÷êî
UnitBase* Punch_CreateUnit(void);