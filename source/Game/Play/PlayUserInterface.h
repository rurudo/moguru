#pragma once
#include "../System/DxLibMath.h"
#include "../System/FontManager.h"
#include <list>
class PlayUserInterface
{
private:
	struct Rect
	{
		float x, y, width, height;
	}m_FieldRect;
	float m_LinePos;			// ���[�_�[���C���̈ʒu
	int m_LineCount;			// ���[�_�[���C���̔���J�E���g
	VECTOR m_Mouse;				// �}�E�X���W
	int m_CurrentPosition;		// ���ݕW���̓������Ă���g
	float	m_EscButton;		// �E�o�{�^��X���W
	float	ESC_IN_POS;			// �E�o�{�^����ʒu�i�����j
	float   ESC_OUT_POS;		// �E�o�{�^����ʒu�i�O���j
	float   ESC_BUTTON_WIDTH;	// �E�o�{�^����
	float   ESC_BUTTON_HEIGHT;	// �E�o�{�^������ 
	bool	m_GetOut;			// �E�o�t���O
	bool	m_Retry;
	float	m_EscChkButtonSize[3];	// �E�o�m�F�{�^���T�C�Y
	bool	m_EscChkSEFlg[3];	// �E�o�m�F�{�^��SE�t���O
	bool	m_DrawEffect;		// �t�B�[���h�G�t�F�N�g��`�悷�邩
	VECTOR	m_FieldEffect[2];	// �t�B�[���h�G�t�F�N�g�ʒu
	float	m_EffectAlpha[2];	// �t�B�[���h�G�t�F�N�g���l
	float   FIELD_EFFECT_WIDTH; // �t�B�[���h�G�t�F�N�g��
	float   FIELD_EFFECT_HEIGHT;// �t�B�[���h�G�t�F�N�g����
	FontManager m_Font;			// �����`��p
	double	m_LifeRot;			// ���C�t���[�^�[�\���ʒu
	double	m_ResourceRot;		// ���\�[�X���[�^�[�\���ʒu
	int		m_PrevLife;			// �O��̃��C�t
	int		m_DamageCount;		// �_���[�W�G�t�F�N�g
	bool	m_VisibleFlag;		// �������̕\���t���O
	bool	m_EscapeFlag;
	// ���[�_�[������
	static const int OBJECT_MAX = 50;
	struct DrawObject
	{
		bool exist;
		int x, y;
		int id, alpha;
		double size;
	} m_DrawObject[OBJECT_MAX];
	int m_NumObject;

	void Input(void);
	void RadarCalc(void);
	void AddObject(int x, int y, int id);

	void ClearButtonSize(void)
	{
		for(int i=0; i<3; i++)
		{
			m_EscChkButtonSize[i] = 0.5f;
			m_EscChkSEFlg[i] = false;
		}
	}
public:
	PlayUserInterface(void);
	~PlayUserInterface(void);
	void Update(void);
	void UpdateEffect(void);
	void UpdateButton(void);
	void UpdateLife(void);
	void Draw(float depth);
	void DrawMogll(void);
	void DrawFieldEffect(void);
	void DrawEscape(void);
	void Init(void);
	
	void CheckCurrentSlot(void);

	void SetVisible(bool flag)
	{
		m_VisibleFlag = flag;
	}

	//�E�o�t���O�̎擾
	bool GetOutFlg(void)
	{
		return m_GetOut;
	}

	//�E�o�t���O�̎擾
	bool GetRetryFlg(void)
	{
		return m_Retry;
	}

	//�E�o�E�B���h�E��Ԃ̎擾
	bool GetEsFlg(void)
	{
		return m_EscapeFlag;
	}
};

