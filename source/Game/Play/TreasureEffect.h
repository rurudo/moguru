#pragma once
#include "../System/DxLibMath.h"
#include "GetTreasure.h"
#include "../System/FontManager.h"
#include "Glliter.h"
class TreasureEffect
{
private:
	enum Status
	{
		TREASURE_STATUS_IN,
		TREASURE_STATUS_ITEMIN,
		TREASURE_STATUS_WAIT,
		TREASURE_STATUS_OUT,
		TREASURE_STATUS_ITEMFRAMEIN,
		TREASURE_STATUS_ITEMDESCRIPTION,
		TREASURE_STATUS_ALLOUT
	}m_Status;

	static const int cm_IconPosX;
	static const int cm_IconPosY;

	int m_Frame;			// 演出用フレームカウント

	int m_ItemAlpha;
	int m_FrameAlpha;
	int m_DesAlpha;
	float m_ItemPosX;
	float m_ItemPosY;
	float m_FramePosX;
	float m_FramePosY;
	float m_DesPosX;
	float m_DesPosY;

	char m_Message[256];
	
	bool m_Skip;
	bool m_NowSkip;
	bool m_OutFlag;
	
	DXLibMath::Vector2 m_BackPosition;
	DXLibMath::Vector2 m_GlliterPosition;

	GetTreasure m_GetTreasure;
	Glliter m_Glliter[2];

	FontManager m_FontManager;

	void Init(void);
	void Update_In(void);
	void Update_ItemIn(void);
	void Update_Wait(void);
	void Update_Out(void);
	void Update_InFrame(void);
	void Update_InDes(void);
	void Update_AllOut(void);

	void DrawItem(void);

	void GetItemStatusChange(void);

	void GlliterUpdate(void);
	void GlliterDraw(DataManager &data);
public:
	TreasureEffect(void);
	~TreasureEffect(void);
	bool Update(void);
	void Draw(void);
};

