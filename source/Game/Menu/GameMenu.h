//========================================================================
//	@file		GameMenu.h
//	@note		インベントリ
//	@author		RyotaUehara
//	@version	1.0
//========================================================================
#pragma once
//------------------------------------------------------------------------
//	IncludeHeader
//------------------------------------------------------------------------
#include "../System/CustomUserInterface.h"
#include "../System/FontManager.h"
#include "../System/DataManager.h"
#include "Equip.h"
#include "ItemEquip.h"
#include "MixProduction.h"
#include "FirstMixProduction.h"
#include "UIDisplay.h"

typedef struct DiscriptData{
	IdData			id;			//どのアイコンかの番号
	int				type;		//装備かユニットか
	bool			flag;		//表示フラグ
}DiscriptData;

//------------------------------------------------------------------------
//	command name headerName
//	@Class GameMenu GameMenu.h
//	@brief インベントリ
//------------------------------------------------------------------------
class GameMenu
{
	//--------------------------------------------------------------------
	//	Member
	//--------------------------------------------------------------------
	private:
		bool					m_Enable;					//有効フラグ
		bool					m_Equip;					//装備フラグ
		int						m_DescriptionFlag;			//説明文用のフラグ
		int						m_DescriptionSpan;			//説明文表示時のスパン
		int						m_DescriptionColor;			//説明文の色
		int						m_DrawJudge[2];				//描画時のアイテムをうす暗くする判定値リスト
		int						m_Drawsilhouette[1];		//描画時のアイテムを暗くする判定値リスト
		unsigned int			m_NameCount;
		unsigned int			m_DescriptionCount;
		unsigned int			m_Step;						//ステップ状態
		float					m_BackGroundPos;			//インベントリ背景のx位置

		DXLibMath::Vector2		m_Mouse;					//マウス位置
		DiscriptData			m_DescriptionData;			//説明用データ
		DiscriptData			m_MemDescriptionData;		//説明用データ
		DiscriptData			m_Material[4];				//

		CustomUserInterface		m_EquipmentUI;				//装備欄
		CustomUserInterface		m_UnitUI;					//ユニット欄
		CustomUserInterface		m_EquipmentIconUI;			//装備アイコン
		CustomUserInterface		m_UnitIconUI;				//ユニットアイコン

		FontManager				m_FontManager;				//独自フォント、自動改行用
		Equip					m_EquipManager;				//装備処理クラス
		ItemEquip				m_ItemEquipManager;
		MixProduction			m_MixProduction;
		FirstMixProduction		m_FirstMixProduction;

		int						m_DebugNowGetID;
		int						*m_EquipmenthandleList;		//装備ハンドルリスト
		int						*m_UnithandleList;			//ユニットハンドルリスト
		int						*m_EquipmentFhandleList;	//装備品欄ハンドルリスト
		int						*m_UnitFhandleList;			//ユニット欄ハンドルリスト

		DataManager				*m_Data;

		static const float		cm_BackGroundLeftPos;		//インベントリ背景の格納時位置割合
		static const float		cm_BackGroundXPos;			//インベントリ背景の表示x位置割合
		static const float		cm_BackGroundYPos;			//インベントリ背景の表示y位置割合
		static const float		cm_BackGroundMovement;		//インベントリ背景の移動割合
		static const float		cm_BackGroundWidth;			//インベントリ背景の表示幅割合
		static const float		cm_BackGroundHeight;		//インベントリ背景の表示高さ割合

		static const float		cm_InventlyX;				//インベントリ開閉用画像x
		static const float		cm_InventlyY;				//インベントリ開閉用画像y
		static const float		cm_InventlyWidth;			//インベントリ開閉用画像幅
		static const float		cm_InventlyHeight;			//インベントリ開閉用画像高さ
		
		static const float		cm_DescriptionFrameXPos;	//説明枠x
		static const float		cm_DescriptionFrameYPos;	//説明枠y
		static const float		cm_DescriptionFrameXMargin;	//説明枠x補正
		static const float		cm_DescriptionFrameYMargin;	//説明枠y補正
		static const float		cm_DescriptionFrameWidth;	//説明枠幅
		static const float		cm_DescriptionFrameHeight;	//説明枠高さ

