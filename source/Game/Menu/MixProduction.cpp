//========================================================================
//	@file		MixProduction.cpp
//	@note		�����������o
//	@author		RyotaUehara
//========================================================================
//------------------------------------------------------------------------
//	IncludeHeader
//------------------------------------------------------------------------
#include "../System/GameInput.h"
#include "GameMenu.h"
//#include "MixProduction.h"
#include "MenuIconSort.h"
#include "MixTreeData.h"

//------------------------------------------------------------------------
//	Const
//------------------------------------------------------------------------
const int		MixProduction :: cm_WhiteAlpha			= 100;
const int		MixProduction :: cm_CircleAlpha			= 100;
//const int		MixProduction :: cm_DivisionHermite		= 10;			//�G���~�[�g
const float		MixProduction :: cm_MaxExpansion		= 2.0f;			//�g��ő�{
const float		MixProduction :: cm_MaxExpansionPlus	= (cm_MaxExpansion - 1.0f) / Time_Finish;		//�g��ő�{

//------------------------------------------------------------------------
//	Constructor
//------------------------------------------------------------------------
MixProduction :: MixProduction(void)
{
	Init();
}
MixProduction :: ~MixProduction(void)
{
	Release();
}
//------------------------------------------------------------------------
//	@fn		Init
//	@brief	����������
//------------------------------------------------------------------------
void MixProduction :: Init(void){
	m_Step = None;
	m_Content = None;
	m_Time = 0;
	m_Enable = false;
	m_Draw = false;

	m_RootId = -1;
	m_RootType = -1;

	Reset();
}
//------------------------------------------------------------------------
//	@fn		Update
//	@brief	�X�V����
//------------------------------------------------------------------------
bool MixProduction :: Update(void){
	if(m_Enable){
		m_Draw = true;

		StepFirstEmission();
		StepSecondEmission();

		switch(m_Step){
		case FEmission:
			if(m_Time < Time_FEmission){
				m_Time++;
			}
			else{
				m_Time = 0;
				m_Step++;
			}
			break;
		case SEmission:
			if(m_Time < Time_SEmission){
				m_Time++;
			}
			else{
				m_Time = 0;
				m_Step++;
			}
			break;
		case Start:
			if(m_Time == 0)
				StepStart();
			if(m_Time < Time_Start){
				m_Time++;
			}
			else{
				m_Time = 0;
				m_Step++;
			}
			break;
		case Preparation:
			if(m_Time < Time_Start){
				StepPreparation();
				m_Time++;
			}
			else{
				m_Time = 0;
				m_Step++;
			}
			break;
		case Run:
			if(m_Time < Time_Run){
				StepRun();
				m_Time++;
			}
			else{
				if(m_Content == Break){
					Init();
					return false;
				}
				else if(m_Content == Mix){
					m_Circle.data.position = m_Main.position;
					m_Circle.data.position.x += GameMenu::cm_OneFrameWidth/2;
					m_Circle.data.position.y += GameMenu::cm_OneFrameHeight/2;
					m_Circle.data.flag = true;
					m_Circle.data.alpha = 100;
				}
				m_Time = 0;
				m_Step++;
			}
			break;
		case Finish:
			if(m_Time < Time_Finish){
				StepFinish();
				m_Time++;
			}
			else{
				Init();
				return false;
			}
			break;
		}

		if(GameInput::GetInstance().GetMouse(GameInput::MouseLeftTrg)){
			Init();
			//StopSoundMem(DataManager::GetInstance().Get( DataManager::SoundSE50 ));
			return false;
		}

		return true;
	}

	return false;
}
//------------------------------------------------------------------------
//	@fn		Release
//	@brief	�������
//------------------------------------------------------------------------
void MixProduction :: Release(void){
}
//------------------------------------------------------------------------
//	@fn		
//	@brief	����
//------------------------------------------------------------------------
int MixProduction :: ReverseGetID(int id,char type){
	switch(type){
	case 0:
		for(int i=0;i<60;i++){
			if(SORT_ItemIconSortList[i] == id)
				return i;
		}
		break;
	case 1:
		for(int i=0;i<30;i++){
			if(SORT_UnitIconSortList[i] == id)
				return i;
		}
		break;
	}
	return -1;
}
//------------------------------------------------------------------------
//	@fn		StepFirstEmission
//	@brief	��ꔭ���X�e�b�v����
//------------------------------------------------------------------------
void MixProduction :: StepFirstEmission(void){
	static int l_time = 0;
	static int l_num = 0;
	float l_work;

	if(m_Step == FEmission){
		//�c���[�̔ԍ��̎擾
		for(int i=0;i<cm_MixTreeNum;i++){
			if(m_MixTreeData[i].main.id == m_RootId && m_MixTreeData[i].main.type == m_RootType){
				l_num = i;
				break;
			}
		}
		if(m_Content == Mix){
			//�f�ނ̈ʒu���v�Z
			for(int i=0;i<4;i++){
				switch(m_MixTreeData[l_num].Material[i].type){
				case Equipment:
					//x���W�̌v�Z
					l_work = ReverseGetID(m_MixTreeData[l_num].Material[i].id,m_MixTreeData[l_num].Material[i].type) % 10 * GameMenu::cm_OneFrameWidth;
					m_Material[i].position.x = GameMenu::cm_EquipmentUIXPos + l_work;
					//y���W�̌v�Z
					l_work = ReverseGetID(m_MixTreeData[l_num].Material[i].id,m_MixTreeData[l_num].Material[i].type) / 10 * GameMenu::cm_OneFrameHeight;
					m_Material[i].position.y = GameMenu::cm_EquipmentUIYPos + GameMenu::cm_BackYMargin + l_work;
					m_Material[i].flag = true;
					m_Material[i].alpha = cm_WhiteAlpha;
					break;
				case Unit:
					//x���W�̌v�Z
					l_work = ReverseGetID(m_MixTreeData[l_num].Material[i].id,m_MixTreeData[l_num].Material[i].type) % 10 * GameMenu::cm_OneFrameWidth;
					m_Material[i].position.x = GameMenu::cm_UnitUIXPos + l_work;
					//y���W�̌v�Z
					l_work = ReverseGetID(m_MixTreeData[l_num].Material[i].id,m_MixTreeData[l_num].Material[i].type)  / 10 * GameMenu::cm_OneFrameHeight;
					m_Material[i].position.y = GameMenu::cm_UnitUIYPos + GameMenu::cm_BackYMargin + l_work;
					m_Material[i].flag = true;
					m_Material[i].alpha = cm_WhiteAlpha;
					break;
				default:
					i += 4;
					break;
				}
			}
		}
		else if(m_Content == Break){
			switch(m_MixTreeData[l_num].main.type){
			case Equipment:
				//x���W�̌v�Z
				l_work = ReverseGetID(m_MixTreeData[l_num].main.id,m_MixTreeData[l_num].main.type) % 10 * GameMenu::cm_OneFrameWidth;
				m_Main.position.x = GameMenu::cm_EquipmentUIXPos + l_work;
				//y���W�̌v�Z
				l_work = ReverseGetID(m_MixTreeData[l_num].main.id,m_MixTreeData[l_num].main.type) / 10 * GameMenu::cm_OneFrameHeight;
				m_Main.position.y = GameMenu::cm_EquipmentUIYPos + GameMenu::cm_BackYMargin + l_work;
				break;
			case Unit:
				//x���W�̌v�Z
				l_work = ReverseGetID(m_MixTreeData[l_num].main.id,m_MixTreeData[l_num].main.type) % 10 * GameMenu::cm_OneFrameWidth;
				m_Main.position.x = GameMenu::cm_UnitUIXPos + l_work;
				//y���W�̌v�Z
				l_work = ReverseGetID(m_MixTreeData[l_num].main.id,m_MixTreeData[l_num].main.type) / 10 * GameMenu::cm_OneFrameHeight;
				m_Main.position.y = GameMenu::cm_UnitUIYPos + GameMenu::cm_BackYMargin + l_work;
				break;
			}
			m_Main.flag = true;
			m_Main.alpha = cm_WhiteAlpha;
		}
	}
}
//------------------------------------------------------------------------
//	@fn		StepSecondEmission
//	@brief	��񔭌��X�e�b�v����
//------------------------------------------------------------------------
void MixProduction :: StepSecondEmission(void){
	static int l_num = 0;
	float l_work;

	if(m_Step >= SEmission){
		//�c���[�̔ԍ��̎擾
		for(int i=0;i<cm_MixTreeNum;i++){
			if(m_MixTreeData[i].main.id == m_RootId && m_MixTreeData[i].main.type == m_RootType){
				l_num = i;
				break;
			}
		}
		if(m_Content == Mix){
			switch(m_MixTreeData[l_num].main.type){
			case Equipment:
				//x���W�̌v�Z
				l_work = (ReverseGetID(m_MixTreeData[l_num].main.id,m_MixTreeData[l_num].main.type) % 10) * GameMenu::cm_OneFrameWidth;
				m_Main.position.x = GameMenu::cm_EquipmentUIXPos + l_work;
				//y���W�̌v�Z
				l_work = (ReverseGetID(m_MixTreeData[l_num].main.id,m_MixTreeData[l_num].main.type) / 10) * GameMenu::cm_OneFrameHeight;
				m_Main.position.y = GameMenu::cm_EquipmentUIYPos + GameMenu::cm_BackYMargin + l_work;
				break;
			case Unit:
				//x���W�̌v�Z
				l_work = ReverseGetID(m_MixTreeData[l_num].main.id,m_MixTreeData[l_num].main.type) % 10 * GameMenu::cm_OneFrameWidth;
				m_Main.position.x = GameMenu::cm_UnitUIXPos + l_work;
				//y���W�̌v�Z
				l_work = ReverseGetID(m_MixTreeData[l_num].main.id,m_MixTreeData[l_num].main.type) / 10 * GameMenu::cm_OneFrameHeight;
				m_Main.position.y = GameMenu::cm_UnitUIYPos + GameMenu::cm_BackYMargin + l_work;
				break;
			}
			m_Main.flag = true;
			m_Main.alpha = cm_WhiteAlpha;
		}
		else if(m_Content == Break){
			//�f�ނ̈ʒu���v�Z
			for(int i=0;i<4;i++){
				switch(m_MixTreeData[l_num].Material[i].type){
				case Equipment:
					//x���W�̌v�Z
					l_work = ReverseGetID(m_MixTreeData[l_num].Material[i].id,m_MixTreeData[l_num].Material[i].type) % 10 * GameMenu::cm_OneFrameWidth;
					m_Material[i].position.x = GameMenu::cm_EquipmentUIXPos + l_work;
					//y���W�̌v�Z
					l_work = ReverseGetID(m_MixTreeData[l_num].Material[i].id,m_MixTreeData[l_num].Material[i].type) / 10 * GameMenu::cm_OneFrameHeight;
					m_Material[i].position.y = GameMenu::cm_EquipmentUIYPos + GameMenu::cm_BackYMargin + l_work;
					m_Material[i].flag = true;
					m_Material[i].alpha = cm_WhiteAlpha;
					break;
				case Unit:
					//x���W�̌v�Z
					l_work = ReverseGetID(m_MixTreeData[l_num].Material[i].id,m_MixTreeData[l_num].Material[i].type) % 10 * GameMenu::cm_OneFrameWidth;
					m_Material[i].position.x = GameMenu::cm_UnitUIXPos + l_work;
					//y���W�̌v�Z
					l_work = ReverseGetID(m_MixTreeData[l_num].Material[i].id,m_MixTreeData[l_num].Material[i].type) / 10 * GameMenu::cm_OneFrameHeight;
					m_Material[i].position.y = GameMenu::cm_UnitUIYPos + GameMenu::cm_BackYMargin + l_work;
					m_Material[i].flag = true;
					m_Material[i].alpha = cm_WhiteAlpha;
					break;
				default:
					i += 4;
					break;
				}
			}
		}
	}
}
//------------------------------------------------------------------------
//	@fn		StepStart
//	@brief	�X�^�[�g�X�e�b�v����
//------------------------------------------------------------------------
void MixProduction :: StepStart(void){
	if(m_Content == Mix){
		//�f�ނ̈ʒu���v�Z
		for(int i=0;i<4;i++){
			m_Sphere[i].data = m_Material[i];
			m_Sphere[i].data.position.x += GameMenu::cm_OneFrameWidth/2;
			m_Sphere[i].data.position.y += GameMenu::cm_OneFrameHeight/2;
			m_Sphere[i].velocity.x = (m_Main.position.x - m_Material[i].position.x) / Time_Run;
			m_Sphere[i].velocity.y = (m_Main.position.y - m_Material[i].position.y) / Time_Run;
		}
	}
	else if(m_Content == Break){
		for(int i=0;i<4;i++){
			m_Sphere[i].data = m_Main;
			m_Sphere[i].data.flag = m_Material[i].flag;
			m_Sphere[i].data.position.x += GameMenu::cm_OneFrameWidth/2;
			m_Sphere[i].data.position.y += GameMenu::cm_OneFrameHeight/2;
			m_Sphere[i].velocity.x = (m_Material[i].position.x - m_Main.position.x) / Time_Run;
			m_Sphere[i].velocity.y = (m_Material[i].position.y - m_Main.position.y) / Time_Run;
		}
	}
}
//------------------------------------------------------------------------
//	@fn		StepPreparation
//	@brief	�����X�e�b�v����
//------------------------------------------------------------------------
void MixProduction :: StepPreparation(void){
	for(int i=0;i<4;i++){
		m_Sphere[i].data.position.y -= 0.1f / Time_Preparation;
	}
}
//------------------------------------------------------------------------
//	@fn		StepRun
//	@brief	���s�X�e�b�v����
//------------------------------------------------------------------------
void MixProduction :: StepRun(void){
	for(int i=0;i<4;i++){
		m_Sphere[i].data.position.x += m_Sphere[i].velocity.x;
		m_Sphere[i].data.position.y += m_Sphere[i].velocity.y;
	}
}
//------------------------------------------------------------------------
//	@fn		StepFinish
//	@brief	�����X�e�b�v����
//------------------------------------------------------------------------
void MixProduction :: StepFinish(void){
	
	m_Circle.data.alpha += (255 - cm_CircleAlpha) / Time_Finish;
	m_Circle.expansion += cm_MaxExpansionPlus;
}

