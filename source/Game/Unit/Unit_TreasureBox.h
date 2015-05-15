// ��

#pragma once
#include "UnitBase.h"
#include "../System/DxLibMath.h"

class Unit_TreasureBox :
	public UnitBase
{
private:
	int m_TreasureID;		// �����Ă���󕨂�ID
	float m_FrameCount;		// �t���[��
public:
	Unit_TreasureBox(void);
	virtual ~Unit_TreasureBox(void);
	virtual void Init(void);
	virtual void Draw(void);
	virtual void Update(void);
	void AddDamage( int damage, int type, const VECTOR &value, UnitBase *enemy);
	// �w��̕������
	void SetTreasureID(int id);
};

// �����֐�
UnitBase* TreasureBox_CreateUnit(void);