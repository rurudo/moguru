#pragma once
#include "Unit_SmallMog.h"
#include "../System/DxLibMath.h"

class Unit_BombMog :
	public Unit_SmallMog
{
protected:
	void DeadCalc(void);
public:
	Unit_BombMog(void);
	virtual ~Unit_BombMog(void);
	void Update(void);
};

// ê∂ê¨ä÷êî
UnitBase* BombMog_CreateUnit(void);