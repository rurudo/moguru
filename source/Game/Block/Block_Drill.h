#pragma once
#include "BlockBase.h"
class Block_Drill :
	public BlockBase
{
public:
	Block_Drill(void);
	virtual ~Block_Drill(void);

	virtual void Update();
	void AddDamage( int damage, int enemyID, bool isEnemy );
};

//�����֐�
BlockBase* Drill_CreateBlock(void);

