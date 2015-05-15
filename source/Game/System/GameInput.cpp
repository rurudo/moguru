#include "GameInput.h"
#include "DxLibMath.h"
#include "DataManager.h"
#include <time.h>

GameInput::GameInput(void)
{
	m_InputStatus.Set(FLAG_INPUT_AUTO, false);
	m_Frame = 0;
	m_ReplayHeader.seed = static_cast<unsigned int>(time(NULL));
	SRand(m_ReplayHeader.seed);
}

GameInput::~GameInput(void)
{
	// 記録フラグが立っていれば記録データ書き出し
	if(m_InputStatus.Get(FLAG_INPUT_RESISTER))
	{
		m_ReplayHeader.buffer[0] = 'R';
		m_ReplayHeader.buffer[1] = 'E';
		m_ReplayHeader.buffer[2] = 'P';
		m_ReplayHeader.frame = m_Frame;
		FILE* fp;
		fopen_s( &fp, "replay.rep" , "wb" );
		fwrite( &m_ReplayHeader , sizeof( ReplayHeader ), 1, fp );
		// リプレイデータの書き出し
		for(int i = 0; i < m_ReplayHeader.frame / REPLAY_FRAME + 1; i++)
		{
			fwrite( m_replayRegister[i], sizeof( ReplayData ), REPLAY_FRAME, fp );
		}
		fclose( fp );
	}
	// リプレイデータの開放処理
	while(m_replayRegister.size() > 0){
		ReplayData* data = m_replayRegister.back();
		delete[] data;
		m_replayRegister.pop_back();
	}
}

void GameInput::UpdateKeyboard(void)
{
	char buf[256];
	//現在の状態を取得
	GetHitKeyStateAll(buf);
		
	for(int i=0; i<256; i++)
	{
		//トリガ
		if(!m_KeyPrs[i] && buf[i] == 1)
			m_KeyTrg[i] = true;
		else
			m_KeyTrg[i] = false;

		//リリース
		if(m_KeyPrs[i] && buf[i] != 1)
			m_KeyRls[i] = true;
		else
			m_KeyRls[i] = false;

		//プレス
		if(buf[i] == 1)
			m_KeyPrs[i] = true;
		else
			m_KeyPrs[i] = false;
	}
}

void GameInput::UpdateMouse(void)
{
	int input;
	// リプレイ再生中なら
	if(m_InputStatus.Get(FLAG_INPUT_AUTO))
	{
		ReadRegister(&input);
	}
	// 入力記録中なら
	else if(m_InputStatus.Get(FLAG_INPUT_RESISTER))
	{
		AddRegister(&input);
	}
	// リプレイ関係の動作を行わない
	else
	{
		DXLibMath::GetMousePointResize(&m_MouseX, &m_MouseY);
		input = GetMouseInput();
	}
	int oldMouseWheel = m_MouseWheelRotVol;
	m_MouseWheelMove[0] = false;
	m_MouseWheelMove[1] = false;
	m_MouseWheelRotVol = GetMouseWheelRotVol();
	if( m_MouseWheelRotVol != oldMouseWheel)
	{
		if( m_MouseWheelRotVol == 1 )
		{
			m_MouseWheelMove[0] = true;
		}
		else if( m_MouseWheelRotVol == -1 )
		{
			m_MouseWheelMove[1] = true;
		}
	}
	//左
	//トリガ
	if(!m_MouseStatus[MouseLeftPrs] && (input & MOUSE_INPUT_LEFT))
		m_MouseStatus[MouseLeftTrg] = true;
	else
		m_MouseStatus[MouseLeftTrg] = false;
	//リリース
	if(m_MouseStatus[MouseLeftPrs] && !(input & MOUSE_INPUT_LEFT))
		m_MouseStatus[MouseLeftRls] = true;
	else
		m_MouseStatus[MouseLeftRls] = false;
	//プレス
	if(input & MOUSE_INPUT_LEFT)
		m_MouseStatus[MouseLeftPrs] = true;
	else
		m_MouseStatus[MouseLeftPrs] = false;
	//右
	//トリガ
	if(!m_MouseStatus[MouseRightPrs] && (input & MOUSE_INPUT_RIGHT))
		m_MouseStatus[MouseRightTrg] = true;
	else
		m_MouseStatus[MouseRightTrg] = false;
	//リリース
	if(m_MouseStatus[MouseRightPrs] && !(input & MOUSE_INPUT_RIGHT))
		m_MouseStatus[MouseRightRls] = true;
	else
		m_MouseStatus[MouseRightRls] = false;
	//プレス
	if(input & MOUSE_INPUT_RIGHT)
		m_MouseStatus[MouseRightPrs] = true;
	else
		m_MouseStatus[MouseRightPrs] = false;
}

