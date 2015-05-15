//========================================================================
//	@file	MixTreeData.h
//	@brief	合成物ツリーデータ
//========================================================================
#pragma once
#include "MenuStruct.h"
#include "../System/DataManager.h"

//タイプ
enum Type
{
	None=-1,										//ない時
	Equipment,										//装備
	Unit,											//ユニット
};

typedef struct{
	TreeData		main;
	TreeData		Material[4];
}MixTreeData;

static const char	N = -1;							//ない時の数値
static const char	cm_MixTreeNum	= 36;			//合成ツリー数

//N,N,N,GameMenu::None

//合成リスト
static const MixTreeData m_MixTreeData[cm_MixTreeNum] = 
{
	//成果物ステータス(ID,Type):必要素材1,必要素材2,必要素材3,必要素材4
	//{{{id.x,id.y,id.z},type},{{{id.x,id.y,id.z},type},{{id.x,id.y,id.z},type},{{id.x,id.y,id.z},type}}}
	{ 10,	Unit		,  1,Equipment	,  3,Equipment	,  N,None		,  N,None		},		// 0鎧モグラ				:ユニット
	{ 11,	Unit		, 10,Unit		,  0,Unit		,  N,None		,  N,None		},		// 1鎧トレジャー			:ユニット
	{  2,	Unit		,  5,Equipment	, 23,Equipment	,  N,None		,  N,None		},		// 2炎モグラ				:ユニット
	{ 14,	Unit		,  7,Equipment	, 35,Equipment	,  N,None		,  N,None		},		// 3モグラソルジャー		:ユニット
	{  8,	Unit		, 30,Equipment	, 43,Equipment	,  N,None		,  N,None		},		// 4ドロドロ				:ユニット
	{  9,	Unit		,  2,Equipment	, 50,Equipment	,  N,None		,  N,None		},		// 5フローちゃん			:ユニット
	{ 24,	Equipment	,  1,Unit		, 27,Equipment	,  N,None		,  N,None		},		// 6混乱玉				:装備
	{ 21,	Equipment	, 31,Equipment	,  8,Equipment	,  N,None		,  N,None		},		// 7ビリリ玉				:装備
	{ 25,	Unit		, 24,Unit		, 15,Equipment	,  N,None		,  N,None		},		// 8ティラノ				:ユニット
	{ 27,	Unit		, 26,Unit		, 20,Equipment	,  N,None		,  N,None		},		// 9クラーケン			:ユニット
	{ 28,	Unit		, 41,Equipment	, 33,Equipment	,  N,None		,  N,None		},		// 10クロックラビット		:ユニット
	{ 18,	Unit		, 14,Unit		, 21,Equipment	,  N,None		,  N,None		},		// 11忍者					:ユニット
	{ 26,	Unit		,  8,Unit		,  1,Equipment	,  N,None		,  N,None		},		// 12スライム				:ユニット
	{ 49,	Equipment	, 18,Unit		, 57,Equipment	,  N,None		,  N,None		},		// 13全滅勲章				:装備
	{ 12,	Unit		, 10,Unit		, 44,Equipment	, 47,Equipment	,  N,None		},		// 14デカモグラ			:ユニット
	{ 13,	Unit		, 13,Equipment	, 37,Equipment	, 11,Equipment	,  N,None		},		// 15スペースモグラ		:ユニット
	{ 24,	Unit		, 32,Equipment	, 11,Equipment	, 52,Equipment	,  N,None		},		// 16ホラーくん			:ユニット
	{  6,	Unit		,  2,Unit		, 55,Equipment	, 14,Equipment	,  N,None		},		// 17サラマンダー			:ユニット
	{ 57,	Equipment	,  2,Unit		, 40,Equipment	, 25,Equipment	,  N,None		},		// 18炎上ボディ			:装備
	{ 58,	Equipment	, 57,Equipment	, 28,Equipment	, 15,Equipment	,  N,None		},		// 19人工太陽				:装備
	{  7,	Unit		, 14,Unit		,  5,Equipment	,  6,Equipment	,  N,None		},		// 20発掘モグラ			:ユニット
	{ 36,	Equipment	,  7,Unit		, 34,Equipment	, 46,Equipment	,  N,None		},		// 21発掘者シンボル		:装備
	{ 22,	Equipment	,  9,Unit		, 29,Equipment	, 28,Equipment	,  N,None		},		// 22氷玉					:装備
	{ 15,	Unit		,  8,Unit		, 22,Equipment	, 26,Equipment	,  N,None		},		// 23フローちゃんEX		:ユニット
	{ 56,	Equipment	,  8,Unit		, 48,Equipment	, 39,Equipment	,  N,None		},		// 24量子ワープ装置		:装備
	{ 15,	Equipment	, 24,Equipment	, 14,Equipment	, 31,Equipment	,  N,None		},		// 25帝王の心				:装備
	{ 19,	Unit		, 24,Equipment	, 54,Equipment	, 18,Equipment	,  N,None		},		// 26パンチモグラ			:ユニット
	{  3,	Unit		, 19,Unit		, 17,Equipment	, 19,Equipment	,  N,None		},		// 27爆弾モグラ			:ユニット
	{ 23,	Unit		, 22,Unit		, 45,Equipment	, 53,Equipment	,  N,None		},		// 28ガーディアン			:ユニット
	{  4,	Unit		, 12,Unit		,  0,Unit		,  9,Equipment	, 10,Equipment	},		// 29金モグラ				:ユニット
	{ 16,	Unit		,  7,Unit		, 16,Equipment	, 12,Equipment	, 45,Equipment	},		// 30地底王				:ユニット
	{ 17,	Unit		, 16,Unit		, 15,Unit		, 42,Equipment	, 15,Equipment	},		// 31ヘル					:ユニット
	{ 21,	Unit		,  3,Unit		, 40,Equipment	, 41,Equipment	, 51,Equipment	},		// 32ボムボム箱			:ユニット
	{ 22,	Unit		, 19,Unit		, 38,Equipment	, 34,Equipment	,  6,Equipment	},		// 33勇者モグラ			:ユニット
	{  5,	Unit		,  4,Unit		, 13,Unit		, 25,Equipment	,  0,Equipment	},		// 34ギャラクシーモグラ	:ユニット
	{ 20,	Unit		, 14,Unit		, 21,Equipment	, 19,Equipment	, 17,Equipment	}		// 35電気モグラ			:ユニット
};

