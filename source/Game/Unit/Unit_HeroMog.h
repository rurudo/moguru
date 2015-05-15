#pragma once
#include "Unit_SmallMog.h"
#include "../System/DxLibMath.h"

class Unit_HeroMog :
	public Unit_SmallMog
{
private:
	void Shot(float x, float y, bool isEnemy, bool blockHit = false);
public:
	Unit_HeroMog(void);
	virtual ~Unit_HeroMog(void);
};

// ê∂ê¨ä÷êî
UnitBase* HeroMog_CreateUnit(void);