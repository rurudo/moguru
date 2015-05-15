#include "TaskFunction.h"
#include "../System/DataManager.h"

#include "../System/TaskManager.h"
#include "../Task/Task_DrawEffect.h"
#include "../Task/Task_Bullet.h"

#include "../System/EquipmentFunction.h"

TaskBase* TaskSet_DrawExplodTask(float x, float y)
{
	TaskManager &taskManager = TaskManager::GetInstance();
	Task_DrawEffect* task = dynamic_cast<Task_DrawEffect*>( taskManager.CreateTask(TASK_TYPE_DRAW_EFFECT) );
	task->SetAutoSlide( true );
	task->SetPosition( x, y );
	// エフェクトの画像と時間を指定
	DataManager &data = DataManager::GetInstance();
	task->Add( data.Get( DataManager::GraphicGroupExplodeAnim_1 ), 5);
	task->Add( data.Get( DataManager::GraphicGroupExplodeAnim_2 ), 5);
	task->Add( data.Get( DataManager::GraphicGroupExplodeAnim_3 ), 5);
	task->Add( data.Get( DataManager::GraphicGroupExplodeAnim_4 ), 5);
	task->Add( data.Get( DataManager::GraphicGroupExplodeAnim_5 ), 5);
	task->Add( data.Get( DataManager::GraphicGroupExplodeAnim_6 ), 5);
	task->Add( data.Get( DataManager::GraphicGroupExplodeAnim_7 ), 5);
	return task;
}

void TaskSet_DrawExplod(float x, float y)
{
	PlaySoundMem( DataManager::GetInstance().Get( DataManager::SoundSE48 ), DX_PLAYTYPE_BACK);
	TaskManager &taskManager = TaskManager::GetInstance();
	TaskBase* task = TaskSet_DrawExplodTask( x, y );
	// タスクマネージャにこのタスクを登録
	taskManager.Add( task, 0 );
}

void TaskSet_DeadCalc(float x, float y, UnitBase* base)
{
	TaskManager &taskManager = TaskManager::GetInstance();
	TaskBase* task = TaskSet_DrawExplodTask( x, y );
	// タスクマネージャにこのタスクを登録
	taskManager.Add( task, 0 );
	EquipmentFunction_41( base );		// 味方が爆発
	EquipmentFunction_52( base );		// 敵が爆発
	EquipmentFunction_53();				// 回復
	PlaySoundMem( DataManager::GetInstance().Get( DataManager::SoundSE48 ), DX_PLAYTYPE_BACK);
	// 宝生成
	if( base->m_TreasureID != -1 && base->m_MoveStatus == UnitBase::Enemy)
	{
		VECTOR position;
		position.x = base->m_x;
		position.y = base->m_y - BlockManager::GetInstance().GetDepth() - 0.3f;
		UnitManager::GetInstance().AddTreasureBox( position, base->m_TreasureID );
	}
}

void TaskSet_BlockBreakCalc(float x, float y, int id, int enemyID, bool isEnemy)
{
	DataManager& data = DataManager::GetInstance();
	int resource = data.m_SystemData.block[ id - 1].resource;
	if( resource == 0)
	{
		PlaySoundMem( data.Get( DataManager::SoundSE27 ), DX_PLAYTYPE_BACK);
	}
	else
	{
		PlaySoundMem( data.Get( DataManager::SoundSE25 ), DX_PLAYTYPE_BACK);
	}
	// 敵がブロックを壊した時は資源を与えない
	if( isEnemy )	return;
	int value = EquipmentFunction_07( resource );
	value = EquipmentFunction_47( value );
	if( enemyID == UNIT_King )
	{
		value = static_cast<int>( value * 1.5f );
	}
	data.m_MogllStatus.resource += value;
}

