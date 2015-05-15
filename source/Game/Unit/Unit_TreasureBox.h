// •ó” 

#pragma once
#include "UnitBase.h"
#include "../System/DxLibMath.h"

class Unit_TreasureBox :
	public UnitBase
{
private:
	int m_TreasureID;		// “ü‚Á‚Ä‚¢‚é•ó•¨‚ÌID
	float m_FrameCount;		// ƒtƒŒ[ƒ€
public:
	Unit_TreasureBox(void);
	virtual ~Unit_TreasureBox(void);
	virtual void Init(void);
	virtual void Draw(void);
	virtual void Update(void);
	void AddDamage( int damage, int type, const VECTOR &value, UnitBase *enemy);
	// w’è‚Ì•ó‚ğ“ü‚ê‚é
	void SetTreasureID(int id);
};

// ¶¬ŠÖ”
UnitBase* TreasureBox_CreateUnit(void);