#include "Unit_BattleMog.h"
#include "../System/DataManager.h"
#include "../Task/TaskFunction.h"

UnitBase* BattleMog_CreateUnit(void)
{
	return new Unit_BattleMog();
}

Unit_BattleMog::Unit_BattleMog(void)
{
}

Unit_BattleMog::~Unit_BattleMog(void)
{
}

void Unit_BattleMog::Shot(float x, float y, bool isEnemy, bool blockHit)
{
	if( !m_AttackEnable )
	{
		return;
	}
	VECTOR damageData;
	TaskSet_Shot( m_Power, UnitBase::DAMAGETYPE_NORMAL, damageData, m_x, m_y, x, y, isEnemy, blockHit, this);
}