void TaskSet_BlockFireDamage(float x, float y)
{
	UnitManager &unitManager = UnitManager::GetInstance();
	std::list<UnitBase*> &unitList = unitManager.GetAreaUnit( x, y, 2.0f );
	int damage = 6;
	damage = EquipmentFunction_56( damage );
	for(std::list<UnitBase*>::iterator i = unitList.begin(); i != unitList.end(); i++)
	{
		VECTOR damageData;
		(*i)->AddDamage( damage, UnitBase::DAMAGETYPE_NORMAL, damageData, NULL);
	}
	DataManager &data = DataManager::GetInstance();
	VECTOR position;
	DXLibMath::ConvertScreenToBlock( data.m_MogllStatus.position.x, data.m_MogllStatus.position.y, &position.x, &position.y );
	position.x -= x;
	position.y -= y;
	if( DXLibMath::Length( position ) < 2.0f )
	{
		damage = EquipmentFunction_05( damage );
		data.m_MogllStatus.life -= damage;
	}
}

void TaskSet_AreaUnitDamage(float x, float y, int damage, float range)
{
	UnitManager &unitManager = UnitManager::GetInstance();
	std::list<UnitBase*> &unitList = unitManager.GetAreaUnit( x, y, range );
	for(std::list<UnitBase*>::iterator i = unitList.begin(); i != unitList.end(); i++)
	{
		VECTOR damageData;
		(*i)->AddDamage( damage, UnitBase::DAMAGETYPE_BLOCK, damageData, NULL);
	}
}

void TaskSet_AreaUnitBadStatus( float x, float y, int damage, float range, int type, const VECTOR &damageData )
{
	UnitManager &unitManager = UnitManager::GetInstance();
	std::list<UnitBase*> &unitList = unitManager.GetAreaUnit( x, y, range );
	for(std::list<UnitBase*>::iterator i = unitList.begin(); i != unitList.end(); i++)
	{
		(*i)->AddDamage( damage, type, damageData, NULL);
	}
}

void TaskSet_AreaUnitBadStatusFriend( float x, float y, int damage, float range, int type, const VECTOR &damageData, bool isEnemy)
{
	UnitManager &unitManager = UnitManager::GetInstance();
	std::list<UnitBase*> &unitList = unitManager.GetAreaUnit( x, y, range );
	for(std::list<UnitBase*>::iterator i = unitList.begin(); i != unitList.end(); i++)
	{
		if( ((*i)->m_MoveStatus == UnitBase::Enemy && !isEnemy) ||
			((*i)->m_MoveStatus != UnitBase::Enemy && isEnemy))
		{
			(*i)->AddDamage( damage, type, damageData, NULL);
		}
	}
}

void TaskSet_AreaBlockDamage(float x, float y, int damage, float range)
{
	BlockManager &blockManager = BlockManager::GetInstance();
	std::list<BlockBase*> &blockList = blockManager.GetAreaBlock( x, y, range );
	int cnt = 0;
	for(std::list<BlockBase*>::iterator i = blockList.begin(); i != blockList.end(); i++)
	{
		if( (*i)->m_ID != BLOCK_FIRE )
		{
			(*i)->AddDamage( damage, 0, true );
		}
	}
}

