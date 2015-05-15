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
	// �L�^�t���O�������Ă���΋L�^�f�[�^�����o��
	if(m_InputStatus.Get(FLAG_INPUT_RESISTER))
	{
		m_ReplayHeader.buffer[0] = 'R';
		m_ReplayHeader.buffer[1] = 'E';
		m_ReplayHeader.buffer[2] = 'P';
		m_ReplayHeader.frame = m_Frame;
		FILE* fp;
		fopen_s( &fp, "replay.rep" , "wb" );
		fwrite( &m_ReplayHeader , sizeof( ReplayHeader ), 1, fp );
		// ���v���C�f�[�^�̏����o��
		for(int i = 0; i < m_ReplayHeader.frame / REPLAY_FRAME + 1; i++)
		{
			fwrite( m_replayRegister[i], sizeof( ReplayData ), REPLAY_FRAME, fp );
		}
		fclose( fp );
	}
	// ���v���C�f�[�^�̊J������
	while(m_replayRegister.size() > 0){
		ReplayData* data = m_replayRegister.back();
		delete[] data;
		m_replayRegister.pop_back();
	}
}

void GameInput::UpdateKeyboard(void)
{
	char buf[256];
	//���݂̏�Ԃ��擾
	GetHitKeyStateAll(buf);
		
	for(int i=0; i<256; i++)
	{
		//�g���K
		if(!m_KeyPrs[i] && buf[i] == 1)
			m_KeyTrg[i] = true;
		else
			m_KeyTrg[i] = false;

		//�����[�X
		if(m_KeyPrs[i] && buf[i] != 1)
			m_KeyRls[i] = true;
		else
			m_KeyRls[i] = false;

		//�v���X
		if(buf[i] == 1)
			m_KeyPrs[i] = true;
		else
			m_KeyPrs[i] = false;
	}
}

void GameInput::UpdateMouse(void)
{
	int input;
	// ���v���C�Đ����Ȃ�
	if(m_InputStatus.Get(FLAG_INPUT_AUTO))
	{
		ReadRegister(&input);
	}
	// ���͋L�^���Ȃ�
	else if(m_InputStatus.Get(FLAG_INPUT_RESISTER))
	{
		AddRegister(&input);
	}
	// ���v���C�֌W�̓�����s��Ȃ�
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
	//��
	//�g���K
	if(!m_MouseStatus[MouseLeftPrs] && (input & MOUSE_INPUT_LEFT))
		m_MouseStatus[MouseLeftTrg] = true;
	else
		m_MouseStatus[MouseLeftTrg] = false;
	//�����[�X
	if(m_MouseStatus[MouseLeftPrs] && !(input & MOUSE_INPUT_LEFT))
		m_MouseStatus[MouseLeftRls] = true;
	else
		m_MouseStatus[MouseLeftRls] = false;
	//�v���X
	if(input & MOUSE_INPUT_LEFT)
		m_MouseStatus[MouseLeftPrs] = true;
	else
		m_MouseStatus[MouseLeftPrs] = false;
	//�E
	//�g���K
	if(!m_MouseStatus[MouseRightPrs] && (input & MOUSE_INPUT_RIGHT))
		m_MouseStatus[MouseRightTrg] = true;
	else
		m_MouseStatus[MouseRightTrg] = false;
	//�����[�X
	if(m_MouseStatus[MouseRightPrs] && !(input & MOUSE_INPUT_RIGHT))
		m_MouseStatus[MouseRightRls] = true;
	else
		m_MouseStatus[MouseRightRls] = false;
	//�v���X
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
		// �t�@�C���������������̏���
	}
	else
	{
		// �t�@�C���ǂݍ��݂ƋL�^�������ɋN����Ȃ��悤�ɂ���
		m_InputStatus.Set(FLAG_INPUT_AUTO, false);
		// ���v���C�f�[�^��ǂݏo��
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
	// ���v���C�t�@�C����ǂݍ���ł��Ȃ��Ȃ�L�^��ԂɕύX
	if(!m_InputStatus.Get(FLAG_INPUT_AUTO))
	{
		m_InputStatus.Set(FLAG_INPUT_RESISTER, true);
		// ���v���C�L�^���̃Z�[�u�f�[�^�����v���C�f�[�^�ɕۑ�
		memcpy( &m_ReplayHeader.saveData.header[0], &DataManager::GetInstance().m_SaveData.header[0], sizeof(StoreData) );
	}
}

void GameInput::AddRegister(int *input)
{
	DXLibMath::GetMousePointResize(&m_MouseX, &m_MouseY);
	// �L�^�̈悪�Ȃ��Ȃ�����ǉ��Ŋm�ۂ���
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
		// �͈͊O�ɓ��B������蓮�ɐؑ�
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