//========================================================================
//	@file	AfterGetMapProduction.cpp
//	@note	宝ゲット後の演出
//========================================================================

//------------------------------------------------------------------------
//	IncludeHeader
//------------------------------------------------------------------------
#include "AfterGetMapProduction.h"
#include "../System/GameInput.h"
#include "../Menu/MenuIconSort.h"

//------------------------------------------------------------------------
//	Const
//------------------------------------------------------------------------
const int	AfterGetMapProduction :: cm_BackPosX			= 800;		//背景位置
const int	AfterGetMapProduction :: cm_BackPosY			= -462;		//背景位置
const int	AfterGetMapProduction :: cm_BackOff				= 100;		//背景位置
const int	AfterGetMapProduction :: cm_StagePosX			= 400;		//アイコン位置
const int	AfterGetMapProduction :: cm_StagePosY			= 220;		//アイコン位置
const int	AfterGetMapProduction :: cm_IconPosX			= 400;		//アイコン位置
const int	AfterGetMapProduction :: cm_IconPosY			= 150;		//アイコン位置
const int	AfterGetMapProduction :: cm_GetMessagePosX		= 80;		//メッセージ:入手しました位置
const int	AfterGetMapProduction :: cm_GetMessagePosY		= 100;		//メッセージ:入手しました位置
const int	AfterGetMapProduction :: cm_GetMessageOff		= 50;		//メッセージ:入手しました位置
const int	AfterGetMapProduction :: cm_DecriptionPosX		= 110;		//入手したものの説明位置
const int	AfterGetMapProduction :: cm_DecriptionPosY		= 300;		//入手したものの説明位置
const int	AfterGetMapProduction :: cm_DecriptionOff		= 50;		//入手したものの説明位置

//------------------------------------------------------------------------
//	Constructor
//------------------------------------------------------------------------
AfterGetMapProduction :: AfterGetMapProduction(void)
{
	Init();
}
AfterGetMapProduction :: ~AfterGetMapProduction(void)
{
	Release();
}

//------------------------------------------------------------------------
//	@fn		Init
//	@brief	初期化
//------------------------------------------------------------------------
void AfterGetMapProduction::Init(void){
	m_Enable = false;
	m_Skip = false;	
	m_NowSkip = false;
	m_Step = STEP_Init;	
	m_Frame = 0;

	m_ItemNum = -1;	
	m_ItemHandle = -1;
	m_ItemAipha = 0;	
	m_ItemExpansion = 0.4f;

	m_MessAipha = 0;

	m_DesAipha = 0;

	memset(m_Message,0,sizeof(m_Message));
	

	m_BackPos.x = cm_BackPosX;
	m_BackPos.y = cm_BackPosY;

	m_MessagePos.x = static_cast<int>(cm_GetMessagePosX);
	m_MessagePos.y = static_cast<int>(cm_GetMessagePosY+cm_GetMessageOff);

	m_DescriptionPos.x = static_cast<int>(cm_DecriptionPosX);
	m_DescriptionPos.y = static_cast<int>(cm_DecriptionPosY+cm_DecriptionOff);

	m_Data = &DataManager::GetInstance();

	// 独自フォントを使用
	m_FontManager.Load( FontManager::FontSet_AZUKI_W00225 );
	m_FontManager.Load( FontManager::FontSet_AZUKI_W001625 );
	m_FontManager.Load( FontManager::FontSet_AZUKI_W00375 );
	m_FontManager.Load( FontManager::FontSet_AZUKI_W005 );
}
//------------------------------------------------------------------------
//	@fn		Reset
//	@brief	
//------------------------------------------------------------------------
void AfterGetMapProduction::Reset(void){
	m_Skip = false;	
	m_NowSkip = false;
	m_Step = STEP_Init;	
	m_Frame = 0;

	m_ItemNum = -1;		
	m_ItemHandle = -1;
	m_ItemAipha = 0;	
	m_ItemExpansion = 0.4f;

	m_MessAipha = 0;

	m_DesAipha = 0;

	m_BackPos.x = cm_BackPosX;
	m_BackPos.y = cm_BackPosY;

	m_MessagePos.x = static_cast<int>(cm_GetMessagePosX);
	m_MessagePos.y = static_cast<int>(cm_GetMessagePosY+cm_GetMessageOff);

	m_DescriptionPos.x = static_cast<int>(cm_DecriptionPosX);
	m_DescriptionPos.y = static_cast<int>(cm_DecriptionPosY+cm_DecriptionOff);

	m_ItemNum = m_Data->m_MogllStatus.treasureStatus;
	if(m_ItemNum > -1 && m_ItemNum < 60){
		sprintf_s(m_Message,256,"%sをゲット！",m_Data->m_SystemData.equip[m_ItemNum].name);
		m_ItemHandle = m_ItemNum + DataManager::GG_ITEM0;
	}
	else if(m_ItemNum >= 60){
		sprintf_s(m_Message,256,"新しい惑星へいけるようになりました");
		m_ItemHandle = (m_ItemNum - 60) + DataManager::Ic_stage1;
		if((m_ItemNum - 60) > 0){
			m_Data->m_SaveData.stageDepth[m_ItemNum-60] = 0;
		}
	}
}
//------------------------------------------------------------------------
//	@fn		Release
//	@brief	解放
//------------------------------------------------------------------------
void AfterGetMapProduction::Release(void){

}

