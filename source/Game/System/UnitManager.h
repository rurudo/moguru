#pragma once
#include "DxLibMath.h"
#include "../Unit/CreateUnit.h"
#include <list>
#include <map>
class UnitManager
{
private:
	static const int UNIT_ID_OFFSET = 1000;
	std::list<UnitBase*> m_ActiveList;			// 描画中敵リスト
	std::map<int, UnitBase*> m_UnitContainer;	// メモリの管理マップ
	std::list<UnitBase*> m_ReturnBuffer;		// 検索結果を返すためのバッファ

	UnitBase* CreateUnit(int id);
	// プライベートコンストラクタ
	UnitManager(void);
public:
	~UnitManager(void);
	// ユニットを生成する
	void Add(const VECTOR &position, const VECTOR &target, int type, UnitBase::MoveStatus moveType);
	void AddTreasureUnit(const VECTOR &position, const VECTOR &target, int type, UnitBase::MoveStatus moveType, int treasureID);
	// 宝箱を生成する
	void AddTreasureBox(const VECTOR &position, int treasureID);
	void Update(void);
	void Draw(void);
	// 保持していた領域を開放
	void Release(void);
	// 指定値だけ全ユニットが上に移動する(画面座標系）
	void MoveUp(float depth);
	// 指定範囲内で一番近いユニットを返す。いなければNULL
	UnitBase* GetNearUnit(const VECTOR &position, float r, bool searchEnemy, bool allFlag = false, UnitBase* self = NULL);
	// 指定範囲内にガーディアンがいればヒットする
	UnitBase* GetNearGuardian( float x, float y, float r, bool searchEnemy);
	// 指定範囲内のユニットを返す
	std::list<UnitBase*>& GetAreaUnit(float x, float y, float r);
	std::list<UnitBase*>& GetAll( void );
	//インスタンス取得
	static UnitManager& GetInstance(void)
	{
		static UnitManager unitManager;
		return unitManager;
	}
};

