#pragma once
#include "TaskBase.h"
#include "../System/DxLibMath.h"

class Task_DrawEffect :
	public TaskBase
{
private:
	static const int HANDLE_MAX = 16;	// �o�^�ł���摜��

	float m_Depth;						// �u���b�N�}�l�[�W������擾�����[�x

	int m_Handle[ HANDLE_MAX ];			// �`�悷��n���h��
	int m_ChangeTime[ HANDLE_MAX ];		// �摜���ς��^�C�~���O
	int m_Time;							// ���ݎ���
	int m_NumData;						// �f�[�^����
	VECTOR m_Position;					// �\���ʒu
	VECTOR m_Velocity;					// �ړ���
	float m_Rotation;					// ��]��
	float m_Size;						// �\���{��
	float m_AddSize;					// �����T�C�Y
	bool m_AutoSlide;					// ��ʂ̃X�N���[���ɍ��킹��Ȃ�true
public:
	Task_DrawEffect(void);
	virtual ~Task_DrawEffect(void);
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
};

TaskBase* DrawEffect_CreateTask(void);