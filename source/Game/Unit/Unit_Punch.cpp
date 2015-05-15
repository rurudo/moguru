#include "Unit_Punch.h"
#include "../System/DataManager.h"
#include "../Task/TaskFunction.h"

UnitBase* Punch_CreateUnit(void)
{
	return new Unit_Punch();
}

Unit_Punch::Unit_Punch(void)
{
}

Unit_Punch::~Unit_Punch(void)
{
}

void Unit_Punch::Shot(float x, float y, bool isEnemy, bool blockHit)
{
	if( !m_AttackEnable )
	{
		return;
	}
	// êÅÇ´îÚÇŒÇµó ÇÃåvéZ
	VECTOR damageData;
	damageData.x = x - m_x;
	damageData.y = y - m_y;
	DXLibMath::Normalize( &damageData, damageData );
	damageData.z = damageData.y * 0.8f;
	damageData.y = damageData.x * 0.8f;
	damageData.x = 5.0f;
	TaskSet_Shot( m_Power, UnitBase::DAMAGETYPE_MOVE, damageData, m_x, m_y, x, y, isEnemy, blockHit, this);
}
