//========================================================================
//	@file		GameMenu.h
//	@note		�C���x���g��
//	@author		RyotaUehara
//	@version	1.0
//========================================================================
#pragma once
//------------------------------------------------------------------------
//	IncludeHeader
//------------------------------------------------------------------------
#include "../System/CustomUserInterface.h"
#include "../System/FontManager.h"
#include "../System/DataManager.h"
#include "Equip.h"
#include "ItemEquip.h"
#include "MixProduction.h"
#include "FirstMixProduction.h"
#include "UIDisplay.h"

typedef struct DiscriptData{
	IdData			id;			//�ǂ̃A�C�R�����̔ԍ�
	int				type;		//���������j�b�g��
	bool			flag;		//�\���t���O
}DiscriptData;

//------------------------------------------------------------------------
//	command name headerName
//	@Class GameMenu GameMenu.h
//	@brief �C���x���g��
//------------------------------------------------------------------------
class GameMenu
{
	//--------------------------------------------------------------------
	//	Member
	//--------------------------------------------------------------------
	private:
		bool					m_Enable;					//�L���t���O
		bool					m_Equip;					//�����t���O
		int						m_DescriptionFlag;			//�������p�̃t���O
		int						m_DescriptionSpan;			//�������\�����̃X�p��
		int						m_DescriptionColor;			//�������̐F
		int						m_DrawJudge[2];				//�`�掞�̃A�C�e���������Â����锻��l���X�g
		int						m_Drawsilhouette[1];		//�`�掞�̃A�C�e�����Â����锻��l���X�g
		unsigned int			m_NameCount;
		unsigned int			m_DescriptionCount;
		unsigned int			m_Step;						//�X�e�b�v���
		float					m_BackGroundPos;			//�C���x���g���w�i��x�ʒu

		DXLibMath::Vector2		m_Mouse;					//�}�E�X�ʒu
		DiscriptData			m_DescriptionData;			//�����p�f�[�^
		DiscriptData			m_MemDescriptionData;		//�����p�f�[�^
		DiscriptData			m_Material[4];				//

		CustomUserInterface		m_EquipmentUI;				//������
		CustomUserInterface		m_UnitUI;					//���j�b�g��
		CustomUserInterface		m_EquipmentIconUI;			//�����A�C�R��
		CustomUserInterface		m_UnitIconUI;				//���j�b�g�A�C�R��

		FontManager				m_FontManager;				//�Ǝ��t�H���g�A�������s�p
		Equip					m_EquipManager;				//���������N���X
		ItemEquip				m_ItemEquipManager;
		MixProduction			m_MixProduction;
		FirstMixProduction		m_FirstMixProduction;

		int						m_DebugNowGetID;
		int						*m_EquipmenthandleList;		//�����n���h�����X�g
		int						*m_UnithandleList;			//���j�b�g�n���h�����X�g
		int						*m_EquipmentFhandleList;	//�����i���n���h�����X�g
		int						*m_UnitFhandleList;			//���j�b�g���n���h�����X�g

		DataManager				*m_Data;

		static const float		cm_BackGroundLeftPos;		//�C���x���g���w�i�̊i�[���ʒu����
		static const float		cm_BackGroundXPos;			//�C���x���g���w�i�̕\��x�ʒu����
		static const float		cm_BackGroundYPos;			//�C���x���g���w�i�̕\��y�ʒu����
		static const float		cm_BackGroundMovement;		//�C���x���g���w�i�̈ړ�����
		static const float		cm_BackGroundWidth;			//�C���x���g���w�i�̕\��������
		static const float		cm_BackGroundHeight;		//�C���x���g���w�i�̕\����������

		static const float		cm_InventlyX;				//�C���x���g���J�p�摜x
		static const float		cm_InventlyY;				//�C���x���g���J�p�摜y
		static const float		cm_InventlyWidth;			//�C���x���g���J�p�摜��
		static const float		cm_InventlyHeight;			//�C���x���g���J�p�摜����
		
		static const float		cm_DescriptionFrameXPos;	//�����gx
		static const float		cm_DescriptionFrameYPos;	//�����gy
		static const float		cm_DescriptionFrameXMargin;	//�����gx�␳
		static const float		cm_DescriptionFrameYMargin;	//�����gy�␳
		static const float		cm_DescriptionFrameWidth;	//�����g��
		static const float		cm_DescriptionFrameHeight;	//�����g����

		static const float		cm_DescriptionNameMarginX;	//�������Ox�␳�l
		static const float		cm_DescriptionNameMarginY;	//�������Oy�␳�l
		static const float		cm_DescriptionMarginX;		//������x�␳�l
		static const float		cm_DescriptionMarginY;		//������y�␳�l

