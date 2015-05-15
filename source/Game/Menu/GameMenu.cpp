//========================================================================
//	@file	GameMenu.cpp
//	@note	インベントリ
//	@author	RyotaUehara
//========================================================================
//------------------------------------------------------------------------
//	IncludeHeader
//------------------------------------------------------------------------
#include "GameMenu.h"
#include "MixTreeData.h"
#include "MenuIconSort.h"
#include "../System/GameInput.h"
#include "DxLib.h"

//------------------------------------------------------------------------
//	Const
//------------------------------------------------------------------------
//インベントリ背景
const float		GameMenu :: cm_BackGroundLeftPos			= -0.75f;						//格納時位置
const float		GameMenu :: cm_BackGroundXPos				= 0.0f;							//表示位置
const float		GameMenu :: cm_BackGroundYPos				= 0.0f;							//表示位置
const float		GameMenu :: cm_BackGroundMovement			= -cm_BackGroundLeftPos/30;		//移動割合
const float		GameMenu :: cm_BackYMargin					= 20/600.0f;
const float		GameMenu :: cm_BackGroundWidth				= 600/800.0f;//0.75f;						//表示幅割合
const float		GameMenu :: cm_BackGroundHeight				= 480/600.0f;//13.0f / 15.0f;				//表示高さ割合

//欄
const int		GameMenu :: cm_EquipmentHNum				= 6;							//装備欄行数
const int		GameMenu :: cm_UnitHNum						= 3;							//ユニット欄行数
const int		GameMenu :: cm_ColumnVNum					= 10;							//欄列数

//説明
const float		GameMenu :: cm_DescriptionFrameXPos			= 600.0f/800.0f;				//X
const float		GameMenu :: cm_DescriptionFrameYPos			= 10.0f/600.0f;					//Y
const float		GameMenu :: cm_DescriptionFrameXMargin		= 0.03125f;						//X補正
const float		GameMenu :: cm_DescriptionFrameYMargin		= 0.04166f;						//Y補正
const float		GameMenu :: cm_DescriptionFrameWidth		= 0.3125f;						//幅
const float		GameMenu :: cm_DescriptionFrameHeight		= 0.25f;						//高さ

const float		GameMenu :: cm_DescriptionNameMarginX		= 0.025f;						//説明名前x補正
const float		GameMenu :: cm_DescriptionNameMarginY		= 0.033f;						//説明名前y補正
const float		GameMenu :: cm_DescriptionMarginX			= 0.03125f;						//説明文x補正値
const float		GameMenu :: cm_DescriptionMarginY			= 0.0833f;						//説明文y補正値

//const float		GameMenu :: cm_ColumnUIXPos					= 0.175f;						//欄の表示x位置割合
const float		GameMenu :: cm_EquipmentUIXPos				= 140/800.0f;							//欄の表示x位置割合
const float		GameMenu :: cm_EquipmentUIWidth				= 440/800.0f;							//欄の表示幅割合
const float		GameMenu :: cm_EquipmentUIYPos				= 40/600.0f;							//装備欄の表示y位置割合
const float		GameMenu :: cm_EquipmentUIHeight			= 264/600.0f;							//装備欄の表示高さ割合
	  
const float		GameMenu :: cm_UnitUIXPos					= 68/800.0f;						//ユニット欄の表示y位置割合
const float		GameMenu :: cm_UnitUIYPos					= 319/600.0f;						//ユニット欄の表示y位置割合
const float		GameMenu :: cm_UnitUIHeight					= 135/600.0f;						//ユニット欄の表示高さ割合

const float		GameMenu :: cm_OneFrameWidth				= 44/800.0f;							//一枠の幅
const float		GameMenu :: cm_OneFrameHeight				= 44/600.0f;						//一枠の高さ

const float		GameMenu :: cm_DescriptionNameSize			= 0.0225f;						//説明:名前の文字サイズ割合
const float		GameMenu :: cm_DescriptionSize				= 0.01625f;						//説明:説明分の文字サイズ割合

const int		GameMenu :: cm_NameSpan						= 3;							//
const int		GameMenu :: cm_DescriptionSpan				= 2;							//

//インベントリ開閉
const float		GameMenu :: cm_InventlyX					= 0.78375f;						//x
const float		GameMenu :: cm_InventlyY					= 0.61f;						//y
const float		GameMenu :: cm_InventlyWidth				= 0.1275f;						//幅
const float		GameMenu :: cm_InventlyHeight				= 0.09f;						//高さ

