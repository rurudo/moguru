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
	// プライベートコンストラクタ
	TaskManager(void);
	// 他マネージャーのポインタ
	BlockManager *m_BlockManager;
	UnitManager *m_UnitManager;
	// メモリマップデータ
	static const int TASK_ID_OFFSET = 1000;
	std::map<int, TaskBase*> m_TaskContainer;
	// 優先度リスト
	// 優先度の高いものから先に実行する
	static const int TASK_PRIORITY_MAX = 5;
	std::list<TaskBase*> m_PriorityList[ TASK_PRIORITY_MAX ];

public:
	~TaskManager(void);
	void Update(void);
	// タスクを生成
	TaskBase* CreateTask(int id);
	// タスクを登録
	void Add(TaskBase *task, int priority);
	// 描画タスクを実行
	void Draw(void);
	// 他マネージャーと接続する
	void Connect(BlockManager *blockManager, UnitManager *unitManager);
	// 登録中のタスクを全部消す
	void Clear(void);
	// メモリを開放する
	void Release(void);
	//インスタンス取得
	static TaskManager& GetInstance(void)
	{
		static TaskManager taskManager;
		return taskManager;
	}
};

