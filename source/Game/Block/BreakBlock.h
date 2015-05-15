#pragma once
#include "../System/DxLibMath.h"
#include <vector>

class BreakBlock
{
private:
	static const int	cm_AddRangeX;			//�u���b�N���S����j�Ђ�ǉ�����͈�
	static const int	cm_AddRangeY;			//�u���b�N���S����j�Ђ�ǉ�����͈�
	static const int	cm_AddRangeBaseX;		//�u���b�N���S����j�Ђ�ǉ�����͈�
	static const int	cm_AddRangeBaseY;		//�u���b�N���S����j�Ђ�ǉ�����͈�
	static const int	cm_AlphaValue;			//���l�̑����l
	static const int	cm_DefaultLife;			//�������C�t
	static const int	cm_BaseSize;			//
	static const int	cm_RangeSize;			//
	static const float	cm_BaseVelocityX;		//
	static const float	cm_BaseVelocityY;		//
	static const float	cm_BaseAcceleX;			//
	static const float	cm_BaseAcceleY;			//
	static const float	cm_Waight;				//

	typedef struct ParticleSimpleData{
		DXLibMath::Vector2	point[4];			//���S�_����̊e�_�܂ł̋���
		DXLibMath::Vector2	cPosition;			//���S���W
		DXLibMath::Vector2	velocity;			//���x
		DXLibMath::Vector2	accele;				//�����x
		int					alpha;				//���l
		//bool				alive;				//�����t���O
	}ParticleSimpleData;

	typedef struct ParticleData{
		ParticleSimpleData*	particleData;

		DXLibMath::Vector2	cPosition;		//���S���W
		int					handle;
		int					life;
		int					particleNum;
		bool				alive;
	}ParticleData;

	//�p�[�e�B�N�����X�g
	std::vector<ParticleData*>	m_ParticleList;
	bool						m_Enable;

	void Init(void);
	void Release(void);

	void ParticleUpdate(int num);

	void EnableJudge(void);
public:
	BreakBlock(void);
	~BreakBlock(void);

	void Update(void);
	void Draw(void);

	void Add(DXLibMath::Vector2 cPos,int particleNum,int handle);
};

