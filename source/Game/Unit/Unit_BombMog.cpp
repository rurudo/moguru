#include "Unit_BombMog.h"
#include "../System/DataManager.h"
#include "../System/BlockManager.h"

#include "../Task/TaskFunction.h"

UnitBase* BombMog_CreateUnit(void)
{
	return new Unit_BombMog();
}

Unit_BombMog::Unit_BombMog(void)
{
}

Unit_BombMog::~Unit_BombMog(void)
{
}

void Unit_BombMog::DeadCalc(void)
{
	if( m_Life <= 0)
	{
		m_Exist = false;
		TaskSet_DrawExplod( m_x, m_y );
		TaskSet_AreaUnitDamage( m_x, m_y, 500, 2.0f );
		TaskSet_AreaBlockDamage( m_x, m_y, 500, 1.0f );
	}
}

void Unit_BombMog::Update(void)
{
	DeadCalc();
	SetStatus();
	BadStatusUpdate();
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