//------------------------------------------------------------------------
//	@fn		Update
//	@brief	更新
//------------------------------------------------------------------------
void AfterGetMapProduction::Update(void){
	if(m_Enable){
		if(GameInput::GetInstance().GetMouse( GameInput::MouseLeftTrg ) && (m_Step < STEP_EndWait || m_Step == STEP_TreeOut))
		{
			m_Skip = true;
		}

		if(m_Step == STEP_Init){
			Reset();
			m_Step++;
			//PlaySoundMem( m_Data->Get( DataManager::SoundSE01 ), DX_PLAYTYPE_BACK);
			return;
		}
		UpdateStep();
	}
}
//------------------------------------------------------------------------
//	@fn		UpdateStep
//	@brief	ステップ更新
//------------------------------------------------------------------------
void AfterGetMapProduction::UpdateStep(void){
	static int se_count = 0;
	GameInput &input = GameInput::GetInstance();

	switch(m_Step){
	case STEP_FrameIn:
		InFrame();
		break;
	case STEP_InWait:
		if(m_Frame > FRAME_InWait){
			m_Step = STEP_IconIn;
			m_Frame = 0;
		}
		m_Frame++;

		break;
	case STEP_IconIn:
		InIcon();
		break;
	case STEP_MessageIn:
		InMessage();
		break;
	case STEP_DescriptionIn:
		InDescription();
		break;
	case STEP_EndWait:
		if( input.GetMouse( GameInput::MouseLeftTrg ))
		{
			m_Step = STEP_TreeOut;
		}
		break;
	case STEP_TreeOut:
		OutFrame();
		break;
	}

//	if(se_count > 139 && 1 != CheckSoundMem(DataManager::SoundSE04)){//0 == CheckSoundMem( m_Data->Get( DataManager::SoundSE04 ) ) ){
//		PlaySoundMem( m_Data->Get( DataManager::SoundSE04_3 ), DX_PLAYTYPE_BACK);
//		se_count = 0;
//	}
//	else if(se_count > 139 && 1 != CheckSoundMem(DataManager::SoundSE04_2)){//0 == CheckSoundMem( m_Data->Get( DataManager::SoundSE04 ) ) ){
//		PlaySoundMem( m_Data->Get( DataManager::SoundSE04 ), DX_PLAYTYPE_BACK);
//		se_count = 0;
//	}
//	else if(se_count > 139 && 1 != CheckSoundMem(DataManager::SoundSE04_3)){//0 == CheckSoundMem( m_Data->Get( DataManager::SoundSE04 ) ) ){
//		PlaySoundMem( m_Data->Get( DataManager::SoundSE04_2 ), DX_PLAYTYPE_BACK);
//		se_count = 0;
//	}
//	se_count++;
}
//------------------------------------------------------------------------
//	@fn		InFrame
//	@brief	ツリー枠イン処理
//------------------------------------------------------------------------
void AfterGetMapProduction::InFrame(void){
	if(m_Skip && !m_NowSkip){
		m_NowSkip = true;
		while(m_Skip){
			InFrame();
		}
		return;
	}

	m_BackPos.x += -880.0f / FRAME_FrameIn;
	m_BackPos.y +=  330.0f / FRAME_FrameIn;

	if(m_Frame > FRAME_FrameIn)
	{
		m_Step++;
		m_Frame = 0;
		m_Skip = false;
		m_NowSkip = false;

		m_ItemNum = m_Data->m_MogllStatus.treasureStatus;
	}
	m_Frame++;
}
//------------------------------------------------------------------------
//	@fn		InIcon
//	@brief	アイコンイン処理
//------------------------------------------------------------------------
void AfterGetMapProduction::InIcon(void){
	if(m_Skip && !m_NowSkip){
		m_NowSkip = true;
		while(m_Skip){
			InIcon();
		}
		return;
	}

	m_ItemAipha += 260 / FRAME_IconIn;
	if(m_ItemAipha > 255)
		m_ItemAipha = 0;

	m_ItemExpansion += 1.1f / FRAME_IconIn;
	if(m_ItemExpansion > 1.5f)
		m_ItemExpansion = 1.5f;

	if(m_Frame == FRAME_IconIn/2){
		PlaySoundMem( m_Data->Get( DataManager::SoundSE01 ), DX_PLAYTYPE_BACK);
		PlaySoundMem( m_Data->Get( DataManager::SoundSE04 ), DX_PLAYTYPE_BACK);
	}

	if(m_Frame > FRAME_IconIn)
	{
		m_Step++;
		m_ItemExpansion -= 1.1f / FRAME_IconIn;
		m_Frame = 0;
		m_Skip = false;
		m_NowSkip = false;
	}
	m_Frame++;
}
//------------------------------------------------------------------------
//	@fn		InMessage
//	@brief	メッセージイン処理
//------------------------------------------------------------------------
void AfterGetMapProduction::InMessage(void){
	if(m_Skip && !m_NowSkip){
		m_NowSkip = true;
		while(m_Skip){
			InMessage();
		}
		return;
	}

	m_MessagePos.y -= cm_GetMessageOff/FRAME_MessageIn;

	m_MessAipha += 260 / FRAME_MessageIn;
	if(m_MessAipha > 255)
		m_MessAipha = 0;

	if(m_Frame == FRAME_MessageIn/2){
		PlaySoundMem( m_Data->Get( DataManager::SoundSE07 ), DX_PLAYTYPE_BACK);
	}

	if(m_Frame > FRAME_MessageIn)
	{
		m_Step++;
		m_MessagePos.y += (cm_GetMessageOff/FRAME_MessageIn)*4;
		m_Frame = 0;
		m_Skip = false;
		m_NowSkip = false;
	}
	m_Frame++;
}
//------------------------------------------------------------------------
//	@fn		InDescription
//	@brief	説明イン処理
//------------------------------------------------------------------------
void AfterGetMapProduction::InDescription(void){
	if(m_Skip && !m_NowSkip){
		m_NowSkip = true;
		while(m_Skip){
			InDescription();
		}
		return;
	}

	if(m_ItemNum >= 60){
		m_Step++;
		m_Frame = 0;
		m_Skip = false;
		m_NowSkip = false;

		return;
	}

	m_DescriptionPos.y -= cm_GetMessageOff/FRAME_DescriptionIn;

	m_DesAipha += 260 / FRAME_DescriptionIn;
	if(m_DesAipha > 255)
		m_DesAipha = 0;

	if(m_Frame == FRAME_DescriptionIn/2){
		PlaySoundMem( m_Data->Get( DataManager::SoundSE07 ), DX_PLAYTYPE_BACK);
	}

	if(m_Frame > FRAME_DescriptionIn)
	{
		m_Step++;
		m_DescriptionPos.y += (cm_GetMessageOff/FRAME_DescriptionIn)*4;
		m_Frame = 0;
		m_Skip = false;
		m_NowSkip = false;
	}
	m_Frame++;
}
//------------------------------------------------------------------------
//	@fn		OutFrame
//	@brief	ツリー枠アウト処理
//------------------------------------------------------------------------
void AfterGetMapProduction::OutFrame(void){
	if(m_Skip && !m_NowSkip){
		m_NowSkip = true;
		while(m_Skip){
			OutFrame();
		}
		return;
	}

	m_BackPos.x += -880.0f / FRAME_FrameIn;
	m_BackPos.y +=  330.0f / FRAME_FrameIn;

	if(m_Frame > FRAME_FrameOut)
	{
		m_Data->m_MogllStatus.treasureStatus = -1;
		m_Frame = 0;
		m_Skip = false;
		m_NowSkip = false;

		m_Step = STEP_Init;
		m_Enable = false;
		return;
	}
	m_Frame++;
}

