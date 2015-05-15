#pragma once
#include "TaskBase.h"

enum TASK_TYPE
{
	TASK_TYPE_NONE,
	TASK_TYPE_DRAW_EFFECT,	// エフェクトを表示する
	TASK_TYPE_CREATE_UNIT,	// ユニットを生成する
	TASK_TYPE_BULLET,		// 攻撃を行う
	TASK_TYPE_AREA_DAMAGE,	// 範囲攻撃を行う
	TASK_TYPE_NUM	// いつも最後
};
typedef TaskBase* (*CreateTaskTable)(void);

#ifndef ___TASK_CREATE_MAIN___
extern CreateTaskTable sp_CreateTaskTable[TASK_TYPE_NUM];
#endif