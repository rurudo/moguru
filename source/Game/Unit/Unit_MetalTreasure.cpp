#include "Unit_MetalTreasure.h"
#include "../System/DataManager.h"
#include "../Task/TaskFunction.h"

UnitBase* MetalTreasure_CreateUnit(void)
{
	return new Unit_MetalTreasure();
}

Unit_MetalTreasure::Unit_MetalTreasure(void)
{
}

Unit_MetalTreasure::~Unit_MetalTreasure(void)
{
}

void Unit_MetalTreasure::Shot(float x, float y, bool isEnemy, bool blockHit, bool enemyHit)
{
	if( !m_AttackEnable )
	{
		return;
	}
	VECTOR damageData;
	TaskSet_Shot( m_Power, UnitBase::DAMAGETYPE_NORMAL, damageData, m_x, m_y, x, y, isEnemy, blockHit, this, enemyHit);
}

void Unit_MetalTreasure::AddDamage( int damage, int type, const VECTOR &value, UnitBase *enemy)
{
	// ダメージをカット
	int d = static_cast<int>(damage * 0.7f);
	if( d < 1)
	{
		d = 1;
	}
	Unit_Treasure::AddDamage( d, type, value, enemy );
}