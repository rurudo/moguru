#include "GameScenePlay.h"
#include "../System/GameInput.h"
#include "../System/DataManager.h"
#include "../System/DxLibMath.h"
#include "../System/TaskManager.h"
#include "../System/EquipmentFunction.h"
#include "../Menu/MenuIconSort.h"

//====================================================
// 生成関数
GameScene* GameScenePlay_CreateScene()
{
	return new GameScenePlay();
}

//====================================================
// クラスメソッド
GameScenePlay :: GameScenePlay(void)
{
	Init();
}
GameScenePlay :: ~GameScenePlay(void)
{
	Release();
}

//------------------------
// ゲームの初期化処理
void GameScenePlay :: Init(void)
{
	m_DebugNowGetID = 0;
	DataManager& data = DataManager::GetInstance();
	//data.Load(DataManager::ResourceSetPlay);
	data.m_MogllStatus.life = 1000;
	data.m_MogllStatus.maxLife = 1000;
	data.m_MogllStatus.maxResource = 1000;
	data.m_MogllStatus.resource = 500;
	data.m_MogllStatus.treasureStatus = -1;
	data.m_MogllStatus.noHitTime = 0;
	// データの初期化
	data.Load( DataManager::ResourceSetPlay );
	m_DepthSelect.Init();
	m_GameOver.Init();
	m_GameClear.Init();
	m_Help.Init();
	m_SoundTime = 0;
	m_HelpFlg = false;
	m_EscapeFlag = false;
	for( int i = 0; i < 3; i++)
	{
		data.m_MogllStatus.equipStatus[i] = 0;
	}
	for(int i = 0; i < 30; i++)
	{
		data.m_MogllStatus.unitCount[i] = 99;
	}

	// 惑星の階層初期データ
	const PLANET_HIERARCHY hierarchy[5] =
	{	{9, 120, 240, 372, 492,  600, 744, 864, 996, 1080,  600},		// 地下都市
		{4, 120, 240, 420, 600,  600, 120, 240, 360, 480,  600},		// 氷河
		{5, 120, 240, 360, 480,  600, 120, 240, 360, 480,  600},		// 沼地
		{5, 100, 200, 300, 400,  500, 100, 200, 300, 400,  500},		// 火山
		{5, 120, 240, 360, 480,  600, 120, 240, 360, 480,  600}};	// 近未来

	// 惑星の階層初期データを代入
	for(int i = 0; i < 5; i++)
	{
		HIERARCHY[i] = hierarchy[i];
	}

	//メニュークラスのインスタンスの作成
	m_Menu = new GameMenu;
	// ブロックマネージャーのデータ読み込み
	BlockManager &BM = BlockManager::GetInstance();
	BM.Init();
	switch( data.m_SceneInt["StageNo"] )
	{
	case 1:
		BM.LoadGraphic("resource/texture/Map/STAGE_2.bmp");
		BM.LoadEnemyGraphic("resource/texture/Map/ENEMY_2.bmp");
		if(CheckSoundMem(data.Get( DataManager::SoundBGM05 )) == 0)
			PlaySoundMem( data.Get( DataManager::SoundBGM05 ), DX_PLAYTYPE_LOOP);
		break;
	case 2:
		BM.LoadGraphic("resource/texture/Map/STAGE_3.bmp");
		BM.LoadEnemyGraphic("resource/texture/Map/ENEMY_3.bmp");
		if(CheckSoundMem(data.Get( DataManager::SoundBGM06 )) == 0)
			PlaySoundMem( data.Get( DataManager::SoundBGM06 ), DX_PLAYTYPE_LOOP);
		break;
	case 3:
		BM.LoadGraphic("resource/texture/Map/STAGE_4.bmp");
		BM.LoadEnemyGraphic("resource/texture/Map/ENEMY_4.bmp");
		if(CheckSoundMem(data.Get( DataManager::SoundBGM07 )) == 0)
			PlaySoundMem( data.Get( DataManager::SoundBGM07 ), DX_PLAYTYPE_LOOP);
		break;
	case 4:
		BM.LoadGraphic("resource/texture/Map/STAGE_5.bmp");
		BM.LoadEnemyGraphic("resource/texture/Map/ENEMY_5.bmp");
		if(CheckSoundMem(data.Get( DataManager::SoundBGM08 )) == 0)
			PlaySoundMem( data.Get( DataManager::SoundBGM08 ), DX_PLAYTYPE_LOOP);
		break;
	default:
		BM.LoadGraphic("resource/texture/Map/STAGE_1.bmp");
		BM.LoadEnemyGraphic("resource/texture/Map/ENEMY_1.bmp");
		if(CheckSoundMem(data.Get( DataManager::SoundBGM04 )) == 0)
			PlaySoundMem( data.Get( DataManager::SoundBGM04 ), DX_PLAYTYPE_LOOP);
		break;
	}
	// タスクマネージャーの互換性の問題
	TaskManager::GetInstance().Connect( &BM, &UnitManager::GetInstance() );
	m_FrameCount = 0;

	BlockManager::GetInstance().SetBreakBlock(&m_BreakBlock);
}

