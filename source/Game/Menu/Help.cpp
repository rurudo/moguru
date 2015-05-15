#include "Help.h"
#include "../System/DataManager.h"
#include "../System/DxLibMath.h"
#include "../System/GameInput.h"

const char g_Index[8][30] =
{
	"モグル",			
	"ユニット",			
	"宝箱",				
	"メニュー：装備",	
	"メニュー：合成分解",
	"ヒント",			
	"ブロック一覧",	
	"状態異常一覧",		
};

Help::Help(void)
{
}

void Help::Init(void)
{
	DataManager &data = DataManager::GetInstance();
	// 値の初期化
	m_State = INDEX;
	m_Page = 0;
	m_Index = -1;
	m_Frame = 0;
	m_ScalFlg = false;
	m_M_Scal = 0.55f;
	m_Exist = false;
	m_OffFrame = false;
	m_Help_Button_Scale = 1.0f;
	// 遊び方文字
	const DRAW_DATA w_howto[NUM_PAGE] = {  {0.5f, 0.5f, 1.0f, 0.0f, data.Get(DataManager::Description1)},
											{0.5f, 0.5f, 1.0f, 0.0f, data.Get(DataManager::Description2_1)},
											{0.5f, 0.5f, 1.0f, 0.0f, data.Get(DataManager::Description2_2)},
											{0.5f, 0.5f, 1.0f, 0.0f, data.Get(DataManager::Description3)},
											{0.5f, 0.5f, 1.0f, 0.0f, data.Get(DataManager::Description4_1)},
											{0.5f, 0.5f, 1.0f, 0.0f, data.Get(DataManager::Description4_2)},
											{0.5f, 0.5f, 1.0f, 0.0f, data.Get(DataManager::Description5_1)},
											{0.5f, 0.5f, 1.0f, 0.0f, data.Get(DataManager::Description5_2)},
											{0.5f, 0.5f, 1.0f, 0.0f, data.Get(DataManager::Description6)},
											{0.5f, 0.5f, 1.0f, 0.0f, data.Get(DataManager::Description7_1)},
											{0.5f, 0.5f, 1.0f, 0.0f, data.Get(DataManager::Description7_2)},
											{0.5f, 0.5f, 1.0f, 0.0f, data.Get(DataManager::Description8)},
									};
	for(int i=0; i<NUM_PAGE; i++)	
		m_WordHowto[i] = w_howto[i];
	//拡縮率初期化
	for(int i=0; i<NUM_INDEX; i++)
		m_I_Scale[i] = 1.0f;
	//項目ごとのページ数設定
	m_IndexPage[ 0] = 1;
	m_IndexPage[ 1] = 2;
	m_IndexPage[ 2] = 1;
	m_IndexPage[ 3] = 2;
	m_IndexPage[ 4] = 2;
	m_IndexPage[ 5] = 1;
	m_IndexPage[ 6] = 2;
	m_IndexPage[ 7] = 1;
}

Help::~Help(void)
{
	SetDrawBright(255, 255, 255);
}