//仮 装備イメージ
static const char EquipItemImageList[60] = 
{
	DataManager::EI_IMAGE_Gear,
	DataManager::EI_IMAGE_Gear,
	DataManager::EI_IMAGE_Gear,
	DataManager::EI_IMAGE_Iron,
	DataManager::EI_IMAGE_Iron,
	DataManager::EI_IMAGE_Drill,
	DataManager::EI_IMAGE_Gear,
	DataManager::EI_IMAGE_Circuit,
	DataManager::EI_IMAGE_Circuit,
	DataManager::EI_IMAGE_Circuit,
	
	DataManager::EI_IMAGE_Iron,
	DataManager::EI_IMAGE_Circuit,
	DataManager::EI_IMAGE_Gear,
	DataManager::EI_IMAGE_Iron,
	DataManager::EI_IMAGE_Circuit,
	DataManager::EI_IMAGE_Circuit,
	DataManager::EI_IMAGE_Drill,
	DataManager::EI_IMAGE_Sword,
	DataManager::EI_IMAGE_Iron,
	DataManager::EI_IMAGE_Sword,
	
	DataManager::EI_IMAGE_Orb,
	DataManager::EI_IMAGE_Orb,
	DataManager::EI_IMAGE_Orb,
	DataManager::EI_IMAGE_Orb,
	DataManager::EI_IMAGE_Orb,
	DataManager::EI_IMAGE_Iron,
	DataManager::EI_IMAGE_Orb,
	DataManager::EI_IMAGE_Gear,
	DataManager::EI_IMAGE_Gear,
	DataManager::EI_IMAGE_Gear,
	
	DataManager::EI_IMAGE_Orb,
	DataManager::EI_IMAGE_Circuit,
	DataManager::EI_IMAGE_Gear,
	DataManager::EI_IMAGE_Circuit,
	DataManager::EI_IMAGE_Drill,
	DataManager::EI_IMAGE_Circuit,
	DataManager::EI_IMAGE_Medal,
	DataManager::EI_IMAGE_Iron,
	DataManager::EI_IMAGE_Iron,
	DataManager::EI_IMAGE_Gear,
	
	DataManager::EI_IMAGE_Gear,
	DataManager::EI_IMAGE_Gear,
	DataManager::EI_IMAGE_Gear,
	DataManager::EI_IMAGE_Gear,
	DataManager::EI_IMAGE_Gear,
	DataManager::EI_IMAGE_Gear,
	DataManager::EI_IMAGE_Circuit,
	DataManager::EI_IMAGE_Gear,
	DataManager::EI_IMAGE_Gear,
	DataManager::EI_IMAGE_Medal,
	
	DataManager::EI_IMAGE_Circuit,
	DataManager::EI_IMAGE_Orb,
	DataManager::EI_IMAGE_Gear,
	DataManager::EI_IMAGE_Sword,
	DataManager::EI_IMAGE_Orb,
	DataManager::EI_IMAGE_Iron,
	DataManager::EI_IMAGE_Gear,
	DataManager::EI_IMAGE_Iron,
	DataManager::EI_IMAGE_Sword,
	DataManager::EI_IMAGE_Medal
};

//========================================================================
//	End of file
//========================================================================