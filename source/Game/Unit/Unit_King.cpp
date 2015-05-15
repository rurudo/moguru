#include "Unit_King.h"
#include "../System/DataManager.h"
#include "../Task/TaskFunction.h"

UnitBase* King_CreateUnit(void)
{
	return new Unit_King();
}

Unit_King::Unit_King(void)
{
}

Unit_King::~Unit_King(void)
{
}

void Unit_King::Shot(float x, float y, bool isEnemy, bool blockHit, bool enemyHit)
{
	if( !m_AttackEnable )
	{
		return;
	}
	VECTOR damageData;
	int power = m_Power;
	if( blockHit && !enemyHit)
	{
		power = static_cast<int>( power * 3.0f );
	}
	TaskSet_Shot( power, UnitBase::DAMAGETYPE_NORMAL, damageData, m_x, m_y, x, y, isEnemy, blockHit, this, enemyHit);
}
