#pragma once
#include "GameScene.h"

//�^�C�g���N���X
class GameSceneTitle : public GameScene
{
private:
	// �`��\����
	struct ANIME_DATA{
		int		frame;
		int		handle;
	};
	struct DRAW_DATA{
		float	x, y;
		float	scal, rot;
		int		handle;
	};

	static const int FADE_IN_COUNT = 30;
	static const int FADE_OUT_COUNT = 15;
	VECTOR		m_mouse;		//�}�E�X���W
	bool		Break_flg, Hit_flg;
	bool		m_rotflg_st[4], m_rotflg_how[3];
	bool		RotFlg;
	int			m_Mog_Anim_ST;	// ���O���̃A�j���X�e�[�^�X
	int			flg;
	int			loop[3];
	int			Anim[2];
	int			TutFlg;
	int			m_MouseFlg;
	float		MouRot;
	float		m_Bright;
	ANIME_DATA	m_Crack[3];
	ANIME_DATA	m_Crash[2];
	DRAW_DATA	m_Title;
	DRAW_DATA	m_Mog;
	DRAW_DATA	m_Rock[2];
	DRAW_DATA	m_WordStart[4];
	DRAW_DATA	m_WordStartBack[4];
	DRAW_DATA	m_S_Rock[8];
	DRAW_DATA	m_LogoBack;
	int			m_LogoBackAlpha;	//�^�C�g�����S�̔w�i�̃��l
	bool		m_Fadeflg;


	// �Q�[���J�ڏ��
	enum Status
	{
		STATE_TeamLogo,		// �`�[�����S
		STATE_AutoDemo,		// �f��
		STATE_Title,		// �^�C�g��
		STATE_FADE			// �t�F�[�h
	};
	enum Mouse_Status
	{
		START,				// start
		HOWTO,				// haw to play
		NON					// �I���Ȃ�
	};
	enum MogST
	{
		Move1,
		Shake,
		Move2,
		Move3,
		Move4,
		Stop,
	};

	Status m_TitleStatus;	// �V�[���̏��
	int m_FrameCount;		// �t���[���J�E���g
public:
	GameSceneTitle();
	virtual ~GameSceneTitle(void);
	virtual int Update(void);
	virtual void Draw(void);

	void Init(void);
	void Release(void);

	void FadeCalc(int outCount);
	void AutoDemo(void);

	void ObjDraw(void);
	void RockDraw(void);
};

//�����֐�
GameScene* GameSceneTitle_CreateScene();