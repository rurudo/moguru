#pragma once
#include "BlockBase.h"
class Block_Mud :
	public BlockBase
{
public:
	Block_Mud(void);
	virtual ~Block_Mud(void);

	virtual void Update();
};

//�����֐�
BlockBase* Mud_CreateBlock(void);

