#include "GetTreasureShine.h"

GetTreasureShine :: GetTreasureShine(void)
{
	Init();
}


GetTreasureShine :: ~GetTreasureShine(void)
{
}

void GetTreasureShine :: Init(void){
	for(int i=0;i<4;i++){
		m_Pos[i].x = 0.0f;
		m_Pos[i].y = 0.0f;
	}

	m_Cp.x = 0.0f;
	m_Cp.y = 0.0f;
	
	//m_Velocity = (float)Velocity;

	m_Step[0] = Step_Move1;
	m_Step[1] = Step_Move1;

	m_Enable = false;

	m_Flag[0] = false;
	m_Flag[1] = false;
	m_Flag[2] = false;
	m_Flag[3] = false;
	m_Flag[4] = false;
}

void GetTreasureShine :: Release(void){
}

void GetTreasureShine :: SetPoint(float x,float y){
	if(!m_Enable){
		Init();
		m_Enable = true;
		m_Cp.x = x;
		m_Cp.y = y;
		m_Pos[0].x = m_Cp.x;
		m_Pos[0].y = 0.0f;
		m_Pos[1].x = m_Cp.x;
		m_Pos[1].y = 0.0f;
		m_Pos[2].x = m_Cp.x;
		m_Pos[2].y = m_Cp.y;
	}
}

void GetTreasureShine :: Update(void){
	if(m_Enable){
		Move1();
		Move2();
		Move3();
		Move4();
		Move5();
	}
}
void GetTreasureShine :: Move1(void){
	if(m_Step[0] == Step_Move1){
		m_Pos[0].x += Velocity1;
		if(m_Pos[0].x >= 1000.0f){
			m_Step[0]++;
		}
		m_Alpha += 20;
		if(m_Alpha > 200){
			m_Alpha = 200;
		}
	}
	if(m_Flag[0] == false && Dis1 <= (m_Pos[0].x - m_Pos[1].x))
		m_Flag[0] = true;
	if(m_Step[1] == Step_Move1 && m_Flag[0]){
		m_Pos[1].x += Velocity4;
		if(m_Pos[1].x >= 1000.0f){
			m_Step[1]++;
			m_Flag[0] = false;
		}
	}
}
void GetTreasureShine :: Move2(void){
	if(m_Step[0] == Step_Move2){
		m_Pos[0].y += Velocity2;
		if(m_Pos[0].y >= 800.0f){
			m_Step[0]++;
		}
	}
	if(m_Flag[1] == false && Dis2 <= (m_Pos[0].y - m_Pos[1].y))
		m_Flag[1] = true;
	if(m_Step[1] == Step_Move2 && m_Flag[1]){
		m_Pos[1].y += Velocity5;
		if(m_Pos[1].y >= 800.0f){
			m_Step[1]++;
			m_Flag[1] = false;
		}
	}
}
void GetTreasureShine :: Move3(void){
	if(m_Step[0] == Step_Move3){
		m_Pos[0].x -= Velocity3;
		if(m_Pos[0].x <= -200.0f){
			m_Step[0]++;
		}
	}
	if(m_Flag[2] == false && Dis3 <= (m_Pos[1].x - m_Pos[0].x))
		m_Flag[2] = true;
	if(m_Step[1] == Step_Move3 && m_Flag[2]){
		m_Pos[1].x -= Velocity6;
		if(m_Pos[1].x <= -200.0f){
			m_Step[1]++;
			m_Flag[2] = false;
		}
	}
}
void GetTreasureShine :: Move4(void){
	if(m_Step[0] == Step_Move4){
		m_Pos[0].y -= Velocity2;
		if(m_Pos[0].y <= -200.0f){
			m_Step[0]++;
		}
	}
	if(m_Flag[3] == false && Dis2 <= (m_Pos[1].y - m_Pos[0].y))
		m_Flag[3] = true;
	if(m_Step[1] == Step_Move4 && m_Flag[3]){
		m_Pos[1].y -= Velocity5;
		if(m_Pos[1].y <= -200.0f){
			m_Step[1]++;
			m_Flag[3] = false;
		}
	}
}
void GetTreasureShine :: Move5(void){
	if(m_Step[0] == Step_Move5){
		m_Pos[0].x += Velocity1;
		m_Alpha -= 20;
		if(m_Alpha < 0)
			m_Alpha = 0;
	}
	if(m_Flag[4] == false && Dis1 <= (m_Pos[1].x - m_Pos[0].x))
		m_Flag[4] = true;
	if(m_Step[1] == Step_Move5 && m_Flag[4]){
		m_Pos[1].x += Velocity4;
		if(m_Pos[1].x >=  m_Cp.x + 200.0f){
			m_Step[0] = Step_Move1;
			m_Step[1] = Step_Move1;
			m_Flag[4] = false;
			m_Enable = false;
			m_Alpha = 0;
			Disable();
		}
	}
}

void GetTreasureShine :: Draw(void){
	int l_color = GetColor(255,239,133);//243,213,26);
	int l_color2 = GetColor(243,213,26);

	if(m_Enable){
		SetDrawBlendMode(DX_BLENDMODE_ADD,255);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_Alpha);
		DrawTriangle(	static_cast<int>(m_Pos[0].x),static_cast<int>(m_Pos[0].y),
						static_cast<int>(m_Pos[1].x),static_cast<int>(m_Pos[1].y),
						static_cast<int>(m_Pos[2].x),static_cast<int>(m_Pos[2].y),l_color2,TRUE);
		DrawTriangle(	static_cast<int>(m_Pos[0].x),static_cast<int>(m_Pos[0].y),
						static_cast<int>(m_Pos[1].x),static_cast<int>(m_Pos[1].y),
						static_cast<int>(m_Pos[2].x),static_cast<int>(m_Pos[2].y),l_color,TRUE);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
	}											
}

void GetTreasureShine :: Disable(void){
	m_Enable = false;
}

