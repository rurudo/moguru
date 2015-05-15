#include "TaskManager.h"

TaskManager::TaskManager(void)
{
}

TaskManager::~TaskManager(void)
{
}

void TaskManager::Connect(BlockManager *blockManager, UnitManager *unitManager)
{
	m_BlockManager = blockManager;
	m_UnitManager = unitManager;
}

void TaskManager::Update(void)
{
	for(int i = TASK_PRIORITY_MAX - 1; i >= 0; i--)
	{
		for(std::list<TaskBase*>::iterator j = m_PriorityList[i].begin();
			j != m_PriorityList[i].end();)
		{
			TaskBase *task = (*j);
			task->Update(m_UnitManager, m_BlockManager);
			if( task->IsExist() )
			{
				j++;
			}
			else
			{
				j = m_PriorityList[i].erase(j);
			}
		}
	}
}

void TaskManager::Draw(void)
{
	for(int i = TASK_PRIORITY_MAX - 1; i >= 0; i--)
	{
		for(std::list<TaskBase*>::iterator j = m_PriorityList[i].begin();
			j != m_PriorityList[i].end(); j++)
		{
			TaskBase *task = (*j);
			task->Draw();
		}
	}
}

TaskBase* TaskManager::CreateTask(int id)
{
	TaskBase *base = NULL;
	for(int i = 0; i < TASK_ID_OFFSET; i++)
	{
		base = m_TaskContainer[id * TASK_ID_OFFSET + i ];
		if( base == NULL)
		{
			base = sp_CreateTaskTable[id]();
			m_TaskContainer[id * TASK_ID_OFFSET + i] = base;
			base->SetID( id );
			break;
		}
		else if( !base->IsExist() )
		{
			break;
		}
	}
	base->Init();
	base->SetExist( true );
	return base;
}

void TaskManager::Add(TaskBase *task, int priority)
{
	m_PriorityList[priority].push_back(task);
}

void TaskManager::Clear(void)
{
	for(int i = 0; i < TASK_PRIORITY_MAX; i++)
	{
		m_PriorityList[i].clear();
	}
}

void TaskManager::Release(void)
{
	for(int i = 0; i < TASK_PRIORITY_MAX; i++)
	{
		m_PriorityList[i].clear();
	}
	for(std::map<int, TaskBase*>::iterator it = m_TaskContainer.begin(); it != m_TaskContainer.end(); it++)
	{
		TaskBase *base = it->second;
		if(base != NULL)
		{
			delete base;
		}
	}
	m_TaskContainer.clear();
}