#pragma once
#include <string.h>
#include "DxLib.h"
#include "../System/DxLibMath.h"
#include "../System/FontManager.h"

class Help
{
private:
	enum STATE
	{
		INDEX,
		REFERENCE,
	};
	enum CONTROL
	{
		STAY,
		PREV,
		NEXT,
		BACK,
	};
	struct DRAW_DATA{
		float	x, y;
		float	scal, rot;
		int		handle;
	};

	bool		m_Exist;
	bool		m_OffFrame;			// 終了したフレームかどうか（ヘルプのUpdateのあとにOpenが走るので）
	int			m_Frame;			// 演出のタイミングカウンタ
	STATE		m_State;			// ステート
	int			m_Index;			// 選択目次
	int			m_Page;				// ページ
	int			m_OldPage;			// 前ページ
	int			m_PageAlpha;		// ページのα値
	float		m_M_Scal;			// マウスの拡縮
	float		m_Help_Button_Scale;// ヘルプボタンの拡縮
	bool		m_ScalFlg;			// 拡大か縮小のフラグ
	const static int	NUM_PAGE = 12;
	DRAW_DATA	m_WordHowto[NUM_PAGE];		// 描画データ
	const static int	NUM_INDEX = 8;
	int			m_IndexPage[NUM_INDEX];		// 項目ごとのページ数
	float		m_I_Scale[NUM_INDEX];		// 項目の拡縮率
	FontManager m_Font;			// 文字描画用

	int UpdateIndex(void);	// 目次
	Help::STATE UpdateReference(void);	//ページ更新
	Help::CONTROL UpdatePages(void);	//ページ送り

	void DrawIndex(void);
	void DrawReference(void);

	bool Close(void);

	//カラー変更
	int	ChangeColor(int i)
	{
		if(i == m_Index)
			return GetColor(255, 16, 16);
		return GetColor(0, 0, 0);
	}

public:
	Help(void);
	~Help(void);
	void Draw(void);
	bool Update(void);
	void Init(void);
	bool Open(DXLibMath::Vector2 &mouse);
};

