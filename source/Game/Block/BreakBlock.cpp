#include "BreakBlock.h"
#include <stdlib.h>
#include <time.h>

const int		BreakBlock :: cm_AddRangeX		= 60;
const int		BreakBlock :: cm_AddRangeY		= 70;
const int		BreakBlock :: cm_AddRangeBaseX	= 10;
const int		BreakBlock :: cm_AddRangeBaseY	= 20;
const int		BreakBlock :: cm_AlphaValue		= 10;
const int		BreakBlock :: cm_DefaultLife	= 15;			//初期ライフ
const int		BreakBlock :: cm_RangeSize		= 6;			//
const int		BreakBlock :: cm_BaseSize		= 1;			//
const float		BreakBlock :: cm_BaseVelocityX	= 1.0f;			//
const float		BreakBlock :: cm_BaseVelocityY	= 5.0f;			//
const float		BreakBlock :: cm_BaseAcceleX	= 1.0f;			//
const float		BreakBlock :: cm_BaseAcceleY	= 3.0f;			// *cm_Waight
const float		BreakBlock :: cm_Waight			= 0.5f;			//
BreakBlock::BreakBlock(void)
{
	Init();
}

BreakBlock::~BreakBlock(void)
{
	Release();
}

void BreakBlock :: Init(void){
	m_ParticleList.clear();

	srand((unsigned) time(NULL));
}

void BreakBlock :: Release(void){
	while(m_ParticleList.size() > 0)
	{
		ParticleData* dData = m_ParticleList.back();
		delete[] dData->particleData;
		delete dData;
		m_ParticleList.pop_back();
	}
}

void BreakBlock :: Update(void){
	int i=0;
	if(m_Enable){
		for(std::vector<ParticleData*>::iterator itr = m_ParticleList.begin(); itr != m_ParticleList.end();)
		{
			ParticleUpdate(i);
			if( m_ParticleList[i]->alive )
			{
				itr++;
				i++;
			}
			else
			{
				delete[] m_ParticleList[i]->particleData;
				delete m_ParticleList[i];
				itr = m_ParticleList.erase(itr);
			}
		}
	}

	//処理に入るかの判定
	EnableJudge();
}

void BreakBlock :: ParticleUpdate(int num){
	for(int i=0;i<m_ParticleList[num]->particleNum;i++){
		//位置の更新
		m_ParticleList[num]->particleData[i].cPosition.x += m_ParticleList[num]->particleData[i].velocity.x;
		m_ParticleList[num]->particleData[i].cPosition.y += m_ParticleList[num]->particleData[i].velocity.y;
		//速度の更新
		m_ParticleList[num]->particleData[i].velocity.x += m_ParticleList[num]->particleData[i].accele.x;
		m_ParticleList[num]->particleData[i].velocity.y += m_ParticleList[num]->particleData[i].accele.y;
		//アルファの更新
		m_ParticleList[num]->particleData[i].alpha -= cm_AlphaValue;
		if(m_ParticleList[num]->particleData[i].alpha < 0)
		m_ParticleList[num]->particleData[i].alpha = 0;
	}

	m_ParticleList[num]->life--;
	if(m_ParticleList[num]->life == 0){
		m_ParticleList[num]->life = 0;
		m_ParticleList[num]->alive = false;
	}
}

