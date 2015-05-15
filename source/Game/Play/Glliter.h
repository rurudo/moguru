//========================================================================
//	@file		Glliter.h
//	@note		ゲット後ツリーアイコンのきらきら
//========================================================================
#pragma once
//------------------------------------------------------------------------
//	IncludeHeader
//------------------------------------------------------------------------
#include "../System/DxLibMath.h"
#include "../System/DataManager.h"

typedef struct GlliterData{
	DXLibMath::Vector2 pos;
	char step;
	int alpha;
	float expantion;
	bool alive;
}GlliterData;

//------------------------------------------------------------------------
//	@brief ゲット後ツリーアイコンのきらきら
//------------------------------------------------------------------------
class Glliter
{
	//--------------------------------------------------------------------
	//	Member
	//--------------------------------------------------------------------
	private:
		DXLibMath::Vector2 m_ReferencePoint;

		GlliterData m_GlliterList[4];
	public:
	//--------------------------------------------------------------------
	//	Method
	//--------------------------------------------------------------------
	private:
		//
		void Add(DXLibMath::Vector2* rp);
	public:
		//================================================================
		//	Constructor
		//================================================================
		Glliter(void);
		//デストラクタ
		virtual ~Glliter(void);

		//初期化
		void Init(void);
		//更新
		void Updata(DXLibMath::Vector2* rp);
		//描画
		void Draw(DataManager *data);

		void Clear(void);

		//bool GetEnable(void);
};

//========================================================================
//	End of file
//========================================================================