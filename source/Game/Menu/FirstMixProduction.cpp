#include "FirstMixProduction.h"
#include "../System/DataManager.h"
#include "../System/DxLibMath.h"
#include "../System/GameInput.h"
#include "MixTreeData.h"

#define _CRT_SECURE_NO_DEPRECATE

const int FirstMixProduction::FrameInItem			= 40;
const int FirstMixProduction::FrameInFrame			= 40;
const int FirstMixProduction::FrameInMessage		= 40;
const int FirstMixProduction::FrameInDescription	= 40;
const int FirstMixProduction::FrameWait				= 250;
const int FirstMixProduction::FrameOutItem			= 10;
const int FirstMixProduction::FrameOutMessage		= 10;
const int FirstMixProduction::FrameOutFrame			= 10;
const int FirstMixProduction::FrameOutDescription	= 10;

const int FirstMixProduction::Movement				= 50;

FirstMixProduction::FirstMixProduction(void){
	Init();
}

FirstMixProduction::~FirstMixProduction(void){
	Release();
}

void FirstMixProduction::Init(void){
	m_Frame				= 0;
	m_AlphaItem			= 0;
	m_AlphaFrame		= 0;
	m_AlphaMessage		= 0;
	m_AlphaDescription	= 0;
	m_Step				= STEP_Init;

	m_ItemW			= 100;
	m_ItemH			= 100;
	m_FrameW		= 700;
	m_FrameH		= 350;
	m_MessageW		= 640;
	m_DescriptionW	= 520;

	//初期位置の設定
	m_ItemX			= 400-m_ItemW/2;
	m_ItemY			= 100-m_ItemH/2+Movement;
	m_FrameX		= 50;
	m_FrameY		= 200+Movement;
	m_MessageX		= m_FrameX+60;
	m_MessageY		= m_FrameY+60;
	m_DescriptionX	= m_MessageX+35;
	m_DescriptionY	= m_MessageY+60;

	m_ID = -1;
	m_Type = -1;

	m_Enable = false;
	m_Skip = false;
	m_NowSkip = false;

	for(int i=0;i<60;i++)
		m_ItemStatus[i] = DataManager::GetInstance().m_SaveData.itemStatus[i];
	for(int i=0;i<30;i++)
		m_UnitStatus[i] = DataManager::GetInstance().m_SaveData.unitStatus[i];
}

void FirstMixProduction::Reset(void){
	m_Frame				= 0;
	m_AlphaItem			= 0;
	m_AlphaFrame		= 0;
	m_AlphaMessage		= 0;
	m_AlphaDescription	= 0;
	m_Step				= STEP_Init;

	m_ItemW			= 100;
	m_ItemH			= 100;
	m_FrameW		= 700;
	m_FrameH		= 350;
	m_MessageW		= 640;
	m_DescriptionW	= 520;

	//初期位置の設定
	m_ItemX			= 400-m_ItemW/2;
	m_ItemY			= 100-m_ItemH/2+Movement;
	m_FrameX		= 50;
	m_FrameY		= 200+Movement;
	m_MessageX		= m_FrameX+60;
	m_MessageY		= m_FrameY+60;
	m_DescriptionX	= m_MessageX+35;
	m_DescriptionY	= m_MessageY+60;

	m_ID = -1;
	m_Type = -1;

	m_Skip = false;
	m_NowSkip = false;
}

void FirstMixProduction::Release(void){
	
}

