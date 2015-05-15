#include "Block_Fire.h"
#include "../System/DataManager.h"
#include "../System/BlockManager.h"
#include "../Task/TaskFunction.h"

// ê∂ê¨ä÷êî
BlockBase* Fire_CreateBlock()
{
	return new Block_Fire();
}

Block_Fire::Block_Fire(void)
{
}

Block_Fire::~Block_Fire(void)
{
}

void Block_Fire::Init(void)
{
	BlockBase::Init();
	m_FrameCount = 0;
}

void Block_Fire::Update(void)
{
	if( m_Life <= 0 )
	{
		m_Exist = false;
		TaskSet_DrawExplod( m_x, m_y - BlockManager::GetInstance().GetDepth() );
		TaskSet_BlockBreakCalc( m_x, m_y, m_ID, m_EnemyID, m_EnemyLastHit );
		Release();
	}
}