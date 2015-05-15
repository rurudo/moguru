#pragma once
#include "GameScene.h"
#include "../System/CustomUserInterface.h"
#include "../System/BlockManager.h"
#include "../System/UnitManager.h"

#include "../Menu/GameMenu.h"
#include "../Menu/Help.h"
#include "../Play/DepthSelect.h"
#include "../Play/PlayUserInterface.h"
#include "../Play/GameOver.h"
#include "../Play/GameClear.h"
#include "../Play/TreasureEffect.h"
#include "../Play/AfterGetMapProduction.h"
#include "../Play/StageDig.h"
#include "../Block/BreakBlock.h"


//�Q�[���N���X
class GameScenePlay : public GameScene
{
private:
	// �f���̊K�w�\����
	struct PLANET_HIERARCHY{
		int		H_num;		// ���K�w���邩
		int		Hier[10];	// �K�w�����̊�_
	};
	// �f���f�[�^�i�[�p
	PLANET_HIERARCHY HIERARCHY[5];

	//�t���[���J�E���g
	int m_FrameCount;

	int m_DebugNowGetID;

	// ���j���[
	GameMenu *m_Menu;
	Help	  m_Help;
	UIDisplay m_UIDisplay;
	// �K�w�I��
	DepthSelect m_DepthSelect;
	// UI
	PlayUserInterface m_UserInterface;
	// �Q�[���I�[�o�[
	GameOver m_GameOver;
	// �Q�[���N���A
	GameClear m_GameClear;
	// �@�鏈������
	StageDig m_Dig;
	// ����Q�b�g�G�t�F�N�g
	TreasureEffect m_TreasureEffect;
	//
	AfterGetMapProduction m_AfterGetItem;

	BreakBlock m_BreakBlock;
	// Help���J���Ă��邩�̃t���O
	bool m_HelpFlg;
	// �E�o�E�B���h�E�̃t���O
	bool m_EscapeFlag;
	// ���^�C�~���O�p�ϐ�
	int m_SoundTime;

	void SetDebugData(void);
	// �������̃p�b�V�u���ʂ̏���
	void AutoSkill(void);
public:
	GameScenePlay(void);
	virtual ~GameScenePlay(void);
	virtual int Update(void);
	virtual void Draw(void);
	
	void Init(void);
	void Release(void);
};

//�����֐�
GameScene* GameScenePlay_CreateScene();