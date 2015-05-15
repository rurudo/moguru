#pragma once
#include "DxLib.h"
#include "BoolArray.h"
#include "StoreData.h"
#include <vector>
//���͎擾�N���X
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
		FLAG_INPUT_AUTO,		// ���̓f�[�^���O�����痘�p���邩
		FLAG_INPUT_RESISTER	// ���̓f�[�^���L�^���邩
	};
	GameInput(void);
	bool	m_KeyPrs[256];
	bool	m_KeyTrg[256];
	bool	m_KeyRls[256];
	double	m_MouseX, m_MouseY;
	bool	m_MouseStatus[MouseStatusMax];
	bool	m_MouseWheelMove[2];
	int		m_MouseWheelRotVol;

	// ���̓��v���C�֌W
	// ���v���C�w�b�_
	int m_Frame;			// ���݂̃t���[��
	static const int REPLAY_FRAME = 1000;
	struct ReplayHeader
	{
		char buffer[32];		// �����Ƃ�
		int frame;				// ���t���[����
		unsigned int seed;		// ���������V�[�h�l
		StoreData saveData;		// �Z�[�u�f�[�^
	}m_ReplayHeader;
	// 1�t���[���ӂ�̃f�[�^
	struct ReplayData
	{
		float x, y;
		int input;
	};
	BoolArray m_InputStatus;
	std::vector<ReplayData*> m_replayRegister;	// ���v���C�f�[�^�̋L�^��
	// �f�[�^���L�^����
	void AddRegister(int *input);
	// �f�[�^��ǂݏo��
	void ReadRegister(int *input);
public:
	~GameInput(void);
	//������
	void Init(void)
	{
		for(int i=0; i<256; i++)
			m_KeyPrs[i] = m_KeyTrg[i] = m_KeyRls[i] = false;
	}
	//���͏�Ԏ擾
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
	// ����(0.0)�A�E��(1.0)�Ƃ���double�l��Ԃ�
	double GetX(void)
	{
		return m_MouseX;
	}
	double GetY(void)
	{
		return m_MouseY;
	}
	// float���~������
	float GetXf(void)
	{
		return static_cast<float>(m_MouseX);
	}
	float GetYf(void)
	{
		return static_cast<float>(m_MouseY);
	}
	// �}�E�X�̓��͏�Ԏ擾
	bool GetMouse(MouseStatus index)
	{
		return m_MouseStatus[index];
	}
	// ���v���C�t�@�C���̓ǂݍ���
	void LoadAutoInputFile(char* fileName);
	// ���v���C���L�^����
	void SaveAutoInputFile(void);
	//�X�V
	void Update(void);
	void UpdateKeyboard(void);
	void UpdateMouse(void);
	//�C���X�^���X�擾
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
