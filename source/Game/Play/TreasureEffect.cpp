#include "TreasureEffect.h"
//
#include "../Menu/MenuIconSort.h"
#include "../System/GameInput.h"
#include "../System/DataManager.h"

const int	TreasureEffect :: cm_IconPosX			= 380;		//アイコン位置
const int	TreasureEffect :: cm_IconPosY			= 180+80;		//アイコン位置

TreasureEffect::TreasureEffect(void)
{
	Init();
}

TreasureEffect::~TreasureEffect(void)
{
}

void TreasureEffect::Init(void)
{
	DataManager &data = DataManager::GetInstance();
	//data.m_MogllStatus.treasureStatus = -1;
	m_Status = TREASURE_STATUS_IN;
	m_Frame = 0;

	m_ItemAlpha = 0;
	m_ItemPosX = (float)cm_IconPosX;
	m_ItemPosY = (float)cm_IconPosY;

	m_FrameAlpha= 0;
	m_FramePosX = 80;
	m_FramePosY = 100;

	m_DesAlpha= 0;
	m_DesPosX = 110;
	m_DesPosY = 300+50;

	m_Skip = false;
	m_NowSkip = false;
	m_OutFlag = true;

	m_BackPosition.x = 1.0f;
	m_BackPosition.y = -0.77f;
	m_GlliterPosition.x = 400.0f + 10.0f;
	m_GlliterPosition.y = 400.0f;//-462.0f + -10.0f;

	m_GetTreasure.Disable();
	m_Glliter[0].Clear();

	// 独自フォントを使用
	m_FontManager.Load( FontManager::FontSet_AZUKI_W00225 );
	m_FontManager.Load( FontManager::FontSet_AZUKI_W001625 );
	m_FontManager.Load( FontManager::FontSet_AZUKI_W00375 );
	m_FontManager.Load( FontManager::FontSet_AZUKI_W005 );
}

//
bool TreasureEffect::Update(void)
{
	switch(m_Status)
	{
	case TREASURE_STATUS_IN:
		Update_In();
		break;
	case TREASURE_STATUS_WAIT:
		Update_Wait();
		break;
	case TREASURE_STATUS_ITEMIN:
		Update_ItemIn();
		break;
	case TREASURE_STATUS_OUT:
		Update_Out();
		break;
	case TREASURE_STATUS_ITEMFRAMEIN:
		Update_InFrame();
		break;
	case TREASURE_STATUS_ITEMDESCRIPTION:
		Update_InDes();
		break;
	case TREASURE_STATUS_ALLOUT:
		Update_AllOut();
		if(m_Status == TREASURE_STATUS_IN)
			return true;
		break;
	default:
		break;
	}

	if(GameInput::GetInstance().GetMouse( GameInput::MouseLeftTrg ))
	{
		m_Skip = true;
	}
	
	if(m_Status == TREASURE_STATUS_OUT && m_OutFlag){
		m_OutFlag = false;
		m_Skip = false;
	}

	return false;
}
void TreasureEffect::GlliterUpdate(void){
	//m_GlliterPosition.x -= 80.0f;
	//m_GlliterPosition.y += 30.0f;
	//m_Glliter[0].Updata(&m_GlliterPosition);
	//m_Glliter[0].Updata(&m_GlliterPosition);
}

