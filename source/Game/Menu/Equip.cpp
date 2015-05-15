//========================================================================
//	@file	Equip.cpp
//	@note	装備
//	@author	RyotaUehara
//========================================================================
//------------------------------------------------------------------------
//	IncludeHeader
//------------------------------------------------------------------------
#include "GameMenu.h"
#include "Equip.h"
#include "MenuIconSort.h"
#include "MixTreeData.h"
#include "../System/DxLibMath.h"
#include "../System/GameInput.h"
#include "DxLib.h"

#define _CRT_SECURE_NO_DEPRECATE

//------------------------------------------------------------------------
//	Const
//------------------------------------------------------------------------
const int		Equip :: cm_ItemSlotPosFrame			= 5;						

const float		Equip :: cm_RootMixStrX					= 0.175f;					//ルート合成過程文字x座標
const float		Equip :: cm_RootMixStrY					= 0.166f;					//ルート合成過程文字y座標
const float		Equip :: cm_ProcessStrX					= 0.1875f;					//ルート合成過程処理文字y座標
const float		Equip :: cm_ProcessStrY					= 0.216f;					//ルート合成過程処理文字y座標
const float		Equip :: cm_ProcessSupStrX				= 0.2f;						//ルート合成過程処理補助文字y座標
const float		Equip :: cm_ProcessSupStrY				= 0.25f;					//ルート合成過程処理補助文字y座標
const float		Equip :: cm_MaterialStrX				= 0.2125f;					//素材文字x座標
const float		Equip :: cm_MaterialStrY				= 0.33f;					//素材文字y座標
const float		Equip :: cm_MaterialStrHeight			= 0.033f;					//素材文字高さ
const float		Equip :: cm_ClickIconX					= 0.2f;						//クリックアイコンx座標
const float		Equip :: cm_RClickIconX					= 0.4375f;					//右クリックアイコンx座
const float		Equip :: cm_ClickIconY					= 0.525f;					//クリックアイコンy座標
const float		Equip :: cm_ClickIconWidth				= 0.1125f;					//クリックアイコン幅
const float		Equip :: cm_ClickIconHeight				= 0.15f;					//クリックアイコン高さ
const float		Equip :: cm_ClickIconSupX				= 0.245f;					//クリックアイコン補助文字x座標
const float		Equip :: cm_RClickIconSupX				= 0.45f;					//右クリックアイコン補助文字x座標
const float		Equip :: cm_ClickIconSupY				= 0.683f;					//クリックアイコン補助文字y座標

