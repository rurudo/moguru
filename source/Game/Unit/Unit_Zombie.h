#pragma once
#include "Unit_SmallMog.h"
#include "../System/DxLibMath.h"

class Unit_Zombie :
	public Unit_SmallMog
{
protected:
	int m_Count;			// €–SŒã‚ÌƒJƒEƒ“ƒg
	void DeadCalc(void);
public:
	Unit_Zombie(void);
	virtual ~Unit_Zombie(void);
	void Update(void);
	void Init(void);
};

// ¶¬ŠÖ”
UnitBase* Zombie_CreateUnit(void);