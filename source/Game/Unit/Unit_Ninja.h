#pragma once
#include "Unit_SmallMog.h"
#include "../System/DxLibMath.h"

class Unit_Ninja :
	public Unit_SmallMog
{
private:
	void Shot(float x, float y, bool isEnemy, bool blockHit = false);
public:
	Unit_Ninja(void);
	virtual ~Unit_Ninja(void);
	void AddDamage( int damage, int type, const VECTOR &value, UnitBase *enemy);
};

// ê∂ê¨ä÷êî
UnitBase* Ninja_CreateUnit(void);