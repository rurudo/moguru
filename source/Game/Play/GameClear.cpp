#include "GameClear.h"
#include "../System/DataManager.h"
#include "../System/DxLibMath.h"
#include "../System/GameInput.h"

GameClear::GameClear(void)
{
}

void GameClear::Init(void)
{
	DataManager &data = DataManager::GetInstance();
	// 値の初期化
	m_Frame = 0;
	m_Bright = 0.0f;
	m_ClearState = State_Move;
	m_End = false;
	m_isAct = false;

	// 文字の初期位置
	for(int i=0; i<4; i++){
		m_WordPosition[i].x = 0.15f + (i*0.15f);
		m_WordPosition[i].y = 0.33f;
	}
	for(int i=4; i<9; i++){
		m_WordPosition[i].x = 0.1f + ((i-4)*0.15f);
		m_WordPosition[i].y = 0.53f;
	}
	// 文字の定位置保存
	for(int i=0; i<9; i++){
		m_WordPositionData[i] = m_WordPosition[i];
	}

	// 文字画像のハンドル格納
	const int word_handle[9] =
	{	data.Get(DataManager::Play_Graph_Clear1),
		data.Get(DataManager::Play_Graph_Clear2),
		data.Get(DataManager::Play_Graph_Clear3),
		data.Get(DataManager::Play_Graph_Clear4),
		data.Get(DataManager::Play_Graph_Clear5),
		data.Get(DataManager::Play_Graph_Clear6),
		data.Get(DataManager::Play_Graph_Clear7),
		data.Get(DataManager::Play_Graph_Clear8),
		data.Get(DataManager::Play_Graph_Clear9),
	};

	// ハンドルの代入
	for(int i=0; i<9; i++){
		m_Word_Handle[i] = word_handle[i];
	}

	// 進行方向ベクトルを計算(各位置から中心に向かう)
	for(int i=0; i<9; i++){
		m_WordDirection[i].x = 0.5f - m_WordPosition[i].x;
		m_WordDirection[i].y = 0.5f - m_WordPosition[i].y;
		// 正規化
		DXLibMath::Normalize(&m_WordDirection[i], m_WordDirection[i]);
	}

	// 移動前の位置を指定
	for(int i=0; i<9; i++){
		for(int j=0; j<50; j++){
			m_WordPosition[i].x -= m_WordDirection[i].x/50;
			m_WordPosition[i].y -= m_WordDirection[i].y/50;
		}
	}
}

GameClear::~GameClear(void)
{
	SetDrawBright(255, 255, 255);
}

void GameClear::Update(void)
{
	GameInput &input = GameInput::GetInstance();

	switch(m_ClearState){
	case State_Move:	// 文字の移動
		m_isAct = true;

		if(m_Frame < 50){
			for(int i=0; i<9; i++){
					m_WordPosition[i].x += m_WordDirection[i].x/50;
					m_WordPosition[i].y += m_WordDirection[i].y/50;
			}
			m_Frame++;
		}
		else	m_ClearState = State_bright;
		break;
	case State_bright:	// 画面の輝度
		m_Bright += 1.5f;
		if(m_Bright >= 255.0f)	m_End = true;
		break;
	}

	// ショ―トカット
	if(input.GetMouse(GameInput::MouseLeftTrg))	m_End = true;
}

void GameClear::Draw(void)
{
	DataManager &data = DataManager::GetInstance();

	for(int i=0; i<9; i++){
		DXLibMath::DrawRotaGraphResize(m_WordPosition[i].x, m_WordPosition[i].y, 1.0f, 0.0f, m_Word_Handle[i], TRUE);	// 文字
	}

	// 輝度の演出
	if(m_ClearState == State_bright){
		// 四角
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)m_Bright);
		DXLibMath::DrawBoxResize(0.0f, 0.0f, 1.0f, 1.0f, GetColor(255, 255, 255), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}

bool GameClear::IsEnd(void)
{
	return m_End;
}