//------------------------
// ゲームの終了処理
void GameScenePlay :: Release()
{
	TaskManager::GetInstance().Release();
	BlockManager::GetInstance().Release();
	UnitManager::GetInstance().Release();
	
	delete m_Menu;
}

//------------------------
// 描画処理
void GameScenePlay :: Draw(void)
{
	ClearDrawScreen(); // 描画先クリア
	
	DataManager& data = DataManager::GetInstance();
	// ゲーム開始描画
	m_DepthSelect.Draw();
	// ブロック描画
	BlockManager::GetInstance().Draw();
	// ユニット描画
	UnitManager::GetInstance().Draw();
	// モグルの描画
	m_UserInterface.DrawMogll();
	//ブロック破壊パーティクル
	m_BreakBlock.Draw();
	// 死んだらエフェクトを表示しない
	if( data.m_MogllStatus.life > 0 )
	{
		// タスク描画
		TaskManager::GetInstance().Draw();
	}
	// 宇宙船描画
	m_DepthSelect.SpacecraftDraw();
	//フィールドエフェクト描画
	m_UserInterface.DrawFieldEffect();
	// UI描画
	m_UserInterface.Draw( BlockManager::GetInstance().GetDepth());
	if(m_Menu->GetConfirmationFlag() || m_Menu->GetFirstProduction() || m_Menu->GetProduction()){
		// ヘルプ表示
		m_Help.Draw();
	}
	// メニュー描画
	m_Menu->Draw();
	// 脱出メニュー
	m_UserInterface.DrawEscape();
	// レーダーオンオフ
	m_UIDisplay.Draw();
	if(!m_Menu->GetConfirmationFlag() && !m_Menu->GetFirstProduction() && !m_Menu->GetProduction()){
		// ヘルプ表示
		m_Help.Draw();
	}
	// お宝ゲット画面
	m_TreasureEffect.Draw();
	//
	m_AfterGetItem.Draw();
	// ゲームクリア画面描画
	m_GameClear.Draw();
	// ゲームオーバー画面描画
	m_GameOver.Draw();

	//ScreenFlip();//スワップ
}

