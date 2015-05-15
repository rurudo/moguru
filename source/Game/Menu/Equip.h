//========================================================================
//	@file		Equip.h
//	@note		��������
//	@author		RyotaUehara
//	@version	1.0
//========================================================================
#pragma once
//------------------------------------------------------------------------
//	IncludeHeader
//------------------------------------------------------------------------
#include "MixTreeData.h"
#include "ItemEquip.h"

//------------------------------------------------------------------------
//	Const
//------------------------------------------------------------------------

//------------------------------------------------------------------------
//	Equip
//	@brief �����N���X
//------------------------------------------------------------------------
class Equip
{
	//--------------------------------------------------------------------
	//	Member
	//--------------------------------------------------------------------
	private:
		bool					m_End;						//�I���t���O
		bool					m_Check;					//�`�F�b�N�t���O
		bool					m_ConfirmationFlag;			//�����E�����m�F�t���O
		bool					m_HaveItem;					//�A�C�e���������Ă�����

		bool					m_Debug;					//

		int						m_OkCancel;					//�����E�����̉�
		int						m_ItemFlag;					//�A�C�e���̏����t���O

		int						m_EquipCount;
		int						m_UnitCount;

		int						m_ItemSlotPos;				//�E���X���b�g�I�[�o�[���A�C�R���X���b�g���o���Ƃ��̍��W

		DXLibMath::Vector2		m_Mouse;					//�}�E�X�ʒu
		EquipData				m_MixRoot;					//���������̃f�[�^
		EquipData				m_MixData;					//��������A�C�e���f�[�^
		EquipData				m_BreakData;				//��������A�C�e���f�[�^

		TreeData				m_EquipData;				//

		TreeData				m_memData;
		TreeData				m_memData2;

		EquipData				*m_EquipmentSlot;			//�����i�����X���b�g
		EquipData				*m_UnitSlot;				//���j�b�g�����X���b�g

		FontManager				m_FontManager;				//�Ǝ��t�H���g�A�������s�p

		ItemEquip				*m_ItemEquipManager;

		DataManager				*m_Data;

		static const int		cm_ItemSlotPosFrame;		//�E���̃X���b�g�I�[�o�[���p�t���[����

		static const float		cm_RootMixStrX;				//���[�g�����ߒ�����x���W
		static const float		cm_RootMixStrY;				//���[�g�����ߒ�����y���W
		static const float		cm_ProcessStrX;				//���[�g�����ߒ���������y���W
		static const float		cm_ProcessStrY;				//���[�g�����ߒ���������y���W
		static const float		cm_ProcessSupStrX;			//���[�g�����ߒ������⏕����y���W
		static const float		cm_ProcessSupStrY;			//���[�g�����ߒ������⏕����y���W
		static const float		cm_MaterialStrX;			//�f�ޕ���x���W
		static const float		cm_MaterialStrY;			//�f�ޕ���y���W
		static const float		cm_MaterialStrHeight;		//�f�ޕ�������
		static const float		cm_ClickIconX;				//�N���b�N�A�C�R��x���W
		static const float		cm_RClickIconX;				//�E�N���b�N�A�C�R��x���W
		static const float		cm_ClickIconY;				//�N���b�N�A�C�R��y���W
		static const float		cm_ClickIconWidth;			//�N���b�N�A�C�R����
		static const float		cm_ClickIconHeight;			//�N���b�N�A�C�R������
		static const float		cm_ClickIconSupX;			//�N���b�N�A�C�R���⏕����x���W
		static const float		cm_RClickIconSupX;			//�E�N���b�N�A�C�R���⏕����x���W
		static const float		cm_ClickIconSupY;			//�N���b�N�A�C�R���⏕����y���W

		enum Flag{
			None = -1,
			Flag_Mix,										//��������
			Flag_Break,										//�������Ȃ���΂����Ȃ�

			Flag_OK,										//OK
			Flag_Cancel										//�L�����Z��
		};

	public:
	//--------------------------------------------------------------------
	//	Method
	//--------------------------------------------------------------------
	private:
		//�ǂ̑����i�E���j�b�g�����f
		bool Judge(void);
		//�����ł��邩���f
		bool EquipJudge(void);
		//�����`�F�b�N
		bool EquipCheck(void);
		bool EquipCheck(EquipData data);
		//�����`�F�b�N
		bool MixCheck(void);
		//�n���ꂽID�̂��̂̎w�肳�ꂽ�f�ޔԍ������Ƃɒ��o���Ԃ�:�ċA����
		bool MinRankExtractionNum(EquipData root,EquipData artifacts,int matNum);
		//�f�ނ��獇����𒊏o:�ċA����
		bool OriginExtraction(EquipData artifacts);
		//��������
		void Mix(void);
		//��������
		void Break(void);

		//�����E�����m�F����
		bool Confirmation(void);

		//�����̊m�F
		void EquipConfirmation(void);
		//�����ς݃V���{���̕`�揈��
		void DrawEquipSymbol(void);
		//New�V���{���`��
		void DrawNewSymbol(void);
		//���݂���ł���A�C�R���`��
		void DrawHaveItem(void);
		//�I�[�o�[���̑����X���b�g�����点��
		void DrawSlotOver(void);

		//�����I���㏉����
		void Clear(void);

		//���O���̑����X�e�[�^�X���Z�b�g
		void SetMogllEquipStatus(void);
		void SetMogllEquipStatus(char type,int slotNum);

		//�\�[�g���ꂽ���X�g����t����
		int ReverseGetID(int id,char type);
	public:
		//================================================================
		//	Constructor
		//================================================================
		Equip(void);
		//�f�X�g���N�^
		virtual ~Equip(void);

		//����������
		void Init(void);
		//�X�V����
		bool Update(int *Content,TreeData *Root);
		//�`�揈��
		void Draw(void);
		//�X���b�g�̕`��
		void DrawSlot(void);
		void SymbolDraw(void);
		void OtherDraw(void);

		//�������
		void Release(void);

		//�f�o�b�O�p���Z�b�g
		void Reset(void);

		//�`�F�b�N�t���O�𗧂Ă�
		void CheckEnable(void);
		//����ł���A�C�e���̍폜
		void ResetHaveItem(void);
		//����ł���A�C�e���̍폜:�X���b�g���߂�
		void ResetHaveItem2(void);
		//�A�C�e�������N���X�ւ̃|�C���^���i�[
		void SetItemEquip(ItemEquip* instance);

		bool GetHaveFlag(void);

		TreeData* GetHaveItem(void){
			return &m_EquipData;
		}

		void SetDebug(void){
			if(m_Debug)
				m_Debug = false;
			else
				m_Debug = true;
		}

		//���������m�F�����m�F
		bool GetConfirmationFlag(void){
			return m_ConfirmationFlag;
		}

		//bool isConfirmation(void)
		//{
		//	return m_ConfirmationFlag;
		//}
};

//========================================================================
//	End of file
//========================================================================