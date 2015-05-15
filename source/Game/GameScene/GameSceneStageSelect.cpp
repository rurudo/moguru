#include "GameSceneStageSelect.h"
#include "../System/GameInput.h"
#include "../System/DataManager.h"
#include "../System/TaskManager.h"
#include "../Task/Task_DrawEffect.h"

//====================================================
// 生成関数
GameScene* GameSceneStageSelect_CreateScene()
{
	return new GameSceneStageSelect();
}

//====================================================
// クラスメソッド
GameSceneStageSelect :: GameSceneStageSelect(void)
{
	Init();
}
GameSceneStageSelect :: ~GameSceneStageSelect(void)
{
	Release();
}

//------------------------
// ゲームの初期化処理
void GameSceneStageSelect :: Init(void)
{
	DataManager& data = DataManager::GetInstance();
	DataManager& Backdata = DataManager::GetInstance();

	data.Load(DataManager::ResourceSetStageSelect);
	// 惑星の初期データ
	const DRAW_DATA planet[PLANET_MAX] =
	{	{0.45f, 0.52f, 0.0f, 1.0f, 0.0f, data.Get(DataManager::Ic_stage1), false, 0.0f,	0.0f,  -0.035f},	// 地下都市
		{0.13f, 0.42f, 0.0f, 0.8f, 0.0f, data.Get(DataManager::Ic_stage2), false, 0.0f, -0.01f, 0.015f},	// 氷海
		{0.30f, 0.80f, 0.0f, 0.7f, 0.0f, data.Get(DataManager::Ic_stage3), false, 0.0f, 0.0f,   0.07f},		// 沼地
		{0.72f, 0.80f, 0.0f, 0.8f, 0.0f, data.Get(DataManager::Ic_stage4), false, 0.0f, -0.01f, -0.01f},	// 火山
		{0.72f, 0.30f, 0.0f, 0.7f, 0.0f, data.Get(DataManager::Ic_stage5), false, 0.0f, 0.0f,   0.05f}};	// 近未来
	// 惑星の背景パス
	const int planet_back[PLANET_MAX] =
	{	data.Get(DataManager::Ic_stage1_Back),	// 地下都市の背景
		data.Get(DataManager::Ic_stage2_Back),	// 氷海の背景
		data.Get(DataManager::Ic_stage3_Back),	// 沼地の背景
		data.Get(DataManager::Ic_stage4_Back),	// 火山の背景
		data.Get(DataManager::Ic_stage5_Back)};	// 近未来の背景

	// 自機の情報設定
	m_Ship.position.x = 0.5f;
	m_Ship.position.y = 0.5f;
	m_Ship.handle = data.Get(DataManager::Spaceship);

	// 惑星のデータを代入
	for(int i = 0; i < PLANET_MAX; i++)
	{
		m_Planet[i] = planet[i];
		m_Planet_Back_handle[i] = planet_back[i];
		// 惑星の半径を求める
		m_Planet[i].r = 0.125f * m_Planet[i].scal;		// 画面の横サイズ800と画像横サイズ200より割合を0.25、その半径なので0.125
		m_st[i].x = 0.5f - m_Planet[i].x;
		m_st[i].y = 0.5f - m_Planet[i].y;
		// 解放されているかどうかのチェック(-1は未開放、0以上は開放)
		if(data.m_SaveData.stageDepth[i] >= 0.0f)	m_Planet[i].release = true;

		// 拡縮の保存
		m_PlanetBackScal[i] = planet[i].scal;
	}

	// 前の遷移がタイトルの場合
	if(Backdata.m_SceneInt["BackST"] == GAME_SCENE_TITLE){
		// フェード用
		m_Brightness = 0;
		m_BrightnessFlg = NON;
		m_ship_scal = 0.3f;
		m_id_back = 0;
		m_speed = 0.01f;
		m_CursorScal = m_Planet[0].scal;
	}

	// 前の遷移がプレイの場合
	if(Backdata.m_SceneInt["BackST"] == GAME_SCENE_PLAY){
		// フェード用
		m_Brightness = 255;
		m_BrightnessFlg = FADE2;
		m_ship_scal = 0.05f;
		m_id_back = data.m_SceneInt["StageNo"];
		Backup();
		m_Ship.position.x = m_Planet[m_id_back].x+0.01f;
		m_Ship.position.y = m_Planet[m_id_back].y;
		m_speed = 0.0001f;
		m_scal_back = m_Planet[m_id_back].scal;
		m_CursorScal = planet[m_id_back].scal;
	}

	m_AddAlpha		= 64.0f;
	m_AddAlphaState = 1.0f;
	m_BeforeId = 0;
	m_PlanetEffectFlg = false;
	m_CursorFlg = false;
	m_BackBrightness = m_FrameBrightness = 255;
	m_BackBrightnessFlg = m_FrameBrightnessFlg = false;

	PlaySoundMem( data.Get( DataManager::SoundBGM02 ), DX_PLAYTYPE_LOOP);
	m_Font.Load( FontManager::FontSet_AZUKI_003 );
}

