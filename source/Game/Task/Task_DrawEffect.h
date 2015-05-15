#pragma once
#include "TaskBase.h"
#include "../System/DxLibMath.h"

class Task_DrawEffect :
	public TaskBase
{
private:
	static const int HANDLE_MAX = 16;	// 登録できる画像数

	float m_Depth;						// ブロックマネージャから取得した深度

	int m_Handle[ HANDLE_MAX ];			// 描画するハンドル
	int m_ChangeTime[ HANDLE_MAX ];		// 画像が変わるタイミング
	int m_Time;							// 現在時間
	int m_NumData;						// データ総数
	VECTOR m_Position;					// 表示位置
	VECTOR m_Velocity;					// 移動量
	float m_Rotation;					// 回転量
	float m_Size;						// 表示倍率
	float m_AddSize;					// 増加サイズ
	bool m_AutoSlide;					// 画面のスクロールに合わせるならtrue
public:
	Task_DrawEffect(void);
	virtual ~Task_DrawEffect(void);
	virtual void Init(void);
	virtual void Update(UnitManager *unitManager, BlockManager *blockManager);
	virtual void Draw(void);
	// アニメーションの描画定義
	void Add(int handle, int time);
	// 位置設定
	void SetPosition(float x, float y);
	void SetVelocity(float x, float y);
	void SetRotation(float rot);
	void SetSize(float size);
	void SetAddSize(float size);
	void SetAutoSlide(bool flag);
};

TaskBase* DrawEffect_CreateTask(void);