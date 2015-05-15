#include "Cracker.h"
#include<stdlib.h>
#include<time.h>



Cracker::Cracker(void)
{
	Init();
}


Cracker::~Cracker(void)
{
	Release();
}

void Cracker :: Init(void){
	m_Position.x = 1000.0f;
	m_Position.y = 1000.0f;
	m_Offset.x = 0.0f;
	m_Offset.y = 0.0f;
	m_Angle = 0.0f;
	m_Direction = false;

	m_Enable = false;

	m_Frame = 0;
	m_Alpha = 0;

	m_Step = STEP_In;

	srand((unsigned)time(NULL));

	//ハンドルリストを作成
	m_Data = &DataManager::GetInstance();
}
void Cracker :: Release(void){
}
void Cracker :: SetContent(void){
	m_Content.cracker = ((rand() % CrackerNum*3)%CrackerNum)*2;
	//
	for(int i=0;i<4;i++){
		m_Content.tape[i].type = (rand() % 2);
		switch(m_Content.tape[i].type){
		case Type_Roll:
			m_Content.tapeNum[i] = (rand() % TapeRollNum);
			break;
		case Type_St:
			m_Content.tapeNum[i] = (rand() % TapeStNum);
			break;
		}
		m_Content.tape[i].alpha = 0;
		m_Content.tape[i].angle = -(float)TapeAngle*i;
		m_Content.tape[i].Distance.x = -(float)TapeDisX*(i+1) + CrackerMarginX;
		m_Content.tape[i].Distance.y = -(float)TapeDisY*(3-i) + CrackerMarginY;
		if(m_Direction){
			m_Content.tape[i].angle = -m_Content.tape[i].angle;
			m_Content.tape[i].Distance.x = -m_Content.tape[i].Distance.x;
		}
	}
	//紙吹雪の設定
	for(int i=0;i<6;i++){
		m_Content.paper[i].type = (rand() % TickerNum + 1);
		int l_dir = (rand() % 2);
		switch(l_dir){
		case 0:
			m_Content.paperDir[i] = false;
			break;
		case 1:
			m_Content.paperDir[i] = true;
			break;
		}
		m_Content.paper[i].alpha =0;
		m_Content.paper[i].angle =0;
		m_Content.paper[i].Distance.x = static_cast<float>((rand() % TickerDisRangeX + 1 - TickerDisRangeX/4) + TickerDisBaseX);
		m_Content.paper[i].Distance.y = static_cast<float>((rand() % TickerDisRangeY + 1 - TickerDisRangeY/2) + TickerDisBaseY);
		if(m_Direction){
			m_Content.paper[i].angle = -m_Content.paper[i].angle;
			m_Content.paper[i].Distance.x = -m_Content.paper[i].Distance.x;
		}
	}
}
void Cracker :: SetPosition(DXLibMath::Vector2 pos,int dir){
	m_Position = pos;
	switch(dir){
	case 0:
		m_Direction = false;
		break;
	case 1:
		m_Direction = true;
		break;
	}

	m_Enable = true;
	SetContent();
}

bool Cracker :: Update(void){
	if(m_Enable){
		switch(m_Step){
		case STEP_In:
			UpdateIn();
			break;
		case STEP_Wait:
			if(m_Frame > TIME_Wait){
				m_Frame = 0;
				m_Step++;
			}
			m_Frame++;
			break;
		case STEP_Explosion:
			UpdateExplosion();
			break;
		case STEP_Stay:
			UpdateStay();
			return true;
			break;
		}
	}
	return false;
}