//------------------------
// ゲームの終了処理
void GameSceneStageSelect :: Release()
{
	DataManager& data = DataManager::GetInstance();
	TaskManager::GetInstance().Release();
	StopSoundMem( data.Get( DataManager::SoundBGM02 ) );
}
//-------------------------
// 描画処理
void GameSceneStageSelect :: Draw(void)
{
	ClearDrawScreen(); // 描画先クリア
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	DataManager& data = DataManager::GetInstance();

	// BG
	DXLibMath::DrawGraphResize(0.0, 0.0, data.Get(DataManager::StageSelect_Background), TRUE);

	// 星
	for(int i = 0; i < PLANET_MAX; i++)
	{
		// 惑星の背景
		if(m_Ship.id == i)	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_BackBrightness);		// α値の変更
		else				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);					// α値の変更

		DXLibMath::DrawRotaGraphResize(m_Planet[i].x, m_Planet[i].y, m_Planet[i].scal, m_Planet[i].rot, m_Planet_Back_handle[i], TRUE);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);			// α値を戻す

		// 未開放の星は黒く 開放は明るく
		if(m_Planet[i].release == true)	SetDrawBright(255, 255, 255);
		else							SetDrawBright(0, 0, 0);
		// 選択されていない星を描画
		if(m_id_back != i)	DXLibMath::DrawRotaGraphResize(m_Planet[i].x, m_Planet[i].y, m_Planet[i].scal, m_Planet[i].rot, m_Planet[i].handle, TRUE);
		// 明るさを元に戻す
		SetDrawBright(255, 255, 255);
		if(m_Planet[i].release == false)
			DXLibMath::DrawRotaGraphResize(m_Planet[i].x, m_Planet[i].y, m_Planet[i].scal, 0.0f, data.Get(DataManager::Ic_stage_Cascade), TRUE);
	}


	// プライオリティの管理ができないので選択されている星だけ最後に描画する
	DXLibMath::DrawRotaGraphResize(m_Planet[m_id_back].x, m_Planet[m_id_back].y, m_Planet[m_id_back].scal, m_Planet[m_id_back].rot, m_Planet[m_id_back].handle, TRUE);

	// フレーム
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_FrameBrightness);		// α値の変更
	DXLibMath::DrawGraphResize(0.0, 0.0, data.Get(DataManager::StageSelect_Frame_Back), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);			// α値を戻す
	DXLibMath::DrawGraphResize(0.0, 0.0, data.Get(DataManager::StageSelect_Frame), TRUE);
	DXLibMath::DrawGraphResize(0.0, 0.0, data.Get(DataManager::StageSelect_FrameCharacter), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_ADD, (int)m_AddAlpha);		// α値の変更
	DXLibMath::DrawGraphResize(0.0, 0.0, data.Get(DataManager::StageSelect_FrameCharacter_Add), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);			// α値を戻す


	// ターゲットにはインフォメーションを表示
	if(m_BrightnessFlg == NON)
	{
		//DXLibMath::DrawRotaGraphResize(m_Planet[m_Ship.id].x+m_Planet[m_Ship.id].cur_x, m_Planet[m_Ship.id].y+m_Planet[m_Ship.id].cur_y, m_CursorScal+m_Planet[m_Ship.id].cur_scal, 0.0f, data.Get(DataManager::Cur_stage), TRUE);
		DXLibMath::DrawRotaGraphResize(m_Planet[m_Ship.id].x+0.17f, m_Planet[m_Ship.id].y-0.15f, 0.8f, 0.0f, data.Get(DataManager::StageInfo_Bar), TRUE);
		int count = 0;
		for(int i = 10 * m_Ship.id; i < 10 * (m_Ship.id + 1); i++)
		{
			if( data.m_SaveData.stageItemStatus[i] == 1 )	count++;
		}
		//char buf[256];
		//sprintf_s(buf, "%d   10", count );
		//m_Font.DrawFontString( FontManager::FontSet_AZUKI_003, m_Planet[m_Ship.id].x+0.17f, m_Planet[m_Ship.id].y-0.2f, buf, 0.2f, GetColor( 128, 255, 128 ) );
		DrawFormatStringToHandle( static_cast<int>(800.0f * (m_Planet[m_Ship.id].x + 0.14f)),
			static_cast<int>( 600.0f * (m_Planet[m_Ship.id].y - 0.22f)),
			GetColor(128,255,128), m_Font.GetHandle( FontManager::FontSet_MSGothic_Middle ), "%d / 10", count );
	}

	// 宇宙船
	DXLibMath::DrawRotaGraphResize(m_Ship.position.x, m_Ship.position.y, m_ship_scal, DXLibMath::CalcRotation(m_Ship.facing),m_Ship.handle, TRUE);
	// リング
	TaskManager::GetInstance().Draw();

	if(m_BrightnessFlg != NON){
		// 四角
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_Brightness);
		DXLibMath::DrawBoxResize(0.0f, 0.0f, 1.0f, 1.0f, GetColor(255, 255, 255), TRUE);
	}

	//ScreenFlip();//スワップ
}

