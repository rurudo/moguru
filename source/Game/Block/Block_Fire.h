#pragma once
#include "BlockBase.h"
class Block_Fire :
	public BlockBase
{
private:
	int m_FrameCount;
public:
	Block_Fire(void);
	virtual ~Block_Fire(void);

	void Init();
	virtual void Update();
};

//ê∂ê¨ä÷êî
BlockBase* Fire_CreateBlock(void);

