#pragma once
#include "BlockBase.h"
class Block_Water :
	public BlockBase
{
public:
	Block_Water(void);
	virtual ~Block_Water(void);

	virtual void Update();
};

//�����֐�
BlockBase* Water_CreateBlock(void);

