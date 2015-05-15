#pragma once
#include "BlockBase.h"
class Block_Confuse :
	public BlockBase
{
public:
	Block_Confuse(void);
	virtual ~Block_Confuse(void);

	virtual void Update();
};

//ê∂ê¨ä÷êî
BlockBase* Confuse_CreateBlock(void);