//------------------------------------------------------------------------
//	Constructor
//------------------------------------------------------------------------
GameMenu :: GameMenu(void)
{
	Init();
}
GameMenu :: ~GameMenu(void)
{
	Release();
}
//------------------------------------------------------------------------
//	@fn		Init
//	@brief	初期化処理
//------------------------------------------------------------------------
void GameMenu :: Init(void){
	m_Enable = false;							//有効フラグをオフに
	m_Equip = false;							//装備フラグをオフに

	m_DebugNowGetID = 0;

	m_DrawJudge[0] = DataManager::ITEM_CANMIX_EXIST;
	m_DrawJudge[1] = DataManager::ITEM_MATERIAL;

	m_Drawsilhouette[0] = DataManager::ITEM_CANMIX;

	//説明に使用するデータのセット
	m_NameCount = 1;
	m_DescriptionCount = 0;
	m_DescriptionSpan = cm_NameSpan;

	//説明文のフラグをセット
	m_DescriptionFlag = Flag_Name;
	//説明文の
	m_DescriptionColor = GetColor(0,255,40);
	
	//説明用データの初期化
	m_DescriptionData.id.x = 0;
	m_DescriptionData.id.y = 0;
	m_DescriptionData.id.z = 0;
	m_DescriptionData.type = Equipment;
	m_DescriptionData.flag = false;

	m_Step = In;								//インステップ

	for(int i=0;i<4;i++){
		m_Material[i].id.x = 0;
		m_Material[i].id.y = 0;
		m_Material[i].id.z = 0;
		m_Material[i].type = Equipment;
		m_Material[i].flag = false;
	}

	//ハンドルリストを作成
	m_Data = &DataManager::GetInstance();

	// 装備欄の設定
	m_EquipmentUI.SetInSpace(0, 0, 0, 0);
	m_EquipmentUI.SetVisible(true);
	m_EquipmentUI.SetRect(cm_EquipmentUIXPos, cm_EquipmentUIYPos+cm_BackYMargin,cm_EquipmentUIWidth, cm_EquipmentUIHeight);
	//装備品欄表示物の生成
	m_EquipmentFhandleList = new int[cm_EquipmentHNum * cm_ColumnVNum];
	for(int i = 0; i < cm_EquipmentHNum ; i++)
	{
		for(int j = 0; j < cm_ColumnVNum ; j++)
		{
			m_EquipmentFhandleList[i*cm_ColumnVNum + j] = m_Data->GetGraphicGroupData( i + DataManager::GG_ICONBG_Stage1 );
		}
	}

	// ユニット欄の設定
	m_UnitUI.SetInSpace(0, 0, 0, 0);
	m_UnitUI.SetVisible(true);
	m_UnitUI.SetRect(cm_UnitUIXPos, cm_UnitUIYPos+cm_BackYMargin,cm_EquipmentUIWidth, cm_UnitUIHeight);
	//ユニット欄表示物の生成
	m_UnitFhandleList = new int[cm_ColumnVNum * cm_UnitHNum];
	for(int i = 0; i < cm_ColumnVNum; i++)
	{
		for(int j = 0; j < cm_UnitHNum; j++)
		{
			m_UnitFhandleList[i*cm_UnitHNum + j] = m_Data->GetGraphicGroupData( DataManager::GG_ICONBG_Unit );
		}
	}

	//装備品表示物の生成
	m_EquipmenthandleList = new int[cm_ColumnVNum * cm_EquipmentHNum];
	//ユニット表示物の生成
	m_UnithandleList = new int[cm_ColumnVNum * cm_UnitHNum];

	// 装備アイコンの設定
	m_EquipmentIconUI.SetInSpace(0, 0, 0, 0);
	m_EquipmentIconUI.SetVisible(true);
	m_EquipmentIconUI.SetRect(cm_EquipmentUIXPos, cm_EquipmentUIYPos+cm_BackYMargin,cm_EquipmentUIWidth, cm_EquipmentUIHeight);
	
	// ユニットアイコンの設定
	m_UnitIconUI.SetInSpace(0, 0, 0, 0);
	m_UnitIconUI.SetVisible(true);
	m_UnitIconUI.SetRect(cm_UnitUIXPos, cm_UnitUIYPos+cm_BackYMargin,cm_EquipmentUIWidth, cm_UnitUIHeight);
	
	ItemCheck();
	IconChange();

	m_BackGroundPos = cm_BackGroundLeftPos;		//初期x位置割合を格納

	// 独自フォントを使用
	m_FontManager.Load( FontManager::FontSet_AZUKI_W00225 );
	m_FontManager.Load( FontManager::FontSet_AZUKI_W001625 );

	m_EquipManager.SetItemEquip(&m_ItemEquipManager);

	m_Data->SaveData();

}
//------------------------------------------------------------------------
//	@fn		ItemStatusReset
//	@brief	装備・ユニットのステータスの初期化処理:デバッグ用
//------------------------------------------------------------------------
void GameMenu :: ItemStatusReset(void){
	//すべてのユニットを持っている
	for(int i = 0;i<30;i++){
		m_Data->m_SaveData.unitStatus[i] = DataManager::ITEM_NO_EXIST;
	}
	//すべての装備品を持っている
	for(int i = 0;i<60;i++){
		m_Data->m_SaveData.itemStatus[i] = DataManager::ITEM_NO_EXIST;
	}
	for(int i = 1;i<5;i++){
		m_Data->m_SaveData.stageDepth[i] = -1;
	}

	//装備中アイテムのリセット
	m_Data->m_SaveData.equipItem[0] = -1;
	m_Data->m_SaveData.equipItem[1] = -1;
	m_Data->m_SaveData.equipItem[2] = -1;
	m_Data->m_MogllStatus.equip[0] = -1;
	m_Data->m_MogllStatus.equip[1] = -1;
	m_Data->m_MogllStatus.equip[2] = -1;

	//ユニットステータスの初期化
	m_Data->m_SaveData.unitStatus[SORT_UnitIconSortList[0]] = DataManager::ITEM_EQUIP;
	m_Data->m_SaveData.unitStatus[SORT_UnitIconSortList[1]] = DataManager::ITEM_EQUIP;
	m_Data->m_SaveData.unitStatus[SORT_UnitIconSortList[2]] = DataManager::ITEM_EQUIP;

	//装備中ユニットのリセット
	m_Data->m_SaveData.equipUnit[0] = SORT_UnitIconSortList[0];
	m_Data->m_SaveData.equipUnit[1] = SORT_UnitIconSortList[1];
	m_Data->m_SaveData.equipUnit[2] = SORT_UnitIconSortList[2];
	m_Data->m_SaveData.equipUnit[3] = -1;
	m_Data->m_SaveData.equipUnit[4] = -1;
	m_Data->m_SaveData.equipUnit[5] = -1;
	m_Data->m_MogllStatus.equipUnit[0] = -1;
	m_Data->m_MogllStatus.equipUnit[1] = -1;
	m_Data->m_MogllStatus.equipUnit[2] = -1;
	m_Data->m_MogllStatus.equipUnit[3] = -1;
	m_Data->m_MogllStatus.equipUnit[4] = -1;
	m_Data->m_MogllStatus.equipUnit[5] = -1;

	ItemCheck();
	IconChange();

	m_EquipManager.Reset();
	m_DebugNowGetID = 0;

	//セーブ
	m_Data->SaveData();
}
//------------------------------------------------------------------------
//	@fn		GetItem
//	@brief	アイテムを一つずつゲット:デバッグ用
//------------------------------------------------------------------------
void GameMenu :: GetItem(void){
	if(m_DebugNowGetID == 0){
		//すべての装備品を持ってない
		for(int i = 0;i<60;i++){
			m_Data->m_SaveData.itemStatus[i] = DataManager::ITEM_NO_EXIST;
		}
		for(int i = 0;i<30;i++){
			m_Data->m_SaveData.unitStatus[i] = DataManager::ITEM_NO_EXIST;
		}
	}

	m_Data->m_SaveData.unitStatus[SORT_UnitIconSortList[0]] = DataManager::ITEM_EQUIP;
	m_Data->m_SaveData.unitStatus[SORT_UnitIconSortList[1]] = DataManager::ITEM_EQUIP;
	m_Data->m_SaveData.unitStatus[SORT_UnitIconSortList[2]] = DataManager::ITEM_EQUIP;

	//すべての装備品を持っている
	m_Data->m_SaveData.itemStatus[SORT_ItemIconSortList[m_DebugNowGetID]] = DataManager::ITEM_NEW;
	for(int i=0;i<m_DebugNowGetID-1;i++){
		m_Data->m_SaveData.itemStatus[SORT_ItemIconSortList[i]] = DataManager::ITEM_EXIST;
	}
	if(m_DebugNowGetID < 49)
		m_DebugNowGetID++;

	if((m_DebugNowGetID%10) == 1 && m_DebugNowGetID != 1){
		if(m_Data->m_SaveData.stageDepth[(m_DebugNowGetID/10)] < 0)
			m_Data->m_SaveData.stageDepth[(m_DebugNowGetID/10)] = 0;
	}

	//合成ツリー内のアイテムをなしに
	for(int i = 0;i<cm_MixTreeNum;i++){
		switch(m_MixTreeData[i].main.type){
		case 0:
			m_Data->m_SaveData.itemStatus[m_MixTreeData[i].main.id] = DataManager::ITEM_NO_EXIST;
			break;
		case 1:
			m_Data->m_SaveData.unitStatus[m_MixTreeData[i].main.id] = DataManager::ITEM_NO_EXIST;
			break;
		}
	}

	ItemCheck();
	IconChange();

	m_EquipManager.Reset();

	//セーブ
	//m_Data->SaveData();
}
//------------------------------------------------------------------------
//	@fn		GetMap
//	@brief	アイテムを一つずつゲット:デバッグ用
//------------------------------------------------------------------------
void GameMenu :: GetMap(void){
	if(m_DebugNowGetID == 0){
		//すべての装備品を持ってない
		for(int i = 1;i<5;i++){
			m_Data->m_SaveData.stageDepth[i] = -1;
		}
		m_DebugNowGetID++;
	}

	m_Data->m_SaveData.stageDepth[m_DebugNowGetID] = 0;

	if(m_DebugNowGetID < 5)
		m_DebugNowGetID++;
	else
		m_DebugNowGetID = 0;
}
//------------------------------------------------------------------------
//	@fn		IconChange
//	@brief	アイコン変更処理処理
//------------------------------------------------------------------------
void GameMenu :: IconChange(void){
	for(int i = 0; i < cm_ColumnVNum; i++)
	{
		for(int j = 0; j < cm_EquipmentHNum; j++)
		{
			switch(m_Data->m_SaveData.itemStatus[SORT_ItemIconSortList[i*cm_EquipmentHNum + j]]){
			case DataManager::ITEM_NOT_FIND:
			case DataManager::ITEM_NO_EXIST:
				m_EquipmenthandleList[i*cm_EquipmentHNum + j] = m_Data->Get(DataManager::Question_ic);
				break;
			case DataManager::ITEM_EXIST:
			case DataManager::ITEM_NEW:
			case DataManager::ITEM_EQUIP:
			case DataManager::ITEM_CANMIX:
			case DataManager::ITEM_CANMIX_EXIST:
			case DataManager::ITEM_MIX:
			case DataManager::ITEM_MATERIAL:
			case DataManager::ITEM_MIX_EQUIP:
				//EquipIconJudge(i*cm_EquipmentHNum + j);
				m_EquipmenthandleList[i*cm_EquipmentHNum + j] = m_Data->GetGraphicGroupData( SORT_ItemIconSortList[i*cm_EquipmentHNum + j] + DataManager::GG_ITEM0 );
				break;
			default:
				break;
			}
		}
	}

	for(int i = 0; i < cm_ColumnVNum; i++)
	{
		for(int j = 0; j < cm_UnitHNum; j++)
		{
			switch(m_Data->m_SaveData.unitStatus[SORT_UnitIconSortList[i*cm_UnitHNum + j]]){
			case DataManager::ITEM_NOT_FIND:
			case DataManager::ITEM_NO_EXIST:
				m_UnithandleList[i*cm_UnitHNum + j] = m_Data->Get(DataManager::Question_ic);
				break;
			case DataManager::ITEM_EXIST:
			case DataManager::ITEM_NEW:
			case DataManager::ITEM_EQUIP:
			case DataManager::ITEM_CANMIX:
			case DataManager::ITEM_CANMIX_EXIST:
			case DataManager::ITEM_MIX:
			case DataManager::ITEM_MATERIAL:
			case DataManager::ITEM_MIX_EQUIP:
				m_UnithandleList[i*cm_UnitHNum + j] = m_Data->GetGraphicGroupData( SORT_UnitIconSortList[i*cm_UnitHNum + j] + DataManager::GG_UNIT_Treasure );
				break;
			default:
				break;
			}
		}
	}
}
//------------------------------------------------------------------------
//	@fn		ItemCheck
//	@brief	アイテム状態チェック処理
//------------------------------------------------------------------------
void GameMenu :: ItemCheck(void){
	bool flag[4];

	for(int i=0;i<cm_MixTreeNum;i++){
		flag[0] = false;
		flag[1] = false;
		flag[2] = false;
		flag[3] = false;

		//素材がそろっているか確認
		for(int j=0;j<4;j++){
			switch(m_MixTreeData[i].Material[j].type){
			case Equipment:
				if(	m_Data->m_SaveData.itemStatus[m_MixTreeData[i].Material[j].id] == DataManager::ITEM_EXIST ||
					m_Data->m_SaveData.itemStatus[m_MixTreeData[i].Material[j].id] == DataManager::ITEM_CANMIX ||
					m_Data->m_SaveData.itemStatus[m_MixTreeData[i].Material[j].id] == DataManager::ITEM_NEW ||
					m_Data->m_SaveData.itemStatus[m_MixTreeData[i].Material[j].id] == DataManager::ITEM_CANMIX_EXIST ||
					m_Data->m_SaveData.itemStatus[m_MixTreeData[i].Material[j].id] == DataManager::ITEM_MIX ||
					m_Data->m_SaveData.itemStatus[m_MixTreeData[i].Material[j].id] == DataManager::ITEM_EQUIP ||
					m_Data->m_SaveData.itemStatus[m_MixTreeData[i].Material[j].id] == DataManager::ITEM_MATERIAL ||
					m_Data->m_SaveData.itemStatus[m_MixTreeData[i].Material[j].id] == DataManager::ITEM_MIX_EQUIP)
					flag[j] = true;
				break;
			case Unit:
				if(	m_Data->m_SaveData.unitStatus[m_MixTreeData[i].Material[j].id] == DataManager::ITEM_EXIST ||
					m_Data->m_SaveData.unitStatus[m_MixTreeData[i].Material[j].id] == DataManager::ITEM_NEW ||
					m_Data->m_SaveData.unitStatus[m_MixTreeData[i].Material[j].id] == DataManager::ITEM_CANMIX ||
					m_Data->m_SaveData.unitStatus[m_MixTreeData[i].Material[j].id] == DataManager::ITEM_CANMIX_EXIST ||
					m_Data->m_SaveData.unitStatus[m_MixTreeData[i].Material[j].id] == DataManager::ITEM_MIX ||
					m_Data->m_SaveData.unitStatus[m_MixTreeData[i].Material[j].id] == DataManager::ITEM_EQUIP ||
					m_Data->m_SaveData.unitStatus[m_MixTreeData[i].Material[j].id] == DataManager::ITEM_MATERIAL ||
					m_Data->m_SaveData.unitStatus[m_MixTreeData[i].Material[j].id] == DataManager::ITEM_MIX_EQUIP)
					flag[j] = true;
				break;
			default:
				flag[j] = true;
			}
		}

		//素材がそろっていたら
		if(flag[0] && flag[1] && flag[2] && flag[3]){
		//合成できる状態へ変更
			switch(m_MixTreeData[i].main.type){
			case Equipment:
				if(	m_Data->m_SaveData.itemStatus[m_MixTreeData[i].main.id] == DataManager::ITEM_NOT_FIND ||
					m_Data->m_SaveData.itemStatus[m_MixTreeData[i].main.id] == DataManager::ITEM_NO_EXIST &&
					m_Data->m_SaveData.itemStatus[m_MixTreeData[i].main.id] != DataManager::ITEM_MIX &&
					m_Data->m_SaveData.itemStatus[m_MixTreeData[i].main.id] != DataManager::ITEM_MIX_EQUIP &&
					m_Data->m_SaveData.itemStatus[m_MixTreeData[i].main.id] != DataManager::ITEM_CANMIX_EXIST &&
					m_Data->m_SaveData.itemStatus[m_MixTreeData[i].main.id] != DataManager::ITEM_MATERIAL)

					m_Data->m_SaveData.itemStatus[m_MixTreeData[i].main.id] = DataManager::ITEM_CANMIX;
				break;
			case Unit:
				if(	m_Data->m_SaveData.unitStatus[m_MixTreeData[i].main.id] == DataManager::ITEM_NOT_FIND ||
					m_Data->m_SaveData.unitStatus[m_MixTreeData[i].main.id] == DataManager::ITEM_NO_EXIST &&
					m_Data->m_SaveData.unitStatus[m_MixTreeData[i].main.id] != DataManager::ITEM_MIX &&
					m_Data->m_SaveData.unitStatus[m_MixTreeData[i].main.id] != DataManager::ITEM_MIX_EQUIP &&
					m_Data->m_SaveData.unitStatus[m_MixTreeData[i].main.id] != DataManager::ITEM_CANMIX_EXIST &&
					m_Data->m_SaveData.unitStatus[m_MixTreeData[i].main.id] != DataManager::ITEM_MATERIAL)

					m_Data->m_SaveData.unitStatus[m_MixTreeData[i].main.id] = DataManager::ITEM_CANMIX;
				break;
			}
		}
	}

	//m_Data->SaveData();
}

