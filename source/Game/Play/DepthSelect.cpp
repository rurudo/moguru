#include "DepthSelect.h"
#include "../System/DataManager.h"
#include "../System/GameInput.h"
#include "../System/BlockManager.h"

DepthSelect::DepthSelect(void)
{
	m_Enable = true;
	m_Frame = 0;
	m_State = State_Fall;
	DataManager &data = DataManager::GetInstance();
	data.m_MogllStatus.position.x = 0.617f;
	data.m_MogllStatus.position.y = -0.2f;
}

DepthSelect::~DepthSelect(void)
{
}

//------------------------
// ゲームの初期化処理
void DepthSelect :: Init(void)
{
	DataManager &data = DataManager::GetInstance();

	// 背景画像ハンドル格納
	const PLANET_BACKSTAGE Chikatoshi[NUM_STAGEBACK] =
	{	0.375f,	0.5f,	0.0f,	1.0f,	0.0f,	 0.0f, 0.00001f, 0.0f, 100, 200,	data.Get(DataManager::Stage_Chikatoshi_1), true,
		0.375f,	0.5f,	0.0f,	2.0f,	0.0f,	 0.02f, 0.0f, 0.0f, 0, -10,	data.Get(DataManager::Stage_Chikatoshi_2), true,
		0.375f,	0.5f,	0.0f,	1.0f,	0.0f,	 0.00008f, 0.0f, 0.0f, 0, 200,	data.Get(DataManager::Stage_Chikatoshi_3), true,
		0.375f,	0.5f,	0.0f,	1.0f,	0.0f,	 0.0f, 0.00006f, 0.0f, 150, 300,	data.Get(DataManager::Stage_Chikatoshi_4), true,
		0.375f,	0.5f,	0.0f,	1.0f,	0.0f,	 0.0f, 0.00006f, 0.0f, 150, 300,	data.Get(DataManager::Stage_Chikatoshi_4), false,
		0.375f,	0.5f,	0.0f,	1.0f,	0.0f,	 0.0f, 0.0f, 0.0f, 0, 0,	data.Get(DataManager::Stage_Chikatoshi_Sky), true };
	const PLANET_BACKSTAGE Hyoukai[NUM_STAGEBACK] =
	{	0.375f,	0.5f,	0.0f,	1.0f,	0.0f,	 0.0f, 0.00001f, 0.0f, 100, 300,	data.Get(DataManager::Stage_Hyoukai_1), true,
		0.375f,	0.5f,	0.0f,	1.0f,	0.0f,	 0.013f,  0.0f, 0.0f, 0, -10,	data.Get(DataManager::Stage_Hyoukai_2), true,
		0.375f,	0.5f,	0.0f,	1.0f,	0.0f,	 0.0f, 0.0001f, 0.0f, 0, 240,	data.Get(DataManager::Stage_Hyoukai_3), true,
		0.375f,	0.5f,	0.0f,	1.0f,	0.0f,	 0.0f, 0.00008f, 0.0f, 0, 300,	data.Get(DataManager::Stage_Hyoukai_4), true,
		0.375f,	0.5f,	0.0f,	1.0f,	0.0f,	 0.0f, 0.00006f, 0.0f, 0, 360,	data.Get(DataManager::Stage_Hyoukai_5), true,
		0.375f,	0.5f,	0.0f,	1.0f,	0.0f,	 0.0f, 0.0f, 0.0f, 0, 0,	data.Get(DataManager::Stage_Hyoukai_Sky), true };
	const PLANET_BACKSTAGE Numachi[NUM_STAGEBACK] =
	{	0.375f,	0.5f,	0.0f,	1.0f,	0.0f,	 0.0f, 0.01f, 0.0f, 0, -10,	data.Get(DataManager::Stage_Numachi_1), true,
		0.375f,	0.5f,	0.0f,	1.0f,	0.0f,	 0.0f, 0.00001f, 0.0f, 0, 200,	data.Get(DataManager::Stage_Numachi_2), true,
		0.375f,	0.5f,	0.0f,	1.0f,	0.0f,	 0.00004f,0.0f, 0.0f, 200, 300,	data.Get(DataManager::Stage_Numachi_3), true,
		0.375f,	0.5f,	0.0f,	1.0f,	0.0f,	 0.00002f,0.0f, 0.0f, 0, 300,	data.Get(DataManager::Stage_Numachi_4), true,
		0.375f,	0.5f,	0.0f,	1.0f,	0.0f,	 0.00001f,0.0f, 0.0f, 0, 400,	data.Get(DataManager::Stage_Numachi_5), true,
		0.375f,	0.5f,	0.0f,	1.0f,	0.0f,	 0.0f, 0.0f, 0.0f, 0, 0,	data.Get(DataManager::Stage_Numachi_Sky), true, };
	const PLANET_BACKSTAGE Maguma[NUM_STAGEBACK] =
	{	0.375f,	0.5f,	0.0f,	1.0f,	0.0f,	 0.0f, 0.00001f, 0.0f, 0, 200,	data.Get(DataManager::Stage_Maguma_1), true,
		0.375f,	0.5f,	0.0f,	1.0f,	0.0f,	 0.0f, 0.00006f, 0.0f, 0, 120,	data.Get(DataManager::Stage_Maguma_2), true,
		0.375f,	0.5f,	0.0f,	1.0f,	0.0f,	 0.0f, 0.00012f, 0.0f, 0, 180,	data.Get(DataManager::Stage_Maguma_3), true,
		0.375f,	0.5f,	0.0f,	1.0f,	0.0f,	 0.0f, 0.0002f, 0.0f, 0, 240,	data.Get(DataManager::Stage_Maguma_4), true,
		0.375f,	0.5f,	0.0f,	1.0f,	0.0f,	 0.0f, 0.00006f, 0.0f, 150, 300,	data.Get(DataManager::Stage_Chikatoshi_4), false,
		0.375f,	0.5f,	0.0f,	1.0f,	0.0f,	 0.0f, 0.0f, 0.0f, 0, 0,	data.Get(DataManager::Stage_Maguma_Sky), true, };
	const PLANET_BACKSTAGE Kinmirai[NUM_STAGEBACK] =
	{	0.375f,	0.5f,	0.0f,	1.0f,	0.0f,	 0.0f, 0.0f, 0.0f, 0, 0,	data.Get(DataManager::Stage_Kinmirai_1), true,
		0.375f,	0.5f,	0.0f,	1.0f,	0.0f,	 0.0f, 0.0f, 0.0f, 0, 0,	data.Get(DataManager::Stage_Kinmirai_2), true,
		0.375f,	0.5f,	0.0f,	1.0f,	0.0f,	 0.0f, 0.0f, 0.0f, 0, 0,	data.Get(DataManager::Stage_Kinmirai_3), true,
		0.375f,	0.5f,	0.0f,	1.0f,	0.0f,	 0.0f, 0.0f, 0.0f, 0, 0,	data.Get(DataManager::Stage_Kinmirai_4), true,
		0.375f,	0.5f,	0.0f,	1.0f,	0.0f,	 0.0f, 0.00006f, 0.0f, 150, 300,	data.Get(DataManager::Stage_Chikatoshi_4), false,
		0.375f,	0.5f,	0.0f,	1.0f,	0.0f,	 0.0f, 0.0f, 0.0f, 0, 0,	data.Get(DataManager::Stage_Kinmirai_Sky), true, };

	// ハンドル代入
	switch(data.m_SceneInt["StageNo"]){
	case 0:// 地下都市
		for(int i=0; i<NUM_STAGEBACK; i++)
			m_BackStageDate[i] = Chikatoshi[i];
		break;
	case 1:// 氷河
		for(int i=0; i<NUM_STAGEBACK; i++)
			m_BackStageDate[i] = Hyoukai[i];
		break;
	case 2:// 沼地
		for(int i=0; i<NUM_STAGEBACK; i++)
			m_BackStageDate[i] = Numachi[i];
		break;
	case 3:// 火山
		for(int i=0; i<NUM_STAGEBACK; i++)
			m_BackStageDate[i] = Maguma[i];
		break;
	case 4:// 近未来
		for(int i=0; i<NUM_STAGEBACK; i++)
			m_BackStageDate[i] = Kinmirai[i];
		break;
	}

	// 数値画像のハンドル格納
	const int handle[9] =
	{	data.Get(DataManager::Floor_Number_1),
		data.Get(DataManager::Floor_Number_2),
		data.Get(DataManager::Floor_Number_3),
		data.Get(DataManager::Floor_Number_4),
		data.Get(DataManager::Floor_Number_5),
		data.Get(DataManager::Floor_Number_6),
		data.Get(DataManager::Floor_Number_7),
		data.Get(DataManager::Floor_Number_8),
		data.Get(DataManager::Floor_Number_9) };

	// ハンドルの代入
	for(int i=0; i<9; i++){
		m_Num_Handle[i] = handle[i];
	}

	// 惑星の階層初期データ
	const PLANET_HIERARCHY hierarchy[5] =
	{	{9, 120, 240, 372, 492,  600, 744, 864, 996, 1080,  600},		// 地下都市
		{4, 120, 240, 420, 600,  600, 120, 240, 360, 480,  600},		// 氷河
		{5, 120, 240, 360, 480,  600, 120, 240, 360, 480,  600},		// 沼地
		{5, 100, 200, 300, 400,  500, 100, 200, 300, 400,  500},		// 火山
		{5, 120, 240, 360, 480,  600, 120, 240, 360, 480,  600}};	// 近未来

	// 惑星の階層初期データを代入
	for(int i=0; i<5; i++)
		HIERARCHY[i] = hierarchy[i];

	Open_Hiera = 0;
	for(int i=0; i<HIERARCHY[data.m_SceneInt["StageNo"]].H_num -1; i++){
		// データと各惑星が持っているチェックポイントの照合
		if(data.m_SaveData.stageDepth[data.m_SceneInt["StageNo"]] >= HIERARCHY[data.m_SceneInt["StageNo"]].Hier[i])	
			Open_Hiera++;
		else	
			break;
	}

	// 階層表示用
	for(int i=0; i<5; i++)	m_BackFlameLoop[i] = 0;
	m_NowFloor = Open_Hiera;
	mouse_st = 0;
	m_NumScal = 1.0f;
	bright_flg = num_st = NON;
	bright = 255;
	m_myship.x = 0.65f;
	m_myship.y = data.m_MogllStatus.position.y;
	m_BlockY = 0.0f;
	m_BlockYBack = 0;
	m_SubX = -0.5f;
	m_BG_WIDTH = 600.0f / 800.0f;
	m_BG_HEIGHT = 600.0f / 600.0f;
	m_numachiAnim = 10;
	m_numachiAnimFlg = false;
	m_GoScale = 1.0f;
}

