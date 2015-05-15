#include "Unit_Ninja.h"
#include "../System/DataManager.h"
#include "../Task/TaskFunction.h"

UnitBase* Ninja_CreateUnit(void)
{
	return new Unit_Ninja();
}

Unit_Ninja::Unit_Ninja(void)
{
}

Unit_Ninja::~Unit_Ninja(void)
{
}

void Unit_Ninja::Shot(float x, float y, bool isEnemy, bool blockHit)
{
	if( !m_AttackEnable )
	{
		return;
	}
	VECTOR damageData;
	TaskSet_Shot( m_Power, UnitBase::DAMAGETYPE_NORMAL, damageData, m_x, m_y, x, y, isEnemy, blockHit, this);
}

void Unit_Ninja::AddDamage( int damage, int type, const VECTOR &value, UnitBase *enemy)
{
	// ÉuÉçÉbÉNÇ©ÇÁÇÃçUåÇÇÕéÛÇØÇ»Ç¢
	if( type != UnitBase::DAMAGETYPE_BLOCK)
	{
		Unit_SmallMog::AddDamage( damage, type, value, enemy );
	}
}
