#pragma once
#include "BlockBase.h"
class Block_Alarm :
	public BlockBase
{
public:
	Block_Alarm(void);
	virtual ~Block_Alarm(void);
	virtual void Update();
	int GetHandle();
};

//�����֐�
BlockBase* Alarm_CreateBlock(void);

