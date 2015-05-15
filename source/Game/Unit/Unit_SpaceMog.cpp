#include "Unit_SpaceMog.h"
#include "../System/DataManager.h"
#include "../Task/TaskFunction.h"

UnitBase* SpaceMog_CreateUnit(void)
{
	return new Unit_SpaceMog();
}

Unit_SpaceMog::Unit_SpaceMog(void)
{
}

Unit_SpaceMog::~Unit_SpaceMog(void)
{
}

void Unit_SpaceMog::Shot(float x, float y, bool isEnemy, bool blockHit)
{
	if( !m_AttackEnable )
	{
		return;
	}
	VECTOR damageData;
	TaskSet_Shot( m_Power, UnitBase::DAMAGETYPE_NORMAL, damageData, m_x, m_y, x, y, isEnemy, blockHit, this);
}

void Unit_SpaceMog::Init(void)
{
	Unit_SmallMog::Init();
	m_DefenceCount = 10;
}

void Unit_SpaceMog::AddDamage( int damage, int type, const VECTOR &value, UnitBase *enemy)
{
	// ƒoƒŠƒA‚ª‘¶İ‚µ‚Ä‚¢‚éŠÔ‚ÍUŒ‚‚ğ–³Œø‰»‚·‚é
	if( m_DefenceCount )
	{
		m_DefenceCount--;
	}
	else
	{
		Unit_SmallMog::AddDamage( damage, type, value, enemy );
	}
}
