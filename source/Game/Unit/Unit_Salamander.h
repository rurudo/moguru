#pragma once
#include "Unit_SmallMog.h"
#include "../System/DxLibMath.h"

class Unit_Salamander :
	public Unit_SmallMog
{
private:
	int m_Count;			// �t���[���J�E���^
public:
	Unit_Salamander(void);
	virtual ~Unit_Salamander(void);
	void Init(void);
	void Update(void);
};

// �����֐�
UnitBase* Salamander_CreateUnit(void);