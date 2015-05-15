#pragma once
#include "DxLib.h"
class GameOver
{
private:
	enum State
	{
		State_Fall,				// �󂩂�~���Ă��Ęf���ɒ���
		State_Anime,			// ���o
		State_Up,				// ��ʒu�ֈړ�
	} m_State;

	int m_ArmState;				// �A�[���J�ڗp�X�e�[�^�X
	int m_AnimeArm;				// �A�[���̃A�j���[�V�����p�̃t���O
	int m_Frame;				// ���o�̃^�C�~���O�J�E���^
	int m_Arm_Handle[2];		// �A�[���̉摜�n���h���i�[�p
	int m_Word_Handle[4];		// �����̉摜�n���h���i�[�p
	float m_Bright;				// ���邳
	float m_WordRot[4];			// �����̉�]
	bool m_End;					// ���o���I�����Ă�����true
	VECTOR m_ArmPosition;		// �A�[���̍��W
	VECTOR m_WordPosition[4];	// �����̍��W
public:
	GameOver(void);
	~GameOver(void);
	void Init(void);
	void Draw(void);
	void Update(void);
	bool IsEnd(void);
};

