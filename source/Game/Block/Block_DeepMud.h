#pragma once
#include "BlockBase.h"
class Block_DeepMud :
	public BlockBase
{
public:
	Block_DeepMud(void);
	virtual ~Block_DeepMud(void);

	virtual void Update();
};

//�����֐�
BlockBase* DeepMud_CreateBlock(void);

