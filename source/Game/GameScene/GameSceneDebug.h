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
	// csv���o�C�i���ɕϊ�����
	void ConvertBinary(void);
	void BitmapToBinary(char *fileName);
};

//�����֐�
GameScene* GameSceneDebug_CreateScene();