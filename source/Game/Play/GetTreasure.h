#include "../System/DxLibMath.h"
#include "../System/DataManager.h"
#include "GetTreasureShine.h"
#include "Cracker.h"
//=======================================================================
//	@file	MenuIconSort.h
//	@note	メニュー内でのアイコンの並び替えデータ
//=======================================================================
typedef struct MainData{
	DXLibMath::Vector2 pos;
	int alpha;
}MainData;

typedef struct GetSring{
	MainData data;
	int gg_index;
}GetSring;

typedef struct GetShine{
	MainData data;
	float angle;
	float expansion;
	bool expRFlag;
}GetShine;

//------------------------------------------------------------------------
//	GetTreasure
//	@brief 装備クラス
//------------------------------------------------------------------------
class  GetTreasure{
	//--------------------------------------------------------------------
	//	Member
	//--------------------------------------------------------------------
	private:
		MainData				m_GetTreasure;
		GetSring				m_GetString1;
		GetSring				m_GetString2;
		GetShine				m_GetShine;
		GetTreasureShine		m_Shine[3];
		//クラッカー
		Cracker					m_Cracker;
		Cracker					m_Cracker2;
		Cracker					m_Cracker3;
		//キラキラ
		int						m_Step;
		int						m_ShineStep;
		int						m_Frame;
		int						m_StringFrame1;
		int						m_StringFrame2;
		int						m_ShineFrame;
		int						m_CrackerFrame;

		int						m_AllAlpha;
		bool					m_OutFlag;

		bool					m_GetStringType;
		bool					m_Enable;
		bool					m_Skip;
		bool					m_NowSkip;
		bool					m_SEFlag;
		bool					m_LightFlag;

		DataManager				*m_Data;

		static const int		cm_GT_MogllFrame;
		static const int		cm_GT_StringFrame;
		static const int		cm_GT_CrackerFrame;
		static const float		cm_GT_MogllPosX;
		static const float		cm_GT_MogllPosY;
		static const float		cm_GT_MogllTargetPosY;
		static const float		cm_GT_TreasureShinePosX;
		static const float		cm_GT_TreasureShinePosY;
		static const float		cm_GT_String1PosX;
		static const float		cm_GT_String1PosY;
		static const float		cm_GT_String2PosX;
		static const float		cm_GT_String2PosY;
		static const float		cm_GT_StringTargetDistanceX;
		static const float		cm_GT_StringTargetDistanceY;
		static const float		cm_GT_Cracker1PosX;
		static const float		cm_GT_Cracker1PosY;
		static const float		cm_GT_Cracker2PosX;
		static const float		cm_GT_Cracker2PosY;
		static const float		cm_GT_Cracker3PosX;
		static const float		cm_GT_Cracker3PosY;

		enum Step{
			STEP_Mogll,
			STEP_TreasureShine,
			STEP_String1,
			STEP_String2,
			STEP_Cracker1,
			STEP_Cracker2,
			STEP_Wait
		};

		enum TreasureShineStep{
			TSS_Shine1,
			TSS_Shine2,
			TSS_Wait,
			TSST_Shine1 = 10,
			TSST_Shine2	= 25,
			TSST_Wait	= 80
		};

	//--------------------------------------------------------------------
	//	Method
	//--------------------------------------------------------------------
	public:
		//コンストラクタ
		GetTreasure(void);
		//デストラクタ
		~GetTreasure(void);

		void Update(void);
		void Init(void);
		void Release(void);
		void Draw(void);

		void Enable(void);
		void Disable(void);
		void Reset(void);

		bool Out(void);

		bool GetEnable(void);
		void SetLightFlag(bool flag);
		void SetOutFlag(bool flag);
	private:
		//ステップごとの処理----
		//モグルイン
		void UpdateMogll(void);
		//宝キラキラ
		void UpdateTreasureShine(void);
		//宝ゲット文字
		void UpdateGetString1(void);
		void UpdateGetString2(void);
		//クラッカー演出
		void UpdateCracker(void);
		//きらきら演出
		void UpdateGlliter(void);

		//ステップごとの描画----
		//モグルイン
		void DrawMogll(void);
		//宝キラキラ
		void DrawTreasureShine(void);
		//宝ゲット文字
		void DrawGetString1(void);
		void DrawGetString2(void);
		//クラッカー演出
		void DrawCracker(void);
		//きらきら演出
		void DrawGlliter(void);

};
//========================================================================
//	End of file
//========================================================================