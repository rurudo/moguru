#pragma once
#include "BlockBase.h"
class Block_EnemyIce :
	public BlockBase
{
public:
	Block_EnemyIce(void);
	virtual ~Block_EnemyIce(void);
	virtual void Update();
	void DrawUnder();
	int GetHandle();
};

//�����֐�
BlockBase* EnemyIce_CreateBlock(void);