//------------------------------------------------------------------------
//	@fn		Update
//	@brief	更新処理
//------------------------------------------------------------------------
void GameMenu :: Update(void){
	int l_Content = -1;
	static bool l_SEflag = false;
	TreeData l_Root;

	// マウスの座標を保存
	m_Mouse.x = GameInput::GetInstance().GetXf();
	m_Mouse.y = GameInput::GetInstance().GetYf();

	if(	m_Mouse.x > cm_InventlyX && m_Mouse.x < cm_InventlyX + cm_InventlyWidth && 
		m_Mouse.y > cm_InventlyY && m_Mouse.y < cm_InventlyY + cm_InventlyHeight && 
		!m_MixProduction.GetEnable() && !m_FirstMixProduction.GetEnable() && !m_EquipManager.GetConfirmationFlag()){
			if(!l_SEflag){
				PlaySoundMem( m_Data->Get( DataManager::SoundSE07 ), DX_PLAYTYPE_BACK);
				l_SEflag = true;
			}
	}
	else{
		l_SEflag = false;
	}

	if(m_Enable){
		switch(m_Step){
		//スライドインステップ
		case In:
			SrideIn();
			ItemCheck();
			IconChange();
			break;
		case Stay:
			KeyAction();

			if(m_MixProduction.Update()){
				return;
			}

			if(m_FirstMixProduction.Update()){
				return;
			}

			m_ItemEquipManager.Update();
			if(Equip(&l_Content,&l_Root)){
				m_MixProduction.SetContent(l_Content,l_Root.id,l_Root.type);
				m_FirstMixProduction.Enable(l_Root.id,l_Root.type);
				return;
			}

			if(!m_Equip){
				IconOver();
				
			}
			ItemCheck();
			IconChange();
			break;
		case Out:
			SrideOut();
			break;
		default:
			break;
		}

		//m_UIDisplay.Update();
	}
}
//------------------------------------------------------------------------
//	@fn		Release
//	@brief	解放処理
//------------------------------------------------------------------------
void GameMenu :: Release(void){
	delete[] m_EquipmenthandleList;
	delete[] m_UnithandleList;
	delete[] m_EquipmentFhandleList;
	delete[] m_UnitFhandleList;
}
//------------------------------------------------------------------------
//	@fn		KeyAction
//	@brief	キー処理
//------------------------------------------------------------------------
void GameMenu :: KeyAction(void){
	if(GameInput::GetInstance().GetMouse(GameInput::MouseLeftTrg)){
		if(!m_Equip && m_MixProduction.GetEnable() == false){
			m_Equip = true;
			m_EquipManager.CheckEnable();
		}
	}
	if(GameInput::GetInstance().GetMouse(GameInput::MouseRightTrg) && m_EquipManager.GetHaveFlag()){
		m_EquipManager.ResetHaveItem2();
	}
}

