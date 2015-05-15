#include "Help.h"
#include "../System/DataManager.h"
#include "../System/DxLibMath.h"
#include "../System/GameInput.h"

const char g_Index[8][30] =
{
	"���O��",			
	"���j�b�g",			
	"��",				
	"���j���[�F����",	
	"���j���[�F��������",
	"�q���g",			
	"�u���b�N�ꗗ",	
	"��Ԉُ�ꗗ",		
};

Help::Help(void)
{
}

void Help::Init(void)
{
	DataManager &data = DataManager::GetInstance();
	// �l�̏�����
	m_State = INDEX;
	m_Page = 0;
	m_Index = -1;
	m_Frame = 0;
	m_ScalFlg = false;
	m_M_Scal = 0.55f;
	m_Exist = false;
	m_OffFrame = false;
	m_Help_Button_Scale = 1.0f;
	// �V�ѕ�����
	const DRAW_DATA w_howto[NUM_PAGE] = {  {0.5f, 0.5f, 1.0f, 0.0f, data.Get(DataManager::Description1)},
											{0.5f, 0.5f, 1.0f, 0.0f, data.Get(DataManager::Description2_1)},
											{0.5f, 0.5f, 1.0f, 0.0f, data.Get(DataManager::Description2_2)},
											{0.5f, 0.5f, 1.0f, 0.0f, data.Get(DataManager::Description3)},
											{0.5f, 0.5f, 1.0f, 0.0f, data.Get(DataManager::Description4_1)},
											{0.5f, 0.5f, 1.0f, 0.0f, data.Get(DataManager::Description4_2)},
											{0.5f, 0.5f, 1.0f, 0.0f, data.Get(DataManager::Description5_1)},
											{0.5f, 0.5f, 1.0f, 0.0f, data.Get(DataManager::Description5_2)},
											{0.5f, 0.5f, 1.0f, 0.0f, data.Get(DataManager::Description6)},
											{0.5f, 0.5f, 1.0f, 0.0f, data.Get(DataManager::Description7_1)},
											{0.5f, 0.5f, 1.0f, 0.0f, data.Get(DataManager::Description7_2)},
											{0.5f, 0.5f, 1.0f, 0.0f, data.Get(DataManager::Description8)},
									};
	for(int i=0; i<NUM_PAGE; i++)	
		m_WordHowto[i] = w_howto[i];
	//�g�k��������
	for(int i=0; i<NUM_INDEX; i++)
		m_I_Scale[i] = 1.0f;
	//���ڂ��Ƃ̃y�[�W���ݒ�
	m_IndexPage[ 0] = 1;
	m_IndexPage[ 1] = 2;
	m_IndexPage[ 2] = 1;
	m_IndexPage[ 3] = 2;
	m_IndexPage[ 4] = 2;
	m_IndexPage[ 5] = 1;
	m_IndexPage[ 6] = 2;
	m_IndexPage[ 7] = 1;
}

Help::~Help(void)
{
	SetDrawBright(255, 255, 255);
}

