//========================================================================
//	@file	GetTreasure.cpp
//	@note	ゲット演出
//	@author	RyotaUehara
//========================================================================
//------------------------------------------------------------------------
//	IncludeHeader
//------------------------------------------------------------------------
#include "GetTreasure.h"
#include "../System/GameInput.h"

//------------------------------------------------------------------------
//	Const
//------------------------------------------------------------------------
const int	GetTreasure :: cm_GT_MogllFrame				= 30;
const int	GetTreasure :: cm_GT_StringFrame			= 30;
const int	GetTreasure :: cm_GT_CrackerFrame			= 12;
const float GetTreasure :: cm_GT_MogllPosX				= 310.0f;
const float GetTreasure :: cm_GT_MogllPosY				= 550.0f;
const float GetTreasure :: cm_GT_MogllTargetPosY		= cm_GT_MogllPosY-350.0f;
const float GetTreasure :: cm_GT_TreasureShinePosX		= 400;//cm_GT_MogllPosX+50.0f;
const float GetTreasure :: cm_GT_TreasureShinePosY		= 150;//cm_GT_MogllTargetPosY;
const float	GetTreasure :: cm_GT_String1PosX			= 205.0f;
const float	GetTreasure :: cm_GT_String1PosY			= 250.0f;
const float	GetTreasure :: cm_GT_String2PosX			= 660.0f;
const float	GetTreasure :: cm_GT_String2PosY			= 150.0f;
const float	GetTreasure :: cm_GT_StringTargetDistanceX	= 490.0f;//310.0f;
const float	GetTreasure :: cm_GT_StringTargetDistanceY	= -240.0f;//340.0f;
const float GetTreasure :: cm_GT_Cracker1PosX			= 700.0f;
const float GetTreasure :: cm_GT_Cracker1PosY			= 300.0f;
const float GetTreasure :: cm_GT_Cracker2PosX			= 100.0f;
const float GetTreasure :: cm_GT_Cracker2PosY			= 200.0f;
const float GetTreasure :: cm_GT_Cracker3PosX			= 200.0f;
const float GetTreasure :: cm_GT_Cracker3PosY			= 500.0f;

