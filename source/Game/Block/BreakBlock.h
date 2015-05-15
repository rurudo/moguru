#pragma once
#include "../System/DxLibMath.h"
#include <vector>

class BreakBlock
{
private:
	static const int	cm_AddRangeX;			//ブロック中心から破片を追加する範囲
	static const int	cm_AddRangeY;			//ブロック中心から破片を追加する範囲
	static const int	cm_AddRangeBaseX;		//ブロック中心から破片を追加する範囲
	static const int	cm_AddRangeBaseY;		//ブロック中心から破片を追加する範囲
	static const int	cm_AlphaValue;			//α値の増減値
	static const int	cm_DefaultLife;			//初期ライフ
	static const int	cm_BaseSize;			//
	static const int	cm_RangeSize;			//
	static const float	cm_BaseVelocityX;		//
	static const float	cm_BaseVelocityY;		//
	static const float	cm_BaseAcceleX;			//
	static const float	cm_BaseAcceleY;			//
	static const float	cm_Waight;				//

	typedef struct ParticleSimpleData{
		DXLibMath::Vector2	point[4];			//中心点からの各点までの距離
		DXLibMath::Vector2	cPosition;			//中心座標
		DXLibMath::Vector2	velocity;			//速度
		DXLibMath::Vector2	accele;				//加速度
		int					alpha;				//α値
		//bool				alive;				//生存フラグ
	}ParticleSimpleData;

	typedef struct ParticleData{
		ParticleSimpleData*	particleData;

		DXLibMath::Vector2	cPosition;		//中心座標
		int					handle;
		int					life;
		int					particleNum;
		bool				alive;
	}ParticleData;

	//パーティクルリスト
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

