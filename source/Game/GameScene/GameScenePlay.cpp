#include "GameScenePlay.h"
#include "../System/GameInput.h"
#include "../System/DataManager.h"
#include "../System/DxLibMath.h"
#include "../System/TaskManager.h"
#include "../System/EquipmentFunction.h"
#include "../Menu/MenuIconSort.h"

//====================================================
// �����֐�
GameScene* GameScenePlay_CreateScene()
{
	return new GameScenePlay();
}

//====================================================
// �N���X���\�b�h
GameScenePlay :: GameScenePlay(void)
{
	Init();
}
GameScenePlay :: ~GameScenePlay(void)
{
	Release();
}

//------------------------
// �Q�[���̏���������
void GameScenePlay :: Init(void)
{
	m_DebugNowGetID = 0;
	DataManager& data = DataManager::GetInstance();
	//data.Load(DataManager::ResourceSetPlay);
	data.m_MogllStatus.life = 1000;
	data.m_MogllStatus.maxLife = 1000;
	data.m_MogllStatus.maxResource = 1000;
	data.m_MogllStatus.resource = 500;
	data.m_MogllStatus.treasureStatus = -1;
	data.m_MogllStatus.noHitTime = 0;
	// �f�[�^�̏�����
	data.Load( DataManager::ResourceSetPlay );
	m_DepthSelect.Init();
	m_GameOver.Init();
	m_GameClear.Init();
	m_Help.Init();
	m_SoundTime = 0;
	m_HelpFlg = false;
	m_EscapeFlag = false;
	for( int i = 0; i < 3; i++)
	{
		data.m_MogllStatus.equipStatus[i] = 0;
	}
	for(int i = 0; i < 30; i++)
	{
		data.m_MogllStatus.unitCount[i] = 99;
	}

	// �f���̊K�w�����f�[�^
	const PLANET_HIERARCHY hierarchy[5] =
	{	{9, 120, 240, 372, 492,  600, 744, 864, 996, 1080,  600},		// �n���s�s
		{4, 120, 240, 420, 600,  600, 120, 240, 360, 480,  600},		// �X��
		{5, 120, 240, 360, 480,  600, 120, 240, 360, 480,  600},		// ���n
		{5, 100, 200, 300, 400,  500, 100, 200, 300, 400,  500},		// �ΎR
		{5, 120, 240, 360, 480,  600, 120, 240, 360, 480,  600}};	// �ߖ���

	// �f���̊K�w�����f�[�^����
	for(int i = 0; i < 5; i++)
	{
		HIERARCHY[i] = hierarchy[i];
	}

	//���j���[�N���X�̃C���X�^���X�̍쐬
	m_Menu = new GameMenu;
	// �u���b�N�}�l�[�W���[�̃f�[�^�ǂݍ���
	BlockManager &BM = BlockManager::GetInstance();
	BM.Init();
	switch( data.m_SceneInt["StageNo"] )
	{
	case 1:
		BM.LoadGraphic("resource/texture/Map/STAGE_2.bmp");
		BM.LoadEnemyGraphic("resource/texture/Map/ENEMY_2.bmp");
		if(CheckSoundMem(data.Get( DataManager::SoundBGM05 )) == 0)
			PlaySoundMem( data.Get( DataManager::SoundBGM05 ), DX_PLAYTYPE_LOOP);
		break;
	case 2:
		BM.LoadGraphic("resource/texture/Map/STAGE_3.bmp");
		BM.LoadEnemyGraphic("resource/texture/Map/ENEMY_3.bmp");
		if(CheckSoundMem(data.Get( DataManager::SoundBGM06 )) == 0)
			PlaySoundMem( data.Get( DataManager::SoundBGM06 ), DX_PLAYTYPE_LOOP);
		break;
	case 3:
		BM.LoadGraphic("resource/texture/Map/STAGE_4.bmp");
		BM.LoadEnemyGraphic("resource/texture/Map/ENEMY_4.bmp");
		if(CheckSoundMem(data.Get( DataManager::SoundBGM07 )) == 0)
			PlaySoundMem( data.Get( DataManager::SoundBGM07 ), DX_PLAYTYPE_LOOP);
		break;
	case 4:
		BM.LoadGraphic("resource/texture/Map/STAGE_5.bmp");
		BM.LoadEnemyGraphic("resource/texture/Map/ENEMY_5.bmp");
		if(CheckSoundMem(data.Get( DataManager::SoundBGM08 )) == 0)
			PlaySoundMem( data.Get( DataManager::SoundBGM08 ), DX_PLAYTYPE_LOOP);
		break;
	default:
		BM.LoadGraphic("resource/texture/Map/STAGE_1.bmp");
		BM.LoadEnemyGraphic("resource/texture/Map/ENEMY_1.bmp");
		if(CheckSoundMem(data.Get( DataManager::SoundBGM04 )) == 0)
			PlaySoundMem( data.Get( DataManager::SoundBGM04 ), DX_PLAYTYPE_LOOP);
		break;
	}
	// �^�X�N�}�l�[�W���[�̌݊����̖��
	TaskManager::GetInstance().Connect( &BM, &UnitManager::GetInstance() );
	m_FrameCount = 0;

	BlockManager::GetInstance().SetBreakBlock(&m_BreakBlock);
}

