#pragma once
#include "BoolArray.h"
#include "DxLibMath.h"
class CustomUserInterface
{
private:
	enum InterfaceFlags
	{
		InterfaceFlag_Visible
	};
	BoolArray m_Flags;
	DXLibMath::Vector2 m_Position;
	DXLibMath::Vector2 m_Size;
	DXLibMath::LayOut m_OutSpace;	// �t���[���̗]��
	DXLibMath::LayOut m_InSpace;	// �q�v�f�̗]��
	int	m_InSpaceX, m_InSpaceY;
	int m_OutSpaceX, m_OutSpaceY;
	int m_Handle;					// �t���[���̉摜�n���h��
public:
	CustomUserInterface(void);
	~CustomUserInterface(void);
	void Update(void);
	void Draw(int widthNum, int heightNum, int *handle);
	void Draw(	int widthNum, int heightNum, int *handle,
				char judgeList[],int sortList[],int judgeVal[],int judgeNum,int silhouetteVal[],int silhouetteNum);
	void GetPosition(int width, int height, int *x, int *y);
	// �`��t���O�̐؂�ւ�
	void SetVisible(bool isVisible);
	// �`��̈�̃T�C�Y�w��
	void SetRect(double x, double y, double width, double height);
	void SetRect(float x, float y, float width, float height);
	void SetPosition(double x, double y);
	void SetGraphicHandle(int handle);
	// �O���̃X�y�[�X���Z�b�g����
	void SetOutSpace(double up, double down, double left, double right);
	// �q�v�f�Ԃ̃X�y�[�X���Z�b�g����
	void SetInSpace(double up, double down, double left, double right);
};

