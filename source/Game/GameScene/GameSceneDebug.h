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
	// csv‚ğƒoƒCƒiƒŠ‚É•ÏŠ·‚·‚é
	void ConvertBinary(void);
	void BitmapToBinary(char *fileName);
};

//¶¬ŠÖ”
GameScene* GameSceneDebug_CreateScene();