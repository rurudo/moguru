#include "DepthSelect.h"
#include "../System/DataManager.h"
#include "../System/GameInput.h"
#include "../System/BlockManager.h"

DepthSelect::DepthSelect(void)
{
	m_Enable = true;
	m_Frame = 0;
	m_State = State_Fall;
	DataManager &data = DataManager::GetInstance();
	data.m_MogllStatus.position.x = 0.617f;
	data.m_MogllStatus.position.y = -0.2f;
}

DepthSelect::~DepthSelect(void)
{
}

//------------------------
// �Q�[���̏���������
void DepthSelect :: Init(void)
{
	DataManager &data = DataManager::GetInstance();

	// �w�i�摜�n���h���i�[
	const PLANET_BACKSTAGE Chikatoshi[NUM_STAGEBACK] =
	{	0.375f,	0.5f,	0.0f,	1.0f,	0.0f,	 0.0f, 0.00001f, 0.0f, 100, 200,	data.Get(DataManager::Stage_Chikatoshi_1), true,
		0.375f,	0.5f,	0.0f,	2.0f,	0.0f,	 0.02f, 0.0f, 0.0f, 0, -10,	data.Get(DataManager::Stage_Chikatoshi_2), true,
		0.375f,	0.5f,	0.0f,	1.0f,	0.0f,	 0.00008f, 0.0f, 0.0f, 0, 200,	data.Get(DataManager::Stage_Chikatoshi_3), true,
		0.375f,	0.5f,	0.0f,	1.0f,	0.0f,	 0.0f, 0.00006f, 0.0f, 150, 300,	data.Get(DataManager::Stage_Chikatoshi_4), true,
		0.375f,	0.5f,	0.0f,	1.0f,	0.0f,	 0.0f, 0.00006f, 0.0f, 150, 300,	data.Get(DataManager::Stage_Chikatoshi_4), false,
		0.375f,	0.5f,	0.0f,	1.0f,	0.0f,	 0.0f, 0.0f, 0.0f, 0, 0,	data.Get(DataManager::Stage_Chikatoshi_Sky), true };
	const PLANET_BACKSTAGE Hyoukai[NUM_STAGEBACK] =
	{	0.375f,	0.5f,	0.0f,	1.0f,	0.0f,	 0.0f, 0.00001f, 0.0f, 100, 300,	data.Get(DataManager::Stage_Hyoukai_1), true,
		0.375f,	0.5f,	0.0f,	1.0f,	0.0f,	 0.013f,  0.0f, 0.0f, 0, -10,	data.Get(DataManager::Stage_Hyoukai_2), true,
		0.375f,	0.5f,	0.0f,	1.0f,	0.0f,	 0.0f, 0.0001f, 0.0f, 0, 240,	data.Get(DataManager::Stage_Hyoukai_3), true,
		0.375f,	0.5f,	0.0f,	1.0f,	0.0f,	 0.0f, 0.00008f, 0.0f, 0, 300,	data.Get(DataManager::Stage_Hyoukai_4), true,
		0.375f,	0.5f,	0.0f,	1.0f,	0.0f,	 0.0f, 0.00006f, 0.0f, 0, 360,	data.Get(DataManager::Stage_Hyoukai_5), true,
		0.375f,	0.5f,	0.0f,	1.0f,	0.0f,	 0.0f, 0.0f, 0.0f, 0, 0,	data.Get(DataManager::Stage_Hyoukai_Sky), true };
	const PLANET_BACKSTAGE Numachi[NUM_STAGEBACK] =
	{	0.375f,	0.5f,	0.0f,	1.0f,	0.0f,	 0.0f, 0.01f, 0.0f, 0, -10,	data.Get(DataManager::Stage_Numachi_1), true,
		0.375f,	0.5f,	0.0f,	1.0f,	0.0f,	 0.0f, 0.00001f, 0.0f, 0, 200,	data.Get(DataManager::Stage_Numachi_2), true,
		0.375f,	0.5f,	0.0f,	1.0f,	0.0f,	 0.00004f,0.0f, 0.0f, 200, 300,	data.Get(DataManager::Stage_Numachi_3), true,
		0.375f,	0.5f,	0.0f,	1.0f,	0.0f,	 0.00002f,0.0f, 0.0f, 0, 300,	data.Get(DataManager::Stage_Numachi_4), true,
		0.375f,	0.5f,	0.0f,	1.0f,	0.0f,	 0.00001f,0.0f, 0.0f, 0, 400,	data.Get(DataManager::Stage_Numachi_5), true,
		0.375f,	0.5f,	0.0f,	1.0f,	0.0f,	 0.0f, 0.0f, 0.0f, 0, 0,	data.Get(DataManager::Stage_Numachi_Sky), true, };
	const PLANET_BACKSTAGE Maguma[NUM_STAGEBACK] =
	{	0.375f,	0.5f,	0.0f,	1.0f,	0.0f,	 0.0f, 0.00001f, 0.0f, 0, 200,	data.Get(DataManager::Stage_Maguma_1), true,
		0.375f,	0.5f,	0.0f,	1.0f,	0.0f,	 0.0f, 0.00006f, 0.0f, 0, 120,	data.Get(DataManager::Stage_Maguma_2), true,
		0.375f,	0.5f,	0.0f,	1.0f,	0.0f,	 0.0f, 0.00012f, 0.0f, 0, 180,	data.Get(DataManager::Stage_Maguma_3), true,
		0.375f,	0.5f,	0.0f,	1.0f,	0.0f,	 0.0f, 0.0002f, 0.0f, 0, 240,	data.Get(DataManager::Stage_Maguma_4), true,
		0.375f,	0.5f,	0.0f,	1.0f,	0.0f,	 0.0f, 0.00006f, 0.0f, 150, 300,	data.Get(DataManager::Stage_Chikatoshi_4), false,
		0.375f,	0.5f,	0.0f,	1.0f,	0.0f,	 0.0f, 0.0f, 0.0f, 0, 0,	data.Get(DataManager::Stage_Maguma_Sky), true, };
	const PLANET_BACKSTAGE Kinmirai[NUM_STAGEBACK] =
	{	0.375f,	0.5f,	0.0f,	1.0f,	0.0f,	 0.0f, 0.0f, 0.0f, 0, 0,	data.Get(DataManager::Stage_Kinmirai_1), true,
		0.375f,	0.5f,	0.0f,	1.0f,	0.0f,	 0.0f, 0.0f, 0.0f, 0, 0,	data.Get(DataManager::Stage_Kinmirai_2), true,
		0.375f,	0.5f,	0.0f,	1.0f,	0.0f,	 0.0f, 0.0f, 0.0f, 0, 0,	data.Get(DataManager::Stage_Kinmirai_3), true,
		0.375f,	0.5f,	0.0f,	1.0f,	0.0f,	 0.0f, 0.0f, 0.0f, 0, 0,	data.Get(DataManager::Stage_Kinmirai_4), true,
		0.375f,	0.5f,	0.0f,	1.0f,	0.0f,	 0.0f, 0.00006f, 0.0f, 150, 300,	data.Get(DataManager::Stage_Chikatoshi_4), false,
		0.375f,	0.5f,	0.0f,	1.0f,	0.0f,	 0.0f, 0.0f, 0.0f, 0, 0,	data.Get(DataManager::Stage_Kinmirai_Sky), true, };

	// �n���h�����
	switch(data.m_SceneInt["StageNo"]){
	case 0:// �n���s�s
		for(int i=0; i<NUM_STAGEBACK; i++)
			m_BackStageDate[i] = Chikatoshi[i];
		break;
	case 1:// �X��
		for(int i=0; i<NUM_STAGEBACK; i++)
			m_BackStageDate[i] = Hyoukai[i];
		break;
	case 2:// ���n
		for(int i=0; i<NUM_STAGEBACK; i++)
			m_BackStageDate[i] = Numachi[i];
		break;
	case 3:// �ΎR
		for(int i=0; i<NUM_STAGEBACK; i++)
			m_BackStageDate[i] = Maguma[i];
		break;
	case 4:// �ߖ���
		for(int i=0; i<NUM_STAGEBACK; i++)
			m_BackStageDate[i] = Kinmirai[i];
		break;
	}

	// ���l�摜�̃n���h���i�[
	const int handle[9] =
	{	data.Get(DataManager::Floor_Number_1),
		data.Get(DataManager::Floor_Number_2),
		data.Get(DataManager::Floor_Number_3),
		data.Get(DataManager::Floor_Number_4),
		data.Get(DataManager::Floor_Number_5),
		data.Get(DataManager::Floor_Number_6),
		data.Get(DataManager::Floor_Number_7),
		data.Get(DataManager::Floor_Number_8),
		data.Get(DataManager::Floor_Number_9) };

	// �n���h���̑��
	for(int i=0; i<9; i++){
		m_Num_Handle[i] = handle[i];
	}

	// �f���̊K�w�����f�[�^
	const PLANET_HIERARCHY hierarchy[5] =
	{	{9, 120, 240, 372, 492,  600, 744, 864, 996, 1080,  600},		// �n���s�s
		{4, 120, 240, 420, 600,  600, 120, 240, 360, 480,  600},		// �X��
		{5, 120, 240, 360, 480,  600, 120, 240, 360, 480,  600},		// ���n
		{5, 100, 200, 300, 400,  500, 100, 200, 300, 400,  500},		// �ΎR
		{5, 120, 240, 360, 480,  600, 120, 240, 360, 480,  600}};	// �ߖ���

	// �f���̊K�w�����f�[�^����
	for(int i=0; i<5; i++)
		HIERARCHY[i] = hierarchy[i];

	Open_Hiera = 0;
	for(int i=0; i<HIERARCHY[data.m_SceneInt["StageNo"]].H_num -1; i++){
		// �f�[�^�Ɗe�f���������Ă���`�F�b�N�|�C���g�̏ƍ�
		if(data.m_SaveData.stageDepth[data.m_SceneInt["StageNo"]] >= HIERARCHY[data.m_SceneInt["StageNo"]].Hier[i])	
			Open_Hiera++;
		else	
			break;
	}

	// �K�w�\���p
	for(int i=0; i<5; i++)	m_BackFlameLoop[i] = 0;
	m_NowFloor = Open_Hiera;
	mouse_st = 0;
	m_NumScal = 1.0f;
	bright_flg = num_st = NON;
	bright = 255;
	m_myship.x = 0.65f;
	m_myship.y = data.m_MogllStatus.position.y;
	m_BlockY = 0.0f;
	m_BlockYBack = 0;
	m_SubX = -0.5f;
	m_BG_WIDTH = 600.0f / 800.0f;
	m_BG_HEIGHT = 600.0f / 600.0f;
	m_numachiAnim = 10;
	m_numachiAnimFlg = false;
	m_GoScale = 1.0f;
}

