#include "Task_DrawEffect.h"
#include "../System/BlockManager.h"

TaskBase* DrawEffect_CreateTask(void)
{
	return new Task_DrawEffect();
}

Task_DrawEffect::Task_DrawEffect(void)
{
}

Task_DrawEffect::~Task_DrawEffect(void)
{
}

void Task_DrawEffect::Init(void)
{
	for(int i = 0; i < HANDLE_MAX; i++)
	{
		m_Handle[i] = 0;
		m_ChangeTime[i] = 0;
	}
	m_Time = 0;
	m_NumData = 0;
	m_Position.x = 0.0f;
	m_Position.y = 0.0f;
	m_Velocity.x = 0.0f;
	m_Velocity.y = 0.0f;
	m_Rotation = 0.0f;
	m_Size = 1.0f;
	m_AddSize = 1.0f;
	m_AutoSlide = false;
}

void Task_DrawEffect::Update(UnitManager *unitManager, BlockManager *blockManager)
{
	m_Position.x += m_Velocity.x;
	m_Position.y += m_Velocity.y - BlockManager::GetInstance().GetOneFrameDepth();
	m_Time++;
	m_Size *= m_AddSize;
	int sumTime = 0;
	for(int i = 0; i < m_NumData; i++)
	{
		sumTime += m_ChangeTime[i];
	}
	// アニメーションが終了したらタスクを消す
	if(m_Time > sumTime)
	{
		m_Exist = false;
	}
}

void Task_DrawEffect::Draw(void)
{
	int sumTime = 0;
	for(int i = 0; i < m_NumData; i++)
	{
		sumTime += m_ChangeTime[i];
		if(m_Time < sumTime)
		{
			if( m_AutoSlide )
			{
				float x, y;
				DXLibMath::ConvertBlockToScreen( m_Position.x, m_Position.y, &x, &y );
				DXLibMath::DrawRotaGraphResize( x, y, m_Size, m_Rotation, m_Handle[i], TRUE);
			}
			else
			{
				DXLibMath::DrawRotaGraphResize( m_Position.x, m_Position.y, m_Size, m_Rotation,
					m_Handle[i], TRUE);
			}
			return;
		}
	}
}

void Task_DrawEffect::Add(int handle, int time)
{
	m_Handle[ m_NumData ] = handle;
	m_ChangeTime[ m_NumData ] = time;
	m_NumData++;
}

void Task_DrawEffect::SetPosition(float x, float y)
{
	m_Position.x = x;
	m_Position.y = y;
}

void Task_DrawEffect::SetVelocity(float x, float y)
{
	m_Velocity.x = x;
	m_Velocity.y = y;
}

void Task_DrawEffect::SetRotation(float rot)
{
	m_Rotation = rot;
}

void Task_DrawEffect::SetSize(float size)
{
	m_Size = size;
}

void Task_DrawEffect::SetAddSize(float size)
{
	m_AddSize = size;
}

void Task_DrawEffect::SetAutoSlide(bool flag)
{
	m_AutoSlide = flag;
}