//-------------------------
// 更新処理
int GameSceneStageSelect :: Update(void)
{
	GameInput &input = GameInput::GetInstance();

	// マウスの座標を保存
	m_mouse.x = GameInput::GetInstance().GetXf();
	m_mouse.y = GameInput::GetInstance().GetYf();
	if(m_BrightnessFlg == NON)
	{
		// 各惑星と判定
		for(int i=0; i< PLANET_MAX; i++){
			VECTOR cur;
			cur.x = m_Planet[i].x;
			cur.y = m_Planet[i].y;

			// マウスカーソルと星のチェック	当たっていればフラグを立て、ステータスの表示
			if(DXLibMath::CircleOnPoint(m_mouse, cur, m_Planet[i].r) == true && m_Planet[i].release == true)
			{
				if( m_Ship.id != i )
				{
					PlaySoundMem( DataManager::GetInstance().Get( DataManager::SoundSE11 ), DX_PLAYTYPE_BACK);
					m_Ship.id = i;
				}
				// 左クリック
				if(input.GetMouse(GameInput::MouseLeftTrg) && m_BrightnessFlg == NON)
				{
					PlaySoundMem( DataManager::GetInstance().Get( DataManager::SoundSE12 ), DX_PLAYTYPE_BACK);
					DataManager& data = DataManager::GetInstance();
					data.m_SceneInt["StageNo"] = m_Ship.id;
					m_scal_back = m_Planet[i].scal;
					m_id_back = m_Ship.id;
					m_BrightnessFlg = FADE1;
				}
				break;
			}
		}
	}
	// 宇宙船を移動させる
	MovePoint();
	static int m_Count;
	TaskManager &taskManager = TaskManager::GetInstance();
	if( m_Count % 2 == 0)
	{
		Task_DrawEffect* task = dynamic_cast<Task_DrawEffect*>( taskManager.CreateTask(TASK_TYPE_DRAW_EFFECT) );
		task->SetPosition( -m_Ship.facing.x * 0.1f + m_Ship.position.x, -m_Ship.facing.y * 0.1f + m_Ship.position.y );
		task->SetVelocity( -m_Ship.facing.x * 0.005f, -m_Ship.facing.y * 0.005f );
		task->SetRotation( DXLibMath::CalcRotation( m_Ship.facing ) );
		task->SetSize( m_ship_scal );
		task->SetAddSize( 0.9f );
		// 発射するエフェクトの画像と時間を指定
		DataManager &data = DataManager::GetInstance();
		task->Add( data.Get( DataManager::JetRing ), 60);

		// タスクマネージャにこのタスクを登録
		taskManager.Add( task, 0 );
	}
	taskManager.Update();

	// フレームの明るさ
	if(m_FrameBrightnessFlg == false){
		m_FrameBrightness -= 2;
		if(m_FrameBrightness <= 80)		m_FrameBrightnessFlg = true;
	}
	else{
		m_FrameBrightness += 2;
		if(m_FrameBrightness >= 255)	m_FrameBrightnessFlg = false;
	}

	// 惑星演出
	if(m_BrightnessFlg == NON){
		if(m_PlanetEffectFlg == false){
			m_BackBrightness			-= (int)((255-80) / (0.2f / 0.005f));
			m_Planet[m_Ship.id].scal	-= 0.005f;
			if((m_BackBrightness <= 80) || (m_Planet[m_Ship.id].scal <= m_PlanetBackScal[m_Ship.id])){
				m_PlanetEffectFlg = true;
				m_BackBrightness = 80;
				m_Planet[m_Ship.id].scal = m_PlanetBackScal[m_Ship.id];
			}
		}
		else{
			m_BackBrightness			+= (int)((255-80) / (0.2f / 0.005f));
			m_Planet[m_Ship.id].scal	+= 0.005f;
			if( (m_BackBrightness >= 255) || (m_Planet[m_Ship.id].scal >= m_PlanetBackScal[m_Ship.id] + 0.2f)){
				m_PlanetEffectFlg = false;
				m_BackBrightness = 255;
				m_Planet[m_Ship.id].scal = m_PlanetBackScal[m_Ship.id] + 0.2f;
			}
		}
	}

	//m_Planet[i].scal m_PlanetBackScal
	// カーソルの拡縮
	//if(m_CursorFlg == false){
	//	m_CursorScal -= 0.007f;
	//	if(m_CursorScal <= m_Planet[m_Ship.id].scal+m_Planet[m_Ship.id].cur_scal - 0.2f)
	//		m_CursorFlg = true;
	//}
	//else{
	//	m_CursorScal += 0.007f;
	//	if(m_CursorScal >= m_Planet[m_Ship.id].scal+m_Planet[m_Ship.id].cur_scal - 0.05f)
	//		m_CursorFlg = false;
	//}

	//文字の光
	m_AddAlpha += m_AddAlphaState;
	if(m_AddAlpha < 32.0f || m_AddAlpha > 160.0f)
		m_AddAlphaState = -m_AddAlphaState;

	m_Count++;

	// カーソルが移動したらカーソルの拡縮をセットしなおす
	if(m_BeforeId != m_Ship.id){
		m_CursorScal = m_Planet[m_Ship.id].scal+m_Planet[m_Ship.id].cur_scal;
		m_CursorFlg = false;
		m_Planet[m_BeforeId].scal = m_PlanetBackScal[m_BeforeId];
		m_BackBrightness = 80;
	}

	m_BeforeId = m_Ship.id;
	// 遷移
	if(m_BrightnessFlg == FADE1 && m_Brightness >= 255){
		return GAME_SCENE_PLAY;
	}

	if(m_BrightnessFlg == FADE2 && m_Brightness <= 0){
		m_BrightnessFlg = NON;
		m_Brightness = 0;
		m_CursorScal = m_Planet[m_Ship.id].scal;
	}
	return GAME_SCENE_THIS;
}