void TreasureEffect::Draw(void)
{
	int l_ItemNum = DataManager::GetInstance().m_MogllStatus.treasureStatus;
	DataManager &data = DataManager::GetInstance();
	if( data.m_MogllStatus.treasureStatus != -1 )
	{
		DrawGraph( (int)(800 * m_BackPosition.x), (int)(600 * m_BackPosition.y),
			data.Get( DataManager::Play_GetTreasure_BG ), TRUE);
	}
	if(m_Status == TREASURE_STATUS_WAIT || m_Status == TREASURE_STATUS_ITEMIN || m_Status == TREASURE_STATUS_OUT){
		m_GetTreasure.Draw();		
	}

	DrawItem();

	if(m_Status >= TREASURE_STATUS_ITEMFRAMEIN && m_Status < TREASURE_STATUS_ALLOUT){
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_FrameAlpha);
		if(l_ItemNum < 60 && l_ItemNum > -1){
			DrawExtendGraph(static_cast<int>(m_FramePosX)-50,static_cast<int>(m_FramePosY)+150-50,
							770,static_cast<int>(m_FramePosY)+150+250,
							data.Get(DataManager::Icon_Description_Frame),TRUE);
			m_FontManager.DrawFontString(	FontManager::FontSet_AZUKI_W005,
											static_cast<int>(m_FramePosX),static_cast<int>(m_FramePosY)+150,
											m_Message,700,GetColor(0,0,0));
			
		}
		else if(l_ItemNum >= 60){
			DrawExtendGraph(static_cast<int>(m_FramePosX)-60,static_cast<int>(m_FramePosY+100)+150-100,
							770,static_cast<int>(m_FramePosY+180)+150-100,
							data.Get(DataManager::Icon_Description_Frame),TRUE);
			m_FontManager.DrawFontString(	FontManager::FontSet_AZUKI_W004375,
											static_cast<int>(m_FramePosX),static_cast<int>(m_FramePosY+100)+170-100,
											m_Message,700,GetColor(0,0,0));
		}

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	}

	if(m_Status >= TREASURE_STATUS_ITEMDESCRIPTION && m_Status < TREASURE_STATUS_ALLOUT){
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_DesAlpha);
		if(l_ItemNum < 60 && l_ItemNum > -1){
			m_FontManager.DrawFontString(	FontManager::FontSet_AZUKI_W00375,
											static_cast<int>(m_DesPosX),static_cast<int>(m_DesPosY),
											DataManager::GetInstance().m_SystemData.equip[l_ItemNum].text,600,GetColor(0,0,0));
		}
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	}
	
}

void TreasureEffect::DrawItem(void){
	int l_ItemNum = DataManager::GetInstance().m_MogllStatus.treasureStatus;
	if(m_Status >= TREASURE_STATUS_ITEMIN && m_Status < TREASURE_STATUS_ALLOUT){
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_ItemAlpha);
		if(l_ItemNum < 60 && l_ItemNum > -1){
			DrawRotaGraph(	m_ItemPosX,m_ItemPosY,2.0f,0.0f,
							DataManager::GetInstance().GetGraphicGroupData( l_ItemNum  + DataManager::GG_ITEM0), TRUE);
		}
		else if(l_ItemNum >= 60){
			DrawRotaGraph(	m_ItemPosX,m_ItemPosY,0.8f,0.0f,
				DataManager::GetInstance().Get( static_cast<DataManager::GraphicSet>((l_ItemNum - 60) + DataManager::Ic_stage1)),TRUE);
		}
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	}
}

void TreasureEffect::GlliterDraw(DataManager &data){
	m_Glliter[0].Draw(&data);
}


void TreasureEffect::Update_In(void)
{
	if(m_Skip && !m_NowSkip){
		m_NowSkip = true;
		while(m_Skip){
			Update_In();
		}
		return;
	}

	m_BackPosition.x -= 1.1f/75;
	m_BackPosition.y += 0.5f/75;
	if(m_Frame > 75)
	{
		//ゲットしたアイテムの状態をNEWに
		GetItemStatusChange();

		m_Status = TREASURE_STATUS_WAIT;
		m_GetTreasure.Enable();
		m_Frame = 0;
		m_Skip = false;
		m_NowSkip = false;

	}
	m_Frame++;
}

void TreasureEffect::Update_Wait(void)
{
	if(m_Skip && !m_NowSkip){
		m_NowSkip = true;
		while(m_Skip){
			Update_Wait();
		}
		return;
	}

	m_GetTreasure.Update();

	if(m_Frame > 160)
	{
		m_Status = TREASURE_STATUS_ITEMIN;
		m_Skip = false;
		m_NowSkip = false;
		m_Frame = 0;
	}
	m_Frame++;
}

void TreasureEffect::Update_ItemIn(void)
{
	GameInput &input = GameInput::GetInstance();

	m_GetTreasure.Update();

	if(m_Skip && !m_NowSkip){
		m_NowSkip = true;
		while(m_Skip){
			Update_ItemIn();
		}
		return;
	}

	if(m_Frame > 80)
	{
		//m_Status = TREASURE_STATUS_WAIT;
		m_ItemAlpha = 255;
		m_ItemPosY = 180;
		m_GetTreasure.SetLightFlag(true);
		m_GetTreasure.SetOutFlag(true);

		if( input.GetMouse( GameInput::MouseLeftTrg ))
		{
			m_Status = TREASURE_STATUS_OUT;
			m_Frame = 0;
			m_Skip = false;
			m_NowSkip = false;
		}

		if(m_Frame > 300 && m_NowSkip){
			m_Status = TREASURE_STATUS_OUT;
			m_Frame = 0;
			m_Skip = false;
			m_NowSkip = false;
		}
	}
	else{
		m_ItemAlpha += 255/80;
		m_ItemPosY -= 80/80;
	}
	m_Frame++;
}

