#include "GameOver.h"
#include "../System/DataManager.h"
#include "../System/DxLibMath.h"
#include "../System/GameInput.h"

GameOver::GameOver(void)
{
}
void GameOver::Init(void)
{
	DataManager &data = DataManager::GetInstance();

	m_Frame = 0;
	m_End = false;
	m_ArmPosition.x = 0.75f * 0.45f - 0.07f;
	m_ArmPosition.y = -0.5f;
	m_ArmState = State_Fall;
	m_AnimeArm = 0;
	m_Bright = 255;
	for(int i=0; i<4; i++){
		m_WordPosition[i].x = (0.18f*i) + 0.1f;
		m_WordPosition[i].y = -0.2f;
	}
	m_WordRot[0] = 0.2f;
	m_WordRot[1] = -0.05f;
	m_WordRot[2] = 0.02f;
	m_WordRot[3] = -0.1f;

	// アーム画像のハンドル格納
	const int arm_handle[2] =
	{	data.Get(DataManager::Moguru_Salvage1),
		data.Get(DataManager::Moguru_Salvage2) };

	// ハンドルの代入
	for(int i=0; i<2; i++){
		m_Arm_Handle[i] = arm_handle[i];
	}

	// 文字画像のハンドル格納
	const int word_handle[4] =
	{	data.Get(DataManager::Play_Graph_Dead1),
		data.Get(DataManager::Play_Graph_Dead2),
		data.Get(DataManager::Play_Graph_Dead3),
		data.Get(DataManager::Play_Graph_Dead4)
	};

	// ハンドルの代入
	for(int i=0; i<4; i++){
		m_Word_Handle[i] = word_handle[i];
	}
}
GameOver::~GameOver(void)
{
	SetDrawBright(255, 255, 255);
}

void GameOver::Update(void)
{
	GameInput &input = GameInput::GetInstance();
	DataManager &data = DataManager::GetInstance();

	int animesp = 10;
	float speed = 0.004f;
	float hight = 0.43f;	// 文字落下を止める高さ
	// アーム
	switch (m_ArmState){
	case State_Fall:// アームが下りていく
		m_ArmPosition.y += speed;
		if(m_ArmPosition.y >= (data.m_MogllStatus.position.y - 0.37f)){
			m_ArmPosition.y = (data.m_MogllStatus.position.y - 0.37f);
			m_ArmState = State_Anime;
			m_Frame = 0;
		}
		break;
	case State_Anime:// アームのアニメーション
			 if(m_Frame < animesp)		m_AnimeArm = 0;
		else if(m_Frame < animesp*2)	m_AnimeArm = 1;
		else{
										m_AnimeArm = 1;
										m_ArmState = State_Up;
		}
		m_Frame++;
		break;
	case State_Up:// モグルが上に持ち上げられていく
		m_ArmPosition.y					-= speed;
		data.m_MogllStatus.position.y	-= speed;
		if( data.m_MogllStatus.position.y < -0.1f )	m_End = true;
		break;
	default:
		break;
	}

	// 文字
		 if(m_WordPosition[0].y != hight){
		m_WordPosition[0].y += 0.02f;
		if(m_WordPosition[0].y >= hight) m_WordPosition[0].y = hight;
	}
	else if(m_WordPosition[1].y != hight){
		m_WordPosition[1].y += 0.02f;
		if(m_WordPosition[1].y >= hight) m_WordPosition[1].y = hight;
	}
	else if(m_WordPosition[2].y != hight){
		m_WordPosition[2].y += 0.02f;
		if(m_WordPosition[2].y >= hight) m_WordPosition[2].y = hight;
	}
	else if(m_WordPosition[3].y != hight){
		m_WordPosition[3].y += 0.02f;
		if(m_WordPosition[3].y >= hight) m_WordPosition[3].y = hight;
	}

	// 画面を暗くしていく
	m_Bright -= 1.0f;
}

void GameOver::Draw(void)
{
	DataManager &data = DataManager::GetInstance();
	SetDrawBright((int)m_Bright, (int)m_Bright, (int)m_Bright);
	DXLibMath::DrawExtendGraphResize( m_ArmPosition.x, m_ArmPosition.y, 0.2f, 0.4f, m_Arm_Handle[m_AnimeArm], TRUE);			// アーム
	for(int i=0; i<4; i++){
		DXLibMath::DrawRotaGraphResize(m_WordPosition[i].x, m_WordPosition[i].y, 1.0f, m_WordRot[i], m_Word_Handle[i], TRUE);	// 文字
	}
}

bool GameOver::IsEnd(void)
{
	return m_End;
}