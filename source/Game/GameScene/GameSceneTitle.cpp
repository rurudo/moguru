#include "GameSceneTitle.h"
#include "../System/GameInput.h"
#include "../System/DataManager.h"
#include "../System/DxLibMath.h"

//====================================================
// �����֐�
GameScene* GameSceneTitle_CreateScene()
{
	return new GameSceneTitle();
}

//====================================================
// �N���X���\�b�h
GameSceneTitle :: GameSceneTitle(void)
{
	Init();
}
GameSceneTitle :: ~GameSceneTitle(void)
{
	Release();
}

//------------------------
// �Q�[���̏���������
void GameSceneTitle :: Init(void)
{
	DataManager& data = DataManager::GetInstance();
	data.Load(DataManager::ResourceSetTitle);

	m_FrameCount = 0;
	m_TitleStatus = STATE_TeamLogo;

	// �A�j���[�V�����f�[�^����
	const ANIME_DATA Crack[3] =
	{	{20, data.Get(DataManager::Title_stone_Crack1)},
		{20, data.Get(DataManager::Title_stone_Crack2)},
		{20, data.Get(DataManager::Title_stone_Crack3)}};
	for(int i = 0; i < 3; i++){
		m_Crack[i] = Crack[i];
	}
	const ANIME_DATA Crash[2] =
	{	{15, data.Get(DataManager::Title_stone_Crash1)},
		{15, data.Get(DataManager::Title_stone_Crash2)}};
	for(int i = 0; i < 2; i++){
		m_Crash[i] = Crash[i];
	}

	// �`�揉���l�̑��
	// �^�C�g��
	const DRAW_DATA title = {0.5f, 0.5f, 1.0f, 0.0f, data.Get(DataManager::Title_logo)};
	m_Title = title;
	//�^�C�g���w�i
	const DRAW_DATA logoBack = {0.505f, 0.3f, 1.0f, 0.0f, data.Get(DataManager::Title_logo_Back)};
	m_LogoBack		= logoBack;
	m_LogoBackAlpha = 0;

	// ���O��
	const DRAW_DATA Mog = {0.48f, -0.9f, 1.0f, 0.0f, data.Get(DataManager::Unit_moguru_top)};
	m_Mog = Mog;
	// ��
	const DRAW_DATA Rock[2] =
	{	{0.5f, 0.5f, 1.0f, 0.0f, data.Get(DataManager::Title_stone_break_left)},
		{0.5f, 0.5f, 1.0f, 0.0f, data.Get(DataManager::Title_stone_break_right)}};
	for(int i=0; i<2; i++)	m_Rock[i] = Rock[i];
	// �͂��߂镶��
	const DRAW_DATA w_start[4] = {  {0.36f, 1.5f, 0.77f, 0.0f, data.Get(DataManager::Start1)},
									{0.45f, 1.5f, 0.77f, 0.0f, data.Get(DataManager::Start2)},
									{0.54f, 1.5f, 0.77f, 0.0f, data.Get(DataManager::Start3)},
									{0.63f, 1.5f, 0.77f, 0.0f, data.Get(DataManager::Start4)}};
	for(int i=0; i<4; i++){
		m_WordStart[i] = w_start[i];
		m_WordStartBack[i] = w_start[i];
	}
	// �}�E�X�Ŕ�΂������p
	m_WordStartBack[0].y = m_WordStartBack[1].y = m_WordStartBack[2].y = m_WordStartBack[3].y = 0.75f;

	// ��������
	const DRAW_DATA s_rock[8] = {   {0.1f,  0.0f, 1.0f, 1.0f, data.Get(DataManager::Block_Rock)},
									{0.0f,  0.2f, 1.0f, 0.3f, data.Get(DataManager::Block_Rock)},
									{0.9f,  0.0f, 1.0f, 1.8f, data.Get(DataManager::Block_Rock)},
									{1.0f,  0.2f, 1.0f, 0.8f, data.Get(DataManager::Block_Rock)},
									{0.1f,  1.0f, 1.0f, 0.4f, data.Get(DataManager::Block_Rock)},
									{0.0f,  0.8f, 1.0f, 2.3f, data.Get(DataManager::Block_Rock)},
									{0.9f,  1.0f, 1.0f, 0.0f, data.Get(DataManager::Block_Rock)},
									{1.0f,  0.8f, 1.0f, 0.8f, data.Get(DataManager::Block_Rock)}};
	for(int i=0; i<8; i++)	m_S_Rock[i] = s_rock[i];

	// ���l�A�t���O�̏�����
	loop[0] = loop[1] = loop[2] = Anim[0] = Anim[1] = 0;
	MouRot = 0.4f;
	Break_flg = Hit_flg = RotFlg = false;
	m_rotflg_st[0]  = m_rotflg_st[1]  = m_rotflg_st[2]  = m_rotflg_st[3] = false;
	TutFlg = m_MouseFlg = 0;
	m_Bright = 255.0f;
	m_Fadeflg = false;
	// �X�e�[�^�X�̏�����
	m_Mog_Anim_ST = Move1;
}

