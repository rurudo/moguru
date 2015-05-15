#pragma once
#include "BlockBase.h"
class Block_Bomb :
	public BlockBase
{
public:
	Block_Bomb(void);
	virtual ~Block_Bomb(void);

	virtual void Update();
};

//ê∂ê¨ä÷êî
BlockBase* Bomb_CreateBlock(void);