//------------------------------------------------------------------------
//	Constructor
//------------------------------------------------------------------------
Equip :: Equip(void)
{
	Init();
}
Equip :: ~Equip(void)
{
	Release();
}
//------------------------------------------------------------------------
//	@fn		Init
//	@brief	初期化処理
//------------------------------------------------------------------------
void Equip :: Init(void){
	m_End = false;
	m_Check = false;
	m_ConfirmationFlag = false;
	m_HaveItem = false;
	m_ItemFlag = None;

	m_Debug = false;

	m_EquipmentSlot = new EquipData[3];			//装備品スロット
	m_UnitSlot = new EquipData[6];				//ユニットスロット

	m_ItemSlotPos = 0;

	m_EquipCount = 0;
	m_UnitCount = 0;

	//ハンドルリストを作成
	m_Data = &DataManager::GetInstance();

	//スロットの初期化
	for(int i=0;i<3;i++){				//装備
		m_EquipmentSlot[i].id.z = -1;
		m_EquipmentSlot[i].id.x = -1;
		m_EquipmentSlot[i].id.y = -1;
		m_EquipmentSlot[i].type = None;
	}
	for(int i=0;i<6;i++){				//ユニット
		m_UnitSlot[i].id.z = -1;
		m_UnitSlot[i].id.x = -1;
		m_UnitSlot[i].id.y = -1;
		m_UnitSlot[i].type = None;
	}

	//装備アイテムのセット
	for(int i=0;i<3;i++){
		m_EquipmentSlot[i].id.z = m_Data->m_SaveData.equipItem[i];
		m_EquipmentSlot[i].id.x = m_EquipmentSlot[i].id.z%10;
		m_EquipmentSlot[i].id.y = m_EquipmentSlot[i].id.z/10;
		m_UnitSlot[i].type = 0;
	}

	//装備ユニットのセット
	for(int i=0;i<6;i++){
		m_UnitSlot[i].id.z = m_Data->m_SaveData.equipUnit[i];
		m_UnitSlot[i].id.x = m_UnitSlot[i].id.z%10;
		m_UnitSlot[i].id.y = m_UnitSlot[i].id.z/10;
		m_UnitSlot[i].type = 1;
	}

	SetMogllEquipStatus();

	m_MixRoot.id.x = -1;
	m_MixRoot.id.y = -1;
	m_MixRoot.id.z = -1;
	m_MixRoot.type = -1;

	m_MixData.id.x = -1;
	m_MixData.id.y = -1;
	m_MixData.id.z = -1;
	m_MixData.type = -1;

	m_BreakData.id.x = -1;
	m_BreakData.id.y = -1;
	m_BreakData.id.z = -1;
	m_BreakData.type = -1;

	m_EquipData.id = -1;
	m_EquipData.type = -1;

	// 独自フォントを使用
	m_FontManager.Load( FontManager::FontSet_AZUKI_W0025 );
	m_FontManager.Load( FontManager::FontSet_AZUKI_W001875 );

}
//------------------------------------------------------------------------
//	@fn		Reset
//	@brief	デバッグ用リセット
//------------------------------------------------------------------------
void Equip :: Reset(void){
	//スロットの初期化
	for(int i=0;i<3;i++){				//装備
		m_EquipmentSlot[i].id.z = -1;
		m_EquipmentSlot[i].id.x = -1;
		m_EquipmentSlot[i].id.y = -1;
		m_EquipmentSlot[i].type = None;
	}
	for(int i=0;i<6;i++){				//ユニット
		m_UnitSlot[i].id.z = -1;
		m_UnitSlot[i].id.x = -1;
		m_UnitSlot[i].id.y = -1;
		m_UnitSlot[i].type = None;
	}

	//装備アイテムのセット
	for(int i=0;i<3;i++){
		m_EquipmentSlot[i].id.z = m_Data->m_SaveData.equipItem[i];
		m_EquipmentSlot[i].id.x = m_EquipmentSlot[i].id.z%10;
		m_EquipmentSlot[i].id.y = m_EquipmentSlot[i].id.z/10;
		m_UnitSlot[i].type = 0;
	}

	//装備ユニットのセット
	for(int i=0;i<6;i++){
		m_UnitSlot[i].id.z = m_Data->m_SaveData.equipUnit[i];
		m_UnitSlot[i].id.x = m_UnitSlot[i].id.z%10;
		m_UnitSlot[i].id.y = m_UnitSlot[i].id.z/10;
		m_UnitSlot[i].type = 1;
	}

	EquipConfirmation();
	SetMogllEquipStatus();

	m_MixData.id.x = -1;
	m_MixData.id.y = -1;
	m_MixData.id.z = -1;
	m_MixData.type = -1;

	m_BreakData.id.x = -1;
	m_BreakData.id.y = -1;
	m_BreakData.id.z = -1;
	m_BreakData.type = -1;

	m_EquipData.id = -1;
	m_EquipData.type = -1;
}
//------------------------------------------------------------------------
//	@fn		SetMogllEquipStatus
//	@brief	モグルの装備ステータスをセット処理
//------------------------------------------------------------------------
void Equip :: SetMogllEquipStatus(void){
	int l_count = 0;

	for(int i=0;i<3;i++){
		if(m_EquipmentSlot[i].id.z != -1){
			m_Data->m_MogllStatus.equip[i] = m_EquipmentSlot[i].id.z;
		}
		else{
			m_Data->m_MogllStatus.equip[i] = -1;
		}
		m_Data->m_SaveData.equipItem[i] = m_Data->m_MogllStatus.equip[i];
	}

	for(int i=0;i<6;i++){
		if(m_UnitSlot[i].id.z != -1){
			m_Data->m_MogllStatus.equipUnit[i] = m_UnitSlot[i].id.z;
			m_Data->m_SaveData.equipUnit[i] = m_UnitSlot[i].id.z;
		}
		else{
			m_Data->m_MogllStatus.equipUnit[i] = 30;
			m_Data->m_SaveData.equipUnit[i] = 30;
		}
	}

	m_Data->SaveData();
}
void Equip :: SetMogllEquipStatus(char type,int slotNum){
	int l_count = 0;

	switch(type){
	case Equipment:
		for(int i=0;i<3;i++){
			if(m_EquipmentSlot[i].id.z != -1){
				m_Data->m_MogllStatus.equip[i] = m_EquipmentSlot[i].id.z;
			}
			else{
				m_Data->m_MogllStatus.equip[i] = -1;
			}

			if(m_EquipmentSlot[i].id.z == m_EquipData.id && i != slotNum){
				m_Data->m_MogllStatus.equip[i] = -1;

				m_EquipmentSlot[i].id.z = -1;
			}
			m_Data->m_SaveData.equipItem[i] = m_Data->m_MogllStatus.equip[i];
		}
		break;
	case Unit:
		for(int i=0;i<6;i++){
			if(m_UnitSlot[i].id.z != -1){
				m_Data->m_MogllStatus.equipUnit[i] = m_UnitSlot[i].id.z;
				m_Data->m_SaveData.equipUnit[i] = m_UnitSlot[i].id.z;
			}
			else{
				m_Data->m_MogllStatus.equipUnit[i] = 30;
				m_Data->m_SaveData.equipUnit[i] = 30;
			}

			if(m_UnitSlot[i].id.z == m_EquipData.id && i != slotNum){
				m_Data->m_MogllStatus.equipUnit[i] = 30;
				m_Data->m_SaveData.equipUnit[i] = 30;

				m_UnitSlot[i].id.z = -1;
			}
		}
		break;
	}

	m_Data->SaveData();
}
//------------------------------------------------------------------------
//	@fn		Update
//	@brief	更新処理
//------------------------------------------------------------------------
bool Equip :: Update(int *Content,TreeData *Root){
	m_End = false;

	
	// マウスの座標を保存
	m_Mouse.x = GameInput::GetInstance().GetXf();
	m_Mouse.y = GameInput::GetInstance().GetYf();

	if(Confirmation() && m_OkCancel == Flag_OK){
		//合成・分解
		switch(m_ItemFlag){
		case Flag_Mix:
			Mix();
			*Content = 0;
			Root->id = m_MixData.id.z;
			Root->type = m_MixData.type;
			break;
		case Flag_Break:
			Break();
			*Content = 1;
			Root->id = m_BreakData.id.z;
			Root->type = m_BreakData.type;
			break;
		}
		
		m_ConfirmationFlag = false;
		if(m_End == false){
			//装備状態の確認
			EquipConfirmation();
			return true;
		}
	}
	else if(m_OkCancel == Flag_Cancel){
		m_ConfirmationFlag = false;
		m_OkCancel = None;
		m_ItemFlag = None;
		*Content = -1;
		Root->id = -1;
		Root->type = -1;
		
		m_MixRoot.id.x = -1;
		m_MixRoot.id.y = -1;
		m_MixRoot.id.z = -1;
		m_MixRoot.type = -1;
		return true;
	}

	//確認
	if(m_Check && m_ConfirmationFlag == false){
		//チェック
		if(!EquipJudge() && Judge()){
			if(EquipCheck()){
				m_MixRoot.id.x = -1;
				m_MixRoot.id.y = -1;
				m_MixRoot.id.z = -1;
				m_MixRoot.type = -1;
				return true;
			}
		}
	}

	//合成・分解確認
	if(m_End == false && m_ConfirmationFlag == false){
		if(MixCheck()){
			m_End = true;
		}
	}

	if(m_End && m_ConfirmationFlag == false){
		//合成・分解
		switch(m_ItemFlag){
		case Flag_Mix:
			Mix();
			*Content = 0;
			Root->id = m_MixData.id.z;
			Root->type = m_MixData.type;
			break;
		case Flag_Break:
			Break();
			*Content = 1;
			Root->id = m_BreakData.id.z;
			Root->type = m_BreakData.type;
			break;
		}
	}

	//装備処理
	if(m_End){
		//装備状態の確認
		EquipConfirmation();
	}

	m_Check = false;
	return m_End;
}
//------------------------------------------------------------------------
//	@fn		Release
//	@brief	解放処理
//------------------------------------------------------------------------
void Equip :: Release(void){
	delete[] m_EquipmentSlot;
	delete[] m_UnitSlot;
}
//------------------------------------------------------------------------
//	@fn		Draw
//	@brief	描画処理
//------------------------------------------------------------------------
void Equip :: Draw(void){
	int l_FontColor = GetColor(0,0,0);
	int l_num = -1;

	int l_xNum;
	int l_yNum;
	float l_xWork;
	float l_yWork;

	float l_FontWidth = 0.5f;
	char l_str[256];
	char l_str2[256];

	EquipData l_workData;

	//DrawSlot();

	//確認時
	if(m_ConfirmationFlag){
		//薄暗く
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);									//透過率のセット
		DXLibMath::DrawBoxResize(0.0f, 0.0f, 1.0f, 1.0f, GetColor(0, 0, 0), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);									//透過率のセット
		//表示枠
		DXLibMath::DrawExtendGraphResize(0.09375f,0.108f,0.5625f,0.65f, m_Data->Get(DataManager::Confirmation_Frame), FALSE);
		
		//何の過程か-----------------------------------------------
		switch(m_MixRoot.type){
		case Equipment:
			sprintf_s(l_str,"[ %s ] の合成過程",m_Data->m_SystemData.equip[m_MixRoot.id.z].name);
			break;
		case Unit:
			sprintf_s(l_str,"[ %s ] の合成過程",m_Data->m_SystemData.unit[m_MixRoot.id.z].name);
			break;
		}
		m_FontManager.DrawFontString(	FontManager::FontSet_AZUKI_W0025,
										cm_RootMixStrX,cm_RootMixStrY,
										l_str,
										l_FontWidth,
										l_FontColor);

		//なにをするのか-------------------------------------------
		switch(m_ItemFlag){
		case Flag_Mix:
			if(m_MixData.type == Equipment){
				sprintf_s(l_str,"%s の合成をします",m_Data->m_SystemData.equip[m_MixData.id.z].name);
			}
			else if(m_MixData.type == Unit){
				sprintf_s(l_str,"%s の合成をします",m_Data->m_SystemData.unit[m_MixData.id.z].name);
			}
			l_workData = m_MixData;
			sprintf_s(l_str2,"以下のものを使用します");
			break;
		case Flag_Break:
			if(m_BreakData.type == Equipment){
				sprintf_s(l_str,"%s の分解をします",m_Data->m_SystemData.equip[m_BreakData.id.z].name);
			}
			else if(m_BreakData.type == Unit){
				sprintf_s(l_str,"%s の分解をします",m_Data->m_SystemData.unit[m_BreakData.id.z].name);
			}
			l_workData = m_BreakData;
			sprintf_s(l_str2,"以下のものになります");
			break;
		}
		m_FontManager.DrawFontString(	FontManager::FontSet_AZUKI_W001875,
										cm_ProcessStrX,cm_ProcessStrY,
										l_str,
										l_FontWidth,
										l_FontColor);
		m_FontManager.DrawFontString(	FontManager::FontSet_AZUKI_W001875,
										cm_ProcessSupStrX,cm_ProcessSupStrY,
										l_str2,
										l_FontWidth,
										l_FontColor);

		//素材の表示
		for(int i=0;i<cm_MixTreeNum;i++){
			if(m_MixTreeData[i].main.id == l_workData.id.z && m_MixTreeData[i].main.type == l_workData.type){
				l_num = i;
				break;
			}
		}
		for(int i=0;i<4;i++){
			if(m_MixTreeData[l_num].Material[i].id != -1){
				switch(m_MixTreeData[l_num].Material[i].type){
				case Equipment:
					sprintf_s(l_str,"%s",m_Data->m_SystemData.equip[m_MixTreeData[l_num].Material[i].id].name);
					break;
				case Unit:
					sprintf_s(l_str,"%s",m_Data->m_SystemData.unit[m_MixTreeData[l_num].Material[i].id].name);
					break;
				}
				m_FontManager.DrawFontString(	FontManager::FontSet_AZUKI_W001875,
												cm_MaterialStrX,cm_MaterialStrY+(cm_MaterialStrHeight*i),
												l_str,
												l_FontWidth,
												l_FontColor);
			}
		}
		

		DXLibMath::DrawExtendGraphResize(cm_ClickIconX,cm_ClickIconY,cm_ClickIconWidth,cm_ClickIconHeight, m_Data->Get(DataManager::Click), TRUE);
		m_FontManager.DrawFontString(	FontManager::FontSet_AZUKI_W001875,
										cm_ClickIconSupX,cm_ClickIconSupY,
										"OK",
										l_FontWidth,
										l_FontColor);
		DXLibMath::DrawExtendGraphResize(cm_RClickIconX,cm_ClickIconY,cm_ClickIconWidth,cm_ClickIconHeight, m_Data->Get(DataManager::RightClick), TRUE);
		m_FontManager.DrawFontString(	FontManager::FontSet_AZUKI_W001875,
										cm_RClickIconSupX,cm_ClickIconSupY,
										"キャンセル",
										l_FontWidth,
										l_FontColor);

		return;
	}

	if(m_Debug){
		for(int i=0;i<60;i++){
			sprintf_s(l_str,"%d",m_Data->m_SaveData.itemStatus[i]);
			l_xNum = ReverseGetID(i,0)%10;
			l_yNum = ReverseGetID(i,0)/10;
			l_xWork = GameMenu::cm_OneFrameWidth * l_xNum + GameMenu::cm_EquipmentUIXPos;
			l_yWork = GameMenu::cm_OneFrameHeight * l_yNum + GameMenu::cm_EquipmentUIYPos + (20/600.0f);
			m_FontManager.DrawFontString(	FontManager::FontSet_AZUKI_W0025,
											l_xWork,l_yWork,
											l_str,
											l_FontWidth,
											GetColor(255,255,0));
		}
		for(int i=0;i<30;i++){
			sprintf_s(l_str,"%d",m_Data->m_SaveData.unitStatus[i]);
			l_xNum = ReverseGetID(i,1)%10;
			l_yNum = ReverseGetID(i,1)/10;
			l_xWork = GameMenu::cm_OneFrameWidth * l_xNum + GameMenu::cm_UnitUIXPos;
			l_yWork = GameMenu::cm_OneFrameHeight * l_yNum + GameMenu::cm_UnitUIYPos + (20/600.0f);
			m_FontManager.DrawFontString(	FontManager::FontSet_AZUKI_W0025,
											l_xWork,l_yWork,
											l_str,
											l_FontWidth,
											GetColor(0,255,255));
		}
	}
}
void Equip :: SymbolDraw(void){
	//装備シンボルの描画
	DrawEquipSymbol();

	DrawNewSymbol();
}
void Equip :: OtherDraw(void){
	DrawSlotOver();
	DrawHaveItem();
}

