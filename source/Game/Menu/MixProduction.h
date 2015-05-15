//========================================================================
//	@file		MixProduction.h
//	@note		合成分解演出
//	@author		RyotaUehara
//========================================================================

//------------------------------------------------------------------------
//	IncludeHeader
//------------------------------------------------------------------------
#include "../System/DxLibMath.h"

typedef struct MixObj{
	VECTOR	position;		//位置
	int					alpha;			//アルファ値
	bool				flag;

	MixObj(void) : alpha(255),flag(false){
		position.x = 0.0;
		position.y = 0.0;
	}
}MixObj;

typedef struct MixSphere{
	MixObj				data;
	VECTOR	velocity;
}MixSphere;

typedef struct MixCircle{
	MixObj				data;			//データ
	float				expansion;		//拡大率

	MixCircle(void) : expansion(1.0){}
}MixCircle;

//------------------------------------------------------------------------
//	@Class MixProduction MixProduction.h 
//	@brief 合成分解演出
//------------------------------------------------------------------------
class MixProduction
{
	//--------------------------------------------------------------------
	//	Member
	//--------------------------------------------------------------------
	private:
		bool					m_Enable;					//有効フラグ
		bool					m_Draw;						//描画フラグ
		int						m_Step;						//処理ステップ
		int						m_Content;					//内容フラグ:合成か分解か
		int						m_Time;						//時間

		int						m_RootId;
		int						m_RootType;

		MixSphere				m_Sphere[4];				//合成・分解時の球のデータ
		MixObj					m_Material[4];				//
		MixObj					m_Main;						//
		MixCircle				m_Circle;					//合成時の球のデータ

		enum Step{
			None = -1,
			FEmission,
			SEmission,
			Start,
			Preparation,
			Run,
			Finish
		};

		enum StepTime{
			Time_FEmission		= 10,
			Time_SEmission		= 10,
			Time_Start			= 5,
			Time_Preparation	= 30,
			Time_Run			= 30,
			Time_Finish			= 10
		};

		static const int		cm_WhiteAlpha;				//
		static const int		cm_CircleAlpha;				//
		//static const int		cm_DivisionHermite;			//エルミート分割数
		static const float		cm_MaxExpansion;			//拡大最大倍率
		static const float		cm_MaxExpansionPlus;		//拡大最大倍率
	public:
		enum Contant{
			Mix,
			Break
		};
	//--------------------------------------------------------------------
	//	Method
	//--------------------------------------------------------------------
	private:
		//第一発光ステップ
		void StepFirstEmission(void);
		//第二発光ステップ
		void StepSecondEmission(void);
		//スタートステップ
		void StepStart(void);
		//準備ステップ
		void StepPreparation(void);
		//実行ステップ
		void StepRun(void);
		//完了ステップ
		void StepFinish(void);

		//第一発光描画
		void DrawFirstEmission(void);
		//第二発光描画
		void DrawSecondEmission(void);
		//スタート描画
		void DrawStart(void);
		//完了描画
		void DrawFinish(void);

		//演出データリセット
		void Reset(void);

		//ソートされたリストから逆引き
		int ReverseGetID(int id,char type);
	public:
		//================================================================
		//	Constructor
		//================================================================
		MixProduction(void);
		//デストラクタ
		virtual ~MixProduction(void);

		//初期化処理
		void Init(void);
		//更新処理
		bool Update(void);
		//描画処理
		void Draw(void);
		//解放処理
		void Release(void);

		//内容をセット
		void SetContent(int Content,int RootId,int RootType);

		bool GetEnable(void);
};

//========================================================================
//	End of file
//========================================================================