//------------------------------------------------------------------------
//	Constructor
//------------------------------------------------------------------------
GetTreasure :: GetTreasure(void)
{
	Init();
}
GetTreasure :: ~GetTreasure(void)
{
	Release();
}
//------------------------------------------------------------------------
//	@fn		Init
//	@brief	初期化処理
//------------------------------------------------------------------------
void GetTreasure :: Init(void){
	m_Step = STEP_Mogll;
	m_ShineStep = TSS_Shine1;
	m_Frame = 0;
	m_StringFrame1 = 0;
	m_StringFrame2 = 0;
	m_ShineFrame = 0;
	m_CrackerFrame = 0;

	m_AllAlpha = 255;

	m_OutFlag = false;
	m_GetStringType = false;
	m_Enable = false;
	m_Skip = false;
	m_NowSkip = false;
	m_SEFlag = false;
	m_LightFlag = false;

	m_Cracker.Init();
	m_Cracker2.Init();
	m_Cracker3.Init();

	m_Shine[0].Init();
	m_Shine[1].Init();
	m_Shine[2].Init();

	m_GetTreasure.pos.x = cm_GT_MogllPosX;
	m_GetTreasure.pos.y = cm_GT_MogllPosY;
	m_GetTreasure.alpha = 0;

	m_GetString1.data.pos.x = cm_GT_String1PosX + cm_GT_StringTargetDistanceX;
	m_GetString1.data.pos.y = cm_GT_String1PosY + cm_GT_StringTargetDistanceY;
	m_GetString1.data.alpha = 0;
	m_GetString1.gg_index = DataManager::GG_Get_Treasure_String1;

	m_GetString2.data.pos.x = cm_GT_String2PosX + cm_GT_StringTargetDistanceX;
	m_GetString2.data.pos.y = cm_GT_String2PosY + cm_GT_StringTargetDistanceY;
	m_GetString2.data.alpha = 0;
	m_GetString2.gg_index = DataManager::GG_Get_Get_String1;

	m_GetShine.data.pos.x = cm_GT_TreasureShinePosX;
	m_GetShine.data.pos.y = cm_GT_TreasureShinePosY;
	m_GetShine.data.alpha = 0;
	m_GetShine.angle = 0;
	m_GetShine.expansion = 1.0f;
	m_GetShine.expRFlag = false;

	//ハンドルリストを作成
	m_Data = &DataManager::GetInstance();
}
//------------------------------------------------------------------------
//	@fn		Reset
//	@brief	初期化処理
//------------------------------------------------------------------------
void GetTreasure :: Reset(void){
	m_Step = STEP_Mogll;
	m_ShineStep = TSS_Shine1;
	m_Frame = 0;
	m_StringFrame1 = 0;
	m_StringFrame2 = 0;
	m_ShineFrame = 0;
	m_CrackerFrame = 0;

	m_AllAlpha = 255;

	m_OutFlag = false;
	m_GetStringType = false;
	m_Skip = false;
	m_NowSkip = false;
	m_SEFlag = false;
	m_LightFlag = false;

	m_Cracker.Init();
	m_Cracker2.Init();
	m_Cracker3.Init();

	m_Shine[0].Init();
	m_Shine[1].Init();
	m_Shine[2].Init();

	m_GetTreasure.pos.x = cm_GT_MogllPosX;
	m_GetTreasure.pos.y = cm_GT_MogllPosY;
	m_GetTreasure.alpha = 0;

	m_GetString1.data.pos.x = cm_GT_String1PosX + cm_GT_StringTargetDistanceX;
	m_GetString1.data.pos.y = cm_GT_String1PosY + cm_GT_StringTargetDistanceY;
	m_GetString1.data.alpha = 0;
	m_GetString1.gg_index = DataManager::GG_Get_Treasure_String1;

	m_GetString2.data.pos.x = cm_GT_String2PosX + cm_GT_StringTargetDistanceX;
	m_GetString2.data.pos.y = cm_GT_String2PosY + cm_GT_StringTargetDistanceY;
	m_GetString2.data.alpha = 0;
	m_GetString2.gg_index = DataManager::GG_Get_Get_String1;

	m_GetShine.data.pos.x = cm_GT_TreasureShinePosX;
	m_GetShine.data.pos.y = cm_GT_TreasureShinePosY;
	m_GetShine.data.alpha = 0;
	m_GetShine.angle = 0;
	m_GetShine.expansion = 1.0f;
	m_GetShine.expRFlag = false;
}
//------------------------------------------------------------------------
//	@fn		Release
//	@brief	処理
//------------------------------------------------------------------------
void GetTreasure :: Release(void){
}

bool GetTreasure :: Out(void){

	m_AllAlpha -= 5;
	//m_OutFlag = true;
	if(m_AllAlpha <= 0){
		m_AllAlpha = 0;
		m_OutFlag = false;
		return true;
	}

	return false;
}