void DepthSelect::Update( bool Inventory_ST )
{
	const float fallVel = 0.005f;
	const float difference = 0.085f;
	static float back;
	DataManager &data = DataManager::GetInstance();

	if( !m_Enable )
	{
		m_BlockY = (float)(BlockManager::GetInstance().GetDepthOffset());
		m_BlockY -= (float)m_BlockYBack;	// どれだけ進んでいるか
		m_BlockYBack += (int)m_BlockY;		// 次回計算時の時に利用
		m_BlockY /= 600;					// 画面の座標値に置き換える
		// 座標の更新
		for(int i=4; i>=0; i--)
			m_BackStageDate[i].Pos.y -= m_BlockY;
		m_myship.y -= m_BlockY;

		// 各BGのアニメーション
		BgAnime();

		return;
	}

	// マウスの座標を保存
	m_mouse.x = GameInput::GetInstance().GetXf();
	m_mouse.y = GameInput::GetInstance().GetYf();

	switch( m_State )
	{
	case State_Fall:
		{
			// 演出待つのが長かったので無理やり飛ばしてます
			bool skipFlag = GameInput::GetInstance().GetMouse( GameInput::MouseLeftTrg );
			do
			{
				if( data.m_MogllStatus.position.y < 0.525f)
				{
					data.m_MogllStatus.position.y += fallVel;
					m_myship.y = data.m_MogllStatus.position.y - difference;
					if(CheckSoundMem(data.Get( DataManager::SoundSE39 )) == 0)
						PlaySoundMem( data.Get( DataManager::SoundSE39 ), DX_PLAYTYPE_BACK);
				}
				else
				{
					for(int i=0; i<NUM_STAGEBACK-1; i++)
						m_BackStageDate[i].Pos.y -= fallVel;	// BGスクロール
					float x, y;
					DXLibMath::ConvertScreenToBlock( 0.0f, fallVel, &x, &y );
					BlockManager::GetInstance().AddDepth( y );
					if( m_Frame > 63 )
					{
						StopSoundMem(data.Get( DataManager::SoundSE39 ));
						PlaySoundMem( data.Get( DataManager::SoundSE40 ), DX_PLAYTYPE_BACK);//プシュー
						m_State = State_Product;
						m_Frame = 0;
					}
					else if(CheckSoundMem(data.Get( DataManager::SoundSE39 )) == 0)
						PlaySoundMem( data.Get( DataManager::SoundSE39 ), DX_PLAYTYPE_BACK);
					m_Frame++;
				}
			}
			while( skipFlag && m_State == State_Fall );
		}
		break;
	case State_Product:
		// 真ん中まで来たら
		if(data.m_MogllStatus.position.x <= 0.45f * 0.75f && data.m_MogllStatus.position.y >= m_myship.y + difference){
			data.m_MogllStatus.position.x = 0.45f * 0.75f;
			data.m_MogllStatus.position.y = m_myship.y + difference;
			m_State = State_Select;
			PlaySoundMem( data.Get( DataManager::SoundSE55 ), DX_PLAYTYPE_BACK);//モグル着地音再生

			// ブロックの位置を取得
			back = (float)BlockManager::GetInstance().GetDepthOffset();
		}
		else{
			// 斜方投射
			data.m_MogllStatus.position.x = m_Frame * -0.05f * cos(30.0f) + m_myship.x;
			data.m_MogllStatus.position.y = (m_Frame * 0.0205f * sin(30.0f)) + (0.001f * m_Frame * m_Frame / 2) + (m_myship.y + 0.08f);
			m_Frame++;
		}
		break;
	case State_Select:	// 開始時
		if(Inventory_ST == false)	Selection();	// インベントリ開いてる時は無効
		break;
	case State_Up:
		if( data.m_MogllStatus.position.y < 0.25f )	// モグルの表示高さ調整
		{
			data.m_MogllStatus.position.y += fallVel;
			if(data.m_MogllStatus.position.y >= 0.25f)
				data.m_MogllStatus.position.y = 0.25f;
		}
		else if( data.m_MogllStatus.position.y == 0.25f )
		{
			m_Enable = false;
		}
		else
		{
			float x, y;
			DXLibMath::ConvertScreenToBlock( 0.0f, fallVel, &x, &y );
			BlockManager::GetInstance().AddDepth( y );

			// 座標の更新
			data.m_MogllStatus.position.y -= fallVel - 0.00045f;						// モグル

			m_BlockY = (float)(BlockManager::GetInstance().GetDepthOffset());
			m_BlockY -= (float)back;			// どれだけ進んでいるか
			back += (int)m_BlockY;				// 次回計算時の時に利用
			m_BlockY /= 600;					// 画面の座標値に置き換える
			// 座標の更新
			for(int i=4; i>=0; i--)
				m_BackStageDate[i].Pos.y -= m_BlockY;
			m_myship.y -= m_BlockY;

			// ブロックの位置を取得
			m_BlockYBack = BlockManager::GetInstance().GetDepthOffset();
		}

		float mogx, mogy;
		// 地面を掘る
		DXLibMath::ConvertScreenToBlock(data.m_MogllStatus.position.x, data.m_MogllStatus.position.y, &mogx, &mogy);
		m_Dig.OPUpdate(mogy);
		// ブロック更新
		BlockManager::GetInstance().Update();

		break;
	default:
		break;
	}

	// 各BGのアニメーション
	BgAnime();
}