void DepthSelect::Update( bool Inventory_ST )
{
	const float fallVel = 0.005f;
	const float difference = 0.085f;
	static float back;
	DataManager &data = DataManager::GetInstance();

	if( !m_Enable )
	{
		m_BlockY = (float)(BlockManager::GetInstance().GetDepthOffset());
		m_BlockY -= (float)m_BlockYBack;	// �ǂꂾ���i��ł��邩
		m_BlockYBack += (int)m_BlockY;		// ����v�Z���̎��ɗ��p
		m_BlockY /= 600;					// ��ʂ̍��W�l�ɒu��������
		// ���W�̍X�V
		for(int i=4; i>=0; i--)
			m_BackStageDate[i].Pos.y -= m_BlockY;
		m_myship.y -= m_BlockY;

		// �eBG�̃A�j���[�V����
		BgAnime();

		return;
	}

	// �}�E�X�̍��W��ۑ�
	m_mouse.x = GameInput::GetInstance().GetXf();
	m_mouse.y = GameInput::GetInstance().GetYf();

	switch( m_State )
	{
	case State_Fall:
		{
			// ���o�҂̂����������̂Ŗ�������΂��Ă܂�
			bool skipFlag = GameInput::GetInstance().GetMouse( GameInput::MouseLeftTrg );
			do
			{
				if( data.m_MogllStatus.position.y < 0.525f)
				{
					data.m_MogllStatus.position.y += fallVel;
					m_myship.y = data.m_MogllStatus.position.y - difference;
					if(CheckSoundMem(data.Get( DataManager::SoundSE39 )) == 0)
						PlaySoundMem( data.Get( DataManager::SoundSE39 ), DX_PLAYTYPE_BACK);
				}
				else
				{
					for(int i=0; i<NUM_STAGEBACK-1; i++)
						m_BackStageDate[i].Pos.y -= fallVel;	// BG�X�N���[��
					float x, y;
					DXLibMath::ConvertScreenToBlock( 0.0f, fallVel, &x, &y );
					BlockManager::GetInstance().AddDepth( y );
					if( m_Frame > 63 )
					{
						StopSoundMem(data.Get( DataManager::SoundSE39 ));
						PlaySoundMem( data.Get( DataManager::SoundSE40 ), DX_PLAYTYPE_BACK);//�v�V���[
						m_State = State_Product;
						m_Frame = 0;
					}
					else if(CheckSoundMem(data.Get( DataManager::SoundSE39 )) == 0)
						PlaySoundMem( data.Get( DataManager::SoundSE39 ), DX_PLAYTYPE_BACK);
					m_Frame++;
				}
			}
			while( skipFlag && m_State == State_Fall );
		}
		break;
	case State_Product:
		// �^�񒆂܂ŗ�����
		if(data.m_MogllStatus.position.x <= 0.45f * 0.75f && data.m_MogllStatus.position.y >= m_myship.y + difference){
			data.m_MogllStatus.position.x = 0.45f * 0.75f;
			data.m_MogllStatus.position.y = m_myship.y + difference;
			m_State = State_Select;
			PlaySoundMem( data.Get( DataManager::SoundSE55 ), DX_PLAYTYPE_BACK);//���O�����n���Đ�

			// �u���b�N�̈ʒu���擾
			back = (float)BlockManager::GetInstance().GetDepthOffset();
		}
		else{
			// �Ε�����
			data.m_MogllStatus.position.x = m_Frame * -0.05f * cos(30.0f) + m_myship.x;
			data.m_MogllStatus.position.y = (m_Frame * 0.0205f * sin(30.0f)) + (0.001f * m_Frame * m_Frame / 2) + (m_myship.y + 0.08f);
			m_Frame++;
		}
		break;
	case State_Select:	// �J�n��
		if(Inventory_ST == false)	Selection();	// �C���x���g���J���Ă鎞�͖���
		break;
	case State_Up:
		if( data.m_MogllStatus.position.y < 0.25f )	// ���O���̕\����������
		{
			data.m_MogllStatus.position.y += fallVel;
			if(data.m_MogllStatus.position.y >= 0.25f)
				data.m_MogllStatus.position.y = 0.25f;
		}
		else if( data.m_MogllStatus.position.y == 0.25f )
		{
			m_Enable = false;
		}
		else
		{
			float x, y;
			DXLibMath::ConvertScreenToBlock( 0.0f, fallVel, &x, &y );
			BlockManager::GetInstance().AddDepth( y );

			// ���W�̍X�V
			data.m_MogllStatus.position.y -= fallVel - 0.00045f;						// ���O��

			m_BlockY = (float)(BlockManager::GetInstance().GetDepthOffset());
			m_BlockY -= (float)back;			// �ǂꂾ���i��ł��邩
			back += (int)m_BlockY;				// ����v�Z���̎��ɗ��p
			m_BlockY /= 600;					// ��ʂ̍��W�l�ɒu��������
			// ���W�̍X�V
			for(int i=4; i>=0; i--)
				m_BackStageDate[i].Pos.y -= m_BlockY;
			m_myship.y -= m_BlockY;

			// �u���b�N�̈ʒu���擾
			m_BlockYBack = BlockManager::GetInstance().GetDepthOffset();
		}

		float mogx, mogy;
		// �n�ʂ��@��
		DXLibMath::ConvertScreenToBlock(data.m_MogllStatus.position.x, data.m_MogllStatus.position.y, &mogx, &mogy);
		m_Dig.OPUpdate(mogy);
		// �u���b�N�X�V
		BlockManager::GetInstance().Update();

		break;
	default:
		break;
	}

	// �eBG�̃A�j���[�V����
	BgAnime();
}

