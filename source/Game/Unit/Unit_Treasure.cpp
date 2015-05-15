#include "Unit_Treasure.h"
#include "../System/DataManager.h"
#include "../System/BlockManager.h"
#include "../System/UnitManager.h"
#include "../Task/TaskFunction.h"
#include "../System/EquipmentFunction.h"

UnitBase* Treasure_CreateUnit(void)
{
	return new Unit_Treasure();
}

Unit_Treasure::Unit_Treasure(void)
{
}

Unit_Treasure::~Unit_Treasure(void)
{
}

void Unit_Treasure::Update(void)
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

void Unit_Treasure::Shot(float x, float y, bool isEnemy, bool blockHit, bool enemyHit)
{
	if( !m_AttackEnable )
	{
		return;
	}
	VECTOR damageData;
	int damage = m_Power;
	// �G�ɓ����鎞�͍T���߂̃_���[�W
	if( enemyHit )
	{
		damage /= 4;
	}
	TaskSet_Shot( damage, UnitBase::DAMAGETYPE_NORMAL, damageData, m_x, m_y, x, y, isEnemy, blockHit, this, enemyHit);
}

void Unit_Treasure::MovePoint(void)
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
	// �߂��ɕ󂪂���Ȃ�
	UnitManager &unitManager = UnitManager::GetInstance();
	std::list<UnitBase*> &list = unitManager.GetAll();
	UnitBase* unit = NULL;
	for( std::list<UnitBase*>::iterator i = list.begin(); i != list.end(); i++)
	{
		if( (*i)->m_ID == UNIT_TreasureBox )
		{
			unit = (*i);
			break;
		}
	}
	if( unit != NULL )
	{
		if( m_AtackCount > 1.0f)
		{
			Shot( unit->m_x, unit->m_y, false );
			m_AtackCount -= 1.0f;
		}
		m_AtackCount += m_AttackSpeed;
	}
	// �i�s�r���Ɏז��ȃu���b�N������Ȃ�j��
	if( block != NULL && block->m_ID != BLOCK_WATER && block->m_ID != BLOCK_FIRE)
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
	block = blockManager.GetNearHardBlock( position, m_Rang );
	// �d���u���b�N����������U��
	if( block != NULL )
	{
		if( m_AtackCount > 1.0f)
		{
			Shot( block->m_x, block->m_y - blockManager.GetDepth(), false, true, false );
			m_AtackCount -= 1.0f;
		}
		m_AtackCount += m_AttackSpeed;
	}
	// �ڕW�n�_�ɓ��B�����玩�R�s��
	// �܂��͍U�����󂯂��玩�R�s��
	if( DXLibMath::CircleOnPoint( position, target, 0.1f) || m_DamageSrc != NULL)
	{
		m_MoveStatus = UnitBase::Free;
	}
}

void Unit_Treasure::FreeMove(void)
{
	VECTOR position;
	position.x = m_x;
	position.y = m_y;

	// �u���b�N��T��
	BlockManager &blockManager = BlockManager::GetInstance();
	BlockBase* block = blockManager.GetNearHardBlock( position, m_Rang );
	// �d���u���b�N����������U��
	if( block != NULL )
	{
		if( m_AtackCount > 1.0f)
		{
			Shot( block->m_x, block->m_y - blockManager.GetDepth(), false, true, false );
			m_AtackCount -= 1.0f;
		}
		m_AtackCount += m_AttackSpeed;
	}
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

void Unit_Treasure::EnemyMove(void)
{
	// �ړ�
	VECTOR position;	// ���j�b�g�̍��W
	VECTOR mogllPos;		// ���O���̍��W
	position.x = m_x;
	position.y = m_y;
	// ���O���̍��W����ʍ��W�Ȃ̂ŕϊ�
	DataManager &data = DataManager::GetInstance();
	DXLibMath::ConvertScreenToBlock( data.m_MogllStatus.position.x, data.m_MogllStatus.position.y, &mogllPos.x, &mogllPos.y );
	// �����ς�
	DXLibMath::FacingTarget( position, mogllPos, &m_Facing, 0.1f);
	// �u���b�N��T��
	BlockManager &blockManager = BlockManager::GetInstance();
	BlockBase* block = blockManager.GetNearHardBlock( position, m_Rang );
	// �d���u���b�N����������U��
	if( block != NULL )
	{
		if( m_AtackCount > 1.0f)
		{
			Shot( block->m_x, block->m_y - blockManager.GetDepth(), true, true, false );
			m_AtackCount -= 1.0f;
		}
		m_AtackCount += m_AttackSpeed;
	}
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
	else if( DXLibMath::CircleOnPoint( position, mogllPos, m_Rang ) )
	{
		if( m_AtackCount > 1.0f)
		{
			Shot( mogllPos.x, mogllPos.y, true );
			m_AtackCount -= 1.0f;
		}
		m_AtackCount += m_AttackSpeed;
	}
	// ����ɉ��������Ȃ�ړ�
	else
	{
		VECTOR facing;
		DXLibMath::FacingTarget( position, mogllPos, &m_Facing, 0.1f);
		facing.x = mogllPos.x - m_x;
		facing.y = mogllPos.y - m_y;
		DXLibMath::Normalize( &facing, facing );
		// �ʉߕs�u���b�N������Ȃ�U��
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