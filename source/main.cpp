#include "DxLib.h"
#include "Game/GameMain.h"
#include "Game/System/DataManager.h"

// �f�o�b�O�p
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
// �f�o�b�O�p�I���

//  �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
						LPSTR lpCmdLine, int nCmdShow )
{
	// ���������[�N���m
#if defined(DEBUG) | defined(_DEBUG)
    _CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	//_CrtSetBreakAlloc( 3421 );//����ڂ̌Ăяo����break���邩
#endif
	//===========================================
	//����������
	//DX���C�u����������
	ChangeWindowMode(TRUE);					// �E�B���h�E���[�h�ɐݒ�
	// DX�A�[�J�C�u�ň��k�����t�@�C���̊g���q��ݒ� : ���ݒ�(dxa)
	SetDXArchiveExtension( "dat" ) ;
	// DX�A�[�J�C�u�ň��k�������ɐݒ肵���p�X���[�h���w��
	SetDXArchiveKeyString("S3tKuIs800");
	SetOutApplicationLogValidFlag(FALSE);	// ���O���o�͂��Ȃ�
	SetWindowIconID( 101 );					// �A�C�R��ID
	SetMainWindowText("���O��") ;			// �E�B���h�E�^�C�g��
	SetGraphMode(800, 600, 32);
	if( DxLib_Init() == -1 )				// �c�w���C�u��������������
		return -1 ;							// �G���[���N�����璼���ɏI��
	SetDrawScreen( DX_SCREEN_BACK );		// �o�b�N�o�b�t�@
	//�Q�[��������
	GameMain gameMain;
	gameMain.Init();
	
	//===========================================
	//�Q�[�����[�v
	while(1)
	{
		// ���b�Z�[�W���[�v�ɑ��鏈��������
		if( ProcessMessage()  == -1 ||
			CheckHitKey(KEY_INPUT_ESCAPE) == 1 ||
			gameMain.Update() == -1)
		{
			break ;		// �G���[���N�����烋�[�v�𔲂���
		}
	}
	
	//===========================================
	//�I������
	gameMain.Release();
	DataManager::GetInstance().SaveData();
	DataManager::GetInstance().MemRelease();
	DxLib_End() ;				// �c�w���C�u�����g�p�̏I������

	return 0 ;				// �\�t�g�̏I�� 
}