// �`��
void DepthSelect::Draw(void)
{
	DataManager &data = DataManager::GetInstance();

	if( !m_Enable )
	{	// �F���D
		DXLibMath::DrawRotaGraphResize(m_myship.x, m_myship.y, 0.8f, 0.0f, data.Get(DataManager::Spaceship), TRUE);
		// �w�i
		BgDraw();
		return;
	}

	// �w�i
	BgDraw();

	switch( m_State )
	{
	case State_Fall:
		DXLibMath::DrawExtendGraphResize( data.m_MogllStatus.position.x, data.m_MogllStatus.position.y, 0.07f, 0.1f,
			data.Get( DataManager::GG_PLAYER_Drill01 ), TRUE );
		break;
	case State_Product:
		break;
	case State_Select:
		if(bright_flg == NON){
			if(Open_Hiera != 0){
				if(mouse_st == 1 && st_flg == St_Select)
					DXLibMath::DrawGraphResize(0.42f, 0.32f, data.Get(DataManager::Play_Button_Floor_Down), TRUE);			// �K�w�{�^���_�E��
				else
					DXLibMath::DrawGraphResize(0.42f, 0.32f, data.Get(DataManager::Play_Button_Floor), TRUE);				// �K�w�{�^��
			}
			//if(mouse_st == 1 && st_flg == St_Go)
			//	DXLibMath::DrawGraphResize(0.16f, 0.32f, data.Get(DataManager::Play_Button_Go_Down), TRUE);					// �f�n�{�^���_�E��
			//else
			DXLibMath::DrawRotaGraphResize( 0.243f, 0.403f, m_GoScale, 0.0f,
			data.Get(DataManager::Play_Button_Go), TRUE );
			//DXLibMath::DrawGraphResize(0.16f, 0.32f, data.Get(DataManager::Play_Button_Go), TRUE);						// �f�n�{�^��
			if(Open_Hiera != 0)
				DXLibMath::DrawRotaGraphResize(0.52f, 0.4f, m_NumScal, 0.0f, m_Num_Handle[m_NowFloor], TRUE);				// ����
		}
		break;
	case State_Up:
		break;
	default:
		break;
	}
}

