#pragma once
#include "Unit_SmallMog.h"
#include "../System/DxLibMath.h"

class Unit_BigMog :
	public Unit_SmallMog
{
private:
	void Shot(float x, float y, bool isEnemy, bool blockHit = false);
public:
	Unit_BigMog(void);
	virtual ~Unit_BigMog(void);
	void Update(void);
	void AddDamage( int damage, int type, const VECTOR &value, UnitBase *enemy);
};

// ê∂ê¨ä÷êî
UnitBase* BigMog_CreateUnit(void);