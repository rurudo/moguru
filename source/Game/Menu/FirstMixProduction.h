#pragma once
#include "DxLib.h"
#include "../System/FontManager.h"

class FirstMixProduction
{
public:
	FirstMixProduction(void);
	~FirstMixProduction(void);

	//初期化
	void Init(void);
	//解放
	void Release(void);
	//更新
	bool Update(void);
	//描画
	void Draw(void);

	//有効化
	void Enable(int MixNum,int MixType);

	bool GetEnable(void);
private:
	//ステップの更新
	void StepUpdate(void);

	//ステップ処理
	void StepInItem(void);
	void StepInFrame(void);
	void StepInMessage(void);
	void StepInDescription(void);
	void StepOutItem(void);
	void StepOutFrame(void);
	void StepOutMessage(void);
	void StepOutDescription(void);

	//ステップ毎の描画
	void DrawItem(void);
	void DrawFrame(void);
	void DrawMessage(void);
	void DrawDescription(void);

	//リセット
	void Reset(void);

	char m_ItemStatus[60];			// 装備の所持、未所持、未発見、装備等のステータス
	char m_UnitStatus[30];			// ユニットの所持、未所持、未発見、装備等のステータス

	//合成したもののID
	int m_ID;
	//タイプ
	int m_Type;
	//フレーム
	int m_Frame;
	//α値
	int m_AlphaItem;
	int m_AlphaFrame;
	int m_AlphaMessage;
	int m_AlphaDescription;

	int m_ItemX;
	int m_ItemY;
	int m_ItemW;
	int m_ItemH;
	int m_FrameX;
	int m_FrameY;
	int m_FrameW;
	int m_FrameH;
	int m_MessageX;
	int m_MessageY;
	int m_MessageW;
	int m_DescriptionX;
	int m_DescriptionY;
	int m_DescriptionW;
	//ステップ
	int m_Step;

	//有効フラグ
	bool m_Enable;
	//スキップフラグ
	bool m_Skip;
	//スキップ中フラグ
	bool m_NowSkip;

	FontManager m_FontManager;

	enum Step{
		STEP_Init,
		STEP_InItem,
		STEP_InFrame,
		STEP_InMessage,
		STEP_InDescription,
		STEP_Wait,
		STEP_OutItem,
		STEP_OutFrame,
		STEP_OutMessage,
		STEP_OutDescription
	};

	static const int FrameInItem;
	static const int FrameInFrame;
	static const int FrameInMessage;
	static const int FrameInDescription;
	static const int FrameWait;
	static const int FrameOutItem;
	static const int FrameOutFrame;
	static const int FrameOutMessage;
	static const int FrameOutDescription;
	
	static const int Movement;
};

