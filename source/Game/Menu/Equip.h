//========================================================================
//	@file		Equip.h
//	@note		装備処理
//	@author		RyotaUehara
//	@version	1.0
//========================================================================
#pragma once
//------------------------------------------------------------------------
//	IncludeHeader
//------------------------------------------------------------------------
#include "MixTreeData.h"
#include "ItemEquip.h"

//------------------------------------------------------------------------
//	Const
//------------------------------------------------------------------------

//------------------------------------------------------------------------
//	Equip
//	@brief 装備クラス
//------------------------------------------------------------------------
class Equip
{
	//--------------------------------------------------------------------
	//	Member
	//--------------------------------------------------------------------
	private:
		bool					m_End;						//終了フラグ
		bool					m_Check;					//チェックフラグ
		bool					m_ConfirmationFlag;			//合成・分解確認フラグ
		bool					m_HaveItem;					//アイテムを持っている状態

		bool					m_Debug;					//

		int						m_OkCancel;					//合成・分解の可否
		int						m_ItemFlag;					//アイテムの処理フラグ

		int						m_EquipCount;
		int						m_UnitCount;

		int						m_ItemSlotPos;				//右下スロットオーバー時アイコンスロットを出すときの座標

		DXLibMath::Vector2		m_Mouse;					//マウス位置
		EquipData				m_MixRoot;					//合成する先のデータ
		EquipData				m_MixData;					//合成するアイテムデータ
		EquipData				m_BreakData;				//分解するアイテムデータ

		TreeData				m_EquipData;				//

		TreeData				m_memData;
		TreeData				m_memData2;

		EquipData				*m_EquipmentSlot;			//装備品装備スロット
		EquipData				*m_UnitSlot;				//ユニット装備スロット

		FontManager				m_FontManager;				//独自フォント、自動改行用

		ItemEquip				*m_ItemEquipManager;

		DataManager				*m_Data;

		static const int		cm_ItemSlotPosFrame;		//右下のスロットオーバー時用フレーム数

		static const float		cm_RootMixStrX;				//ルート合成過程文字x座標
		static const float		cm_RootMixStrY;				//ルート合成過程文字y座標
		static const float		cm_ProcessStrX;				//ルート合成過程処理文字y座標
		static const float		cm_ProcessStrY;				//ルート合成過程処理文字y座標
		static const float		cm_ProcessSupStrX;			//ルート合成過程処理補助文字y座標
		static const float		cm_ProcessSupStrY;			//ルート合成過程処理補助文字y座標
		static const float		cm_MaterialStrX;			//素材文字x座標
		static const float		cm_MaterialStrY;			//素材文字y座標
		static const float		cm_MaterialStrHeight;		//素材文字高さ
		static const float		cm_ClickIconX;				//クリックアイコンx座標
		static const float		cm_RClickIconX;				//右クリックアイコンx座標
		static const float		cm_ClickIconY;				//クリックアイコンy座標
		static const float		cm_ClickIconWidth;			//クリックアイコン幅
		static const float		cm_ClickIconHeight;			//クリックアイコン高さ
		static const float		cm_ClickIconSupX;			//クリックアイコン補助文字x座標
		static const float		cm_RClickIconSupX;			//右クリックアイコン補助文字x座標
		static const float		cm_ClickIconSupY;			//クリックアイコン補助文字y座標

		enum Flag{
			None = -1,
			Flag_Mix,										//合成する
			Flag_Break,										//分解しなければいけない

			Flag_OK,										//OK
			Flag_Cancel										//キャンセル
		};

	public:
	//--------------------------------------------------------------------
	//	Method
	//--------------------------------------------------------------------
	private:
		//どの装備品・ユニットか判断
		bool Judge(void);
		//装備できるか判断
		bool EquipJudge(void);
		//装備チェック
		bool EquipCheck(void);
		bool EquipCheck(EquipData data);
		//合成チェック
		bool MixCheck(void);
		//渡されたIDのものの指定された素材番号をもとに抽出し返す:再帰処理
		bool MinRankExtractionNum(EquipData root,EquipData artifacts,int matNum);
		//素材から合成先を抽出:再帰処理
		bool OriginExtraction(EquipData artifacts);
		//合成処理
		void Mix(void);
		//分解処理
		void Break(void);

		//合成・分解確認処理
		bool Confirmation(void);

		//装備の確認
		void EquipConfirmation(void);
		//装備済みシンボルの描画処理
		void DrawEquipSymbol(void);
		//Newシンボル描画
		void DrawNewSymbol(void);
		//現在つかんでいるアイコン描画
		void DrawHaveItem(void);
		//オーバー中の装備スロットを光らせる
		void DrawSlotOver(void);

		//処理終了後初期化
		void Clear(void);

		//モグルの装備ステータスをセット
		void SetMogllEquipStatus(void);
		void SetMogllEquipStatus(char type,int slotNum);

		//ソートされたリストから逆引き
		int ReverseGetID(int id,char type);
	public:
		//================================================================
		//	Constructor
		//================================================================
		Equip(void);
		//デストラクタ
		virtual ~Equip(void);

		//初期化処理
		void Init(void);
		//更新処理
		bool Update(int *Content,TreeData *Root);
		//描画処理
		void Draw(void);
		//スロットの描画
		void DrawSlot(void);
		void SymbolDraw(void);
		void OtherDraw(void);

		//解放処理
		void Release(void);

		//デバッグ用リセット
		void Reset(void);

		//チェックフラグを立てる
		void CheckEnable(void);
		//つかんでいるアイテムの削除
		void ResetHaveItem(void);
		//つかんでいるアイテムの削除:スロットも戻す
		void ResetHaveItem2(void);
		//アイテム装備クラスへのポインタを格納
		void SetItemEquip(ItemEquip* instance);

		bool GetHaveFlag(void);

		TreeData* GetHaveItem(void){
			return &m_EquipData;
		}

		void SetDebug(void){
			if(m_Debug)
				m_Debug = false;
			else
				m_Debug = true;
		}

		//合成分解確認中か確認
		bool GetConfirmationFlag(void){
			return m_ConfirmationFlag;
		}

		//bool isConfirmation(void)
		//{
		//	return m_ConfirmationFlag;
		//}
};

//========================================================================
//	End of file
//========================================================================