void DepthSelect::ChallengeDraw()
{
	DataManager &data = DataManager::GetInstance();
	double size = 1.0f + 0.2f * sin( 3.1415 / 18.0 * m_Challenge.animCount );
	DrawRotaGraph(100, 400, size, 0.0f, data.Get( DataManager::Play_Challenge ), TRUE );
}

// �F���D�`��
void DepthSelect::SpacecraftDraw(){
	DataManager &data = DataManager::GetInstance();
	if(bright_flg == NON)
		DXLibMath::DrawRotaGraphResize(m_myship.x, m_myship.y, 0.8f, 0.0f, data.Get(DataManager::Spaceship), TRUE);			// �F���D
}

// �w�i�`��
void DepthSelect::BgDraw(){
	DataManager &data = DataManager::GetInstance();

	// �w�i
	for(int i=(NUM_STAGEBACK-1); i>=0; i--){
		if(m_BackStageDate[i].isValid){
			switch(data.m_SceneInt["StageNo"]){
			case 0:// �n���s�s
				if(i == 1)
					DXLibMath::DrawRotaGraphResize(m_BackStageDate[i].Pos.x-(m_BG_WIDTH*m_BackStageDate[i].Scal), m_BackStageDate[i].Pos.y, m_BackStageDate[i].Scal, m_BackStageDate[i].Rot, m_BackStageDate[i].Handle, TRUE);

				DXLibMath::DrawRotaGraphResize(m_BackStageDate[i].Pos.x, m_BackStageDate[i].Pos.y, m_BackStageDate[i].Scal, m_BackStageDate[i].Rot, m_BackStageDate[i].Handle, TRUE);
				break;
			case 1:// �X��
				if(i == 1)
					DXLibMath::DrawRotaGraphResize(m_BackStageDate[i].Pos.x-(m_BG_WIDTH*m_BackStageDate[i].Scal), m_BackStageDate[i].Pos.y, m_BackStageDate[i].Scal, m_BackStageDate[i].Rot, m_BackStageDate[i].Handle, TRUE);

				DXLibMath::DrawRotaGraphResize(m_BackStageDate[i].Pos.x, m_BackStageDate[i].Pos.y, m_BackStageDate[i].Scal, m_BackStageDate[i].Rot, m_BackStageDate[i].Handle, TRUE);
				break;
			case 2:// ���n
				if(i == 0)
				{
					if(m_numachiAnimFlg)
						m_BackStageDate[i].Handle = data.Get(DataManager::Stage_Numachi_1_ani);
					else
						m_BackStageDate[i].Handle = data.Get(DataManager::Stage_Numachi_1);

					//DXLibMath::DrawRotaGraphResize(m_BackStageDate[i].Pos.x-(m_BG_WIDTH*m_BackStageDate[i].Scal), m_BackStageDate[i].Pos.y, m_BackStageDate[i].Scal, m_BackStageDate[i].Rot, m_BackStageDate[i].Handle, TRUE);
					DXLibMath::DrawRotaGraphResize(m_BackStageDate[i].Pos.x, m_BackStageDate[i].Pos.y-(m_BG_HEIGHT*m_BackStageDate[i].Scal), m_BackStageDate[i].Scal, m_BackStageDate[i].Rot, m_BackStageDate[i].Handle, TRUE);
				}
				DXLibMath::DrawRotaGraphResize(m_BackStageDate[i].Pos.x, m_BackStageDate[i].Pos.y, m_BackStageDate[i].Scal, m_BackStageDate[i].Rot, m_BackStageDate[i].Handle, TRUE);
				break;
			case 3:// �ΎR
				DXLibMath::DrawRotaGraphResize(m_BackStageDate[i].Pos.x, m_BackStageDate[i].Pos.y, m_BackStageDate[i].Scal, m_BackStageDate[i].Rot, m_BackStageDate[i].Handle, TRUE);
				break;
			case 4:// �ߖ���
				DXLibMath::DrawRotaGraphResize(m_BackStageDate[i].Pos.x, m_BackStageDate[i].Pos.y, m_BackStageDate[i].Scal, m_BackStageDate[i].Rot, m_BackStageDate[i].Handle, TRUE);
				break;
			}
		}
	}

}

