#pragma once
#include "BlockBase.h"
class Block_Stone :
	public BlockBase
{
public:
	Block_Stone(void);
	virtual ~Block_Stone(void);

	virtual void Update();
};

//�����֐�
BlockBase* Stone_CreateBlock(void);

