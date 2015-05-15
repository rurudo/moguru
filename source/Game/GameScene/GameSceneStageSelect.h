#pragma once
#include "GameScene.h"
#include "../System/DxLibMath.h"
#include "../System/FontManager.h"

//�^�C�g���N���X
class GameSceneStageSelect : public GameScene
{
private:
	// �f����`
	enum PlanetID
	{
		PLANET_1,
		PLANET_2,
		PLANET_3,
		PLANET_4,
		PLANET_5,
		PLANET_MAX
	};
	// �t�F�[�h�n�̃t���O
	enum Fade{
		NON,
		FADE1,
		FADE2
	};
	// �`��\����
	struct DRAW_DATA{
		float		x, y, r;
		float		scal, rot;
		int			handle;
		bool		release;
		float		cur_x, cur_y;
		float		cur_scal;
	};

	// �g�p�f�[�^
	DRAW_DATA	m_Planet[5];				// �f���̃f�[�^
	DRAW_DATA	m_b_Planet[5];				// �f���̌��f�[�^�����p(�X�e�[�W�A�җp�̃o�b�N�A�b�v�f�[�^)
	VECTOR		m_b_st[5];					// ���o�p�ɐ��Ɛ��̂��Ƃ̈ʒu�����ԃx�N�g����ۑ�����(�X�e�[�W�A�җp�̃o�b�N�A�b�v�f�[�^)
	VECTOR		m_terget;					// �ړI�n
	VECTOR		m_st[5];					// ���o�p�ɐ��ƒ��_(0.5f,0.5f)�����ԃx�N�g����ۑ�����
	FontManager	m_Font;						// �t�H���g�Ǘ�
	int			m_Planet_Back_handle[5];	// �f���w�i�̃n���h��
	int			m_BackBrightness;			// �f���w�i�̖��邳
	int			m_FrameBrightness;			// �f���w�i�̖��邳
	int			m_Brightness;				// �t�F�[�h�p
	int			m_BrightnessFlg;			// �t�F�[�h�p
	int			m_id_back;					// id�̕ۑ�
	int			m_BeforeId;					// �O�t���[���̑I����Ԃ̕ۑ�
	bool		m_BackBrightnessFlg;		// �f���w�i�̖��邳�̃t���O
	bool		m_FrameBrightnessFlg;		// �f���w�i�̖��邳�̃t���O
	bool		m_CursorFlg;				// �J�[�\���̉�]���g�k�t���O
	bool		m_PlanetEffectFlg;			// �f���̊g�k�t���O
	float		m_scal_back;				// ���Ƃ��Ƃ̊g�k����ۑ����Ă�����
	float		m_ship_scal;				// �F���D�̃X�P�[��
	float		m_CursorScal;				// �J�[�\���̊g�k
	float		m_speed;					// �ړ����x
	float		m_AddAlpha;					// ���Z�����\�����̃��l
	float		m_AddAlphaState;			// ���̃��l��ς�����
	float		m_PlanetBackScal[5];		// �f���̌��̊g�k��ۑ����Ă����p

	// ���@�\����
	struct Ship
	{
		// �R���X�g���N�^
		Ship()
		{
			position.x = 0.0f;
			position.y = 0.0f;
			facing.x = 0.0f;
			facing.y = 0.0f;
			id = PLANET_1;
			handle = 0;
		}
		VECTOR position;		// ���W
		VECTOR facing;			// ����
		int id;					// ��������̘f��
		int handle;				// �`��ׂ̈̃n���h��
	}m_Ship;
	//�}�E�X���W
	VECTOR m_mouse;
	// �v���C�x�[�g�֐�
	void MovePoint();			// �F���D���ړ�������
	void Staging();				// �X�e�[�W�ɓ���ۂ̉��o
	void Staging2();			// �X�e�[�W����o��ۂ̉��o
public:
	GameSceneStageSelect();
	virtual ~GameSceneStageSelect(void);
	virtual int Update(void);
	virtual void Draw(void);

	void Init(void);
	void Release(void);
	void Backup(void);
};

//�����֐�
GameScene* GameSceneStageSelect_CreateScene();