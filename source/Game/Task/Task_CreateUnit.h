#pragma once
#include "TaskBase.h"
class Task_CreateUnit :
	public TaskBase
{
public:
	VECTOR m_Position;				// 出現座標
	VECTOR m_MovePoint;				// 移動先
	int m_UnitID;					// 出すユニットのID
	UnitBase::MoveStatus m_Status;	// ステータス

	Task_CreateUnit(void);
	virtual ~Task_CreateUnit(void);
	virtual void Init(void);
	virtual void Update(UnitManager *unitManager, BlockManager *blockManager);
};

TaskBase* CreateUnit_CreateTask(void);