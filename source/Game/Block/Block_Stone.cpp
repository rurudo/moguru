#include "Block_Stone.h"
#include "../System/DataManager.h"
#include "../System/BlockManager.h"
#include "../Task/TaskFunction.h"

// ê∂ê¨ä÷êî
BlockBase* Stone_CreateBlock()
{
	return new Block_Stone();
}

Block_Stone::Block_Stone(void)
{
}

Block_Stone::~Block_Stone(void)
{
}

void Block_Stone::Update(void)
{
	if( m_Life <= 0 )
	{
		m_Exist = false;
		TaskSet_DrawExplod( m_x, m_y - BlockManager::GetInstance().GetDepth() );
		TaskSet_BlockBreakCalc( m_x, m_y, m_ID, m_EnemyID, m_EnemyLastHit );
		Release();
	}
}