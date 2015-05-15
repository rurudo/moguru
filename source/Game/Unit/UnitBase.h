#pragma once
#include "DxLib.h"

class UnitBase
{
public:
	enum DamageType
	{
		// y:�_���[�W��
		DAMAGETYPE_FIRE,			// �R��
		// y:�ቺ�{��
		DAMAGETYPE_SLOW,			// �X���E
		DAMAGETYPE_STOP,			// ����
		DAMAGETYPE_PARALYSIS,		// ���
		// y:�{��
		DAMAGETYPE_RANG,			// �����W
		DAMAGETYPE_CONFUSION,		// ����
		// y:�{��
		DAMAGETYPE_ATTACKSPEED,		// �U�����x
		// yz: �ړ���
		DAMAGETYPE_MOVE,			// �m�b�N�o�b�N
		DAMAGETYPE_MAX,				// ��Ԉُ�̍ő�l

		DAMAGETYPE_NORMAL,			// �ʏ�
		DAMAGETYPE_LIFESTEAL,		// �h���C��
		DAMAGETYPE_BLOCK			// �u���b�N����
	};
protected:
	// ���
	float m_nextX, m_nextY;		// �ړ���
	bool m_Exist;
	bool m_AttackEnable;		// �U���\�t���O
	float m_AtackCount;			// �U���p�x�J�E���g
	VECTOR m_Facing;			// ����
	int m_AnimTime;				// �A�j���[�V��������
public:
	int m_TreasureID;			// �������Ă����
	UnitBase *m_DamageSrc;		// �U����
	VECTOR m_BadStatus[DAMAGETYPE_MAX];		// �t���ϐ�(x: ���ʎ���, yz:���R)
	int	m_ID;					// ���j�b�gID
	float m_x, m_y;
	// �X�e�[�^�X
	int m_MaxLife;
	int m_Life;
	float m_Speed;
	float m_AttackSpeed;
	float m_Rang;
	int m_Power;
	// �ړ����@�̏��
	enum MoveStatus
	{
		MovePoint,	// ���ߒn�_�Ɉړ���
		Free,		// ���R�s����
		Enemy		// ���̃��j�b�g�͓G
	}m_MoveStatus;
	UnitBase(void);
	virtual ~UnitBase(void);
	virtual void Update();
	virtual void Draw();
	virtual void DrawAlpha();
	virtual void Init();
	virtual void Release();
	// ��Ԉُ�̏������X�V
	void BadStatusUpdate(void);
	// �����X�e�[�^�X���Z�b�g
	void SetStatus(void);

	virtual void AddDamage( int damage, int type, const VECTOR &value, UnitBase *enemy);

	void SetPosition(float x, float y);
	void AddPosition(float x, float y);
	void SetTargetPosition(float x, float y);
	bool IsExist(void);
	void SetExist(bool flag);
	int GetMaxLife( void );
	bool GetStopFlag( void );
	void SetTreasureID( int id );
};

