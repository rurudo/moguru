//========================================================================
//	@file		GetTreeIconGlliter.h
//	@note		ゲット後ツリーアイコンのきらきら
//========================================================================
#pragma once
//------------------------------------------------------------------------
//	IncludeHeader
//------------------------------------------------------------------------
#include <list>
#include "../System/DxLibMath.h"

typedef struct GlliterData{
	VECTOR pos;
	VECTOR velocity;
	int alpha;
	bool alive;
}GlliterData;

//------------------------------------------------------------------------
//	@brief ゲット後ツリーアイコンのきらきら
//------------------------------------------------------------------------
class GetTreeIconGlliter
{
	//--------------------------------------------------------------------
	//	Member
	//--------------------------------------------------------------------
	private:
		bool m_Enable;

		std::list<GlliterData*> m_GlliterList;
	public:
	//--------------------------------------------------------------------
	//	Method
	//--------------------------------------------------------------------
	private:
		//削除
		void Delete(void);
	public:
		//================================================================
		//	Constructor
		//================================================================
		GetTreeIconGlliter(void);
		//デストラクタ
		virtual ~GetTreeIconGlliter(void);

		//初期化
		void Init(void);
		//更新
		void Updata(void);
		//描画
		void Draw(void);
		//解放
		void Release(void);

		bool GetEnable(void);
};

//========================================================================
//	End of file
//========================================================================