//-------------------------
// 更新処理
int GameScenePlay :: Update(void)
{
	DataManager& data = DataManager::GetInstance();

	DXLibMath::Vector2 l_mouse;
	//マウスの座標を保存
	l_mouse.x = GameInput::GetInstance().GetXf();
	l_mouse.y = GameInput::GetInstance().GetYf();

	// falseならフラグを折って操作可能に
	m_HelpFlg = m_Help.Update();
	//ヘルプを開くor閉じる:右クリック(トリガー)
	if((data.m_MogllStatus.treasureStatus == -1 && GameInput::GetInstance().GetMouse(GameInput::MouseLeftTrg) && m_HelpFlg == false && m_EscapeFlag == false
		&& !m_Menu->GetConfirmationFlag() && !m_Menu->GetFirstProduction() && !m_Menu->GetProduction())){
		// trueならフラグを立てて操作不可に
		if(m_Help.Open(l_mouse))	m_HelpFlg = true;
	}

	if(m_HelpFlg == false &&  data.m_MogllStatus.life > 0 && !m_GameClear.IsAct() && m_EscapeFlag == false && 
		!m_Menu->GetConfirmationFlag() && !m_Menu->GetFirstProduction() && !m_Menu->GetProduction()){
		//メニューを開くor閉じる:左クリック(トリガー)
		if(data.m_MogllStatus.treasureStatus == -1 && GameInput::GetInstance().GetMouse(GameInput::MouseLeftTrg)){
			if(m_Menu->OpeningClosing(l_mouse)){
				m_UIDisplay.SetFlag(UIDisplay::Flag_CO);
				m_UserInterface.CheckCurrentSlot();
			}
			if(m_Menu->GetEnable())
				m_UserInterface.SetVisible(false);
		}
		//メニューを開くor閉じる:右クリック(トリガー)
		if(data.m_MogllStatus.treasureStatus == -1 && GameInput::GetInstance().GetMouse(GameInput::MouseRightTrg)){
			if(m_Menu->OpeningClosing()){
				m_UIDisplay.SetFlag(UIDisplay::Flag_CO);
				m_UserInterface.CheckCurrentSlot();
			}
			if(m_Menu->GetEnable())
				m_UserInterface.SetVisible(false);
		}
	}

	//メニュー更新
	if( !m_UserInterface.GetEsFlg() )// エスケープ確認画面の時は処理しない
	{
		m_Menu->Update();
	}
	m_UIDisplay.Update();
	if(!m_Menu->GetEnable())
		m_UserInterface.SetVisible(true);
	//フィールドエフェクト更新
	m_UserInterface.UpdateEffect();
	// ライフメーター更新
	m_UserInterface.UpdateLife();

	// 脱出フラグ更新(バグ回避用)
	m_EscapeFlag = m_UserInterface.GetEsFlg();
	//脱出ボタン更新
	//if( !m_Menu->GetEnable() && m_HelpFlg == false){
	if( m_HelpFlg == false && !m_Menu->GetConfirmationFlag() && !m_Menu->GetFirstProduction() && !m_Menu->GetProduction()){
		m_UserInterface.UpdateButton();
	}
	if(m_UserInterface.GetOutFlg())	// 脱出
	{
		data.m_SceneInt["BackST"] = GAME_SCENE_PLAY;
		data.m_MogllStatus.frameSkip = 0;
		return GAME_SCENE_STAGESELECT;
	}
	if(m_UserInterface.GetRetryFlg()){	// リトライ
		return GAME_SCENE_PLAY;
	}
	// ゲームスタート更新
	if(m_HelpFlg == false && m_EscapeFlag == false)
		m_DepthSelect.Update(m_Menu->GetEnable());

	if( m_DepthSelect.IsEnable() )
	{
		//ブロック破壊
		m_BreakBlock.Update();
		return GAME_SCENE_THIS;
	}
	// お宝を取得していたら処理する
	if( data.m_MogllStatus.treasureStatus != -1)
	{
		if( m_SoundTime == 0 )
		{
			PlaySoundMem( data.Get( DataManager::SoundSE01 ), DX_PLAYTYPE_BACK);
			m_SoundTime++;
			// 今回のアイテムを取得済みにする
			for( int i = 0; i < 50; i++ )
			{
				if( data.m_SystemData.treasure[i].id == data.m_MogllStatus.treasureStatus )
				{
					data.m_SaveData.stageItemStatus[ i ] = 1;
					break;
				}
			}
			if( data.m_MogllStatus.treasureStatus == 59 )
			{
				data.m_SaveData.stageItemStatus[50] = 1;
			}
		}
		if(m_TreasureEffect.Update())
		{
			m_SoundTime = 0;
		}
		return GAME_SCENE_THIS;
	}
	////ゲット後ツリー演出
	//if( data.m_MogllStatus.treasureStatus != -1){
	//	//m_AfterGetTree.Update();
	//	m_AfterGetItem.Update();
	//	return GAME_SCENE_THIS;
	//}

	// 耐久値が無くなったらゲームオーバー
	GameInput &input = GameInput::GetInstance();
	if( data.m_MogllStatus.life <= 0 && EquipmentFunction_46())
	{
		if( m_SoundTime == 0 )
		{
			PlaySoundMem( data.Get( DataManager::SoundBGM10 ), DX_PLAYTYPE_BACK);
			m_SoundTime++;
		}
		m_GameOver.Update();
		if( m_GameOver.IsEnd() )
		{
			// 深度を記録
			int depth = static_cast<int>( BlockManager::GetInstance().GetDepth() );
			if( depth > data.m_SaveData.stageDepth[ data.m_SceneInt["StageNo"] ] )
			{
				data.m_SaveData.stageDepth[ data.m_SceneInt["StageNo"] ] = depth;
			}
			data.m_SceneInt["BackST"] = GAME_SCENE_PLAY;
			data.m_MogllStatus.frameSkip = 0;
			return GAME_SCENE_STAGESELECT;
		}
		return GAME_SCENE_THIS;
	}

	// 現在の深度が最下層を超えるとゲームクリア
	if(HIERARCHY[data.m_SceneInt["StageNo"]].Hier[HIERARCHY[data.m_SceneInt["StageNo"]].H_num-1] <= BlockManager::GetInstance().GetDepth()){
		if( m_SoundTime == 0 )
		{
			//ステージBGMをストップ
			switch( data.m_SceneInt["StageNo"] )
			{
			case 0:
				StopSoundMem( data.Get( DataManager::SoundBGM04 ));
				break;
			case 1:
				StopSoundMem( data.Get( DataManager::SoundBGM05 ));
				break;
			case 2:
				StopSoundMem( data.Get( DataManager::SoundBGM06 ));
				break;
			case 3:
				StopSoundMem( data.Get( DataManager::SoundBGM07 ));
				break;
			case 4:
				StopSoundMem( data.Get( DataManager::SoundBGM08 ));
				break;
			default:
				break;
			}
			PlaySoundMem( data.Get( DataManager::SoundBGM09 ), DX_PLAYTYPE_BACK);
			m_SoundTime++;
		}
		m_GameClear.Update();
		if( m_GameClear.IsEnd() )
		{
			data.m_SceneInt["BackST"] = GAME_SCENE_PLAY;
			data.m_MogllStatus.frameSkip = 0;
			return GAME_SCENE_STAGESELECT;
		}
		return GAME_SCENE_THIS;
	}

	if( !m_Menu->GetEnable() && m_HelpFlg == false && m_EscapeFlag == false  && !m_Menu->GetConfirmationFlag() && !m_Menu->GetProduction())
	{
		// 入力更新
		m_UserInterface.Update();

		// ブロック更新
		BlockManager::GetInstance().Update();

		// ユニット更新
		UnitManager::GetInstance().Update();

		// 地面を掘る
		m_Dig.Update();

		//ブロック破壊
		m_BreakBlock.Update();

		// タスク更新
		TaskManager::GetInstance().Update();

		AutoSkill();

	}

	// 無敵時間減少
	if( data.m_MogllStatus.noHitTime )
	{
		data.m_MogllStatus.noHitTime--;
	}
	data.m_MogllStatus.frameSkip = 1;
	m_FrameCount++;
	return GAME_SCENE_THIS;

}

void GameScenePlay::AutoSkill(void)
{
	EquipmentFunction_02( m_FrameCount );
	EquipmentFunction_13( m_FrameCount );
	EquipmentFunction_14_Dec( m_FrameCount );
	EquipmentFunction_33( m_FrameCount );
	EquipmentFunction_44( m_FrameCount );
	EquipmentFunction_48( m_FrameCount );
	EquipmentFunction_49( m_FrameCount );
	EquipmentFunction_50( m_FrameCount );
	EquipmentFunction_54( m_FrameCount );
	EquipmentFunction_58( m_FrameCount );
	EquipmentFunction_59( m_FrameCount );
	EquipmentFunction_03();
	EquipmentFunction_60();
	// 自動回復
	if( m_FrameCount % 30 == 0)
	{
		DataManager::GetInstance().m_MogllStatus.resource++;
	}
}
