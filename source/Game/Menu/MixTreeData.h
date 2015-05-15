//========================================================================
//	@file	MixTreeData.h
//	@brief	�������c���[�f�[�^
//========================================================================
#pragma once
#include "MenuStruct.h"
#include "../System/DataManager.h"

//�^�C�v
enum Type
{
	None=-1,										//�Ȃ���
	Equipment,										//����
	Unit,											//���j�b�g
};

typedef struct{
	TreeData		main;
	TreeData		Material[4];
}MixTreeData;

static const char	N = -1;							//�Ȃ����̐��l
static const char	cm_MixTreeNum	= 36;			//�����c���[��

//N,N,N,GameMenu::None

//�������X�g
static const MixTreeData m_MixTreeData[cm_MixTreeNum] = 
{
	//���ʕ��X�e�[�^�X(ID,Type):�K�v�f��1,�K�v�f��2,�K�v�f��3,�K�v�f��4
	//{{{id.x,id.y,id.z},type},{{{id.x,id.y,id.z},type},{{id.x,id.y,id.z},type},{{id.x,id.y,id.z},type}}}
	{ 10,	Unit		,  1,Equipment	,  3,Equipment	,  N,None		,  N,None		},		// 0�Z���O��				:���j�b�g
	{ 11,	Unit		, 10,Unit		,  0,Unit		,  N,None		,  N,None		},		// 1�Z�g���W���[			:���j�b�g
	{  2,	Unit		,  5,Equipment	, 23,Equipment	,  N,None		,  N,None		},		// 2�����O��				:���j�b�g
	{ 14,	Unit		,  7,Equipment	, 35,Equipment	,  N,None		,  N,None		},		// 3���O���\���W���[		:���j�b�g
	{  8,	Unit		, 30,Equipment	, 43,Equipment	,  N,None		,  N,None		},		// 4�h���h��				:���j�b�g
	{  9,	Unit		,  2,Equipment	, 50,Equipment	,  N,None		,  N,None		},		// 5�t���[�����			:���j�b�g
	{ 24,	Equipment	,  1,Unit		, 27,Equipment	,  N,None		,  N,None		},		// 6������				:����
	{ 21,	Equipment	, 31,Equipment	,  8,Equipment	,  N,None		,  N,None		},		// 7�r������				:����
	{ 25,	Unit		, 24,Unit		, 15,Equipment	,  N,None		,  N,None		},		// 8�e�B���m				:���j�b�g
	{ 27,	Unit		, 26,Unit		, 20,Equipment	,  N,None		,  N,None		},		// 9�N���[�P��			:���j�b�g
	{ 28,	Unit		, 41,Equipment	, 33,Equipment	,  N,None		,  N,None		},		// 10�N���b�N���r�b�g		:���j�b�g
	{ 18,	Unit		, 14,Unit		, 21,Equipment	,  N,None		,  N,None		},		// 11�E��					:���j�b�g
	{ 26,	Unit		,  8,Unit		,  1,Equipment	,  N,None		,  N,None		},		// 12�X���C��				:���j�b�g
	{ 49,	Equipment	, 18,Unit		, 57,Equipment	,  N,None		,  N,None		},		// 13�S�ŌM��				:����
	{ 12,	Unit		, 10,Unit		, 44,Equipment	, 47,Equipment	,  N,None		},		// 14�f�J���O��			:���j�b�g
	{ 13,	Unit		, 13,Equipment	, 37,Equipment	, 11,Equipment	,  N,None		},		// 15�X�y�[�X���O��		:���j�b�g
	{ 24,	Unit		, 32,Equipment	, 11,Equipment	, 52,Equipment	,  N,None		},		// 16�z���[����			:���j�b�g
	{  6,	Unit		,  2,Unit		, 55,Equipment	, 14,Equipment	,  N,None		},		// 17�T���}���_�[			:���j�b�g
	{ 57,	Equipment	,  2,Unit		, 40,Equipment	, 25,Equipment	,  N,None		},		// 18����{�f�B			:����
	{ 58,	Equipment	, 57,Equipment	, 28,Equipment	, 15,Equipment	,  N,None		},		// 19�l�H���z				:����
	{  7,	Unit		, 14,Unit		,  5,Equipment	,  6,Equipment	,  N,None		},		// 20���@���O��			:���j�b�g
	{ 36,	Equipment	,  7,Unit		, 34,Equipment	, 46,Equipment	,  N,None		},		// 21���@�҃V���{��		:����
	{ 22,	Equipment	,  9,Unit		, 29,Equipment	, 28,Equipment	,  N,None		},		// 22�X��					:����
	{ 15,	Unit		,  8,Unit		, 22,Equipment	, 26,Equipment	,  N,None		},		// 23�t���[�����EX		:���j�b�g
	{ 56,	Equipment	,  8,Unit		, 48,Equipment	, 39,Equipment	,  N,None		},		// 24�ʎq���[�v���u		:����
	{ 15,	Equipment	, 24,Equipment	, 14,Equipment	, 31,Equipment	,  N,None		},		// 25�鉤�̐S				:����
	{ 19,	Unit		, 24,Equipment	, 54,Equipment	, 18,Equipment	,  N,None		},		// 26�p���`���O��			:���j�b�g
	{  3,	Unit		, 19,Unit		, 17,Equipment	, 19,Equipment	,  N,None		},		// 27���e���O��			:���j�b�g
	{ 23,	Unit		, 22,Unit		, 45,Equipment	, 53,Equipment	,  N,None		},		// 28�K�[�f�B�A��			:���j�b�g
	{  4,	Unit		, 12,Unit		,  0,Unit		,  9,Equipment	, 10,Equipment	},		// 29�����O��				:���j�b�g
	{ 16,	Unit		,  7,Unit		, 16,Equipment	, 12,Equipment	, 45,Equipment	},		// 30�n�ꉤ				:���j�b�g
	{ 17,	Unit		, 16,Unit		, 15,Unit		, 42,Equipment	, 15,Equipment	},		// 31�w��					:���j�b�g
	{ 21,	Unit		,  3,Unit		, 40,Equipment	, 41,Equipment	, 51,Equipment	},		// 32�{���{����			:���j�b�g
	{ 22,	Unit		, 19,Unit		, 38,Equipment	, 34,Equipment	,  6,Equipment	},		// 33�E�҃��O��			:���j�b�g
	{  5,	Unit		,  4,Unit		, 13,Unit		, 25,Equipment	,  0,Equipment	},		// 34�M�����N�V�[���O��	:���j�b�g
	{ 20,	Unit		, 14,Unit		, 21,Equipment	, 19,Equipment	, 17,Equipment	}		// 35�d�C���O��			:���j�b�g
};

