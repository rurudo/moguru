#pragma once
#include "CustomUserInterface.h"
#include "DxLibMath.h"
#include "../Block/CreateBlock.h"
#include "../Block/BreakBlock.h"
#include <map>
#include <list>
#include <vector>
// ブロック座標系とはブロック１つの長さを1.0fとした座標系
class BlockManager
{
public:
	static const int HEIGHT_NUM_BLOCK = 13;
private:
	static const int BLOCK_ID_OFFSET = 1000;
	static const int WIDTH_NUM_BLOCK = 15;
	VECTOR m_Position;		// UI設置位置
	VECTOR m_Size;			// UIサイズ
	VECTOR m_BlockSize;		// ブロック1つのサイズ
	int m_Depth;			// 深度
	int m_DepthOffset;		// ブロック表示基準位置
	float m_DepthFloat;		// 中途半端な深度(整数値以下の深度）
	float m_AddDepth;		// 深度更新分
	int m_TopLine;			// 現在のブロックリストの一番上のインデックス
	std::map<int, BlockBase*> m_BlockContainer;
	// リターン用のlist
	std::list<BlockBase*> m_ReturnBuffer;
	// 読み込むマップデータ格納位置
	struct MapHeader
	{
		int x, y;
	}m_MapHeader;
	char *m_MapData;
	// 敵のデータ読み込み先
	struct EnemyData
	{
		int x, y, id;
	};
	std::vector<EnemyData*> m_EnemyData;
	int m_EnemyCount;						// 出現させた敵の数

	CustomUserInterface m_MapUI;
	BreakBlock* m_pBreakBlock;
	BlockBase* m_BlockMap[ WIDTH_NUM_BLOCK ][ HEIGHT_NUM_BLOCK+1 ];
	// 指定したIDのブロックを割り当てる
	BlockBase* CreateBlock(int id);
	void LoadLineCalc(int num);
	void DrawBlockFrame(char *buf);
	// プライベートコンストラクタ
	BlockManager(void);
public:
	~BlockManager(void);
	// マップデータの読み込み
	void LoadBinary(char *fileName);
	void LoadGraphic(char *fileName);
	// 敵データの読み込み
	void LoadEnemyGraphic(char *fileName);
	// depthマスマップを読み進める
	void AddDepth(float depth);
	void Draw(void);
	void Update(void);
	void Init(void);
	void Release(void);
	// 指定範囲内のブロックを返す(ブロック座標系）
	std::list<BlockBase*>& GetAreaBlock(float x, float y, float r);
	// 指定点のブロックを返す（ブロック座標系）
	BlockBase* GetBlock(float x, float y);
	// 指定点から一番近いブロックを返す。半径rより近いブロックが無い時はNULLを返す(ブロック座標系）
	BlockBase* GetNearBlock(const VECTOR &position, float r);
	// 指定地点から一番近い通行不能なブロックを返す
	BlockBase* GetNearHardBlock(const VECTOR &position, float r);
	// 指定のブロックの画面座標を返す
	void ConvertScreen( BlockBase* block, float *x, float *y );
	// 指定ラインのデータを現在のカレントラインにロードする
	// 同時に一番古いラインをアンロードする
	// 指定のラインをロード
	void LoadLine(int num);
	// 次のラインをロード
	void LoadLine(void);
	// 現在の深度を返す
	float GetDepth(void);
	// このフレームで掘った深度を返す
	float GetOneFrameDepth(void);
	// 掘った深度int版
	int GetDepthOffset(void);
	// 指定の座標のお宝IDを返す。なければ-1, 対象が敵の場合enemy=1,ブロックの場合enemy=0
	int GetTreasureID( int x, int y, int *enemy );
	// 指定の座標の敵IDを返す。なければ-1
	int GetEnemyID( int x, int y );
	//インスタンス取得
	static BlockManager& GetInstance(void)
	{
		static BlockManager blockManager;
		return blockManager;
	}

	void SetBreakBlock(BreakBlock* pBreakBlock){
		m_pBreakBlock = pBreakBlock;
	}
};