//------------------------------------------------------------------------
//	@fn		SrideIn
//	@brief	スライドイン処理
//------------------------------------------------------------------------
void GameMenu :: SrideIn(void){
	if(m_BackGroundPos < cm_BackGroundXPos)
		m_BackGroundPos += cm_BackGroundMovement;
	
	if(m_BackGroundPos > cm_BackGroundXPos){
		m_BackGroundPos = cm_BackGroundXPos;
		m_Step = Stay;
		//m_UIDisplay.SetFlag(UIDisplay::Flag_CO);
	}
}

//------------------------------------------------------------------------
//	@fn		SrideOut
//	@brief	スライドアウト処理
//------------------------------------------------------------------------
void GameMenu :: SrideOut(void){
	if(m_BackGroundPos > cm_BackGroundLeftPos)
		m_BackGroundPos -= cm_BackGroundMovement;
	
	if(m_BackGroundPos <= cm_BackGroundLeftPos){
		m_BackGroundPos = cm_BackGroundLeftPos;
		m_Enable = false;
		m_ItemEquipManager.SetEnable(false);
		m_Step = In;
	}
}

//------------------------------------------------------------------------
//	@fn		Draw
//	@brief	描画処理
//------------------------------------------------------------------------
void GameMenu :: Draw(void){
	int l_DescriptionNameFontSize = 0;

	int l_DescriptPosX = 0;
	int l_DescriptPosY = 0;
	
	int l_DescriptionFrameWidth = 0;
	int l_DescriptionFrameHeight = 0;

	static unsigned int l_num = 1;
	static unsigned int l_span = 5;

	char l_str[256];
	memset(l_str,0,sizeof(l_str));

	//float l_pos = 0.02f;

	//インベントリ開く閉じるボタン
	DXLibMath::DrawExtendGraphResize(cm_InventlyX,cm_InventlyY,cm_InventlyWidth,cm_InventlyHeight, m_Data->Get(DataManager::Invently_ic), TRUE);

	if(m_Enable){
		//インベントリ枠の表示
		DXLibMath::DrawExtendGraphResize(m_BackGroundPos,cm_BackGroundYPos+cm_BackYMargin,cm_BackGroundWidth,cm_BackGroundHeight, m_Data->Get(DataManager::Menu_Background), TRUE);

		switch(m_Step){
		//スライドインステップ
		case In:
			SrideIn();
			m_ItemEquipManager.Draw();
			break;
		//インベントリステイステップ
		case Stay:
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);									//透過率のセット
			//装備欄の描画
			m_EquipmentUI.Draw(cm_ColumnVNum,cm_EquipmentHNum,m_EquipmentFhandleList);
			//ユニット欄の描画
			m_UnitUI.Draw(cm_ColumnVNum,cm_UnitHNum,m_UnitFhandleList);
			
			//仮　装備品・ユニットの描画
			m_EquipmentIconUI.Draw(	cm_ColumnVNum,cm_EquipmentHNum,m_EquipmenthandleList,
									m_Data->m_SaveData.itemStatus,(int*)SORT_ItemIconSortList,
									m_DrawJudge,2,m_Drawsilhouette,1);

			m_UnitIconUI.Draw(	cm_ColumnVNum,cm_UnitHNum,m_UnithandleList,
								m_Data->m_SaveData.unitStatus,(int*)SORT_UnitIconSortList,
								m_DrawJudge,2,m_Drawsilhouette,1);

			//合成に必要な素材を光らせる
			DrawMaterialShine();
			//インベントリの背景のステージに掛けるはてなのマスク
			DrawStageMask();

			//レーダーオンオフ
			DrawBox(static_cast<int>((UIDisplay::Def_PosX-UIDisplay::Size_DefX)),static_cast<int>((UIDisplay::Def_PosY-UIDisplay::Size_DefY)),
					static_cast<int>((UIDisplay::Def_PosX+UIDisplay::Size_DefX)),static_cast<int>((UIDisplay::Def_PosY+UIDisplay::Size_DefY)),
					GetColor(0,0,0), TRUE);

			//説明文の描画
			if(m_DescriptionData.flag && !m_Equip && m_MixProduction.GetEnable() == false){
				DXLibMath::ConvertPixcelX(m_Mouse.x+cm_DescriptionFrameXMargin,&l_DescriptPosX);
				DXLibMath::ConvertPixcelY(m_Mouse.y+cm_DescriptionFrameYMargin,&l_DescriptPosY);
				DXLibMath::ConvertPixcelX(cm_DescriptionFrameWidth,&l_DescriptionFrameWidth);
				DXLibMath::ConvertPixcelY(cm_DescriptionFrameHeight,&l_DescriptionFrameHeight);

				//前回と違うところをオーバーしている時、情報のリセット
				if(m_MemDescriptionData.id.z != m_DescriptionData.id.z || m_MemDescriptionData.type != m_DescriptionData.type){
					m_NameCount = 1;
					m_DescriptionCount = 0;
					m_DescriptionFlag = Flag_Name;
					m_DescriptionSpan = cm_NameSpan;
				}

				switch(m_DescriptionData.type){
				case Equipment:
					//説明文の描画
					if(m_Data->m_SaveData.itemStatus[SORT_ItemIconSortList[m_DescriptionData.id.z]] != DataManager::ITEM_CANMIX){

						//名前の描画
						m_FontManager.DrawFontStringNumSet(
							FontManager::FontSet_AZUKI_W00225,
							cm_DescriptionFrameXPos + cm_DescriptionFrameXMargin + cm_DescriptionNameMarginX,
							cm_DescriptionFrameYPos + cm_DescriptionFrameYMargin + cm_DescriptionNameMarginY,
							m_Data->m_SystemData.equip[SORT_ItemIconSortList[m_DescriptionData.id.z]].name,
							0.145f, m_NameCount,m_DescriptionColor);
						//情報の描画
						m_FontManager.DrawFontStringNumSet(
							FontManager::FontSet_AZUKI_W001625,
							cm_DescriptionFrameXPos + cm_DescriptionFrameXMargin + cm_DescriptionMarginX,
							cm_DescriptionFrameYPos + cm_DescriptionFrameYMargin + cm_DescriptionMarginY + cm_DescriptionNameMarginY,
							m_Data->m_SystemData.equip[SORT_ItemIconSortList[m_DescriptionData.id.z]].text,
							0.14f, m_DescriptionCount, m_DescriptionColor);

						//文字数のカウント
						switch(m_DescriptionFlag){
						case Flag_Name:						//名前
							if(m_DescriptionSpan > 0){
								m_DescriptionSpan--;
							}
							else{
								m_NameCount++;
								m_DescriptionSpan = 0;
								if(m_NameCount > strlen(m_Data->m_SystemData.equip[SORT_ItemIconSortList[m_DescriptionData.id.z]].name))
									m_DescriptionFlag = Flag_Description;
							}
							break;
						case Flag_Description:				//情報
							if(m_DescriptionSpan > 0){
								m_DescriptionSpan--;
							}
							else{
								m_DescriptionCount++;
								if(m_DescriptionCount > strlen(m_Data->m_SystemData.equip[SORT_ItemIconSortList[m_DescriptionData.id.z]].text))
									m_DescriptionFlag = Flag_Wait;
							}
							break;
						}
					}
					else{
						//合成できる:メッセージ描画
						DrawCanMixString();
					}
					break;
				case Unit:
					if(m_Data->m_SaveData.unitStatus[SORT_UnitIconSortList[m_DescriptionData.id.z]] != DataManager::ITEM_CANMIX){

						//名前の描画
						m_FontManager.DrawFontStringNumSet(
							FontManager::FontSet_AZUKI_W00225,
							cm_DescriptionFrameXPos + cm_DescriptionFrameXMargin + cm_DescriptionNameMarginX,
							cm_DescriptionFrameYPos + cm_DescriptionFrameYMargin + cm_DescriptionNameMarginY,
							m_Data->m_SystemData.unit[SORT_UnitIconSortList[m_DescriptionData.id.z]].name,
							0.145f, m_NameCount,m_DescriptionColor);
						//情報の描画
						m_FontManager.DrawFontStringNumSet(
							FontManager::FontSet_AZUKI_W001625,
							cm_DescriptionFrameXPos + cm_DescriptionFrameXMargin + cm_DescriptionMarginX,
							cm_DescriptionFrameYPos + cm_DescriptionFrameYMargin + cm_DescriptionMarginY + cm_DescriptionNameMarginY,
							m_Data->m_SystemData.unit[SORT_UnitIconSortList[m_DescriptionData.id.z]].text,
							0.14f, m_DescriptionCount, m_DescriptionColor);

						//文字数のカウント
						switch(m_DescriptionFlag){
						case Flag_Name:						//名前
							if(m_DescriptionSpan > 0){
								m_DescriptionSpan--;
							}
							else{
								m_NameCount++;
								m_DescriptionSpan = 0;
								if(m_NameCount > strlen(m_Data->m_SystemData.unit[SORT_UnitIconSortList[m_DescriptionData.id.z]].name))
									m_DescriptionFlag = Flag_Description;
							}
							break;
						case Flag_Description:				//情報
							if(m_DescriptionSpan > 0){
								m_DescriptionSpan--;
							}
							else{
								m_DescriptionCount++;
								if(m_DescriptionCount > strlen(m_Data->m_SystemData.unit[SORT_UnitIconSortList[m_DescriptionData.id.z]].text))
									m_DescriptionFlag = Flag_Wait;
							}
							break;
						}
					}
					else{
						//合成できる:メッセージ描画
						DrawCanMixString();
					}
					break;
				}
				
				m_MemDescriptionData = m_DescriptionData;
			}
			else{
				//リセット
				m_NameCount = 1;
				m_DescriptionCount = 0;
				m_DescriptionFlag = Flag_Name;
				m_DescriptionSpan = cm_NameSpan;
			}

			if(!m_MixProduction.GetEnable() && !m_FirstMixProduction.GetEnable() && !m_EquipManager.GetConfirmationFlag())
				m_EquipManager.DrawSlot();

			m_EquipManager.SymbolDraw();
			//アイテム装備に関する描画
			m_ItemEquipManager.Draw();
			//装備に関する描画:持っているアイテム(カーソル),スロットをオーバーしたとき
			m_EquipManager.OtherDraw();
			//装備の描画
			m_EquipManager.Draw();

			//装備の描画
			//m_EquipManager.Draw();

			//演出
			m_MixProduction.Draw();

			m_FirstMixProduction.Draw();


			//DrawPosCheck(	(int)(m_ItemEquipManager.GetPosition().x),(int)(m_ItemEquipManager.GetPosition().y),
			//				(int)(m_ItemEquipManager.GetSlotSize()+m_ItemEquipManager.GetWidth()),
			//				(int)(m_ItemEquipManager.GetSlotSize()));
			break;
		//スライドアウトステップ
		case Out:
			SrideOut();
			m_ItemEquipManager.Draw();
			break;
		default:
			break;
		}
	}
}
int GameMenu :: StrLength(const char *s)
{
	int n = 0;			/* カウンタを０に初期化 */

	while (*s++)		/* sが'\0'でなければ */
		n++;			/* カウンタを１増やす */
	return (n);			/* 文字列の長さを返す */
}