//------------------------
// �Q�[���̏I������
void GameScenePlay :: Release()
{
	TaskManager::GetInstance().Release();
	BlockManager::GetInstance().Release();
	UnitManager::GetInstance().Release();
	
	delete m_Menu;
}

//------------------------
// �`�揈��
void GameScenePlay :: Draw(void)
{
	ClearDrawScreen(); // �`���N���A
	
	DataManager& data = DataManager::GetInstance();
	// �Q�[���J�n�`��
	m_DepthSelect.Draw();
	// �u���b�N�`��
	BlockManager::GetInstance().Draw();
	// ���j�b�g�`��
	UnitManager::GetInstance().Draw();
	// ���O���̕`��
	m_UserInterface.DrawMogll();
	//�u���b�N�j��p�[�e�B�N��
	m_BreakBlock.Draw();
	// ���񂾂�G�t�F�N�g��\�����Ȃ�
	if( data.m_MogllStatus.life > 0 )
	{
		// �^�X�N�`��
		TaskManager::GetInstance().Draw();
	}
	// �F���D�`��
	m_DepthSelect.SpacecraftDraw();
	//�t�B�[���h�G�t�F�N�g�`��
	m_UserInterface.DrawFieldEffect();
	// UI�`��
	m_UserInterface.Draw( BlockManager::GetInstance().GetDepth());
	if(m_Menu->GetConfirmationFlag() || m_Menu->GetFirstProduction() || m_Menu->GetProduction()){
		// �w���v�\��
		m_Help.Draw();
	}
	// ���j���[�`��
	m_Menu->Draw();
	// �E�o���j���[
	m_UserInterface.DrawEscape();
	// ���[�_�[�I���I�t
	m_UIDisplay.Draw();
	if(!m_Menu->GetConfirmationFlag() && !m_Menu->GetFirstProduction() && !m_Menu->GetProduction()){
		// �w���v�\��
		m_Help.Draw();
	}
	// ����Q�b�g���
	m_TreasureEffect.Draw();
	//
	m_AfterGetItem.Draw();
	// �Q�[���N���A��ʕ`��
	m_GameClear.Draw();
	// �Q�[���I�[�o�[��ʕ`��
	m_GameOver.Draw();

	//ScreenFlip();//�X���b�v
}