//更新
bool FirstMixProduction::Update(void){
	for(int i=0;i<60;i++)
		m_ItemStatus[i] = DataManager::GetInstance().m_SaveData.itemStatus[i];
	for(int i=0;i<30;i++)
		m_UnitStatus[i] = DataManager::GetInstance().m_SaveData.unitStatus[i];

	if(m_Enable){
		StepUpdate();

		return true;
	}
	return false;
}
void FirstMixProduction::StepUpdate(void){
	GameInput &input = GameInput::GetInstance();

	if(GameInput::GetInstance().GetMouse( GameInput::MouseLeftTrg ) && 
		m_Step < STEP_Wait)
	{
		m_Skip = true;
	}

	switch(m_Step){
	case STEP_Init:
		m_Step++;
		PlaySoundMem( DataManager::GetInstance().Get( DataManager::SoundSE01 ), DX_PLAYTYPE_BACK);
		break;
	case STEP_InItem:
		StepInItem();
		break;
	case STEP_InFrame:
		StepInFrame();
		break;
	case STEP_InMessage:
		StepInMessage();
		break;
	case STEP_InDescription:
		StepInDescription();
		break;
	case STEP_Wait:
		if( input.GetMouse( GameInput::MouseLeftTrg ))
		{
			Reset();
			m_Enable = false;
		}
		if(m_Frame > FrameWait){
			m_Frame = 0;

			Reset();
			m_Enable = false;

			return;
		}
		m_Frame++;
		//キー入力で
		break;
	case STEP_OutItem:
		StepOutItem();
		break;
	case STEP_OutFrame:
		StepOutFrame();
		break;
	case STEP_OutMessage:
		StepOutMessage();
		break;
	case STEP_OutDescription:
		StepOutDescription();
		break;
	}
}
void FirstMixProduction::StepInItem(void){
	if(m_Skip && !m_NowSkip){
		m_NowSkip = true;
		while(m_Skip){
			StepInItem();
		}
		return;
	}

	m_ItemY -= Movement/FrameInItem;
	if(m_ItemY>m_ItemY+Movement)
		m_ItemY = m_ItemY+Movement;

	m_AlphaItem += 260/FrameInItem;
	if(m_AlphaItem>255)
		m_AlphaItem = 255;

	if(m_Frame > FrameInItem){
		m_Frame = 0;
		m_Step++;
		m_Skip = false;
		m_NowSkip = false;
		//PlaySoundMem( DataManager::GetInstance().Get( DataManager::SoundSE07 ), DX_PLAYTYPE_BACK);
	}
	m_Frame++;
}
void FirstMixProduction::StepInFrame(void){
	if(m_Skip && !m_NowSkip){
		m_NowSkip = true;
		while(m_Skip){
			StepInFrame();
		}
		return;
	}

	m_FrameY -= Movement/FrameInItem;
	if(m_FrameY>m_FrameY+Movement)
		m_FrameY = m_FrameY+Movement;

	m_AlphaFrame += 260/FrameInFrame;
	if(m_AlphaFrame>255)
		m_AlphaFrame = 255;

	if(m_Frame > FrameInFrame){
		m_Frame = 0;
		m_Step++;
		m_Skip = false;
		m_NowSkip = false;
		PlaySoundMem( DataManager::GetInstance().Get( DataManager::SoundSE07 ), DX_PLAYTYPE_BACK);
	}
	m_Frame++;
}
void FirstMixProduction::StepInMessage(void){
	if(m_Skip && !m_NowSkip){
		m_NowSkip = true;
		while(m_Skip){
			StepInMessage();
		}
		return;
	}

	m_MessageY -= Movement/FrameInItem;
	if(m_MessageY>m_MessageY+Movement)
		m_MessageY = m_MessageY+Movement;

	m_AlphaMessage += 260/FrameInMessage;
	if(m_AlphaMessage>255)
		m_AlphaMessage = 255;

	if(m_Frame > FrameInMessage){
		m_Frame = 0;
		m_Step++;
		m_Skip = false;
		m_NowSkip = false;
		PlaySoundMem( DataManager::GetInstance().Get( DataManager::SoundSE07 ), DX_PLAYTYPE_BACK);
	}
	m_Frame++;
}
void FirstMixProduction::StepInDescription(void){
	if(m_Skip && !m_NowSkip){
		m_NowSkip = true;
		while(m_Skip){
			StepInDescription();
		}
		return;
	}

	m_DescriptionY -= Movement/FrameInItem;
	if(m_DescriptionY>m_DescriptionY+Movement)
		m_DescriptionY = m_DescriptionY+Movement;

	m_AlphaDescription += 260/FrameInDescription;
	if(m_AlphaDescription>255)
		m_AlphaDescription = 255;

	if(m_Frame > FrameInDescription){
		m_Frame = 0;
		m_Step++;
		m_Skip = false;
		m_NowSkip = false;
	}
	m_Frame++;
}

void FirstMixProduction::StepOutItem(void){
	
}
void FirstMixProduction::StepOutFrame(void){
	
}
void FirstMixProduction::StepOutMessage(void){
	
}
void FirstMixProduction::StepOutDescription(void){
	
}

