#include "Block_HardSoil.h"
#include "../System/DataManager.h"
#include "../System/TaskManager.h"
#include "../Task/TaskFunction.h"

// ê∂ê¨ä÷êî
BlockBase* HardSoil_CreateBlock()
{
	return new Block_HardSoil();
}

Block_HardSoil::Block_HardSoil(void)
{
}

Block_HardSoil::~Block_HardSoil(void)
{	
}

void Block_HardSoil::Update(void)
{
	if( m_Life <= 0 )
	{
		TaskSet_BlockBreakCalc( m_x, m_y, m_ID, m_EnemyID, m_EnemyLastHit );
		m_Exist = false;
		Release();
	}
}