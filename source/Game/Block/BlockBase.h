#pragma once
#include "../System/DxLibMath.h"

class BlockBase
{
protected:
	bool m_Exist;
	int m_TreasureID;
	int m_EnemyID;
	bool m_EnemyLastHit;
public:
	int m_ID;
	int m_Life;
	float m_x, m_y;
	int m_InEnemyID;		// 破壊した時に出てくる敵のID

	BlockBase(void);
	virtual ~BlockBase(void);
	virtual void Update();
	virtual int GetHandle();
	// ブロックの下レイヤー
	virtual void DrawUnder();
	// ブロックの上レイヤー
	virtual void DrawUpper();
	virtual void Init();
	virtual void Release();
	virtual void AddDamage( int damage, int enemyID, bool isEnemy );

	void SetPosition(float x, float y);
	bool IsExist(void);
	void SetExist(bool flag);
	void SetTreasureID( int id );

	int GetID(void);
	int GetHP(void);
	DXLibMath::Vector2 GetPosition(void);
};

