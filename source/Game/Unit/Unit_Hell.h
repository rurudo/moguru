#pragma once
#include "Unit_SmallMog.h"
#include "../System/DxLibMath.h"

class Unit_Hell :
	public Unit_SmallMog
{
private:
	int m_Count;			// フレームカウンタ
	void Shot(float x, float y, bool isEnemy, bool blockHit = false);
public:
	Unit_Hell(void);
	virtual ~Unit_Hell(void);
	void Init(void);
	void Update(void);
	void AddDamage( int damage, int type, const VECTOR &value, UnitBase *enemy);
};

// 生成関数
UnitBase* Hell_CreateUnit(void);