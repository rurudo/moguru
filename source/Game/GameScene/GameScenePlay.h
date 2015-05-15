#pragma once
#include "GameScene.h"
#include "../System/CustomUserInterface.h"
#include "../System/BlockManager.h"
#include "../System/UnitManager.h"

#include "../Menu/GameMenu.h"
#include "../Menu/Help.h"
#include "../Play/DepthSelect.h"
#include "../Play/PlayUserInterface.h"
#include "../Play/GameOver.h"
#include "../Play/GameClear.h"
#include "../Play/TreasureEffect.h"
#include "../Play/AfterGetMapProduction.h"
#include "../Play/StageDig.h"
#include "../Block/BreakBlock.h"


//ゲームクラス
class GameScenePlay : public GameScene
{
private:
	// 惑星の階層構造体
	struct PLANET_HIERARCHY{
		int		H_num;		// 何階層あるか
		int		Hier[10];	// 階層分けの基準点
	};
	// 惑星データ格納用
	PLANET_HIERARCHY HIERARCHY[5];

	//フレームカウント
	int m_FrameCount;

	int m_DebugNowGetID;

	// メニュー
	GameMenu *m_Menu;
	Help	  m_Help;
	UIDisplay m_UIDisplay;
	// 階層選択
	DepthSelect m_DepthSelect;
	// UI
	PlayUserInterface m_UserInterface;
	// ゲームオーバー
	GameOver m_GameOver;
	// ゲームクリア
	GameClear m_GameClear;
	// 掘る処理部分
	StageDig m_Dig;
	// お宝ゲットエフェクト
	TreasureEffect m_TreasureEffect;
	//
	AfterGetMapProduction m_AfterGetItem;

	BreakBlock m_BreakBlock;
	// Helpを開いているかのフラグ
	bool m_HelpFlg;
	// 脱出ウィンドウのフラグ
	bool m_EscapeFlag;
	// 音タイミング用変数
	int m_SoundTime;

	void SetDebugData(void);
	// 装備等のパッシブ効果の処理
	void AutoSkill(void);
public:
	GameScenePlay(void);
	virtual ~GameScenePlay(void);
	virtual int Update(void);
	virtual void Draw(void);
	
	void Init(void);
	void Release(void);
};

//生成関数
GameScene* GameScenePlay_CreateScene();