// �I��
void DepthSelect::Selection(void){
	DataManager &data = DataManager::GetInstance();
	int floor = 0;	// �K�w����̐� �{���|��

	// �}�E�X�̈ʒu����ǂ̃{�^���ɂ���̂����擾
	if(m_mouse.y >= 0.32f && m_mouse.y <= 0.32f+0.166f){	// y���W�͕ς��Ȃ�
		if(m_mouse.x >= 0.16f && m_mouse.x <= 0.16f+0.163f){
			if( st_flg != St_Go )
			{
				st_flg = St_Go;
				PlaySoundMem( DataManager::GetInstance().Get( DataManager::SoundSE07 ), DX_PLAYTYPE_BACK);
			}
		}
		else if(m_mouse.x >= 0.42f && m_mouse.x <= 0.42f+0.163f && Open_Hiera != 0){
			if( st_flg != St_Select )
			{
				st_flg = St_Select;
				PlaySoundMem( DataManager::GetInstance().Get( DataManager::SoundSE07 ), DX_PLAYTYPE_BACK);
			}
		}
		else	st_flg = St_Non;	// ��O����
	}
	else		st_flg = St_Non;	// ��O����

	//�{�^���̊g�k
	if(st_flg == St_Go)
		m_GoScale += (1.2f - m_GoScale)*0.4f;
	else
		m_GoScale += (1.0f - m_GoScale)*0.4f;

	// �N���b�N��
	if( GameInput::GetInstance().GetMouse( GameInput::MouseLeftTrg ))
	{// �K�w�I��
		// �������s
		if(st_flg != St_Non){
			if(Open_Hiera != 0)
				PlaySoundMem( DataManager::GetInstance().Get( DataManager::SoundSE10 ), DX_PLAYTYPE_BACK);
			if(st_flg == St_Select && num_st == NON){
				num_st = ON;
				m_floor = 1;// �K�w��i�܂��鐔�ݒ�
			}
			mouse_st = 1;
		}
	}
	// �����[�X��
	if(GameInput::GetInstance().GetMouse( GameInput::MouseLeftRls ) && mouse_st == 1){
		if(st_flg != St_Non){
			if(st_flg == St_Go){
				if(m_NowFloor != 0){
					bright_flg = ON;
				}
				else{
					m_State = State_Up;
				}
			}
		}
		mouse_st = 0;
	}
	//�}�E�X�z�C�[����]��
	if(floor == 0  && Open_Hiera != 0)
	{
		//�㉺����
		floor += GameInput::GetInstance().GetMouseWheelUp() * -1;
		floor += GameInput::GetInstance().GetMouseWheelDown() * 1;
		if(floor != 0)
		{
			// �������s
			if(num_st == NON){
				PlaySoundMem( DataManager::GetInstance().Get( DataManager::SoundSE10 ), DX_PLAYTYPE_BACK);
				num_st = ON;
				m_floor = floor;
			}
		}
	}
	
	//�����ύX�������s
	if(num_st != NON){
		NumberScal();
	}
	if(bright_flg != NON){
		Black();
	}
}

