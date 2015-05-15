#pragma once
#include "Unit_Treasure.h"
#include "../System/DxLibMath.h"

class Unit_MetalTreasure :
	public Unit_Treasure
{
private:
	void Shot(float x, float y, bool isEnemy, bool blockHit = false, bool enemyHit = true);
public:
	Unit_MetalTreasure(void);
	virtual ~Unit_MetalTreasure(void);
	void AddDamage( int damage, int type, const VECTOR &value, UnitBase *enemy);
};

// ê∂ê¨ä÷êî
UnitBase* MetalTreasure_CreateUnit(void);