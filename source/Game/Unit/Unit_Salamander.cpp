#include "Unit_Salamander.h"
#include "../System/DataManager.h"
#include "../System/BlockManager.h"

#include "../Task/TaskFunction.h"
#include "../System/EquipmentFunction.h"

UnitBase* Salamander_CreateUnit(void)
{
	return new Unit_Salamander();
}

Unit_Salamander::Unit_Salamander(void)
{
}

Unit_Salamander::~Unit_Salamander(void)
{
}

void Unit_Salamander::Init(void)
{
	Unit_SmallMog::Init();
	m_Count = 0;
}

void Unit_Salamander::Update(void)
{
	if( m_Life <= 0)
	{
		m_Exist = false;
		TaskSet_DeadCalc( m_x, m_y, this );
		return;
	}
	if( m_Count % 10 == 0)
	{
		int damage = 25;
		// ‘Ï”Mƒ†ƒjƒbƒg‚ÅŒ¸­
		damage = EquipmentFunction_56( damage );
		TaskSet_AreaBlockDamage( m_x, m_y, 10, 1.3f );
		VECTOR damageData;
		TaskSet_AreaUnitBadStatusFriend( m_x, m_y,
			damage, 3.0f, UnitBase::DAMAGETYPE_NORMAL, damageData, m_MoveStatus == Enemy);
	}
	m_Count++;
	Unit_SmallMog::Update();
	
}
