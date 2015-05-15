#include "Unit_Cuttlefish.h"
#include "../System/DataManager.h"
#include "../Task/TaskFunction.h"

UnitBase* Cuttlefish_CreateUnit(void)
{
	return new Unit_Cuttlefish();
}

Unit_Cuttlefish::Unit_Cuttlefish(void)
{
}

Unit_Cuttlefish::~Unit_Cuttlefish(void)
{
}

void Unit_Cuttlefish::Shot(float x, float y, bool isEnemy, bool blockHit)
{
	if( !m_AttackEnable )
	{
		return;
	}
	VECTOR damageData;
	damageData.x = 300.0f;
	damageData.y = 0.5f;
	TaskSet_Shot( m_Power, UnitBase::DAMAGETYPE_RANG, damageData, m_x, m_y, x, y, isEnemy, blockHit, this);
}