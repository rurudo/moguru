#pragma once
#include <list>
#include <map>
#include "DxLib.h"
#include "UnitManager.h"
#include "BlockManager.h"
#include "../Task/CreateTask.h"

class TaskManager
{
private:
	// �v���C�x�[�g�R���X�g���N�^
	TaskManager(void);
	// ���}�l�[�W���[�̃|�C���^
	BlockManager *m_BlockManager;
	UnitManager *m_UnitManager;
	// �������}�b�v�f�[�^
	static const int TASK_ID_OFFSET = 1000;
	std::map<int, TaskBase*> m_TaskContainer;
	// �D��x���X�g
	// �D��x�̍������̂����Ɏ��s����
	static const int TASK_PRIORITY_MAX = 5;
	std::list<TaskBase*> m_PriorityList[ TASK_PRIORITY_MAX ];

public:
	~TaskManager(void);
	void Update(void);
	// �^�X�N�𐶐�
	TaskBase* CreateTask(int id);
	// �^�X�N��o�^
	void Add(TaskBase *task, int priority);
	// �`��^�X�N�����s
	void Draw(void);
	// ���}�l�[�W���[�Ɛڑ�����
	void Connect(BlockManager *blockManager, UnitManager *unitManager);
	// �o�^���̃^�X�N��S������
	void Clear(void);
	// ���������J������
	void Release(void);
	//�C���X�^���X�擾
	static TaskManager& GetInstance(void)
	{
		static TaskManager taskManager;
		return taskManager;
	}
};

