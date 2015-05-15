#pragma once
#include "DxLib.h"
class GameOver
{
private:
	enum State
	{
		State_Fall,				// 空から降ってきて惑星に着陸
		State_Anime,			// 演出
		State_Up,				// 定位置へ移動
	} m_State;

	int m_ArmState;				// アーム遷移用ステータス
	int m_AnimeArm;				// アームのアニメーション用のフラグ
	int m_Frame;				// 演出のタイミングカウンタ
	int m_Arm_Handle[2];		// アームの画像ハンドル格納用
	int m_Word_Handle[4];		// 文字の画像ハンドル格納用
	float m_Bright;				// 明るさ
	float m_WordRot[4];			// 文字の回転
	bool m_End;					// 演出が終了していたらtrue
	VECTOR m_ArmPosition;		// アームの座標
	VECTOR m_WordPosition[4];	// 文字の座標
public:
	GameOver(void);
	~GameOver(void);
	void Init(void);
	void Draw(void);
	void Update(void);
	bool IsEnd(void);
};

