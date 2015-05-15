#pragma once
#include "DxLib.h"
enum GameSceneID
{
	GAME_SCENE_TITLE,
	GAME_SCENE_STAGESELECT,
	GAME_SCENE_PLAY,
	GAME_SCENE_DEBUG,
	GAME_SCENE_THIS,
};

class GameScene
{
private:
	int m_States;
public:
	GameScene(void);
	virtual ~GameScene(void);
	virtual int Update(void) = 0;
	virtual void Draw(void) = 0;
};
