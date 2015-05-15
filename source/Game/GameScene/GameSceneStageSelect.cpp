#include "GameSceneStageSelect.h"
#include "../System/GameInput.h"
#include "../System/DataManager.h"
#include "../System/TaskManager.h"
#include "../Task/Task_DrawEffect.h"

//====================================================
// �����֐�
GameScene* GameSceneStageSelect_CreateScene()
{
	return new GameSceneStageSelect();
}

//====================================================
// �N���X���\�b�h
GameSceneStageSelect :: GameSceneStageSelect(void)
{
	Init();
}
GameSceneStageSelect :: ~GameSceneStageSelect(void)
{
	Release();
}

//------------------------
// �Q�[���̏���������
void GameSceneStageSelect :: Init(void)
{
	DataManager& data = DataManager::GetInstance();
	DataManager& Backdata = DataManager::GetInstance();

	data.Load(DataManager::ResourceSetStageSelect);
	// �f���̏����f�[�^
	const DRAW_DATA planet[PLANET_MAX] =
	{	{0.45f, 0.52f, 0.0f, 1.0f, 0.0f, data.Get(DataManager::Ic_stage1), false, 0.0f,	0.0f,  -0.035f},	// �n���s�s
		{0.13f, 0.42f, 0.0f, 0.8f, 0.0f, data.Get(DataManager::Ic_stage2), false, 0.0f, -0.01f, 0.015f},	// �X�C
		{0.30f, 0.80f, 0.0f, 0.7f, 0.0f, data.Get(DataManager::Ic_stage3), false, 0.0f, 0.0f,   0.07f},		// ���n
		{0.72f, 0.80f, 0.0f, 0.8f, 0.0f, data.Get(DataManager::Ic_stage4), false, 0.0f, -0.01f, -0.01f},	// �ΎR
		{0.72f, 0.30f, 0.0f, 0.7f, 0.0f, data.Get(DataManager::Ic_stage5), false, 0.0f, 0.0f,   0.05f}};	// �ߖ���
	// �f���̔w�i�p�X
	const int planet_back[PLANET_MAX] =
	{	data.Get(DataManager::Ic_stage1_Back),	// �n���s�s�̔w�i
		data.Get(DataManager::Ic_stage2_Back),	// �X�C�̔w�i
		data.Get(DataManager::Ic_stage3_Back),	// ���n�̔w�i
		data.Get(DataManager::Ic_stage4_Back),	// �ΎR�̔w�i
		data.Get(DataManager::Ic_stage5_Back)};	// �ߖ����̔w�i

	// ���@�̏��ݒ�
	m_Ship.position.x = 0.5f;
	m_Ship.position.y = 0.5f;
	m_Ship.handle = data.Get(DataManager::Spaceship);

	// �f���̃f�[�^����
	for(int i = 0; i < PLANET_MAX; i++)
	{
		m_Planet[i] = planet[i];
		m_Planet_Back_handle[i] = planet_back[i];
		// �f���̔��a�����߂�
		m_Planet[i].r = 0.125f * m_Planet[i].scal;		// ��ʂ̉��T�C�Y800�Ɖ摜���T�C�Y200��芄����0.25�A���̔��a�Ȃ̂�0.125
		m_st[i].x = 0.5f - m_Planet[i].x;
		m_st[i].y = 0.5f - m_Planet[i].y;
		// �������Ă��邩�ǂ����̃`�F�b�N(-1�͖��J���A0�ȏ�͊J��)
		if(data.m_SaveData.stageDepth[i] >= 0.0f)	m_Planet[i].release = true;

		// �g�k�̕ۑ�
		m_PlanetBackScal[i] = planet[i].scal;
	}

	// �O�̑J�ڂ��^�C�g���̏ꍇ
	if(Backdata.m_SceneInt["BackST"] == GAME_SCENE_TITLE){
		// �t�F�[�h�p
		m_Brightness = 0;
		m_BrightnessFlg = NON;
		m_ship_scal = 0.3f;
		m_id_back = 0;
		m_speed = 0.01f;
		m_CursorScal = m_Planet[0].scal;
	}

	// �O�̑J�ڂ��v���C�̏ꍇ
	if(Backdata.m_SceneInt["BackST"] == GAME_SCENE_PLAY){
		// �t�F�[�h�p
		m_Brightness = 255;
		m_BrightnessFlg = FADE2;
		m_ship_scal = 0.05f;
		m_id_back = data.m_SceneInt["StageNo"];
		Backup();
		m_Ship.position.x = m_Planet[m_id_back].x+0.01f;
		m_Ship.position.y = m_Planet[m_id_back].y;
		m_speed = 0.0001f;
		m_scal_back = m_Planet[m_id_back].scal;
		m_CursorScal = planet[m_id_back].scal;
	}

	m_AddAlpha		= 64.0f;
	m_AddAlphaState = 1.0f;
	m_BeforeId = 0;
	m_PlanetEffectFlg = false;
	m_CursorFlg = false;
	m_BackBrightness = m_FrameBrightness = 255;
	m_BackBrightnessFlg = m_FrameBrightnessFlg = false;

	PlaySoundMem( data.Get( DataManager::SoundBGM02 ), DX_PLAYTYPE_LOOP);
	m_Font.Load( FontManager::FontSet_AZUKI_003 );
}