void BreakBlock :: Draw(void){
	if(m_Enable){
		for(int i=0;i<static_cast<int>(m_ParticleList.size());i++){
			for(int j=0;j<m_ParticleList[i]->particleNum;j++){
				if(m_ParticleList[i]->alive){
					SetDrawBlendMode(DX_BLENDMODE_ALPHA,m_ParticleList[i]->particleData[j].alpha);
					SetDrawBright(0,0,0);
					DrawModiGraph(	static_cast<int>((m_ParticleList[i]->cPosition.x+m_ParticleList[i]->particleData[j].cPosition.x+m_ParticleList[i]->particleData[j].point[0].x-1)),
									static_cast<int>((m_ParticleList[i]->cPosition.y+m_ParticleList[i]->particleData[j].cPosition.y+m_ParticleList[i]->particleData[j].point[0].y-1)),
									static_cast<int>((m_ParticleList[i]->cPosition.x+m_ParticleList[i]->particleData[j].cPosition.x+m_ParticleList[i]->particleData[j].point[2].x+1)),
									static_cast<int>((m_ParticleList[i]->cPosition.y+m_ParticleList[i]->particleData[j].cPosition.y+m_ParticleList[i]->particleData[j].point[2].y-1)),
									static_cast<int>((m_ParticleList[i]->cPosition.x+m_ParticleList[i]->particleData[j].cPosition.x+m_ParticleList[i]->particleData[j].point[3].x+1)),
									static_cast<int>((m_ParticleList[i]->cPosition.y+m_ParticleList[i]->particleData[j].cPosition.y+m_ParticleList[i]->particleData[j].point[3].y+1)),
									static_cast<int>((m_ParticleList[i]->cPosition.x+m_ParticleList[i]->particleData[j].cPosition.x+m_ParticleList[i]->particleData[j].point[1].x-1)),
									static_cast<int>((m_ParticleList[i]->cPosition.y+m_ParticleList[i]->particleData[j].cPosition.y+m_ParticleList[i]->particleData[j].point[1].y+1)),
									m_ParticleList[i]->handle,TRUE);
					SetDrawBright(255,255,255);
					DrawModiGraph(	static_cast<int>((m_ParticleList[i]->cPosition.x+m_ParticleList[i]->particleData[j].cPosition.x+m_ParticleList[i]->particleData[j].point[0].x)),
									static_cast<int>((m_ParticleList[i]->cPosition.y+m_ParticleList[i]->particleData[j].cPosition.y+m_ParticleList[i]->particleData[j].point[0].y)),
									static_cast<int>((m_ParticleList[i]->cPosition.x+m_ParticleList[i]->particleData[j].cPosition.x+m_ParticleList[i]->particleData[j].point[2].x)),
									static_cast<int>((m_ParticleList[i]->cPosition.y+m_ParticleList[i]->particleData[j].cPosition.y+m_ParticleList[i]->particleData[j].point[2].y)),
									static_cast<int>((m_ParticleList[i]->cPosition.x+m_ParticleList[i]->particleData[j].cPosition.x+m_ParticleList[i]->particleData[j].point[3].x)),
									static_cast<int>((m_ParticleList[i]->cPosition.y+m_ParticleList[i]->particleData[j].cPosition.y+m_ParticleList[i]->particleData[j].point[3].y)),
									static_cast<int>((m_ParticleList[i]->cPosition.x+m_ParticleList[i]->particleData[j].cPosition.x+m_ParticleList[i]->particleData[j].point[1].x)),
									static_cast<int>((m_ParticleList[i]->cPosition.y+m_ParticleList[i]->particleData[j].cPosition.y+m_ParticleList[i]->particleData[j].point[1].y)),
									m_ParticleList[i]->handle,TRUE);
					SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
				}
			}
		}
	}
}

