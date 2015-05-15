#pragma once
#include "TaskBase.h"
class Task_CreateUnit :
	public TaskBase
{
public:
	VECTOR m_Position;				// �o�����W
	VECTOR m_MovePoint;				// �ړ���
	int m_UnitID;					// �o�����j�b�g��ID
	UnitBase::MoveStatus m_Status;	// �X�e�[�^�X

	Task_CreateUnit(void);
	virtual ~Task_CreateUnit(void);
	virtual void Init(void);
	virtual void Update(UnitManager *unitManager, BlockManager *blockManager);
};

TaskBase* CreateUnit_CreateTask(void);