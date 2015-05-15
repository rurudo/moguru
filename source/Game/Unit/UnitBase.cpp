#include "UnitBase.h"
#include "../System/DxLibMath.h"
#include "../System/DataManager.h"
#include "../System/BlockManager.h"
#include "../System/UnitManager.h"
#include "../System/EquipmentFunction.h"
#include "../System/GameInput.h"

UnitBase::UnitBase(void)
{
	m_x = 0.0f;
	m_y = 0.0f;
	m_nextX = 0.0f;
	m_nextY = 0.0f;
	m_MoveStatus = MovePoint;
	m_Exist = false;
	m_AttackEnable = true;
	m_ID = 1;
}


UnitBase::~UnitBase(void)
{
}

void UnitBase::Init(void)
{
	m_Facing.x = 0.0f;
	m_Facing.y = 0.0f;
	m_AtackCount = 0.0f;
	DataManager &data = DataManager::GetInstance();
	m_Life = data.m_SystemData.unit[m_ID - 1].hp;
	m_MaxLife = m_Life;
	m_DamageSrc = NULL;
	m_TreasureID = -1;
	m_AnimTime = 0;
	for(int i = 0; i < DAMAGETYPE_MAX; i++)
	{
		m_BadStatus[i].x = 0.0f;
		m_BadStatus[i].y = 0.0f;
		m_BadStatus[i].z = 0.0f;
	}
}

void UnitBase::Draw(void)
{
	DataManager &data = DataManager::GetInstance();
	float x, y;
	DXLibMath::ConvertBlockToScreen( m_x, m_y, &x, &y);

	int l_frame = 40;
	// 向きに合わせた画像変換
	if( m_Facing.x < 0.0f)
	{
		if( m_AnimTime % l_frame < l_frame/2 )
		{
			DXLibMath::DrawRotaGraphResize(x, y, 1.0f,
				0.0f, data.GetGraphicGroupData( DataManager::GG_UNIT_Treasure + m_ID - 1 ), TRUE);
		}
		else
		{
			DXLibMath::DrawRotaGraphResize(x, y, 1.0f,
				0.0f, data.GetGraphicGroupData( DataManager::GG_UNIT_Treasure2 + m_ID - 1 ), TRUE);
		}
	}
	else
	{
		if( m_AnimTime % l_frame < l_frame/2 )
		{
			DXLibMath::DrawRotaGraphResize(x, y, 1.0f,
				0.0f, data.GetGraphicGroupData( DataManager::GG_UNIT_Treasure + m_ID - 1 ), TRUE, TRUE);
		}
		else
		{
			DXLibMath::DrawRotaGraphResize(x, y, 1.0f,
				0.0f, data.GetGraphicGroupData( DataManager::GG_UNIT_Treasure2 + m_ID - 1 ), TRUE, TRUE);
		}
	}
}

void UnitBase::DrawAlpha(void)
{
}

void UnitBase::SetPosition(float x, float y)
{
	m_x = x;
	m_y = y;
}

void UnitBase::AddPosition(float x, float y)
{
	m_x += x;
	m_y += y;
}

void UnitBase::SetTargetPosition(float x, float y)
{
	m_nextX = x;
	m_nextY = y;
}

void UnitBase::Update(void)
{
}

void UnitBase::Release(void)
{
}

bool UnitBase::IsExist(void)
{
	return m_Exist;
}

void UnitBase::SetExist(bool flag)
{
	m_Exist = flag;
}

