#pragma once
#include "CustomUserInterface.h"
#include "DxLibMath.h"
#include "../Block/CreateBlock.h"
#include "../Block/BreakBlock.h"
#include <map>
#include <list>
#include <vector>
// �u���b�N���W�n�Ƃ̓u���b�N�P�̒�����1.0f�Ƃ������W�n
class BlockManager
{
public:
	static const int HEIGHT_NUM_BLOCK = 13;
private:
	static const int BLOCK_ID_OFFSET = 1000;
	static const int WIDTH_NUM_BLOCK = 15;
	VECTOR m_Position;		// UI�ݒu�ʒu
	VECTOR m_Size;			// UI�T�C�Y
	VECTOR m_BlockSize;		// �u���b�N1�̃T�C�Y
	int m_Depth;			// �[�x
	int m_DepthOffset;		// �u���b�N�\����ʒu
	float m_DepthFloat;		// ���r���[�Ȑ[�x(�����l�ȉ��̐[�x�j
	float m_AddDepth;		// �[�x�X�V��
	int m_TopLine;			// ���݂̃u���b�N���X�g�̈�ԏ�̃C���f�b�N�X
	std::map<int, BlockBase*> m_BlockContainer;
	// ���^�[���p��list
	std::list<BlockBase*> m_ReturnBuffer;
	// �ǂݍ��ރ}�b�v�f�[�^�i�[�ʒu
	struct MapHeader
	{
		int x, y;
	}m_MapHeader;
	char *m_MapData;
	// �G�̃f�[�^�ǂݍ��ݐ�
	struct EnemyData
	{
		int x, y, id;
	};
	std::vector<EnemyData*> m_EnemyData;
	int m_EnemyCount;						// �o���������G�̐�

	CustomUserInterface m_MapUI;
	BreakBlock* m_pBreakBlock;
	BlockBase* m_BlockMap[ WIDTH_NUM_BLOCK ][ HEIGHT_NUM_BLOCK+1 ];
	// �w�肵��ID�̃u���b�N�����蓖�Ă�
	BlockBase* CreateBlock(int id);
	void LoadLineCalc(int num);
	void DrawBlockFrame(char *buf);
	// �v���C�x�[�g�R���X�g���N�^
	BlockManager(void);
public:
	~BlockManager(void);
	// �}�b�v�f�[�^�̓ǂݍ���
	void LoadBinary(char *fileName);
	void LoadGraphic(char *fileName);
	// �G�f�[�^�̓ǂݍ���
	void LoadEnemyGraphic(char *fileName);
	// depth�}�X�}�b�v��ǂݐi�߂�
	void AddDepth(float depth);
	void Draw(void);
	void Update(void);
	void Init(void);
	void Release(void);
	// �w��͈͓��̃u���b�N��Ԃ�(�u���b�N���W�n�j
	std::list<BlockBase*>& GetAreaBlock(float x, float y, float r);
	// �w��_�̃u���b�N��Ԃ��i�u���b�N���W�n�j
	BlockBase* GetBlock(float x, float y);
	// �w��_�����ԋ߂��u���b�N��Ԃ��B���ar���߂��u���b�N����������NULL��Ԃ�(�u���b�N���W�n�j
	BlockBase* GetNearBlock(const VECTOR &position, float r);
	// �w��n�_�����ԋ߂��ʍs�s�\�ȃu���b�N��Ԃ�
	BlockBase* GetNearHardBlock(const VECTOR &position, float r);
	// �w��̃u���b�N�̉�ʍ��W��Ԃ�
	void ConvertScreen( BlockBase* block, float *x, float *y );
	// �w�胉�C���̃f�[�^�����݂̃J�����g���C���Ƀ��[�h����
	// �����Ɉ�ԌÂ����C�����A�����[�h����
	// �w��̃��C�������[�h
	void LoadLine(int num);
	// ���̃��C�������[�h
	void LoadLine(void);
	// ���݂̐[�x��Ԃ�
	float GetDepth(void);
	// ���̃t���[���Ō@�����[�x��Ԃ�
	float GetOneFrameDepth(void);
	// �@�����[�xint��
	int GetDepthOffset(void);
	// �w��̍��W�̂���ID��Ԃ��B�Ȃ����-1, �Ώۂ��G�̏ꍇenemy=1,�u���b�N�̏ꍇenemy=0
	int GetTreasureID( int x, int y, int *enemy );
	// �w��̍��W�̓GID��Ԃ��B�Ȃ����-1
	int GetEnemyID( int x, int y );
	//�C���X�^���X�擾
	static BlockManager& GetInstance(void)
	{
		static BlockManager blockManager;
		return blockManager;
	}

	void SetBreakBlock(BreakBlock* pBreakBlock){
		m_pBreakBlock = pBreakBlock;
	}
};

