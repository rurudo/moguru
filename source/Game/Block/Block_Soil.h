#pragma once
#include "BlockBase.h"
class Block_Soil :
	public BlockBase
{
public:
	Block_Soil(void);
	virtual ~Block_Soil(void);

	virtual void Update();
};

//ê∂ê¨ä÷êî
BlockBase* Soil_CreateBlock(void);

