#pragma once
#include "DxLib.h"
class GameClear
{
private:
	enum State
	{
		State_Move,					// 文字の移動
		State_bright,				// 明暗
	} m_State;

	int m_Frame;					// 演出のタイミングカウンタ
	int m_Word_Handle[9];			// 文字のハンドル
	int m_ClearState;				// クリアステート
	float m_Bright;					// 明るさ
	VECTOR m_WordPosition[9];		// 文字の座標(表示用)
	VECTOR m_WordPositionData[9];	// 文字の座標(保存用)
	VECTOR m_WordDirection[9];		// 文字の進行方向ベクトル格納
	bool m_End;						// 演出が終了していたらtrue
	bool m_isAct;					// 演出中フラグ

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