bool Help::Update(void)
{
	GameInput &input = GameInput::GetInstance();
	float x = input.GetXf();
	float y = input.GetYf();

	int nextPage = -1;
	if(m_Exist)
	{
		switch(m_State)
		{
		case INDEX:
			nextPage = UpdateIndex();
			if(nextPage >= 0)
			{
				m_OldPage = -1;		//�O�y�[�W�ۑ�
				m_Page = nextPage;	//���y�[�W�i�[
				m_State = REFERENCE;//�X�e�[�g�ؑ�
				m_PageAlpha = 0;	//��������
			}
			break;
		case REFERENCE:
			m_State = UpdateReference();
			break;
		}
		//����{�^������
		if(Close())
		{
			m_Exist = false;
			m_OffFrame = true;
		}
	}

	//�{�^���̊g�k
	if(x >= 0.9425f && y <= 0.07f)
		m_Help_Button_Scale += (1.3f - m_Help_Button_Scale) * 0.3f;
	else
		m_Help_Button_Scale += (1.0f - m_Help_Button_Scale) * 0.3f;

	return m_Exist;
}
//�ڎ�����
int Help :: UpdateIndex(void)
{
	int	page = 0;
	GameInput &input = GameInput::GetInstance();
	float x = input.GetXf();
	float y = input.GetYf();

	//�ʒu����
	if(x > 0.3125f && x < 0.6875f)
	{
		//Y����
		for(int i=0; i<NUM_INDEX; i++)
		{
			if(y > (0.383f + 0.06667f*(float)i) && y < (0.383f + 0.06667f*(float)(i+1)))
				m_Index = i;
			else
			{
				if(i == 0)
					m_Index = -1;
			}
		}
	}
	else
		m_Index = -1;

	//���ڂ̊g�k
	for(int i=0; i< NUM_INDEX; i++)
	{
		if(i == m_Index)
			m_I_Scale[i] += (1.3f-m_I_Scale[i]) * 0.2f;
		else
			m_I_Scale[i] += (1.0f-m_I_Scale[i]) * 0.2f;
	}

	//�N���b�N�Ői��
	if(	input.GetMouse(GameInput::MouseLeftTrg) && 
		m_Index >= 0 && m_Index < NUM_PAGE)
	{
		//�����܂ł̃y�[�W���΂�
		for(int i=0; i<m_Index; i++)
			page += m_IndexPage[i];
		return page;
	}
	return -1;
}
//���t�@�����X�y�[�W�̍X�V
Help::STATE Help::UpdateReference(void)
{
	int nextPage = m_Page;

	//���l�X�V
	m_PageAlpha += 10;
	if(m_PageAlpha > 255)
		m_PageAlpha = 255;

	//�����ꂽ�{�^�����Ƃ̏���
	switch(UpdatePages())
	{
	case STAY:
		break;
	case PREV:
			nextPage--;
		break;
	case NEXT:
			nextPage++;
		break;
	case BACK:
		m_Index = -1;
		return INDEX;
		break;
	}

	//�y�[�W���ς��΍X�V
	if(nextPage != m_Page)
	{
		m_OldPage = m_Page;	//�O�y�[�W�ۑ�
		m_Page = nextPage;	//���y�[�W�i�[
		m_PageAlpha = 0;	//��������
	}

	return REFERENCE;
}
//���t�@�����X�{�^������
Help::CONTROL Help :: UpdatePages(void)
{
	GameInput &input = GameInput::GetInstance();
	float x = input.GetXf();
	float y = input.GetYf();
	Help::CONTROL ret = STAY;

	//�ʒu����
	//�O�y�[�W�{�^��
	if( m_Page > 0 &&
		x > 0.37f && x < 0.43 &&
		y > 0.91f && y < 0.95)
		ret = PREV;

	//���y�[�W�{�^��
	if( m_Page < NUM_PAGE-1 &&
		x > 0.57f && x < 0.63 &&
		y > 0.91f && y < 0.95)
		ret = NEXT;

	//�߂�{�^��
	if( x > 0.45f && x < 0.55 &&
		y > 0.89f && y < 0.97)
		ret = BACK;

	////�g�k
	//if(!m_ScalFlg){
	//	m_M_Scal += 0.01f;
	//	if(m_M_Scal >= 0.7f)	m_ScalFlg = true;
	//}
	//else{
	//	m_M_Scal -= 0.01f;
	//	if(m_M_Scal <= 0.4f)	m_ScalFlg = false;
	//}
	//�N���b�N�Ői��
	if(input.GetMouse(GameInput::MouseLeftTrg))
		return ret;

	return STAY;
}

