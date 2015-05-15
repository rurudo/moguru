#include "Task_AreaDamage.h"
#include "../System/DataManager.h"
#include "TaskFunction.h"
#include "../System/EquipmentFunction.h"
#include "../System/TaskManager.h"
#include "../Task/Task_DrawEffect.h"

TaskBase* AreaDamage_CreateTask(void)
{
	return new Task_AreaDamage();
}

Task_AreaDamage::Task_AreaDamage(void)
{
}

Task_AreaDamage::~Task_AreaDamage(void)
{
}

void Task_AreaDamage::Init(void)
{
	m_LifeTime = 0;

	m_Position.x = 0.0f;
	m_Position.y = 0.0f;

	m_Damage = 0;
	m_EnemyShot = false;
	m_TargetEnemy = true;
	m_TargetBlock = false;
	m_TargetMogll = true;
	m_allFlag = false;
	m_DamageType = UnitBase::DAMAGETYPE_NORMAL;
	m_DamageData.x = 0.0f;
	m_DamageData.y = 0.0f;
	m_DamageData.z = 0.0f;
	m_enemy = NULL;
	m_task = NULL;
	m_AreaRange = 1.0f;
}

void Task_AreaDamage::PlayTask( void )
{
	if( m_task != NULL )
	{
		if( m_task->GetID() == TASK_TYPE_AREA_DAMAGE )
		{
			Task_AreaDamage* task = dynamic_cast<Task_AreaDamage*>(m_task);
			task->SetPosition( m_Position.x, m_Position.y );
		}
		else if( m_task->GetID() == TASK_TYPE_DRAW_EFFECT )
		{
			Task_DrawEffect* task = dynamic_cast<Task_DrawEffect*>(m_task);
			task->SetPosition( m_Position.x, m_Position.y );
		}
		TaskManager::GetInstance().Add( m_task, 0);
		m_task = NULL;
	}
}

void Task_AreaDamage::Update(UnitManager *unitManager, BlockManager *blockManager)
{
	// 画面外に出たら削除
	if( m_Position.x < -0.5f || 15.5f < m_Position.x || m_Position.y < -2.0f || m_Position.y > 13.0f)
	{
		m_Exist = false;
		return;
	}
	// 範囲内にユニットがいたら攻撃
	if( m_TargetEnemy )
	{
		TaskSet_AreaUnitBadStatusFriend( m_Position.x, m_Position.y, m_Damage, m_AreaRange, m_DamageType, m_DamageData, m_EnemyShot);
	}
	// 範囲内にモグルがいたら攻撃
	DataManager &data = DataManager::GetInstance();
	VECTOR target;
	DXLibMath::ConvertScreenToBlock( data.m_MogllStatus.position.x, data.m_MogllStatus.position.y, &target.x, &target.y );
	if( m_TargetMogll && m_EnemyShot && DXLibMath::CircleOnPoint( m_Position, target, m_AreaRange) )
	{
		data.m_MogllStatus.life -= m_Damage;
	}
	// 範囲内にブロックがあったら攻撃
	if( m_TargetBlock )
	{
		BlockBase* block = blockManager->GetNearBlock( m_Position, m_AreaRange );
		if( block != NULL )
		{
			block->AddDamage( m_Damage, m_enemy->m_ID, (m_enemy->MovePoint == m_enemy->Enemy) );
		}
	}
	// 時間がなくなったら削除
	if( m_LifeTime <= 0 )
	{
		m_Exist = false;
		PlayTask();
		return;
	}
	else
	{
		m_LifeTime--;
	}
}

void Task_AreaDamage::EquipmentConvert( void )
{
	// 味方のみ効果がある装備効果
	if( !m_EnemyShot )
	{
		m_Damage = EquipmentFunction_08( m_Damage );
		// 仲間割れ攻撃アップ装備
		if( EquipmentFunction_16() )
		{
			m_Damage = EquipmentFunction_16_Value( m_Damage );
			m_allFlag = true;
		}
		m_Damage = EquipmentFunction_20( m_Damage, &m_enemy->m_Life );
		// 全員対象攻撃装備
		if( EquipmentFunction_15() )
		{
			m_TargetBlock = true;
			m_TargetEnemy = true;
		}
		EquipmentFunction_21( &m_DamageType, &m_DamageData.x, &m_DamageData.y );
		EquipmentFunction_22( &m_DamageType, &m_DamageData.x );
		EquipmentFunction_23( &m_DamageType, &m_DamageData.x );
		EquipmentFunction_24( &m_DamageType, &m_DamageData.x, &m_DamageData.y );
		EquipmentFunction_25( &m_DamageType, &m_DamageData.x );
	}
	// 敵のみ効果がある装備効果
	else
	{
		m_Damage = EquipmentFunction_30( m_Damage );
	}
}


void Task_AreaDamage::SetPosition(float x, float y)
{
	m_Position.x = x;
	m_Position.y = y;
}


void Task_AreaDamage::SetIsEnemy(bool flag)
{
	m_EnemyShot = flag;
}

void Task_AreaDamage::SetDamage(int damage)
{
	m_Damage = damage;
}

void Task_AreaDamage::SetEnemyHit(bool flag)
{
	m_TargetEnemy = flag;
}

void Task_AreaDamage::SetBlockHit(bool flag)
{
	m_TargetBlock = flag;
}

void Task_AreaDamage::SetMogllHit(bool flag)
{
	m_TargetMogll = flag;
}

void Task_AreaDamage::SetLifeTime( int time )
{
	m_LifeTime = time;
}

void Task_AreaDamage::SetAllFlag( bool flag )
{
	m_allFlag = flag;
}

void Task_AreaDamage::SetDamageType( int type, const VECTOR &value, UnitBase *enemy)
{
	m_DamageType = type;
	m_DamageData = value;
	m_enemy = enemy;
}

void Task_AreaDamage::SetRange(float range)
{
	m_AreaRange = range;
}

void Task_AreaDamage::SetTask(TaskBase* task)
{
	m_task = task;
}