void UnitBase::BadStatusUpdate( void )
{
	float time = EquipmentFunction_12( 1.0f );
	// 燃焼
	if( m_BadStatus[ DAMAGETYPE_FIRE ].x > 0.0f )
	{
		// 30フレームに１回ダメージ
		if( static_cast<int>( m_BadStatus[ DAMAGETYPE_FIRE ].x ) % 30 == 0)
		{
			m_Life -= static_cast<int>( m_BadStatus[ DAMAGETYPE_FIRE ].y );
		}
		m_BadStatus[ DAMAGETYPE_FIRE ].x -= time;
	}
	// 自分が存在するブロック毎の処理
	BlockBase* block = BlockManager::GetInstance().GetBlock( m_x, m_y );
	if( block && m_ID != UNIT_Ninja )
	{
		switch( block->m_ID )
		{
		case BLOCK_WATER:
			m_Speed *= EquipmentFunction_06(0.8f);
			break;
		case BLOCK_MUD:
			m_Speed *= EquipmentFunction_06(0.7f);
			break;
		case BLOCK_DEEPMUD:
			m_Speed *= EquipmentFunction_06(0.6f);
			break;
		case BLOCK_FIRE:
			//if( GameInput::GetInstance().GetFrame() % 2 == 0 && m_ID != UNIT_Salamander)
			if( m_ID != UNIT_Salamander )
			{
				m_Life -= EquipmentFunction_56(2);
			}
			break;
		default:
			break;
		}
	}
	// スロウ
	if( m_BadStatus[ DAMAGETYPE_SLOW ].x > 0.0f )
	{
		m_Speed *= m_BadStatus[ DAMAGETYPE_SLOW ].y;
		m_BadStatus[ DAMAGETYPE_SLOW ].x -= time;
	}
	// 停止
	if( m_BadStatus[ DAMAGETYPE_STOP ].x > 0.0f )
	{
		m_Speed = 0.0f;
		m_AttackEnable = false;
		m_BadStatus[ DAMAGETYPE_SLOW ].x = 0.0f;
		m_BadStatus[ DAMAGETYPE_PARALYSIS ].x = 0.0f;
		m_BadStatus[ DAMAGETYPE_STOP ].x -= time;
	}
	// 攻撃速度低下
	if( m_BadStatus[ DAMAGETYPE_ATTACKSPEED ].x > 0.0f )
	{
		m_AttackSpeed *= m_BadStatus[ DAMAGETYPE_ATTACKSPEED ].y;
		m_BadStatus[ DAMAGETYPE_ATTACKSPEED ].x -= time;
	}
	// 混乱
	if( m_BadStatus[ DAMAGETYPE_CONFUSION ].x > 0.0f )
	{
		//m_BadStatus[ DAMAGETYPE_CONFUSION ].x =
		//	EquipmentFunction_19( m_BadStatus[ DAMAGETYPE_CONFUSION ].x, m_MoveStatus == Enemy );
		m_BadStatus[ DAMAGETYPE_CONFUSION ].x -= time;
	}
	// ノックバック
	if( m_BadStatus[ DAMAGETYPE_MOVE ].x > 0.0f )
	{
		m_BadStatus[ DAMAGETYPE_MOVE ].x =
			EquipmentFunction_19( m_BadStatus[ DAMAGETYPE_MOVE ].x, m_MoveStatus == Enemy );
		if( m_BadStatus[ DAMAGETYPE_MOVE ].x > 0.0f )
		{
			m_x += m_BadStatus[ DAMAGETYPE_MOVE ].y;
			m_y += m_BadStatus[ DAMAGETYPE_MOVE ].z;
			m_BadStatus[ DAMAGETYPE_MOVE ].x -= time;
		}
	}
	// 麻痺
	if( m_BadStatus[ DAMAGETYPE_PARALYSIS ].x > 0.0f )
	{
		m_AttackEnable = false;
		m_BadStatus[ DAMAGETYPE_PARALYSIS ].x -= time;
	}
	// 射程
	if( m_BadStatus[ DAMAGETYPE_RANG ].x > 0.0f )
	{
		m_BadStatus[ DAMAGETYPE_RANG ].x -= time;
		m_Rang *= m_BadStatus[ DAMAGETYPE_RANG ].y;
	}
	m_AnimTime++;
}

void UnitBase::SetStatus( void )
{
	DataManager &data = DataManager::GetInstance();
	if( m_MoveStatus != Enemy )
	{
		// 資源ゲージの割合でステータスが変化
		float rate = 0.7f + 0.6f * ( data.m_MogllStatus.resource * 1.0f / ( data.m_MogllStatus.maxResource * 1.0f ) );
		m_AttackSpeed = EquipmentFunction_36( data.m_SystemData.unit[m_ID - 1].aSpd * 0.001f ) * rate;
		m_Speed = EquipmentFunction_42( data.m_SystemData.unit[m_ID - 1].spd * 0.001f ) * rate;
		m_Rang = EquipmentFunction_09( data.m_SystemData.unit[m_ID - 1].rang * 0.1f ) * rate;
		m_Power = static_cast<int>( data.m_SystemData.unit[m_ID - 1].power * rate );
		EquipmentFunction_32( &m_Power, &m_Rang );
	}
	else
	{
		m_AttackSpeed = EquipmentFunction_29( data.m_SystemData.unit[m_ID - 1].aSpd * 0.001f );
		m_Speed = data.m_SystemData.unit[m_ID - 1].spd * 0.001f;
		m_Rang = data.m_SystemData.unit[m_ID - 1].rang * 0.1f;
		m_Power = data.m_SystemData.unit[m_ID - 1].power;
	}
	m_AttackEnable = true;
}

void UnitBase::AddDamage( int damage, int type, const VECTOR &value, UnitBase *enemy)
{
	m_Life -= damage;
	m_DamageSrc = enemy;
	if( type == DAMAGETYPE_LIFESTEAL )
	{
		enemy->m_Life += static_cast<int>(damage * value.x);
		if( enemy->m_Life > DataManager::GetInstance().m_SystemData.unit[enemy->m_ID - 1].hp )
		{
			enemy->m_Life = DataManager::GetInstance().m_SystemData.unit[enemy->m_ID - 1].hp;
		}
	}
	else if( type < DAMAGETYPE_MAX )
	{
		m_BadStatus[type] = value;
	}
}

int UnitBase::GetMaxLife( void )
{
	DataManager &data = DataManager::GetInstance();
	if( m_ID != 31 )
	{
		return data.m_SystemData.unit[m_ID - 1].hp;
	}
	else
	{
		return 1000;
	}
}

bool UnitBase::GetStopFlag( void )
{
	return !m_AttackEnable;
}

void UnitBase::SetTreasureID( int id )
{
	m_TreasureID = id;
}