// 描画
void DepthSelect::Draw(void)
{
	DataManager &data = DataManager::GetInstance();

	if( !m_Enable )
	{	// 宇宙船
		DXLibMath::DrawRotaGraphResize(m_myship.x, m_myship.y, 0.8f, 0.0f, data.Get(DataManager::Spaceship), TRUE);
		// 背景
		BgDraw();
		return;
	}

	// 背景
	BgDraw();

	switch( m_State )
	{
	case State_Fall:
		DXLibMath::DrawExtendGraphResize( data.m_MogllStatus.position.x, data.m_MogllStatus.position.y, 0.07f, 0.1f,
			data.Get( DataManager::GG_PLAYER_Drill01 ), TRUE );
		break;
	case State_Product:
		break;
	case State_Select:
		if(bright_flg == NON){
			if(Open_Hiera != 0){
				if(mouse_st == 1 && st_flg == St_Select)
					DXLibMath::DrawGraphResize(0.42f, 0.32f, data.Get(DataManager::Play_Button_Floor_Down), TRUE);			// 階層ボタンダウン
				else
					DXLibMath::DrawGraphResize(0.42f, 0.32f, data.Get(DataManager::Play_Button_Floor), TRUE);				// 階層ボタン
			}
			//if(mouse_st == 1 && st_flg == St_Go)
			//	DXLibMath::DrawGraphResize(0.16f, 0.32f, data.Get(DataManager::Play_Button_Go_Down), TRUE);					// ＧＯボタンダウン
			//else
			DXLibMath::DrawRotaGraphResize( 0.243f, 0.403f, m_GoScale, 0.0f,
			data.Get(DataManager::Play_Button_Go), TRUE );
			//DXLibMath::DrawGraphResize(0.16f, 0.32f, data.Get(DataManager::Play_Button_Go), TRUE);						// ＧＯボタン
			if(Open_Hiera != 0)
				DXLibMath::DrawRotaGraphResize(0.52f, 0.4f, m_NumScal, 0.0f, m_Num_Handle[m_NowFloor], TRUE);				// 数字
		}
		break;
	case State_Up:
		break;
	default:
		break;
	}
}

