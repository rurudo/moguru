#pragma once
#include "Unit_Treasure.h"
#include "../System/DxLibMath.h"

class Unit_GoldenMog :
	public Unit_Treasure
{
private:
	void Shot(float x, float y, bool isEnemy, bool blockHit = false, bool enemyHit = true);
public:
	Unit_GoldenMog(void);
	virtual ~Unit_GoldenMog(void);
};

// ê∂ê¨ä÷êî
UnitBase* GoldenMog_CreateUnit(void);