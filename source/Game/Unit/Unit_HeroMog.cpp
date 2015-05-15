#include "Unit_HeroMog.h"
#include "../System/DataManager.h"
#include "../Task/TaskFunction.h"

UnitBase* HeroMog_CreateUnit(void)
{
	return new Unit_HeroMog();
}

Unit_HeroMog::Unit_HeroMog(void)
{
}

Unit_HeroMog::~Unit_HeroMog(void)
{
}

void Unit_HeroMog::Shot(float x, float y, bool isEnemy, bool blockHit)
{
	if( !m_AttackEnable )
	{
		return;
	}
	VECTOR damageData;
	TaskSet_Shot( m_Power, UnitBase::DAMAGETYPE_NORMAL, damageData, m_x, m_y, x, y, isEnemy, blockHit, this);
}