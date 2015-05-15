#include "UnitManager.h"
#include "DataManager.h"
#include "../Unit/Unit_TreasureBox.h"
UnitManager::UnitManager(void)
{
}

UnitManager::~UnitManager(void)
{
}

void UnitManager::Release(void)
{
	for(std::map<int, UnitBase*>::iterator it = m_UnitContainer.begin(); it != m_UnitContainer.end(); it++)
	{
		UnitBase *base = it->second;
		if(base != NULL)
		{
			delete base;
		}
	}
	m_UnitContainer.clear();
	m_ActiveList.clear();
}

void UnitManager::Add(const VECTOR &position, const VECTOR &target, int type, UnitBase::MoveStatus moveType)
{
	if(type != UNIT_NONE)
	{
		UnitBase* base = CreateUnit( type );
		base->Init();
		base->SetExist( true );
		base->SetPosition( position.x, position.y );
		base->SetTargetPosition( target.x, target.y );
		base->m_MoveStatus = moveType;
		m_ActiveList.push_back( base );
	}
}

void UnitManager::AddTreasureUnit(const VECTOR &position, const VECTOR &target, int type, UnitBase::MoveStatus moveType, int treasureID)
{
	if(type != UNIT_NONE)
	{
		UnitBase* base = CreateUnit( type );
		base->Init();
		base->SetExist( true );
		base->SetPosition( position.x, position.y );
		base->SetTargetPosition( target.x, target.y );
		base->m_MoveStatus = moveType;
		base->SetTreasureID( treasureID );
		m_ActiveList.push_back( base );
	}
}


void UnitManager::AddTreasureBox(const VECTOR &position, int treasureID)
{
	Unit_TreasureBox* base = dynamic_cast<Unit_TreasureBox*>( CreateUnit( UNIT_TreasureBox ) );
	base->SetTreasureID( treasureID );
	base->Init();
	base->SetExist( true );
	base->SetPosition( position.x, position.y );
	base->m_MoveStatus = UnitBase::Enemy;
	for(std::list<UnitBase*>::iterator i = m_ActiveList.begin(); i != m_ActiveList.end(); i++)
	{
		if((*i) == base )
		{
			break;
		}
	}
	m_ActiveList.push_back( base );
}

void UnitManager::Update(void)
{
	for(std::list<UnitBase*>::iterator i = m_ActiveList.begin(); i != m_ActiveList.end();)
	{
		UnitBase* base = (*i);
		// 画面の1マスより外のユニットは消去
		if( base->IsExist() && base->m_y > -1.0f && base->m_y < 14.0f && base->m_x > -1.0f && base->m_x < 16.0f )
		{
			base->Update();
			i++;
		}
		else
		{
			(*i)->SetExist( false );
			i = m_ActiveList.erase( i );
		}
	}
}

void UnitManager::Draw(void)
{
	for(std::list<UnitBase*>::iterator i = m_ActiveList.begin(); i != m_ActiveList.end(); i++)
	{
		UnitBase* base = (*i);
		base->Draw();
	}
	// ライフバー
	for(std::list<UnitBase*>::iterator i = m_ActiveList.begin(); i != m_ActiveList.end(); i++)
	{
		UnitBase* base = (*i);
		if( base->m_Life <= base->m_MaxLife && 0 < base->m_Life )
		{
			float x, y;
			int r = 64, g = 255, b = 64;
			if( base->m_MoveStatus == UnitBase::Enemy )
			{
				r = 255;
				g = 64;
				b = 64;
			}
			DXLibMath::ConvertBlockToScreen( base->m_x, base->m_y, &x, &y);
			DXLibMath::DrawBoxResize( x - 0.025f, y - 0.05f , 0.05f, 0.01f, GetColor(32, 32, 32), TRUE);
			float length = base->m_Life / static_cast<float>( base->m_MaxLife );
			DXLibMath::DrawBoxResize( x - 0.025f, y - 0.05f , 0.05f * length, 0.01f, GetColor(r, g, b), TRUE);
		}
	}
	// 状態異常
	for(std::list<UnitBase*>::iterator i = m_ActiveList.begin(); i != m_ActiveList.end(); i++)
	{
		UnitBase* base = (*i);
		float x, y;
		DXLibMath::ConvertBlockToScreen( base->m_x, base->m_y, &x, &y);
		for( int i = 0; i < 7; i++)
		{
			if( base->m_BadStatus[ i ].x >= 1.0f )
			{
				DXLibMath::DrawGraphResize( x - 0.005f * i, y - 0.06f,
					DataManager::GetInstance().GetGraphicGroupData( DataManager::GG_STATUS_FIRE + i ), TRUE );
			}
		}
	}
}

