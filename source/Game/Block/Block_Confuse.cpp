#include "Block_Confuse.h"
#include "../System/DataManager.h"
#include "../System/BlockManager.h"
#include "../Task/TaskFunction.h"

// ê∂ê¨ä÷êî
BlockBase* Confuse_CreateBlock()
{
	return new Block_Confuse();
}

Block_Confuse::Block_Confuse(void)
{
}

Block_Confuse::~Block_Confuse(void)
{
}

void Block_Confuse::Update(void)
{
	if( m_Life <= 0 )
	{
		m_Exist = false;
		TaskSet_DrawExplod( m_x, m_y - BlockManager::GetInstance().GetDepth() );
		TaskSet_BlockBreakCalc( m_x, m_y, m_ID, m_EnemyID, m_EnemyLastHit );
		VECTOR damageData;
		damageData.x = 300.0f;
		TaskSet_AreaUnitBadStatus( m_x, m_y, 0, 1.0f, UnitBase::DAMAGETYPE_CONFUSION, damageData);
		Release();
	}
}