//------------------------
// �Q�[���̏I������
void GameSceneTitle :: Release()
{
	SetDrawBright(255, 255, 255);
	DataManager& data = DataManager::GetInstance();
	StopSoundMem( data.Get( DataManager::SoundBGM01 ) );
}

//-------------------------
// �`�揈��
void GameSceneTitle :: Draw(void)
{
	ClearDrawScreen(); // �`���N���A
	DataManager& data = DataManager::GetInstance();
	switch(m_TitleStatus)
	{
	case STATE_TeamLogo:
		DXLibMath::DrawBoxResize(0.0f, 0.0f, 1.0f, 1.0f, GetColor(255, 255, 255), TRUE);	// ���l�p
		DXLibMath::DrawGraphResize(0.3f, 0.2f, data.Get(DataManager::Team_logo), TRUE);		// �`�[�����S
		break;
	case STATE_AutoDemo:
		// �w�i
		for(int i = 0; i < 4; i++){
			for(int j = 0; j < 3; j++){
				DXLibMath::DrawGraphResize(0.25f * i, (0.333f * j)-0.157f, data.Get(DataManager::Block_soil), TRUE);
			}
		}
		//���S�w�i
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_LogoBackAlpha);
		DXLibMath::DrawRotaGraphResize(m_LogoBack.x, m_LogoBack.y, m_LogoBack.scal, 0.0f, m_LogoBack.handle , TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		// �^�C�g�����S
		DXLibMath::DrawRotaGraphResize(m_Title.x, m_Title.y, m_Title.scal, m_Title.rot, m_Title.handle, TRUE);
		// �h�������O��
		DXLibMath::DrawRotaGraphResize(m_Mog.x, m_Mog.y, m_Mog.scal, m_Mog.rot, m_Mog.handle, TRUE);
		DXLibMath::DrawRotaGraphResize(m_Mog.x, m_Mog.y+0.415f, m_Mog.scal, m_Mog.rot, data.GetGraphicGroupData( DataManager::GG_TITLE_Drill01 + 3-(m_FrameCount / 4) % 4), TRUE );
		// ���܂�l�ɍŌ��1�s�̓h�������O���̌�ɕ`��
		for(int i = 0; i < 4; i++)
			DXLibMath::DrawGraphResize(0.25f * i, 0.842f, data.Get(DataManager::Block_soil), TRUE);
		// ���߉B��
		DXLibMath::DrawGraphResize(0.25f, 0.509f, data.Get(DataManager::Block_soilsub), TRUE);
		// �����Ȋ�
		RockDraw();
		// ��
		if(Break_flg == false){	// ����Ă��Ȃ�
			DXLibMath::DrawRotaGraphResize(m_Rock[0].x, m_Rock[0].y, 1.0f, 0.0f, data.Get(DataManager::Title_stone), TRUE);
		}
		else{					// ����Ă���
			for(int i=0; i<2; i++)
				DXLibMath::DrawRotaGraphResize(m_Rock[i].x, m_Rock[i].y, m_Rock[i].scal, m_Rock[i].rot, m_Rock[i].handle, TRUE);
		}
		if(Hit_flg == true){
			// �Ђ�
			if(Anim[0] < 3){
				DXLibMath::DrawRotaGraphResize(m_Rock[0].x, m_Rock[0].y, 1.0f, 0.0f, m_Crack[Anim[0]].handle, TRUE);
				if(m_Crack[Anim[0]].frame <= loop[1]){
					Anim[0]++;
					loop[1] = 0;
				}
			}
			// �j��
			if(Anim[1] < 2){
				DXLibMath::DrawRotaGraphResize(0.5f, 0.3f, 1.0f, 0.0f, m_Crash[Anim[1]].handle, TRUE);
				if(m_Crash[Anim[1]].frame <= loop[2]){
					Anim[1]++;
					loop[2] = 0;
					if(Anim[1] >= 2) Anim[1] = 0;
				}
			}
		}
		// �n�߂�
		DXLibMath::DrawRotaGraphResize(0.5f, m_WordStart[0].y, 1.0f, 0.0f, data.Get(DataManager::StartBack), TRUE);
		for(int i=0; i<4; i++)
			DXLibMath::DrawRotaGraphResize(m_WordStart[i].x, m_WordStart[i].y, m_WordStart[i].scal, m_WordStart[i].rot, m_WordStart[i].handle, TRUE);

		break;
	case STATE_Title:
		ObjDraw();
		break;
	case STATE_FADE:
		ObjDraw();
	default:
		break;
	}
	//ScreenFlip();//�X���b�v
}

