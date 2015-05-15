#pragma once
// DX���C�u�����̊֐������b�v�����֐��Q
// ��ʃT�C�Y��ύX���Ă����������ŏ��������ł���
// ���ׁ̈A���W�w��ɂ̓s�N�Z���ł͖�����ʂł̔䗦�Ŏw�肷��
#include "DxLib.h"
namespace DXLibMath
{
	const double defaultWidth = 800.0;		// ���ʃT�C�Y
	const double defaultHeight = 600.0;		// ���ʃT�C�Y
	const double deltaValue = 0.000000001;	// �덷�΍�̔����l
	struct Vector2
	{
		Vector2(): x(0.0), y(0.0){}
		double x, y;
	};

	struct LayOut
	{
		LayOut(): up(0.0), down(0.0), left(0.0), right(0.0){}
		double up, down, left, right;
	};

	// ��ʃT�C�Y�̐ݒ�֐�
	void SetWindowSizeRate(double width, double height);

	// ��ʃT�C�Y�ɍ��킹���`��֐�
	void DrawRotaGraphResize(double x, double y, double extend, double rotation, int handle, int transFlag);
	void DrawRotaGraphResize(float x, float y, float extend, float rotation, int handle, int transFlag, int turnFlag = FALSE);
	// ���̂܂ܕ`��
	void DrawGraphResize(double x, double y, int handle, int transFlag);
	void DrawGraphResize(float x, float y, int handle, int transFlag);
	// �w��̗̈�ɑ΂��ĕ`��
	void DrawExtendGraphResize(double x, double y, double width, double height, int handle, int transFlag);
	void DrawExtendGraphResize(float x, float y, float width, float height, int handle, int transFlag);
	// �w��̗̈�Ɏl�p�`��`��
	void DrawBoxResize(float x, float y, float width, float height, int color, int transFlag);

	// ��ʃT�C�Y�ɍ��킹�����W�̊������擾����
	void GetMousePointResize(double *x, double *y);
	// unsigned short�̒l�����W�̊����ł���double�ɕϊ�����
	void ConverDisplay(const unsigned short x, const unsigned short y, double *out_x, double *out_y);
	// double�l�����s�N�Z���ʒu�ɕϊ�����
	void ConvertPixcel(double x, double y, int *out_x, int *out_y);
	// double�l�����s�N�Z���ʒu�ɕϊ�����:X�l�̂�
	void ConvertPixcelX(double x, int *out_x);
	// double�l�����s�N�Z���ʒu�ɕϊ�����:Y�l�̂�
	void ConvertPixcelY(double y, int *out_y);

	// �u���b�N���W�n����ʍ��W�n�ɕϊ�����
	void ConvertBlockToScreen(float x, float y, float *out_x, float *out_y);
	// ��ʍ��W�n���u���b�N���W�n�ɕϊ�����
	void ConvertScreenToBlock(float x, float y, float *out_x, float *out_y);

	// ��ʃo�b�t�@�`��p�֐�
	void DrawFrontBuffer(int handle);

	//---------------------------------------------------------------------------
	// ���w�֐�
	//---------------------------------------------------------------------------
	// position�ʒu�ɂ��鎞�Atarget�̌����Ɍ��݂̌���facing��power�̊�������������power=1.0f�ő�����target�̕�������
	void FacingTarget(const VECTOR &position, const VECTOR &target, VECTOR *facing, float power);
	// �x�N�g���̒�����Ԃ��Az��0�Ƃ��Čv�Z����
	float Length(const VECTOR &vector);
	// in�x�N�g���𐳋K������out�x�N�g���ɏo�͂���,Z�͖�������
	void Normalize(VECTOR *out, const VECTOR &in);
	// in�x�N�g���̊p�xRotation�����߂�
	float CalcRotation(const VECTOR &vector);
	// point�ʒu�����ar��circlePos�ʒu�ɒ��S�̂���~�̓����ɂ��邩�ǂ����i�����ɂ��鎞true)
	bool CircleOnPoint(const VECTOR &position, const VECTOR &circlePos, float r);
	// �s�N�Z���ɖ����Ȃ��[����؂�̂Ă�
	void Floor(double *width, double *height);
};