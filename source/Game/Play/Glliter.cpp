//========================================================================
//	@file	FunctionName.cpp
//	@note	AnyFunction
//========================================================================
//------------------------------------------------------------------------
//	IncludeHeader
//------------------------------------------------------------------------
#include "Glliter.h"
#include<stdlib.h>
#include<time.h>

//------------------------------------------------------------------------
//	Constructor
//------------------------------------------------------------------------
Glliter :: Glliter(void)
{
	Init();
}
Glliter :: ~Glliter(void)
{
}

//------------------------------------------------------------------------
//	@fn		FunctionName
//	@brief	Description
//------------------------------------------------------------------------

//------------------------------------------------------------------------
//	@fn		FunctionName
//	@brief	Description
//------------------------------------------------------------------------
void Glliter :: Init(void){
	m_ReferencePoint.x = 0.0f;
	m_ReferencePoint.y = 0.0f;

	for(int i=0;i<4;i++){
		m_GlliterList[i].pos.x = 0.0f;
		m_GlliterList[i].pos.y = 0.0f;
		m_GlliterList[i].step = 0;
		m_GlliterList[i].expantion = 1.0f;
		m_GlliterList[i].alpha = 0;
		m_GlliterList[i].alive = false;
	}

	srand((unsigned)time(NULL));
}
//------------------------------------------------------------------------
//	@fn		FunctionName
//	@brief	Description
//------------------------------------------------------------------------
void Glliter :: Updata(DXLibMath::Vector2* rp){
	Add(rp);

	for(int i=0;i<4;i++){
		if(m_GlliterList[i].alive){
			switch(m_GlliterList[i].step){
			case 0:
				m_GlliterList[i].alpha += 5;
				if(m_GlliterList[i].alpha > 255){
					m_GlliterList[i].alpha = 255;
					m_GlliterList[i].step = 1;
				}
				break;
			case 1:
				m_GlliterList[i].alpha -= 5;
				if(m_GlliterList[i].alpha < 0){
					m_GlliterList[i].alpha = 0;
					m_GlliterList[i].alive = false;
				}
				break;
			}
		}
	}
}
//------------------------------------------------------------------------
//	@fn		FunctionName
//	@brief	Description
//------------------------------------------------------------------------
void Glliter :: Draw(DataManager *data){
	for(int i=0;i<4;i++){
		if(m_GlliterList[i].alive){
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_GlliterList[i].alpha);			//透過率のセット
			DrawRotaGraph(	static_cast<int>(m_GlliterList[i].pos.x),static_cast<int>(m_GlliterList[i].pos.y),m_GlliterList[i].expantion,0.0,
							data->Get(DataManager::Play_Treasure_Shine),TRUE);
		}
	}
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);			//透過率のセット
}
//------------------------------------------------------------------------
//	@fn		FunctionName
//	@brief	Description
//------------------------------------------------------------------------
void Glliter :: Add(DXLibMath::Vector2* rp){
	for(int i=0;i<4;i++){
		if(m_GlliterList[i].alive == false){
			m_GlliterList[i].pos.x = (rand() % 100 + 1 - 50) + rp->x;
			m_GlliterList[i].pos.y = (rand() % 100 + 1 - 50) + rp->y;
			m_GlliterList[i].expantion = static_cast<float>((rand() % 8 + 1))/10;
			m_GlliterList[i].alpha = rand() % 200 + 1;
			m_GlliterList[i].step = 0;
			m_GlliterList[i].alive = true;
		}
	}
}

void Glliter::Clear(void){
	for(int i=0;i<4;i++){
		m_GlliterList[i].pos.x = 0.0f;
		m_GlliterList[i].pos.y = 0.0f;
		m_GlliterList[i].step = 0;
		m_GlliterList[i].expantion = 1.0f;
		m_GlliterList[i].alpha = 0;
		m_GlliterList[i].alive = false;
	}
}

//========================================================================
//	End of file
//========================================================================
