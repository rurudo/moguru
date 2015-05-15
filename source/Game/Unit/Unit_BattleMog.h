#pragma once
#include "Unit_SmallMog.h"
#include "../System/DxLibMath.h"

class Unit_BattleMog :
	public Unit_SmallMog
{
private:
	void Shot(float x, float y, bool isEnemy, bool blockHit = false);
public:
	Unit_BattleMog(void);
	virtual ~Unit_BattleMog(void);
};

// ê∂ê¨ä÷êî
UnitBase* BattleMog_CreateUnit(void);