//------------------------
// �Q�[���̏I������
void GameSceneStageSelect :: Release()
{
	DataManager& data = DataManager::GetInstance();
	TaskManager::GetInstance().Release();
	StopSoundMem( data.Get( DataManager::SoundBGM02 ) );
}
//-------------------------
// �`�揈��
void GameSceneStageSelect :: Draw(void)
{
	ClearDrawScreen(); // �`���N���A
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	DataManager& data = DataManager::GetInstance();

	// BG
	DXLibMath::DrawGraphResize(0.0, 0.0, data.Get(DataManager::StageSelect_Background), TRUE);

	// ��
	for(int i = 0; i < PLANET_MAX; i++)
	{
		// �f���̔w�i
		if(m_Ship.id == i)	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_BackBrightness);		// ���l�̕ύX
		else				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);					// ���l�̕ύX

		DXLibMath::DrawRotaGraphResize(m_Planet[i].x, m_Planet[i].y, m_Planet[i].scal, m_Planet[i].rot, m_Planet_Back_handle[i], TRUE);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);			// ���l��߂�

		// ���J���̐��͍��� �J���͖��邭
		if(m_Planet[i].release == true)	SetDrawBright(255, 255, 255);
		else							SetDrawBright(0, 0, 0);
		// �I������Ă��Ȃ�����`��
		if(m_id_back != i)	DXLibMath::DrawRotaGraphResize(m_Planet[i].x, m_Planet[i].y, m_Planet[i].scal, m_Planet[i].rot, m_Planet[i].handle, TRUE);
		// ���邳�����ɖ߂�
		SetDrawBright(255, 255, 255);
		if(m_Planet[i].release == false)
			DXLibMath::DrawRotaGraphResize(m_Planet[i].x, m_Planet[i].y, m_Planet[i].scal, 0.0f, data.Get(DataManager::Ic_stage_Cascade), TRUE);
	}


	// �v���C�I���e�B�̊Ǘ����ł��Ȃ��̂őI������Ă��鐯�����Ō�ɕ`�悷��
	DXLibMath::DrawRotaGraphResize(m_Planet[m_id_back].x, m_Planet[m_id_back].y, m_Planet[m_id_back].scal, m_Planet[m_id_back].rot, m_Planet[m_id_back].handle, TRUE);

	// �t���[��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_FrameBrightness);		// ���l�̕ύX
	DXLibMath::DrawGraphResize(0.0, 0.0, data.Get(DataManager::StageSelect_Frame_Back), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);			// ���l��߂�
	DXLibMath::DrawGraphResize(0.0, 0.0, data.Get(DataManager::StageSelect_Frame), TRUE);
	DXLibMath::DrawGraphResize(0.0, 0.0, data.Get(DataManager::StageSelect_FrameCharacter), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_ADD, (int)m_AddAlpha);		// ���l�̕ύX
	DXLibMath::DrawGraphResize(0.0, 0.0, data.Get(DataManager::StageSelect_FrameCharacter_Add), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);			// ���l��߂�


	// �^�[�Q�b�g�ɂ̓C���t�H���[�V������\��
	if(m_BrightnessFlg == NON)
	{
		//DXLibMath::DrawRotaGraphResize(m_Planet[m_Ship.id].x+m_Planet[m_Ship.id].cur_x, m_Planet[m_Ship.id].y+m_Planet[m_Ship.id].cur_y, m_CursorScal+m_Planet[m_Ship.id].cur_scal, 0.0f, data.Get(DataManager::Cur_stage), TRUE);
		DXLibMath::DrawRotaGraphResize(m_Planet[m_Ship.id].x+0.17f, m_Planet[m_Ship.id].y-0.15f, 0.8f, 0.0f, data.Get(DataManager::StageInfo_Bar), TRUE);
		int count = 0;
		for(int i = 10 * m_Ship.id; i < 10 * (m_Ship.id + 1); i++)
		{
			if( data.m_SaveData.stageItemStatus[i] == 1 )	count++;
		}
		//char buf[256];
		//sprintf_s(buf, "%d   10", count );
		//m_Font.DrawFontString( FontManager::FontSet_AZUKI_003, m_Planet[m_Ship.id].x+0.17f, m_Planet[m_Ship.id].y-0.2f, buf, 0.2f, GetColor( 128, 255, 128 ) );
		DrawFormatStringToHandle( static_cast<int>(800.0f * (m_Planet[m_Ship.id].x + 0.14f)),
			static_cast<int>( 600.0f * (m_Planet[m_Ship.id].y - 0.22f)),
			GetColor(128,255,128), m_Font.GetHandle( FontManager::FontSet_MSGothic_Middle ), "%d / 10", count );
	}

	// �F���D
	DXLibMath::DrawRotaGraphResize(m_Ship.position.x, m_Ship.position.y, m_ship_scal, DXLibMath::CalcRotation(m_Ship.facing),m_Ship.handle, TRUE);
	// �����O
	TaskManager::GetInstance().Draw();

	if(m_BrightnessFlg != NON){
		// �l�p
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_Brightness);
		DXLibMath::DrawBoxResize(0.0f, 0.0f, 1.0f, 1.0f, GetColor(255, 255, 255), TRUE);
	}

	//ScreenFlip();//�X���b�v
}

