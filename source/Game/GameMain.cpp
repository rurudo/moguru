#include "GameMain.h"
#include "GameScene/CreateScene.h"
#include "System/GameInput.h"
#include "System/DataManager.h"

GameMain :: GameMain()
{
	m_pGameScene = NULL;
	m_Pause = false;
	m_FrameCount = 0;
	m_SkipFrame = 0;
	m_SkipRate = 0;
	memset(m_TimeCount, 0, sizeof(m_TimeCount) );
}
GameMain :: ~GameMain()
{
}

void GameMain :: Init(void)
{
	//���͏�����
	DataManager::GetInstance().LoadData("save.dat");
	GameInput::GetInstance().Init();
	//GameInput::GetInstance().SaveAutoInputFile();				// ����̃v���C���L�^����
	//GameInput::GetInstance().LoadAutoInputFile("replay.rep");	// ���v���C�t�@�C�����Đ�����
	DXLibMath::SetWindowSizeRate(800.0, 600.0);
	m_ScreenBuffer = MakeScreen(800, 600);
	DataManager::GetInstance().m_MogllStatus.frameSkip = 0;
}
int GameMain :: Update(void)
{
	// FPS����
	int nowTime = GetNowCount();
	int inputTime = nowTime - m_TimeCount[60];
	// �傫������v���l�̓m�C�Y�Ƃ��Ď��W���Ȃ�
	if( inputTime < 100 )
	{
		m_TimeCount[m_FrameCount % 60] = inputTime;
	}
	m_TimeCount[60] = nowTime;
	int time = 0;
	for(int i = 0; i < 60; i++)
	{
		time += m_TimeCount[i];
	}
	m_FPS = 1000.0f / (time / 60.0f);
	//printfDx("FPS %.1f", m_FPS);
	m_FrameCount++;
	// FPS����I��
	if(m_pGameScene == NULL)
		m_pGameScene = (*sp_CreateTable[GAME_SCENE_TITLE])();
	//�|�[�Y����
	//if(CheckHitKey(KEY_INPUT_P))
	//{
	//	m_Pause = true;
	//}
	//if(CheckHitKey(KEY_INPUT_S))
	//{
	//	m_Pause = false;
	//}
	if( !m_Pause )
	{
		//���͎擾
		GameInput::GetInstance().Update();
		//�Q�[���X�V
		int scene = m_pGameScene->Update();
		if(scene != GAME_SCENE_THIS)
		{
			delete m_pGameScene;
			m_pGameScene = (*sp_CreateTable[scene])();
		}
	}

	//if(GameInput::GetInstance().GetKeyTrg(KEY_INPUT_1))
	//{
	//	SetGraphMode(640, 480, 32);
	//	DXLibMath::SetWindowSizeRate(640.0, 480.0);
	//	DataManager::GetInstance().Release();
	//	DataManager::GetInstance().Load(DataManager::ResourceSetTitle);
	//	m_ScreenBuffer = MakeScreen(800, 600);
	//}
	//if(GameInput::GetInstance().GetKeyTrg(KEY_INPUT_2))
	//{
	//	SetGraphMode(800, 600, 32);
	//	DXLibMath::SetWindowSizeRate(800.0, 600.0);
	//	DataManager::GetInstance().Release();
	//	DataManager::GetInstance().Load(DataManager::ResourceSetTitle);
	//	m_ScreenBuffer = MakeScreen(800, 600);
	//}
	//if(GameInput::GetInstance().GetKeyTrg(KEY_INPUT_3))
	//{
	//	SetGraphMode(1024, 768, 32);
	//	DXLibMath::SetWindowSizeRate(1024.0, 768.0);
	//	DataManager::GetInstance().Release();
	//	DataManager::GetInstance().Load(DataManager::ResourceSetTitle);
	//	m_ScreenBuffer = MakeScreen(800, 600);
	//}

	// �f�o�b�O�p�t���[���X�L�b�v
	//if( GameInput::GetInstance().GetFrame() < 9000)
	//if( GameInput::GetInstance().GetFrame() % 10 != 0)
	//{
	//	return 0;
	//}
	if( DataManager::GetInstance().m_MogllStatus.frameSkip != 0 )
	{
		if (m_SkipFrame >0 )
		{
			if( m_SkipRate )
			{
				m_SkipRate--;
			}
			m_SkipFrame--;
			return 0;
		}
		else if( m_FPS < 55.0f )
		{
			m_SkipRate += 10;
			m_SkipFrame = m_SkipRate / 100;
		}
	}

	//�`��
	// �`��Ώۂ��쐬�����X�N���[����
	SetDrawScreen( m_ScreenBuffer );
	m_pGameScene->Draw();
	//DrawFormatString(0, 0, GetColor(255, 255, 255), "FPS %.1f", m_FPS);
	int minute = DataManager::GetInstance().m_SaveData.playFrame;
	int second = (minute / 60) % 60;
	minute = minute / 60 / 60;
	DrawFormatString(0, 0, GetColor(255, 255, 255), "%d:%02d", minute, second);
	DataManager::GetInstance().m_SaveData.playFrame++;

	GameInput::GetInstance().DrawReplayFrame();
	// �`��Ώۂ�\��ʂ�
	SetDrawScreen( DX_SCREEN_BACK );
	DXLibMath::DrawFrontBuffer( m_ScreenBuffer );
	//DrawExtendGraph( 0, 0, 1024, 768, m_ScreenBuffer, FALSE ) ;
	ScreenFlip();
	return 0;
}
void GameMain :: Release(void)
{
	if( m_pGameScene != NULL )
	{
		delete m_pGameScene;
	}
}