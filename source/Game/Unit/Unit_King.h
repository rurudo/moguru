#pragma once
#include "Unit_Treasure.h"
#include "../System/DxLibMath.h"

class Unit_King :
	public Unit_Treasure
{
private:
	void Shot(float x, float y, bool isEnemy, bool blockHit = false, bool enemyHit = true);
public:
	Unit_King(void);
	virtual ~Unit_King(void);
};

// ê∂ê¨ä÷êî
UnitBase* King_CreateUnit(void);