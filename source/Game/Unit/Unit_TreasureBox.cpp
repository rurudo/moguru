#include "Unit_TreasureBox.h"
#include "../System/DataManager.h"
#include "../Unit/CreateUnit.h"
#include "../System/EquipmentFunction.h"

UnitBase* TreasureBox_CreateUnit(void)
{
	return new Unit_TreasureBox();
}

Unit_TreasureBox::Unit_TreasureBox(void)
{
}

Unit_TreasureBox::~Unit_TreasureBox(void)
{
}

void Unit_TreasureBox::Init(void)
{
	DataManager &data = DataManager::GetInstance();
	int treasureID = 0;
	for(int i = 0; i < 50; i++)
	{
		if( data.m_SystemData.treasure[ i ].id == m_TreasureID )
		{
			treasureID = i;
			break;
		}
	}
	m_MaxLife = data.m_SystemData.treasure[ treasureID ].life;
	m_Life = data.m_SystemData.treasure[ treasureID ].life;
	m_AttackSpeed = 0.05f;
	m_Speed = 0.1f;
	m_Rang = 2.0f;
	m_Power = 5;
	m_DamageSrc = NULL;
	for(int i = 0; i < DAMAGETYPE_MAX; i++)
	{
		m_BadStatus[i].x = 0.0f;
		m_BadStatus[i].y = 0.0f;
		m_BadStatus[i].z = 0.0f;
	}
	m_FrameCount = 0.0f;
}

void Unit_TreasureBox::Draw(void)
{
	DataManager &data = DataManager::GetInstance();
	float x, y;
	DXLibMath::ConvertBlockToScreen( m_x, m_y, &x, &y);
	int handle;
	if( m_TreasureID > 60 )
	{
		handle = data.Get( DataManager::Play_MapBox );
	}
	else
	{
		handle = data.Get( DataManager::Play_TreasureBox );
	}
	DXLibMath::DrawRotaGraphResize(x, y, 1.0f + 0.5f * sin( m_FrameCount / 30.0f * 3.141592f),
		0.0f, handle, TRUE);
}

void Unit_TreasureBox::Update(void)
{
	DataManager &data = DataManager::GetInstance();
	if( m_Life <= 0)
	{
		// 宝箱を破壊した時、ゲットフラグを立てる
		m_Exist = false;
		data.m_MogllStatus.treasureStatus = m_TreasureID;
		return;
	}
	m_FrameCount += 1.0f;
}

void Unit_TreasureBox::SetTreasureID(int id)
{
	m_TreasureID = id;
}

void Unit_TreasureBox::AddDamage( int damage, int type, const VECTOR &value, UnitBase *enemy)
{
	// トレジャー系のダメージを増加
	int d = damage;
	if( enemy &&
		(enemy->m_ID == UNIT_Treasure		||
		enemy->m_ID == UNIT_GoldenMog		||
		enemy->m_ID == UNIT_Dig				||
		enemy->m_ID == UNIT_MetalTreasure	||
		enemy->m_ID == UNIT_King			||
		EquipmentFunction_10()))
	{
		d *= 20;
	}
	UnitBase::AddDamage( d, type, value, enemy);
}