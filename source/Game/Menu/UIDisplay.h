#pragma once
#include "../System/DxLibMath.h"
#include "../System/DataManager.h"

typedef struct UIDispMainData{
	DXLibMath::Vector2 pos;
	DXLibMath::Vector2 size;
	VECTOR color;
}UIDispMainData;

class UIDisplay
{
public:
	UIDisplay(void);
	~UIDisplay(void);

	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);

	//引数からメインデータに格納
	void SetMainData(DXLibMath::Vector2 pos,DXLibMath::Vector2 size,VECTOR color,int flag);
	//フラグのセット
	void SetFlag(int flag);

	enum Flag{
		Flag_OC,			//開いて閉じる
		Flag_CO,			//閉じて開く
		Flag_Close,
		Flag_Open,
		Flag_ColorP,
		Flag_ColorM
	};

	enum Size{
		Def_PosX = 700,
		Def_PosY = 195,
		Size_DefX = 126/2,
		Size_DefY = 300/2,
		Size_SubC1 = -Size_DefY,	//Y
		Size_SubC2 = -Size_DefX,	//X
		Size_SubC3 =	 30,		//Y
		Size_SubC4 =	-30,		//Y
		Size_SubC5 =	 10,		//X
		Size_SubC6 =	-10,		//X

		Size_SubO1 = Size_DefX,		//X
		Size_SubO2 = Size_DefY		//Y
	};

private:
	bool			m_Enable;
	int				m_Flag;
	int				m_Step;
	int				m_SubStep;

	int				m_Frame;

	int				m_Alpha;

	UIDispMainData	m_MainData;

	//DataManager		*m_Data;

	enum Step{
		Step_Open,			//開く
		Step_Close,			//閉じる
		Step_Wait			//待ち状態
	};

	enum SubStep{
		Sub1,
		Sub2,
		Sub3,
		Sub4,
		Sub5,
		Sub6
	};

	enum Frame{
		//Frame_Open = 30,	//開く処理時間
		//Frame_Close = 30,	//閉じる処理時間
		Frame_SubO1 = 6,
		Frame_SubO2 = 7,

		Frame_SubC1 = 5,
		Frame_SubC2 = 4,
		Frame_SubC3 = 2,
		Frame_SubC4 = 2,
		Frame_SubC5 = 2,
		Frame_SubC6 = 1,

		Frame_SubO = Frame_SubO1+Frame_SubO2,
		Frame_SubC = Frame_SubC1+Frame_SubC2+Frame_SubC3+Frame_SubC4+Frame_SubC5+Frame_SubC6,
	};

	//サブアップデート
	void UpdateOpen(void);
	void UpdateClose(void);
	void UpdateOC(void);
	void UpdateCO(void);

	void Reset(void);

	//開く処理
	bool Open(void);
	//閉じる処理
	bool Close(void);

	//
	void Judge(void);

	void CalcColor(int colVal,int flag);
};

