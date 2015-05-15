#pragma once
#include "../System/UnitManager.h"
#include "../System/BlockManager.h"

class TaskBase
{
protected:
	bool m_Exist;
	int m_ID;
public:
	TaskBase(void);
	virtual ~TaskBase(void);
	virtual void Init(void) = 0;
	virtual void Update(UnitManager *unitManager, BlockManager *blockManager) = 0;
	virtual void Draw(void);

	bool IsExist(void);
	void SetExist(bool flag);
	void SetID(int id);
	int GetID( void );
};

