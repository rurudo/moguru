#pragma once
#include "UnitBase.h"
#include "../System/DxLibMath.h"

class Unit_Chop :
	public UnitBase
{
private:
	virtual void Shot(float x, float y, bool isEnemy, bool blockHit = false, bool enemyHit = true);
	void MovePoint(void);
	void FreeMove(void);
	void EnemyMove(void);
public:
	Unit_Chop(void);
	virtual ~Unit_Chop(void);
	virtual void Update(void);
};

// ê∂ê¨ä÷êî
UnitBase* Chop_CreateUnit(void);