#pragma once
#include "../System/DxLibMath.h"
#include "../System/FontManager.h"
#include <list>
class PlayUserInterface
{
private:
	struct Rect
	{
		float x, y, width, height;
	}m_FieldRect;
	float m_LinePos;			// レーダーラインの位置
	int m_LineCount;			// レーダーラインの判定カウント
	VECTOR m_Mouse;				// マウス座標
	int m_CurrentPosition;		// 現在標準の当たっている枠
	float	m_EscButton;		// 脱出ボタンX座標
	float	ESC_IN_POS;			// 脱出ボタン基準位置（内側）
	float   ESC_OUT_POS;		// 脱出ボタン基準位置（外側）
	float   ESC_BUTTON_WIDTH;	// 脱出ボタン幅
	float   ESC_BUTTON_HEIGHT;	// 脱出ボタン高さ 
	bool	m_GetOut;			// 脱出フラグ
	bool	m_Retry;
	float	m_EscChkButtonSize[3];	// 脱出確認ボタンサイズ
	bool	m_EscChkSEFlg[3];	// 脱出確認ボタンSEフラグ
	bool	m_DrawEffect;		// フィールドエフェクトを描画するか
	VECTOR	m_FieldEffect[2];	// フィールドエフェクト位置
	float	m_EffectAlpha[2];	// フィールドエフェクトα値
	float   FIELD_EFFECT_WIDTH; // フィールドエフェクト幅
	float   FIELD_EFFECT_HEIGHT;// フィールドエフェクト高さ
	FontManager m_Font;			// 文字描画用
	double	m_LifeRot;			// ライフメーター表示位置
	double	m_ResourceRot;		// リソースメーター表示位置
	int		m_PrevLife;			// 前回のライフ
	int		m_DamageCount;		// ダメージエフェクト
	bool	m_VisibleFlag;		// 装備欄の表示フラグ
	bool	m_EscapeFlag;
	// レーダー発見物
	static const int OBJECT_MAX = 50;
	struct DrawObject
	{
		bool exist;
		int x, y;
		int id, alpha;
		double size;
	} m_DrawObject[OBJECT_MAX];
	int m_NumObject;

	void Input(void);
	void RadarCalc(void);
	void AddObject(int x, int y, int id);

	void ClearButtonSize(void)
	{
		for(int i=0; i<3; i++)
		{
			m_EscChkButtonSize[i] = 0.5f;
			m_EscChkSEFlg[i] = false;
		}
	}
public:
	PlayUserInterface(void);
	~PlayUserInterface(void);
	void Update(void);
	void UpdateEffect(void);
	void UpdateButton(void);
	void UpdateLife(void);
	void Draw(float depth);
	void DrawMogll(void);
	void DrawFieldEffect(void);
	void DrawEscape(void);
	void Init(void);
	
	void CheckCurrentSlot(void);

	void SetVisible(bool flag)
	{
		m_VisibleFlag = flag;
	}

	//脱出フラグの取得
	bool GetOutFlg(void)
	{
		return m_GetOut;
	}

	//脱出フラグの取得
	bool GetRetryFlg(void)
	{
		return m_Retry;
	}

	//脱出ウィンドウ状態の取得
	bool GetEsFlg(void)
	{
		return m_EscapeFlag;
	}
};

