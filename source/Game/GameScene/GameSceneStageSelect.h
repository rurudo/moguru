#pragma once
#include "GameScene.h"
#include "../System/DxLibMath.h"
#include "../System/FontManager.h"

//タイトルクラス
class GameSceneStageSelect : public GameScene
{
private:
	// 惑星定義
	enum PlanetID
	{
		PLANET_1,
		PLANET_2,
		PLANET_3,
		PLANET_4,
		PLANET_5,
		PLANET_MAX
	};
	// フェード系のフラグ
	enum Fade{
		NON,
		FADE1,
		FADE2
	};
	// 描画構造体
	struct DRAW_DATA{
		float		x, y, r;
		float		scal, rot;
		int			handle;
		bool		release;
		float		cur_x, cur_y;
		float		cur_scal;
	};

	// 使用データ
	DRAW_DATA	m_Planet[5];				// 惑星のデータ
	DRAW_DATA	m_b_Planet[5];				// 惑星の元データ所持用(ステージ帰還用のバックアップデータ)
	VECTOR		m_b_st[5];					// 演出用に星と星のもとの位置を結ぶベクトルを保存する(ステージ帰還用のバックアップデータ)
	VECTOR		m_terget;					// 目的地
	VECTOR		m_st[5];					// 演出用に星と中点(0.5f,0.5f)を結ぶベクトルを保存する
	FontManager	m_Font;						// フォント管理
	int			m_Planet_Back_handle[5];	// 惑星背景のハンドル
	int			m_BackBrightness;			// 惑星背景の明るさ
	int			m_FrameBrightness;			// 惑星背景の明るさ
	int			m_Brightness;				// フェード用
	int			m_BrightnessFlg;			// フェード用
	int			m_id_back;					// idの保存
	int			m_BeforeId;					// 前フレームの選択状態の保存
	bool		m_BackBrightnessFlg;		// 惑星背景の明るさのフラグ
	bool		m_FrameBrightnessFlg;		// 惑星背景の明るさのフラグ
	bool		m_CursorFlg;				// カーソルの回転率拡縮フラグ
	bool		m_PlanetEffectFlg;			// 惑星の拡縮フラグ
	float		m_scal_back;				// もともとの拡縮率を保存しておく為
	float		m_ship_scal;				// 宇宙船のスケール
	float		m_CursorScal;				// カーソルの拡縮
	float		m_speed;					// 移動速度
	float		m_AddAlpha;					// 加算合成表示物のα値
	float		m_AddAlphaState;			// ↑のα値を変えるやつ
	float		m_PlanetBackScal[5];		// 惑星の元の拡縮を保存しておく用

	// 自機構造体
	struct Ship
	{
		// コンストラクタ
		Ship()
		{
			position.x = 0.0f;
			position.y = 0.0f;
			facing.x = 0.0f;
			facing.y = 0.0f;
			id = PLANET_1;
			handle = 0;
		}
		VECTOR position;		// 座標
		VECTOR facing;			// 向き
		int id;					// 向かう先の惑星
		int handle;				// 描画の為のハンドル
	}m_Ship;
	//マウス座標
	VECTOR m_mouse;
	// プライベート関数
	void MovePoint();			// 宇宙船を移動させる
	void Staging();				// ステージに入る際の演出
	void Staging2();			// ステージから出る際の演出
public:
	GameSceneStageSelect();
	virtual ~GameSceneStageSelect(void);
	virtual int Update(void);
	virtual void Draw(void);

	void Init(void);
	void Release(void);
	void Backup(void);
};

//生成関数
GameScene* GameSceneStageSelect_CreateScene();