bool Help::Update(void)
{
	GameInput &input = GameInput::GetInstance();
	float x = input.GetXf();
	float y = input.GetYf();

	int nextPage = -1;
	if(m_Exist)
	{
		switch(m_State)
		{
		case INDEX:
			nextPage = UpdateIndex();
			if(nextPage >= 0)
			{
				m_OldPage = -1;		//前ページ保存
				m_Page = nextPage;	//次ページ格納
				m_State = REFERENCE;//ステート切替
				m_PageAlpha = 0;	//α初期化
			}
			break;
		case REFERENCE:
			m_State = UpdateReference();
			break;
		}
		//閉じるボタン処理
		if(Close())
		{
			m_Exist = false;
			m_OffFrame = true;
		}
	}

	//ボタンの拡縮
	if(x >= 0.9425f && y <= 0.07f)
		m_Help_Button_Scale += (1.3f - m_Help_Button_Scale) * 0.3f;
	else
		m_Help_Button_Scale += (1.0f - m_Help_Button_Scale) * 0.3f;

	return m_Exist;
}
//目次処理
int Help :: UpdateIndex(void)
{
	int	page = 0;
	GameInput &input = GameInput::GetInstance();
	float x = input.GetXf();
	float y = input.GetYf();

	//位置判定
	if(x > 0.3125f && x < 0.6875f)
	{
		//Y判定
		for(int i=0; i<NUM_INDEX; i++)
		{
			if(y > (0.383f + 0.06667f*(float)i) && y < (0.383f + 0.06667f*(float)(i+1)))
				m_Index = i;
			else
			{
				if(i == 0)
					m_Index = -1;
			}
		}
	}
	else
		m_Index = -1;

	//項目の拡縮
	for(int i=0; i< NUM_INDEX; i++)
	{
		if(i == m_Index)
			m_I_Scale[i] += (1.3f-m_I_Scale[i]) * 0.2f;
		else
			m_I_Scale[i] += (1.0f-m_I_Scale[i]) * 0.2f;
	}

	//クリックで進む
	if(	input.GetMouse(GameInput::MouseLeftTrg) && 
		m_Index >= 0 && m_Index < NUM_PAGE)
	{
		//そこまでのページを飛ばす
		for(int i=0; i<m_Index; i++)
			page += m_IndexPage[i];
		return page;
	}
	return -1;
}
//リファレンスページの更新
Help::STATE Help::UpdateReference(void)
{
	int nextPage = m_Page;

	//α値更新
	m_PageAlpha += 10;
	if(m_PageAlpha > 255)
		m_PageAlpha = 255;

	//押されたボタンごとの処理
	switch(UpdatePages())
	{
	case STAY:
		break;
	case PREV:
			nextPage--;
		break;
	case NEXT:
			nextPage++;
		break;
	case BACK:
		m_Index = -1;
		return INDEX;
		break;
	}

	//ページが変われば更新
	if(nextPage != m_Page)
	{
		m_OldPage = m_Page;	//前ページ保存
		m_Page = nextPage;	//次ページ格納
		m_PageAlpha = 0;	//α初期化
	}

	return REFERENCE;
}
//リファレンスボタン処理
Help::CONTROL Help :: UpdatePages(void)
{
	GameInput &input = GameInput::GetInstance();
	float x = input.GetXf();
	float y = input.GetYf();
	Help::CONTROL ret = STAY;

	//位置判定
	//前ページボタン
	if( m_Page > 0 &&
		x > 0.37f && x < 0.43 &&
		y > 0.91f && y < 0.95)
		ret = PREV;

	//次ページボタン
	if( m_Page < NUM_PAGE-1 &&
		x > 0.57f && x < 0.63 &&
		y > 0.91f && y < 0.95)
		ret = NEXT;

	//戻るボタン
	if( x > 0.45f && x < 0.55 &&
		y > 0.89f && y < 0.97)
		ret = BACK;

	////拡縮
	//if(!m_ScalFlg){
	//	m_M_Scal += 0.01f;
	//	if(m_M_Scal >= 0.7f)	m_ScalFlg = true;
	//}
	//else{
	//	m_M_Scal -= 0.01f;
	//	if(m_M_Scal <= 0.4f)	m_ScalFlg = false;
	//}
	//クリックで進む
	if(input.GetMouse(GameInput::MouseLeftTrg))
		return ret;

	return STAY;
}

