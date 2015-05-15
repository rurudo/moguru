/*
 * 基本的な動作はDrawEffectと同じ
 * 違いはバレットクラスにはユニットとの当たり判定と衝突した時の効果を記述する
 */

#pragma once
#include "TaskBase.h"
#include "../System/DxLibMath.h"
#include "../Unit/UnitBase.h"

class Task_AreaDamage :
	public TaskBase
{
private:

	VECTOR m_Position;					// 表示位置
	bool m_EnemyShot;					// 敵の攻撃かどうか
	int m_Damage;						// 攻撃の威力
	bool m_TargetEnemy;					// 敵に当たるか
	bool m_TargetBlock;					// ブロックに当たるか
	bool m_TargetMogll;					// モグルに当たるかどうか
	bool m_allFlag;						// 全てのユニットに当たるかどうか
	int m_LifeTime;						// 生存時間
	int m_DamageType;					// 攻撃の種類
	VECTOR m_DamageData;				// 攻撃タイプの付属データ

	float m_AreaRange;					// 範囲攻撃のレンジ

	UnitBase *m_enemy;					// 攻撃元のアドレス
	TaskBase *m_task;					// 追加タスク
	void PlayTask(void);				// 登録されたタスクを実行する
public:
	Task_AreaDamage(void);
	virtual ~Task_AreaDamage(void);
	virtual void Init(void);
	virtual void Update(UnitManager *unitManager, BlockManager *blockManager);

	// 位置設定
	void SetPosition(float x, float y);
	void SetIsEnemy(bool flag);
	void SetDamage(int damage);
	void SetEnemyHit(bool flag);
	void SetBlockHit(bool flag);
	void SetMogllHit(bool flag);
	void SetLifeTime(int time);
	void SetAllFlag(bool flag);
	void SetDamageType( int type, const VECTOR &value, UnitBase *enemy);
	void SetRange(float range);
	void SetTask(TaskBase *task);
	// 入力されたデータに装備補正をかける
	void EquipmentConvert( void );
};

TaskBase* AreaDamage_CreateTask(void);