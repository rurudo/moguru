//========================================================================
//	@file		AfterGetMapProduction.h
//	@note		��Q�b�g��̉��o
//========================================================================
#pragma once
//------------------------------------------------------------------------
//	IncludeHeader
//------------------------------------------------------------------------
#include "../Menu/MixTreeData.h"
#include "../System/DxLibMath.h"
#include "../System/DataManager.h"
#include "../System/FontManager.h"
#include "Glliter.h"
#include <vector>

//------------------------------------------------------------------------
//	Const
//------------------------------------------------------------------------

//------------------------------------------------------------------------
//	@Class AfterGetMapProduction
//	@brief ��Q�b�g��̉��o
//------------------------------------------------------------------------
class AfterGetMapProduction
{
	//--------------------------------------------------------------------
	//	Member
	//--------------------------------------------------------------------
	private:
		bool				m_Enable;						//�L���t���O
		bool				m_Skip;							//�X�L�b�v�t���O
		bool				m_NowSkip;						//�X�L�b�v���t���O
		int					m_Step;							//�X�e�b�v
		int					m_Frame;						//�t���[���J�E���g

		int					m_ItemNum;						//���肵����:0~(�A�C�e��)�@60~(�}�b�v)
		int					m_ItemHandle;						//���肵����:0~(�A�C�e��)�@60~(�}�b�v)
		int					m_ItemAipha;					//���肵�����̃A���t�@�l
		int					m_MessAipha;					//���肵�����̃A���t�@�l
		int					m_DesAipha;					//���肵�����̃A���t�@�l
		float				m_ItemExpansion;				//���肵�����̊g�嗦

		char				m_Message[256];

		DXLibMath::Vector2	m_BackPos;						//�w�i�̈ʒu
		DXLibMath::Vector2	m_MessagePos;					//�ʒu
		DXLibMath::Vector2	m_DescriptionPos;				//�ʒu
		DXLibMath::Vector2	m_FramePos;						//�ʒu

		DataManager			*m_Data;						//

		FontManager			m_FontManager;					//�Ǝ��t�H���g�A�������s�p

		static const int	cm_BackPosX;					//�w�i�ʒu
		static const int	cm_BackPosY;					//�w�i�ʒu
		static const int	cm_BackOff;						//�w�i�ʒu
		static const int	cm_StagePosX;					//�A�C�R���ʒu
		static const int	cm_StagePosY;					//�A�C�R���ʒu
		static const int	cm_IconPosX;					//�A�C�R���ʒu
		static const int	cm_IconPosY;					//�A�C�R���ʒu
		static const int	cm_GetMessagePosX;				//���b�Z�[�W:���肵�܂����ʒu
		static const int	cm_GetMessagePosY;				//���b�Z�[�W:���肵�܂����ʒu
		static const int	cm_GetMessageOff;				//���b�Z�[�W:���肵�܂����ʒu
		static const int	cm_DecriptionPosX;				//���肵�����̂̐����ʒu
		static const int	cm_DecriptionPosY;				//���肵�����̂̐����ʒu
		static const int	cm_DecriptionOff;				//���肵�����̂̐����ʒu

		enum Step{
			STEP_Init = 0,				//������
			STEP_FrameIn,				//�w�i�C��
			STEP_InWait,				//�E�F�C�g����
			STEP_IconIn,				//�A�C�R���C��
			STEP_MessageIn,				//���b�Z�[�W�C��
			STEP_DescriptionIn,			//�����C��
			STEP_EndWait,
			STEP_TreeOut				//�g�A�E�g
		};

		enum Frame{
			FRAME_FrameIn = 75,		//�w�i�C��
			FRAME_InWait = 20,			//�E�F�C�g����
			FRAME_IconIn = 40,			//�A�C�R���C��
			FRAME_MessageIn = 40,		//���b�Z�[�W�C��
			FRAME_DescriptionIn = 40,	//�����C��
			FRAME_EndWait = 40,
			FRAME_FrameOut = 100		//�g�A�E�g
		};
	public:
	//--------------------------------------------------------------------
	//	Method
	//--------------------------------------------------------------------
	private:
		//�X�e�b�v�X�V����
		void UpdateStep(void);

		//�c���[�g�C��
		void InFrame(void);
		//
		void InIcon(void);
		//
		void InMessage(void);
		//
		void InDescription(void);
		//�c���[�g�A�E�g
		void OutFrame(void);

		//�c���[�g�`��
		void DrawFrame(void);
		//
		void DrawIcon(void);
		//
		void DrawMessage(void);
		//
		void DrawDescription(void);
		//
		void DrawMixresult(void);

		//
		void Reset(void);
	public:
		//================================================================
		//	Constructor
		//================================================================
		AfterGetMapProduction(void);
		//�f�X�g���N�^
		virtual ~AfterGetMapProduction(void);

		//������
		void Init(void);
		//�X�V
		void Update(void);
		//�`��
		void Draw(void);
		//���
		void Release(void);

		void Enable(void);

		bool GetEnable(void);
};

//========================================================================
//	End of file
//========================================================================