void DepthSelect::ChallengeDraw()
{
	DataManager &data = DataManager::GetInstance();
	double size = 1.0f + 0.2f * sin( 3.1415 / 18.0 * m_Challenge.animCount );
	DrawRotaGraph(100, 400, size, 0.0f, data.Get( DataManager::Play_Challenge ), TRUE );
}

// 宇宙船描画
void DepthSelect::SpacecraftDraw(){
	DataManager &data = DataManager::GetInstance();
	if(bright_flg == NON)
		DXLibMath::DrawRotaGraphResize(m_myship.x, m_myship.y, 0.8f, 0.0f, data.Get(DataManager::Spaceship), TRUE);			// 宇宙船
}

// 背景描画
void DepthSelect::BgDraw(){
	DataManager &data = DataManager::GetInstance();

	// 背景
	for(int i=(NUM_STAGEBACK-1); i>=0; i--){
		if(m_BackStageDate[i].isValid){
			switch(data.m_SceneInt["StageNo"]){
			case 0:// 地下都市
				if(i == 1)
					DXLibMath::DrawRotaGraphResize(m_BackStageDate[i].Pos.x-(m_BG_WIDTH*m_BackStageDate[i].Scal), m_BackStageDate[i].Pos.y, m_BackStageDate[i].Scal, m_BackStageDate[i].Rot, m_BackStageDate[i].Handle, TRUE);

				DXLibMath::DrawRotaGraphResize(m_BackStageDate[i].Pos.x, m_BackStageDate[i].Pos.y, m_BackStageDate[i].Scal, m_BackStageDate[i].Rot, m_BackStageDate[i].Handle, TRUE);
				break;
			case 1:// 氷河
				if(i == 1)
					DXLibMath::DrawRotaGraphResize(m_BackStageDate[i].Pos.x-(m_BG_WIDTH*m_BackStageDate[i].Scal), m_BackStageDate[i].Pos.y, m_BackStageDate[i].Scal, m_BackStageDate[i].Rot, m_BackStageDate[i].Handle, TRUE);

				DXLibMath::DrawRotaGraphResize(m_BackStageDate[i].Pos.x, m_BackStageDate[i].Pos.y, m_BackStageDate[i].Scal, m_BackStageDate[i].Rot, m_BackStageDate[i].Handle, TRUE);
				break;
			case 2:// 沼地
				if(i == 0)
				{
					if(m_numachiAnimFlg)
						m_BackStageDate[i].Handle = data.Get(DataManager::Stage_Numachi_1_ani);
					else
						m_BackStageDate[i].Handle = data.Get(DataManager::Stage_Numachi_1);

					//DXLibMath::DrawRotaGraphResize(m_BackStageDate[i].Pos.x-(m_BG_WIDTH*m_BackStageDate[i].Scal), m_BackStageDate[i].Pos.y, m_BackStageDate[i].Scal, m_BackStageDate[i].Rot, m_BackStageDate[i].Handle, TRUE);
					DXLibMath::DrawRotaGraphResize(m_BackStageDate[i].Pos.x, m_BackStageDate[i].Pos.y-(m_BG_HEIGHT*m_BackStageDate[i].Scal), m_BackStageDate[i].Scal, m_BackStageDate[i].Rot, m_BackStageDate[i].Handle, TRUE);
				}
				DXLibMath::DrawRotaGraphResize(m_BackStageDate[i].Pos.x, m_BackStageDate[i].Pos.y, m_BackStageDate[i].Scal, m_BackStageDate[i].Rot, m_BackStageDate[i].Handle, TRUE);
				break;
			case 3:// 火山
				DXLibMath::DrawRotaGraphResize(m_BackStageDate[i].Pos.x, m_BackStageDate[i].Pos.y, m_BackStageDate[i].Scal, m_BackStageDate[i].Rot, m_BackStageDate[i].Handle, TRUE);
				break;
			case 4:// 近未来
				DXLibMath::DrawRotaGraphResize(m_BackStageDate[i].Pos.x, m_BackStageDate[i].Pos.y, m_BackStageDate[i].Scal, m_BackStageDate[i].Rot, m_BackStageDate[i].Handle, TRUE);
				break;
			}
		}
	}

}

