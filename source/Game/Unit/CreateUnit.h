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
	UNIT_Metal,			// �Z���O��
	UNIT_MetalTreasure,	// �Z�g���W���[
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
	UNIT_HeroMog,	// �E�҃��O��
	UNIT_Guardian,
	UNIT_Zombie,
	UNIT_Tyranno,	// �e�B���m
	UNIT_Slime,
	UNIT_Cuttlefish,	// �C�J
	UNIT_ClockRabbit,
	UNIT_Chop,
	UNIT_TreasureBox,	// ��
	UNIT_NUM	// �����Ō�
};

typedef UnitBase* (*CreateUnitTable)(void);

#ifndef ___UNIT_CREATE_MAIN___
extern CreateUnitTable sp_CreateUnitTable[UNIT_NUM];
#endif