UnitBase* UnitManager::CreateUnit(int id)
{
	UnitBase* base = NULL;
	// 指定したユニットのポインタを探す
	for(int i = 0; i < UNIT_ID_OFFSET; i++)
	{
		// 指定のIDのユニットが足りなければ追加
		base = m_UnitContainer[id * UNIT_ID_OFFSET + i];
		if( base == NULL)
		{
			base = sp_CreateUnitTable[id]();
			m_UnitContainer[id * UNIT_ID_OFFSET + i] = base;
			base->m_ID = id;
			break;
		}
		// 空いてるなら有効にして使いまわす
		else if( !base->IsExist() )
		{
			break;
		}
	}
	return base;
}

void UnitManager::MoveUp(float depth)
{
	for(std::list<UnitBase*>::iterator i = m_ActiveList.begin(); i != m_ActiveList.end(); i++)
	{
		UnitBase* base = (*i);
		base->AddPosition( 0.0f, -depth );
	}
}

UnitBase* UnitManager::GetNearUnit(const VECTOR &position, float r, bool searchEnemy, bool allFlag, UnitBase* self)
{
	UnitBase *ret = NULL;
	float min = 10000.0f;
	for(std::list<UnitBase*>::iterator i = m_ActiveList.begin(); i != m_ActiveList.end(); i++)
	{
		UnitBase* base = (*i);
		if( base == self ) continue;	// 自身は処理しない
		VECTOR u_position;
		u_position.x = base->m_x - position.x;
		u_position.y = base->m_y - position.y;
		float length = DXLibMath::Length( u_position );
		// 指定したサーチタイプのユニットのみ判定
		if( allFlag || ( base->m_MoveStatus == UnitBase::Enemy && searchEnemy) ||
			( base->m_MoveStatus != UnitBase::Enemy && !searchEnemy) )
		{
			if( min > length)
			{
				ret = base;
				min = length;
			}
		}
	}
	if( ret != NULL )
	{
		VECTOR u_position;
		u_position.x = ret->m_x;
		u_position.y = ret->m_y;
		// 一番近いユニットが射程外の場合
		if( !DXLibMath::CircleOnPoint( position, u_position, r) )
		{
			ret = NULL;
		}
	}
	return ret;
}

UnitBase* UnitManager::GetNearGuardian( float x, float y, float r, bool searchEnemy)
{
	UnitBase *ret = NULL;
	float min = 10000.0f;
	for(std::list<UnitBase*>::iterator i = m_ActiveList.begin(); i != m_ActiveList.end(); i++)
	{
		UnitBase* base = (*i);
		VECTOR u_position;
		u_position.x = base->m_x - x;
		u_position.y = base->m_y - y;
		float length = DXLibMath::Length( u_position );
		// 指定したサーチタイプのユニットのみ判定
		if( ( base->m_MoveStatus == UnitBase::Enemy && searchEnemy) ||
			( base->m_MoveStatus != UnitBase::Enemy && !searchEnemy) )
		{
			if( min > length && base->m_ID == UNIT_Guardian)
			{
				ret = base;
				min = length;
			}
		}
	}
	if( ret != NULL )
	{
		VECTOR u_position;
		u_position.x = ret->m_x;
		u_position.y = ret->m_y;
		VECTOR position;
		position.x = x;
		position.y = y;
		// 一番近いユニットが射程外の場合
		if( !DXLibMath::CircleOnPoint( position, u_position, r) )
		{
			ret = NULL;
		}
	}
	return ret;
}

std::list<UnitBase*>& UnitManager::GetAreaUnit(float x, float y, float r)
{
	m_ReturnBuffer.clear();
	VECTOR position;
	position.x = x;
	position.y = y;
	position.z = r;
	for(std::list<UnitBase*>::iterator i = m_ActiveList.begin(); i != m_ActiveList.end(); i++)
	{
		UnitBase* base = (*i);
		VECTOR pos;
		pos.x = base->m_x;
		pos.y = base->m_y;
		if( DXLibMath::CircleOnPoint( pos, position, r ) )
		{
			m_ReturnBuffer.push_back( base );
		}
	}
	return m_ReturnBuffer;
}

std::list<UnitBase*>& UnitManager::GetAll( void )
{
	return m_ActiveList;
}