void GameInput::Update(void)
{
	UpdateKeyboard();
	UpdateMouse();
	m_Frame++;
}

void GameInput::LoadAutoInputFile(char* fileName)
{
	FILE* fp;
	if(fopen_s(&fp, fileName, "rb") != 0)
	{
		// ファイルが無かった時の処理
	}
	else
	{
		// ファイル読み込みと記録が同時に起こらないようにする
		m_InputStatus.Set(FLAG_INPUT_AUTO, false);
		// リプレイデータを読み出し
		fread( &m_ReplayHeader , sizeof( ReplayHeader ), 1, fp );
		for(int i = 0; i < 1 + m_ReplayHeader.frame / REPLAY_FRAME; i++)
		{
			m_replayRegister.push_back(new ReplayData[REPLAY_FRAME]);
			fread( m_replayRegister[i], sizeof(ReplayData), REPLAY_FRAME, fp);
		}
		fclose(fp);
		memcpy( &DataManager::GetInstance().m_SaveData.header[0], &m_ReplayHeader.saveData.header[0], sizeof(StoreData) );
		m_InputStatus.Set(FLAG_INPUT_AUTO, true);
	}
}

void GameInput::SaveAutoInputFile(void)
{
	// リプレイファイルを読み込んでいないなら記録状態に変更
	if(!m_InputStatus.Get(FLAG_INPUT_AUTO))
	{
		m_InputStatus.Set(FLAG_INPUT_RESISTER, true);
		// リプレイ記録時のセーブデータをリプレイデータに保存
		memcpy( &m_ReplayHeader.saveData.header[0], &DataManager::GetInstance().m_SaveData.header[0], sizeof(StoreData) );
	}
}

void GameInput::AddRegister(int *input)
{
	DXLibMath::GetMousePointResize(&m_MouseX, &m_MouseY);
	// 記録領域がなくなったら追加で確保する
	if(static_cast<int>(m_replayRegister.size()) <= m_Frame / REPLAY_FRAME)
	{
		m_replayRegister.push_back(new ReplayData[REPLAY_FRAME]);
	}
	m_replayRegister[m_Frame / REPLAY_FRAME][m_Frame % REPLAY_FRAME].x = static_cast<float>(m_MouseX);
	m_replayRegister[m_Frame / REPLAY_FRAME][m_Frame % REPLAY_FRAME].y = static_cast<float>(m_MouseY);
	*input = GetMouseInput();
	m_replayRegister[m_Frame / REPLAY_FRAME][m_Frame % REPLAY_FRAME].input = *input;
}

void GameInput::ReadRegister(int *input)
{
	if(m_Frame <= m_ReplayHeader.frame)
	{
		m_MouseX = static_cast<double>(m_replayRegister[m_Frame / REPLAY_FRAME][m_Frame % REPLAY_FRAME].x);
		m_MouseY = static_cast<double>(m_replayRegister[m_Frame / REPLAY_FRAME][m_Frame % REPLAY_FRAME].y);
		*input = m_replayRegister[m_Frame / REPLAY_FRAME][m_Frame % REPLAY_FRAME].input;
	}
	else
	{
		// 範囲外に到達したら手動に切替
		m_InputStatus.Set(FLAG_INPUT_AUTO, false);
		*input = GetMouseInput();
	}
}

void GameInput::DrawReplayFrame(void)
{
	if(m_InputStatus.Get(FLAG_INPUT_AUTO) && m_Frame <= m_ReplayHeader.frame)
	{
		DrawFormatString( 100, 0, GetColor(255, 255, 255), "%d / %d", m_Frame, m_ReplayHeader.frame);
	}
}