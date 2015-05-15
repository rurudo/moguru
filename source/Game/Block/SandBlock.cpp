#include "SandBlock.h"
#include "../Task/TaskFunction.h"

// ê∂ê¨ä÷êî
BlockBase* SandBlock_CreateBlock()
{
	return new SandBlock();
}

SandBlock::SandBlock(void)
{
}

SandBlock::~SandBlock(void)
{
}

void SandBlock::Update(void)
{
	if( m_Life <= 0 )
	{
		m_Exist = false;
		TaskSet_BlockBreakCalc( m_x, m_y, m_ID, m_EnemyID, m_EnemyLastHit );
		Release();
	}
}