		static const float		cm_DescriptionNameSize;		//����:���O�̕����T�C�Y����
		static const float		cm_DescriptionSize;			//����:�������̕����T�C�Y����
		
		static const int		cm_NameSpan;			//
		static const int		cm_DescriptionSpan;			//

		//�X�e�b�v
		enum Step
		{
			In,												//�C���X�e�b�v
			Stay,											//�X�e�C�X�e�b�v
			Out,											//�A�E�g�X�e�b�v
		};

		enum Flag{
			Flag_Mix,										//��������
			Flag_Break,										//�������Ȃ���΂����Ȃ�
			Flag_Name,										//����:���O
			Flag_Description,								//����
			Flag_MixOK,										//
			Flag_Wait

		};
	public:
		static const float		cm_BackYMargin;				//�w�i�̃T�C�Y������ĂȂ��̂ŏ��������邽��
		
		static const float		cm_EquipmentUIXPos;			//���̕\��x�ʒu����
		static const float		cm_EquipmentUIWidth;			//���̕\��������

		static const float		cm_OneFrameWidth;			//��g�̕�
		static const float		cm_OneFrameHeight;			//��g�̍���

		static const float		cm_EquipmentUIYPos;			//�������̕\��y�ʒu����
		static const float		cm_EquipmentUIHeight;		//�������̕\����������

		static const float		cm_UnitUIXPos;				//���j�b�g���̕\��y�ʒu����
		static const float		cm_UnitUIYPos;				//���j�b�g���̕\��y�ʒu����
		static const float		cm_UnitUIHeight;			//���j�b�g���̕\����������

		static const int		cm_EquipmentHNum;			//�������s��
		static const int		cm_UnitHNum;				//���j�b�g���s��
		static const int		cm_ColumnVNum;				//����

		////�^�C�v
		//enum Type
		//{
		//	None=-1,										//�Ȃ���
		//	Equipment,										//����
		//	Unit,											//���j�b�g
		//};
	//--------------------------------------------------------------------
	//	Method
	//--------------------------------------------------------------------
	private:
		//�X���C�h�̃C������
		void SrideIn(void);
		//�X���C�h�̃C������
		void SrideOut(void);

		//�L�[����
		void KeyAction(void);

		//�A�C�R���}�E�X�I�[�o�[���̔��菈��
		void IconOver(void);
		//�I�[�o�[���̑����X���b�g
		void SetSlotOver(void);

		//�A�C�R���̕ύX
		void IconChange(void);
		//�A�C�R���̔���
		void EquipIconJudge(int num);

		//�A�C�e����ԃ`�F�b�N
		void ItemCheck(void);

		//��������
		bool Equip(int *Content,TreeData *Root);

		//�����E���j�b�g�̃X�e�[�^�X�̏���������:�f�o�b�O�p
		void ItemStatusReset(void);

		int GetMixTreeNum(int id,int type);
		int GetSortNum(int id,int type);
		
		void GetMaterialShine(int num);

		void DrawMaterialShine(void);
		void DrawStageMask(void);
		void DrawCanMixString(void);
		//�ʒu�m�F�p
		void DrawPosCheck(float x,float y,float w,float h);
		void DrawPosCheck(int x,int y,int w,int h);

		int ReverseGetID(int id,char type);

		int StrLength(const char *s);

		//�A�C�e��������Q�b�g
		void GetItem(void);
		//�A�C�e��������Q�b�g
		void GetMap(void);

	public:
		//================================================================
		//	Constructor
		//================================================================
		GameMenu(void);
		//�f�X�g���N�^
		virtual ~GameMenu(void);

		//����������
		void Init(void);
		//�X�V����
		void Update(void);
		//�`�揈��
		void Draw(void);
		//�������
		void Release(void);

		//�J����
		bool OpeningClosing(void);
		bool OpeningClosing(DXLibMath::Vector2 &mouse);

		//�L���E�����؂�ւ�
		void ChangeEnable(void);

		//================================================================
		//	Getter
		//================================================================
		bool GetEnable(void);

		bool GetConfirmationFlag(void){
			return m_EquipManager.GetConfirmationFlag();
		}

		bool GetFirstProduction(void){
			return m_FirstMixProduction.GetEnable();
		}
		bool GetProduction(void){
			return m_MixProduction.GetEnable();
		}

		// �������̃��j�b�g��ID��Ԃ�(int�U��)
		//void GetUnitEquipment(int *unitID);
};

//========================================================================
//	End of file
//========================================================================