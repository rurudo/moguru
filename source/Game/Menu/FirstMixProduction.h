#pragma once
#include "DxLib.h"
#include "../System/FontManager.h"

class FirstMixProduction
{
public:
	FirstMixProduction(void);
	~FirstMixProduction(void);

	//������
	void Init(void);
	//���
	void Release(void);
	//�X�V
	bool Update(void);
	//�`��
	void Draw(void);

	//�L����
	void Enable(int MixNum,int MixType);

	bool GetEnable(void);
private:
	//�X�e�b�v�̍X�V
	void StepUpdate(void);

	//�X�e�b�v����
	void StepInItem(void);
	void StepInFrame(void);
	void StepInMessage(void);
	void StepInDescription(void);
	void StepOutItem(void);
	void StepOutFrame(void);
	void StepOutMessage(void);
	void StepOutDescription(void);

	//�X�e�b�v���̕`��
	void DrawItem(void);
	void DrawFrame(void);
	void DrawMessage(void);
	void DrawDescription(void);

	//���Z�b�g
	void Reset(void);

	char m_ItemStatus[60];			// �����̏����A�������A�������A�������̃X�e�[�^�X
	char m_UnitStatus[30];			// ���j�b�g�̏����A�������A�������A�������̃X�e�[�^�X

	//�����������̂�ID
	int m_ID;
	//�^�C�v
	int m_Type;
	//�t���[��
	int m_Frame;
	//���l
	int m_AlphaItem;
	int m_AlphaFrame;
	int m_AlphaMessage;
	int m_AlphaDescription;

	int m_ItemX;
	int m_ItemY;
	int m_ItemW;
	int m_ItemH;
	int m_FrameX;
	int m_FrameY;
	int m_FrameW;
	int m_FrameH;
	int m_MessageX;
	int m_MessageY;
	int m_MessageW;
	int m_DescriptionX;
	int m_DescriptionY;
	int m_DescriptionW;
	//�X�e�b�v
	int m_Step;

	//�L���t���O
	bool m_Enable;
	//�X�L�b�v�t���O
	bool m_Skip;
	//�X�L�b�v���t���O
	bool m_NowSkip;

	FontManager m_FontManager;

	enum Step{
		STEP_Init,
		STEP_InItem,
		STEP_InFrame,
		STEP_InMessage,
		STEP_InDescription,
		STEP_Wait,
		STEP_OutItem,
		STEP_OutFrame,
		STEP_OutMessage,
		STEP_OutDescription
	};

	static const int FrameInItem;
	static const int FrameInFrame;
	static const int FrameInMessage;
	static const int FrameInDescription;
	static const int FrameWait;
	static const int FrameOutItem;
	static const int FrameOutFrame;
	static const int FrameOutMessage;
	static const int FrameOutDescription;
	
	static const int Movement;
};

