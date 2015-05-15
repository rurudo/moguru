//========================================================================
//	@file		AfterGetMapProduction.h
//	@note		宝ゲット後の演出
//========================================================================
#pragma once
//------------------------------------------------------------------------
//	IncludeHeader
//------------------------------------------------------------------------
#include "../Menu/MixTreeData.h"
#include "../System/DxLibMath.h"
#include "../System/DataManager.h"
#include "../System/FontManager.h"
#include "Glliter.h"
#include <vector>

//------------------------------------------------------------------------
//	Const
//------------------------------------------------------------------------

//------------------------------------------------------------------------
//	@Class AfterGetMapProduction
//	@brief 宝ゲット後の演出
//------------------------------------------------------------------------
class AfterGetMapProduction
{
	//--------------------------------------------------------------------
	//	Member
	//--------------------------------------------------------------------
	private:
		bool				m_Enable;						//有効フラグ
		bool				m_Skip;							//スキップフラグ
		bool				m_NowSkip;						//スキップ中フラグ
		int					m_Step;							//ステップ
		int					m_Frame;						//フレームカウント

		int					m_ItemNum;						//入手した物:0~(アイテム)　60~(マップ)
		int					m_ItemHandle;						//入手した物:0~(アイテム)　60~(マップ)
		int					m_ItemAipha;					//入手した物のアルファ値
		int					m_MessAipha;					//入手した物のアルファ値
		int					m_DesAipha;					//入手した物のアルファ値
		float				m_ItemExpansion;				//入手した物の拡大率

		char				m_Message[256];

		DXLibMath::Vector2	m_BackPos;						//背景の位置
		DXLibMath::Vector2	m_MessagePos;					//位置
		DXLibMath::Vector2	m_DescriptionPos;				//位置
		DXLibMath::Vector2	m_FramePos;						//位置

		DataManager			*m_Data;						//

		FontManager			m_FontManager;					//独自フォント、自動改行用

		static const int	cm_BackPosX;					//背景位置
		static const int	cm_BackPosY;					//背景位置
		static const int	cm_BackOff;						//背景位置
		static const int	cm_StagePosX;					//アイコン位置
		static const int	cm_StagePosY;					//アイコン位置
		static const int	cm_IconPosX;					//アイコン位置
		static const int	cm_IconPosY;					//アイコン位置
		static const int	cm_GetMessagePosX;				//メッセージ:入手しました位置
		static const int	cm_GetMessagePosY;				//メッセージ:入手しました位置
		static const int	cm_GetMessageOff;				//メッセージ:入手しました位置
		static const int	cm_DecriptionPosX;				//入手したものの説明位置
		static const int	cm_DecriptionPosY;				//入手したものの説明位置
		static const int	cm_DecriptionOff;				//入手したものの説明位置

		enum Step{
			STEP_Init = 0,				//初期化
			STEP_FrameIn,				//背景イン
			STEP_InWait,				//ウェイト時間
			STEP_IconIn,				//アイコンイン
			STEP_MessageIn,				//メッセージイン
			STEP_DescriptionIn,			//説明イン
			STEP_EndWait,
			STEP_TreeOut				//枠アウト
		};

		enum Frame{
			FRAME_FrameIn = 75,		//背景イン
			FRAME_InWait = 20,			//ウェイト時間
			FRAME_IconIn = 40,			//アイコンイン
			FRAME_MessageIn = 40,		//メッセージイン
			FRAME_DescriptionIn = 40,	//説明イン
			FRAME_EndWait = 40,
			FRAME_FrameOut = 100		//枠アウト
		};
	public:
	//--------------------------------------------------------------------
	//	Method
	//--------------------------------------------------------------------
	private:
		//ステップ更新処理
		void UpdateStep(void);

		//ツリー枠イン
		void InFrame(void);
		//
		void InIcon(void);
		//
		void InMessage(void);
		//
		void InDescription(void);
		//ツリー枠アウト
		void OutFrame(void);

		//ツリー枠描画
		void DrawFrame(void);
		//
		void DrawIcon(void);
		//
		void DrawMessage(void);
		//
		void DrawDescription(void);
		//
		void DrawMixresult(void);

		//
		void Reset(void);
	public:
		//================================================================
		//	Constructor
		//================================================================
		AfterGetMapProduction(void);
		//デストラクタ
		virtual ~AfterGetMapProduction(void);

		//初期化
		void Init(void);
		//更新
		void Update(void);
		//描画
		void Draw(void);
		//解放
		void Release(void);

		void Enable(void);

		bool GetEnable(void);
};

//========================================================================
//	End of file
//========================================================================