void GameMenu :: DrawCanMixString(void){
	char l_CanMixString[256];
	memset(l_CanMixString,0,sizeof(l_CanMixString));

	//メッセージのセット
	sprintf_s(l_CanMixString,256,"合成できます");

	//メッセージの描画
	m_FontManager.DrawFontStringNumSet(
		FontManager::FontSet_AZUKI_W00225,
		cm_DescriptionFrameXPos + cm_DescriptionFrameXMargin + cm_DescriptionNameMarginX,
		cm_DescriptionFrameYPos + cm_DescriptionFrameYMargin + cm_DescriptionNameMarginY,
		l_CanMixString,
		0.145f, m_NameCount,m_DescriptionColor);

	if(m_DescriptionSpan > 0){
		m_DescriptionSpan--;
	}
	else{
		m_NameCount++;
		m_DescriptionSpan = 0;
		if(m_NameCount > strlen(l_CanMixString))
			m_NameCount = strlen(l_CanMixString);
	}
}

void GameMenu :: DrawPosCheck(float x,float y,float w,float h){
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);									//透過率のセット
	DXLibMath::DrawBoxResize(	x,y,w,h,GetColor(255,255,255), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);									//透過率のセット
}

void GameMenu :: DrawPosCheck(int x,int y,int w,int h){
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);									//透過率のセット
	DrawBox(x,y,w+x,h+y,GetColor(255,255,255), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);									//透過率のセット
}

