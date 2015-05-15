#include "Unit_GoldenMog.h"
#include "../System/DataManager.h"
#include "../Task/TaskFunction.h"

UnitBase* GoldenMog_CreateUnit(void)
{
	return new Unit_GoldenMog();
}

Unit_GoldenMog::Unit_GoldenMog(void)
{
}

Unit_GoldenMog::~Unit_GoldenMog(void)
{
}

void Unit_GoldenMog::Shot(float x, float y, bool isEnemy, bool blockHit, bool enemyHit)
{
	if( !m_AttackEnable )
	{
		return;
	}
	VECTOR damageData;
	int power = m_Power;
	if( blockHit && !enemyHit)
	{
		power = static_cast<int>( power * 2.0f );
	}
	TaskSet_Shot( power, UnitBase::DAMAGETYPE_NORMAL, damageData, m_x, m_y, x, y, isEnemy, blockHit, this, enemyHit);
}
