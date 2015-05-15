#include "Block_DeepMud.h"
#include "../System/DataManager.h"
#include "../System/BlockManager.h"
#include "../Task/TaskFunction.h"

// ê∂ê¨ä÷êî
BlockBase* DeepMud_CreateBlock()
{
	return new Block_DeepMud();
}

Block_DeepMud::Block_DeepMud(void)
{
}

Block_DeepMud::~Block_DeepMud(void)
{
}

void Block_DeepMud::Update(void)
{
	if( m_Life <= 0 )
	{
		m_Exist = false;
		TaskSet_BlockBreakCalc( m_x, m_y, m_ID, m_EnemyID, m_EnemyLastHit );
		Release();
	}
}