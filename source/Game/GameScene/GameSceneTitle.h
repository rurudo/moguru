#pragma once
#include "GameScene.h"

//タイトルクラス
class GameSceneTitle : public GameScene
{
private:
	// 描画構造体
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
	VECTOR		m_mouse;		//マウス座標
	bool		Break_flg, Hit_flg;
	bool		m_rotflg_st[4], m_rotflg_how[3];
	bool		RotFlg;
	int			m_Mog_Anim_ST;	// モグラのアニメステータス
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
	int			m_LogoBackAlpha;	//タイトルロゴの背景のα値
	bool		m_Fadeflg;


	// ゲーム遷移状態
	enum Status
	{
		STATE_TeamLogo,		// チームロゴ
		STATE_AutoDemo,		// デモ
		STATE_Title,		// タイトル
		STATE_FADE			// フェード
	};
	enum Mouse_Status
	{
		START,				// start
		HOWTO,				// haw to play
		NON					// 選択なし
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

	Status m_TitleStatus;	// シーンの状態
	int m_FrameCount;		// フレームカウント
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

//生成関数
GameScene* GameSceneTitle_CreateScene();