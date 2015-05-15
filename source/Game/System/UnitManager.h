#pragma once
#include "DxLibMath.h"
#include "../Unit/CreateUnit.h"
#include <list>
#include <map>
class UnitManager
{
private:
	static const int UNIT_ID_OFFSET = 1000;
	std::list<UnitBase*> m_ActiveList;			// �`�撆�G���X�g
	std::map<int, UnitBase*> m_UnitContainer;	// �������̊Ǘ��}�b�v
	std::list<UnitBase*> m_ReturnBuffer;		// �������ʂ�Ԃ����߂̃o�b�t�@

	UnitBase* CreateUnit(int id);
	// �v���C�x�[�g�R���X�g���N�^
	UnitManager(void);
public:
	~UnitManager(void);
	// ���j�b�g�𐶐�����
	void Add(const VECTOR &position, const VECTOR &target, int type, UnitBase::MoveStatus moveType);
	void AddTreasureUnit(const VECTOR &position, const VECTOR &target, int type, UnitBase::MoveStatus moveType, int treasureID);
	// �󔠂𐶐�����
	void AddTreasureBox(const VECTOR &position, int treasureID);
	void Update(void);
	void Draw(void);
	// �ێ����Ă����̈���J��
	void Release(void);
	// �w��l�����S���j�b�g����Ɉړ�����(��ʍ��W�n�j
	void MoveUp(float depth);
	// �w��͈͓��ň�ԋ߂����j�b�g��Ԃ��B���Ȃ����NULL
	UnitBase* GetNearUnit(const VECTOR &position, float r, bool searchEnemy, bool allFlag = false, UnitBase* self = NULL);
	// �w��͈͓��ɃK�[�f�B�A��������΃q�b�g����
	UnitBase* GetNearGuardian( float x, float y, float r, bool searchEnemy);
	// �w��͈͓��̃��j�b�g��Ԃ�
	std::list<UnitBase*>& GetAreaUnit(float x, float y, float r);
	std::list<UnitBase*>& GetAll( void );
	//�C���X�^���X�擾
	static UnitManager& GetInstance(void)
	{
		static UnitManager unitManager;
		return unitManager;
	}
};

