#pragma once
#include "../Unit/UnitBase.h"
#include "../Task/TaskBase.h"
// 描画系
// 指定の座標に爆発アニメーションを行う
void TaskSet_DrawExplod(float x, float y);
// タスクだけくれるバージョン
TaskBase* TaskSet_DrawExplodTask(float x, float y);

// 処理系
// 指定の座標に指定のユニットの死亡演出を行う
void TaskSet_DeadCalc(float x, float y, UnitBase* base);
// 指定の座標に指定のIDブロックの破壊演出を行う
void TaskSet_BlockBreakCalc(float x, float y, int id, int enemyID, bool isEnemy);
// 指定の座標にブロックのマグマダメージ
void TaskSet_BlockFireDamage(float x, float y);

// ダメージ系
// 指定のポイントから半径rangeの範囲のブロックに指定のダメージ
void TaskSet_AreaBlockDamage(float x, float y, int damage, float range);
// 指定のポイントから半径rangeの範囲のユニットに指定のダメージ
void TaskSet_AreaUnitDamage(float x, float y, int damage, float range);
// 指定のポイントから半径rangeの範囲のユニットに指定の状態異常を与える
void TaskSet_AreaUnitBadStatus( float x, float y, int damage, float range, int type, const VECTOR &damageData );
// 敵や味方のみに当てることができる
void TaskSet_AreaUnitBadStatusFriend( float x, float y, int damage, float range, int type, const VECTOR &damageData, bool isEnemy);

void TaskSet_Shot(int power, int type, const VECTOR &damageData, float x, float y, float enemyX, float enemyY,
	bool isEnemy, bool blockHit, UnitBase* unit, bool enemyHit = true);

// 誘導
void TaskSet_AllTargetSet( float x, float y, UnitBase* unit);
void TaskSet_FriendTargetSet( float x, float y );
void TaskSet_FriendReact( float x, float y );

// 召喚
void TaskSet_CreateEnemy( float x, float y, int id );