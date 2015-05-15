#pragma once
#include "../Unit/UnitBase.h"
#include "../Task/TaskBase.h"
// �`��n
// �w��̍��W�ɔ����A�j���[�V�������s��
void TaskSet_DrawExplod(float x, float y);
// �^�X�N���������o�[�W����
TaskBase* TaskSet_DrawExplodTask(float x, float y);

// �����n
// �w��̍��W�Ɏw��̃��j�b�g�̎��S���o���s��
void TaskSet_DeadCalc(float x, float y, UnitBase* base);
// �w��̍��W�Ɏw���ID�u���b�N�̔j�󉉏o���s��
void TaskSet_BlockBreakCalc(float x, float y, int id, int enemyID, bool isEnemy);
// �w��̍��W�Ƀu���b�N�̃}�O�}�_���[�W
void TaskSet_BlockFireDamage(float x, float y);

// �_���[�W�n
// �w��̃|�C���g���甼�arange�͈̔͂̃u���b�N�Ɏw��̃_���[�W
void TaskSet_AreaBlockDamage(float x, float y, int damage, float range);
// �w��̃|�C���g���甼�arange�͈̔͂̃��j�b�g�Ɏw��̃_���[�W
void TaskSet_AreaUnitDamage(float x, float y, int damage, float range);
// �w��̃|�C���g���甼�arange�͈̔͂̃��j�b�g�Ɏw��̏�Ԉُ��^����
void TaskSet_AreaUnitBadStatus( float x, float y, int damage, float range, int type, const VECTOR &damageData );
// �G�□���݂̂ɓ��Ă邱�Ƃ��ł���
void TaskSet_AreaUnitBadStatusFriend( float x, float y, int damage, float range, int type, const VECTOR &damageData, bool isEnemy);

void TaskSet_Shot(int power, int type, const VECTOR &damageData, float x, float y, float enemyX, float enemyY,
	bool isEnemy, bool blockHit, UnitBase* unit, bool enemyHit = true);

// �U��
void TaskSet_AllTargetSet( float x, float y, UnitBase* unit);
void TaskSet_FriendTargetSet( float x, float y );
void TaskSet_FriendReact( float x, float y );

// ����
void TaskSet_CreateEnemy( float x, float y, int id );