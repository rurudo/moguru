/**
 * ステージ開始時の階層選択画面での演出
 */

#pragma once
#include "../System/DxLibMath.h"
#include "../Play/StageDig.h"

class DepthSelect
{
private:
	// 惑星の階層構造体
	struct PLANET_HIERARCHY{
		int		H_num;	// 何階層あるか
		int		Hier[10];// 階層分けの基準点
	};

	// 惑星の背景用構造体
	struct PLANET_BACKSTAGE{
		VECTOR	Pos;
		float	Scal, Rot;
		VECTOR	Speed;
		int		frame_cnt, FRAME_CNT;
		int		Handle;
		bool	isValid;

	};

	// 状態遷移
	enum State
	{
		State_Fall,			// 空から降ってきて惑星に着陸
		State_Product,		// 演出
		State_Select,		// 階層を選択
		State_Up			// 定位置へ移動
	} m_State;

	enum SwitchState
	{
		St_Go,				// 開始
		St_Select,			// 階層セレクト
		St_Non				// なにもなし
	} m_SwitchState;

	enum NumState
	{
		ON,					// 開始
		OFF,				// 階層セレクト
		NON					// なにもなし
	} m_NumState;
	const static int NUM_STAGEBACK = 6;

	bool m_Enable;			// trueの時処理する
	int m_Frame;			// ウェイト調整用
	PLANET_HIERARCHY HIERARCHY[5];
	PLANET_BACKSTAGE	m_BackStageDate[NUM_STAGEBACK];		// 背景画像のハンドル格納用
	int Open_Hiera;			// どこの階層まで解放されているか
	int m_NowFloor;			// 現在の選択階層
	int m_floor;			// 階層の上下
	int	m_Num_Handle[9];	// 数値画像のハンドル格納用
	int	st_flg;				// マウスが今どのスイッチの上にいるのか(99は例外処理)
	int mouse_st;			// マウスの状態
	int num_st;				// 数字のフラグ
	int bright;				// 明るさ
	int bright_flg;			// 明るさのフラグ
	int m_BlockYBack;		// ブロックの初期座標
	int m_BackFlameLoop[5];	// 背景演出用のループ(フレーム)数カウント
	float m_NumScal;		// 数値の拡縮率
	float m_GoScale;		// GOの拡縮率
	float m_BlockY;			// ブロックの座標
	float m_SubX;			// 演出用のサブＸ座標
	float m_BG_WIDTH;		// BGの幅
	float m_BG_HEIGHT;		// BGの高さ
	VECTOR m_mouse;			// マウス座標
	VECTOR m_myship;		// 宇宙船の座標

	int  m_numachiAnim;	//沼地用アニメーションカウンタ
	bool m_numachiAnimFlg;//沼地用アニメーションフラグ

	// ちゃれんじボードデータ
	struct ChallengeData
	{
		int animCount;
		ChallengeData()
		{
			animCount = 0;
		}
	}m_Challenge;

	// 掘る処理部分
	StageDig m_Dig;
public:
	DepthSelect(void);
	~DepthSelect(void);

	void Init(void);
	void Update(bool);
	void Draw(void);
	void SpacecraftDraw(void);
	void BgAnime(void);
	void BgDraw(void);
	void ChallengeDraw(void);
	bool IsEnable(void)
	{
		return m_Enable;
	}

	void Selection(void);		// マウスで選択
	void NumberScal(void);		// 数字の拡縮
	void Black(void);			// 暗幕
};

