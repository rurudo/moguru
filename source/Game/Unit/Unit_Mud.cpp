#include "Unit_Mud.h"
#include "../System/DataManager.h"
#include "../Task/TaskFunction.h"

UnitBase* Mud_CreateUnit(void)
{
	return new Unit_Mud();
}

Unit_Mud::Unit_Mud(void)
{
}

Unit_Mud::~Unit_Mud(void)
{
}

void Unit_Mud::Shot(float x, float y, bool isEnemy, bool blockHit)
{
	if( !m_AttackEnable )
	{
		return;
	}
	VECTOR damageData;
	damageData.x = 300.0f;
	damageData.y = 0.3f;
	TaskSet_Shot( m_Power, UnitBase::DAMAGETYPE_SLOW, damageData, m_x, m_y, x, y, isEnemy, blockHit, this);
}
