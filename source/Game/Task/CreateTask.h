#pragma once
#include "TaskBase.h"

enum TASK_TYPE
{
	TASK_TYPE_NONE,
	TASK_TYPE_DRAW_EFFECT,	// �G�t�F�N�g��\������
	TASK_TYPE_CREATE_UNIT,	// ���j�b�g�𐶐�����
	TASK_TYPE_BULLET,		// �U�����s��
	TASK_TYPE_AREA_DAMAGE,	// �͈͍U�����s��
	TASK_TYPE_NUM	// �����Ō�
};
typedef TaskBase* (*CreateTaskTable)(void);

#ifndef ___TASK_CREATE_MAIN___
extern CreateTaskTable sp_CreateTaskTable[TASK_TYPE_NUM];
#endif