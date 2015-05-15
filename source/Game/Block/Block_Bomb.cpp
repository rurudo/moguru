#include "Block_Bomb.h"
#include "../System/DataManager.h"
#include "../System/BlockManager.h"
#include "../Task/TaskFunction.h"

// ê∂ê¨ä÷êî
BlockBase* Bomb_CreateBlock()
{
	return new Block_Bomb();
}

Block_Bomb::Block_Bomb(void)
{
}

Block_Bomb::~Block_Bomb(void)
{
}

void Block_Bomb::Update(void)
{
	if( m_Life <= 0 )
	{
		m_Exist = false;
		float y = m_y - BlockManager::GetInstance().GetDepth();
		TaskSet_DrawExplod( m_x, y );
		TaskSet_BlockBreakCalc( m_x, m_y, m_ID, m_EnemyID, m_EnemyLastHit );
		TaskSet_AreaBlockDamage( m_x, y, 500, 1.3f );
		TaskSet_AreaUnitDamage( m_x, y, 500, 1.3f );
		Release();
	}
}