//描画処理
void Help::Draw(void)
{
	DataManager &data = DataManager::GetInstance();
	GameInput &input = GameInput::GetInstance();

	if(m_Exist)
	{
		//BG
		DXLibMath::DrawRotaGraphResize(	0.5f, 0.5f, 1.0f, 0.0f, 
										DataManager::GetInstance().Get(DataManager::Help_BG), TRUE);
		switch(m_State)
		{
		case INDEX:
			DrawIndex();
			break;
		case REFERENCE:
			DrawReference();
			break;
		}
		//閉じるボタン
		DXLibMath::DrawRotaGraphResize(0.97f, 0.035f, m_Help_Button_Scale, 0.0f, data.Get(DataManager::Help_Button_Close), TRUE);
	}
	else
		DXLibMath::DrawRotaGraphResize(0.97f, 0.035f, m_Help_Button_Scale, 0.0f, data.Get(DataManager::Play_UI_Play_HelpButton), TRUE);
}
//目次描画
void Help::DrawIndex(void)
{
	float extend = 1.0f;
	//ラベル
	DXLibMath::DrawRotaGraphResize(	0.5f, 0.17f, 1.0f, 0.0f, 
									DataManager::GetInstance().Get(DataManager::Help_Label), TRUE);
	for(int i=0; i<NUM_INDEX; i++)
	{
		DXLibMath::DrawRotaGraphResize(	0.5f, 0.408f + ((float)i * 0.06667f), m_I_Scale[i], 0.0f, 
									DataManager::GetInstance().Get(DataManager::Help_Index), TRUE);
	}
	// 文字表示
	int color = GetColor(255, 255, 255);
	for(int i=0; i<NUM_INDEX; i++)
	{
		color = ChangeColor(i);
		//m_Font.DrawFontString(FontManager::FontSet_AZUKI_25 , 280, 230+i*40, (char*)&g_Index[i][0],	400, color);
		m_Font.DrawCenter(FontManager::FontSet_AZUKI_25, 400, 230+i*40, const_cast<char*>(&g_Index[i][0]), color);
	}
}
//ページ描画
void Help::DrawReference(void)
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);			// α値を戻す

	//αが小さければ前のも描画する
	if(m_PageAlpha < 255)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - m_PageAlpha);
		if(m_OldPage >= 0 && m_OldPage < NUM_PAGE)
		DXLibMath::DrawRotaGraphResize(	m_WordHowto[m_OldPage].x, m_WordHowto[m_OldPage].y, 
											m_WordHowto[m_OldPage].scal, m_WordHowto[m_OldPage].rot, 
											m_WordHowto[m_OldPage].handle, TRUE);
		
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_PageAlpha);
	}
	//シート
	DXLibMath::DrawRotaGraphResize(	m_WordHowto[m_Page].x, m_WordHowto[m_Page].y, 
										m_WordHowto[m_Page].scal, m_WordHowto[m_Page].rot, 
										m_WordHowto[m_Page].handle, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);			// α値を戻す

	//前ページボタン
	if(m_Page > 0)
		DXLibMath::DrawRotaGraphResize(	0.4f, 0.93f, 
										1.0f, 0.0f, 
										DataManager::GetInstance().Get(DataManager::Help_Button_Prev), TRUE);
	//次ページボタン
	if(m_Page < NUM_PAGE-1)
		DXLibMath::DrawRotaGraphResize(	0.6f, 0.93f, 
										1.0f, 0.0f, 
										DataManager::GetInstance().Get(DataManager::Help_Button_Next), TRUE);
	//戻るボタン
	DXLibMath::DrawRotaGraphResize(	0.5f, 0.93f, 
									1.0f, 0.0f,
									DataManager::GetInstance().Get(DataManager::Help_Button_Back), TRUE);
}

//有効化処理
bool Help::Open(DXLibMath::Vector2 &mouse)
{
	//クリック判定
	if(	mouse.x >= 0.9425f && mouse.x < 1.0f &&
		mouse.y <= 0.07f && mouse.y > 0.0f &&
		!m_OffFrame	)
	{
		m_Exist	= true;
		m_Index = -1;
		m_Page = 0;
		m_State = INDEX;
		return true;
	}

	m_OffFrame = false;
	return false;
}
//無効化処理
bool Help::Close(void)
{
	GameInput &input = GameInput::GetInstance();
	float x = input.GetXf();
	float y = input.GetYf();

	if(	input.GetMouse(GameInput::MouseLeftTrg) && 
		x >= 0.9425f && x < 1.0f &&
		y <= 0.07f && y > 0.0f)
		return true;

	return false;
}