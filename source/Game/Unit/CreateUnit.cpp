#define ___UNIT_CREATE_MAIN___

#include "Unit_Treasure.h"
#include "Unit_SmallMog.h"
#include "Unit_FireMog.h"
#include "Unit_BombMog.h"
#include "Unit_GoldenMog.h"
#include "Unit_GalaxyMog.h"
#include "Unit_Salamander.h"
#include "Unit_Dig.h"
#include "Unit_Mud.h"
// 10
#include "Unit_Frozen.h"
#include "Unit_Metal.h"
#include "Unit_MetalTreasure.h"
#include "Unit_BigMog.h"
#include "Unit_SpaceMog.h"
#include "Unit_BattleMog.h"
#include "Unit_FrozenEX.h"
#include "Unit_King.h"
#include "Unit_Hell.h"
#include "Unit_Ninja.h"
// 20
#include "Unit_Punch.h"
#include "Unit_Thunder.h"
#include "Unit_BombBox.h"
#include "Unit_HeroMog.h"
#include "Unit_Guardian.h"
#include "Unit_Zombie.h"
#include "Unit_Tyranno.h"
#include "Unit_Slime.h"
#include "Unit_Cuttlefish.h"
#include "Unit_ClockRabbit.h"
#include "Unit_Chop.h"
#include "Unit_TreasureBox.h"
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
	// 10
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
	// 20
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
	UNIT_TreasureBox,
	UNIT_NUM	// いつも最後
};

typedef UnitBase* (*CreateUnitTable)(void);

CreateUnitTable sp_CreateUnitTable[UNIT_NUM] = 
{
	0,
	Treasure_CreateUnit,
	SmallMog_CreateUnit,
	FireMog_CreateUnit,
	BombMog_CreateUnit,
	GoldenMog_CreateUnit,
	GalaxyMog_CreateUnit,
	Salamander_CreateUnit,
	Dig_CreateUnit,
	Mud_CreateUnit,
	// 10
	Frozen_CreateUnit,
	Metal_CreateUnit,
	MetalTreasure_CreateUnit,
	BigMog_CreateUnit,
	SpaceMog_CreateUnit,
	BattleMog_CreateUnit,
	FrozenEX_CreateUnit,
	King_CreateUnit,
	Hell_CreateUnit,
	Ninja_CreateUnit,
	// 20
	Punch_CreateUnit,
	Thunder_CreateUnit,
	BombBox_CreateUnit,
	HeroMog_CreateUnit,
	Guardian_CreateUnit,
	Zombie_CreateUnit,
	Tyranno_CreateUnit,
	Slime_CreateUnit,
	Cuttlefish_CreateUnit,
	ClockRabbit_CreateUnit,
	Chop_CreateUnit,
	TreasureBox_CreateUnit
};

