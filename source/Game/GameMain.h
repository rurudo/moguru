#pragma once
#include "GameScene/GameScene.h"
class GameMain
{
private:
	GameScene* m_pGameScene;
	bool		m_Pause;
	float		m_FPS;			// �P�b�ӂ�̃t���[����
	int			m_TimeCount[61];// ���ԃJ�E���^
	int			m_FrameCount;	// �t���[���J�E���g
	int			m_ScreenBuffer;	// ��ʃo�b�t�@
	int			m_SkipFrame;	// �X�L�b�v����t���[����
	int			m_SkipRate;		// �X�L�b�v����t���[���]���l

public:
	GameMain();
	~GameMain();

	void Init(void);
	int Update(void);
	void Release(void);
};