//------------------------------------------------------------------------
//	@fn		Draw
//	@brief	�`�揈��
//------------------------------------------------------------------------
void MixProduction :: Draw(void){
	if(m_Draw){
		DrawFirstEmission();
		DrawSecondEmission();
		DrawStart();
		DrawFinish();
	}
}
//------------------------------------------------------------------------
//	@fn		DrawFirstEmission
//	@brief	��ꔭ���`��
//------------------------------------------------------------------------
void MixProduction :: DrawFirstEmission(void){
	if(m_Step >= FEmission){
		//���Â�
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);									//���ߗ��̃Z�b�g
		DXLibMath::DrawBoxResize(0.0f, 0.0f, 1.0f, 1.0f, GetColor(0, 0, 0), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);									//���ߗ��̃Z�b�g

		switch(m_Content){
		case Mix:
			for(int i=0;i<4;i++){
				if(m_Material[i].flag){
					SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_Material[i].alpha);				//���ߗ��̃Z�b�g
					DXLibMath::DrawBoxResize(static_cast<float>(m_Material[i].position.x),static_cast<float>(m_Material[i].position.y), 
						GameMenu::cm_OneFrameWidth, GameMenu::cm_OneFrameHeight, GetColor(255,255,255), TRUE);
					SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);								//���ߗ��̃Z�b�g
				}
				else
					break;
			}
			break;
		case Break:
			if(m_Main.flag){
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_Main.alpha);							//���ߗ��̃Z�b�g
				DXLibMath::DrawBoxResize(static_cast<float>(m_Main.position.x),static_cast<float>(m_Main.position.y), 
					GameMenu::cm_OneFrameWidth, GameMenu::cm_OneFrameHeight, GetColor(255,255,255), TRUE);
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);									//���ߗ��̃Z�b�g
			}
			break;
		}
	}
}
//------------------------------------------------------------------------
//	@fn		DrawSecondEmission
//	@brief	��񔭌��`��
//------------------------------------------------------------------------
void MixProduction :: DrawSecondEmission(void){
	if(m_Step >= SEmission){
		switch(m_Content){
		case Mix:
			if(m_Main.flag){
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_Main.alpha);							//���ߗ��̃Z�b�g
				DXLibMath::DrawBoxResize(static_cast<float>(m_Main.position.x),static_cast<float>(m_Main.position.y), 
					GameMenu::cm_OneFrameWidth, GameMenu::cm_OneFrameHeight, GetColor(255,255,255), TRUE);
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);									//���ߗ��̃Z�b�g
			}
			break;
		case Break:
			for(int i=0;i<4;i++){
				if(m_Material[i].flag){
					SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_Material[i].alpha);				//���ߗ��̃Z�b�g
					DXLibMath::DrawBoxResize(static_cast<float>(m_Material[i].position.x),static_cast<float>(m_Material[i].position.y), 
						GameMenu::cm_OneFrameWidth, GameMenu::cm_OneFrameHeight, GetColor(255,255,255), TRUE);
					SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);								//���ߗ��̃Z�b�g
				}
				else
					break;
			}
			break;
		}
	}
}
//------------------------------------------------------------------------
//	@fn		DrawStart
//	@brief	�X�^�[�g�`��
//------------------------------------------------------------------------
void MixProduction :: DrawStart(void){
	DataManager& data = DataManager::GetInstance();

	if(m_Step >= Start){
		for(int i=0;i<4;i++){
			if(m_Sphere[i].data.flag)
				DXLibMath::DrawExtendGraphResize(	static_cast<float>(m_Sphere[i].data.position.x)-20/800.0f,static_cast<float>(m_Sphere[i].data.position.y)-5/600.0f, 
													(float)(40/800.0f), (float)(40/600.0f), data.GetGraphicGroupData(DataManager::GG_BULLET_NORMAL04), TRUE);
		}
	}
}
//------------------------------------------------------------------------
//	@fn		DrawFinish
//	@brief	�����`��
//------------------------------------------------------------------------
void MixProduction :: DrawFinish(void){
	DataManager& data = DataManager::GetInstance();

	if(m_Step >= Finish){
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_Circle.data.alpha);				//���ߗ��̃Z�b�g
		DXLibMath::DrawRotaGraphResize(m_Circle.data.position.x-20/800.0f,m_Circle.data.position.y-5/600.0f,m_Circle.expansion,0.0f,
						data.GetGraphicGroupData(DataManager::GG_BULLET_NORMAL08),TRUE);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);				//���ߗ��̃Z�b�g
	}
}

