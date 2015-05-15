/**
 * �X�e�[�W�J�n���̊K�w�I����ʂł̉��o
 */

#pragma once
#include "../System/DxLibMath.h"
#include "../Play/StageDig.h"

class DepthSelect
{
private:
	// �f���̊K�w�\����
	struct PLANET_HIERARCHY{
		int		H_num;	// ���K�w���邩
		int		Hier[10];// �K�w�����̊�_
	};

	// �f���̔w�i�p�\����
	struct PLANET_BACKSTAGE{
		VECTOR	Pos;
		float	Scal, Rot;
		VECTOR	Speed;
		int		frame_cnt, FRAME_CNT;
		int		Handle;
		bool	isValid;

	};

	// ��ԑJ��
	enum State
	{
		State_Fall,			// �󂩂�~���Ă��Ęf���ɒ���
		State_Product,		// ���o
		State_Select,		// �K�w��I��
		State_Up			// ��ʒu�ֈړ�
	} m_State;

	enum SwitchState
	{
		St_Go,				// �J�n
		St_Select,			// �K�w�Z���N�g
		St_Non				// �Ȃɂ��Ȃ�
	} m_SwitchState;

	enum NumState
	{
		ON,					// �J�n
		OFF,				// �K�w�Z���N�g
		NON					// �Ȃɂ��Ȃ�
	} m_NumState;
	const static int NUM_STAGEBACK = 6;

	bool m_Enable;			// true�̎���������
	int m_Frame;			// �E�F�C�g�����p
	PLANET_HIERARCHY HIERARCHY[5];
	PLANET_BACKSTAGE	m_BackStageDate[NUM_STAGEBACK];		// �w�i�摜�̃n���h���i�[�p
	int Open_Hiera;			// �ǂ��̊K�w�܂ŉ������Ă��邩
	int m_NowFloor;			// ���݂̑I���K�w
	int m_floor;			// �K�w�̏㉺
	int	m_Num_Handle[9];	// ���l�摜�̃n���h���i�[�p
	int	st_flg;				// �}�E�X�����ǂ̃X�C�b�`�̏�ɂ���̂�(99�͗�O����)
	int mouse_st;			// �}�E�X�̏��
	int num_st;				// �����̃t���O
	int bright;				// ���邳
	int bright_flg;			// ���邳�̃t���O
	int m_BlockYBack;		// �u���b�N�̏������W
	int m_BackFlameLoop[5];	// �w�i���o�p�̃��[�v(�t���[��)���J�E���g
	float m_NumScal;		// ���l�̊g�k��
	float m_GoScale;		// GO�̊g�k��
	float m_BlockY;			// �u���b�N�̍��W
	float m_SubX;			// ���o�p�̃T�u�w���W
	float m_BG_WIDTH;		// BG�̕�
	float m_BG_HEIGHT;		// BG�̍���
	VECTOR m_mouse;			// �}�E�X���W
	VECTOR m_myship;		// �F���D�̍��W

	int  m_numachiAnim;	//���n�p�A�j���[�V�����J�E���^
	bool m_numachiAnimFlg;//���n�p�A�j���[�V�����t���O

	// �����񂶃{�[�h�f�[�^
	struct ChallengeData
	{
		int animCount;
		ChallengeData()
		{
			animCount = 0;
		}
	}m_Challenge;

	// �@�鏈������
	StageDig m_Dig;
public:
	DepthSelect(void);
	~DepthSelect(void);

	void Init(void);
	void Update(bool);
	void Draw(void);
	void SpacecraftDraw(void);
	void BgAnime(void);
	void BgDraw(void);
	void ChallengeDraw(void);
	bool IsEnable(void)
	{
		return m_Enable;
	}

	void Selection(void);		// �}�E�X�őI��
	void NumberScal(void);		// �����̊g�k
	void Black(void);			// �Ö�
};