void BreakBlock :: Add(DXLibMath::Vector2 cPos,int particleNum,int handle){
	ParticleData* addData;
	DXLibMath::Vector2 l_work;
	float l_length;

	addData = new ParticleData;
	addData->particleData = new ParticleSimpleData[particleNum];

	addData->alive = true;
	addData->cPosition = cPos;
	addData->cPosition.x += 20;
	addData->cPosition.y += 20;
	addData->handle = handle;
	addData->life = cm_DefaultLife;
	addData->particleNum = particleNum;

	//左に飛ぶやつ
	for(int i=0;i<particleNum/2;i++){
		l_work.x = -( rand() % cm_AddRangeX+1+cm_AddRangeBaseX );
		l_work.y = -( rand() % cm_AddRangeY+1+cm_AddRangeBaseY );
		l_length = (float)sqrt((l_work.x*l_work.x)+(l_work.y*l_work.y));

		l_work.x = l_work.x / l_length;
		l_work.y = l_work.y / l_length;

		addData->particleData[i].cPosition.x = l_work.x * (rand() % cm_AddRangeX+1);
		addData->particleData[i].cPosition.y = l_work.y * (rand() % cm_AddRangeY+1);

		if(cm_BaseVelocityX > 0.0f){
			addData->particleData[i].velocity.x = -( (rand() % static_cast<int>( cm_BaseVelocityX+1 ) +2 ) );
		}
		if(cm_BaseVelocityY > 0.0f){
			addData->particleData[i].velocity.y = -( (rand() % static_cast<int>( cm_BaseVelocityY+1 ) +3 ) );
		}
		if(cm_BaseAcceleX >= 1.0f){
		//if(cm_BaseAcceleX > 1.0f){
			addData->particleData[i].accele.x = (float)(-(rand() % static_cast<int>( cm_BaseAcceleX+1 ) * cm_Waight ) );
			//addData->particleData[i].accele.x = (float)(-(rand() % static_cast<int>(cm_BaseAcceleX+1)) ;
		}
		if(cm_BaseAcceleY >= 1.0f){
		//if(cm_BaseAcceleY > 0.0f){
			addData->particleData[i].accele.y = (float)( (rand() % (static_cast<int>( cm_BaseAcceleY)+2 ) * cm_Waight ) );
			//addData->particleData[i].accele.y = (float)( (rand() % static_cast<int>(cm_BaseAcceleY+1)) ;
		}
		addData->particleData[i].alpha = 255;

		//四点の計算---------------------------------------------
		//左上
		addData->particleData[i].point[0].x = -( rand() % cm_RangeSize + 1 + cm_BaseSize);
		addData->particleData[i].point[0].y = -( rand() % cm_RangeSize + 1 + cm_BaseSize);
		//左下
		addData->particleData[i].point[1].x = -( rand() % cm_RangeSize + 1 + cm_BaseSize);
		addData->particleData[i].point[1].y =    rand() % cm_RangeSize + 1 + cm_BaseSize;
		//右上
		addData->particleData[i].point[2].x =    rand() % cm_RangeSize + 1 + cm_BaseSize;
		addData->particleData[i].point[2].y = -( rand() % cm_RangeSize + 1 + cm_BaseSize);
		//右下
		addData->particleData[i].point[3].x = rand() % cm_RangeSize + 1 + cm_BaseSize;
		addData->particleData[i].point[3].y = rand() % cm_RangeSize + 1 + cm_BaseSize;
	}
	//右に飛ぶやつ
	for(int i=particleNum/2;i<particleNum;i++){
		l_work.x =  ( rand() % cm_AddRangeX+1+cm_AddRangeBaseX );
		l_work.y = -( rand() % cm_AddRangeY+1+cm_AddRangeBaseY );
		l_length = (float)sqrt((l_work.x*l_work.x)+(l_work.y*l_work.y));

		l_work.x = l_work.x / l_length;
		l_work.y = l_work.y / l_length;

		addData->particleData[i].cPosition.x = l_work.x * (rand() % cm_AddRangeX+1);
		addData->particleData[i].cPosition.y = l_work.y * (rand() % cm_AddRangeY+1);

		if(cm_BaseVelocityX > 0.0f){
			addData->particleData[i].velocity.x =  ( (rand() % static_cast<int>( cm_BaseVelocityX+1 ) +2 ) );
		}
		if(cm_BaseVelocityX > 0.0f){
			addData->particleData[i].velocity.y = -( (rand() % static_cast<int>( cm_BaseVelocityY+1 ) +3 ) );
		}
		if(cm_BaseAcceleX >= 1.0f){
		//if(cm_BaseAcceleX > 0.0f){
			addData->particleData[i].accele.x = (float)((rand() % static_cast<int>( cm_BaseAcceleX+1 ) *cm_Waight ) );
			//addData->particleData[i].accele.x = ( rand() % static_cast<int>(cm_BaseAcceleX+1 );
		}
		if(cm_BaseAcceleY >= 1.0f){
		//if(cm_BaseAcceleY > 0.0f){
			addData->particleData[i].accele.y =  (float)((rand() % static_cast<int>( cm_BaseAcceleY+2 )*cm_Waight ) );
			//addData->particleData[i].accele.y = ( rand() % static_cast<int>(cm_BaseAcceleY+1 );
		}
		addData->particleData[i].alpha = 255;

		//四点の計算---------------------------------------------
		//左上
		addData->particleData[i].point[0].x = -( rand() % cm_RangeSize + 1 + cm_BaseSize);
		addData->particleData[i].point[0].y = -( rand() % cm_RangeSize + 1 + cm_BaseSize);
		//左下
		addData->particleData[i].point[1].x = -( rand() % cm_RangeSize + 1 + cm_BaseSize);
		addData->particleData[i].point[1].y =    rand() % cm_RangeSize + 1 + cm_BaseSize;
		//右上
		addData->particleData[i].point[2].x =    rand() % cm_RangeSize + 1 + cm_BaseSize;
		addData->particleData[i].point[2].y = -( rand() % cm_RangeSize + 1 + cm_BaseSize);
		//右下
		addData->particleData[i].point[3].x = rand() % cm_RangeSize + 1 + cm_BaseSize;
		addData->particleData[i].point[3].y = rand() % cm_RangeSize + 1 + cm_BaseSize;
	}

	m_ParticleList.push_back(addData);

	//処理に入るかの判定
	EnableJudge();
}

void BreakBlock :: EnableJudge(void){
	if(m_ParticleList.empty()){
		m_Enable = false;
	}
	else{
		m_Enable = true;
	}
}