//-------------------------
// �X�V����
int GameSceneStageSelect :: Update(void)
{
	GameInput &input = GameInput::GetInstance();

	// �}�E�X�̍��W��ۑ�
	m_mouse.x = GameInput::GetInstance().GetXf();
	m_mouse.y = GameInput::GetInstance().GetYf();
	if(m_BrightnessFlg == NON)
	{
		// �e�f���Ɣ���
		for(int i=0; i< PLANET_MAX; i++){
			VECTOR cur;
			cur.x = m_Planet[i].x;
			cur.y = m_Planet[i].y;

			// �}�E�X�J�[�\���Ɛ��̃`�F�b�N	�������Ă���΃t���O�𗧂āA�X�e�[�^�X�̕\��
			if(DXLibMath::CircleOnPoint(m_mouse, cur, m_Planet[i].r) == true && m_Planet[i].release == true)
			{
				if( m_Ship.id != i )
				{
					PlaySoundMem( DataManager::GetInstance().Get( DataManager::SoundSE11 ), DX_PLAYTYPE_BACK);
					m_Ship.id = i;
				}
				// ���N���b�N
				if(input.GetMouse(GameInput::MouseLeftTrg) && m_BrightnessFlg == NON)
				{
					PlaySoundMem( DataManager::GetInstance().Get( DataManager::SoundSE12 ), DX_PLAYTYPE_BACK);
					DataManager& data = DataManager::GetInstance();
					data.m_SceneInt["StageNo"] = m_Ship.id;
					m_scal_back = m_Planet[i].scal;
					m_id_back = m_Ship.id;
					m_BrightnessFlg = FADE1;
				}
				break;
			}
		}
	}
	// �F���D���ړ�������
	MovePoint();
	static int m_Count;
	TaskManager &taskManager = TaskManager::GetInstance();
	if( m_Count % 2 == 0)
	{
		Task_DrawEffect* task = dynamic_cast<Task_DrawEffect*>( taskManager.CreateTask(TASK_TYPE_DRAW_EFFECT) );
		task->SetPosition( -m_Ship.facing.x * 0.1f + m_Ship.position.x, -m_Ship.facing.y * 0.1f + m_Ship.position.y );
		task->SetVelocity( -m_Ship.facing.x * 0.005f, -m_Ship.facing.y * 0.005f );
		task->SetRotation( DXLibMath::CalcRotation( m_Ship.facing ) );
		task->SetSize( m_ship_scal );
		task->SetAddSize( 0.9f );
		// ���˂���G�t�F�N�g�̉摜�Ǝ��Ԃ��w��
		DataManager &data = DataManager::GetInstance();
		task->Add( data.Get( DataManager::JetRing ), 60);

		// �^�X�N�}�l�[�W���ɂ��̃^�X�N��o�^
		taskManager.Add( task, 0 );
	}
	taskManager.Update();

	// �t���[���̖��邳
	if(m_FrameBrightnessFlg == false){
		m_FrameBrightness -= 2;
		if(m_FrameBrightness <= 80)		m_FrameBrightnessFlg = true;
	}
	else{
		m_FrameBrightness += 2;
		if(m_FrameBrightness >= 255)	m_FrameBrightnessFlg = false;
	}

	// �f�����o
	if(m_BrightnessFlg == NON){
		if(m_PlanetEffectFlg == false){
			m_BackBrightness			-= (int)((255-80) / (0.2f / 0.005f));
			m_Planet[m_Ship.id].scal	-= 0.005f;
			if((m_BackBrightness <= 80) || (m_Planet[m_Ship.id].scal <= m_PlanetBackScal[m_Ship.id])){
				m_PlanetEffectFlg = true;
				m_BackBrightness = 80;
				m_Planet[m_Ship.id].scal = m_PlanetBackScal[m_Ship.id];
			}
		}
		else{
			m_BackBrightness			+= (int)((255-80) / (0.2f / 0.005f));
			m_Planet[m_Ship.id].scal	+= 0.005f;
			if( (m_BackBrightness >= 255) || (m_Planet[m_Ship.id].scal >= m_PlanetBackScal[m_Ship.id] + 0.2f)){
				m_PlanetEffectFlg = false;
				m_BackBrightness = 255;
				m_Planet[m_Ship.id].scal = m_PlanetBackScal[m_Ship.id] + 0.2f;
			}
		}
	}

	//m_Planet[i].scal m_PlanetBackScal
	// �J�[�\���̊g�k
	//if(m_CursorFlg == false){
	//	m_CursorScal -= 0.007f;
	//	if(m_CursorScal <= m_Planet[m_Ship.id].scal+m_Planet[m_Ship.id].cur_scal - 0.2f)
	//		m_CursorFlg = true;
	//}
	//else{
	//	m_CursorScal += 0.007f;
	//	if(m_CursorScal >= m_Planet[m_Ship.id].scal+m_Planet[m_Ship.id].cur_scal - 0.05f)
	//		m_CursorFlg = false;
	//}

	//�����̌�
	m_AddAlpha += m_AddAlphaState;
	if(m_AddAlpha < 32.0f || m_AddAlpha > 160.0f)
		m_AddAlphaState = -m_AddAlphaState;

	m_Count++;

	// �J�[�\�����ړ�������J�[�\���̊g�k���Z�b�g���Ȃ���
	if(m_BeforeId != m_Ship.id){
		m_CursorScal = m_Planet[m_Ship.id].scal+m_Planet[m_Ship.id].cur_scal;
		m_CursorFlg = false;
		m_Planet[m_BeforeId].scal = m_PlanetBackScal[m_BeforeId];
		m_BackBrightness = 80;
	}

	m_BeforeId = m_Ship.id;
	// �J��
	if(m_BrightnessFlg == FADE1 && m_Brightness >= 255){
		return GAME_SCENE_PLAY;
	}

	if(m_BrightnessFlg == FADE2 && m_Brightness <= 0){
		m_BrightnessFlg = NON;
		m_Brightness = 0;
		m_CursorScal = m_Planet[m_Ship.id].scal;
	}
	return GAME_SCENE_THIS;
}

