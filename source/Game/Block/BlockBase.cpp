#include "BlockBase.h"
#include "../System/UnitManager.h"
#include "../System/BlockManager.h"
#include "../System/DataManager.h"
#include "../System/EquipmentFunction.h"

BlockBase::BlockBase(void)
{
	m_x = 0.0f;
	m_y = 0.0f;
	m_TreasureID = -1;
	m_ID = 1;
	m_EnemyID = 0;
	m_InEnemyID = -1;
	m_EnemyLastHit = true;
}


BlockBase::~BlockBase(void)
{
}

void BlockBase::SetPosition(float x, float y)
{
	m_x = x;
	m_y = y;
}

void BlockBase::Update(void)
{
}

void BlockBase::Release(void)
{
	if( m_TreasureID != -1)
	{
		VECTOR position;
		position.x = m_x;
		position.y = m_y - BlockManager::GetInstance().GetDepth() - 0.3f;
		UnitManager::GetInstance().AddTreasureBox( position, m_TreasureID );
	}
}

void BlockBase::AddDamage(int damage, int enemyID, bool isEnemy)
{
	m_Life -= damage;
	m_EnemyID = enemyID;
	m_EnemyLastHit = isEnemy;
}

void BlockBase::Init( void )
{
	DataManager& data = DataManager::GetInstance();
	m_Life = data.m_SystemData.block[ m_ID - 1 ].hp;
}

int BlockBase::GetHandle( void )
{
	DataManager& data = DataManager::GetInstance();
	return data.GetGraphicGroupData(DataManager::GG_MAPTIP_SAND + m_ID - 1);
}

int BlockBase::GetID(void){
	return m_ID-1;
}

DXLibMath::Vector2 BlockBase::GetPosition(void){
	DXLibMath::Vector2 l_returnPos;
	l_returnPos.x = static_cast<int>(m_x * 40) - 20;
	l_returnPos.y = static_cast<int>((m_y - BlockManager::GetInstance().GetDepth()) * 40 - 20);

	return l_returnPos;
}

int BlockBase::GetHP(void){
	return m_Life;
}

void BlockBase::DrawUnder()
{
}

void BlockBase::DrawUpper()
{
	DataManager& data = DataManager::GetInstance();
	int l_CrackStatus = 0;
	int x = static_cast<int>(m_x * 40) - 20;
	int y = static_cast<int>((m_y - BlockManager::GetInstance().GetDepth()) * 40 - 20);

	if( EquipmentFunction_28() && m_TreasureID != -1 )
	{
		if( m_TreasureID > 60 )
		{
			DrawGraph( x, y, data.Get( DataManager::Play_MapBox ), TRUE );
		}
		else
		{
			DrawGraph( x, y, data.Get( DataManager::Play_TreasureBox ), TRUE );
		}
	}

	if( m_Life != data.m_SystemData.block[ m_ID - 1].hp )
	{
		if( m_Life < data.m_SystemData.block[ m_ID-1 ].hp*0.3f )
		{
			l_CrackStatus = 3;
		}
		else if( m_Life < data.m_SystemData.block[ m_ID-1 ].hp*0.7f )
		{
			l_CrackStatus = 2;
		}
		else
		{
			l_CrackStatus = 1;
		}
	}
	
	if(l_CrackStatus > 0)
		DrawGraph( x, y, data.GetGraphicGroupData(DataManager::GG_BLOCK_CRACK1 + l_CrackStatus - 1), TRUE);
}

bool BlockBase::IsExist(void)
{
	return m_Exist;
}

void BlockBase::SetExist(bool flag)
{
	m_Exist = flag;
}

void BlockBase::SetTreasureID( int id )
{
	m_TreasureID = id;
}