#pragma once
#include "Unit_SmallMog.h"
#include "../System/DxLibMath.h"

class Unit_GalaxyMog :
	public Unit_SmallMog
{
private:
	int m_DefenceCount;			// �h��J�E���g
	void Shot(float x, float y, bool isEnemy, bool blockHit = false);
public:
	Unit_GalaxyMog(void);
	virtual ~Unit_GalaxyMog(void);
	void Init(void);
	void Update(void);
	void AddDamage( int damage, int type, const VECTOR &value, UnitBase *enemy);
};

// �����֐�
UnitBase* GalaxyMog_CreateUnit(void);