//-------------------------
// �X�V����
int GameSceneTitle :: Update(void)
{
	GameInput &input = GameInput::GetInstance();
	// �}�E�X�̍��W��ۑ�
	m_mouse.x = GameInput::GetInstance().GetXf();
	m_mouse.y = GameInput::GetInstance().GetYf();

	switch(m_TitleStatus)
	{
	// �^�C�g��
	case STATE_TeamLogo:
		// ���N���b�N
		if(input.GetMouse(GameInput::MouseLeftTrg) || m_FrameCount >= 120 + FADE_OUT_COUNT)
		{
			m_FrameCount = 0;
			m_TitleStatus = STATE_AutoDemo;

			PlaySoundMem( DataManager::GetInstance().Get( DataManager::SoundBGM01 ), DX_PLAYTYPE_LOOP);
		}
		FadeCalc(120 + FADE_OUT_COUNT);
		break;
	// �^�C�g���f��
	case STATE_AutoDemo:
		if(input.GetMouse(GameInput::MouseLeftTrg))
		{
			m_FrameCount = 0;
			m_TitleStatus = STATE_Title;
			m_Fadeflg = true;
			FadeCalc(3000);
		}
		else{
			AutoDemo();
			SetDrawBright(255, 255, 255);
		}
		break;
	// �^�C�g���m��
	case STATE_Title:
		if((m_mouse.y >= 0.69f && m_mouse.y <= 0.81f) && (m_mouse.x >= 0.3f && m_mouse.x <= 0.3f+0.375f))	// �I���}�E�X���̃A�j���[�V����
		{
			if( flg != START )
			{
				PlaySoundMem( DataManager::GetInstance().Get( DataManager::SoundSE07 ), DX_PLAYTYPE_BACK);
				flg = START;
				if(m_rotflg_st[0]==false && m_rotflg_st[1]==false && m_rotflg_st[2]==false && m_rotflg_st[3]==false)	m_rotflg_st[0] = true;	// ��]�t���O�𗧂Ă�
			}
			m_MouseFlg = 1;
		}
		else{
			flg = NON;
			m_MouseFlg = 0;
		}

		// ���N���b�N
		if(input.GetMouse(GameInput::MouseLeftTrg) && flg == START)
		{
			PlaySoundMem( DataManager::GetInstance().Get( DataManager::SoundSE10 ), DX_PLAYTYPE_BACK);
			DataManager& Backdata = DataManager::GetInstance();
			Backdata.m_SceneInt["BackST"] = GAME_SCENE_TITLE;
			m_TitleStatus = STATE_FADE;
		}
		// �E�N���b�N
		//if(input.GetMouse(GameInput::MouseRightTrg))
		//{
		//	return GAME_SCENE_DEBUG;
		//}
		// �O�X�e�[�g�ŃN���b�N�Ŕ�΂����ꍇ
		if(m_Fadeflg == true)	FadeCalc(1000000);
		break;
	// �t�F�[�h
	case STATE_FADE:
		// ��ʂ��Â����Ă���
		m_Bright -= 10.0f;
		if(m_Bright <= 0.0f)	return GAME_SCENE_STAGESELECT;
		SetDrawBright((int)m_Bright, (int)m_Bright, (int)m_Bright);
		break;

	default:
		break;
	}

	// ������]����	�͂��߂�
	for(int i=0; i<4; i++){
		if(m_rotflg_st[i] == true){
			m_WordStart[i].rot += 0.2f;
			if(m_WordStart[i].rot >= 3.141592653f * 2.0f){
				m_WordStart[i].rot = 0.0f;
				m_rotflg_st[i] = false;
				if(m_MouseFlg == 1){	// �I���}�E�X�Ȃ玟�̕����ɓ`��
					if(i != 3)	m_rotflg_st[i+1] = true;
					else		m_rotflg_st[0]   = true;
				}
			}
		}
	}

	m_FrameCount++;
	
	//���v���C�܂ł̃V���[�g�J�b�g
	//if(GameInput::GetInstance().GetKeyTrg(KEY_INPUT_F1)){// || (GameInput::GetInstance().GetMouse(GameInput::MouseLeftTrg) && m_mouse.x > 0 && m_mouse.x < 0 + 30 && 
	//														//m_mouse.y > 0 && m_mouse.y < 0 + 30)){
	//	return GAME_SCENE_PLAY;
	//}

	return GAME_SCENE_THIS;
}
// �t�F�[�h
void GameSceneTitle::FadeCalc(int outCount)
{
	int bright = 255 / FADE_IN_COUNT * m_FrameCount;
	if(bright > 255)
	{
		bright = 255;
	}
	// outCount�Ƀt���[���������B�������_�ŉ�ʐ^���Â�
	if(outCount - FADE_OUT_COUNT <= m_FrameCount)
	{
		bright = 255 / FADE_OUT_COUNT * (outCount - m_FrameCount);
	}
	SetDrawBright(bright, bright, bright);
}

