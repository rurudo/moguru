#include "Block_EnemyIce.h"
#include "../System/DataManager.h"

#include "../System/EquipmentFunction.h"
#include "../Task/TaskFunction.h"

// ê∂ê¨ä÷êî
BlockBase* EnemyIce_CreateBlock()
{
	return new Block_EnemyIce();
}

Block_EnemyIce::Block_EnemyIce(void)
{
}

Block_EnemyIce::~Block_EnemyIce(void)
{
}

void Block_EnemyIce::Update(void)
{
	if( m_Life <= 0 )
	{
		m_Exist = false;
		TaskSet_BlockBreakCalc( m_x, m_y, m_ID, m_EnemyID, m_EnemyLastHit );
		TaskSet_DrawExplod( m_x, m_y - BlockManager::GetInstance().GetDepth() );
		if( m_InEnemyID == -1 )
		{
			TaskSet_CreateEnemy( m_x, m_y - BlockManager::GetInstance().GetDepth(), UNIT_BombBox );
		}
		else
		{
			TaskSet_CreateEnemy( m_x, m_y - BlockManager::GetInstance().GetDepth(), m_InEnemyID );
		}
		Release();
	}
}

int Block_EnemyIce::GetHandle( void )
{
	DataManager& data = DataManager::GetInstance();
	return data.GetGraphicGroupData(DataManager::GG_MAPTIP_SAND + m_ID - 1);
}

void Block_EnemyIce::DrawUnder()
{
	DataManager& data = DataManager::GetInstance();
	int x = static_cast<int>(m_x * 40) - 20;
	int y = static_cast<int>((m_y - BlockManager::GetInstance().GetDepth()) * 40 - 20);
	if( m_InEnemyID == -1 )
	{
		DrawGraph(x, y,
			data.Get( DataManager::GG_UNIT_BombBox ), TRUE);
	}
	else
	{
		DrawGraph(x, y,
			data.GetGraphicGroupData( DataManager::GG_UNIT_Treasure + m_InEnemyID - 1 ), TRUE);
	}
}