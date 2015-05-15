/*
 * 基本的な動作はDrawEffectと同じ
 * 違いはバレットクラスにはユニットとの当たり判定と衝突した時の効果を記述する
 */

#pragma once
#include "TaskBase.h"
#include "../System/DxLibMath.h"
#include "../Unit/UnitBase.h"

class Task_Bullet :
	public TaskBase
{
private:
	static const int HANDLE_MAX = 16;	// 登録できる画像数

	int m_Handle[ HANDLE_MAX ];			// 描画するハンドル
	int m_ChangeTime[ HANDLE_MAX ];		// 画像が変わるタイミング
	int m_AnimTime;						// 現在時間
	int m_NumData;						// データ総数
	VECTOR m_Position;					// 表示位置
	VECTOR m_Velocity;					// 移動量
	float m_Rotation;					// 回転量
	float m_Size;						// 表示倍率
	float m_AddSize;					// 増加サイズ
	bool m_AutoSlide;					// 画面のスクロールに合わせるならtrue
	bool m_EnemyShot;					// 敵の攻撃かどうか
	int m_Damage;						// 攻撃の威力
	bool m_TargetEnemy;					// 敵に当たるか
	bool m_TargetBlock;					// ブロックに当たるか
	bool m_TargetMogll;					// モグルに当たるかどうか
	bool m_allFlag;						// 全てのユニットに当たるかどうか
	int m_LifeTime;						// 生存時間
	int m_DamageType;					// 攻撃の種類
	VECTOR m_DamageData;				// 攻撃タイプの付属データ
	int m_PowerCount;					// 発射されてからカウント。攻撃レート

	UnitBase *m_enemy;					// 攻撃元のアドレス
	TaskBase *m_task;					// 弾ヒット時に実行するタスク
	void PlayTask();					// タスクを実行する
public:
	Task_Bullet(void);
	virtual ~Task_Bullet(void);
	virtual void Init(void);
	virtual void Update(UnitManager *unitManager, BlockManager *blockManager);
	virtual void Draw(void);
	// アニメーションの描画定義
	void Add(int handle, int time);
	// 位置設定
	void SetPosition(float x, float y);
	void SetVelocity(float x, float y);
	void SetRotation(float rot);
	void SetSize(float size);
	void SetAddSize(float size);
	void SetAutoSlide(bool flag);
	void SetIsEnemy(bool flag);
	void SetDamage(int damage);
	void SetEnemyHit(bool flag);
	void SetBlockHit(bool flag);
	void SetMogllHit(bool flag);
	void SetLifeTime(int time);
	void SetAllFlag(bool flag);
	void SetDamageType( int type, const VECTOR &value, UnitBase *enemy);
	// 入力されたデータに装備補正をかける
	void EquipmentConvert( void );
	void SetTask( TaskBase* task );
};

TaskBase* Bullet_CreateTask(void);