#include "Unit_Frozen.h"
#include "../System/DataManager.h"
#include "../Task/TaskFunction.h"

UnitBase* Frozen_CreateUnit(void)
{
	return new Unit_Frozen();
}

Unit_Frozen::Unit_Frozen(void)
{
}

Unit_Frozen::~Unit_Frozen(void)
{
}

void Unit_Frozen::Shot(float x, float y, bool isEnemy, bool blockHit)
{
	if( !m_AttackEnable )
	{
		return;
	}
	VECTOR damageData;
	damageData.x = 60.0f;
	TaskSet_Shot( m_Power, UnitBase::DAMAGETYPE_STOP, damageData, m_x, m_y, x, y, isEnemy, blockHit, this);
}