//------------------------------------------------------------------------
//	@fn		DrawMaterialShine
//	@brief	
//------------------------------------------------------------------------
void GameMenu :: DrawMaterialShine(void){
	DXLibMath::Vector2 l_work;

	for(int i=0;i<4;i++){
		if(m_Material[i].flag){
			switch(m_Material[i].type){
			case Equipment:
				l_work.x = ReverseGetID(m_Material[i].id.z,m_Material[i].type) % 10 * cm_OneFrameWidth;
				l_work.x = cm_EquipmentUIXPos + l_work.x;

				l_work.y = ReverseGetID(m_Material[i].id.z,m_Material[i].type) / 10 * cm_OneFrameHeight;
				l_work.y = cm_EquipmentUIYPos + cm_BackYMargin + l_work.y;
				break;
			case Unit:
				l_work.x = ReverseGetID(m_Material[i].id.z,m_Material[i].type) % 10 * cm_OneFrameWidth;
				l_work.x = cm_UnitUIXPos + l_work.x;

				l_work.y = ReverseGetID(m_Material[i].id.z,m_Material[i].type) / 10 * cm_OneFrameHeight;
				l_work.y = cm_UnitUIYPos + cm_BackYMargin + l_work.y;
				break;
			}

			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);				//透過率のセット
			DXLibMath::DrawBoxResize(static_cast<float>(l_work.x),static_cast<float>(l_work.y), GameMenu::cm_OneFrameWidth, GameMenu::cm_OneFrameHeight, GetColor(255,255,255), TRUE);
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);				//透過率のセット
		}
	}
}
//------------------------------------------------------------------------
//	@fn		DrawStageMask
//	@brief	
//------------------------------------------------------------------------
void GameMenu :: DrawStageMask(void){
	for(int i=1;i<5;i++){
		if(m_Data->m_SaveData.stageDepth[i] == -1){
			DrawExtendGraph(73,106+(44*(i-1)),65+73,39+106+(44*(i-1)),m_Data->Get(DataManager::Menu_StageMask),TRUE);
		}
	}
}