void Cracker :: UpdateIn(void){
	m_Alpha += 260 / TIME_In;
	if(m_Alpha > 255)
		m_Alpha = 255;

	if(m_Frame > TIME_In){
		m_Step++;
		m_Frame = 0;
		m_Content.cracker++;
		PlaySoundMem( m_Data->Get( DataManager::SoundSE54 ), DX_PLAYTYPE_BACK);
		PlaySoundMem( m_Data->Get( DataManager::SoundSE54 ), DX_PLAYTYPE_BACK);
		PlaySoundMem( m_Data->Get( DataManager::SoundSE54 ), DX_PLAYTYPE_BACK);
	}
	m_Frame++;
}
void Cracker :: UpdateExplosion(void){
	for(int i=0;i<4;i++){
		m_Content.tape[i].alpha += 260 / TIME_Explosion/10;
		if(m_Content.tape[i].alpha > 255)
			m_Content.tape[i].alpha = 255;
	}
	for(int i=0;i<6;i++){
		m_Content.paper[i].alpha += 260 / TIME_Explosion/10;
		if(m_Content.paper[i].alpha > 255)
			m_Content.paper[i].alpha = 255;
	}

	if(m_Frame == 1){
		PlaySoundMem( m_Data->Get( DataManager::SoundSE54 ), DX_PLAYTYPE_BACK);
		PlaySoundMem( m_Data->Get( DataManager::SoundSE54 ), DX_PLAYTYPE_BACK);
	}
	if(m_Frame > TIME_Explosion){
		m_Step++;
		m_Frame = 0;
	}
	m_Frame++;
}
void Cracker :: UpdateStay(void){
	if(m_Frame == TIME_In/2){
		m_Angle = 0;
		m_Offset.x = 0.0f;
		m_Offset.y = 0.0f;
	}
	if(m_Frame > TIME_In){
		m_Frame = 0;
		m_Angle = 30;
		m_Offset.x = 30.0f;
		m_Offset.y = -30.0f;
		if(m_Direction){
			m_Angle = -m_Angle;
			m_Offset.x = -m_Offset.x;
		}
	}
	m_Frame++;
}

void Cracker :: Draw(void){
	if(m_Enable){
		DrawIn();
		DrawExplosion();
	}
}

void Cracker :: DrawIn(void){
	if(m_Step >= STEP_In){
		//クラッカー
		DrawRotaGraph(static_cast<int>(m_Position.x),static_cast<int>(m_Position.y),1.2f,GetRadian(m_Angle),
			m_Data->GetGraphicGroupData((DataManager::GG_Get_CrackerBD1 + m_Content.cracker)),TRUE,m_Direction);
	}
}
void Cracker :: DrawExplosion(void){
	if(m_Step >= STEP_Explosion){
		//紙吹雪
		for(int i=0;i<6;i++){
			DrawRotaGraph(static_cast<int>(m_Position.x + m_Content.paper[i].Distance.x + m_Offset.x),static_cast<int>(m_Position.y + m_Content.paper[i].Distance.y + m_Offset.y),
				0.3f,GetRadian(m_Angle+m_Content.paper[i].angle),
				m_Data->GetGraphicGroupData((DataManager::GG_Get_PaperB1 + m_Content.paper[i].type)),TRUE,GetPaperDirection(m_Content.paperDir[i]));
		}
		//テープ
		for(int i=0;i<4;i++){
			DrawRotaGraph(static_cast<int>(m_Position.x + m_Content.tape[i].Distance.x + m_Offset.x),static_cast<int>(m_Position.y + m_Content.tape[i].Distance.y + m_Offset.y),
				0.6f,GetRadian(m_Angle+m_Content.tape[i].angle),
				m_Data->GetGraphicGroupData((GetTapeTypeHandle(m_Content.tape[i].type) + m_Content.tapeNum[i])),TRUE,m_Direction);
		}
	}
}
void Cracker :: Disable(void){
	m_Enable = false;
}

float Cracker :: GetRadian(float degree){
	return degree  * (float)3.141592653589793 / 180.0f;
}

int Cracker :: GetTapeTypeHandle(int type){
	switch(type){
	case Type_Roll:
		return DataManager::GG_Get_TapeRoll1;
		break;
	case Type_St:
		return DataManager::GG_Get_TapeSt1;
		break;
	default:
		return 0;
		break;
	}
}
bool Cracker :: GetPaperDirection(bool paperDir){
	if(!m_Direction){
		if(paperDir){
			return false;
		}
		else
			return true;
	}
	return false;
}