//�� �����C���[�W
static const char EquipItemImageList[60] = 
{
	DataManager::EI_IMAGE_Gear,
	DataManager::EI_IMAGE_Gear,
	DataManager::EI_IMAGE_Gear,
	DataManager::EI_IMAGE_Iron,
	DataManager::EI_IMAGE_Iron,
	DataManager::EI_IMAGE_Drill,
	DataManager::EI_IMAGE_Gear,
	DataManager::EI_IMAGE_Circuit,
	DataManager::EI_IMAGE_Circuit,
	DataManager::EI_IMAGE_Circuit,
	
	DataManager::EI_IMAGE_Iron,
	DataManager::EI_IMAGE_Circuit,
	DataManager::EI_IMAGE_Gear,
	DataManager::EI_IMAGE_Iron,
	DataManager::EI_IMAGE_Circuit,
	DataManager::EI_IMAGE_Circuit,
	DataManager::EI_IMAGE_Drill,
	DataManager::EI_IMAGE_Sword,
	DataManager::EI_IMAGE_Iron,
	DataManager::EI_IMAGE_Sword,
	
	DataManager::EI_IMAGE_Orb,
	DataManager::EI_IMAGE_Orb,
	DataManager::EI_IMAGE_Orb,
	DataManager::EI_IMAGE_Orb,
	DataManager::EI_IMAGE_Orb,
	DataManager::EI_IMAGE_Iron,
	DataManager::EI_IMAGE_Orb,
	DataManager::EI_IMAGE_Gear,
	DataManager::EI_IMAGE_Gear,
	DataManager::EI_IMAGE_Gear,
	
	DataManager::EI_IMAGE_Orb,
	DataManager::EI_IMAGE_Circuit,
	DataManager::EI_IMAGE_Gear,
	DataManager::EI_IMAGE_Circuit,
	DataManager::EI_IMAGE_Drill,
	DataManager::EI_IMAGE_Circuit,
	DataManager::EI_IMAGE_Medal,
	DataManager::EI_IMAGE_Iron,
	DataManager::EI_IMAGE_Iron,
	DataManager::EI_IMAGE_Gear,
	
	DataManager::EI_IMAGE_Gear,
	DataManager::EI_IMAGE_Gear,
	DataManager::EI_IMAGE_Gear,
	DataManager::EI_IMAGE_Gear,
	DataManager::EI_IMAGE_Gear,
	DataManager::EI_IMAGE_Gear,
	DataManager::EI_IMAGE_Circuit,
	DataManager::EI_IMAGE_Gear,
	DataManager::EI_IMAGE_Gear,
	DataManager::EI_IMAGE_Medal,
	
	DataManager::EI_IMAGE_Circuit,
	DataManager::EI_IMAGE_Orb,
	DataManager::EI_IMAGE_Gear,
	DataManager::EI_IMAGE_Sword,
	DataManager::EI_IMAGE_Orb,
	DataManager::EI_IMAGE_Iron,
	DataManager::EI_IMAGE_Gear,
	DataManager::EI_IMAGE_Iron,
	DataManager::EI_IMAGE_Sword,
	DataManager::EI_IMAGE_Medal
};

//========================================================================
//	End of file
//========================================================================