int GameMenu :: ReverseGetID(int id,char type){
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
//	@fn		OpeningClosing
//	@brief	クリックでの開閉処理
//------------------------------------------------------------------------
bool GameMenu :: OpeningClosing(void)
{
	if( !m_EquipManager.GetConfirmationFlag() &&
		!m_MixProduction.GetEnable() && 
		!m_EquipManager.GetHaveFlag())
	{
		//SE
		PlaySoundMem( m_Data->Get( DataManager::SoundSE02 ), DX_PLAYTYPE_BACK);
		//有効・無効切り替え
		ChangeEnable();
		return true;
	}
	return false;
}

bool GameMenu :: OpeningClosing(DXLibMath::Vector2 &mouse){
	if(	mouse.x > cm_InventlyX && mouse.x < cm_InventlyX + cm_InventlyWidth && 
		mouse.y > cm_InventlyY && mouse.y < cm_InventlyY + cm_InventlyHeight &&
		!m_EquipManager.GetConfirmationFlag() &&
		!m_MixProduction.GetEnable() && 
		!m_EquipManager.GetHaveFlag()){
			//SE
			PlaySoundMem( m_Data->Get( DataManager::SoundSE02 ), DX_PLAYTYPE_BACK);
			//有効・無効切り替え
			ChangeEnable();
			return true;
	}
	return false;
}

//------------------------------------------------------------------------
//	@fn		ChangeEnable
//	@brief	有効・無効切り替え
//------------------------------------------------------------------------
void GameMenu :: ChangeEnable(void){
	if(m_Step == Out){
		m_Step = In;
		m_ItemEquipManager.Reset();
	}
	else{
		if(m_Enable){
			m_Step = Out;
			m_EquipManager.ResetHaveItem();
			m_ItemEquipManager.Reset();
		}
		else{
			m_Enable = true;
			m_ItemEquipManager.SetEnable(true);
		}
	}
}
//------------------------------------------------------------------------
//	@fn		IconOver
//	@brief	アイコンマウスオーバー時の判定処理
//------------------------------------------------------------------------
void GameMenu :: IconOver(void){
	int l_num = 0;

	static TreeData l_memData;

	for(int i=0;i<4;i++){
		m_Material[i].id.x = -1;
		m_Material[i].id.y = -1;
		m_Material[i].id.z = -1;
		m_Material[i].type = -1;
		m_Material[i].flag = false;
	}

	//Slot------------------------------------------------------------------------------------------------------------------------------

	//装備
	for(int i = 0; i < 3; i++)
	{
		if(	m_Mouse.x > m_ItemEquipManager.GetPosition().x/800.0f && 
			m_Mouse.x < (m_ItemEquipManager.GetPosition().x + m_ItemEquipManager.GetSlotSize() + m_ItemEquipManager.GetWidth())/800.0f && 
			m_Mouse.y > (m_ItemEquipManager.GetPosition().y + (m_ItemEquipManager.GetSlotSize()*i))/600.0f && 
			m_Mouse.y < (m_ItemEquipManager.GetPosition().y + (m_ItemEquipManager.GetSlotSize()*i) + m_ItemEquipManager.GetSlotSize())/600.0f){

			m_DescriptionData.type = 0;
			for(int j=0;j<60;j++){
				if(SORT_ItemIconSortList[j] == m_Data->m_MogllStatus.equip[i]){
					m_DescriptionData.id.z = j;
					break;
				}
			}

			if(	m_Data->m_MogllStatus.equip[i] > -1 && m_Data->m_MogllStatus.equip[i] < 60 &&
				(m_Data->m_SaveData.itemStatus[SORT_ItemIconSortList[m_DescriptionData.id.z]] == DataManager::ITEM_EQUIP || 
				m_Data->m_SaveData.itemStatus[SORT_ItemIconSortList[m_DescriptionData.id.z]] == DataManager::ITEM_EXIST || 
				m_Data->m_SaveData.itemStatus[SORT_ItemIconSortList[m_DescriptionData.id.z]] == DataManager::ITEM_NEW || 
				m_Data->m_SaveData.itemStatus[SORT_ItemIconSortList[m_DescriptionData.id.z]] == DataManager::ITEM_MIX || 
				m_Data->m_SaveData.itemStatus[SORT_ItemIconSortList[m_DescriptionData.id.z]] == DataManager::ITEM_CANMIX ||
				m_Data->m_SaveData.itemStatus[SORT_ItemIconSortList[m_DescriptionData.id.z]] == DataManager::ITEM_CANMIX_EXIST ||
				m_Data->m_SaveData.itemStatus[SORT_ItemIconSortList[m_DescriptionData.id.z]] == DataManager::ITEM_MATERIAL ||
				m_Data->m_SaveData.itemStatus[SORT_ItemIconSortList[m_DescriptionData.id.z]] == DataManager::ITEM_MIX_EQUIP)){
				
				m_DescriptionData.flag = true;

				if(((l_memData.id != m_DescriptionData.id.z && l_memData.type == Equipment) || l_memData.id == -1) &&
					!m_ItemEquipManager.GetMoveFlag() && !m_ItemEquipManager.GetStayFlag() && !m_ItemEquipManager.GetReverseFlag()){
					PlaySoundMem( m_Data->Get( DataManager::SoundSE07 ), DX_PLAYTYPE_BACK);
				}

				l_memData.id = m_DescriptionData.id.z;
				l_memData.type = Equipment;

				return;
			}
			else if(	m_EquipManager.GetHaveFlag() && m_EquipManager.GetHaveItem()->id != -1 && 
						m_EquipManager.GetHaveItem()->type == 0 && m_Data->m_MogllStatus.equip[i] == -1 ){

				m_DescriptionData.flag = true;
				m_DescriptionData.id.z = m_EquipManager.GetHaveItem()->id;
			}
			else{
				m_DescriptionData.flag = false;
				l_memData.id = -1;
				l_memData.type = -1;

				return;
			}
		}
	}

	//ユニット
	for(int i = 0; i < 6; i++)
	{
		if(	m_Mouse.x > (float)((32 + 92*i)/800.0f) && m_Mouse.x < (float)(((32 + 92*i)+74)/800.0f) && 
			m_Mouse.y > (float)(522/600.0f) && m_Mouse.y < (float)((522+74)/600.0f)){

			m_DescriptionData.type = 1;
			for(int j=0;j<30;j++){
				if(SORT_UnitIconSortList[j] == m_Data->m_MogllStatus.equipUnit[i]){
					m_DescriptionData.id.z = j;
					break;
				}
			}
						
			if(	m_Data->m_MogllStatus.equipUnit[i] < 30 && m_Data->m_MogllStatus.equipUnit[i] > -1 &&
				(m_Data->m_SaveData.unitStatus[SORT_UnitIconSortList[m_DescriptionData.id.z]] == DataManager::ITEM_EQUIP || 
				m_Data->m_SaveData.unitStatus[SORT_UnitIconSortList[m_DescriptionData.id.z]] == DataManager::ITEM_EXIST ||
				m_Data->m_SaveData.unitStatus[SORT_UnitIconSortList[m_DescriptionData.id.z]] == DataManager::ITEM_NEW || 
				m_Data->m_SaveData.unitStatus[SORT_UnitIconSortList[m_DescriptionData.id.z]] == DataManager::ITEM_MIX || 
				m_Data->m_SaveData.unitStatus[SORT_UnitIconSortList[m_DescriptionData.id.z]] == DataManager::ITEM_CANMIX ||
				m_Data->m_SaveData.unitStatus[SORT_UnitIconSortList[m_DescriptionData.id.z]] == DataManager::ITEM_CANMIX_EXIST ||
				m_Data->m_SaveData.unitStatus[SORT_UnitIconSortList[m_DescriptionData.id.z]] == DataManager::ITEM_MATERIAL ||
				m_Data->m_SaveData.unitStatus[SORT_UnitIconSortList[m_DescriptionData.id.z]] == DataManager::ITEM_MIX_EQUIP)){

				m_DescriptionData.flag = true;
				if(((l_memData.id != m_DescriptionData.id.z && l_memData.type == Unit) || l_memData.id == -1)){
					if(m_EquipManager.GetHaveFlag() == false)
						PlaySoundMem( m_Data->Get( DataManager::SoundSE07 ), DX_PLAYTYPE_BACK);
				}
				l_memData.id = m_DescriptionData.id.z;
				l_memData.type = Unit;

				return;
			}
			else if(	m_EquipManager.GetHaveFlag() && m_EquipManager.GetHaveItem()->id != -1 && 
						m_EquipManager.GetHaveItem()->type == 1 && m_Data->m_MogllStatus.equipUnit[i] == 30 ){

				m_DescriptionData.flag = true;
				m_DescriptionData.id.z = m_EquipManager.GetHaveItem()->id;
			}
			else{
				m_DescriptionData.flag = false;
				l_memData.id = -1;
				l_memData.type = -1;

				return;
			}
		}
	}

	//Icon------------------------------------------------------------------------------------------------------------------------------

	//装備
	for(int i = 0; i < cm_EquipmentHNum; i++)
	{
		for(int j = 0; j < cm_ColumnVNum; j++)
		{
			if(	m_Mouse.x > cm_EquipmentUIXPos+(j*cm_OneFrameWidth) && m_Mouse.x < cm_EquipmentUIXPos+(j*cm_OneFrameWidth)+cm_OneFrameWidth && 
				m_Mouse.y > cm_EquipmentUIYPos+(i*cm_OneFrameHeight)+cm_BackYMargin && m_Mouse.y < cm_EquipmentUIYPos+(i*cm_OneFrameHeight)+cm_BackYMargin+cm_OneFrameHeight){
				
				m_DescriptionData.type = Equipment;
				m_DescriptionData.id.x = j;
				m_DescriptionData.id.y = i;
				m_DescriptionData.id.z = j + (i * cm_ColumnVNum);

				l_num = GetMixTreeNum(SORT_ItemIconSortList[m_DescriptionData.id.z],Equipment);

				if(	m_Data->m_SaveData.itemStatus[SORT_ItemIconSortList[m_DescriptionData.id.z]] == DataManager::ITEM_EQUIP || 
					m_Data->m_SaveData.itemStatus[SORT_ItemIconSortList[m_DescriptionData.id.z]] == DataManager::ITEM_EXIST || 
					m_Data->m_SaveData.itemStatus[SORT_ItemIconSortList[m_DescriptionData.id.z]] == DataManager::ITEM_NEW || 
					m_Data->m_SaveData.itemStatus[SORT_ItemIconSortList[m_DescriptionData.id.z]] == DataManager::ITEM_MIX || 
					m_Data->m_SaveData.itemStatus[SORT_ItemIconSortList[m_DescriptionData.id.z]] == DataManager::ITEM_CANMIX ||
					m_Data->m_SaveData.itemStatus[SORT_ItemIconSortList[m_DescriptionData.id.z]] == DataManager::ITEM_CANMIX_EXIST ||
					m_Data->m_SaveData.itemStatus[SORT_ItemIconSortList[m_DescriptionData.id.z]] == DataManager::ITEM_MATERIAL ||
					m_Data->m_SaveData.itemStatus[SORT_ItemIconSortList[m_DescriptionData.id.z]] == DataManager::ITEM_MIX_EQUIP){

					m_DescriptionData.flag = true;

					if(((l_memData.id != m_DescriptionData.id.z && l_memData.type == Equipment) || l_memData.id == -1) &&
						!m_ItemEquipManager.GetMoveFlag() && !m_ItemEquipManager.GetStayFlag() && !m_ItemEquipManager.GetReverseFlag()){
						PlaySoundMem( m_Data->Get( DataManager::SoundSE07 ), DX_PLAYTYPE_BACK);
					}

					GetMaterialShine(l_num);
					l_memData.id = m_DescriptionData.id.z;
					l_memData.type = Equipment;

					return;
				}
				else if(	m_EquipManager.GetHaveFlag() && m_EquipManager.GetHaveItem()->id != -1 && m_EquipManager.GetHaveItem()->type == 0 && 
							(m_Data->m_SaveData.itemStatus[SORT_ItemIconSortList[m_DescriptionData.id.z]] == DataManager::ITEM_NOT_FIND || 
							m_Data->m_SaveData.itemStatus[SORT_ItemIconSortList[m_DescriptionData.id.z]] == DataManager::ITEM_NO_EXIST) ){

					m_DescriptionData.flag = true;
					m_DescriptionData.id.z = GetSortNum(m_EquipManager.GetHaveItem()->id,m_EquipManager.GetHaveItem()->type);
				}
				else{
					m_DescriptionData.flag = false;
					l_memData.id = -1;
					l_memData.type = -1;

					return;
				}
			}
		}
	}

	//ユニット
	for(int i = 0; i < cm_UnitHNum; i++)
	{
		for(int j = 0; j < cm_ColumnVNum; j++)
		{
			if(	m_Mouse.x > cm_UnitUIXPos+(j*cm_OneFrameWidth) && m_Mouse.x < cm_UnitUIXPos+(j*cm_OneFrameWidth)+cm_OneFrameWidth && 
				m_Mouse.y > cm_UnitUIYPos+(i*cm_OneFrameHeight)+cm_BackYMargin && m_Mouse.y < cm_UnitUIYPos+(i*cm_OneFrameHeight)+cm_BackYMargin+cm_OneFrameHeight){
				
				m_DescriptionData.type = Unit;
				m_DescriptionData.id.x = j;
				m_DescriptionData.id.y = i;
				m_DescriptionData.id.z = j + (i * cm_ColumnVNum);

				l_num = GetMixTreeNum(SORT_UnitIconSortList[m_DescriptionData.id.z],Unit);

				if(	m_Data->m_SaveData.unitStatus[SORT_UnitIconSortList[m_DescriptionData.id.z]] == DataManager::ITEM_EQUIP || 
					m_Data->m_SaveData.unitStatus[SORT_UnitIconSortList[m_DescriptionData.id.z]] == DataManager::ITEM_EXIST ||
					m_Data->m_SaveData.unitStatus[SORT_UnitIconSortList[m_DescriptionData.id.z]] == DataManager::ITEM_NEW || 
					m_Data->m_SaveData.unitStatus[SORT_UnitIconSortList[m_DescriptionData.id.z]] == DataManager::ITEM_MIX || 
					m_Data->m_SaveData.unitStatus[SORT_UnitIconSortList[m_DescriptionData.id.z]] == DataManager::ITEM_CANMIX ||
					m_Data->m_SaveData.unitStatus[SORT_UnitIconSortList[m_DescriptionData.id.z]] == DataManager::ITEM_CANMIX_EXIST ||
					m_Data->m_SaveData.unitStatus[SORT_UnitIconSortList[m_DescriptionData.id.z]] == DataManager::ITEM_MATERIAL ||
					m_Data->m_SaveData.unitStatus[SORT_UnitIconSortList[m_DescriptionData.id.z]] == DataManager::ITEM_MIX_EQUIP){
					
					m_DescriptionData.flag = true;
					if(((l_memData.id != m_DescriptionData.id.z && l_memData.type == Unit) || l_memData.id == -1)){
						if(m_EquipManager.GetHaveFlag() == false)
							PlaySoundMem( m_Data->Get( DataManager::SoundSE07 ), DX_PLAYTYPE_BACK);
					}
					GetMaterialShine(l_num);
					l_memData.id = m_DescriptionData.id.z;
					l_memData.type = Unit;
					return;
				}
				else if(	m_EquipManager.GetHaveFlag() && m_EquipManager.GetHaveItem()->id != -1 && m_EquipManager.GetHaveItem()->type == 1 && 
							(m_Data->m_SaveData.unitStatus[SORT_UnitIconSortList[m_DescriptionData.id.z]] == DataManager::ITEM_NOT_FIND || 
							m_Data->m_SaveData.unitStatus[SORT_UnitIconSortList[m_DescriptionData.id.z]] == DataManager::ITEM_NO_EXIST) ){

					m_DescriptionData.flag = true;
					m_DescriptionData.id.z = GetSortNum(m_EquipManager.GetHaveItem()->id,m_EquipManager.GetHaveItem()->type);
				}
				else{
					m_DescriptionData.flag = false;
					l_memData.id = -1;
					l_memData.type = -1;
					return;
				}
				return;
			}
		}
	}

	//HaveItem & NotOver----------------------------------------------------------------------------------------------------------------
	if(m_EquipManager.GetHaveFlag() && m_EquipManager.GetHaveItem()->id != -1){
		switch(m_EquipManager.GetHaveItem()->type){
		case 0:
			m_DescriptionData.id.z = GetSortNum(m_EquipManager.GetHaveItem()->id,m_EquipManager.GetHaveItem()->type);
			m_DescriptionData.type = m_EquipManager.GetHaveItem()->type;
			m_DescriptionData.flag = true;
			l_memData.id = m_DescriptionData.id.z;
			l_memData.type = m_DescriptionData.type;
			return;
			break;
		case 1:
			m_DescriptionData.id.z = GetSortNum(m_EquipManager.GetHaveItem()->id,m_EquipManager.GetHaveItem()->type);
			m_DescriptionData.type = m_EquipManager.GetHaveItem()->type;
			m_DescriptionData.flag = true;
			l_memData.id = m_DescriptionData.id.z;
			l_memData.type = m_DescriptionData.type;
			return;
			break;
		}
	}

	m_DescriptionData.flag = false;
	l_memData.id = -1;
	l_memData.type = -1;
}

int GameMenu :: GetMixTreeNum(int id,int type){
	for(int i=0;i<cm_MixTreeNum;i++){
		if(m_MixTreeData[i].main.id == id && m_MixTreeData[i].main.type == type){
			return i;
		}
	}
	return -1;
}
int GameMenu :: GetSortNum(int id,int type){
	switch(type){
	case 0:
		for(int i=0;i<60;i++){
			if(SORT_ItemIconSortList[i] == id){
				return i;
			}
		}
		break;
	case 1:
		for(int i=0;i<30;i++){
			if(SORT_UnitIconSortList[i] == id){
				return i;
			}
		}
		break;
	}
	return -1;
}
void GameMenu :: GetMaterialShine(int num){
	for(int i=0;i<4;i++){
		m_Material[i].id.x = -1;
		m_Material[i].id.y = -1;
		m_Material[i].id.z = -1;
		m_Material[i].type = -1;
		m_Material[i].flag = false;
	}

	if(num != -1){
		for(int i=0;i<4;i++){
			m_Material[i].type = m_MixTreeData[num].Material[i].type;
			m_Material[i].id.z = m_MixTreeData[num].Material[i].id;
			if(m_Material[i].id.z != -1){
				m_Material[i].id.x = m_Material[i].id.z%10;
				m_Material[i].id.y = m_Material[i].id.z/10;
				m_Material[i].flag = true;
			}
		}
	}
}
//------------------------------------------------------------------------
//	@fn		Equip
//	@brief	装備処理
//------------------------------------------------------------------------
bool GameMenu :: Equip(int *Content,TreeData *Root){
	//装備処理
	if(m_Equip){
		if(m_EquipManager.Update(Content,Root)){
			m_Equip = false;
			return true;
		}
	}

	return false;
}

//------------------------------------------------------------------------
//	@fn		GetEnable
//	@brief	有効フラグのゲット
//------------------------------------------------------------------------
bool GameMenu :: GetEnable(void){
	return m_Enable;
}

//------------------------------------------------------------------------
//	@fn		GetUnitEquipment
//	@brief	ユニットの装備スロットの情報をゲット
//------------------------------------------------------------------------
//void GameMenu :: GetUnitEquipment(int *unitID)
//{
//	m_EquipManager.GetUnitEquipment(unitID);
//}

//========================================================================
//	End of file
//========================================================================