void TaskSet_Shot(int power, int type, const VECTOR &damageData, float x, float y, float enemyX, float enemyY,
	bool isEnemy, bool blockHit, UnitBase* unit, bool enemyHit)
{
	TaskManager &taskManager = TaskManager::GetInstance();
	Task_Bullet* task = dynamic_cast<Task_Bullet*>( taskManager.CreateTask(TASK_TYPE_BULLET) );
	task->SetPosition( x, y );
	// 射出方向の計算
	VECTOR target;
	// ティラノは無差別
	if( unit && unit->m_ID == UNIT_Tyranno )
	{
		task->SetAllFlag( true );
	}
	// 混乱中なら
	if( unit && unit->m_BadStatus[ UnitBase::DAMAGETYPE_CONFUSION ].x > 0.0f )
	{
		task->SetAllFlag( true );
		float rnd = 3.1415f / 180.0f * static_cast<float>(GetRand(360));
		target.x = cos(rnd);
		target.y = sin(rnd);
	}
	else
	{
		target.x = enemyX - x;
		target.y = enemyY - y;
	}
	DXLibMath::Normalize( &target, target );
	task->SetVelocity( target.x * 0.1f, target.y * 0.1f );
	task->SetBlockHit( blockHit );
	task->SetEnemyHit( enemyHit );

	task->SetDamage( power );
	task->SetIsEnemy( isEnemy );
	task->SetAutoSlide( true );					// これつけないとブロック座標系で計算してくれない
	// 攻撃の種類
	task->SetDamageType( type, damageData, unit);
	task->EquipmentConvert();
	// 発射するエフェクトの画像と時間を指定
	DataManager &data = DataManager::GetInstance();
	//task->SetSize( 0.2f );
	if( unit != NULL && unit->m_MoveStatus == UnitBase::Enemy )
	{
		task->Add( data.Get( DataManager::red_shot ), 60 );
	}
	else
	{
		task->Add( data.Get( DataManager::blue_shot ), 60 );
	}
	//task->Add( data.Get( DataManager::GG_BULLET_NORMAL01 ), 5 );
	//task->Add( data.Get( DataManager::GG_BULLET_NORMAL02 ), 5 );
	//task->Add( data.Get( DataManager::GG_BULLET_NORMAL03 ), 5 );
	//task->Add( data.Get( DataManager::GG_BULLET_NORMAL04 ), 5 );
	//task->Add( data.Get( DataManager::GG_BULLET_NORMAL05 ), 5 );
	//task->Add( data.Get( DataManager::GG_BULLET_NORMAL06 ), 5 );
	//task->Add( data.Get( DataManager::GG_BULLET_NORMAL07 ), 5 );
	//task->Add( data.Get( DataManager::GG_BULLET_NORMAL08 ), 5 );
	//task->Add( data.Get( DataManager::GG_BULLET_NORMAL09 ), 5 );
	//task->Add( data.Get( DataManager::GG_BULLET_NORMAL10 ), 5 );
	// タスクマネージャにこのタスクを登録
	taskManager.Add( task, 0 );
}


void TaskSet_AllTargetSet( float x, float y, UnitBase* unit )
{
	UnitManager &unitManager = UnitManager::GetInstance();
	std::list<UnitBase*> &unitList = unitManager.GetAreaUnit( x, y, 5.0f );
	for(std::list<UnitBase*>::iterator i = unitList.begin(); i != unitList.end(); i++)
	{
		// 自分自身と同じ種族はいじらない
		if( unit->m_ID == (*i)->m_ID ) continue;
		(*i)->SetTargetPosition( x, y );
	}
}

void TaskSet_FriendTargetSet( float x, float y)
{
	UnitManager &unitManager = UnitManager::GetInstance();
	std::list<UnitBase*> &unitList = unitManager.GetAll();
	for(std::list<UnitBase*>::iterator i = unitList.begin(); i != unitList.end(); i++)
	{
		// 味方のみ
		if( (*i)->m_MoveStatus == UnitBase::Enemy ) continue;
		(*i)->SetTargetPosition( x, y );
	}
}

void TaskSet_FriendReact( float x, float y)
{
	UnitManager &unitManager = UnitManager::GetInstance();
	std::list<UnitBase*> &unitList = unitManager.GetAll();
	for(std::list<UnitBase*>::iterator i = unitList.begin(); i != unitList.end(); i++)
	{
		// 味方のみ
		if( (*i)->m_MoveStatus != UnitBase::Free ) continue;
		(*i)->SetTargetPosition( x, y );
		(*i)->m_MoveStatus = UnitBase::MovePoint;
	}
}


void TaskSet_CreateEnemy( float x, float y, int id )
{
	UnitManager &unitManager = UnitManager::GetInstance();
	VECTOR position;
	position.x = x;
	position.y = y;
	VECTOR mogllPos;		// モグルの座標
	// モグルの座標が画面座標なので変換
	DataManager &data = DataManager::GetInstance();
	DXLibMath::ConvertScreenToBlock( data.m_MogllStatus.position.x, data.m_MogllStatus.position.y, &mogllPos.x, &mogllPos.y );
	unitManager.Add( position, mogllPos, id, UnitBase::Enemy );
}