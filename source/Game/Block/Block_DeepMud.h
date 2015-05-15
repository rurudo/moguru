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

//ê∂ê¨ä÷êî
BlockBase* DeepMud_CreateBlock(void);

