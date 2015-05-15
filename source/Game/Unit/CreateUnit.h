#pragma once
#include "UnitBase.h"

enum UNIT_TYPE
{
	UNIT_NONE,
	UNIT_Treasure,
	UNIT_SmallMog,
	UNIT_FireMog,
	UNIT_BombMog,
	UNIT_GoldenMog,
	UNIT_GalaxyMog,
	UNIT_Salamander,
	UNIT_Dig,
	UNIT_Mud,
	UNIT_Frozen,
	UNIT_Metal,			// 鎧モグラ
	UNIT_MetalTreasure,	// 鎧トレジャー
	UNIT_BigMog,
	UNIT_SpaceMog,
	UNIT_BattleMog,
	UNIT_FrozenEX,
	UNIT_King,
	UNIT_Hell,
	UNIT_Ninja,
	UNIT_Punch,
	UNIT_Thunder,
	UNIT_BombBox,
	UNIT_HeroMog,	// 勇者モグラ
	UNIT_Guardian,
	UNIT_Zombie,
	UNIT_Tyranno,	// ティラノ
	UNIT_Slime,
	UNIT_Cuttlefish,	// イカ
	UNIT_ClockRabbit,
	UNIT_Chop,
	UNIT_TreasureBox,	// 宝箱
	UNIT_NUM	// いつも最後
};

typedef UnitBase* (*CreateUnitTable)(void);

#ifndef ___UNIT_CREATE_MAIN___
extern CreateUnitTable sp_CreateUnitTable[UNIT_NUM];
#endif