//------------------------------------------------------------------------
//	@fn		Judge
//	@brief	どの装備品・ユニットか判断
//------------------------------------------------------------------------
bool Equip :: Judge(void){
	//static TreeData l_memData;
	//static TreeData l_memData2;
	static bool l_initFlag = true;

	if(l_initFlag){
		//l_memData.id = -1;
		//l_memData.type = -1;
		//l_memData2.id = -1;
		//l_memData2.type = -1;
		m_memData.id = -1;
		m_memData.type = -1;
		m_memData2.id = -1;
		m_memData2.type = -1;
		l_initFlag = false;
	}

	//装備
	for(int i = 0; i < GameMenu::cm_EquipmentHNum; i++)
	{
		for(int j = 0; j < GameMenu::cm_ColumnVNum; j++)
		{
			if(	m_Mouse.x > GameMenu::cm_EquipmentUIXPos+(j*GameMenu::cm_OneFrameWidth) && m_Mouse.x < GameMenu::cm_EquipmentUIXPos+(j*GameMenu::cm_OneFrameWidth)+GameMenu::cm_OneFrameWidth && 
				m_Mouse.y > GameMenu::cm_EquipmentUIYPos+(i*GameMenu::cm_OneFrameHeight) + GameMenu::cm_BackYMargin && m_Mouse.y < GameMenu::cm_EquipmentUIYPos+(i*GameMenu::cm_OneFrameHeight)+GameMenu::cm_OneFrameHeight + GameMenu::cm_BackYMargin){
				
				m_MixRoot.id.x = j;
				m_MixRoot.id.y = i;
				m_MixRoot.id.z = SORT_ItemIconSortList[j + (i * GameMenu::cm_ColumnVNum)];
				m_MixRoot.type = Equipment;
				if(	m_Data->m_SaveData.itemStatus[m_MixRoot.id.z] != DataManager::ITEM_NOT_FIND && 
					m_Data->m_SaveData.itemStatus[m_MixRoot.id.z] != DataManager::ITEM_NO_EXIST && 
					!m_ItemEquipManager->GetMoveFlag() && !m_ItemEquipManager->GetStayFlag() && 
					!m_ItemEquipManager->GetReverseFlag()){
					if(EquipCheck(m_MixRoot)){

						for(int i = 0;i < 3;i++){
							if(m_EquipmentSlot[i].id.z == -1){
								

								if(	m_Data->m_SaveData.itemStatus[m_MixRoot.id.z] == DataManager::ITEM_EXIST || 
									m_Data->m_SaveData.itemStatus[m_MixRoot.id.z] == DataManager::ITEM_NEW){

									m_Data->m_SaveData.itemStatus[m_MixRoot.id.z] = DataManager::ITEM_EQUIP;
								}
								else if(m_Data->m_SaveData.itemStatus[m_MixRoot.id.z] == DataManager::ITEM_MIX){

									m_Data->m_SaveData.itemStatus[m_MixRoot.id.z] = DataManager::ITEM_MIX_EQUIP;
								}
								else{
									m_EquipData.id = -1;
									m_EquipData.type = -1;
									m_HaveItem = false;

									m_MixRoot.id.x = -1;
									m_MixRoot.id.y = -1;
									m_MixRoot.id.z = -1;
									m_MixRoot.type = -1;
									m_memData.id = -1;
									m_memData.type = -1;
									m_memData2.id = -1;
									m_memData2.type = -1;
									if(!m_HaveItem && !m_ItemEquipManager->GetMoveFlag() && !m_ItemEquipManager->GetStayFlag() && !m_ItemEquipManager->GetReverseFlag())
										PlaySoundMem( m_Data->Get( DataManager::SoundSE38 ), DX_PLAYTYPE_BACK);
									return false;
								}
								
								m_EquipmentSlot[i].id.z = m_MixRoot.id.z;
								m_EquipmentSlot[i].type = Equipment;

								SetMogllEquipStatus(Equipment,i);

								PlaySoundMem( m_Data->Get( DataManager::SoundSE28 ), DX_PLAYTYPE_BACK);
							
								return true;
							}
						}

						if(!m_HaveItem && !m_ItemEquipManager->GetReverseFlag()){
							m_HaveItem = true;
							m_EquipData.id = m_MixRoot.id.z;
							m_EquipData.type = m_MixRoot.type;

							m_ItemEquipManager->SetTarget((float)m_Mouse.x,(float)m_Mouse.y);
							PlaySoundMem( m_Data->Get( DataManager::SoundSE19 ), DX_PLAYTYPE_BACK);
							m_memData = m_EquipData;
						}
						else if((m_memData.id != m_MixRoot.id.z && -1 != m_MixRoot.id.z) && m_memData.type == Equipment){
							m_EquipData.id = m_MixRoot.id.z;
							m_EquipData.type = m_MixRoot.type;
							m_HaveItem = true;
							
							m_ItemEquipManager->SetReverse(false);
							m_ItemEquipManager->SetTarget((float)m_Mouse.x,(float)m_Mouse.y);
							PlaySoundMem( m_Data->Get( DataManager::SoundSE19 ), DX_PLAYTYPE_BACK);

							m_memData.id = m_EquipData.id ;
							m_memData.type = m_EquipData.type;
						}
					}
					return true;
				}
				else{
					if(m_Data->m_SaveData.itemStatus[m_MixRoot.id.z] != DataManager::ITEM_NOT_FIND && 
						m_Data->m_SaveData.itemStatus[m_MixRoot.id.z] != DataManager::ITEM_NO_EXIST && m_memData.id != m_MixRoot.id.z){
							m_HaveItem = true;
							m_EquipData.id = m_MixRoot.id.z;
							m_EquipData.type = m_MixRoot.type;

							m_ItemEquipManager->SetReverse(false);
							m_ItemEquipManager->SetTarget((float)m_Mouse.x,(float)m_Mouse.y);
							PlaySoundMem( m_Data->Get( DataManager::SoundSE19 ), DX_PLAYTYPE_BACK);
							m_memData = m_EquipData;

							return true;
					}
					else{
						m_EquipData.id = -1;
						m_EquipData.type = -1;
						m_HaveItem = false;

						m_MixRoot.id.x = -1;
						m_MixRoot.id.y = -1;
						m_MixRoot.id.z = -1;
						m_MixRoot.type = -1;
						m_memData.id = -1;
						m_memData.type = -1;
						m_memData2.id = -1;
						m_memData2.type = -1;
						if(!m_HaveItem && !m_ItemEquipManager->GetMoveFlag() && !m_ItemEquipManager->GetStayFlag() && !m_ItemEquipManager->GetReverseFlag())
							PlaySoundMem( m_Data->Get( DataManager::SoundSE38 ), DX_PLAYTYPE_BACK);
						return false;
					}
				}
			}
		}
	}

	//ユニット
	for(int i = 0; i < GameMenu::cm_UnitHNum; i++)
	{
		for(int j = 0; j < GameMenu::cm_ColumnVNum; j++)
		{
			if(	m_Mouse.x > GameMenu::cm_UnitUIXPos+(j*GameMenu::cm_OneFrameWidth) && m_Mouse.x < GameMenu::cm_UnitUIXPos+(j*GameMenu::cm_OneFrameWidth)+GameMenu::cm_OneFrameWidth && 
				m_Mouse.y > GameMenu::cm_UnitUIYPos+(i*GameMenu::cm_OneFrameHeight) + GameMenu::cm_BackYMargin && m_Mouse.y < GameMenu::cm_UnitUIYPos+(i*GameMenu::cm_OneFrameHeight)+GameMenu::cm_OneFrameHeight + GameMenu::cm_BackYMargin){
				
				m_MixRoot.id.x = j;
				m_MixRoot.id.y = i;
				m_MixRoot.id.z = SORT_UnitIconSortList[j + (i * GameMenu::cm_ColumnVNum)];
				m_MixRoot.type = Unit;
				if(m_Data->m_SaveData.unitStatus[m_MixRoot.id.z] != DataManager::ITEM_NOT_FIND && 
					m_Data->m_SaveData.unitStatus[m_MixRoot.id.z] != DataManager::ITEM_NO_EXIST && 
					!m_ItemEquipManager->GetMoveFlag() && !m_ItemEquipManager->GetStayFlag() && 
					!m_ItemEquipManager->GetReverseFlag()){
					if(EquipCheck(m_MixRoot)){
						if(m_HaveItem && m_EquipData.id == m_MixRoot.id.z && m_EquipData.type == Unit){
							m_EquipData.id = -1;
							m_EquipData.type = -1;
							m_HaveItem = false;

							m_memData2.id = m_EquipData.id ;
							m_memData2.type = m_EquipData.type;
							return true;
						}
						else {//if( m_MixRoot.id.z != m_memData2.id && m_memData2.type != Equipment){
							m_memData2.id = m_EquipData.id ;
							m_memData2.type = m_EquipData.type;

							m_HaveItem = true;
							m_EquipData.id = m_MixRoot.id.z;
							m_EquipData.type = m_MixRoot.type;
							
							PlaySoundMem( m_Data->Get( DataManager::SoundSE19 ), DX_PLAYTYPE_BACK);

							return true;
						}

					}
					m_EquipData.id = -1;
					m_EquipData.type = -1;
					m_HaveItem = false;

					m_memData2.id = m_EquipData.id ;
					m_memData2.type = m_EquipData.type;
					return false;
					
				}
				else{
					m_EquipData.id = -1;
					m_EquipData.type = -1;
					m_HaveItem = false;

					m_MixRoot.id.x = -1;
					m_MixRoot.id.y = -1;
					m_MixRoot.id.z = -1;
					m_MixRoot.type = -1;
					m_memData.id = -1;
					m_memData.type = -1;
					m_memData2.id = -1;
					m_memData2.type = -1;
					if(!m_HaveItem)
						PlaySoundMem( m_Data->Get( DataManager::SoundSE38 ), DX_PLAYTYPE_BACK);
					return false;
				}
			}
		}
	}

	m_EquipData.id = -1;
	m_EquipData.type = -1;
	m_HaveItem = false;

	m_MixRoot.id.x = -1;
	m_MixRoot.id.y = -1;
	m_MixRoot.id.z = -1;
	m_MixRoot.type = -1;
	m_memData.id = -1;
	m_memData.type = -1;
	m_memData2.id = -1;
	m_memData2.type = -1;
	if(!m_HaveItem)
		PlaySoundMem( m_Data->Get( DataManager::SoundSE38 ), DX_PLAYTYPE_BACK);

	//エラー値
	return false;
}
//------------------------------------------------------------------------
//	@fn		EquipJudge
//	@brief	どの装備品・ユニットか判断
//------------------------------------------------------------------------
bool Equip :: EquipJudge(void){
	bool l_SE_flag = false;
	bool l_Skip_flag = false;
	int l_BackData = -1;

	if(m_HaveItem && m_Check){
		switch(m_EquipData.type){
		case Equipment:
			//装備
			for(int i = 0; i < 3; i++)
			{
				if(	m_Mouse.x > m_ItemEquipManager->GetPosition().x/800.0f && 
					m_Mouse.x < (m_ItemEquipManager->GetPosition().x + m_ItemEquipManager->GetSlotSize() + m_ItemEquipManager->GetWidth())/800.0f && 
					m_Mouse.y > (m_ItemEquipManager->GetPosition().y + (m_ItemEquipManager->GetSlotSize()*i))/600.0f && 
					m_Mouse.y < (m_ItemEquipManager->GetPosition().y + (m_ItemEquipManager->GetSlotSize()*i) + m_ItemEquipManager->GetSlotSize())/600.0f){
				
					if(m_Data->m_SaveData.itemStatus[m_EquipmentSlot[i].id.z] == DataManager::ITEM_EQUIP){

						m_Data->m_SaveData.itemStatus[m_EquipmentSlot[i].id.z] = DataManager::ITEM_EXIST;
					}
					else if(m_Data->m_SaveData.itemStatus[m_EquipmentSlot[i].id.z] == DataManager::ITEM_MIX_EQUIP){

						m_Data->m_SaveData.itemStatus[m_EquipmentSlot[i].id.z] = DataManager::ITEM_MIX;
					}

					l_BackData = m_EquipmentSlot[i].id.z;

					m_EquipmentSlot[i].id.z = m_EquipData.id;
					m_EquipmentSlot[i].id.x = m_EquipData.id/10;
					m_EquipmentSlot[i].id.y = m_EquipData.id%10;
					m_EquipmentSlot[i].type = m_EquipData.type;

					if(	m_Data->m_SaveData.itemStatus[m_EquipData.id] == DataManager::ITEM_EXIST || 
						m_Data->m_SaveData.itemStatus[m_EquipData.id] == DataManager::ITEM_NEW){

						m_Data->m_SaveData.itemStatus[m_EquipData.id] = DataManager::ITEM_EQUIP;
					}
					else if(m_Data->m_SaveData.itemStatus[m_EquipData.id] == DataManager::ITEM_MIX){

						m_Data->m_SaveData.itemStatus[m_EquipData.id] = DataManager::ITEM_MIX_EQUIP;
					}

					SetMogllEquipStatus(Equipment,i);

					PlaySoundMem( m_Data->Get( DataManager::SoundSE28 ), DX_PLAYTYPE_BACK);
					
					l_SE_flag = true;

					break;
				}
			}
			if(l_BackData != -1){
				m_HaveItem = true;
				PlaySoundMem( m_Data->Get( DataManager::SoundSE19 ), DX_PLAYTYPE_BACK);
				m_memData = m_EquipData;
				m_EquipData.id = l_BackData;
				m_EquipData.type = Equipment;
					
			}
			else{
				m_HaveItem = false;
				m_ItemEquipManager->SetReverse(true);
				m_EquipData.id = -1;
				m_EquipData.type = -1;

				return false;
			}
			break;
		case Unit:
			//ユニット
			for(int i = 0; i < 6; i++)
			{
				if(	m_Mouse.x > (float)((32 + 92*i)/800.0f) && m_Mouse.x < (float)(((32 + 92*i)+74)/800.0f) && 
					m_Mouse.y > (float)(522/600.0f) && m_Mouse.y < (float)((522+74)/600.0f)){

					if(m_UnitSlot[i].id.z != -1 && m_UnitSlot[i].id.z < 30){
						m_HaveItem = true;
						l_Skip_flag = true;
					}
					else{
						m_HaveItem = false;
					}

					l_BackData = m_UnitSlot[i].id.z;
						
					m_UnitSlot[i].id.z = m_EquipData.id;
					m_UnitSlot[i].id.x = m_EquipData.id/10;
					m_UnitSlot[i].id.y = m_EquipData.id%10;
					m_UnitSlot[i].type = m_EquipData.type;

					if(	m_Data->m_SaveData.unitStatus[m_EquipData.id] == DataManager::ITEM_EXIST || 
						m_Data->m_SaveData.unitStatus[m_EquipData.id] == DataManager::ITEM_NEW){

						m_Data->m_SaveData.unitStatus[m_EquipData.id] = DataManager::ITEM_EQUIP;
					}
					else if(m_Data->m_SaveData.unitStatus[m_EquipData.id] == DataManager::ITEM_MIX){

						m_Data->m_SaveData.unitStatus[m_EquipData.id] = DataManager::ITEM_MIX_EQUIP;
					}

					SetMogllEquipStatus(Unit,i);

					PlaySoundMem( m_Data->Get( DataManager::SoundSE28 ), DX_PLAYTYPE_BACK);

					l_SE_flag = true;

					if(m_UnitSlot[i].id.z != -1 && m_UnitSlot[i].id.z < 30){
						m_EquipData.id = l_BackData;
						m_EquipData.type = 1;
					}
					else{
						m_EquipData.id = -1;
						m_EquipData.type = -1;
					}

					break;
				}
			}

			if(!l_Skip_flag){
				//m_HaveItem = false;
				//m_EquipData.id = -1;
				//m_EquipData.type = -1;

				return false;
			}
			break;
		default:
			m_HaveItem = false;
			m_EquipData.id = -1;
			m_EquipData.type = -1;
			break;
		}

		if(!l_SE_flag){
			PlaySoundMem( m_Data->Get( DataManager::SoundSE38 ), DX_PLAYTYPE_BACK);
		}

		return true;
	}
	else if(!m_HaveItem && m_Check){
		for(int i = 0; i < 3; i++)
			{
				if(	m_Mouse.x > m_ItemEquipManager->GetPosition().x/800.0f && 
					m_Mouse.x < (m_ItemEquipManager->GetPosition().x + m_ItemEquipManager->GetWidth())/800.0f && 
					m_Mouse.y > (m_ItemEquipManager->GetPosition().y + (m_ItemEquipManager->GetSlotSize()*i))/600.0f && 
					m_Mouse.y < (m_ItemEquipManager->GetPosition().y + (m_ItemEquipManager->GetSlotSize()*i) + m_ItemEquipManager->GetSlotSize())/600.0f){

					if(m_Data->m_SaveData.itemStatus[m_EquipmentSlot[i].id.z] == DataManager::ITEM_MIX_EQUIP)
						m_Data->m_SaveData.itemStatus[m_EquipmentSlot[i].id.z] = DataManager::ITEM_MIX;
					else
						m_Data->m_SaveData.itemStatus[m_EquipmentSlot[i].id.z] = DataManager::ITEM_EXIST;

					if(m_EquipmentSlot[i].id.z != -1){
						m_HaveItem = true;
						m_EquipData.id = m_EquipmentSlot[i].id.z;
						m_EquipData.type = 0;
					}

					m_EquipmentSlot[i].id.z = -1;
					m_EquipmentSlot[i].id.x = -1;
					m_EquipmentSlot[i].id.y = -1;
					m_EquipmentSlot[i].type = -1;

					PlaySoundMem( m_Data->Get( DataManager::SoundSE06 ), DX_PLAYTYPE_BACK);

					SetMogllEquipStatus();

					return true;
				}
			}

		for(int i = 0; i < 6; i++){
			if(	m_Mouse.x > (float)((32 + 92*i)/800.0f) && m_Mouse.x < (float)(((32 + 92*i)+74)/800.0f) && 
				m_Mouse.y > (float)(522/600.0f) && m_Mouse.y < (float)((522+74)/600.0f) && m_UnitSlot[i].id.z > -1){
					if(m_Data->m_SaveData.unitStatus[m_UnitSlot[i].id.z] == DataManager::ITEM_MIX_EQUIP)
						m_Data->m_SaveData.unitStatus[m_UnitSlot[i].id.z] = DataManager::ITEM_MIX;
					else
						m_Data->m_SaveData.unitStatus[m_UnitSlot[i].id.z] = DataManager::ITEM_EXIST;

					m_HaveItem = true;
					m_EquipData.id = m_UnitSlot[i].id.z;
					m_EquipData.type = m_UnitSlot[i].type;

					m_UnitSlot[i].id.x = -1;
					m_UnitSlot[i].id.y = -1;
					m_UnitSlot[i].id.z = -1;
					m_UnitSlot[i].type = -1;

					m_memData2.id = m_EquipData.id ;
					m_memData2.type = m_EquipData.type;

					PlaySoundMem( m_Data->Get( DataManager::SoundSE06 ), DX_PLAYTYPE_BACK);

					SetMogllEquipStatus();

					return true;
			}
		}

		SetMogllEquipStatus();
	}

	//エラー値
	return false;
}

