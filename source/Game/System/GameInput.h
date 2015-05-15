#pragma once
#include "DxLib.h"
#include "BoolArray.h"
#include "StoreData.h"
#include <vector>
//入力取得クラス
class GameInput
{
public:
	enum MouseStatus
	{
		MouseLeftPrs,
		MouseLeftTrg,
		MouseLeftRls,
		MouseRightPrs,
		MouseRightTrg,
		MouseRightRls,
		MouseStatusMax
	};
private:
	enum InputStatus
	{
		FLAG_INPUT_AUTO,		// 入力データを外部から利用するか
		FLAG_INPUT_RESISTER	// 入力データを記録するか
	};
	GameInput(void);
	bool	m_KeyPrs[256];
	bool	m_KeyTrg[256];
	bool	m_KeyRls[256];
	double	m_MouseX, m_MouseY;
	bool	m_MouseStatus[MouseStatusMax];
	bool	m_MouseWheelMove[2];
	int		m_MouseWheelRotVol;

	// 入力リプレイ関係
	// リプレイヘッダ
	int m_Frame;			// 現在のフレーム
	static const int REPLAY_FRAME = 1000;
	struct ReplayHeader
	{
		char buffer[32];		// メモとか
		int frame;				// 総フレーム数
		unsigned int seed;		// 乱数生成シード値
		StoreData saveData;		// セーブデータ
	}m_ReplayHeader;
	// 1フレーム辺りのデータ
	struct ReplayData
	{
		float x, y;
		int input;
	};
	BoolArray m_InputStatus;
	std::vector<ReplayData*> m_replayRegister;	// リプレイデータの記録先
	// データを記録する
	void AddRegister(int *input);
	// データを読み出す
	void ReadRegister(int *input);
public:
	~GameInput(void);
	//初期化
	void Init(void)
	{
		for(int i=0; i<256; i++)
			m_KeyPrs[i] = m_KeyTrg[i] = m_KeyRls[i] = false;
	}
	//入力状態取得
	bool GetKeyPrs(int KeyCode)
	{
		return m_KeyPrs[ KeyCode ];
	}
	bool GetKeyTrg(int KeyCode)
	{
		return m_KeyTrg[ KeyCode ];
	}
	bool GetKeyRls(int KeyCode)
	{
		return m_KeyRls[ KeyCode ];
	}
	// 左上(0.0)、右下(1.0)としたdouble値を返す
	double GetX(void)
	{
		return m_MouseX;
	}
	double GetY(void)
	{
		return m_MouseY;
	}
	// floatが欲しい時
	float GetXf(void)
	{
		return static_cast<float>(m_MouseX);
	}
	float GetYf(void)
	{
		return static_cast<float>(m_MouseY);
	}
	// マウスの入力状態取得
	bool GetMouse(MouseStatus index)
	{
		return m_MouseStatus[index];
	}
	// リプレイファイルの読み込み
	void LoadAutoInputFile(char* fileName);
	// リプレイを記録する
	void SaveAutoInputFile(void);
	//更新
	void Update(void);
	void UpdateKeyboard(void);
	void UpdateMouse(void);
	//インスタンス取得
	static GameInput& GetInstance(void)
	{
		static GameInput gameInput;
		return gameInput;
	}
	void DrawReplayFrame(void);
	int GetFrame(void)
	{
		return m_Frame;
	}
	int GetMouseWheelUp( void )
	{
		return m_MouseWheelMove[0];
	}
	int GetMouseWheelDown( void )
	{
		return m_MouseWheelMove[1];
	}
};
