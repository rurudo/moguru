#pragma once
#include "BlockBase.h"
class Block_Rock :
	public BlockBase
{
public:
	Block_Rock(void);
	virtual ~Block_Rock(void);
	virtual void Update();
};

//�����֐�
BlockBase* Rock_CreateBlock(void);

