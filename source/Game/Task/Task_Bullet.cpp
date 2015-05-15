#include "Task_Bullet.h"
#include "../System/DataManager.h"
#include "TaskFunction.h"
#include "../System/EquipmentFunction.h"
#include "../System/TaskManager.h"
#include "../Task/Task_AreaDamage.h"
#include "../Task/Task_DrawEffect.h"

TaskBase* Bullet_CreateTask(void)
{
	return new Task_Bullet();
}

Task_Bullet::Task_Bullet(void)
{
}

Task_Bullet::~Task_Bullet(void)
{
}

void Task_Bullet::Init(void)
{
	for(int i = 0; i < HANDLE_MAX; i++)
	{
		m_Handle[i] = 0;
		m_ChangeTime[i] = 0;
	}
	m_LifeTime = 100000;
	m_AnimTime = 0;
	m_NumData = 0;
	m_Position.x = 0.0f;
	m_Position.y = 0.0f;
	m_Velocity.x = 0.0f;
	m_Velocity.y = 0.0f;
	m_Rotation = 0.0f;
	m_Size = 1.0f;
	m_AddSize = 1.0f;
	m_Damage = 0;
	m_AutoSlide = false;
	m_EnemyShot = false;
	m_TargetEnemy = true;
	m_TargetBlock = false;
	m_TargetMogll = true;
	m_allFlag = false;
	m_DamageType = UnitBase::DAMAGETYPE_NORMAL;
	m_DamageData.x = 0.0f;
	m_DamageData.y = 0.0f;
	m_DamageData.z = 0.0f;
	m_PowerCount = 0;
	m_enemy = NULL;
	m_task = NULL;
}

void Task_Bullet::PlayTask( void )
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

void Task_Bullet::Update(UnitManager *unitManager, BlockManager *blockManager)
{
	m_PowerCount++;
	m_Position.x += m_Velocity.x;
	m_Position.y += m_Velocity.y;
	m_AnimTime++;
	m_Size *= m_AddSize;
	int sumTime = 0;
	for(int i = 0; i < m_NumData; i++)
	{
		sumTime += m_ChangeTime[i];
	}
	// アニメーションが終了したらアニメーションの最初へ
	if(m_AnimTime > sumTime)
	{
		m_AnimTime = 0;
	}
	// 画面外に出たら削除
	if( m_Position.x < -0.5f || 15.5f < m_Position.x || m_Position.y < -2.0f || m_Position.y > 13.0f)
	{
		m_Exist = false;
		if( m_task != NULL )
		{
			m_task->SetExist( false );
		}
		return;
	}
	// 硬いブロックには当たる
	{
		BlockBase* block = blockManager->GetNearHardBlock( m_Position, 1.0f );
		if( block != NULL && m_enemy )
		{
			// ブロックに対するダメージ上昇
			m_Damage = EquipmentFunction_37( m_Damage );
			m_Damage = EquipmentFunction_17_Block( m_Damage );
			m_Damage = EquipmentFunction_18_Block( m_Damage );
			block->AddDamage( m_Damage, m_enemy->m_ID, (m_enemy->MovePoint == m_enemy->Enemy) );
			m_Exist = false;
			PlayTask();
			return;
		}
	}
	// 範囲内にユニットがいたら攻撃
	if( m_TargetEnemy )
	{
		UnitBase* unit = unitManager->GetNearUnit( m_Position, 1.0f, !m_EnemyShot, m_allFlag, m_enemy );
		if( unit != NULL )
		{
			if( m_EnemyShot )
			{
				DataManager &data = DataManager::GetInstance();
				float rate = 1.3f - 0.6f * ( data.m_MogllStatus.resource * 1.0f / ( data.m_MogllStatus.maxResource * 1.0f ) );
				m_Damage = static_cast<int>(m_Damage * rate);
				// ユニットの受けるダメージが減る
				m_Damage = EquipmentFunction_39( m_Damage );
				m_Damage = EquipmentFunction_26( m_Damage );
			}
			else
			{
				m_Damage = EquipmentFunction_17_Enemy( m_Damage );
				m_Damage = EquipmentFunction_18_Enemy( m_Damage );
			}
			UnitBase* guardian = unitManager->GetNearGuardian( m_Position.x, m_Position.y, 6.0f, !m_EnemyShot);
			if( guardian )
			{
				guardian->AddDamage( m_Damage, m_DamageType, m_DamageData, m_enemy );
			}
			else
			{
				unit->AddDamage( m_Damage, m_DamageType ,m_DamageData, m_enemy );
			}
			m_Exist = false;
			PlayTask();
			return;
		}
	}
	// 範囲内にモグルがいたら攻撃
	DataManager &data = DataManager::GetInstance();
	VECTOR target;
	DXLibMath::ConvertScreenToBlock( data.m_MogllStatus.position.x, data.m_MogllStatus.position.y, &target.x, &target.y );
	if( m_TargetMogll && m_EnemyShot && DXLibMath::CircleOnPoint( m_Position, target, 1.0f) )
	{
		// 発射されてから当たるまでの時間に比例したダメージ
		if( m_PowerCount < 30 )
		{
			m_Damage = static_cast<int>( m_PowerCount * m_Damage / 30 );
		}
		// メインユニットへのダメージを減少
		m_Damage = EquipmentFunction_38( m_Damage );
		m_Damage = EquipmentFunction_45( m_Damage );
		// 条件を満たせばダメージ無効化
		m_Damage = EquipmentFunction_14( m_Damage );
		m_Damage = EquipmentFunction_04( m_Damage );
		// ガーディアン
		UnitBase* guardian = unitManager->GetNearGuardian( m_Position.x, m_Position.y, 6.0f, !m_EnemyShot);
		if( guardian )
		{
			guardian->AddDamage( m_Damage, m_DamageType, m_DamageData, m_enemy );
		}
		else
		{
			if( m_Damage > 100 )
			{
				m_Damage = 100;
			}
			if( data.m_MogllStatus.noHitTime == 0)
			{
				data.m_MogllStatus.life -= m_Damage;
				data.m_MogllStatus.noHitTime = 2;
			}
		}
		PlaySoundMem( DataManager::GetInstance().Get( DataManager::SoundSE16 ), DX_PLAYTYPE_BACK);
		m_Exist = false;
		PlayTask();
		return;
	}
	// 範囲内にブロックがあったら攻撃
	if( m_TargetBlock )
	{
		BlockBase* block = blockManager->GetNearBlock( m_Position, 1.0f );
		// 液体は掘れない
		//if( block != NULL && block->m_ID != BLOCK_WATER && block->m_ID != BLOCK_FIRE )
		if( block != NULL )
		{
			// ブロックに対するダメージ上昇
			m_Damage = EquipmentFunction_37( m_Damage );
			m_Damage = EquipmentFunction_17_Block( m_Damage );
			m_Damage = EquipmentFunction_18_Block( m_Damage );
			block->AddDamage( m_Damage, m_enemy->m_ID, (m_enemy->MovePoint == m_enemy->Enemy) );
			m_Exist = false;
			PlayTask();
			return;
		}
	}
	// 時間がなくなったら削除
	if( m_LifeTime < 0 )
	{
		m_Exist = false;
		if( m_task != NULL )
		{
			m_task->SetExist( false );
		}
		return;
	}
	else
	{
		m_LifeTime--;
	}
}