		static const float		cm_DescriptionNameMarginX;	//説明名前x補正値
		static const float		cm_DescriptionNameMarginY;	//説明名前y補正値
		static const float		cm_DescriptionMarginX;		//説明文x補正値
		static const float		cm_DescriptionMarginY;		//説明文y補正値

		static const float		cm_DescriptionNameSize;		//説明:名前の文字サイズ割合
		static const float		cm_DescriptionSize;			//説明:説明分の文字サイズ割合
		
		static const int		cm_NameSpan;			//
		static const int		cm_DescriptionSpan;			//

		//ステップ
		enum Step
		{
			In,												//インステップ
			Stay,											//ステイステップ
			Out,											//アウトステップ
		};

		enum Flag{
			Flag_Mix,										//合成する
			Flag_Break,										//分解しなければいけない
			Flag_Name,										//説明:名前
			Flag_Description,								//説明
			Flag_MixOK,										//
			Flag_Wait

		};
	public:
		static const float		cm_BackYMargin;				//背景のサイズが足りてないので少し下げるため
		
		static const float		cm_EquipmentUIXPos;			//欄の表示x位置割合
		static const float		cm_EquipmentUIWidth;			//欄の表示幅割合

		static const float		cm_OneFrameWidth;			//一枠の幅
		static const float		cm_OneFrameHeight;			//一枠の高さ

		static const float		cm_EquipmentUIYPos;			//装備欄の表示y位置割合
		static const float		cm_EquipmentUIHeight;		//装備欄の表示高さ割合

		static const float		cm_UnitUIXPos;				//ユニット欄の表示y位置割合
		static const float		cm_UnitUIYPos;				//ユニット欄の表示y位置割合
		static const float		cm_UnitUIHeight;			//ユニット欄の表示高さ割合

		static const int		cm_EquipmentHNum;			//装備欄行数
		static const int		cm_UnitHNum;				//ユニット欄行数
		static const int		cm_ColumnVNum;				//欄列数

		////タイプ
		//enum Type
		//{
		//	None=-1,										//ない時
		//	Equipment,										//装備
		//	Unit,											//ユニット
		//};
	//--------------------------------------------------------------------
	//	Method
	//--------------------------------------------------------------------
	private:
		//スライドのイン処理
		void SrideIn(void);
		//スライドのイン処理
		void SrideOut(void);

		//キー処理
		void KeyAction(void);

		//アイコンマウスオーバー時の判定処理
		void IconOver(void);
		//オーバー中の装備スロット
		void SetSlotOver(void);

		//アイコンの変更
		void IconChange(void);
		//アイコンの判別
		void EquipIconJudge(int num);

		//アイテム状態チェック
		void ItemCheck(void);

		//装備処理
		bool Equip(int *Content,TreeData *Root);

		//装備・ユニットのステータスの初期化処理:デバッグ用
		void ItemStatusReset(void);

		int GetMixTreeNum(int id,int type);
		int GetSortNum(int id,int type);
		
		void GetMaterialShine(int num);

		void DrawMaterialShine(void);
		void DrawStageMask(void);
		void DrawCanMixString(void);
		//位置確認用
		void DrawPosCheck(float x,float y,float w,float h);
		void DrawPosCheck(int x,int y,int w,int h);

		int ReverseGetID(int id,char type);

		int StrLength(const char *s);

		//アイテムを一つずつゲット
		void GetItem(void);
		//アイテムを一つずつゲット
		void GetMap(void);

	public:
		//================================================================
		//	Constructor
		//================================================================
		GameMenu(void);
		//デストラクタ
		virtual ~GameMenu(void);

		//初期化処理
		void Init(void);
		//更新処理
		void Update(void);
		//描画処理
		void Draw(void);
		//解放処理
		void Release(void);

		//開閉処理
		bool OpeningClosing(void);
		bool OpeningClosing(DXLibMath::Vector2 &mouse);

		//有効・無効切り替え
		void ChangeEnable(void);

		//================================================================
		//	Getter
		//================================================================
		bool GetEnable(void);

		bool GetConfirmationFlag(void){
			return m_EquipManager.GetConfirmationFlag();
		}

		bool GetFirstProduction(void){
			return m_FirstMixProduction.GetEnable();
		}
		bool GetProduction(void){
			return m_MixProduction.GetEnable();
		}

		// 装備中のユニットのIDを返す(int６つ分)
		//void GetUnitEquipment(int *unitID);
};

//========================================================================
//	End of file
//========================================================================