void GameSceneStageSelect::MovePoint(void)
{
	// ターゲットとなっている惑星の座標を取得
	VECTOR	tie;			// 星と宇宙船を結ぶベクトル
	float	len;			// 宇宙船と接点の距離
	float	dx, dy;			// 計算用
	static float	rot;	// 移動時の回転成分

	// 通常時の宇宙船の動き
	if(m_BrightnessFlg == NON){
		// 宇宙船と惑星の中点を結ぶベクトル
		tie.x = m_Planet[m_Ship.id].x - m_Ship.position.x;
		tie.y = m_Planet[m_Ship.id].y - m_Ship.position.y;
		tie.z = 0.0f;
		if(DXLibMath::Length(tie) >= m_Planet[m_Ship.id].r){	// バグつぶし
			// 宇宙船と接点の長さ
			len = sqrt((DXLibMath::Length(tie)*DXLibMath::Length(tie)) - (m_Planet[m_Ship.id].r*m_Planet[m_Ship.id].r));
			// 計算用の値
			dx = len * (len/DXLibMath::Length(tie));
			dy = m_Planet[m_Ship.id].r * (dx/len);
			// 座標を求める
			m_terget.x = (m_Ship.position.x + (tie.x * dx)) + (-tie.y * dy);
			m_terget.y = (m_Ship.position.y + (tie.y * dx)) + (tie.x * dy);
			m_terget.z = 0.0f;
		}
		rot = 0.15f;
		m_speed = 0.01f;
	}

	// ステージ決定後の宇宙船の動き
	else if(m_BrightnessFlg == FADE1){
		// 演出部分
		Staging();
		rot = 0.05f;
		m_speed -= 0.007f;
		if(m_speed <= 0.003f)	m_speed = 0.003f;
		m_ship_scal -= 0.002f;
		if(m_ship_scal <= 0.05f)	m_ship_scal = 0.05f;
		m_Brightness += 2;
	}

	else if(m_BrightnessFlg == FADE2){
		// 演出部分
		Staging2();
		rot = 0.15f;
		m_speed += 0.00005f;
		if(m_speed >= 0.01f)	m_speed = 0.01f;
		m_ship_scal += 0.002f;
		if(m_ship_scal >= 0.3f)	m_ship_scal = 0.3f;
		m_Brightness -= 2;
	}

	// ターゲットとなっている惑星の方向へ10%方向転換
	DXLibMath::FacingTarget(m_Ship.position, m_terget, &m_Ship.facing, rot);
	// 自分の向いている方向へ移動
	m_Ship.position.x += m_Ship.facing.x * m_speed;
	m_Ship.position.y += m_Ship.facing.y * m_speed;
}

