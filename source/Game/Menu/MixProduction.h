//========================================================================
//	@file		MixProduction.h
//	@note		�����������o
//	@author		RyotaUehara
//========================================================================

//------------------------------------------------------------------------
//	IncludeHeader
//------------------------------------------------------------------------
#include "../System/DxLibMath.h"

typedef struct MixObj{
	VECTOR	position;		//�ʒu
	int					alpha;			//�A���t�@�l
	bool				flag;

	MixObj(void) : alpha(255),flag(false){
		position.x = 0.0;
		position.y = 0.0;
	}
}MixObj;

typedef struct MixSphere{
	MixObj				data;
	VECTOR	velocity;
}MixSphere;

typedef struct MixCircle{
	MixObj				data;			//�f�[�^
	float				expansion;		//�g�嗦

	MixCircle(void) : expansion(1.0){}
}MixCircle;

//------------------------------------------------------------------------
//	@Class MixProduction MixProduction.h 
//	@brief �����������o
//------------------------------------------------------------------------
class MixProduction
{
	//--------------------------------------------------------------------
	//	Member
	//--------------------------------------------------------------------
	private:
		bool					m_Enable;					//�L���t���O
		bool					m_Draw;						//�`��t���O
		int						m_Step;						//�����X�e�b�v
		int						m_Content;					//���e�t���O:������������
		int						m_Time;						//����

		int						m_RootId;
		int						m_RootType;

		MixSphere				m_Sphere[4];				//�����E�������̋��̃f�[�^
		MixObj					m_Material[4];				//
		MixObj					m_Main;						//
		MixCircle				m_Circle;					//�������̋��̃f�[�^

		enum Step{
			None = -1,
			FEmission,
			SEmission,
			Start,
			Preparation,
			Run,
			Finish
		};

		enum StepTime{
			Time_FEmission		= 10,
			Time_SEmission		= 10,
			Time_Start			= 5,
			Time_Preparation	= 30,
			Time_Run			= 30,
			Time_Finish			= 10
		};

		static const int		cm_WhiteAlpha;				//
		static const int		cm_CircleAlpha;				//
		//static const int		cm_DivisionHermite;			//�G���~�[�g������
		static const float		cm_MaxExpansion;			//�g��ő�{��
		static const float		cm_MaxExpansionPlus;		//�g��ő�{��
	public:
		enum Contant{
			Mix,
			Break
		};
	//--------------------------------------------------------------------
	//	Method
	//--------------------------------------------------------------------
	private:
		//��ꔭ���X�e�b�v
		void StepFirstEmission(void);
		//��񔭌��X�e�b�v
		void StepSecondEmission(void);
		//�X�^�[�g�X�e�b�v
		void StepStart(void);
		//�����X�e�b�v
		void StepPreparation(void);
		//���s�X�e�b�v
		void StepRun(void);
		//�����X�e�b�v
		void StepFinish(void);

		//��ꔭ���`��
		void DrawFirstEmission(void);
		//��񔭌��`��
		void DrawSecondEmission(void);
		//�X�^�[�g�`��
		void DrawStart(void);
		//�����`��
		void DrawFinish(void);

		//���o�f�[�^���Z�b�g
		void Reset(void);

		//�\�[�g���ꂽ���X�g����t����
		int ReverseGetID(int id,char type);
	public:
		//================================================================
		//	Constructor
		//================================================================
		MixProduction(void);
		//�f�X�g���N�^
		virtual ~MixProduction(void);

		//����������
		void Init(void);
		//�X�V����
		bool Update(void);
		//�`�揈��
		void Draw(void);
		//�������
		void Release(void);

		//���e���Z�b�g
		void SetContent(int Content,int RootId,int RootType);

		bool GetEnable(void);
};

//========================================================================
//	End of file
//========================================================================