//-------------------------
// �X�V����
int GameScenePlay :: Update(void)
{
	DataManager& data = DataManager::GetInstance();

	DXLibMath::Vector2 l_mouse;
	//�}�E�X�̍��W��ۑ�
	l_mouse.x = GameInput::GetInstance().GetXf();
	l_mouse.y = GameInput::GetInstance().GetYf();

	// false�Ȃ�t���O��܂��đ���\��
	m_HelpFlg = m_Help.Update();
	//�w���v���J��or����:�E�N���b�N(�g���K�[)
	if((data.m_MogllStatus.treasureStatus == -1 && GameInput::GetInstance().GetMouse(GameInput::MouseLeftTrg) && m_HelpFlg == false && m_EscapeFlag == false
		&& !m_Menu->GetConfirmationFlag() && !m_Menu->GetFirstProduction() && !m_Menu->GetProduction())){
		// true�Ȃ�t���O�𗧂Ăđ���s��
		if(m_Help.Open(l_mouse))	m_HelpFlg = true;
	}

	if(m_HelpFlg == false &&  data.m_MogllStatus.life > 0 && !m_GameClear.IsAct() && m_EscapeFlag == false && 
		!m_Menu->GetConfirmationFlag() && !m_Menu->GetFirstProduction() && !m_Menu->GetProduction()){
		//���j���[���J��or����:���N���b�N(�g���K�[)
		if(data.m_MogllStatus.treasureStatus == -1 && GameInput::GetInstance().GetMouse(GameInput::MouseLeftTrg)){
			if(m_Menu->OpeningClosing(l_mouse)){
				m_UIDisplay.SetFlag(UIDisplay::Flag_CO);
				m_UserInterface.CheckCurrentSlot();
			}
			if(m_Menu->GetEnable())
				m_UserInterface.SetVisible(false);
		}
		//���j���[���J��or����:�E�N���b�N(�g���K�[)
		if(data.m_MogllStatus.treasureStatus == -1 && GameInput::GetInstance().GetMouse(GameInput::MouseRightTrg)){
			if(m_Menu->OpeningClosing()){
				m_UIDisplay.SetFlag(UIDisplay::Flag_CO);
				m_UserInterface.CheckCurrentSlot();
			}
			if(m_Menu->GetEnable())
				m_UserInterface.SetVisible(false);
		}
	}

	//���j���[�X�V
	if( !m_UserInterface.GetEsFlg() )// �G�X�P�[�v�m�F��ʂ̎��͏������Ȃ�
	{
		m_Menu->Update();
	}
	m_UIDisplay.Update();
	if(!m_Menu->GetEnable())
		m_UserInterface.SetVisible(true);
	//�t�B�[���h�G�t�F�N�g�X�V
	m_UserInterface.UpdateEffect();
	// ���C�t���[�^�[�X�V
	m_UserInterface.UpdateLife();

	// �E�o�t���O�X�V(�o�O���p)
	m_EscapeFlag = m_UserInterface.GetEsFlg();
	//�E�o�{�^���X�V
	//if( !m_Menu->GetEnable() && m_HelpFlg == false){
	if( m_HelpFlg == false && !m_Menu->GetConfirmationFlag() && !m_Menu->GetFirstProduction() && !m_Menu->GetProduction()){
		m_UserInterface.UpdateButton();
	}
	if(m_UserInterface.GetOutFlg())	// �E�o
	{
		data.m_SceneInt["BackST"] = GAME_SCENE_PLAY;
		data.m_MogllStatus.frameSkip = 0;
		return GAME_SCENE_STAGESELECT;
	}
	if(m_UserInterface.GetRetryFlg()){	// ���g���C
		return GAME_SCENE_PLAY;
	}
	// �Q�[���X�^�[�g�X�V
	if(m_HelpFlg == false && m_EscapeFlag == false)
		m_DepthSelect.Update(m_Menu->GetEnable());

	if( m_DepthSelect.IsEnable() )
	{
		//�u���b�N�j��
		m_BreakBlock.Update();
		return GAME_SCENE_THIS;
	}
	// ������擾���Ă����珈������
	if( data.m_MogllStatus.treasureStatus != -1)
	{
		if( m_SoundTime == 0 )
		{
			PlaySoundMem( data.Get( DataManager::SoundSE01 ), DX_PLAYTYPE_BACK);
			m_SoundTime++;
			// ����̃A�C�e�����擾�ς݂ɂ���
			for( int i = 0; i < 50; i++ )
			{
				if( data.m_SystemData.treasure[i].id == data.m_MogllStatus.treasureStatus )
				{
					data.m_SaveData.stageItemStatus[ i ] = 1;
					break;
				}
			}
			if( data.m_MogllStatus.treasureStatus == 59 )
			{
				data.m_SaveData.stageItemStatus[50] = 1;
			}
		}
		if(m_TreasureEffect.Update())
		{
			m_SoundTime = 0;
		}
		return GAME_SCENE_THIS;
	}
	////�Q�b�g��c���[���o
	//if( data.m_MogllStatus.treasureStatus != -1){
	//	//m_AfterGetTree.Update();
	//	m_AfterGetItem.Update();
	//	return GAME_SCENE_THIS;
	//}

	// �ϋv�l�������Ȃ�����Q�[���I�[�o�[
	GameInput &input = GameInput::GetInstance();
	if( data.m_MogllStatus.life <= 0 && EquipmentFunction_46())
	{
		if( m_SoundTime == 0 )
		{
			PlaySoundMem( data.Get( DataManager::SoundBGM10 ), DX_PLAYTYPE_BACK);
			m_SoundTime++;
		}
		m_GameOver.Update();
		if( m_GameOver.IsEnd() )
		{
			// �[�x���L�^
			int depth = static_cast<int>( BlockManager::GetInstance().GetDepth() );
			if( depth > data.m_SaveData.stageDepth[ data.m_SceneInt["StageNo"] ] )
			{
				data.m_SaveData.stageDepth[ data.m_SceneInt["StageNo"] ] = depth;
			}
			data.m_SceneInt["BackST"] = GAME_SCENE_PLAY;
			data.m_MogllStatus.frameSkip = 0;
			return GAME_SCENE_STAGESELECT;
		}
		return GAME_SCENE_THIS;
	}

	// ���݂̐[�x���ŉ��w�𒴂���ƃQ�[���N���A
	if(HIERARCHY[data.m_SceneInt["StageNo"]].Hier[HIERARCHY[data.m_SceneInt["StageNo"]].H_num-1] <= BlockManager::GetInstance().GetDepth()){
		if( m_SoundTime == 0 )
		{
			//�X�e�[�WBGM���X�g�b�v
			switch( data.m_SceneInt["StageNo"] )
			{
			case 0:
				StopSoundMem( data.Get( DataManager::SoundBGM04 ));
				break;
			case 1:
				StopSoundMem( data.Get( DataManager::SoundBGM05 ));
				break;
			case 2:
				StopSoundMem( data.Get( DataManager::SoundBGM06 ));
				break;
			case 3:
				StopSoundMem( data.Get( DataManager::SoundBGM07 ));
				break;
			case 4:
				StopSoundMem( data.Get( DataManager::SoundBGM08 ));
				break;
			default:
				break;
			}
			PlaySoundMem( data.Get( DataManager::SoundBGM09 ), DX_PLAYTYPE_BACK);
			m_SoundTime++;
		}
		m_GameClear.Update();
		if( m_GameClear.IsEnd() )
		{
			data.m_SceneInt["BackST"] = GAME_SCENE_PLAY;
			data.m_MogllStatus.frameSkip = 0;
			return GAME_SCENE_STAGESELECT;
		}
		return GAME_SCENE_THIS;
	}

	if( !m_Menu->GetEnable() && m_HelpFlg == false && m_EscapeFlag == false  && !m_Menu->GetConfirmationFlag() && !m_Menu->GetProduction())
	{
		// ���͍X�V
		m_UserInterface.Update();

		// �u���b�N�X�V
		BlockManager::GetInstance().Update();

		// ���j�b�g�X�V
		UnitManager::GetInstance().Update();

		// �n�ʂ��@��
		m_Dig.Update();

		//�u���b�N�j��
		m_BreakBlock.Update();

		// �^�X�N�X�V
		TaskManager::GetInstance().Update();

		AutoSkill();

	}

	// ���G���Ԍ���
	if( data.m_MogllStatus.noHitTime )
	{
		data.m_MogllStatus.noHitTime--;
	}
	data.m_MogllStatus.frameSkip = 1;
	m_FrameCount++;
	return GAME_SCENE_THIS;

}

void GameScenePlay::AutoSkill(void)
{
	EquipmentFunction_02( m_FrameCount );
	EquipmentFunction_13( m_FrameCount );
	EquipmentFunction_14_Dec( m_FrameCount );
	EquipmentFunction_33( m_FrameCount );
	EquipmentFunction_44( m_FrameCount );
	EquipmentFunction_48( m_FrameCount );
	EquipmentFunction_49( m_FrameCount );
	EquipmentFunction_50( m_FrameCount );
	EquipmentFunction_54( m_FrameCount );
	EquipmentFunction_58( m_FrameCount );
	EquipmentFunction_59( m_FrameCount );
	EquipmentFunction_03();
	EquipmentFunction_60();
	// ������
	if( m_FrameCount % 30 == 0)
	{
		DataManager::GetInstance().m_MogllStatus.resource++;
	}
}