void Task_Bullet::Draw(void)
{
	int sumTime = 0;
	for(int i = 0; i < m_NumData; i++)
	{
		sumTime += m_ChangeTime[i];
		if(m_AnimTime < sumTime)
		{
			if( m_AutoSlide )
			{
				float x, y;
				DXLibMath::ConvertBlockToScreen( m_Position.x, m_Position.y, &x, &y );
				DXLibMath::DrawRotaGraphResize( x, y, m_Size, m_Rotation, m_Handle[i], TRUE);
			}
			else
			{
				DXLibMath::DrawRotaGraphResize( m_Position.x, m_Position.y, m_Size, m_Rotation,
					m_Handle[i], TRUE);
			}
			return;
		}
	}
	// ループしたら最初の画像を表示
	if( m_AutoSlide )
	{
		float x, y;
		DXLibMath::ConvertBlockToScreen( m_Position.x, m_Position.y, &x, &y );
		DXLibMath::DrawRotaGraphResize( x, y, m_Size, m_Rotation, m_Handle[0], TRUE);
	}
	else
	{
		DXLibMath::DrawRotaGraphResize( m_Position.x, m_Position.y, m_Size, m_Rotation,
			m_Handle[0], TRUE);
	}
}

void Task_Bullet::EquipmentConvert( void )
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
		EquipmentFunction_31( &m_DamageType, &m_DamageData.x, &m_DamageData.y );
		EquipmentFunction_51( &m_DamageType, &m_DamageData.x, &m_DamageData.y );
		EquipmentFunction_55( &m_DamageType, &m_DamageData.x, &m_DamageData.y, &m_DamageData.z, m_Velocity.x, m_Velocity.y);
		EquipmentFunction_27( &m_DamageType, &m_DamageData.x, &m_DamageData.y, &m_DamageData.z );
	}
	// 敵のみ効果がある装備効果
	else
	{
		m_Damage = EquipmentFunction_30( m_Damage );
	}
}

void Task_Bullet::Add(int handle, int time)
{
	m_Handle[ m_NumData ] = handle;
	m_ChangeTime[ m_NumData ] = time;
	m_NumData++;
}

void Task_Bullet::SetPosition(float x, float y)
{
	m_Position.x = x;
	m_Position.y = y;
}

void Task_Bullet::SetVelocity(float x, float y)
{
	m_Velocity.x = x;
	m_Velocity.y = y;
}

void Task_Bullet::SetRotation(float rot)
{
	m_Rotation = rot;
}

void Task_Bullet::SetSize(float size)
{
	m_Size = size;
}

void Task_Bullet::SetAddSize(float size)
{
	m_AddSize = size;
}

void Task_Bullet::SetAutoSlide(bool flag)
{
	m_AutoSlide = flag;
}

void Task_Bullet::SetIsEnemy(bool flag)
{
	m_EnemyShot = flag;
}

void Task_Bullet::SetDamage(int damage)
{
	m_Damage = damage;
}

void Task_Bullet::SetEnemyHit(bool flag)
{
	m_TargetEnemy = flag;
}

void Task_Bullet::SetBlockHit(bool flag)
{
	m_TargetBlock = flag;
}

void Task_Bullet::SetMogllHit(bool flag)
{
	m_TargetMogll = flag;
}

void Task_Bullet::SetLifeTime( int time )
{
	m_LifeTime = time;
}

void Task_Bullet::SetAllFlag( bool flag )
{
	m_allFlag = flag;
}

void Task_Bullet::SetDamageType( int type, const VECTOR &value, UnitBase *enemy)
{
	m_DamageType = type;
	m_DamageData = value;
	m_enemy = enemy;
}

void Task_Bullet::SetTask( TaskBase* task )
{
	m_task = task;
}