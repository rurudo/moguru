#define ___BLOCK_CREATE_MAIN___

#include "SandBlock.h"
#include "Block_Soil.h"
#include "Block_Stone.h"
#include "Block_Rock.h"
#include "Block_HardSoil.h"
#include "Block_Mud.h"
#include "Block_DeepMud.h"
#include "Block_Bomb.h"
#include "Block_Water.h"
#include "Block_Alarm.h"
#include "Block_Fire.h"
#include "Block_Confuse.h"
#include "Block_Drill.h"
#include "Block_EnemyIce.h"
//#include "CreateBlock.h"
enum BLOCK_TYPE
{
	BLOCK_NONE,
	BLOCK_SAND,
	BLOCK_SOIL,
	BLOCK_STONE,
	BLOCK_ROCK,
	BLOCK_OLDBONE,
	BLOCK_METAL,
	BLOCK_DIAMOND,
	BLOCK_MUD,
	BLOCK_DEEPMUD,
	// 10
	BLOCK_TREE,
	BLOCK_RESOURCE,
	BLOCK_BOMB,
	BLOCK_ALARM,
	BLOCK_WATER,
	BLOCK_WEAKICE,
	BLOCK_HARDICE,
	BLOCK_ENEMYICE,
	BLOCK_FIREROCK,
	BLOCK_FIRE,
	// 20
	BLOCK_CONFUSE,
	BLOCK_DRILL,
	BLOCK_DUMMY,
	BLOCK_HARDSOIL,
	BLOCK_NUM	// Ç¢Ç¬Ç‡ç≈å„
};
typedef BlockBase* (*CreateBlockTable)(void);

CreateBlockTable sp_CreateBlockTable[BLOCK_NUM]	= 
{
	0,
	SandBlock_CreateBlock,
	Soil_CreateBlock,
	Stone_CreateBlock,
	Rock_CreateBlock,
	HardSoil_CreateBlock,
	SandBlock_CreateBlock,
	SandBlock_CreateBlock,
	Mud_CreateBlock,
	DeepMud_CreateBlock,
	// 10
	SandBlock_CreateBlock,
	SandBlock_CreateBlock,
	Bomb_CreateBlock,
	Alarm_CreateBlock,
	Water_CreateBlock,
	SandBlock_CreateBlock,
	SandBlock_CreateBlock,
	EnemyIce_CreateBlock,
	Fire_CreateBlock,
	Fire_CreateBlock,
	// 20
	SandBlock_CreateBlock,
	Drill_CreateBlock,
	Alarm_CreateBlock,
	SandBlock_CreateBlock
};