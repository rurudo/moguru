#pragma once
#include "DxLib.h"

class UnitBase
{
public:
	enum DamageType
	{
		// y:ダメージ量
		DAMAGETYPE_FIRE,			// 燃焼
		// y:低下倍率
		DAMAGETYPE_SLOW,			// スロウ
		DAMAGETYPE_STOP,			// 凍結
		DAMAGETYPE_PARALYSIS,		// 麻痺
		// y:倍率
		DAMAGETYPE_RANG,			// レンジ
		DAMAGETYPE_CONFUSION,		// 混乱
		// y:倍率
		DAMAGETYPE_ATTACKSPEED,		// 攻撃速度
		// yz: 移動量
		DAMAGETYPE_MOVE,			// ノックバック
		DAMAGETYPE_MAX,				// 状態異常の最大値

		DAMAGETYPE_NORMAL,			// 通常
		DAMAGETYPE_LIFESTEAL,		// ドレイン
		DAMAGETYPE_BLOCK			// ブロック効果
	};
protected:
	// 情報
	float m_nextX, m_nextY;		// 移動先
	bool m_Exist;
	bool m_AttackEnable;		// 攻撃可能フラグ
	float m_AtackCount;			// 攻撃頻度カウント
	VECTOR m_Facing;			// 向き
	int m_AnimTime;				// アニメーション時間
public:
	int m_TreasureID;			// 所持している宝
	UnitBase *m_DamageSrc;		// 攻撃元
	VECTOR m_BadStatus[DAMAGETYPE_MAX];		// 付属変数(x: 効果時間, yz:自由)
	int	m_ID;					// ユニットID
	float m_x, m_y;
	// ステータス
	int m_MaxLife;
	int m_Life;
	float m_Speed;
	float m_AttackSpeed;
	float m_Rang;
	int m_Power;
	// 移動方法の状態
	enum MoveStatus
	{
		MovePoint,	// 命令地点に移動中
		Free,		// 自由行動中
		Enemy		// このユニットは敵
	}m_MoveStatus;
	UnitBase(void);
	virtual ~UnitBase(void);
	virtual void Update();
	virtual void Draw();
	virtual void DrawAlpha();
	virtual void Init();
	virtual void Release();
	// 状態異常の処理を更新
	void BadStatusUpdate(void);
	// 初期ステータスをセット
	void SetStatus(void);

	virtual void AddDamage( int damage, int type, const VECTOR &value, UnitBase *enemy);

	void SetPosition(float x, float y);
	void AddPosition(float x, float y);
	void SetTargetPosition(float x, float y);
	bool IsExist(void);
	void SetExist(bool flag);
	int GetMaxLife( void );
	bool GetStopFlag( void );
	void SetTreasureID( int id );
};