//描画
void FirstMixProduction::Draw(void){
	if(m_Enable){
		DrawItem();
		DrawFrame();
		DrawMessage();
		DrawDescription();
	}
}
void FirstMixProduction::DrawItem(void){
	if(m_Step >= STEP_InItem){
		//薄暗く
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);									//透過率のセット
		DXLibMath::DrawBoxResize(0.0f, 0.0f, 1.0f, 1.0f, GetColor(0, 0, 0), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);									//透過率のセット

		SetDrawBlendMode(DX_BLENDMODE_ALPHA,m_AlphaItem);
		switch(m_Type){
		case 0:
			DrawExtendGraph(m_ItemX,m_ItemY,m_ItemX+m_ItemW,m_ItemY+m_ItemH,
				DataManager::GetInstance().GetGraphicGroupData(DataManager::GG_ITEM0 + m_ID),TRUE);
			//DrawRotaGraph(m_ItemX,m_ItemY,1.0f,DataManager::GetInstance().Get((DataManager::GraphicSet)(DataManager::Equipment_ic_Gear + EquipItemImageList[m_ID])),TRUE);
			break;
		case 1:
			DrawExtendGraph(m_ItemX,m_ItemY,m_ItemX+m_ItemW,m_ItemY+m_ItemH,
				DataManager::GetInstance().GetGraphicGroupData(DataManager::GG_UNIT_Treasure + m_ID),TRUE);
			//DrawGraph(m_ItemX,m_ItemY,DataManager::GetInstance().GetGraphicGroupData(DataManager::GG_UNIT_Treasure + m_ID),TRUE);
			break;
		}
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
	}
}
void FirstMixProduction::DrawFrame(void){
	if(m_Step >= STEP_InFrame){
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,m_AlphaFrame);
		DrawExtendGraph(m_FrameX,m_FrameY,m_FrameX+m_FrameW,m_FrameY+m_FrameH,DataManager::GetInstance().Get(DataManager::Icon_Description_Frame),TRUE);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
	}
}
void FirstMixProduction::DrawMessage(void){
	char l_str[256];

	memset(l_str,0,sizeof(l_str));

	if(m_Step >= STEP_InMessage){
		switch(m_Type){
		case 0:
			sprintf_s(l_str,"%s を合成しました",DataManager::GetInstance().m_SystemData.equip[m_ID].name);
			m_FontManager.DrawFontString(	FontManager::FontSet_AZUKI_W005,
											m_MessageX,m_MessageY,
											l_str,
											m_MessageW,
											GetColor(0,0,0));
			break;
		case 1:
			sprintf_s(l_str,"%s を合成しました",DataManager::GetInstance().m_SystemData.unit[m_ID].name);
			m_FontManager.DrawFontString(	FontManager::FontSet_AZUKI_W005,
											m_MessageX,m_MessageY,
											l_str,
											m_MessageW,
											GetColor(0,0,0));
			break;
		}
	}
}

void FirstMixProduction::DrawDescription(void){
	char l_str[256];

	memset(l_str,0,sizeof(l_str));

	if(m_Step >= STEP_InDescription){
		switch(m_Type){
		case 0:
			sprintf_s(l_str,"%s",DataManager::GetInstance().m_SystemData.equip[m_ID].text);
			m_FontManager.DrawFontString(	FontManager::FontSet_AZUKI_W004375,
											m_DescriptionX,m_DescriptionY,
											l_str,
											m_DescriptionW,
											GetColor(0,0,0));
			break;
		case 1:
			sprintf_s(l_str,"%s",DataManager::GetInstance().m_SystemData.unit[m_ID].text);
			m_FontManager.DrawFontString(	FontManager::FontSet_AZUKI_W004375,
											m_DescriptionX,m_DescriptionY,
											l_str,
											m_DescriptionW,
											GetColor(0,0,0));
			break;
		}
	}
}

void FirstMixProduction::Enable(int MixNum,int MixType){
	if(!m_Enable){
		m_ID = MixNum;
		m_Type = MixType;

		m_Enable = false;

		switch(m_Type){
		case 0:
			if(m_ItemStatus[m_ID] == DataManager::ITEM_CANMIX)
				m_Enable = true;
			break;
		case 1:
			if(m_UnitStatus[m_ID] == DataManager::ITEM_CANMIX)
				m_Enable = true;
			break;
		}
	}
}

bool FirstMixProduction::GetEnable(void){
	return m_Enable;
}