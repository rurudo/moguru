#include "Unit_Hell.h"
#include "../System/DataManager.h"
#include "../System/BlockManager.h"

#include "../Task/TaskFunction.h"

UnitBase* Hell_CreateUnit(void)
{
	return new Unit_Hell();
}

Unit_Hell::Unit_Hell(void)
{
}

Unit_Hell::~Unit_Hell(void)
{
}

void Unit_Hell::Init(void)
{
	Unit_SmallMog::Init();
	m_Count = 0;
}

void Unit_Hell::Shot(float x, float y, bool isEnemy, bool blockHit)
{
	if( !m_AttackEnable )
	{
		return;
	}
	VECTOR damageData;
	damageData.x = 60.0f;
	TaskSet_Shot( m_Power, UnitBase::DAMAGETYPE_STOP, damageData, m_x, m_y, x, y, isEnemy, blockHit, this);
}

void Unit_Hell::Update(void)
{
	if( m_Life <= 0)
	{
		m_Exist = false;
		TaskSet_DeadCalc( m_x, m_y, this );
		return;
	}
	VECTOR damageData;
	damageData.x = 5.0f;
	TaskSet_AreaUnitBadStatus( m_x, m_y, 0, 2.0f, UnitBase::DAMAGETYPE_STOP, damageData );
	m_Count++;
	Unit_SmallMog::Update();
	
}

void Unit_Hell::AddDamage( int damage, int type, const VECTOR &value, UnitBase *enemy)
{
	// ’âŽ~ó‘Ô‚ÍŽó‚¯•t‚¯‚È‚¢
	if( type == UnitBase::DAMAGETYPE_STOP)
	{
		return;
	}
	Unit_SmallMog::AddDamage( damage, type, value, enemy);
}