void GameSceneStageSelect::MovePoint(void)
{
	// �^�[�Q�b�g�ƂȂ��Ă���f���̍��W���擾
	VECTOR	tie;			// ���ƉF���D�����ԃx�N�g��
	float	len;			// �F���D�Ɛړ_�̋���
	float	dx, dy;			// �v�Z�p
	static float	rot;	// �ړ����̉�]����

	// �ʏ펞�̉F���D�̓���
	if(m_BrightnessFlg == NON){
		// �F���D�Ƙf���̒��_�����ԃx�N�g��
		tie.x = m_Planet[m_Ship.id].x - m_Ship.position.x;
		tie.y = m_Planet[m_Ship.id].y - m_Ship.position.y;
		tie.z = 0.0f;
		if(DXLibMath::Length(tie) >= m_Planet[m_Ship.id].r){	// �o�O�Ԃ�
			// �F���D�Ɛړ_�̒���
			len = sqrt((DXLibMath::Length(tie)*DXLibMath::Length(tie)) - (m_Planet[m_Ship.id].r*m_Planet[m_Ship.id].r));
			// �v�Z�p�̒l
			dx = len * (len/DXLibMath::Length(tie));
			dy = m_Planet[m_Ship.id].r * (dx/len);
			// ���W�����߂�
			m_terget.x = (m_Ship.position.x + (tie.x * dx)) + (-tie.y * dy);
			m_terget.y = (m_Ship.position.y + (tie.y * dx)) + (tie.x * dy);
			m_terget.z = 0.0f;
		}
		rot = 0.15f;
		m_speed = 0.01f;
	}

	// �X�e�[�W�����̉F���D�̓���
	else if(m_BrightnessFlg == FADE1){
		// ���o����
		Staging();
		rot = 0.05f;
		m_speed -= 0.007f;
		if(m_speed <= 0.003f)	m_speed = 0.003f;
		m_ship_scal -= 0.002f;
		if(m_ship_scal <= 0.05f)	m_ship_scal = 0.05f;
		m_Brightness += 2;
	}

	else if(m_BrightnessFlg == FADE2){
		// ���o����
		Staging2();
		rot = 0.15f;
		m_speed += 0.00005f;
		if(m_speed >= 0.01f)	m_speed = 0.01f;
		m_ship_scal += 0.002f;
		if(m_ship_scal >= 0.3f)	m_ship_scal = 0.3f;
		m_Brightness -= 2;
	}

	// �^�[�Q�b�g�ƂȂ��Ă���f���̕�����10%�����]��
	DXLibMath::FacingTarget(m_Ship.position, m_terget, &m_Ship.facing, rot);
	// �����̌����Ă�������ֈړ�
	m_Ship.position.x += m_Ship.facing.x * m_speed;
	m_Ship.position.y += m_Ship.facing.y * m_speed;
}

