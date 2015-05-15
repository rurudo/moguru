#pragma once
#include "BlockBase.h"
class Block_HardSoil :
	public BlockBase
{
public:
	Block_HardSoil(void);
	virtual ~Block_HardSoil(void);

	virtual void Update();
};

//ê∂ê¨ä÷êî
BlockBase* HardSoil_CreateBlock(void);

