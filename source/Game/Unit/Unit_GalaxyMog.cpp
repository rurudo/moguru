#include "Unit_GalaxyMog.h"
#include "../System/DataManager.h"
#include "../Task/TaskFunction.h"

UnitBase* GalaxyMog_CreateUnit(void)
{
	return new Unit_GalaxyMog();
}

Unit_GalaxyMog::Unit_GalaxyMog(void)
{
}

Unit_GalaxyMog::~Unit_GalaxyMog(void)
{
}

void Unit_GalaxyMog::Shot(float x, float y, bool isEnemy, bool blockHit)
{
	if( !m_AttackEnable )
	{
		return;
	}
	VECTOR damageData;
	TaskSet_Shot( m_Power, UnitBase::DAMAGETYPE_NORMAL, damageData, m_x, m_y, x, y, isEnemy, blockHit, this);
}

void Unit_GalaxyMog::Init(void)
{
	Unit_SmallMog::Init();
	m_DefenceCount = 10;
}

void Unit_GalaxyMog::Update(void)
{
	if( m_Life <= 0)
	{
		m_Exist = false;
		TaskSet_DeadCalc( m_x, m_y, this );
		return;
	}
	if( m_y < 3.0f )
	{
		m_y = 8.0f + 0.01f * (GetRand(400));
		m_x = 1.0f + 0.01f * (GetRand(1300));
	}
	Unit_SmallMog::Update();
	
}


void Unit_GalaxyMog::AddDamage( int damage, int type, const VECTOR &value, UnitBase *enemy)
{
	// ƒoƒŠƒA‚ª‘¶Ý‚µ‚Ä‚¢‚éŠÔ‚ÍUŒ‚‚ð–³Œø‰»‚·‚é
	/*if( m_DefenceCount )
	{
		if( damage > 30)
		{
			m_DefenceCount--;
		}
	}
	else
	{
		Unit_SmallMog::AddDamage( damage, type, value, enemy );
	}*/
	Unit_SmallMog::AddDamage( damage, type, value, enemy );
}
