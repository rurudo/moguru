#include "DxLib.h"
#include "Game/GameMain.h"
#include "Game/System/DataManager.h"

// デバッグ用
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
// デバッグ用終わり

//  プログラムは WinMain から始まります
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
						LPSTR lpCmdLine, int nCmdShow )
{
	// メモリリーク検知
#if defined(DEBUG) | defined(_DEBUG)
    _CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	//_CrtSetBreakAlloc( 3421 );//何回目の呼び出しでbreakするか
#endif
	//===========================================
	//初期化処理
	//DXライブラリ初期化
	ChangeWindowMode(TRUE);					// ウィンドウモードに設定
	// DXアーカイブで圧縮したファイルの拡張子を設定 : 未設定(dxa)
	SetDXArchiveExtension( "dat" ) ;
	// DXアーカイブで圧縮した時に設定したパスワードを指定
	SetDXArchiveKeyString("S3tKuIs800");
	SetOutApplicationLogValidFlag(FALSE);	// ログを出力しない
	SetWindowIconID( 101 );					// アイコンID
	SetMainWindowText("モグル") ;			// ウィンドウタイトル
	SetGraphMode(800, 600, 32);
	if( DxLib_Init() == -1 )				// ＤＸライブラリ初期化処理
		return -1 ;							// エラーが起きたら直ちに終了
	SetDrawScreen( DX_SCREEN_BACK );		// バックバッファ
	//ゲーム初期化
	GameMain gameMain;
	gameMain.Init();
	
	//===========================================
	//ゲームループ
	while(1)
	{
		// メッセージループに代わる処理をする
		if( ProcessMessage()  == -1 ||
			CheckHitKey(KEY_INPUT_ESCAPE) == 1 ||
			gameMain.Update() == -1)
		{
			break ;		// エラーが起きたらループを抜ける
		}
	}
	
	//===========================================
	//終了処理
	gameMain.Release();
	DataManager::GetInstance().SaveData();
	DataManager::GetInstance().MemRelease();
	DxLib_End() ;				// ＤＸライブラリ使用の終了処理

	return 0 ;				// ソフトの終了 
}