//------------------------------------------------------------------------
//	@fn		EquipCheck
//	@brief	重複チェック
//------------------------------------------------------------------------
bool Equip :: EquipCheck(void){
	switch(m_MixRoot.type){
	case Equipment:
		if(	m_Data->m_SaveData.itemStatus[m_MixRoot.id.z] == DataManager::ITEM_EXIST ||
			m_Data->m_SaveData.itemStatus[m_MixRoot.id.z] == DataManager::ITEM_EQUIP ||
			m_Data->m_SaveData.itemStatus[m_MixRoot.id.z] == DataManager::ITEM_MIX_EQUIP ||
			m_Data->m_SaveData.itemStatus[m_MixRoot.id.z] == DataManager::ITEM_MIX ||
			m_Data->m_SaveData.itemStatus[m_MixRoot.id.z] == DataManager::ITEM_NEW)
			m_End = true;
		return false;
		break;
	case Unit:
		if(	m_Data->m_SaveData.unitStatus[m_MixRoot.id.z] == DataManager::ITEM_EXIST ||
			m_Data->m_SaveData.unitStatus[m_MixRoot.id.z] == DataManager::ITEM_EQUIP ||
			m_Data->m_SaveData.unitStatus[m_MixRoot.id.z] == DataManager::ITEM_MIX_EQUIP ||
			m_Data->m_SaveData.unitStatus[m_MixRoot.id.z] == DataManager::ITEM_MIX ||
			m_Data->m_SaveData.unitStatus[m_MixRoot.id.z] == DataManager::ITEM_NEW)
			m_End = true;
		return false;
		break;
	}

	return true;
}
bool Equip :: EquipCheck(EquipData data){
	switch(m_MixRoot.type){
	case Equipment:
		if(	m_Data->m_SaveData.itemStatus[data.id.z] == DataManager::ITEM_EXIST ||
			m_Data->m_SaveData.itemStatus[data.id.z] == DataManager::ITEM_EQUIP ||
			m_Data->m_SaveData.itemStatus[data.id.z] == DataManager::ITEM_MIX_EQUIP ||
			m_Data->m_SaveData.itemStatus[data.id.z] == DataManager::ITEM_MIX ||
			m_Data->m_SaveData.itemStatus[data.id.z] == DataManager::ITEM_NEW)
			return true;
		break;
	case Unit:
		if(	m_Data->m_SaveData.unitStatus[data.id.z] == DataManager::ITEM_EXIST ||
			m_Data->m_SaveData.unitStatus[data.id.z] == DataManager::ITEM_EQUIP ||
			m_Data->m_SaveData.unitStatus[data.id.z] == DataManager::ITEM_MIX_EQUIP ||
			m_Data->m_SaveData.unitStatus[data.id.z] == DataManager::ITEM_MIX ||
			m_Data->m_SaveData.unitStatus[data.id.z] == DataManager::ITEM_NEW)
			return true;
		break;
	}

	return false;
}
//------------------------------------------------------------------------
//	@fn		
//	@brief	合成チェック
//------------------------------------------------------------------------
bool Equip :: MixCheck(void){
	int l_num = -1;

	if(m_MixRoot.id.z != -1){
		for(int i=0;i<cm_MixTreeNum;i++){
			if(m_MixTreeData[i].main.id == m_MixRoot.id.z && m_MixTreeData[i].main.type == m_MixRoot.type){
				l_num = i;
				break;
			}
			l_num = -1;
		}

		m_MixData = m_MixRoot;
		return MinRankExtractionNum(m_MixRoot,m_MixData,l_num);
	}

	return true;
}
//------------------------------------------------------------------------
//	@fn		MinRankExtraction
//	@brief	最少ランク素材抽出処理
//------------------------------------------------------------------------
bool Equip :: MinRankExtractionNum(EquipData root,EquipData artifacts,int matNum){
	EquipData l_Work;

	if(matNum == -1){
		switch(root.type){
		case Equipment:
			if(m_Data->m_SaveData.itemStatus[root.id.z] == DataManager::ITEM_MATERIAL){
				//分解確認処理
				if(!OriginExtraction(root)){
					m_ConfirmationFlag = true;
					PlaySoundMem( m_Data->Get( DataManager::SoundSE06 ), DX_PLAYTYPE_BACK);
					return false;
				}
				return true;
			}
			break;
		case Unit:
			if(m_Data->m_SaveData.unitStatus[root.id.z] == DataManager::ITEM_MATERIAL){
				//分解確認処理
				if(!OriginExtraction(root)){
					m_ConfirmationFlag = true;
					PlaySoundMem( m_Data->Get( DataManager::SoundSE06 ), DX_PLAYTYPE_BACK);
					return false;
				}
				return true;
			}
			break;
		}
	}

	switch(m_MixTreeData[matNum].main.type){
	case Equipment:
		if(m_Data->m_SaveData.itemStatus[m_MixTreeData[matNum].main.id] == DataManager::ITEM_MATERIAL){
			//渡すデータをセット
			l_Work.id.z = m_MixTreeData[matNum].main.id;
			l_Work.id.x = m_MixTreeData[matNum].main.id%10;
			l_Work.id.y = m_MixTreeData[matNum].main.id/10;
			l_Work.type = m_MixTreeData[matNum].main.type;
			//分解確認処理
			if(!OriginExtraction(l_Work)){
				m_ConfirmationFlag = true;
				PlaySoundMem( m_Data->Get( DataManager::SoundSE06 ), DX_PLAYTYPE_BACK);
				return false;
			}
			return true;
		}
		else if(m_Data->m_SaveData.itemStatus[m_MixTreeData[matNum].main.id] == DataManager::ITEM_MIX){
			return true;
		}
		break;
	case Unit:
		if(m_Data->m_SaveData.unitStatus[m_MixTreeData[matNum].main.id] == DataManager::ITEM_MATERIAL){
			//渡すデータをセット
			l_Work.id.z = m_MixTreeData[matNum].main.id;
			l_Work.id.x = m_MixTreeData[matNum].main.id%10;
			l_Work.id.y = m_MixTreeData[matNum].main.id/10;
			l_Work.type = m_MixTreeData[matNum].main.type;
			//分解確認処理
			if(!OriginExtraction(l_Work)){
				m_ConfirmationFlag = true;
				PlaySoundMem( m_Data->Get( DataManager::SoundSE06 ), DX_PLAYTYPE_BACK);
				return false;
			}
			return true;
		}
		else if(m_Data->m_SaveData.unitStatus[m_MixTreeData[matNum].main.id] == DataManager::ITEM_MIX){
			return true;
		}
		break;
	}

	//最少ランクの合成物を抽出する
	for(int i=0;i<4;i++){
		for(int j=0;j<cm_MixTreeNum;j++){
			if(m_MixTreeData[matNum].Material[i].id == m_MixTreeData[j].main.id && m_MixTreeData[matNum].Material[i].type == m_MixTreeData[j].main.type){
				switch(m_MixTreeData[j].main.type){
				case Equipment:
					if(	m_Data->m_SaveData.itemStatus[m_MixTreeData[j].main.id] == DataManager::ITEM_MATERIAL){
						//渡すデータをセット
						l_Work.id.z = m_MixTreeData[j].main.id;
						l_Work.id.x = m_MixTreeData[j].main.id%10;
						l_Work.id.y = m_MixTreeData[j].main.id/10;
						l_Work.type = m_MixTreeData[j].main.type;
						//分解確認処理
						if(!OriginExtraction(l_Work)){
							m_ConfirmationFlag = true;
							PlaySoundMem( m_Data->Get( DataManager::SoundSE06 ), DX_PLAYTYPE_BACK);
							return false;
						}
					}
					else if(m_Data->m_SaveData.itemStatus[m_MixTreeData[j].main.id] == DataManager::ITEM_CANMIX ||
							m_Data->m_SaveData.itemStatus[m_MixTreeData[j].main.id] == DataManager::ITEM_CANMIX_EXIST){

						//合成データをセット
						m_MixData.id.z = m_MixTreeData[j].main.id;
						m_MixData.id.x = m_MixTreeData[j].main.id%10;
						m_MixData.id.y = m_MixTreeData[j].main.id/10;
						m_MixData.type = m_MixTreeData[j].main.type;
						//合成フラグを立てる
						m_ItemFlag = Flag_Mix;
						m_ConfirmationFlag = true;
						PlaySoundMem( m_Data->Get( DataManager::SoundSE06 ), DX_PLAYTYPE_BACK);
						//最小ランクの素材を探す
						return MinRankExtractionNum(root,m_MixData,j);
					}
					else
						j+=cm_MixTreeNum;
					break;
				case Unit:
					if(	m_Data->m_SaveData.unitStatus[m_MixTreeData[j].main.id] == DataManager::ITEM_MATERIAL){
						
						//渡すデータをセット
						l_Work.id.z = m_MixTreeData[j].main.id;
						l_Work.id.x = m_MixTreeData[j].main.id%10;
						l_Work.id.y = m_MixTreeData[j].main.id/10;
						l_Work.type = m_MixTreeData[j].main.type;
						//分解確認処理
						if(!OriginExtraction(l_Work)){
							m_ConfirmationFlag = true;
							PlaySoundMem( m_Data->Get( DataManager::SoundSE06 ), DX_PLAYTYPE_BACK);
							return false;
						}
					}
					else if(m_Data->m_SaveData.unitStatus[m_MixTreeData[j].main.id] == DataManager::ITEM_CANMIX ||
							m_Data->m_SaveData.unitStatus[m_MixTreeData[j].main.id] == DataManager::ITEM_CANMIX_EXIST){

						//合成データをセット
						m_MixData.id.z = m_MixTreeData[j].main.id;
						m_MixData.id.x = m_MixTreeData[j].main.id%10;
						m_MixData.id.y = m_MixTreeData[j].main.id/10;
						m_MixData.type = m_MixTreeData[j].main.type;
						//合成フラグを立てる
						m_ItemFlag = Flag_Mix;
						m_ConfirmationFlag = true;
						PlaySoundMem( m_Data->Get( DataManager::SoundSE06 ), DX_PLAYTYPE_BACK);
						//最小ランクの素材を探す
						return MinRankExtractionNum(root,m_MixData,j);
					}
					else
						j+=cm_MixTreeNum;
					break;
				}
				break;
			}
		}

		switch(m_MixTreeData[matNum].Material[i].type){
			case Equipment:
				for(int j=0;j<50;j++){
					if(m_MixTreeData[matNum].Material[i].id == SORT_ItemIconSortList[j]){
						if( m_Data->m_SaveData.itemStatus[m_MixTreeData[matNum].Material[i].id] == DataManager::ITEM_EXIST || 
							m_Data->m_SaveData.itemStatus[m_MixTreeData[matNum].Material[i].id] == DataManager::ITEM_NEW){
								break;
						}
						else if(m_Data->m_SaveData.itemStatus[m_MixTreeData[matNum].Material[i].id] == DataManager::ITEM_MATERIAL){
							//渡すデータをセット
							l_Work.id.z = m_MixTreeData[matNum].Material[i].id;
							l_Work.id.x = l_Work.id.z%10;
							l_Work.id.y = l_Work.id.z/10;
							l_Work.type = m_MixTreeData[matNum].Material[i].type;
							//分解確認処理
							if(!OriginExtraction(l_Work)){
								m_ConfirmationFlag = true;
								PlaySoundMem( m_Data->Get( DataManager::SoundSE06 ), DX_PLAYTYPE_BACK);
								return false;
							}
						}
					}
				}
				break;
			case Unit:
				for(int j=0;j<3;j++){
					if(m_MixTreeData[matNum].Material[i].id == SORT_UnitIconSortList[j]){
						if( m_Data->m_SaveData.unitStatus[m_MixTreeData[matNum].Material[i].id] == DataManager::ITEM_EXIST || 
							m_Data->m_SaveData.unitStatus[m_MixTreeData[matNum].Material[i].id] == DataManager::ITEM_NEW){
								break;
						}
						else if(m_Data->m_SaveData.unitStatus[m_MixTreeData[matNum].Material[i].id] == DataManager::ITEM_MATERIAL){
							//渡すデータをセット
							l_Work.id.z = m_MixTreeData[matNum].Material[i].id;
							l_Work.id.x = l_Work.id.z%10;
							l_Work.id.y = l_Work.id.z/10;
							l_Work.type = m_MixTreeData[matNum].Material[i].type;
							//分解確認処理
							if(!OriginExtraction(l_Work)){
								m_ConfirmationFlag = true;
								PlaySoundMem( m_Data->Get( DataManager::SoundSE06 ), DX_PLAYTYPE_BACK);
								return false;
							}
						}
					}
				}
				break;
		}
	}

	//ルートのアイテムを合成指示
	if(artifacts.id.z == root.id.z && artifacts.type == root.type){
		m_ItemFlag = Flag_Mix;
		m_End = true;
		//Mix();
		return true;
	}

	//現在のアイテムを合成指示
	switch(artifacts.type){
	case Equipment:
		if(m_Data->m_SaveData.itemStatus[artifacts.id.z] != DataManager::ITEM_MIX){
			m_ConfirmationFlag = true;
			PlaySoundMem( m_Data->Get( DataManager::SoundSE06 ), DX_PLAYTYPE_BACK);
			return false;
		}
		break;
	case Unit:
		if(m_Data->m_SaveData.unitStatus[artifacts.id.z] != DataManager::ITEM_MIX){
			m_ConfirmationFlag = true;
			PlaySoundMem( m_Data->Get( DataManager::SoundSE06 ), DX_PLAYTYPE_BACK);
			return false;
		}
		break;
	}

	return false;
}
//------------------------------------------------------------------------
//	@fn		OriginExtraction
//	@brief	素材から合成先を抽出:再帰処理
//------------------------------------------------------------------------
bool  Equip :: OriginExtraction(EquipData artifacts){

	for(int i=0;i<cm_MixTreeNum;i++){
		for(int j=0;j<4;j++){
			if(m_MixTreeData[i].Material[j].id == artifacts.id.z && m_MixTreeData[i].Material[j].type == artifacts.type){
				switch(m_MixTreeData[i].main.type){
				case Equipment:
					//必要素材の合成元だったとき
					if(	m_Data->m_SaveData.itemStatus[m_MixTreeData[i].main.id] == DataManager::ITEM_MIX ||
						m_Data->m_SaveData.itemStatus[m_MixTreeData[i].main.id] == DataManager::ITEM_MIX_EQUIP){
						m_BreakData.id.z = m_MixTreeData[i].main.id;
						m_BreakData.id.x = m_MixTreeData[i].main.id%10;
						m_BreakData.id.y = m_MixTreeData[i].main.id/10;
						m_BreakData.type = m_MixTreeData[i].main.type;
						m_ItemFlag = Flag_Break;
						return false;
					}
					//必要素材が別のものの素材になっていた時
					else if(m_Data->m_SaveData.itemStatus[m_MixTreeData[i].main.id] == DataManager::ITEM_MATERIAL){
						m_BreakData.id.z = m_MixTreeData[i].main.id;
						m_BreakData.id.x = m_MixTreeData[i].main.id%10;
						m_BreakData.id.y = m_MixTreeData[i].main.id/10;
						m_BreakData.type = m_MixTreeData[i].main.type;
						return OriginExtraction(m_BreakData);
					}

					break;
				case Unit:
					//必要素材の合成元だったとき
					if(	m_Data->m_SaveData.unitStatus[m_MixTreeData[i].main.id] == DataManager::ITEM_MIX ||
						m_Data->m_SaveData.unitStatus[m_MixTreeData[i].main.id] == DataManager::ITEM_MIX_EQUIP){
						m_BreakData.id.z = m_MixTreeData[i].main.id;
						m_BreakData.id.x = m_MixTreeData[i].main.id%10;
						m_BreakData.id.y = m_MixTreeData[i].main.id/10;
						m_BreakData.type = m_MixTreeData[i].main.type;
						m_ItemFlag = Flag_Break;
						return false;
					}
					//必要素材が別のものの素材になっていた時
					else if(m_Data->m_SaveData.unitStatus[m_MixTreeData[i].main.id] == DataManager::ITEM_MATERIAL){
						m_BreakData.id.z = m_MixTreeData[i].main.id;
						m_BreakData.id.x = m_MixTreeData[i].main.id%10;
						m_BreakData.id.y = m_MixTreeData[i].main.id/10;
						m_BreakData.type = m_MixTreeData[i].main.type;
						return OriginExtraction(m_BreakData);
					}

					break;
				}
				break;
			}
		}
	}

	return true;
}
//------------------------------------------------------------------------
//	@fn		Mix
//	@brief	合成処理
//------------------------------------------------------------------------
void Equip :: Mix(void){
	int num = 0;				//リスト番号を格納

	//合成フラグが立っている時
	if(m_ItemFlag == Flag_Mix){
		//ツリーの何番目のアイテムが検索
		for(int i=0;i<cm_MixTreeNum;i++){
			if(m_MixTreeData[i].main.id == m_MixData.id.z && m_MixTreeData[i].main.type == m_MixData.type){
				num = i;		//リスト番号を格納
				break;
			}
		}

		//合成に使われたもののステータスを素材に変更
		for(int i=0;i<4;i++){
			switch(m_MixTreeData[num].Material[i].type){
			case Equipment:
				if(m_MixTreeData[num].Material[i].type != None)
					m_Data->m_SaveData.itemStatus[m_MixTreeData[num].Material[i].id] = DataManager::ITEM_MATERIAL;
				break;
			case Unit:
				if(m_MixTreeData[num].Material[i].type != None)
					m_Data->m_SaveData.unitStatus[m_MixTreeData[num].Material[i].id] = DataManager::ITEM_MATERIAL;
				break;
			}
		}

		//合成:ステータスを合成済みに変更
		switch(m_MixData.type){
		case Equipment:
			m_Data->m_SaveData.itemStatus[m_MixData.id.z] = DataManager::ITEM_MIX;
			break;
		case Unit:
			m_Data->m_SaveData.unitStatus[m_MixData.id.z] = DataManager::ITEM_MIX;
			break;
		}

		m_ItemFlag = None;
	}
}
//------------------------------------------------------------------------
//	@fn		Break
//	@brief	分解処理
//------------------------------------------------------------------------
void Equip ::Break(void){
	int num = 0;

	//合成フラグが立っている時
	if(m_ItemFlag == Flag_Break){
		//ツリーの何番目のアイテムが検索
		for(int i=0;i<cm_MixTreeNum;i++){
			if(m_MixTreeData[i].main.id == m_BreakData.id.z && m_MixTreeData[i].main.type == m_BreakData.type){
				num = i;		//リスト番号を格納
				break;
			}
		}

		//合成に使われていたもののステータスを持っているに変更
		for(int i=0;i<4;i++){
			switch(m_MixTreeData[num].Material[i].type){
			case Equipment:
				if(m_MixTreeData[num].Material[i].type != None)
					m_Data->m_SaveData.itemStatus[m_MixTreeData[num].Material[i].id] = DataManager::ITEM_EXIST;
				for(int j=0;j<cm_MixTreeNum;j++){
					if(m_MixTreeData[num].Material[i].id == m_MixTreeData[j].main.id){
						switch(m_MixTreeData[num].Material[i].type){
						case Equipment:
							if(m_MixTreeData[num].Material[i].type != None)
								m_Data->m_SaveData.itemStatus[m_MixTreeData[num].Material[i].id] = DataManager::ITEM_MIX;
							break;
						case Unit:
							if(m_MixTreeData[num].Material[i].type != None)
								m_Data->m_SaveData.itemStatus[m_MixTreeData[num].Material[i].id] = DataManager::ITEM_MIX;
							break;
						}
						break;
					}
				}
				break;
			case Unit:
				if(m_MixTreeData[num].Material[i].type != None)
					m_Data->m_SaveData.unitStatus[m_MixTreeData[num].Material[i].id] = DataManager::ITEM_EXIST;
				for(int j=0;j<cm_MixTreeNum;j++){
					if(m_MixTreeData[num].Material[i].id == m_MixTreeData[j].main.id){
						switch(m_MixTreeData[num].Material[i].type){
						case Equipment:
							if(m_MixTreeData[num].Material[i].type != None)
								m_Data->m_SaveData.unitStatus[m_MixTreeData[num].Material[i].id] = DataManager::ITEM_MIX;
							break;
						case Unit:
							if(m_MixTreeData[num].Material[i].type != None)
								m_Data->m_SaveData.unitStatus[m_MixTreeData[num].Material[i].id] = DataManager::ITEM_MIX;
							break;
						}
						break;
					}
				}
				break;
			}
		}

		//分解:ステータスをに変更
		switch(m_BreakData.type){
		case Equipment:
			m_Data->m_SaveData.itemStatus[m_BreakData.id.z] = DataManager::ITEM_CANMIX_EXIST;
			break;
		case Unit:
			m_Data->m_SaveData.unitStatus[m_BreakData.id.z] = DataManager::ITEM_CANMIX_EXIST;
			break;
		}

		m_ItemFlag = None;
	}
}
//------------------------------------------------------------------------
//	@fn		Confirmation
//	@brief	確認処理
//------------------------------------------------------------------------
bool Equip ::Confirmation(void){
	if(m_ConfirmationFlag){
		if(GameInput::GetInstance().GetMouse(GameInput::MouseLeftTrg)){
			m_OkCancel = Flag_OK;
			PlaySoundMem( m_Data->Get( DataManager::SoundSE28 ), DX_PLAYTYPE_BACK);
			return true;
		}
		if(GameInput::GetInstance().GetMouse(GameInput::MouseRightTrg)){
			m_OkCancel = Flag_Cancel;
			PlaySoundMem( m_Data->Get( DataManager::SoundSE06 ), DX_PLAYTYPE_BACK);
			return true;
		}
	}
	
	return false;
}
//------------------------------------------------------------------------
//	@fn		EquipConfirmation
//	@brief	装備の確認処理
//------------------------------------------------------------------------
void Equip ::EquipConfirmation(void){
	int l_count = 0;

	for(int i=0;i<3;i++){
		if(	m_EquipmentSlot[i].id.z < 0 ||
			(m_Data->m_SaveData.itemStatus[m_EquipmentSlot[i].id.z] != DataManager::ITEM_EQUIP &&
			m_Data->m_SaveData.itemStatus[m_EquipmentSlot[i].id.z] != DataManager::ITEM_MIX_EQUIP)){

				m_EquipmentSlot[i].id.z = -1;
				m_EquipmentSlot[i].id.x = -1;
				m_EquipmentSlot[i].id.y = -1;
				m_EquipmentSlot[i].type = None;
		}
	}

	l_count = 0;

	for(int i=0;i<6;i++){
		if(	m_UnitSlot[i].id.z < 0 ||
			(m_Data->m_SaveData.unitStatus[m_UnitSlot[i].id.z] != DataManager::ITEM_EQUIP &&
			m_Data->m_SaveData.unitStatus[m_UnitSlot[i].id.z] != DataManager::ITEM_MIX_EQUIP)){

				m_UnitSlot[i].id.z = -1;
				m_UnitSlot[i].id.x = -1;
				m_UnitSlot[i].id.y = -1;
				m_UnitSlot[i].type = None;
		}
	}

	SetMogllEquipStatus();

	Clear();
}

