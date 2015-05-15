#pragma once
#include "Unit_SmallMog.h"
#include "../System/DxLibMath.h"

class Unit_Guardian :
	public Unit_SmallMog
{
private:
	void Shot(float x, float y, bool isEnemy, bool blockHit = false);
public:
	Unit_Guardian(void);
	virtual ~Unit_Guardian(void);
	void AddDamage( int damage, int type, const VECTOR &value, UnitBase *enemy);
};

// ê∂ê¨ä÷êî
UnitBase* Guardian_CreateUnit(void);