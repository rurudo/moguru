#include "UIDisplay.h"


UIDisplay::UIDisplay(void)
{
	Init();
}


UIDisplay::~UIDisplay(void)
{
	Release();
}

void UIDisplay::Init(void){
	m_Enable = false;
	m_Flag = Flag_CO;
	m_Step = Step_Wait;
	m_SubStep = Sub1;

	m_Alpha = 255;

	m_MainData.pos.x = static_cast<float>(Def_PosX); 
	m_MainData.pos.y = static_cast<float>(Def_PosY); 
	m_MainData.size.x = static_cast<float>(Size_DefX); 
	m_MainData.size.y = static_cast<float>(Size_DefY); 
	m_MainData.color.x = 0.0f; 
	m_MainData.color.y = 0.0f; 
	m_MainData.color.z = 0.0f; 

	//m_Data = &DataManager::GetInstance();
}
void UIDisplay::Reset(void){
	m_Flag = Flag_CO;
	m_Step = Step_Wait;
	m_SubStep = Sub1;

	m_Alpha = 255;

	m_MainData.pos.x = static_cast<float>(Def_PosX); 
	m_MainData.pos.y = static_cast<float>(Def_PosY); 
	m_MainData.size.x = static_cast<float>(Size_DefX); 
	m_MainData.size.y = static_cast<float>(Size_DefY); 
	m_MainData.color.x = 0.0f; 
	m_MainData.color.y = 0.0f; 
	m_MainData.color.z = 0.0f; 
}
void UIDisplay::Release(void){
}
void UIDisplay::Update(void){
	if(m_Enable){
		switch(m_Flag){
		//開いて閉じる処理
		case Flag_OC:
			UpdateOC();
			break;
		//閉じて開く処理
		case Flag_CO:
			UpdateCO();
			break;
		case Flag_Close:
			UpdateClose();
			break;
		case Flag_Open:
			UpdateOpen();
			m_Alpha -= 100/Frame_SubO;
			if(m_Alpha <= 0){
				m_Alpha = 0;
			}
			break;
		}
	}
}
//サブアップデート
void UIDisplay::UpdateOpen(void){
	Open();
}
void UIDisplay::UpdateClose(void){
	Close();
}
void UIDisplay::UpdateOC(void){
	switch(m_Step){
	case Step_Open:
		if(Open()){
			m_Frame = 0;
			m_Step = Step_Close;
		}
		break;
	case Step_Close:
		if(Close()){
			m_Frame = 0;
			m_Step = Step_Wait;
		}
		break;
	case Step_Wait:
		m_Step = Step_Open;
		break;
	}
}
void UIDisplay::UpdateCO(void){
	switch(m_Step){
	case Step_Open:
		if(Open()){
			m_Frame = 0;
			m_Step = Step_Wait;
		}
		break;
	case Step_Close:
		if(Close()){
			m_Frame = 0;
			m_Step = Step_Open;
		}
		break;
	case Step_Wait:
		m_Step = Step_Close;
		break;
	}
}

//開く処理
bool UIDisplay::Open(void){
	switch(m_SubStep){
	case Sub1:
		m_MainData.size.x += Size_SubO1/Frame_SubO1;
		if(m_MainData.size.x >= Size_SubO1){
			m_MainData.size.x = Size_SubO1;
			m_SubStep++;
		}
		break;
	case Sub2:
		m_MainData.size.y += Size_SubO2/Frame_SubO2;
		if(m_MainData.size.y >= Size_SubO2){
			m_MainData.size.y = Size_SubO2;
			m_MainData.size.x = Size_SubO1;
			//m_Enable = false;
			m_SubStep = Sub1;
			Judge();
		}
		break;
	}

	CalcColor((260/Frame_SubO),Flag_ColorM);

	return false;
}
//閉じる処理
bool UIDisplay::Close(void){
	switch(m_SubStep){
	case Sub1:
		m_MainData.size.y += Size_SubC1/Frame_SubC1;
		if(m_MainData.size.y <= 0){
			m_MainData.size.y = 1;
			m_SubStep++;
		}
		break;
	case Sub2:
		m_MainData.size.x += Size_SubC2/Frame_SubC2;
		if(m_MainData.size.x <= 0){
			m_MainData.size.x = 1;
			m_SubStep++;
		}
		break;
	case Sub3:
		m_MainData.size.y += Size_SubC3/Frame_SubC3;
		if(m_MainData.size.y >= Size_SubC3){
			m_MainData.size.y = Size_SubC3;
			m_SubStep++;
		}
		break;
	case Sub4:
		m_MainData.size.y += Size_SubC4/Frame_SubC4;
		if(m_MainData.size.y <= 0){
			m_MainData.size.y = 0;
			m_SubStep++;
		}
		break;
	case Sub5:
		m_MainData.size.x += Size_SubC5/Frame_SubC5;
		if(m_MainData.size.x <= Size_SubC5){
			m_MainData.size.x = Size_SubC5;
			m_SubStep++;
		}
		break;
	case Sub6:
		m_MainData.size.x += Size_SubC6/Frame_SubC6;
		if(m_MainData.size.x <= 0){
			m_MainData.size.x = 0;
			m_MainData.size.y = 0;
			//m_Enable = false;
			m_SubStep = Sub1;
			Judge();
		}
		break;
	}

	CalcColor((260/Frame_SubC),Flag_ColorP);

	return false;
}

