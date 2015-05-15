#pragma once
#include "../System/DxLibMath.h"
#include "../System/DataManager.h"

typedef struct MatData{
	DXLibMath::Vector2 Distance;
	float angle;
	int alpha;
	int type;
}MatData;

typedef struct ContentData{
	int cracker;
	MatData tape[4];
	int tapeNum[4];
	MatData paper[6];
	bool paperDir[6];
}ContentData;

class Cracker
{
	private:
		ContentData m_Content;

		DXLibMath::Vector2 m_Position;
		DXLibMath::Vector2 m_Offset;
		float	 m_Angle;
		int		m_Frame;
		int		m_Step;
		int		m_Alpha;
		bool	m_Direction;
		bool	m_Enable;

		DataManager *m_Data;

		enum Step{
			STEP_In,
			STEP_Wait,
			STEP_Explosion,
			STEP_Stay,
			TIME_In			= 30,
			TIME_Wait		= 20,
			TIME_Explosion	= 10,
			TIME_Stay		= 60
		};
		enum Const{
			Type_Roll=0,
			Type_St=1,
			Turn1,
			Turn2,
			CrackerNum = 4,
			CrackerMarginX = -20,
			CrackerMarginY = -20,
			TickerNum = 4,
			TickerDisBaseX = -80,
			TickerDisBaseY = -80,
			TickerDisRangeX = 150,
			TickerDisRangeY = 100,
			TapeRollNum = 6,
			TapeStNum = 12,
			TapeDisX = 40,
			TapeDisY = 40,
			TapeAngle = 25
		};
	public:
		enum SetParam{
			Dir_L,
			Dir_R
		};
	public:
		Cracker(void);
		~Cracker(void);

		void Init(void);
		void Release(void);
		bool Update(void);
		void Draw(void);

		void SetPosition(DXLibMath::Vector2 pos,int dir);
		void Disable(void);
	private:
		void SetContent(void);

		void UpdateIn(void);
		void UpdateExplosion(void);
		void UpdateStay(void);

		void DrawIn(void);
		void DrawExplosion(void);

		float GetRadian(float degree);
		int GetTapeTypeHandle(int type);
		bool GetPaperDirection(bool paperDir);
};

