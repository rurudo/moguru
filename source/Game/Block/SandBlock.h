#pragma once
#include "BlockBase.h"
class SandBlock :
	public BlockBase
{
public:
	SandBlock(void);
	virtual ~SandBlock(void);
	virtual void Update();
};

//�����֐�
BlockBase* SandBlock_CreateBlock(void);

