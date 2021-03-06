// 宝箱

#pragma once
#include "UnitBase.h"
#include "../System/DxLibMath.h"

class Unit_TreasureBox :
	public UnitBase
{
private:
	int m_TreasureID;		// 入っている宝物のID
	float m_FrameCount;		// フレーム
public:
	Unit_TreasureBox(void);
	virtual ~Unit_TreasureBox(void);
	virtual void Init(void);
	virtual void Draw(void);
	virtual void Update(void);
	void AddDamage( int damage, int type, const VECTOR &value, UnitBase *enemy);
	// 指定の宝を入れる
	void SetTreasureID(int id);
};

// 生成関数
UnitBase* TreasureBox_CreateUnit(void);