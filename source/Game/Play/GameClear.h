#pragma once
#include "DxLib.h"
class GameClear
{
private:
	enum State
	{
		State_Move,					// �����̈ړ�
		State_bright,				// ����
	} m_State;

	int m_Frame;					// ���o�̃^�C�~���O�J�E���^
	int m_Word_Handle[9];			// �����̃n���h��
	int m_ClearState;				// �N���A�X�e�[�g
	float m_Bright;					// ���邳
	VECTOR m_WordPosition[9];		// �����̍��W(�\���p)
	VECTOR m_WordPositionData[9];	// �����̍��W(�ۑ��p)
	VECTOR m_WordDirection[9];		// �����̐i�s�����x�N�g���i�[
	bool m_End;						// ���o���I�����Ă�����true
	bool m_isAct;					// ���o���t���O

public:
	GameClear(void);
	~GameClear(void);
	void Draw(void);
	void Update(void);
	bool IsEnd(void);
	void Init(void);

	bool IsAct(void)
	{
		return m_isAct;
	}
};

