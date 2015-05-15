#pragma once
#include "UnitBase.h"
#include "../System/DxLibMath.h"

class Unit_FireMog :
	public UnitBase
{
protected:
	virtual void Shot(float x, float y, bool isEnemy, bool blockHit = false);
	void MovePoint(void);
	void FreeMove(void);
	void EnemyMove(void);
public:
	Unit_FireMog(void);
	virtual ~Unit_FireMog(void);
	virtual void Update(void);
};

// ê∂ê¨ä÷êî
UnitBase* FireMog_CreateUnit(void);