#include "Unit_Guardian.h"
#include "../System/DataManager.h"
#include "../Task/TaskFunction.h"

UnitBase* Guardian_CreateUnit(void)
{
	return new Unit_Guardian();
}

Unit_Guardian::Unit_Guardian(void)
{
}

Unit_Guardian::~Unit_Guardian(void)
{
}

void Unit_Guardian::Shot(float x, float y, bool isEnemy, bool blockHit)
{
	if( !m_AttackEnable )
	{
		return;
	}
	VECTOR damageData;
	TaskSet_Shot( m_Power, UnitBase::DAMAGETYPE_NORMAL, damageData, m_x, m_y, x, y, isEnemy, blockHit, this);
}

void Unit_Guardian::AddDamage( int damage, int type, const VECTOR &value, UnitBase *enemy)
{
	// ダメージをカット
	int d = static_cast<int>(damage * 0.7f);
	if( d < 1)
	{
		d = 1;
	}
	Unit_SmallMog::AddDamage( d, type, value, enemy );
}
