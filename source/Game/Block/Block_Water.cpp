#include "Block_Water.h"
#include "../System/DataManager.h"
#include "../System/BlockManager.h"
#include "../Task/TaskFunction.h"

// ê∂ê¨ä÷êî
BlockBase* Water_CreateBlock()
{
	return new Block_Water();
}

Block_Water::Block_Water(void)
{
}

Block_Water::~Block_Water(void)
{
}

void Block_Water::Update(void)
{
	if( m_Life <= 0 )
	{
		m_Exist = false;
		TaskSet_BlockBreakCalc( m_x, m_y, m_ID, m_EnemyID, m_EnemyLastHit );
		Release();
	}
}