void UIDisplay::Draw(void){
	if(m_Enable){
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_Alpha);
		DrawBox(	static_cast<int>((m_MainData.pos.x-Size_DefX)),static_cast<int>((m_MainData.pos.y-Size_DefY)),
					static_cast<int>((m_MainData.pos.x+Size_DefX)),static_cast<int>((m_MainData.pos.y+Size_DefY)),
					GetColor(0,0,0), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);

		DrawBox(	static_cast<int>((m_MainData.pos.x-m_MainData.size.x)),static_cast<int>((m_MainData.pos.y-m_MainData.size.y)),
					static_cast<int>((m_MainData.pos.x+m_MainData.size.x)),static_cast<int>((m_MainData.pos.y+m_MainData.size.y)),
					GetColor((int)m_MainData.color.x, (int)m_MainData.color.y, (int)m_MainData.color.z), TRUE);
	}
}

void UIDisplay::Judge(void){
	m_SubStep = Sub1;
	switch(m_Flag){
	case Flag_OC:
		if(m_Step == Step_Wait){
			m_Step = Step_Open;
			m_MainData.pos.x = static_cast<float>(Def_PosX); 
			m_MainData.pos.y = static_cast<float>(Def_PosY); 
			m_MainData.size.x = 0.0f; 
			m_MainData.size.y = 0.0f;
			m_MainData.color.x = 0.0f; 
			m_MainData.color.y = 0.0f; 
			m_MainData.color.z = 0.0f; 
		}
		else if(m_Step == Step_Open)
			m_Step = Step_Close;
		else if(m_Step == Step_Close){
			m_Enable = false;
			m_Step = Step_Wait;
			Reset();
		}
		break;
	case Flag_CO:
		if(m_Step == Step_Wait){
			m_Step = Step_Close;
			m_MainData.pos.x = static_cast<float>(Def_PosX); 
			m_MainData.pos.y = static_cast<float>(Def_PosY); 
			m_MainData.size.x = static_cast<float>(Size_DefX); 
			m_MainData.size.y = static_cast<float>(Size_DefY); 
			m_MainData.color.x = 0.0f; 
			m_MainData.color.y = 0.0f; 
			m_MainData.color.z = 0.0f; 
		}
		else if(m_Step == Step_Close)
			m_Step = Step_Open;
		else if(m_Step == Step_Open){
			m_Enable = false;
			m_Step = Step_Wait;
			Reset();
		}
		break;
	case Flag_Close:
		if(m_Step == Step_Wait){
			m_Step = Step_Close;
			m_MainData.pos.x = static_cast<float>(Def_PosX); 
			m_MainData.pos.y = static_cast<float>(Def_PosY); 
			m_MainData.size.x = static_cast<float>(Size_DefX); 
			m_MainData.size.y = static_cast<float>(Size_DefY); 
			m_MainData.color.x = 0.0f; 
			m_MainData.color.y = 0.0f; 
			m_MainData.color.z = 0.0f; 
		}
		else if(m_Step == Step_Close){
			m_Enable = false;
			m_Step = Step_Wait;
			Reset();
		}
		break;
	case Flag_Open:
		if(m_Step == Step_Wait){
			m_Step = Step_Open;
			m_MainData.pos.x = static_cast<float>(Def_PosX); 
			m_MainData.pos.y = static_cast<float>(Def_PosY); 
			m_MainData.size.x = 0.0f; 
			m_MainData.size.y = 0.0f;
			m_MainData.color.x = 0.0f; 
			m_MainData.color.y = 0.0f; 
			m_MainData.color.z = 0.0f; 
		}
		else if(m_Step == Step_Open){
			m_Enable = false;
			m_Step = Step_Wait;
			Reset();
		}
		break;
	}

}

void UIDisplay::CalcColor(int colVal,int flag){
	switch(flag){
	case Flag_ColorP:
		m_MainData.color.x += (float)colVal;
		m_MainData.color.y += (float)colVal;
		m_MainData.color.z += (float)colVal;
		if(m_MainData.color.x >= 255.0f){
			m_MainData.color.x = 255.0f;
			m_MainData.color.y = 255.0f;
			m_MainData.color.z = 255.0f;
		}
		break;
	case Flag_ColorM:
		m_MainData.color.x -= (float)colVal;
		m_MainData.color.y -= (float)colVal;
		m_MainData.color.z -= (float)colVal;
		if(m_MainData.color.x <= 0.0f){
			m_MainData.color.x = 0.0f;
			m_MainData.color.y = 0.0f;
			m_MainData.color.z = 0.0f;
		}
		break;
	}
}

void UIDisplay::SetMainData(DXLibMath::Vector2 pos,DXLibMath::Vector2 size,VECTOR color,int flag){
	Reset();

	m_MainData.pos = pos;
	m_MainData.size = size;
	m_MainData.color = color;

	m_Alpha = 255;

	m_Flag = flag;
	m_Step = Step_Wait;
	Judge();
	m_Enable = true;
}

void UIDisplay::SetFlag(int flag){
	m_Alpha = 255;

	m_Flag = flag;
	m_Step = Step_Wait;
	Judge();
	m_Enable = true;
}