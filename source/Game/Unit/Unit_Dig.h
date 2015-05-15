#pragma once
#include "UnitBase.h"
#include "../System/DxLibMath.h"

class Unit_Dig :
	public UnitBase
{
private:
	virtual void Shot(float x, float y, bool isEnemy, bool blockHit = false, bool enemyHit = true);
	void MovePoint(void);
	void FreeMove(void);
	void EnemyMove(void);
public:
	Unit_Dig(void);
	virtual ~Unit_Dig(void);
	virtual void Update(void);
};

// ê∂ê¨ä÷êî
UnitBase* Dig_CreateUnit(void);