#include "Unit_SmallMog.h"
#include "../System/DataManager.h"
#include "../System/BlockManager.h"
#include "../System/UnitManager.h"
#include "../Task/TaskFunction.h"
#include "../System/EquipmentFunction.h"

UnitBase* SmallMog_CreateUnit(void)
{
	return new Unit_SmallMog();
}

Unit_SmallMog::Unit_SmallMog(void)
{
}

Unit_SmallMog::~Unit_SmallMog(void)
{
}

void Unit_SmallMog::Update(void)
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

void Unit_SmallMog::Shot(float x, float y, bool isEnemy, bool blockHit)
{
	if( !m_AttackEnable )
	{
		return;
	}
	VECTOR damageData;
	TaskSet_Shot( m_Power, UnitBase::DAMAGETYPE_NORMAL, damageData, m_x, m_y, x, y, isEnemy, blockHit, this);
}

void Unit_SmallMog::MovePoint(void)
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
	// �i�s�r���Ɏז��ȃu���b�N������Ȃ�j��
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
	// �ڕW�n�_�ɓ��B�����玩�R�s��
	// �܂��͍U�����󂯂��玩�R�s��
	if( DXLibMath::CircleOnPoint( position, target, 0.1f) || m_DamageSrc != NULL)
	{
		m_MoveStatus = UnitBase::Free;
	}
}

void Unit_SmallMog::FreeMove(void)
{
	VECTOR position;
	position.x = m_x;
	position.y = m_y;

	// �߂��ɓG������Ȃ�
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

void Unit_SmallMog::EnemyMove(void)
{
	// �ړ�
	VECTOR position, target;
	position.x = m_x;
	position.y = m_y;
	target.x = m_nextX;
	target.y = m_nextY;
	// �����ς�
	DXLibMath::FacingTarget( position, target, &m_Facing, 0.1f);
	// ���G
	UnitManager &unitManager = UnitManager::GetInstance();
	UnitBase* unit = unitManager.GetNearUnit( position, m_Rang, false );
	// �߂��ɓG������Ȃ�
	if( unit != NULL )
	{
		if( m_AtackCount > 1.0f)
		{
			Shot( unit->m_x, unit->m_y, true );
			m_AtackCount -= 1.0f;
		}
		m_AtackCount += m_AttackSpeed;
	}
	// ���O�����߂��ɂ���Ȃ�
	else if( DXLibMath::CircleOnPoint( position, target, m_Rang ) )
	{
		if( m_AtackCount > 1.0f)
		{
			Shot( target.x, target.y, true );
			m_AtackCount -= 1.0f;
		}
		m_AtackCount += m_AttackSpeed;
	}
	// ����ɉ��������Ȃ�ړ�
	else
	{
		VECTOR facing;
		DXLibMath::FacingTarget( position, target, &m_Facing, 0.1f);
		facing.x = target.x - m_x;
		facing.y = target.y - m_y;
		DXLibMath::Normalize( &facing, facing );
		// �ʉߕs�u���b�N������Ȃ�U��
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