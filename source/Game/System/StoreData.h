#pragma once

// �Z�[�u�f�[�^
struct StoreData
{
	char header[32];				// �w�b�_�[
	char itemStatus[60];			// �����̏����A�������A�������A�������̃X�e�[�^�X
	char unitStatus[30];			// ���j�b�g�̏����A�������A�������A�������̃X�e�[�^�X
	char stageItemStatus[51];		// �e�X�e�[�W�̕�擾��
	int stageDepth[5];				// �e�X�e�[�W�̍ő�[�x
	int equipItem[3];				// �������̑���
	int equipUnit[6];				// �������̃��j�b�g
	int playFrame;					// �v���C���ԁi�t���[���P�ʁj
	bool challengeFlag[100];		// �`�������W���ڒB���t���O
};