void GameSceneStageSelect::Staging(void)
{
	// 選んだ星は真ん中へ(拡大)その他は外へ(縮小)
	for(int i = 0; i < PLANET_MAX; i++)
	{
		if(i == m_id_back){
			m_Planet[i].x += m_st[i].x/255.0f;
			m_Planet[i].y += m_st[i].y/255.0f;
			m_Planet[i].scal += 0.02f;
		}else{
			m_Planet[i].x -= m_st[i].x/500.0f;
			m_Planet[i].y -= m_st[i].y/500.0f;
			m_Planet[i].scal -= 0.002f;
		}
	}
	// 目的地を選んだ星の中点へ
	m_terget.x = m_Planet[m_id_back].x;
	m_terget.y = m_Planet[m_id_back].y;
}

void GameSceneStageSelect::Staging2(void)
{
	// 選んだ星は真ん中へ(拡大)その他は外へ(縮小)逆
	for(int i = 0; i < PLANET_MAX; i++)
	{
		if(i == m_id_back){
			m_Planet[i].x -= m_st[i].x/255.0f;
			m_Planet[i].y -= m_st[i].y/255.0f;
			m_Planet[i].scal -= 0.02f;
		}else{
			m_Planet[i].x += m_st[i].x/500.0f;
			m_Planet[i].y += m_st[i].y/500.0f;
			m_Planet[i].scal += 0.002f;
		}
	}
	// 惑星が戻る方向と逆の方向へ目的地のセット
	if(m_id_back == 0){		// 真ん中の星のみ(変な挙動防止)
		m_terget.x = 0.8f;
		m_terget.y = 0.3f;
	}
	else{
		m_terget.x = 0.5f + (0.5f - m_Planet[m_id_back].x);
		m_terget.y = 0.5f + (0.5f - m_Planet[m_id_back].y);
	}
}

// 画面遷移自のデータの保存
void GameSceneStageSelect :: Backup(void)
{
	int loop = 0;
	while(loop <= 255){
	// 選んだ星は真ん中へ(拡大)その他は外へ(縮小)
		for(int i = 0; i < PLANET_MAX; i++)
		{
			if(i == m_id_back){
				m_Planet[i].x += m_st[i].x/255.0f;
				m_Planet[i].y += m_st[i].y/255.0f;
				m_Planet[i].scal += 0.02f;
			}else{
				m_Planet[i].x -= m_st[i].x/500.0f;
				m_Planet[i].y -= m_st[i].y/500.0f;
				m_Planet[i].scal -= 0.002f;
			}
		}
		loop += 2;
	}
	// 目的地を選んだ星の中点へ
	m_terget.x = 0.4f;
	m_terget.y = 0.4f;
	m_terget.z = 0.0f;
}