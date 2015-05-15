#include "Block_Rock.h"
#include "../System/DataManager.h"

#include "../System/BlockManager.h"
#include "../Task/TaskFunction.h"

// ê∂ê¨ä÷êî
BlockBase* Rock_CreateBlock()
{
	return new Block_Rock();
}

Block_Rock::Block_Rock(void)
{
}

Block_Rock::~Block_Rock(void)
{
}

void Block_Rock::Update(void)
{
	if( m_Life <= 0 )
	{
		m_Exist = false;
		TaskSet_BlockBreakCalc( m_x, m_y, m_ID, m_EnemyID, m_EnemyLastHit );
		TaskSet_DrawExplod( m_x, m_y - BlockManager::GetInstance().GetDepth() );
		Release();
	}
}