// 選択
void DepthSelect::Selection(void){
	DataManager &data = DataManager::GetInstance();
	int floor = 0;	// 階層送りの数 ＋か－か

	// マウスの位置からどのボタンにいるのかを取得
	if(m_mouse.y >= 0.32f && m_mouse.y <= 0.32f+0.166f){	// y座標は変わらない
		if(m_mouse.x >= 0.16f && m_mouse.x <= 0.16f+0.163f){
			if( st_flg != St_Go )
			{
				st_flg = St_Go;
				PlaySoundMem( DataManager::GetInstance().Get( DataManager::SoundSE07 ), DX_PLAYTYPE_BACK);
			}
		}
		else if(m_mouse.x >= 0.42f && m_mouse.x <= 0.42f+0.163f && Open_Hiera != 0){
			if( st_flg != St_Select )
			{
				st_flg = St_Select;
				PlaySoundMem( DataManager::GetInstance().Get( DataManager::SoundSE07 ), DX_PLAYTYPE_BACK);
			}
		}
		else	st_flg = St_Non;	// 例外処理
	}
	else		st_flg = St_Non;	// 例外処理

	//ボタンの拡縮
	if(st_flg == St_Go)
		m_GoScale += (1.2f - m_GoScale)*0.4f;
	else
		m_GoScale += (1.0f - m_GoScale)*0.4f;

	// クリック時
	if( GameInput::GetInstance().GetMouse( GameInput::MouseLeftTrg ))
	{// 階層選択
		// 処理実行
		if(st_flg != St_Non){
			if(Open_Hiera != 0)
				PlaySoundMem( DataManager::GetInstance().Get( DataManager::SoundSE10 ), DX_PLAYTYPE_BACK);
			if(st_flg == St_Select && num_st == NON){
				num_st = ON;
				m_floor = 1;// 階層を進ませる数設定
			}
			mouse_st = 1;
		}
	}
	// リリース時
	if(GameInput::GetInstance().GetMouse( GameInput::MouseLeftRls ) && mouse_st == 1){
		if(st_flg != St_Non){
			if(st_flg == St_Go){
				if(m_NowFloor != 0){
					bright_flg = ON;
				}
				else{
					m_State = State_Up;
				}
			}
		}
		mouse_st = 0;
	}
	//マウスホイール回転時
	if(floor == 0  && Open_Hiera != 0)
	{
		//上下判定
		floor += GameInput::GetInstance().GetMouseWheelUp() * -1;
		floor += GameInput::GetInstance().GetMouseWheelDown() * 1;
		if(floor != 0)
		{
			// 処理実行
			if(num_st == NON){
				PlaySoundMem( DataManager::GetInstance().Get( DataManager::SoundSE10 ), DX_PLAYTYPE_BACK);
				num_st = ON;
				m_floor = floor;
			}
		}
	}
	
	//数字変更処理実行
	if(num_st != NON){
		NumberScal();
	}
	if(bright_flg != NON){
		Black();
	}
}