void GameSceneStageSelect::Staging(void)
{
	// �I�񂾐��͐^�񒆂�(�g��)���̑��͊O��(�k��)
	for(int i = 0; i < PLANET_MAX; i++)
	{
		if(i == m_id_back){
			m_Planet[i].x += m_st[i].x/255.0f;
			m_Planet[i].y += m_st[i].y/255.0f;
			m_Planet[i].scal += 0.02f;
		}else{
			m_Planet[i].x -= m_st[i].x/500.0f;
			m_Planet[i].y -= m_st[i].y/500.0f;
			m_Planet[i].scal -= 0.002f;
		}
	}
	// �ړI�n��I�񂾐��̒��_��
	m_terget.x = m_Planet[m_id_back].x;
	m_terget.y = m_Planet[m_id_back].y;
}

void GameSceneStageSelect::Staging2(void)
{
	// �I�񂾐��͐^�񒆂�(�g��)���̑��͊O��(�k��)�t
	for(int i = 0; i < PLANET_MAX; i++)
	{
		if(i == m_id_back){
			m_Planet[i].x -= m_st[i].x/255.0f;
			m_Planet[i].y -= m_st[i].y/255.0f;
			m_Planet[i].scal -= 0.02f;
		}else{
			m_Planet[i].x += m_st[i].x/500.0f;
			m_Planet[i].y += m_st[i].y/500.0f;
			m_Planet[i].scal += 0.002f;
		}
	}
	// �f�����߂�����Ƌt�̕����֖ړI�n�̃Z�b�g
	if(m_id_back == 0){		// �^�񒆂̐��̂�(�ςȋ����h�~)
		m_terget.x = 0.8f;
		m_terget.y = 0.3f;
	}
	else{
		m_terget.x = 0.5f + (0.5f - m_Planet[m_id_back].x);
		m_terget.y = 0.5f + (0.5f - m_Planet[m_id_back].y);
	}
}

// ��ʑJ�ڎ��̃f�[�^�̕ۑ�
void GameSceneStageSelect :: Backup(void)
{
	int loop = 0;
	while(loop <= 255){
	// �I�񂾐��͐^�񒆂�(�g��)���̑��͊O��(�k��)
		for(int i = 0; i < PLANET_MAX; i++)
		{
			if(i == m_id_back){
				m_Planet[i].x += m_st[i].x/255.0f;
				m_Planet[i].y += m_st[i].y/255.0f;
				m_Planet[i].scal += 0.02f;
			}else{
				m_Planet[i].x -= m_st[i].x/500.0f;
				m_Planet[i].y -= m_st[i].y/500.0f;
				m_Planet[i].scal -= 0.002f;
			}
		}
		loop += 2;
	}
	// �ړI�n��I�񂾐��̒��_��
	m_terget.x = 0.4f;
	m_terget.y = 0.4f;
	m_terget.z = 0.0f;
}