void TreasureEffect::Update_Out(void)
{
	int l_ItemNum;
	if(m_Skip && !m_NowSkip && m_OutFlag == false){
		m_NowSkip = true;
		while(m_Skip){
			Update_Out();
		}
		return;
	}

	m_GetTreasure.Update();

	if(m_GetTreasure.Out()){
		m_Status = TREASURE_STATUS_ITEMFRAMEIN;
		m_GetTreasure.Reset();
		m_Skip = false;
		m_NowSkip = false;
		l_ItemNum = DataManager::GetInstance().m_MogllStatus.treasureStatus;
		if(l_ItemNum > -1 && l_ItemNum < 60){
			sprintf_s(m_Message,256,"%sをゲット！",DataManager::GetInstance().m_SystemData.equip[l_ItemNum].name);
		}
		else if(l_ItemNum >= 60){
			sprintf_s(m_Message,256,"新しい惑星へいけるようになりました");
			if((l_ItemNum - 60) > 0){
				DataManager::GetInstance().m_SaveData.stageDepth[l_ItemNum-60] = 0;
			}
		}
	}
}

void TreasureEffect::Update_InFrame(void)
{
	if(m_Skip && !m_NowSkip){
		m_NowSkip = true;
		while(m_Skip){
			Update_InFrame();
		}
		return;
	}

	m_FrameAlpha += 255/40;
	m_FramePosY +=  50.0f / 40;

	if(m_Frame > 40)
	{
		m_Status = TREASURE_STATUS_ITEMDESCRIPTION;
		m_FrameAlpha = 255;
		m_Frame = 0;
		m_Skip = false;
		m_NowSkip = false;
	}
	m_Frame++;
}

void TreasureEffect::Update_InDes(void)
{
	GameInput &input = GameInput::GetInstance();

	if(m_Skip && !m_NowSkip){
		m_NowSkip = true;
		while(m_Skip){
			Update_InDes();
		}
		return;
	}

	m_DesPosY -= 50/80;

	m_DesAlpha += 260 / 40;
	if(m_DesAlpha > 255)
		m_DesAlpha = 255;

	if(m_Frame == 40/2){
		PlaySoundMem( DataManager::GetInstance().Get( DataManager::SoundSE07 ), DX_PLAYTYPE_BACK);
	}

	if(m_Frame > 40)
	{
		m_DesAlpha = 255;
		m_DesPosY = 350;
		m_Skip = false;
			m_NowSkip = false;
		if( input.GetMouse( GameInput::MouseLeftTrg ))
		{
			m_Status = TREASURE_STATUS_ALLOUT;
			m_Frame = 0;
			m_OutFlag = true;
		}
	}
	m_Frame++;
}

void TreasureEffect::Update_AllOut(void)
{
	if(m_Skip && !m_NowSkip){
		m_NowSkip = true;
		if(m_OutFlag){
			m_OutFlag = false;
			m_NowSkip = false;
			m_Skip = false;
		}
		while(m_Skip){
			Update_AllOut();
		}
		return;
	}

	m_BackPosition.x -= 1.1f/75;
	m_BackPosition.y += 0.5f/75;

	if(m_Frame > 75)
	{
		DataManager::GetInstance().m_MogllStatus.treasureStatus = -1;
		
		Init();
		return;
	}
	m_Frame++;
}

//ゲットしたアイテムの状態をNEWに
void TreasureEffect::GetItemStatusChange(void){
	DataManager *data = &DataManager::GetInstance();

	if(data->m_MogllStatus.treasureStatus != -1 && data->m_MogllStatus.treasureStatus < 60){
		data->m_SaveData.itemStatus[data->m_MogllStatus.treasureStatus] = DataManager::ITEM_NEW;
		data->SaveData();
	}

}