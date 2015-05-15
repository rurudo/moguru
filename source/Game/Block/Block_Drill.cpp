#include "Block_Drill.h"
#include "../System/DataManager.h"
#include "../System/BlockManager.h"
#include "../Task/TaskFunction.h"

// ê∂ê¨ä÷êî
BlockBase* Drill_CreateBlock()
{
	return new Block_Drill();
}

Block_Drill::Block_Drill(void)
{
}

Block_Drill::~Block_Drill(void)
{
}

void Block_Drill::Update(void)
{
	if( m_Life <= 0 )
	{
		m_Exist = false;
		TaskSet_DrawExplod( m_x, m_y - BlockManager::GetInstance().GetDepth() );
		TaskSet_BlockBreakCalc( m_x, m_y, m_ID, m_EnemyID, m_EnemyLastHit );
		Release();
	}
}

void Block_Drill::AddDamage(int damage, int enemyID, bool isEnemy)
{
	m_EnemyID = enemyID;
	m_EnemyLastHit = isEnemy;
}