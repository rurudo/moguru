#pragma once
#include "Unit_SmallMog.h"
#include "../System/DxLibMath.h"

class Unit_Salamander :
	public Unit_SmallMog
{
private:
	int m_Count;			// フレームカウンタ
public:
	Unit_Salamander(void);
	virtual ~Unit_Salamander(void);
	void Init(void);
	void Update(void);
};

// 生成関数
UnitBase* Salamander_CreateUnit(void);