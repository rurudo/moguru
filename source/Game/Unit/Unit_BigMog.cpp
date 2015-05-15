#include "Unit_BigMog.h"
#include "../System/DataManager.h"
#include "../Task/TaskFunction.h"

UnitBase* BigMog_CreateUnit(void)
{
	return new Unit_BigMog();
}

Unit_BigMog::Unit_BigMog(void)
{
}

Unit_BigMog::~Unit_BigMog(void)
{
}

void Unit_BigMog::Shot(float x, float y, bool isEnemy, bool blockHit)
{
	if( !m_AttackEnable )
	{
		return;
	}
	VECTOR damageData;
	TaskSet_Shot( m_Power, UnitBase::DAMAGETYPE_NORMAL, damageData, m_x, m_y, x, y, isEnemy, blockHit, this);
}

void Unit_BigMog::Update(void)
{
	if( m_Life <= 0)
	{
		TaskSet_DeadCalc( m_x, m_y, this );
		m_Exist = false;
	}
	m_y += 0.01f;					// 下がっていく
	SetStatus();
	BadStatusUpdate();
	switch(m_MoveStatus)
	{
	case UnitBase::MovePoint:
		MovePoint();
		break;
	case UnitBase::Free:
		FreeMove();
		break;
	case UnitBase::Enemy:
		EnemyMove();
	default:
		break;
	}
	
}

void Unit_BigMog::AddDamage( int damage, int type, const VECTOR &value, UnitBase *enemy)
{
	// ダメージをカット
	int d = damage;
	if( d <= 30)
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
