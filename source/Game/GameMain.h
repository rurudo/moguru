#pragma once
#include "GameScene/GameScene.h"
class GameMain
{
private:
	GameScene* m_pGameScene;
	bool		m_Pause;
	float		m_FPS;			// １秒辺りのフレーム数
	int			m_TimeCount[61];// 時間カウンタ
	int			m_FrameCount;	// フレームカウント
	int			m_ScreenBuffer;	// 画面バッファ
	int			m_SkipFrame;	// スキップするフレーム数
	int			m_SkipRate;		// スキップするフレーム評価値

public:
	GameMain();
	~GameMain();

	void Init(void);
	int Update(void);
	void Release(void);
};