// 数字の拡縮
void DepthSelect::NumberScal(void){
	// 縮小
	if(num_st == ON){
		m_NumScal -= 0.1f;
		if(m_NumScal <= 0.0f){
			num_st = OFF;
			m_NumScal = 0.0f;
			m_NowFloor += m_floor;	//階層おくり
			m_floor = 0;
			//範囲を越えたらループ
			if(m_NowFloor > Open_Hiera)		m_NowFloor = 0;
			if(m_NowFloor < 0)				m_NowFloor = Open_Hiera;
		}
	}
	// 拡大
	else if(num_st == OFF){
		m_NumScal += 0.1f;
		if(m_NumScal >= 1.0f){
			num_st = NON;
			m_NumScal = 1.0f;
		}
	}
}

// 暗幕
void DepthSelect::Black(void){
	int	row_num	= 13;	// 何行前から読み込むか
	DataManager &data = DataManager::GetInstance();
	// 縮小
	if(bright_flg == ON){
		bright -= 10;
		if(bright <= 0){
			// 中間ワープ暗転時処理
			bright_flg = OFF;
			bright = 0;
			for(int i=HIERARCHY[data.m_SceneInt["StageNo"]].Hier[m_NowFloor-1] - row_num; i<HIERARCHY[data.m_SceneInt["StageNo"]].Hier[m_NowFloor-1]; i++){
				BlockManager::GetInstance().LoadLine(i);
			}
			for(int i = 0; i < 30; i++)
			{
				// 全階層の割合でユニット数を決定
				data.m_MogllStatus.unitCount[i] = 99 / HIERARCHY[data.m_SceneInt["StageNo"]].H_num * (HIERARCHY[data.m_SceneInt["StageNo"]].H_num - m_NowFloor);
			}
			data.m_MogllStatus.position.y = -0.1f;
		}
	}
	// 拡大
	else if(bright_flg == OFF){
		bright += 10;
		if(bright >= 255){
			bright = 255;
			m_State = State_Up;
		}
	}
	SetDrawBright(bright, bright, bright);
}

