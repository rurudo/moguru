//========================================================================
//	@file		MixProduction.cpp
//	@note		合成分解演出
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
//const int		MixProduction :: cm_DivisionHermite		= 10;			//エルミート
const float		MixProduction :: cm_MaxExpansion		= 2.0f;			//拡大最大倍
const float		MixProduction :: cm_MaxExpansionPlus	= (cm_MaxExpansion - 1.0f) / Time_Finish;		//拡大最大倍

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
//	@brief	初期化処理
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
//	@brief	更新処理
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
//	@brief	解放処理
//------------------------------------------------------------------------
void MixProduction :: Release(void){
}
//------------------------------------------------------------------------
//	@fn		
//	@brief	処理
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
//	@brief	第一発光ステップ処理
//------------------------------------------------------------------------
void MixProduction :: StepFirstEmission(void){
	static int l_time = 0;
	static int l_num = 0;
	float l_work;

	if(m_Step == FEmission){
		//ツリーの番号の取得
		for(int i=0;i<cm_MixTreeNum;i++){
			if(m_MixTreeData[i].main.id == m_RootId && m_MixTreeData[i].main.type == m_RootType){
				l_num = i;
				break;
			}
		}
		if(m_Content == Mix){
			//素材の位置を計算
			for(int i=0;i<4;i++){
				switch(m_MixTreeData[l_num].Material[i].type){
				case Equipment:
					//x座標の計算
					l_work = ReverseGetID(m_MixTreeData[l_num].Material[i].id,m_MixTreeData[l_num].Material[i].type) % 10 * GameMenu::cm_OneFrameWidth;
					m_Material[i].position.x = GameMenu::cm_EquipmentUIXPos + l_work;
					//y座標の計算
					l_work = ReverseGetID(m_MixTreeData[l_num].Material[i].id,m_MixTreeData[l_num].Material[i].type) / 10 * GameMenu::cm_OneFrameHeight;
					m_Material[i].position.y = GameMenu::cm_EquipmentUIYPos + GameMenu::cm_BackYMargin + l_work;
					m_Material[i].flag = true;
					m_Material[i].alpha = cm_WhiteAlpha;
					break;
				case Unit:
					//x座標の計算
					l_work = ReverseGetID(m_MixTreeData[l_num].Material[i].id,m_MixTreeData[l_num].Material[i].type) % 10 * GameMenu::cm_OneFrameWidth;
					m_Material[i].position.x = GameMenu::cm_UnitUIXPos + l_work;
					//y座標の計算
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
				//x座標の計算
				l_work = ReverseGetID(m_MixTreeData[l_num].main.id,m_MixTreeData[l_num].main.type) % 10 * GameMenu::cm_OneFrameWidth;
				m_Main.position.x = GameMenu::cm_EquipmentUIXPos + l_work;
				//y座標の計算
				l_work = ReverseGetID(m_MixTreeData[l_num].main.id,m_MixTreeData[l_num].main.type) / 10 * GameMenu::cm_OneFrameHeight;
				m_Main.position.y = GameMenu::cm_EquipmentUIYPos + GameMenu::cm_BackYMargin + l_work;
				break;
			case Unit:
				//x座標の計算
				l_work = ReverseGetID(m_MixTreeData[l_num].main.id,m_MixTreeData[l_num].main.type) % 10 * GameMenu::cm_OneFrameWidth;
				m_Main.position.x = GameMenu::cm_UnitUIXPos + l_work;
				//y座標の計算
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
//	@brief	第二発光ステップ処理
//------------------------------------------------------------------------
void MixProduction :: StepSecondEmission(void){
	static int l_num = 0;
	float l_work;

	if(m_Step >= SEmission){
		//ツリーの番号の取得
		for(int i=0;i<cm_MixTreeNum;i++){
			if(m_MixTreeData[i].main.id == m_RootId && m_MixTreeData[i].main.type == m_RootType){
				l_num = i;
				break;
			}
		}
		if(m_Content == Mix){
			switch(m_MixTreeData[l_num].main.type){
			case Equipment:
				//x座標の計算
				l_work = (ReverseGetID(m_MixTreeData[l_num].main.id,m_MixTreeData[l_num].main.type) % 10) * GameMenu::cm_OneFrameWidth;
				m_Main.position.x = GameMenu::cm_EquipmentUIXPos + l_work;
				//y座標の計算
				l_work = (ReverseGetID(m_MixTreeData[l_num].main.id,m_MixTreeData[l_num].main.type) / 10) * GameMenu::cm_OneFrameHeight;
				m_Main.position.y = GameMenu::cm_EquipmentUIYPos + GameMenu::cm_BackYMargin + l_work;
				break;
			case Unit:
				//x座標の計算
				l_work = ReverseGetID(m_MixTreeData[l_num].main.id,m_MixTreeData[l_num].main.type) % 10 * GameMenu::cm_OneFrameWidth;
				m_Main.position.x = GameMenu::cm_UnitUIXPos + l_work;
				//y座標の計算
				l_work = ReverseGetID(m_MixTreeData[l_num].main.id,m_MixTreeData[l_num].main.type) / 10 * GameMenu::cm_OneFrameHeight;
				m_Main.position.y = GameMenu::cm_UnitUIYPos + GameMenu::cm_BackYMargin + l_work;
				break;
			}
			m_Main.flag = true;
			m_Main.alpha = cm_WhiteAlpha;
		}
		else if(m_Content == Break){
			//素材の位置を計算
			for(int i=0;i<4;i++){
				switch(m_MixTreeData[l_num].Material[i].type){
				case Equipment:
					//x座標の計算
					l_work = ReverseGetID(m_MixTreeData[l_num].Material[i].id,m_MixTreeData[l_num].Material[i].type) % 10 * GameMenu::cm_OneFrameWidth;
					m_Material[i].position.x = GameMenu::cm_EquipmentUIXPos + l_work;
					//y座標の計算
					l_work = ReverseGetID(m_MixTreeData[l_num].Material[i].id,m_MixTreeData[l_num].Material[i].type) / 10 * GameMenu::cm_OneFrameHeight;
					m_Material[i].position.y = GameMenu::cm_EquipmentUIYPos + GameMenu::cm_BackYMargin + l_work;
					m_Material[i].flag = true;
					m_Material[i].alpha = cm_WhiteAlpha;
					break;
				case Unit:
					//x座標の計算
					l_work = ReverseGetID(m_MixTreeData[l_num].Material[i].id,m_MixTreeData[l_num].Material[i].type) % 10 * GameMenu::cm_OneFrameWidth;
					m_Material[i].position.x = GameMenu::cm_UnitUIXPos + l_work;
					//y座標の計算
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
//	@brief	スタートステップ処理
//------------------------------------------------------------------------
void MixProduction :: StepStart(void){
	if(m_Content == Mix){
		//素材の位置を計算
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
//	@brief	準備ステップ処理
//------------------------------------------------------------------------
void MixProduction :: StepPreparation(void){
	for(int i=0;i<4;i++){
		m_Sphere[i].data.position.y -= 0.1f / Time_Preparation;
	}
}
//------------------------------------------------------------------------
//	@fn		StepRun
//	@brief	実行ステップ処理
//------------------------------------------------------------------------
void MixProduction :: StepRun(void){
	for(int i=0;i<4;i++){
		m_Sphere[i].data.position.x += m_Sphere[i].velocity.x;
		m_Sphere[i].data.position.y += m_Sphere[i].velocity.y;
	}
}
//------------------------------------------------------------------------
//	@fn		StepFinish
//	@brief	完了ステップ処理
//------------------------------------------------------------------------
void MixProduction :: StepFinish(void){
	
	m_Circle.data.alpha += (255 - cm_CircleAlpha) / Time_Finish;
	m_Circle.expansion += cm_MaxExpansionPlus;
}

//------------------------------------------------------------------------
//	@fn		Draw
//	@brief	描画処理
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
//	@brief	第一発光描画
//------------------------------------------------------------------------
void MixProduction :: DrawFirstEmission(void){
	if(m_Step >= FEmission){
		//薄暗く
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);									//透過率のセット
		DXLibMath::DrawBoxResize(0.0f, 0.0f, 1.0f, 1.0f, GetColor(0, 0, 0), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);									//透過率のセット

		switch(m_Content){
		case Mix:
			for(int i=0;i<4;i++){
				if(m_Material[i].flag){
					SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_Material[i].alpha);				//透過率のセット
					DXLibMath::DrawBoxResize(static_cast<float>(m_Material[i].position.x),static_cast<float>(m_Material[i].position.y), 
						GameMenu::cm_OneFrameWidth, GameMenu::cm_OneFrameHeight, GetColor(255,255,255), TRUE);
					SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);								//透過率のセット
				}
				else
					break;
			}
			break;
		case Break:
			if(m_Main.flag){
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_Main.alpha);							//透過率のセット
				DXLibMath::DrawBoxResize(static_cast<float>(m_Main.position.x),static_cast<float>(m_Main.position.y), 
					GameMenu::cm_OneFrameWidth, GameMenu::cm_OneFrameHeight, GetColor(255,255,255), TRUE);
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);									//透過率のセット
			}
			break;
		}
	}
}
//------------------------------------------------------------------------
//	@fn		DrawSecondEmission
//	@brief	第二発光描画
//------------------------------------------------------------------------
void MixProduction :: DrawSecondEmission(void){
	if(m_Step >= SEmission){
		switch(m_Content){
		case Mix:
			if(m_Main.flag){
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_Main.alpha);							//透過率のセット
				DXLibMath::DrawBoxResize(static_cast<float>(m_Main.position.x),static_cast<float>(m_Main.position.y), 
					GameMenu::cm_OneFrameWidth, GameMenu::cm_OneFrameHeight, GetColor(255,255,255), TRUE);
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);									//透過率のセット
			}
			break;
		case Break:
			for(int i=0;i<4;i++){
				if(m_Material[i].flag){
					SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_Material[i].alpha);				//透過率のセット
					DXLibMath::DrawBoxResize(static_cast<float>(m_Material[i].position.x),static_cast<float>(m_Material[i].position.y), 
						GameMenu::cm_OneFrameWidth, GameMenu::cm_OneFrameHeight, GetColor(255,255,255), TRUE);
					SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);								//透過率のセット
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
//	@brief	スタート描画
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
//	@brief	完了描画
//------------------------------------------------------------------------
void MixProduction :: DrawFinish(void){
	DataManager& data = DataManager::GetInstance();

	if(m_Step >= Finish){
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_Circle.data.alpha);				//透過率のセット
		DXLibMath::DrawRotaGraphResize(m_Circle.data.position.x-20/800.0f,m_Circle.data.position.y-5/600.0f,m_Circle.expansion,0.0f,
						data.GetGraphicGroupData(DataManager::GG_BULLET_NORMAL08),TRUE);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);				//透過率のセット
	}
}

//------------------------------------------------------------------------
//	@fn		SetContent
//	@brief	内容をセット
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
//	@brief	演出データのリセット
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