#include "Block_Soil.h"
#include "../System/DataManager.h"
#include "../System/TaskManager.h"
#include "../Task/TaskFunction.h"

// ê∂ê¨ä÷êî
BlockBase* Soil_CreateBlock()
{
	return new Block_Soil();
}

Block_Soil::Block_Soil(void)
{
}

Block_Soil::~Block_Soil(void)
{
}

void Block_Soil::Update(void)
{
	if( m_Life <= 0 )
	{
		TaskSet_BlockBreakCalc( m_x, m_y, m_ID, m_EnemyID, m_EnemyLastHit );
		Release();
		m_Exist = false;
	}
}