#pragma once
#include "UnitBase.h"
#include "../System/DxLibMath.h"

class Unit_ClockRabbit :
	public UnitBase
{
private:
	int m_Count;			// フレームカウンタ
	virtual void Shot(float x, float y, bool isEnemy, bool blockHit = false);
	void MovePoint(void);
	void FreeMove(void);
	void EnemyMove(void);
public:
	Unit_ClockRabbit(void);
	virtual ~Unit_ClockRabbit(void);
	void Init(void);
	void Update(void);
};

// 生成関数
UnitBase* ClockRabbit_CreateUnit(void);