#include "Unit_ClockRabbit.h"
#include "../System/DataManager.h"
#include "../System/BlockManager.h"

#include "../Task/TaskFunction.h"

UnitBase* ClockRabbit_CreateUnit(void)
{
	return new Unit_ClockRabbit();
}

Unit_ClockRabbit::Unit_ClockRabbit(void)
{
}

Unit_ClockRabbit::~Unit_ClockRabbit(void)
{
}

void Unit_ClockRabbit::Init(void)
{
	UnitBase::Init();
	m_Count = 0;
}

void Unit_ClockRabbit::Update(void)
{
	if( m_Life <= 0)
	{
		m_Exist = false;
		TaskSet_DeadCalc( m_x, m_y, this );
		return;
	}
	if( m_Count % 10 == 0)
	{
		TaskSet_AllTargetSet( m_x, m_y, this );
	}
	m_Count++;
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

void Unit_ClockRabbit::Shot(float x, float y, bool isEnemy, bool blockHit)
{
	if( !m_AttackEnable )
	{
		return;
	}
	VECTOR damageData;
	TaskSet_Shot( m_Power, UnitBase::DAMAGETYPE_NORMAL, damageData, m_x, m_y, x, y, isEnemy, blockHit, this);
}

void Unit_ClockRabbit::MovePoint(void)
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
	if( block != NULL && data.m_SystemData.block[block->m_ID - 1].moveType)
	{
		if( m_AtackCount > 1.0f)
		{
			Shot( block->m_x, block->m_y - blockManager.GetDepth(), false, true );
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
	if( DXLibMath::CircleOnPoint( position, target, 0.1f) )
	{
		m_MoveStatus = UnitBase::Free;
	}
}

void Unit_ClockRabbit::FreeMove(void)
{
	VECTOR position;
	position.x = m_x;
	position.y = m_y;

	// 近くに敵がいるなら
	UnitManager &unitManager = UnitManager::GetInstance();
	UnitBase* unit = unitManager.GetNearUnit( position, m_Rang, true, true, this );
	if( unit != NULL )
	{
		VECTOR vec;
		vec.x = m_x - unit->m_x;
		vec.y = m_y - unit->m_y;
		DXLibMath::Normalize( &vec, vec );
		m_nextX = m_x + vec.x;
		m_nextY = m_y + vec.y;
		m_MoveStatus = UnitBase::MovePoint;
	}
}

void Unit_ClockRabbit::EnemyMove(void)
{
	// 移動
	VECTOR position, target;
	position.x = m_x;
	position.y = m_y;
	target.x = m_nextX;
	target.y = m_nextY;
	// 向き変え
	DXLibMath::FacingTarget( position, target, &m_Facing, 0.1f);
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
	else if( DXLibMath::CircleOnPoint( position, target, m_Rang ) )
	{
		if( m_AtackCount > 1.0f)
		{
			Shot( target.x, target.y, true );
			m_AtackCount -= 1.0f;
		}
		m_AtackCount += m_AttackSpeed;
	}
	// 周りに何も無いなら移動
	else
	{
		VECTOR facing;
		DXLibMath::FacingTarget( position, target, &m_Facing, 0.1f);
		facing.x = target.x - m_x;
		facing.y = target.y - m_y;
		DXLibMath::Normalize( &facing, facing );
		// 通過不可ブロックがあるなら攻撃
		BlockManager &blockManager = BlockManager::GetInstance();
		BlockBase* block = blockManager.GetBlock( m_x + facing.x * m_Speed, m_y + facing.y * m_Speed );
		DataManager &data = DataManager::GetInstance();
		if( block != NULL && data.m_SystemData.block[block->m_ID - 1].moveType)
		{
			if( m_AtackCount > 1.0f)
			{
				Shot( block->m_x, block->m_y - blockManager.GetDepth(), true, true);
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