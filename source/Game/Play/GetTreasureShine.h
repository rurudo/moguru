#pragma once
#include "../System/DxLibMath.h"
#include "../System/DataManager.h"

class GetTreasureShine
{
private:
	DXLibMath::Vector2 m_Pos[3];
	DXLibMath::Vector2 m_Cp;
	float m_Velocity;
	int m_Alpha;
	int m_Step[2];

	bool m_Enable;
	bool m_Flag[5];

	enum Const{
		Dis1 = 150,
		Dis2 = 250,
		Dis3 = 375,
		Velocity1 = 100,
		Velocity2 = 80,
		Velocity3 = 60,
		Velocity4 = 110,
		Velocity5 = 90,
		Velocity6 = 70
	};

	enum Step{
		Step_Wait,
		Step_Move1,
		Step_Move2,
		Step_Move3,
		Step_Move4,
		Step_Move5,
		Step_Stay
	};

	void Move1(void);
	void Move2(void);
	void Move3(void);
	void Move4(void);
	void Move5(void);
public:
	GetTreasureShine(void);
	~GetTreasureShine(void);

	void Init(void);
	void Release(void);
	void Update(void);
	void Draw(void);

	void SetPoint(float x,float y);

	void Disable(void);
};

