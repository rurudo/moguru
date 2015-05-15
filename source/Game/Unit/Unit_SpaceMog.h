#pragma once
#include "Unit_SmallMog.h"
#include "../System/DxLibMath.h"

class Unit_SpaceMog :
	public Unit_SmallMog
{
private:
	int m_DefenceCount;			// ñhå‰ÉJÉEÉìÉg
	void Shot(float x, float y, bool isEnemy, bool blockHit = false);
public:
	Unit_SpaceMog(void);
	virtual ~Unit_SpaceMog(void);
	void Init(void);
	void AddDamage( int damage, int type, const VECTOR &value, UnitBase *enemy);
};

// ê∂ê¨ä÷êî
UnitBase* SpaceMog_CreateUnit(void);