// 背景アニメーション
void DepthSelect::BgAnime(void){
	for(int i=0; i< NUM_STAGEBACK; i++)
	{
		if(m_BackStageDate[i].isValid)
		{
			//移動
			m_BackStageDate[i].Pos.x += m_BackStageDate[i].Speed.x;
			m_BackStageDate[i].Pos.y += m_BackStageDate[i].Speed.y;
			//範囲制限（フレーム数）
			if(m_BackStageDate[i].FRAME_CNT > 0)
			{
				m_BackStageDate[i].frame_cnt--;
				if(m_BackStageDate[i].frame_cnt <= 0)
				{
					m_BackStageDate[i].Speed.x = -m_BackStageDate[i].Speed.x;
					m_BackStageDate[i].Speed.y = -m_BackStageDate[i].Speed.y;
					m_BackStageDate[i].frame_cnt = m_BackStageDate[i].FRAME_CNT;//フレーム数リセット
				}
			}
			else if(m_BackStageDate[i].FRAME_CNT == -10)
			{
				if(m_BackStageDate[i].Speed.x != 0.0f)
				{
					if(m_BackStageDate[i].Pos.x > (m_BG_WIDTH *1.5f) * m_BackStageDate[i].Scal ) 
						m_BackStageDate[i].Pos.x = (m_BG_WIDTH*0.5f) * m_BackStageDate[i].Scal;
					if(m_BackStageDate[i].Pos.x < (m_BG_WIDTH*0.5f) * m_BackStageDate[i].Scal  ) 
						m_BackStageDate[i].Pos.x = (m_BG_WIDTH *1.5f) * m_BackStageDate[i].Scal;
				}
				if(m_BackStageDate[i].Speed.y != 0.0f)
				{
					if( m_BackStageDate[i].Pos.y > (m_BG_HEIGHT *1.5f) * m_BackStageDate[i].Scal ) 
						m_BackStageDate[i].Pos.y = (m_BG_HEIGHT*0.5f) * m_BackStageDate[i].Scal;
					if( m_BackStageDate[i].Pos.y < (m_BG_HEIGHT*0.5f) * m_BackStageDate[i].Scal  ) 
						m_BackStageDate[i].Pos.y = (m_BG_HEIGHT *1.5f) * m_BackStageDate[i].Scal;
				}
			}
		}
	}

	//沼地用アニメーションカウンタ
	if(--m_numachiAnim < 0)
	{
		m_numachiAnim = 10;
		m_numachiAnimFlg = !m_numachiAnimFlg;
	}
}