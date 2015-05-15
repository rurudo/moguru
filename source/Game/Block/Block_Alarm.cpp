#include "Block_Alarm.h"
#include "../System/DataManager.h"

#include "../System/EquipmentFunction.h"
#include "../Task/TaskFunction.h"

// ê∂ê¨ä÷êî
BlockBase* Alarm_CreateBlock()
{
	return new Block_Alarm();
}

Block_Alarm::Block_Alarm(void)
{
}

Block_Alarm::~Block_Alarm(void)
{
}

void Block_Alarm::Update(void)
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

int Block_Alarm::GetHandle( void )
{
	DataManager& data = DataManager::GetInstance();
	if( EquipmentFunction_28() )
	{
		return data.Get( DataManager::GG_MAPTIP_BOMB );
	}
	else
	{
		return data.GetGraphicGroupData(DataManager::GG_MAPTIP_OLDBONE);
	}
}
