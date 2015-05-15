#include "Unit_Slime.h"
#include "../System/DataManager.h"
#include "../Task/TaskFunction.h"

UnitBase* Slime_CreateUnit(void)
{
	return new Unit_Slime();
}

Unit_Slime::Unit_Slime(void)
{
}

Unit_Slime::~Unit_Slime(void)
{
}

void Unit_Slime::Shot(float x, float y, bool isEnemy, bool blockHit)
{
	if( !m_AttackEnable )
	{
		return;
	}
	VECTOR damageData;
	damageData.x = 0.5f;
	TaskSet_Shot( m_Power, UnitBase::DAMAGETYPE_LIFESTEAL, damageData, m_x, m_y, x, y, isEnemy, blockHit, this);
}