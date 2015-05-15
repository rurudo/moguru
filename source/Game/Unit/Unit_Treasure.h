#pragma once
#include "UnitBase.h"
#include "../System/DxLibMath.h"

class Unit_Treasure :
	public UnitBase
{
private:
	virtual void Shot(float x, float y, bool isEnemy, bool blockHit = false, bool enemyHit = true);
	void MovePoint(void);
	void FreeMove(void);
	void EnemyMove(void);
public:
	Unit_Treasure(void);
	virtual ~Unit_Treasure(void);
	virtual void Update(void);
};

// ê∂ê¨ä÷êî
UnitBase* Treasure_CreateUnit(void);