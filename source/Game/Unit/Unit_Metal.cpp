#include "Unit_Metal.h"
#include "../System/DataManager.h"
#include "../Task/TaskFunction.h"

UnitBase* Metal_CreateUnit(void)
{
	return new Unit_Metal();
}

Unit_Metal::Unit_Metal(void)
{
}

Unit_Metal::~Unit_Metal(void)
{
}

void Unit_Metal::Shot(float x, float y, bool isEnemy, bool blockHit)
{
	if( !m_AttackEnable )
	{
		return;
	}
	VECTOR damageData;
	TaskSet_Shot( m_Power, UnitBase::DAMAGETYPE_NORMAL, damageData, m_x, m_y, x, y, isEnemy, blockHit, this);
}

void Unit_Metal::AddDamage( int damage, int type, const VECTOR &value, UnitBase *enemy)
{
	// ダメージをカット
	int d = static_cast<int>(damage * 0.7f);
	if( d < 1)
	{
		d = 1;
	}
	VECTOR data = value;
	if( type == UnitBase::DAMAGETYPE_MOVE )
	{
		data.x = 0.0f;
	}
	Unit_SmallMog::AddDamage( d, type, data, enemy );
}