//------------------------------------------------------------------------
//	@fn		Clear
//	@brief	処理終了後初期化処理
//------------------------------------------------------------------------
void Equip :: Clear(void){
	m_Check = false;
	m_ConfirmationFlag = false;
	m_OkCancel = -1;
	m_ItemFlag = -1;

	m_MixRoot.id.x = -1;
	m_MixRoot.id.y = -1;
	m_MixRoot.id.z = -1;
	m_MixRoot.type = -1;

	m_MixData.id.x = -1;
	m_MixData.id.y = -1;
	m_MixData.id.z = -1;
	m_MixData.type = -1;

	m_BreakData.id.x = -1;
	m_BreakData.id.y = -1;
	m_BreakData.id.z = -1;
	m_BreakData.type = -1;
}
//------------------------------------------------------------------------
//	@fn		DrawHaveItem
//	@brief	描画処理
//------------------------------------------------------------------------
void Equip :: DrawHaveItem(void){
	DXLibMath::Vector2 l_Mouse;

	l_Mouse.x = GameInput::GetInstance().GetXf();
	l_Mouse.y = GameInput::GetInstance().GetYf();

	if(m_HaveItem){
		switch(m_EquipData.type){
		case Equipment:
			DXLibMath::DrawRotaGraphResize(l_Mouse.x,l_Mouse.y,0.8,0.0,
				m_Data->GetGraphicGroupData((DataManager::GraphicSet)(m_EquipData.id + DataManager::GG_ITEM0)),TRUE);
			break;
		case Unit:
			DXLibMath::DrawRotaGraphResize(l_Mouse.x,l_Mouse.y,1.5,0.0,
				m_Data->GetGraphicGroupData((DataManager::GraphicSet)(m_EquipData.id + DataManager::GG_UNIT_Treasure)),TRUE);
			break;
		}
	}
}
//------------------------------------------------------------------------
//	@fn		DrawSlotOver
//	@brief	描画処理
//------------------------------------------------------------------------
void Equip :: DrawSlotOver(void){
	DXLibMath::Vector2 l_Mouse;
	static int l_eSpan = 0; 
	static int l_uSpan = 0; 
	static int l_memNum = -1;
	int l_size;

	l_Mouse.x = GameInput::GetInstance().GetXf();
	l_Mouse.y = GameInput::GetInstance().GetYf();

	//装備
	for(int i = 0; i < 3; i++)
	{
		if(	l_Mouse.x > m_ItemEquipManager->GetPosition().x/800.0f && 
			l_Mouse.x < (m_ItemEquipManager->GetPosition().x + m_ItemEquipManager->GetSlotSize() + m_ItemEquipManager->GetWidth())/800.0f && 
			l_Mouse.y > (m_ItemEquipManager->GetPosition().y + (m_ItemEquipManager->GetSlotSize()*i))/600.0f && 
			l_Mouse.y < (m_ItemEquipManager->GetPosition().y + (m_ItemEquipManager->GetSlotSize()*i) + m_ItemEquipManager->GetSlotSize())/600.0f &&
			!m_ConfirmationFlag && (m_EquipData.type == 0 || m_EquipData.type == -1)){

			//描画時スロット幅をプラスするかの判定
			if(m_ItemEquipManager->GetStayFlag()){
				l_size = 1;
			}
			else{
				l_size = 0;
			}

			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);									//透過率のセット
			DrawBox(static_cast<int>( m_ItemEquipManager->GetPosition().x ) - m_ItemSlotPos,static_cast<int>( ( m_ItemEquipManager->GetPosition().y + ( m_ItemEquipManager->GetSlotSize()*i ) ) ),
					static_cast<int>( ( m_ItemEquipManager->GetPosition().x + ( m_ItemEquipManager->GetSlotSize()*l_size ) + m_ItemEquipManager->GetWidth() ) ),
					static_cast<int>( ( m_ItemEquipManager->GetPosition().y + ( m_ItemEquipManager->GetSlotSize()*i ) + m_ItemEquipManager->GetSlotSize() ) ),
						GetColor(255,255,255), TRUE);
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);									//透過率のセット

			//if(m_HaveItem && l_memNum != i)
			//	PlaySoundMem( m_Data->Get( DataManager::SoundSE07 ), DX_PLAYTYPE_BACK);

			l_memNum = i;
			l_eSpan = 0;
			m_EquipCount = 0;

			return;
		}
	}

	if(m_HaveItem && m_EquipData.type == Equipment){
		if(l_eSpan == 60){
			if(m_EquipCount < 30){
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);									//透過率のセット
				//スロットのフレームのバックに黒背景
				DrawBox(	static_cast<int>(m_ItemEquipManager->GetPosition().x) , static_cast<int>(m_ItemEquipManager->GetPosition().y), 
							static_cast<int>(m_ItemEquipManager->GetPosition().x + m_ItemEquipManager->GetWidth() + m_ItemEquipManager->GetSlotSize()), 
							static_cast<int>(m_ItemEquipManager->GetPosition().y + m_ItemEquipManager->GetHeight()),
							GetColor(255,255,255), TRUE );
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);									//透過率のセット
				m_EquipCount++;
			}
			else if(m_EquipCount >= 30 && m_EquipCount < 60){
			
				m_EquipCount++;
			}
			else{
				m_EquipCount = 0;
			}
		}
		else{
			if(l_eSpan < 60)
				l_eSpan++;
		}
	}
	else{
		m_EquipCount = 0;
		l_eSpan = 0;
	}

	//ユニット
	for(int i = 0; i < 6; i++)
	{
		if(	l_Mouse.x > (float)((32 + 92*i)/800.0f) && l_Mouse.x < (float)(((32 + 92*i)+74)/800.0f) && 
			l_Mouse.y > (float)(522/600.0f) && l_Mouse.y < (float)((522+74)/600.0f) && !m_ConfirmationFlag && (m_EquipData.type == 1 || m_EquipData.type == -1)){
						
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);									//透過率のセット
			DrawBox((32 + 92*i),522,74+(32 + 92*i),74+522,GetColor(255,255,255), TRUE);
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);									//透過率のセット

			if(m_HaveItem && l_memNum != i)
				PlaySoundMem( m_Data->Get( DataManager::SoundSE07 ), DX_PLAYTYPE_BACK);

			l_memNum = i;
			l_uSpan = 0;
			m_UnitCount = 0;

			return;
		}
	}

	if(m_HaveItem && m_EquipData.type == Unit){
		if(l_uSpan == 60){
			if(m_UnitCount < 30){
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);									//透過率のセット
				for(int i = 0; i < 6; i++){
					//スロットのフレームのバックに黒背景
					DrawBox( (32 + 92*i) , 522 , (32 + 92*i)+74 , 522+74 , GetColor(255,255,255), TRUE );
				}
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);									//透過率のセット
				m_UnitCount++;
			}
			else if(m_UnitCount >= 30 && m_UnitCount < 60){
			
				m_UnitCount++;
			}
			else{
				m_UnitCount = 0;
			}
		}
		else{
			if(l_uSpan < 60)
				l_uSpan++;
		}
	}
	else{
		m_UnitCount = 0;
		l_uSpan = 0;
	}
}
//------------------------------------------------------------------------
//	@fn		DrawSlot
//	@brief	描画処理
//------------------------------------------------------------------------
void Equip :: DrawSlot(void){
	DXLibMath::Vector2 l_Mouse;
	static int l_frame = 0;

	l_Mouse.x = GameInput::GetInstance().GetXf();
	l_Mouse.y = GameInput::GetInstance().GetYf();

	//装備 
	if(	!m_ItemEquipManager->GetStayFlag() && !m_ItemEquipManager->GetMoveFlag() && !m_ItemEquipManager->GetReverseFlag() &&
		l_Mouse.x > m_ItemEquipManager->GetPosition().x/800.0f && 
		l_Mouse.x < (m_ItemEquipManager->GetPosition().x + m_ItemEquipManager->GetSlotSize() + m_ItemEquipManager->GetWidth())/800.0f && 
		l_Mouse.y > (m_ItemEquipManager->GetPosition().y)/600.0f && 
		l_Mouse.y < (m_ItemEquipManager->GetPosition().y + (m_ItemEquipManager->GetSlotSize()*3))/600.0f && (m_EquipData.type == 0 || m_EquipData.type == -1)){

		//スロットの描画
		if(l_frame < cm_ItemSlotPosFrame){
			m_ItemSlotPos += m_ItemEquipManager->GetSlotSize()/cm_ItemSlotPosFrame;
			l_frame++;
		}
		DrawGraph( static_cast<int>( m_ItemEquipManager->GetPosition().x-m_ItemSlotPos ), static_cast<int>( m_ItemEquipManager->GetPosition().y ),
					m_Data->Get( DataManager::Equipment_Icon_Frame ), TRUE );
		for( int j = 0; j < 3; j++ )
		{
			int id = m_Data->m_MogllStatus.equip[j];
			if( id != -1 )
			{
				DrawExtendGraph(static_cast<int>( m_ItemEquipManager->GetPosition().x-m_ItemSlotPos ), static_cast<int>( m_ItemEquipManager->GetPosition().y+( 45*j ) ),
								static_cast<int>( m_ItemEquipManager->GetPosition().x+45-m_ItemSlotPos ), static_cast<int>( m_ItemEquipManager->GetPosition().y+( 45*j )+45 ), 
								m_Data->GetGraphicGroupData( id + DataManager::GG_ITEM0), TRUE );
			}
		}

		//描画時スロット幅をプラスするかの判定
		if(m_ItemEquipManager->GetStayFlag()){
			l_frame = 0;
		}

		return;
	}
	else{
		//スロットの描画
		if(l_frame > 0){
			m_ItemSlotPos -= m_ItemEquipManager->GetSlotSize()/cm_ItemSlotPosFrame;
			l_frame--;
		}
		else
			return;

		DrawGraph( static_cast<int>( m_ItemEquipManager->GetPosition().x-m_ItemSlotPos ), static_cast<int>( m_ItemEquipManager->GetPosition().y ),
					m_Data->Get( DataManager::Equipment_Icon_Frame ), TRUE );

		return;
	}

	l_frame = 0;
	m_ItemSlotPos = 0;
}
//------------------------------------------------------------------------
//	@fn		DrawEquipSymbol
//	@brief	装備済みシンボルの描画処理
//------------------------------------------------------------------------
void Equip :: DrawEquipSymbol(void){
	//装備品
	for(int i=0;i<3;i++){
		if(m_EquipmentSlot[i].id.z != -1){
			DXLibMath::DrawExtendGraphResize(	GameMenu::cm_EquipmentUIXPos+(ReverseGetID(m_EquipmentSlot[i].id.z,0)%10*GameMenu::cm_OneFrameWidth),
												GameMenu::cm_EquipmentUIYPos+(ReverseGetID(m_EquipmentSlot[i].id.z,0)/10*GameMenu::cm_OneFrameHeight) + GameMenu::cm_BackYMargin,
												GameMenu::cm_OneFrameWidth,GameMenu::cm_OneFrameHeight, m_Data->Get(DataManager::Equipment_sin), TRUE);
		}
	}
	//ユニット
	for(int i=0;i<6;i++){
		if(m_UnitSlot[i].id.z != -1 && m_UnitSlot[i].id.z != 30){
			DXLibMath::DrawExtendGraphResize(	GameMenu::cm_UnitUIXPos+(ReverseGetID(m_UnitSlot[i].id.z,1)%10*GameMenu::cm_OneFrameWidth),
												GameMenu::cm_UnitUIYPos+(ReverseGetID(m_UnitSlot[i].id.z,1)/10*GameMenu::cm_OneFrameHeight) + GameMenu::cm_BackYMargin,
												GameMenu::cm_OneFrameWidth,GameMenu::cm_OneFrameHeight, m_Data->Get(DataManager::Equipment_sin), TRUE);
		}
	}
}
//------------------------------------------------------------------------
//	@fn		DrawNewSymbol
//	@brief	NEWシンボルの描画処理
//------------------------------------------------------------------------
void Equip :: DrawNewSymbol(void){
	//装備品
	for(int i=0;i<60;i++){
		if(	m_Data->m_SaveData.itemStatus[i] == DataManager::ITEM_NEW){
			DXLibMath::DrawExtendGraphResize(	GameMenu::cm_EquipmentUIXPos+(ReverseGetID(i,0)%10*GameMenu::cm_OneFrameWidth),
												GameMenu::cm_EquipmentUIYPos+(ReverseGetID(i,0)/10*GameMenu::cm_OneFrameHeight) + GameMenu::cm_BackYMargin,
												30.0f/800.0f,10.0f/600.0f, m_Data->Get(DataManager::New_sin), TRUE);
		}
	}
	//ユニット
	for(int i=0;i<30;i++){
		if(	m_Data->m_SaveData.unitStatus[i] == DataManager::ITEM_NEW){
			DXLibMath::DrawExtendGraphResize(	GameMenu::cm_UnitUIXPos+(ReverseGetID(i,1)%10*GameMenu::cm_OneFrameWidth),
												GameMenu::cm_UnitUIYPos+(ReverseGetID(i,1)/10*GameMenu::cm_OneFrameHeight) + GameMenu::cm_BackYMargin,
												30.0f/800.0f,10.0f/600.0f, m_Data->Get(DataManager::New_sin), TRUE);
		}
	}
}
//------------------------------------------------------------------------
//	@fn		
//	@brief	処理
//------------------------------------------------------------------------
int Equip :: ReverseGetID(int id,char type){
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
//	@fn		CheckEnable
//	@brief	チェックフラグを立てる処理
//------------------------------------------------------------------------
void Equip :: CheckEnable(void){
	m_Check = true;
}

void Equip :: ResetHaveItem(void){
	m_HaveItem = false;
	m_EquipData.id = -1;
	m_EquipData.type = -1;
}
void Equip :: ResetHaveItem2(void){
	if((!m_ItemEquipManager->GetMoveFlag() && m_ItemEquipManager->GetStayFlag() && !m_ItemEquipManager->GetReverseFlag()) || m_EquipData.type == 1){
		m_HaveItem = false;
		m_EquipData.id = -1;
		m_EquipData.type = -1;

		m_MixRoot.id.x = -1;
		m_MixRoot.id.y = -1;
		m_MixRoot.id.z = -1;
		m_MixRoot.type = -1;
		m_memData.id = -1;
		m_memData.type = -1;
		m_memData2.id = -1;
		m_memData2.type = -1;

		m_ItemEquipManager->SetReverse(true);

		PlaySoundMem( m_Data->Get( DataManager::SoundSE38 ), DX_PLAYTYPE_BACK);
	}
}

void Equip :: SetItemEquip(ItemEquip* instance){
	m_ItemEquipManager = instance;
}

bool Equip :: GetHaveFlag(void){
	return m_HaveItem;
}

//========================================================================
//	End of file
//========================================================================