// �����̊g�k
void DepthSelect::NumberScal(void){
	// �k��
	if(num_st == ON){
		m_NumScal -= 0.1f;
		if(m_NumScal <= 0.0f){
			num_st = OFF;
			m_NumScal = 0.0f;
			m_NowFloor += m_floor;	//�K�w������
			m_floor = 0;
			//�͈͂��z�����烋�[�v
			if(m_NowFloor > Open_Hiera)		m_NowFloor = 0;
			if(m_NowFloor < 0)				m_NowFloor = Open_Hiera;
		}
	}
	// �g��
	else if(num_st == OFF){
		m_NumScal += 0.1f;
		if(m_NumScal >= 1.0f){
			num_st = NON;
			m_NumScal = 1.0f;
		}
	}
}

// �Ö�
void DepthSelect::Black(void){
	int	row_num	= 13;	// ���s�O����ǂݍ��ނ�
	DataManager &data = DataManager::GetInstance();
	// �k��
	if(bright_flg == ON){
		bright -= 10;
		if(bright <= 0){
			// ���ԃ��[�v�Ó]������
			bright_flg = OFF;
			bright = 0;
			for(int i=HIERARCHY[data.m_SceneInt["StageNo"]].Hier[m_NowFloor-1] - row_num; i<HIERARCHY[data.m_SceneInt["StageNo"]].Hier[m_NowFloor-1]; i++){
				BlockManager::GetInstance().LoadLine(i);
			}
			for(int i = 0; i < 30; i++)
			{
				// �S�K�w�̊����Ń��j�b�g��������
				data.m_MogllStatus.unitCount[i] = 99 / HIERARCHY[data.m_SceneInt["StageNo"]].H_num * (HIERARCHY[data.m_SceneInt["StageNo"]].H_num - m_NowFloor);
			}
			data.m_MogllStatus.position.y = -0.1f;
		}
	}
	// �g��
	else if(bright_flg == OFF){
		bright += 10;
		if(bright >= 255){
			bright = 255;
			m_State = State_Up;
		}
	}
	SetDrawBright(bright, bright, bright);
}