void GameSceneTitle::AutoDemo(void)
{
	static int Mog_loop;
	static int cnt;

	switch(m_Mog_Anim_ST){
		case Move1:	// ���O�����ォ��~��Ă���
			m_Mog.y += 0.01f;//0.007f;
			if(m_Mog.y >= -0.34f){
				m_Mog_Anim_ST = Shake;
				Mog_loop = loop[0];
				cnt = 0;
				Hit_flg = true;
			}
			break;
		case Shake:	// ���O�������������k����
			if(Mog_loop % 2 == 0)	m_Mog.y += 0.01f;
			else					m_Mog.y -= 0.01f;
			if( m_FrameCount % 10 == 0 )
			{
				PlaySoundMem( DataManager::GetInstance().Get( DataManager::SoundSE15 ), DX_PLAYTYPE_BACK);
			}
			if(loop[0] % 3 == 0){
				Mog_loop++;
				if(cnt >= 60){
					m_Mog_Anim_ST = Move2;
					// �t���O�̕ύX
					Break_flg = true;
					Hit_flg = false;
					PlaySoundMem( DataManager::GetInstance().Get( DataManager::SoundSE14 ), DX_PLAYTYPE_BACK);
				}
			}
			cnt++;

			break;
		case Move2:	// ���O�����܂��~���
			m_Mog.y += 0.007f;
			if(m_Mog.y >= 0.65f){
				m_Mog.y = 0.65f;
				m_Mog_Anim_ST = Move3;
				PlaySoundMem( DataManager::GetInstance().Get( DataManager::SoundSE13 ), DX_PLAYTYPE_BACK);
			}
			break;
		case Move3:	// �^�C�g�����S�Ƃ͂��߂邪��ʒu�Ɉړ�
			for(int i=0; i<4; i++)	m_WordStart[i].y -= 0.007f;	// ����
									m_Title.y -= 0.007f;		// �^�C�g��
			if(m_Title.y <= 0.3f)			m_Title.y = 0.3f;
			if(m_WordStart[0].y <= 0.75f){
				for(int i=0; i<4; i++)	m_WordStart[i].y = 0.75f;
			}
			if(m_Title.y == 0.3f && m_WordStart[0].y == 0.75f){
				m_Mog_Anim_ST = Move4;
				PlaySoundMem( DataManager::GetInstance().Get( DataManager::SoundSE13 ), DX_PLAYTYPE_BACK);
			}
			break;
		case Move4:
			if(m_LogoBackAlpha < 255)
				m_LogoBackAlpha += (int)((float)(260 - m_LogoBackAlpha)*0.15f);
			if(m_LogoBackAlpha >= 254)
			{
				m_LogoBackAlpha = 255;
				m_Mog_Anim_ST = Stop;
			}
			break;
		case Stop:	// �͂܂��ĂƂ܂�
			m_FrameCount = 0;
			m_TitleStatus = STATE_Title;
			break;
		default:
			break;
	}

	// ���ꂽ��̓���
	if(Break_flg == true){
		m_Rock[0].y		+= 0.01f;
		m_Rock[0].x		-= 0.006f;
		m_Rock[0].rot	-= 0.015f;
		m_Rock[1].y		+= 0.01f;
		m_Rock[1].x		+= 0.006f;
		m_Rock[1].rot	+= 0.015f;
	}

	// ���[�v���Z
	loop[0]++;
	if(Hit_flg == true){
		loop[1]++;
		loop[2]++;
	}
}

