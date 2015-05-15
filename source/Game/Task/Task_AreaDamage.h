/*
 * ��{�I�ȓ����DrawEffect�Ɠ���
 * �Ⴂ�̓o���b�g�N���X�ɂ̓��j�b�g�Ƃ̓����蔻��ƏՓ˂������̌��ʂ��L�q����
 */

#pragma once
#include "TaskBase.h"
#include "../System/DxLibMath.h"
#include "../Unit/UnitBase.h"

class Task_AreaDamage :
	public TaskBase
{
private:

	VECTOR m_Position;					// �\���ʒu
	bool m_EnemyShot;					// �G�̍U�����ǂ���
	int m_Damage;						// �U���̈З�
	bool m_TargetEnemy;					// �G�ɓ����邩
	bool m_TargetBlock;					// �u���b�N�ɓ����邩
	bool m_TargetMogll;					// ���O���ɓ����邩�ǂ���
	bool m_allFlag;						// �S�Ẵ��j�b�g�ɓ����邩�ǂ���
	int m_LifeTime;						// ��������
	int m_DamageType;					// �U���̎��
	VECTOR m_DamageData;				// �U���^�C�v�̕t���f�[�^

	float m_AreaRange;					// �͈͍U���̃����W

	UnitBase *m_enemy;					// �U�����̃A�h���X
	TaskBase *m_task;					// �ǉ��^�X�N
	void PlayTask(void);				// �o�^���ꂽ�^�X�N�����s����
public:
	Task_AreaDamage(void);
	virtual ~Task_AreaDamage(void);
	virtual void Init(void);
	virtual void Update(UnitManager *unitManager, BlockManager *blockManager);

	// �ʒu�ݒ�
	void SetPosition(float x, float y);
	void SetIsEnemy(bool flag);
	void SetDamage(int damage);
	void SetEnemyHit(bool flag);
	void SetBlockHit(bool flag);
	void SetMogllHit(bool flag);
	void SetLifeTime(int time);
	void SetAllFlag(bool flag);
	void SetDamageType( int type, const VECTOR &value, UnitBase *enemy);
	void SetRange(float range);
	void SetTask(TaskBase *task);
	// ���͂��ꂽ�f�[�^�ɑ����␳��������
	void EquipmentConvert( void );
};

TaskBase* AreaDamage_CreateTask(void);