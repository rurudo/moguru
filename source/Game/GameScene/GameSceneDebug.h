#pragma once
#include "GameScene.h"
#include "DxLib.h"
#include "../System/FontManager.h"
class GameSceneDebug : public GameScene
{
private:
	FontManager m_FontManager;
public:
	GameSceneDebug(void);
	virtual ~GameSceneDebug(void);
	virtual int Update(void);
	virtual void Draw(void);
	// csvをバイナリに変換する
	void ConvertBinary(void);
	void BitmapToBinary(char *fileName);
};

//生成関数
GameScene* GameSceneDebug_CreateScene();