void GameSceneTitle::ObjDraw(void)
{
	DataManager& data = DataManager::GetInstance();

	// �w�i
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){
			DXLibMath::DrawGraphResize(0.25f * i, (0.333f * j)-0.157f, data.Get(DataManager::Block_soil), TRUE);
		}
	}
	//���S�w�i
	DXLibMath::DrawRotaGraphResize(m_LogoBack.x, m_LogoBack.y, m_LogoBack.scal, 0.0f, m_LogoBack.handle , TRUE);
	// �^�C�g�����S
	DXLibMath::DrawRotaGraphResize(m_Title.x, 0.3f, m_Title.scal, m_Title.rot, m_Title.handle, TRUE);
	// ���O��
	DXLibMath::DrawRotaGraphResize(m_Mog.x, 0.65f, m_Mog.scal, m_Mog.rot, data.Get(DataManager::Unit_moguru_chest), TRUE);
	DXLibMath::DrawRotaGraphResize(m_Mog.x, 0.65f+0.415f, m_Mog.scal, m_Mog.rot, data.Get(DataManager::Unit_moguru_under), TRUE );
	// ���܂�l�ɍŌ��1�s�̓h�������O���̌�ɕ`��
	for(int i = 0; i < 4; i++)	DXLibMath::DrawGraphResize(0.25f * i, 0.842f, data.Get(DataManager::Block_soil), TRUE);
	// ���߉B��
	DXLibMath::DrawGraphResize(0.25f, 0.509f, data.Get(DataManager::Block_soilsub), TRUE);
	// �����Ȋ�
	RockDraw();
	// �n�߂�
	DXLibMath::DrawRotaGraphResize(0.49f, m_WordStartBack[0].y, 1.0f, 0.0f, data.Get(DataManager::StartBack), TRUE);
	for(int i=0; i<4; i++)
		DXLibMath::DrawRotaGraphResize(m_WordStartBack[i].x, m_WordStartBack[i].y, m_WordStartBack[i].scal, m_WordStart[i].rot, m_WordStartBack[i].handle, TRUE);
}

// �����Ȋ�
void GameSceneTitle::RockDraw(void)
{
	DataManager& data = DataManager::GetInstance();

	// ��̕`��
	for(int i=0; i<8; i++)
		DXLibMath::DrawRotaGraphResize(m_S_Rock[i].x, m_S_Rock[i].y, m_S_Rock[i].scal ,m_S_Rock[i].rot ,m_S_Rock[i].handle , TRUE);
}