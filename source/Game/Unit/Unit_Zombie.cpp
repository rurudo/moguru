#include "Unit_Zombie.h"
#include "../System/DataManager.h"
#include "../System/BlockManager.h"

#include "../Task/TaskFunction.h"

UnitBase* Zombie_CreateUnit(void)
{
	return new Unit_Zombie();
}

Unit_Zombie::Unit_Zombie(void)
{
}

Unit_Zombie::~Unit_Zombie(void)
{
}

void Unit_Zombie::DeadCalc(void)
{
	if( m_Life <= 0)
	{
		// ”R‚¦‚½‚çŽ€‚Ê
		if( m_BadStatus[ UnitBase::DAMAGETYPE_FIRE ].x >= 1.0f)
		{
			TaskSet_DeadCalc( m_x, m_y, this );
			m_Exist = false;
			return;
		}
		m_Count++;
		m_Life = 1;
	}
	if( m_Count )
	{
		m_Count++;
		if( m_Count > 60 )
		{
			m_Life = DataManager::GetInstance().m_SystemData.unit[m_ID - 1].hp;
			m_Count = 0;
		}
	}
}

void Unit_Zombie::Init(void)
{
	Unit_SmallMog::Init();
	m_Count = 0;
}

void Unit_Zombie::Update(void)
{
	DeadCalc();
	SetStatus();
	BadStatusUpdate();
	if( m_Count )
	{
		return;
	}
	switch(m_MoveStatus)
	{
	case UnitBase::MovePoint:
		MovePoint();
		break;
	case UnitBase::Free:
		FreeMove();
		break;
	case UnitBase::Enemy:
		EnemyMove();
	default:
		break;
	}
	
}
