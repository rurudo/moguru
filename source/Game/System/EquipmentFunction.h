#pragma once
#include "../Unit/UnitBase.h"
// ���j�b�g�̏���R�X�g�팸
int EquipmentFunction_01( int value );
// 10�t���[����1��
void EquipmentFunction_02( int frame );
// �ő厑���l�㏸
void EquipmentFunction_03( void );
// ���j�b�g�]��
int EquipmentFunction_04( int );
// ���O�����u���b�N����󂯂�_���[�W������
int EquipmentFunction_05( int value );
// �X���E�n�`�̌��ʂ����j�b�g���󂯂Ȃ�
float EquipmentFunction_06( float value );
// �擾�����������Ȃ�
int EquipmentFunction_07( int value );
// ���j�b�g�̗^����_���[�W����������
int EquipmentFunction_08( int value );
// ���j�b�g�̃����W����
float EquipmentFunction_09( float value );
// �S�Ẵ��j�b�g������U�𓾂�
bool EquipmentFunction_10( void );
// �Γ����@�������̃_���[�W������
int EquipmentFunction_11( int value );
// ��Ԉُ������₷������
float EquipmentFunction_12( float value );
// �����������ł��܂��Ă���
void EquipmentFunction_13( int frame );
// �G�̍U���̃_���[�W�𖳌��ɂ��邪�����������Ă���
int EquipmentFunction_14( int value);
void EquipmentFunction_14_Dec( int frame );
// �����j�b�g�̍U�����G�ƃu���b�N�ɓ�����悤�ɂȂ�
bool EquipmentFunction_15( void );
// �����j�b�g�����Ԋ��������悤�ɂȂ邪�U�������Ȃ葝��
bool EquipmentFunction_16( void );
int EquipmentFunction_16_Value( int );	// �㏸�l
// �u���b�N�ɑ΂��čU���͑����A�G�ɑ΂��Ă̓_�E��
int EquipmentFunction_17_Block( int );
int EquipmentFunction_17_Enemy( int );
// �G�ɑ΂��čU���͑����A�u���b�N�ɑ΂��Ă̓_�E��
int EquipmentFunction_18_Block( int );
int EquipmentFunction_18_Enemy( int );
// �����ɂȂ�Ȃ�
float EquipmentFunction_19( float value, bool isEnemy );
// �U���͂𑝉������邪�����ɂ��_���[�W
int EquipmentFunction_20( int power, int *hp);
// ���j�b�g�U���Ƀ����W������t��
void EquipmentFunction_21( int *type, float *time, float *value);
// ���j�b�g�U���ɖ�Ⴢ�t��
void EquipmentFunction_22( int *type, float *time);
// ���j�b�g�U���ɓ�����t��
void EquipmentFunction_23( int *type, float *time);
// ���j�b�g�U���ɔR�Ă�t��
void EquipmentFunction_24( int *type, float *time, float *value);
// ���j�b�g�U���ɍ�����t��
void EquipmentFunction_25( int *type, float *time);
// 100�ȉ��̃_���[�W�𔼌�����
int EquipmentFunction_26( int );
// ��Ԉُ�̌��ʂ𑝕�������
void EquipmentFunction_27( int *type, float *time, float *value1, float *value2);
// �g���b�v�u���b�N�����j���
bool EquipmentFunction_28( void );
// �G�̍U���p�x������������
float EquipmentFunction_29( float value );
// �G�̍U���͂�������
int EquipmentFunction_30( int value );
// ���j�b�g�U���ɍU���p�x������t�^����
void EquipmentFunction_31( int *type, float *time, float *value);
// �����W���k�߂čU���͂�������
void EquipmentFunction_32( int *attack, float *range);
// ��莞�Ԗ��Ƀ��j�b�g���񕜂���
void EquipmentFunction_33( int frame );
// �w��n�_�ɖ�����U������
void EquipmentFunction_34( float x, float y );
// �@��̂��x���Ȃ�
bool EquipmentFunction_35( int frame );
// �����j�b�g�̍U���p�x���グ��
float EquipmentFunction_36( float value );
// �n�`�ɗ^����_���[�W����
int EquipmentFunction_37( int value );
// ���O�����G����󂯂�_���[�W����������
int EquipmentFunction_38( int value );
// ���j�b�g�̎󂯂�_���[�W����������
int EquipmentFunction_39( int value );
// ������̂������Ȃ�
float EquipmentFunction_40( float value );
// ��������������
void EquipmentFunction_41( UnitBase* base );
// ���j�b�g�̈ړ����x���㏸
float EquipmentFunction_42( float value );
// �~�܂��Ă�������U������
void EquipmentFunction_43( float x, float y );
// ���O�����烌���Wa�̓G�̑��x��b%�ɂ���
void EquipmentFunction_44( int frame );
// ���O���ւ̃_���[�W���萔�ɂȂ�
int EquipmentFunction_45( int value );
// �@��̂��x���Ȃ�
bool EquipmentFunction_46( void );
// ���i�����ɂȂ�Ȃ��u���b�N����������𓾂�
int EquipmentFunction_47( int value );
// ���j�b�g�̉�ʂɗ��܂鎞�Ԃ������Ȃ�
void EquipmentFunction_48( int frame );
// ���j�b�g�������ŏo��
void EquipmentFunction_49( int frame );
// �G�����Ȃ���Ԃ��Ǝ����Ƒϋv�l����
void EquipmentFunction_50( int frame );
// ���j�b�g�U���ɃX���E��t��
void EquipmentFunction_51( int *type, float *time, float *value);
// �G����������
void EquipmentFunction_52( UnitBase* base );
// �G���j���Ƀ��C�t��
void EquipmentFunction_53( void );
// ���C�����j�b�g���e������
void EquipmentFunction_54( int frame );
// ���j�b�g�U���Ƀm�b�N�o�b�N��t�^
void EquipmentFunction_55( int *type, float *time, float *x, float *y,
	float dx, float dy);
// ���O�����u���b�N����󂯂�_���[�W������
int EquipmentFunction_56( int value );
// �u���Ɏw��|�C���g�փ��j�b�g����������
bool EquipmentFunction_57( void );
// ��莞�Ԗ��Ƀ��j�b�g�̎��ӂɃ_���[�W
void EquipmentFunction_58( int frame );
// ��莞�Ԗ��ɑS�Ẵ��j�b�g�Ƀ_���[�W
void EquipmentFunction_59( int frame );
// ��Ƀ��\�[�X��9999
void EquipmentFunction_60( void );