//------------------------------------------------------------------------
//	@fn		Draw
//	@brief	描画
//------------------------------------------------------------------------
void AfterGetMapProduction::Draw(void){
	if(m_Enable && m_Step > STEP_Init){
		DrawFrame();
		DrawIcon();
		DrawMessage();
		DrawDescription();
	}
}
//------------------------------------------------------------------------
//	@fn		DrawFrame
//	@brief	枠描画
//------------------------------------------------------------------------
void AfterGetMapProduction::DrawFrame(void){
	if(m_Step >= STEP_FrameIn){
		DrawGraph( static_cast<int>(m_BackPos.x), static_cast<int>(m_BackPos.y),
			m_Data->Get( DataManager::Play_GetTreasure_BG ), TRUE);
	}
}
//------------------------------------------------------------------------
//	@fn		DrawIcon
//	@brief	アイコン描画
//------------------------------------------------------------------------
void AfterGetMapProduction::DrawIcon(void){
	if(m_Step >= STEP_IconIn && m_Step < STEP_TreeOut){
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_ItemAipha);
		if(m_ItemNum < 60 && m_ItemNum > -1){
			DrawRotaGraph(	cm_IconPosX,cm_IconPosY,m_ItemExpansion,0.0f,
							m_Data->GetGraphicGroupData( m_ItemHandle ), TRUE);
		}
		else if(m_ItemNum >= 60){
			DrawRotaGraph(	cm_StagePosX,cm_StagePosY,m_ItemExpansion,0.0f,
							m_Data->Get( static_cast<DataManager::GraphicSet>(m_ItemHandle) ), TRUE);
		}
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	}
}
//------------------------------------------------------------------------
//	@fn		DrawMessage
//	@brief	メッセージ描画
//------------------------------------------------------------------------
void AfterGetMapProduction::DrawMessage(void){
	if(m_Step >= STEP_MessageIn && m_Step < STEP_TreeOut){
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_MessAipha);
		if(m_ItemNum < 60 && m_ItemNum > -1){
			DrawExtendGraph(static_cast<int>(m_MessagePos.x)-50,static_cast<int>(m_MessagePos.y)+cm_IconPosY-50,
							770,static_cast<int>(m_MessagePos.y)+cm_IconPosY+250,
							m_Data->Get(DataManager::Icon_Description_Frame),TRUE);
			m_FontManager.DrawFontString(	FontManager::FontSet_AZUKI_W005,
											static_cast<int>(m_MessagePos.x),static_cast<int>(m_MessagePos.y)+cm_IconPosY,
											m_Message,700,GetColor(0,0,0));
			
		}
		else if(m_ItemNum >= 60){
			DrawExtendGraph(static_cast<int>(m_MessagePos.x)-60,static_cast<int>(m_MessagePos.y+100)+cm_StagePosY-cm_GetMessageOff-50,
							770,static_cast<int>(m_MessagePos.y+180)+cm_StagePosY-cm_GetMessageOff,
							m_Data->Get(DataManager::Icon_Description_Frame),TRUE);
			m_FontManager.DrawFontString(	FontManager::FontSet_AZUKI_W004375,
											static_cast<int>(m_MessagePos.x),static_cast<int>(m_MessagePos.y+100)+cm_StagePosY-cm_GetMessageOff,
											m_Message,700,GetColor(0,0,0));
		}

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	}
}
//------------------------------------------------------------------------
//	@fn		DrawDescription
//	@brief	説明描画
//------------------------------------------------------------------------
void AfterGetMapProduction::DrawDescription(void){
	if(m_Step >= STEP_MessageIn && m_Step < STEP_TreeOut){
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_DesAipha);
		if(m_ItemNum < 60 && m_ItemNum > -1){
			m_FontManager.DrawFontString(	FontManager::FontSet_AZUKI_W00375,
											static_cast<int>(m_DescriptionPos.x),static_cast<int>(m_DescriptionPos.y),
											m_Data->m_SystemData.equip[m_ItemNum].text,600,GetColor(0,0,0));
		}
		else if(m_ItemNum >= 60){
			m_FontManager.DrawFontString(	FontManager::FontSet_AZUKI_W00375,
											static_cast<int>(m_DescriptionPos.x),static_cast<int>(m_DescriptionPos.y),
											m_Data->m_SystemData.equip[m_ItemNum].text,600,GetColor(0,0,0));
		}
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	}
}
//------------------------------------------------------------------------
//	@fn		Enable
//	@brief	
//------------------------------------------------------------------------
void AfterGetMapProduction::Enable(void){
	if(!m_Enable)
		m_Enable = true;
}

//------------------------------------------------------------------------
//	@fn		GetEnable
//	@brief	
//------------------------------------------------------------------------
bool AfterGetMapProduction::GetEnable(void){
	return m_Enable;
}
//========================================================================
//	End of file
//========================================================================