//�`�揈��
void Help::Draw(void)
{
	DataManager &data = DataManager::GetInstance();
	GameInput &input = GameInput::GetInstance();

	if(m_Exist)
	{
		//BG
		DXLibMath::DrawRotaGraphResize(	0.5f, 0.5f, 1.0f, 0.0f, 
										DataManager::GetInstance().Get(DataManager::Help_BG), TRUE);
		switch(m_State)
		{
		case INDEX:
			DrawIndex();
			break;
		case REFERENCE:
			DrawReference();
			break;
		}
		//����{�^��
		DXLibMath::DrawRotaGraphResize(0.97f, 0.035f, m_Help_Button_Scale, 0.0f, data.Get(DataManager::Help_Button_Close), TRUE);
	}
	else
		DXLibMath::DrawRotaGraphResize(0.97f, 0.035f, m_Help_Button_Scale, 0.0f, data.Get(DataManager::Play_UI_Play_HelpButton), TRUE);
}
//�ڎ��`��
void Help::DrawIndex(void)
{
	float extend = 1.0f;
	//���x��
	DXLibMath::DrawRotaGraphResize(	0.5f, 0.17f, 1.0f, 0.0f, 
									DataManager::GetInstance().Get(DataManager::Help_Label), TRUE);
	for(int i=0; i<NUM_INDEX; i++)
	{
		DXLibMath::DrawRotaGraphResize(	0.5f, 0.408f + ((float)i * 0.06667f), m_I_Scale[i], 0.0f, 
									DataManager::GetInstance().Get(DataManager::Help_Index), TRUE);
	}
	// �����\��
	int color = GetColor(255, 255, 255);
	for(int i=0; i<NUM_INDEX; i++)
	{
		color = ChangeColor(i);
		//m_Font.DrawFontString(FontManager::FontSet_AZUKI_25 , 280, 230+i*40, (char*)&g_Index[i][0],	400, color);
		m_Font.DrawCenter(FontManager::FontSet_AZUKI_25, 400, 230+i*40, const_cast<char*>(&g_Index[i][0]), color);
	}
}
//�y�[�W�`��
void Help::DrawReference(void)
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);			// ���l��߂�

	//������������ΑO�̂��`�悷��
	if(m_PageAlpha < 255)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - m_PageAlpha);
		if(m_OldPage >= 0 && m_OldPage < NUM_PAGE)
		DXLibMath::DrawRotaGraphResize(	m_WordHowto[m_OldPage].x, m_WordHowto[m_OldPage].y, 
											m_WordHowto[m_OldPage].scal, m_WordHowto[m_OldPage].rot, 
											m_WordHowto[m_OldPage].handle, TRUE);
		
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_PageAlpha);
	}
	//�V�[�g
	DXLibMath::DrawRotaGraphResize(	m_WordHowto[m_Page].x, m_WordHowto[m_Page].y, 
										m_WordHowto[m_Page].scal, m_WordHowto[m_Page].rot, 
										m_WordHowto[m_Page].handle, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);			// ���l��߂�

	//�O�y�[�W�{�^��
	if(m_Page > 0)
		DXLibMath::DrawRotaGraphResize(	0.4f, 0.93f, 
										1.0f, 0.0f, 
										DataManager::GetInstance().Get(DataManager::Help_Button_Prev), TRUE);
	//���y�[�W�{�^��
	if(m_Page < NUM_PAGE-1)
		DXLibMath::DrawRotaGraphResize(	0.6f, 0.93f, 
										1.0f, 0.0f, 
										DataManager::GetInstance().Get(DataManager::Help_Button_Next), TRUE);
	//�߂�{�^��
	DXLibMath::DrawRotaGraphResize(	0.5f, 0.93f, 
									1.0f, 0.0f,
									DataManager::GetInstance().Get(DataManager::Help_Button_Back), TRUE);
}

//�L��������
bool Help::Open(DXLibMath::Vector2 &mouse)
{
	//�N���b�N����
	if(	mouse.x >= 0.9425f && mouse.x < 1.0f &&
		mouse.y <= 0.07f && mouse.y > 0.0f &&
		!m_OffFrame	)
	{
		m_Exist	= true;
		m_Index = -1;
		m_Page = 0;
		m_State = INDEX;
		return true;
	}

	m_OffFrame = false;
	return false;
}
//����������
bool Help::Close(void)
{
	GameInput &input = GameInput::GetInstance();
	float x = input.GetXf();
	float y = input.GetYf();

	if(	input.GetMouse(GameInput::MouseLeftTrg) && 
		x >= 0.9425f && x < 1.0f &&
		y <= 0.07f && y > 0.0f)
		return true;

	return false;
}