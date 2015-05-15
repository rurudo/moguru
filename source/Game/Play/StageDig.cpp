#include "StageDig.h"
#include "../System/BlockManager.h"
#include "../System/DataManager.h"
#include "../System/UnitManager.h"
#include "../System/GameInput.h"
#include "../System/EquipmentFunction.h"

StageDig::StageDig(void)
{
	m_DigPoint = 0;
	m_SEWaterCnt = 0;
}


StageDig::~StageDig(void)
{
}

void StageDig::Update(void)
{
	// モグルのドリルで敵にダメージ
	UnitManager &unitManager = UnitManager::GetInstance();
	VECTOR position;
	position.x = 7.5f;
	position.y = 5.0f;
	UnitBase* unit = unitManager.GetNearUnit( position, 1.0f, true );
	if( unit != NULL )
	{
		VECTOR damageType;
		unit->AddDamage(1000, UnitBase::DAMAGETYPE_NORMAL, damageType, NULL );
	}
	// ブロック削り判定
	BlockManager &blockManager = BlockManager::GetInstance();
	BlockBase* base = blockManager.GetBlock( position.x, position.y );
	// 指定地点が空なら
	if( base == NULL || base->m_ID == BLOCK_WATER || base->m_ID == BLOCK_FIRE)
	{
		float speed = 0.06f;
		if( base )
		{
			if(base->m_ID == BLOCK_WATER )
			{
				speed = 0.03f;
			}
			else if( base->m_ID == BLOCK_FIRE && GameInput::GetInstance().GetFrame() % 10 == 0)
			{
				DataManager::GetInstance().m_MogllStatus.life -= EquipmentFunction_05(1);
			}
		}
		float fallValue = EquipmentFunction_40( speed );
		blockManager.AddDepth( fallValue );
		DataManager &data = DataManager::GetInstance();
		// 記録更新したら代入
		int depth = static_cast<int>(blockManager.GetDepth() + data.m_MogllStatus.position.y * 600.0f / 40.0f);
		if( data.m_SaveData.stageDepth[ data.m_SceneInt["StageNo"] ] < depth )
		{
			data.m_SaveData.stageDepth[ data.m_SceneInt["StageNo"] ] = depth;
		}
		//UnitManager::GetInstance().MoveUp( fallValue );
	}
	else if( EquipmentFunction_35( GameInput::GetInstance().GetFrame() ) )
	{
		DataManager &data = DataManager::GetInstance();
		// ブロックの削りダメージ
		int damage = 1;
		int mogllDamage = EquipmentFunction_11( data.m_SystemData.block[ base->m_ID - 1 ].damage );
		m_DigPoint += mogllDamage;
		if( m_DigPoint >= 100 )
		{
			data.m_MogllStatus.life -= m_DigPoint / 100;
			m_DigPoint = m_DigPoint % 100;
		}
		base->m_Life -= damage;
	}
	//--------------------------------------------------------------	笹井
	//今いるブロックをチェック
	base = blockManager.GetBlock( position.x, position.y );
	if(base)
	{
		if(base->m_ID == BLOCK_WATER )
		{
			m_SEWaterCnt--;
			if( m_SEWaterCnt <= 0 &&
				CheckSoundMem(DataManager::GetInstance().Get( DataManager::SoundSE57 )) == 0)
			{
				PlaySoundMem( DataManager::GetInstance().Get( DataManager::SoundSE57 ), DX_PLAYTYPE_BACK);
				m_SEWaterCnt = 90;
			}
		}
		else if( base->m_ID == BLOCK_FIRE)
		{
			if(CheckSoundMem(DataManager::GetInstance().Get( DataManager::SoundSE56 )) == 0)
				PlaySoundMem( DataManager::GetInstance().Get( DataManager::SoundSE56 ), DX_PLAYTYPE_BACK);
		}
		if(base->m_ID != BLOCK_WATER )
			m_SEWaterCnt = 0;
	}
}

void StageDig::OPUpdate(float y)
{
	BlockManager &blockManager = BlockManager::GetInstance();
	BlockBase* base = blockManager.GetBlock( 7.5f, y );
	// 指定地点が空なら
	if( base == NULL)
	{
		float fallValue = EquipmentFunction_40( 0.068f );
		blockManager.AddDepth( fallValue );
		//UnitManager::GetInstance().MoveUp( fallValue );
	}
	else if( EquipmentFunction_35( GameInput::GetInstance().GetFrame() ) )
	{
		DataManager &data = DataManager::GetInstance();
		// 通行不可ブロックを削るとダメージ
		int damage = 99999;
		base->m_Life -= damage;
	}
}