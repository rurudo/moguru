#define ___TASK_CREATE_MAIN___

#include "Task_DrawEffect.h"
#include "Task_CreateUnit.h"
#include "Task_Bullet.h"
#include "Task_AreaDamage.h"
#include "CreateTask.h"

CreateTaskTable sp_CreateTaskTable[TASK_TYPE_NUM]	= 
{
	0,
	DrawEffect_CreateTask,
	CreateUnit_CreateTask,
	Bullet_CreateTask,
	AreaDamage_CreateTask,
};