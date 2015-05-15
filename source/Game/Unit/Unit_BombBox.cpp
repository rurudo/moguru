#include "Unit_BombBox.h"
#include "../System/DataManager.h"
#include "../System/TaskManager.h"
#include "../Task/Task_Bullet.h"
#include "../Task/Task_AreaDamage.h"
#include "../Task/TaskFunction.h"

UnitBase* BombBox_CreateUnit(void)
{
	return new Unit_BombBox();
}

Unit_BombBox::Unit_BombBox(void)
{
}

Unit_BombBox::~Unit_BombBox(void)
{
}

void Unit_BombBox::Shot(float x, float y, bool isEnemy, bool blockHit)
{
	if( !m_AttackEnable )
	{
		return;
	}
	TaskManager &taskManager = TaskManager::GetInstance();
	// �ǉ��^�X�N���ɍ쐬
	Task_AreaDamage* addTask = dynamic_cast<Task_AreaDamage*>( taskManager.CreateTask(TASK_TYPE_AREA_DAMAGE) );
	addTask->SetTask( TaskSet_DrawExplodTask( m_x, m_y ) );
	addTask->SetDamage( m_Power );
	addTask->SetRange( 2.0f );
	VECTOR damageData;
	damageData.x = 60.0f;
	addTask->SetAllFlag( true );
	addTask->SetBlockHit( true );
	addTask->SetIsEnemy( isEnemy );
	// �������Ȃ�
	if( m_BadStatus[ UnitBase::DAMAGETYPE_CONFUSION ].x > 0.0f )
	{
		addTask->SetAllFlag( true );
	}
	addTask->SetDamageType( UnitBase::DAMAGETYPE_NORMAL, damageData, this);
	addTask->EquipmentConvert();

	// �e�̕����쐬
	Task_Bullet* task = dynamic_cast<Task_Bullet*>( taskManager.CreateTask(TASK_TYPE_BULLET) );
	task->SetTask( addTask );
	task->SetPosition( m_x, m_y );
	// �ˏo�����̌v�Z
	VECTOR target;
	target.x = x - m_x;
	target.y = y - m_y;
	DXLibMath::Normalize( &target, target );
	task->SetVelocity( target.x * 0.1f, target.y * 0.1f );
	task->SetBlockHit( blockHit );
	task->SetEnemyHit( true );
	// �������Ȃ�
	if( m_BadStatus[ UnitBase::DAMAGETYPE_CONFUSION ].x > 0.0f )
	{
		task->SetAllFlag( true );
	}
	task->SetDamage( 0 );
	task->SetIsEnemy( isEnemy );
	task->SetAutoSlide( true );					// ������Ȃ��ƃu���b�N���W�n�Ōv�Z���Ă���Ȃ�
	// �U���̎��
	task->SetDamageType( UnitBase::DAMAGETYPE_NORMAL, damageData, this);
	task->EquipmentConvert();
	// ���˂���G�t�F�N�g�̉摜�Ǝ��Ԃ��w��
	DataManager &data = DataManager::GetInstance();
	task->Add( data.Get( DataManager::GG_BULLET_NORMAL01 ), 40 );
	// �^�X�N�}�l�[�W���ɂ��̃^�X�N��o�^
	taskManager.Add( task, 0 );
}