// �w�i�A�j���[�V����
void DepthSelect::BgAnime(void){
	for(int i=0; i< NUM_STAGEBACK; i++)
	{
		if(m_BackStageDate[i].isValid)
		{
			//�ړ�
			m_BackStageDate[i].Pos.x += m_BackStageDate[i].Speed.x;
			m_BackStageDate[i].Pos.y += m_BackStageDate[i].Speed.y;
			//�͈͐����i�t���[�����j
			if(m_BackStageDate[i].FRAME_CNT > 0)
			{
				m_BackStageDate[i].frame_cnt--;
				if(m_BackStageDate[i].frame_cnt <= 0)
				{
					m_BackStageDate[i].Speed.x = -m_BackStageDate[i].Speed.x;
					m_BackStageDate[i].Speed.y = -m_BackStageDate[i].Speed.y;
					m_BackStageDate[i].frame_cnt = m_BackStageDate[i].FRAME_CNT;//�t���[�������Z�b�g
				}
			}
			else if(m_BackStageDate[i].FRAME_CNT == -10)
			{
				if(m_BackStageDate[i].Speed.x != 0.0f)
				{
					if(m_BackStageDate[i].Pos.x > (m_BG_WIDTH *1.5f) * m_BackStageDate[i].Scal ) 
						m_BackStageDate[i].Pos.x = (m_BG_WIDTH*0.5f) * m_BackStageDate[i].Scal;
					if(m_BackStageDate[i].Pos.x < (m_BG_WIDTH*0.5f) * m_BackStageDate[i].Scal  ) 
						m_BackStageDate[i].Pos.x = (m_BG_WIDTH *1.5f) * m_BackStageDate[i].Scal;
				}
				if(m_BackStageDate[i].Speed.y != 0.0f)
				{
					if( m_BackStageDate[i].Pos.y > (m_BG_HEIGHT *1.5f) * m_BackStageDate[i].Scal ) 
						m_BackStageDate[i].Pos.y = (m_BG_HEIGHT*0.5f) * m_BackStageDate[i].Scal;
					if( m_BackStageDate[i].Pos.y < (m_BG_HEIGHT*0.5f) * m_BackStageDate[i].Scal  ) 
						m_BackStageDate[i].Pos.y = (m_BG_HEIGHT *1.5f) * m_BackStageDate[i].Scal;
				}
			}
		}
	}

	//���n�p�A�j���[�V�����J�E���^
	if(--m_numachiAnim < 0)
	{
		m_numachiAnim = 10;
		m_numachiAnimFlg = !m_numachiAnimFlg;
	}
}