//------------------------------------------------------------------------
//	@fn		SetContent
//	@brief	���e���Z�b�g
//------------------------------------------------------------------------
void MixProduction :: SetContent(int Content,int RootId,int RootType){
	if(Content != -1){
		m_Step = FEmission;
		m_Content = Content;
		m_Enable = true;
		m_RootId = RootId;
		m_RootType = RootType;
		PlaySoundMem( DataManager::GetInstance().Get( DataManager::SoundSE11 ), DX_PLAYTYPE_BACK);
		PlaySoundMem( DataManager::GetInstance().Get( DataManager::SoundSE26 ), DX_PLAYTYPE_BACK);
	}
}

//------------------------------------------------------------------------
//	@fn		Reset
//	@brief	���o�f�[�^�̃��Z�b�g
//------------------------------------------------------------------------
void MixProduction :: Reset(void){
	m_Main.position.x = -1.0f;
	m_Main.position.y = -1.0f;
	m_Main.alpha = 255;
	m_Main.flag = false;

	for(int i=0;i<4;i++){
		m_Material[i].position.x = -1.0f;
		m_Material[i].position.y = -1.0f;
		m_Material[i].alpha = 255;
		m_Material[i].flag = false;

		m_Sphere[i].data = m_Material[i];
		m_Sphere[i].velocity.x = -1.0f;
		m_Sphere[i].velocity.y = -1.0f;
	}

	m_Circle.data = m_Material[0];
	m_Circle.data.alpha = cm_CircleAlpha;
	m_Circle.expansion = 1.0f;
}

bool MixProduction :: GetEnable(void){
	return m_Enable;
}