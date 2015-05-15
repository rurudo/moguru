#include "Unit_Chop.h"
#include "../System/DataManager.h"
#include "../System/BlockManager.h"
#include "../System/UnitManager.h"
#include "../Task/TaskFunction.h"
#include "../System/EquipmentFunction.h"

UnitBase* Chop_CreateUnit(void)
{
	return new Unit_Chop();
}

Unit_Chop::Unit_Chop(void)
{
}

Unit_Chop::~Unit_Chop(void)
{
}

void Unit_Chop::Update(void)
{
	if( m_Life <= 0)
	{
		TaskSet_DeadCalc( m_x, m_y, this );
		m_Exist = false;
	}
	SetStatus();
	BadStatusUpdate();
	switch(m_MoveStatus)
	{
	case UnitBase::MovePoint:
		MovePoint();
		break;
	case UnitBase::Free:
		FreeMove();
		break;
	case UnitBase::Enemy:
		EnemyMove();
	default:
		break;
	}
	
}

void Unit_Chop::Shot(float x, float y, bool isEnemy, bool blockHit, bool enemyHit)
{
	if( !m_AttackEnable )
	{
		return;
	}
	VECTOR damageData;
	TaskSet_Shot( m_Power, UnitBase::DAMAGETYPE_NORMAL, damageData, m_x, m_y, x, y, isEnemy, blockHit, this, enemyHit);
}

void Unit_Chop::MovePoint(void)
{
	VECTOR position, target, facing;
	position.x = m_x;
	position.y = m_y;
	target.x = m_nextX;
	target.y = m_nextY;
	DXLibMath::FacingTarget( position, target, &m_Facing, 0.1f);
	facing.x = m_nextX - m_x;
	facing.y = m_nextY - m_y;
	DXLibMath::Normalize( &facing, facing );
	BlockManager &blockManager = BlockManager::GetInstance();
	BlockBase* block = blockManager.GetBlock( m_x + facing.x * m_Speed, m_y + facing.y * m_Speed );
	DataManager &data = DataManager::GetInstance();
	// 進行途中に邪魔な硬いブロックがあるなら破壊
	if( block != NULL && data.m_SystemData.block[block->m_ID - 1].moveType)
	{
		if( m_AtackCount > 1.0f)
		{
			Shot( block->m_x, block->m_y - blockManager.GetDepth(), false, false, false );
			m_AtackCount -= 1.0f;
		}
		m_AtackCount += m_AttackSpeed;
	}
	else
	{
		m_x += facing.x * m_Speed;
		m_y += facing.y * m_Speed;
	}
	// 目標地点に到達したら自由行動
	// または攻撃を受けたら自由行動
	if( DXLibMath::CircleOnPoint( position, target, 0.1f) || m_DamageSrc != NULL)
	{
		m_MoveStatus = UnitBase::Free;
	}
}

void Unit_Chop::FreeMove(void)
{
	VECTOR position;
	position.x = m_x;
	position.y = m_y;

	// ブロックを探す
	BlockManager &blockManager = BlockManager::GetInstance();
	BlockBase* block = blockManager.GetNearHardBlock( position, m_Rang );
	// 硬いブロックがあったら攻撃
	if( block != NULL )
	{
		if( m_AtackCount > 1.0f)
		{
			Shot( block->m_x, block->m_y - blockManager.GetDepth(), false, false, false );
			m_AtackCount -= 1.0f;
		}
		m_AtackCount += m_AttackSpeed;
	}
	// 近くに敵がいるなら
	UnitManager &unitManager = UnitManager::GetInstance();
	UnitBase* unit = unitManager.GetNearUnit( position, m_Rang, true, EquipmentFunction_16(), this );
	if( unit != NULL )
	{
		if( m_AtackCount > 1.0f)
		{
			Shot( unit->m_x, unit->m_y, false );
			m_AtackCount -= 1.0f;
		}
		m_AtackCount += m_AttackSpeed;
	}
}

void Unit_Chop::EnemyMove(void)
{
	// 移動
	VECTOR position;	// ユニットの座標
	VECTOR mogllPos;		// モグルの座標
	position.x = m_x;
	position.y = m_y;
	// モグルの座標が画面座標なので変換
	DataManager &data = DataManager::GetInstance();
	DXLibMath::ConvertScreenToBlock( data.m_MogllStatus.position.x, data.m_MogllStatus.position.y, &mogllPos.x, &mogllPos.y );
	// 向き変え
	DXLibMath::FacingTarget( position, mogllPos, &m_Facing, 0.1f);
	// ブロックを探す
	BlockManager &blockManager = BlockManager::GetInstance();
	BlockBase* block = blockManager.GetNearHardBlock( position, m_Rang );
	// 硬いブロックがあったら攻撃
	if( block != NULL )
	{
		if( m_AtackCount > 1.0f)
		{
			Shot( block->m_x, block->m_y - blockManager.GetDepth(), true, true, false );
			m_AtackCount -= 1.0f;
		}
		m_AtackCount += m_AttackSpeed;
	}
	// 索敵
	UnitManager &unitManager = UnitManager::GetInstance();
	UnitBase* unit = unitManager.GetNearUnit( position, m_Rang, false );
	// 近くに敵がいるなら
	if( unit != NULL )
	{
		if( m_AtackCount > 1.0f)
		{
			Shot( unit->m_x, unit->m_y, true );
			m_AtackCount -= 1.0f;
		}
		m_AtackCount += m_AttackSpeed;
	}
	// モグルが近くにいるなら
	else if( DXLibMath::CircleOnPoint( position, mogllPos, m_Rang ) )
	{
		if( m_AtackCount > 1.0f)
		{
			Shot( mogllPos.x, mogllPos.y, true );
			m_AtackCount -= 1.0f;
		}
		m_AtackCount += m_AttackSpeed;
	}
	// 周りに何も無いなら移動
	else
	{
		VECTOR facing;
		DXLibMath::FacingTarget( position, mogllPos, &m_Facing, 0.1f);
		facing.x = mogllPos.x - m_x;
		facing.y = mogllPos.y - m_y;
		DXLibMath::Normalize( &facing, facing );
		// 通過不可ブロックがあるなら攻撃
		BlockManager &blockManager = BlockManager::GetInstance();
		BlockBase* block = blockManager.GetBlock( m_x + facing.x * m_Speed, m_y + facing.y * m_Speed );
		DataManager &data = DataManager::GetInstance();
		if( block != NULL)
		{
			if( m_AtackCount > 1.0f)
			{
				Shot( block->m_x, block->m_y - blockManager.GetDepth(), true, true, false);
				m_AtackCount -= 1.0f;
			}
			m_AtackCount += m_AttackSpeed;
		}
		else
		{
			m_x += facing.x * m_Speed;
			m_y += facing.y * m_Speed;
		}
	}
}