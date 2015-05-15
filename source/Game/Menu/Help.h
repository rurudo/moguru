#pragma once
#include <string.h>
#include "DxLib.h"
#include "../System/DxLibMath.h"
#include "../System/FontManager.h"

class Help
{
private:
	enum STATE
	{
		INDEX,
		REFERENCE,
	};
	enum CONTROL
	{
		STAY,
		PREV,
		NEXT,
		BACK,
	};
	struct DRAW_DATA{
		float	x, y;
		float	scal, rot;
		int		handle;
	};

	bool		m_Exist;
	bool		m_OffFrame;			// �I�������t���[�����ǂ����i�w���v��Update�̂��Ƃ�Open������̂Łj
	int			m_Frame;			// ���o�̃^�C�~���O�J�E���^
	STATE		m_State;			// �X�e�[�g
	int			m_Index;			// �I��ڎ�
	int			m_Page;				// �y�[�W
	int			m_OldPage;			// �O�y�[�W
	int			m_PageAlpha;		// �y�[�W�̃��l
	float		m_M_Scal;			// �}�E�X�̊g�k
	float		m_Help_Button_Scale;// �w���v�{�^���̊g�k
	bool		m_ScalFlg;			// �g�傩�k���̃t���O
	const static int	NUM_PAGE = 12;
	DRAW_DATA	m_WordHowto[NUM_PAGE];		// �`��f�[�^
	const static int	NUM_INDEX = 8;
	int			m_IndexPage[NUM_INDEX];		// ���ڂ��Ƃ̃y�[�W��
	float		m_I_Scale[NUM_INDEX];		// ���ڂ̊g�k��
	FontManager m_Font;			// �����`��p

	int UpdateIndex(void);	// �ڎ�
	Help::STATE UpdateReference(void);	//�y�[�W�X�V
	Help::CONTROL UpdatePages(void);	//�y�[�W����

	void DrawIndex(void);
	void DrawReference(void);

	bool Close(void);

	//�J���[�ύX
	int	ChangeColor(int i)
	{
		if(i == m_Index)
			return GetColor(255, 16, 16);
		return GetColor(0, 0, 0);
	}

public:
	Help(void);
	~Help(void);
	void Draw(void);
	bool Update(void);
	void Init(void);
	bool Open(DXLibMath::Vector2 &mouse);
};