//------------------------------------------------------------------------
//	@fn		Update
//	@brief	処理
//------------------------------------------------------------------------
void GetTreasure :: Update(void){
	static int se_count = 0;

	switch(m_Step){
	case STEP_Mogll:
		UpdateMogll();
		break;
	//case STEP_TreasureShine:
		//break;
	//case STEP_String:
	//	break;
	case STEP_Wait:
		break;
	}

	UpdateGetString1();
	UpdateGetString2();
	UpdateTreasureShine();
	UpdateCracker();
	UpdateGlliter();

	//if(GameInput::GetInstance().GetKeyTrg(KEY_INPUT_F11))
	//{
	//	m_GetTreasure.pos.y = cm_GT_MogllPosY;
	//	m_Step = STEP_Mogll;
	//	m_Frame = 0;
	//}

	if(GameInput::GetInstance().GetMouse( GameInput::MouseLeftTrg ) && m_Step < STEP_Wait)
	{
		m_Skip = true;
	}

	//if(GameInput::GetInstance().GetMouse( GameInput::MouseLeftTrg ) && m_Step == STEP_Wait && m_OutFlag == false){
	//	Reset();
	//	m_Enable = false;
	//}

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
//	@fn		Update
//	@brief	処理
//------------------------------------------------------------------------
void GetTreasure :: UpdateMogll(void){
	if(m_Skip && !m_NowSkip){
		m_NowSkip = true;
		while(m_Skip){
			UpdateMogll();
		}
		return;
	}

	m_GetTreasure.pos.y += (cm_GT_MogllTargetPosY - cm_GT_MogllPosY) / cm_GT_MogllFrame; 
	m_GetTreasure.alpha += 260 / cm_GT_MogllFrame;
	if(m_GetTreasure.alpha > 255){
		m_GetTreasure.alpha = 255;
	}

	if(m_Frame > cm_GT_MogllFrame){
		m_Step++;
		m_Frame = 0;
		m_Shine[0].SetPoint(cm_GT_TreasureShinePosX,cm_GT_TreasureShinePosY);
		m_Skip = false;
		m_NowSkip = false;
		PlaySoundMem( m_Data->Get( DataManager::SoundSE07 ), DX_PLAYTYPE_BACK);
		return ;
	}
	m_Frame++;
}
//------------------------------------------------------------------------
//	@fn		UpdateGetString
//	@brief	処理
//------------------------------------------------------------------------
void GetTreasure :: UpdateGetString1(void){
	if(m_Skip && !m_NowSkip){
		m_NowSkip = true;
		while(m_Skip){
			UpdateGetString1();
		}
		return;
	}

	if(m_Step == STEP_String1){
		m_GetString1.data.pos.x -= cm_GT_StringTargetDistanceX / cm_GT_StringFrame; 
		m_GetString1.data.pos.y -= cm_GT_StringTargetDistanceY / cm_GT_StringFrame; 
		m_GetString1.data.alpha += 260 / cm_GT_StringFrame;
		if(m_GetString1.data.alpha > 255){
			m_GetString1.data.alpha = 255;
		}
	}

	if(m_Step >= STEP_String1){
		if(m_StringFrame1 > cm_GT_StringFrame/2)
			m_GetString1.gg_index = DataManager::GG_Get_Treasure_String2;
	}

	if(m_StringFrame1 > cm_GT_StringFrame){
		m_GetString1.gg_index = DataManager::GG_Get_Treasure_String1;
		if(m_Step == STEP_String1){
			m_Step++;
			PlaySoundMem( m_Data->Get( DataManager::SoundSE07 ), DX_PLAYTYPE_BACK);
		}
		m_StringFrame1 = 0;
		m_Skip = false;
		m_NowSkip = false;
		return ;
	}
	if(m_Step >= STEP_String1){
		m_StringFrame1++;
	}
}
//------------------------------------------------------------------------
void GetTreasure :: UpdateGetString2(void){
	if(m_Skip && !m_NowSkip){
		m_NowSkip = true;
		while(m_Skip){
			UpdateGetString2();
		}
		return;
	}

	if(m_Step == STEP_String2){
		m_GetString2.data.pos.x -= cm_GT_StringTargetDistanceX / cm_GT_StringFrame; 
		m_GetString2.data.pos.y -= cm_GT_StringTargetDistanceY / cm_GT_StringFrame; 
		m_GetString2.data.alpha += 260 / cm_GT_StringFrame;
		if(m_GetString2.data.alpha > 255){
			m_GetString2.data.alpha = 255;
		}
	}

	if(m_Step >= STEP_String2){
		if(m_StringFrame2 > cm_GT_StringFrame/2)
			m_GetString2.gg_index = DataManager::GG_Get_Get_String2;
	}

	if(m_StringFrame2 > cm_GT_StringFrame){
		m_GetString2.gg_index = DataManager::GG_Get_Get_String1;
		if(m_Step == STEP_String2){
			m_Step++;
			DXLibMath::Vector2 l_work;
			l_work.x = cm_GT_Cracker1PosX;
			l_work.y = cm_GT_Cracker1PosY;
			m_Cracker.SetPosition(l_work,Cracker::Dir_L);
			PlaySoundMem( m_Data->Get( DataManager::SoundSE04 ), DX_PLAYTYPE_BACK);
		}
		m_StringFrame2 = 0;
		m_Skip = false;
		m_NowSkip = false;
		return ;
	}

	if(m_Step >= STEP_String2){
		m_StringFrame2++;
	}

	//if(m_Skip){
	//	while(m_Skip)
	//		UpdateGetString2();
	//	return;
	//}
}
//------------------------------------------------------------------------
//	@fn		UpdateTreasureShine
//	@brief	処理
//------------------------------------------------------------------------
void GetTreasure :: UpdateTreasureShine(void){
	if(m_Step >= STEP_TreasureShine && m_Step <= STEP_Wait){
		if(m_Step == STEP_TreasureShine)
			m_Step = STEP_String1;

		m_Shine[0].Update();
		m_Shine[1].Update();
		m_Shine[2].Update();

		switch(m_ShineStep){
		case TSS_Shine1:
			if(m_Frame > TSST_Shine1){
				m_Shine[1].SetPoint(cm_GT_TreasureShinePosX,cm_GT_TreasureShinePosY);
				m_ShineStep++;
				m_ShineFrame = 0;
				m_Frame = 0;
				m_GetShine.data.alpha = 200;
				return ;
			}
			m_Frame++;
			break;
		case TSS_Shine2:
			if(m_ShineFrame > TSST_Shine2){
				m_Shine[2].SetPoint(cm_GT_TreasureShinePosX,cm_GT_TreasureShinePosY);
				m_ShineStep++;
				m_ShineFrame = 0;
				m_Frame = 0;
				m_GetShine.data.alpha = 200;
				return ;
			}
			break;
		case TSS_Wait:
			if(m_ShineFrame > TSST_Wait){
				m_ShineStep = TSS_Shine1;
				m_ShineFrame = 0;
				m_GetShine.angle = 0;
				m_Shine[0].SetPoint(cm_GT_TreasureShinePosX,cm_GT_TreasureShinePosY);
				PlaySoundMem( DataManager::GetInstance().Get( DataManager::SoundSE03 ), DX_PLAYTYPE_BACK);
				return ;
			}
			break;
		}
		m_ShineFrame++;
	}

}
//------------------------------------------------------------------------
//	@fn		UpdateCracker
//	@brief	処理
//------------------------------------------------------------------------
void GetTreasure :: UpdateCracker(void){
	m_Cracker.Update();
	m_Cracker2.Update();
	if(m_Cracker3.Update() && m_SEFlag == false){
		m_SEFlag = true;
		PlaySoundMem( m_Data->Get( DataManager::SoundSE04 ), DX_PLAYTYPE_BACK);
	}


	if(m_CrackerFrame > cm_GT_CrackerFrame){
		if(m_Step == STEP_Cracker1){
			m_Step++;
			DXLibMath::Vector2 l_work;
			l_work.x = cm_GT_Cracker2PosX;
			l_work.y = cm_GT_Cracker2PosY;
			m_Cracker2.SetPosition(l_work,Cracker::Dir_R);
		}
		else if(m_Step == STEP_Cracker2){
			m_Step++;
			DXLibMath::Vector2 l_work;
			l_work.x = cm_GT_Cracker3PosX;
			l_work.y = cm_GT_Cracker3PosY;
			m_Cracker3.SetPosition(l_work,Cracker::Dir_R);
		}
		m_CrackerFrame = 0;
		return ;
	}
	m_CrackerFrame++;
}
//------------------------------------------------------------------------
//	@fn		UpdateGlliter
//	@brief	処理
//------------------------------------------------------------------------
void GetTreasure :: UpdateGlliter(void){
}
//------------------------------------------------------------------------
//	@fn		Draw
//	@brief	処理
//------------------------------------------------------------------------
void GetTreasure :: Draw(void){
	if(m_Enable){
		DrawCracker();
		DrawMogll();
		DrawTreasureShine();
		DrawGetString1();
		DrawGetString2();
		DrawGlliter();
	}
}
//------------------------------------------------------------------------
//	@fn		Draw
//	@brief	処理
//------------------------------------------------------------------------
void GetTreasure :: DrawMogll(void){
	int l_ItemNum = DataManager::GetInstance().m_MogllStatus.treasureStatus;
	if(m_Step >= STEP_Mogll){
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_GetTreasure.alpha);	
		if(m_OutFlag) 
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_AllAlpha);	
		DrawGraph(static_cast<int>(m_GetTreasure.pos.x),static_cast<int>(m_GetTreasure.pos.y),
					m_Data->Get( DataManager::Play_Treasure_Mogll_Graph_Back),TRUE);

		if(l_ItemNum < 60 && l_ItemNum > -1){
			DrawGraph(static_cast<int>(m_GetTreasure.pos.x),static_cast<int>(m_GetTreasure.pos.y),
						m_Data->Get( DataManager::Play_Treasure_Mogll_Graph_BoX_Blue),TRUE);
		}
		else if(l_ItemNum >= 60){
			DrawGraph(static_cast<int>(m_GetTreasure.pos.x),static_cast<int>(m_GetTreasure.pos.y),
						m_Data->Get( DataManager::Play_Treasure_Mogll_Graph_BoX_Pink),TRUE);
		}

		DrawGraph(static_cast<int>(m_GetTreasure.pos.x),static_cast<int>(m_GetTreasure.pos.y),
					m_Data->Get( DataManager::Play_Treasure_Mogll_Graph),TRUE);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);	
	}
}
//------------------------------------------------------------------------
//	@fn		Draw
//	@brief	処理
//------------------------------------------------------------------------
void GetTreasure :: DrawTreasureShine(void){
	if(m_Step >= STEP_TreasureShine && m_LightFlag && !m_OutFlag){
		m_Shine[0].Draw();
		m_Shine[1].Draw();
		m_Shine[2].Draw();
	}
}
//------------------------------------------------------------------------
//	@fn		Draw
//	@brief	処理
//------------------------------------------------------------------------
void GetTreasure :: DrawGetString1(void){
	if(m_Step >= STEP_String1){
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_GetString1.data.alpha);	
		if(m_OutFlag) 
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_AllAlpha);	
		DrawRotaGraph(static_cast<int>(m_GetString1.data.pos.x),static_cast<int>(m_GetString1.data.pos.y),
						0.9f,-15 * (float)3.141592653589793 / 180.0f,m_Data->GetGraphicGroupData( m_GetString1.gg_index),TRUE);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);	
	}
}
//------------------------------------------------------------------------
void GetTreasure :: DrawGetString2(void){
	if(m_Step >= STEP_String2){
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_GetString2.data.alpha);	
		if(m_OutFlag) SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_AllAlpha);	
		DrawRotaGraph(static_cast<int>(m_GetString2.data.pos.x),static_cast<int>(m_GetString2.data.pos.y),
						0.79f,-30 * (float)3.141592653589793 / 180.0f,m_Data->GetGraphicGroupData( m_GetString2.gg_index),TRUE);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);	
	}
}
//------------------------------------------------------------------------
//	@fn		Draw
//	@brief	処理
//------------------------------------------------------------------------
void GetTreasure :: DrawCracker(void){
	if(m_OutFlag) SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_AllAlpha);
	if(m_Step >= STEP_Cracker1){
		m_Cracker.Draw();
	}
	if(m_Step >= STEP_Cracker2){
		m_Cracker2.Draw();
	}
	if(m_Step >= STEP_Wait){
		m_Cracker3.Draw();
	}
	if(m_OutFlag) SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}
//------------------------------------------------------------------------
//	@fn		Draw
//	@brief	処理
//------------------------------------------------------------------------
void GetTreasure :: DrawGlliter(void){
}

//------------------------------------------------------------------------
//	@fn		GetEnable
//	@brief	処理
//------------------------------------------------------------------------
bool GetTreasure :: GetEnable(void){
	return m_Enable;
}
//------------------------------------------------------------------------
//	@fn		Enable
//	@brief	処理
//------------------------------------------------------------------------
void GetTreasure :: Enable(void){
	m_Enable = true;
}
//------------------------------------------------------------------------
//	@fn		Disable
//	@brief	処理
//------------------------------------------------------------------------
void GetTreasure :: Disable(void){
	m_Enable = false;
}

void GetTreasure :: SetLightFlag(bool flag){
	m_LightFlag = flag;
}
void GetTreasure :: SetOutFlag(bool flag){
	m_OutFlag = flag;
}