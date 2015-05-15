#include "Task_CreateUnit.h"

TaskBase* CreateUnit_CreateTask(void)
{
	return new Task_CreateUnit();
}

Task_CreateUnit::Task_CreateUnit(void)
{
}

Task_CreateUnit::~Task_CreateUnit(void)
{
}

void Task_CreateUnit::Init(void)
{
	m_Position.x = 0.0f;
	m_Position.y = 0.0f;
	m_MovePoint.x = 0.0f;
	m_MovePoint.y = 0.0f;
	m_UnitID = UNIT_Treasure;
	m_Status = UnitBase::MovePoint;
}

void Task_CreateUnit::Update(UnitManager *unitManager, BlockManager *blockManager)
{
	unitManager->Add( m_Position, m_MovePoint, m_UnitID, m_Status );
	m_Exist = false;
}