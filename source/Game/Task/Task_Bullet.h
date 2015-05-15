/*
 * ��{�I�ȓ����DrawEffect�Ɠ���
 * �Ⴂ�̓o���b�g�N���X�ɂ̓��j�b�g�Ƃ̓����蔻��ƏՓ˂������̌��ʂ��L�q����
 */

#pragma once
#include "TaskBase.h"
#include "../System/DxLibMath.h"
#include "../Unit/UnitBase.h"

class Task_Bullet :
	public TaskBase
{
private:
	static const int HANDLE_MAX = 16;	// �o�^�ł���摜��

	int m_Handle[ HANDLE_MAX ];			// �`�悷��n���h��
	int m_ChangeTime[ HANDLE_MAX ];		// �摜���ς��^�C�~���O
	int m_AnimTime;						// ���ݎ���
	int m_NumData;						// �f�[�^����
	VECTOR m_Position;					// �\���ʒu
	VECTOR m_Velocity;					// �ړ���
	float m_Rotation;					// ��]��
	float m_Size;						// �\���{��
	float m_AddSize;					// �����T�C�Y
	bool m_AutoSlide;					// ��ʂ̃X�N���[���ɍ��킹��Ȃ�true
	bool m_EnemyShot;					// �G�̍U�����ǂ���
	int m_Damage;						// �U���̈З�
	bool m_TargetEnemy;					// �G�ɓ����邩
	bool m_TargetBlock;					// �u���b�N�ɓ����邩
	bool m_TargetMogll;					// ���O���ɓ����邩�ǂ���
	bool m_allFlag;						// �S�Ẵ��j�b�g�ɓ����邩�ǂ���
	int m_LifeTime;						// ��������
	int m_DamageType;					// �U���̎��
	VECTOR m_DamageData;				// �U���^�C�v�̕t���f�[�^
	int m_PowerCount;					// ���˂���Ă���J�E���g�B�U�����[�g

	UnitBase *m_enemy;					// �U�����̃A�h���X
	TaskBase *m_task;					// �e�q�b�g���Ɏ��s����^�X�N
	void PlayTask();					// �^�X�N�����s����
public:
	Task_Bullet(void);
	virtual ~Task_Bullet(void);
	virtual void Init(void);
	virtual void Update(UnitManager *unitManager, BlockManager *blockManager);
	virtual void Draw(void);
	// �A�j���[�V�����̕`���`
	void Add(int handle, int time);
	// �ʒu�ݒ�
	void SetPosition(float x, float y);
	void SetVelocity(float x, float y);
	void SetRotation(float rot);
	void SetSize(float size);
	void SetAddSize(float size);
	void SetAutoSlide(bool flag);
	void SetIsEnemy(bool flag);
	void SetDamage(int damage);
	void SetEnemyHit(bool flag);
	void SetBlockHit(bool flag);
	void SetMogllHit(bool flag);
	void SetLifeTime(int time);
	void SetAllFlag(bool flag);
	void SetDamageType( int type, const VECTOR &value, UnitBase *enemy);
	// ���͂��ꂽ�f�[�^�ɑ����␳��������
	void EquipmentConvert( void );
	void SetTask( TaskBase* task );
};

TaskBase* Bullet_CreateTask(void);