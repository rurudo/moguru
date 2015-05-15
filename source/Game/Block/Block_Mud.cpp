#include "Block_Mud.h"
#include "../System/DataManager.h"
#include "../System/BlockManager.h"
#include "../Task/TaskFunction.h"

// ê∂ê¨ä÷êî
BlockBase* Mud_CreateBlock()
{
	return new Block_Mud();
}

Block_Mud::Block_Mud(void)
{
}

Block_Mud::~Block_Mud(void)
{
}

void Block_Mud::Update(void)
{
	if( m_Life <= 0 )
	{
		m_Exist = false;
		TaskSet_BlockBreakCalc( m_x, m_y, m_ID, m_EnemyID, m_EnemyLastHit );
		Release();
	}
}