#include "Unit_Dig.h"
#include "../System/DataManager.h"
#include "../System/BlockManager.h"
#include "../System/UnitManager.h"
#include "../Task/TaskFunction.h"
#include "../System/EquipmentFunction.h"

UnitBase* Dig_CreateUnit(void)
{
	return new Unit_Dig();
}

Unit_Dig::Unit_Dig(void)
{
}

Unit_Dig::~Unit_Dig(void)
{
}

void Unit_Dig::Update(void)
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

void Unit_Dig::Shot(float x, float y, bool isEnemy, bool blockHit, bool enemyHit)
{
	if( !m_AttackEnable )
	{
		return;
	}
	VECTOR damageData;
	TaskSet_Shot( m_Power, UnitBase::DAMAGETYPE_NORMAL, damageData, m_x, m_y, x, y, isEnemy, blockHit, this, enemyHit);
}

void Unit_Dig::MovePoint(void)
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
	// 進行途中に邪魔なブロックがあるなら破壊
	if( block != NULL)
	{
		if( m_AtackCount > 1.0f)
		{
			Shot( block->m_x, block->m_y - blockManager.GetDepth(), false, true, false );
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
	// または攻撃を受けても目標地点に向かう
	if( DXLibMath::CircleOnPoint( position, target, 0.1f))
	{
		m_MoveStatus = UnitBase::Free;
	}
}

void Unit_Dig::FreeMove(void)
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
			Shot( block->m_x, block->m_y - blockManager.GetDepth(), false, true, false );
			m_AtackCount -= 1.0f;
		}
		m_AtackCount += m_AttackSpeed;
	}
	// 敵は無視
}

void Unit_Dig::EnemyMove(void)
{
	// 移動
	VECTOR position;	// ユニットの座標
	VECTOR blockPos;	// ブロックの座標
	position.x = m_x;
	position.y = m_y;

	BlockManager &blockManager = BlockManager::GetInstance();
	// 索ブロック範囲
	BlockBase* block = blockManager.GetNearHardBlock( position, m_Rang * 3.0f );
	if( block != NULL )
	{
		blockPos.x = block->m_x;
		blockPos.y = block->m_y - blockManager.GetDepth();
	}
	else
	{
		return;
	}
	// 向き変え
	DXLibMath::FacingTarget( position, blockPos, &m_Facing, 0.1f);
	// ブロックを探す
	block = blockManager.GetNearHardBlock( position, m_Rang );
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

	// 周りに何も無いなら移動
	VECTOR facing;
	DXLibMath::FacingTarget( position, blockPos, &m_Facing, 0.1f);
	facing.x = blockPos.x - m_x;
	facing.y = blockPos.y - m_y;
	DXLibMath::Normalize( &facing, facing );
	// 通過不可ブロックがあるなら攻撃
	block = blockManager.GetBlock( m_x + facing.x * m_Speed, m_y + facing.y * m_Speed );
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