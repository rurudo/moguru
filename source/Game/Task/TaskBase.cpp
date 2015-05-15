#include "TaskBase.h"


TaskBase::TaskBase(void)
{
	m_Exist = false;
	m_ID = 0;
}


TaskBase::~TaskBase(void)
{
}

bool TaskBase::IsExist(void)
{
	return m_Exist;
}

void TaskBase::SetExist(bool flag)
{
	m_Exist = flag;
}

void TaskBase::SetID(int id)
{
	m_ID = id;
}

int TaskBase::GetID( void )
{
	return m_ID;
}

void TaskBase::Update(UnitManager *unitManager, BlockManager *blockManager)
{
}

void TaskBase::Draw(void)
{
}