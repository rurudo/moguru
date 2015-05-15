#pragma once
#include <stdio.h>
#include "GameScene.h"
#include "GameSceneTitle.h"
#include "GameSceneStageSelect.h"
#include "GameScenePlay.h"
#include "GameSceneDebug.h"

static const int SCENE_NUM = 4;
typedef GameScene* (*CreateTable)(void);

static CreateTable sp_CreateTable[SCENE_NUM]	= 
{
	GameSceneTitle_CreateScene,
	GameSceneStageSelect_CreateScene,
	GameScenePlay_CreateScene,
	GameSceneDebug_CreateScene,
};