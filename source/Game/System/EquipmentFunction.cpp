#include "EquipmentFunction.h"
#include "DataManager.h"
#include "UnitManager.h"
#include "DxLibMath.h"
#include "../Task/TaskFunction.h"

bool UsedEquipment( int value )
{
	DataManager &data = DataManager::GetInstance();
	for(int i = 0; i < 3; i++)
	{
		if( data.m_MogllStatus.equip[i] == value )
		{
			data.m_MogllStatus.equipStatus[i] = 5;
			return true;
		}
	}
	return false;
}

int EquipmentFunction_01( int value )
{
	if( UsedEquipment( DataManager::EqID_01 ) )
	{
		return static_cast<int>( value * DataManager::GetInstance().m_SystemData.equip[0].a * 0.01f );
	}
	return value;
}

void EquipmentFunction_02( int frame )
{
	if( frame % DataManager::GetInstance().m_SystemData.equip[1].a != 0 )	return;
	if( UsedEquipment( DataManager::EqID_02 ) )
	{
		DataManager &data = DataManager::GetInstance();
		data.m_MogllStatus.life += DataManager::GetInstance().m_SystemData.equip[1].b;
		if( data.m_MogllStatus.life > data.m_MogllStatus.maxLife )
		{
			data.m_MogllStatus.life = data.m_MogllStatus.maxLife;
		}
	}
}

void EquipmentFunction_03( void )
{
	DataManager &data = DataManager::GetInstance();
	if( UsedEquipment( DataManager::EqID_03 ) )
	{
		data.m_MogllStatus.maxResource = DataManager::GetInstance().m_SystemData.equip[2].a;
		if( data.m_MogllStatus.maxResource < data.m_MogllStatus.resource )
		{
			data.m_MogllStatus.resource = data.m_MogllStatus.maxResource;
		}
	}
	else
	{
		data.m_MogllStatus.maxResource = 1000;
		if( data.m_MogllStatus.resource > 1000)
		{
			data.m_MogllStatus.resource = 1000;
		}
	}
}

int EquipmentFunction_04( int damage )
{
	DataManager &data = DataManager::GetInstance();
	if( UsedEquipment( DataManager::EqID_04 ) && data.m_MogllStatus.currentUnitID != UNIT_NONE &&
		data.m_MogllStatus.unitCount[ data.m_MogllStatus.currentUnitID - 1 ] > 0 )
	{
		data.m_MogllStatus.unitCount[ data.m_MogllStatus.currentUnitID - 1 ]--;
		return 0;
	}
	return damage;
}

int EquipmentFunction_05( int value )
{
	if( UsedEquipment( DataManager::EqID_05 ) )
	{
		return static_cast<int>( value * DataManager::GetInstance().m_SystemData.equip[4].a * 0.01f );
	}
	return value;
}

float EquipmentFunction_06( float value )
{
	if( UsedEquipment( DataManager::EqID_06 ) )
	{
		return 1.0f;
	}
	return value;
}

int EquipmentFunction_07( int value )
{
	if( UsedEquipment( DataManager::EqID_07 ) )
	{
		return static_cast<int>(value * DataManager::GetInstance().m_SystemData.equip[6].a * 0.01f);
	}
	return value;
}

int EquipmentFunction_08( int value )
{
	if( UsedEquipment( DataManager::EqID_08 ) )
	{
		return static_cast<int>(value * DataManager::GetInstance().m_SystemData.equip[7].a * 0.01f);
	}
	return value;
}

float EquipmentFunction_09( float value )
{
	if( UsedEquipment( DataManager::EqID_09 ) )
	{
		return value * DataManager::GetInstance().m_SystemData.equip[8].a * 0.01f;
	}
	return value;
}

bool EquipmentFunction_10( void )
{
	if( UsedEquipment( DataManager::EqID_10 ) )
	{
		return true;
	}
	return false;
}

int EquipmentFunction_11( int value )
{
	if( UsedEquipment( DataManager::EqID_11 ) )
	{
		int damage = static_cast<int>(value * DataManager::GetInstance().m_SystemData.equip[10].a * 0.01f);
		if( value != 0 && damage <= 0 )
		{
			damage = 1;
		}
		return damage;
	}
	return value;
}

float EquipmentFunction_12( float value )
{
	if( UsedEquipment( DataManager::EqID_12 ) )
	{
		return value * DataManager::GetInstance().m_SystemData.equip[11].a * 0.01f;
	}
	return value;
}

void EquipmentFunction_13( int frame )
{
	if( frame % DataManager::GetInstance().m_SystemData.equip[12].a != 0 )	return;
	if( UsedEquipment( DataManager::EqID_13 ) )
	{
		DataManager &data = DataManager::GetInstance();
		data.m_MogllStatus.resource += DataManager::GetInstance().m_SystemData.equip[12].b;
		if( data.m_MogllStatus.resource > data.m_MogllStatus.maxResource )
		{
			data.m_MogllStatus.resource = data.m_MogllStatus.maxResource;
		}
	}
}

int EquipmentFunction_14( int value )
{
	// 敵のダメージを無効にする際、リソースを必要とする
	DataManager &data = DataManager::GetInstance();
	if( UsedEquipment( DataManager::EqID_14 ) && data.m_MogllStatus.resource > 0)
	{
		data.m_MogllStatus.resource--;
		return 0;
	}
	return value;
}

void EquipmentFunction_14_Dec( int frame )
{
	if( frame % DataManager::GetInstance().m_SystemData.equip[13].a != 0 )	return;
	if( UsedEquipment( DataManager::EqID_14 ) )
	{
		DataManager &data = DataManager::GetInstance();
		data.m_MogllStatus.resource -= DataManager::GetInstance().m_SystemData.equip[13].b;
		if( data.m_MogllStatus.resource < 0)
		{
			data.m_MogllStatus.resource = 0;
		}
	}
}

bool EquipmentFunction_15( void )
{
	if( UsedEquipment( DataManager::EqID_15 ))
	{
		return true;
	}
	return false;
}

bool EquipmentFunction_16( void )
{
	if( UsedEquipment( DataManager::EqID_16 ))
	{
		return true;
	}
	return false;
}
int EquipmentFunction_16_Value( int value )
{
	if( UsedEquipment( DataManager::EqID_16 ) )
	{
		return static_cast<int>( value * DataManager::GetInstance().m_SystemData.equip[15].a * 0.01f );
	}
	return value;
}

int EquipmentFunction_17_Block( int value )
{
	if( UsedEquipment( DataManager::EqID_17 ) )
	{
		return static_cast<int>( value * DataManager::GetInstance().m_SystemData.equip[16].a * 0.01f );
	}
	return value;
}

int EquipmentFunction_17_Enemy( int value )
{
	if( UsedEquipment( DataManager::EqID_17 ) )
	{
		return static_cast<int>( value * DataManager::GetInstance().m_SystemData.equip[16].b * 0.01f );
	}
	return value;
}

int EquipmentFunction_18_Block( int value )
{
	if( UsedEquipment( DataManager::EqID_18 ) )
	{
		return static_cast<int>( value * DataManager::GetInstance().m_SystemData.equip[17].b * 0.01f );
	}
	return value;
}

int EquipmentFunction_18_Enemy( int value )
{
	if( UsedEquipment( DataManager::EqID_18 ) )
	{
		return static_cast<int>( value * DataManager::GetInstance().m_SystemData.equip[17].a * 0.01f );
	}
	return value;
}

float EquipmentFunction_19( float value, bool isEnemy )
{
	if( UsedEquipment( DataManager::EqID_19 ) && !isEnemy )
	{
		return 0.0f;
	}
	return value;
}

int EquipmentFunction_20( int power, int *hp)
{
	if( UsedEquipment( DataManager::EqID_20 ) )
	{
		*hp -= static_cast<int>(power * DataManager::GetInstance().m_SystemData.equip[19].b * 0.01f);
		return static_cast<int>( power * DataManager::GetInstance().m_SystemData.equip[19].a * 0.01f );
	}
	return power;
}

void EquipmentFunction_21( int *type, float *time, float *value)
{
	if( UsedEquipment( DataManager::EqID_21 ) )
	{
		if( *type == UnitBase::DAMAGETYPE_NORMAL )
		{
			*type = UnitBase::DAMAGETYPE_RANG;
			*time = 1.0f * DataManager::GetInstance().m_SystemData.equip[20].a;
			*value = DataManager::GetInstance().m_SystemData.equip[20].b * 0.01f;
		}
	}
}

void EquipmentFunction_22( int *type, float *time)
{
	if( UsedEquipment( DataManager::EqID_22 ) )
	{
		if( *type == UnitBase::DAMAGETYPE_NORMAL )
		{
			*type = UnitBase::DAMAGETYPE_PARALYSIS;
			*time = 1.0f * DataManager::GetInstance().m_SystemData.equip[21].a;
		}
	}
}

void EquipmentFunction_23( int *type, float *time)
{
	if( UsedEquipment( DataManager::EqID_23 ) )
	{
		if( *type == UnitBase::DAMAGETYPE_NORMAL )
		{
			*type = UnitBase::DAMAGETYPE_STOP;
			*time = 1.0f * DataManager::GetInstance().m_SystemData.equip[22].a;
		}
	}
}

void EquipmentFunction_24( int *type, float *time, float *value)
{
	if( UsedEquipment( DataManager::EqID_24 ) )
	{
		if( *type == UnitBase::DAMAGETYPE_NORMAL )
		{
			*type = UnitBase::DAMAGETYPE_FIRE;
			*time = 1.0f * DataManager::GetInstance().m_SystemData.equip[23].a;
			*value = 1.0f * DataManager::GetInstance().m_SystemData.equip[23].b;
		}
	}
}

void EquipmentFunction_25( int *type, float *time)
{
	if( UsedEquipment( DataManager::EqID_25 ) )
	{
		if( *type == UnitBase::DAMAGETYPE_NORMAL )
		{
			*type = UnitBase::DAMAGETYPE_CONFUSION;
			*time = 1.0f * DataManager::GetInstance().m_SystemData.equip[24].a;
		}
	}
}

int EquipmentFunction_26( int value )
{
	if( UsedEquipment( DataManager::EqID_26 ) && value < DataManager::GetInstance().m_SystemData.equip[25].a)
	{
		return static_cast<int>( value * DataManager::GetInstance().m_SystemData.equip[25].b * 0.01f );
	}
	return value;
}

void EquipmentFunction_27( int *type, float *time, float *value1, float *value2)
{
	if( UsedEquipment( DataManager::EqID_27 ) )
	{
		*time *= DataManager::GetInstance().m_SystemData.equip[26].a * 0.01f;
		switch( *type )
		{
		case UnitBase::DAMAGETYPE_FIRE:
			*value1 *= DataManager::GetInstance().m_SystemData.equip[26].a * 0.01f;
			break;
		case UnitBase::DAMAGETYPE_ATTACKSPEED:
		case UnitBase::DAMAGETYPE_RANG:
		case UnitBase::DAMAGETYPE_SLOW:
			*value1 /= DataManager::GetInstance().m_SystemData.equip[26].a * 0.01f;
			break;
		default:
			break;
		}
	}
}

bool EquipmentFunction_28( void )
{
	if( UsedEquipment( DataManager::EqID_28 ))
	{
		return true;
	}
	return false;
}

float EquipmentFunction_29( float value )
{
	if( UsedEquipment( DataManager::EqID_29 ) )
	{
		return value * DataManager::GetInstance().m_SystemData.equip[28].a * 0.01f;
	}
	return value;
}

int EquipmentFunction_30( int value )
{
	if( UsedEquipment( DataManager::EqID_30 ) )
	{
		return static_cast<int>( value * DataManager::GetInstance().m_SystemData.equip[29].a * 0.01f );
	}
	return value;
}

void EquipmentFunction_31( int *type, float *time, float *value)
{
	if( UsedEquipment( DataManager::EqID_31 ) )
	{
		if( *type == UnitBase::DAMAGETYPE_NORMAL )
		{
			*type = UnitBase::DAMAGETYPE_ATTACKSPEED;
			*time = 1.0f * DataManager::GetInstance().m_SystemData.equip[30].a;
			*value = DataManager::GetInstance().m_SystemData.equip[30].b * 0.01f;
		}
	}
}


void EquipmentFunction_32( int *attack, float *range)
{
	if( UsedEquipment( DataManager::EqID_32 ) )
	{
		*attack = static_cast<int>( *attack * DataManager::GetInstance().m_SystemData.equip[31].b * 0.01f);
		*range *= DataManager::GetInstance().m_SystemData.equip[31].a * 0.01f;
		if( *range < 2.0f )
		{
			*range = 2.0f;
		}
	}
}

void EquipmentFunction_33( int frame )
{
	if( frame % DataManager::GetInstance().m_SystemData.equip[32].a != 0 )	return;
	if( UsedEquipment( DataManager::EqID_33 ) )
	{
		UnitManager &unitManager = UnitManager::GetInstance();
		DataManager &dataManager = DataManager::GetInstance();
		std::list<UnitBase*> &list = unitManager.GetAll();
		for( std::list<UnitBase*>::iterator i = list.begin(); i != list.end(); i++)
		{
			UnitBase* base = (*i);
			if( base->m_MoveStatus == UnitBase::Enemy )
			{
				continue;
			}
			base->m_Life += DataManager::GetInstance().m_SystemData.equip[32].b;
			if( base->m_Life > base->m_MaxLife )
			{
				base->m_Life = base->m_MaxLife;
			}
		}
	}
}

void EquipmentFunction_34( float x, float y )
{
	if( UsedEquipment( DataManager::EqID_34 ) )
	{
		TaskSet_FriendTargetSet( x, y );
	}
}

bool EquipmentFunction_35( int frame )
{
	if( UsedEquipment( DataManager::EqID_35 ) && frame % DataManager::GetInstance().m_SystemData.equip[34].a == 0)
	{
		return false;
	}
	return true;
}

float EquipmentFunction_36( float value )
{
	if( UsedEquipment( DataManager::EqID_36 ))
	{
		return value * DataManager::GetInstance().m_SystemData.equip[35].a * 0.01f;
	}
	return value;
}

int EquipmentFunction_37( int value )
{
	if( UsedEquipment( DataManager::EqID_37 ) )
	{
		return static_cast<int>( value * DataManager::GetInstance().m_SystemData.equip[36].a * 0.01f );
	}
	return value;
}

int EquipmentFunction_38( int value )
{
	if( UsedEquipment( DataManager::EqID_38 ) )
	{
		return static_cast<int>( value * DataManager::GetInstance().m_SystemData.equip[37].a * 0.01f );
	}
	return value;
}

int EquipmentFunction_39( int value )
{
	if( UsedEquipment( DataManager::EqID_39 ) )
	{
		return static_cast<int>( value * DataManager::GetInstance().m_SystemData.equip[38].a * 0.01f );
	}
	return value;
}

float EquipmentFunction_40( float value )
{
	if( UsedEquipment( DataManager::EqID_40 ) )
	{
		return value * DataManager::GetInstance().m_SystemData.equip[39].a * 0.01f;
	}
	return value;
}

void EquipmentFunction_41( UnitBase* base )
{
	if( UsedEquipment( DataManager::EqID_41 ) && base->m_MoveStatus != UnitBase::Enemy && base->m_DamageSrc )
	{
		TaskSet_DrawExplod( base->m_x, base->m_y );
		TaskSet_AreaUnitDamage( base->m_x, base->m_y, DataManager::GetInstance().m_SystemData.equip[40].b,
			DataManager::GetInstance().m_SystemData.equip[40].a * 0.01f );
	}
}

float EquipmentFunction_42( float value )
{
	if( UsedEquipment( DataManager::EqID_42 ))
	{
		return value * DataManager::GetInstance().m_SystemData.equip[41].a * 0.01f;
	}
	return value;
}

void EquipmentFunction_43( float x, float y )
{
	if( UsedEquipment( DataManager::EqID_43 ) )
	{
		TaskSet_FriendReact( x, y );
	}
}

void EquipmentFunction_44( int frame )
{
	if( frame % 5 != 0 )	return;
	if( UsedEquipment( DataManager::EqID_44 ) )
	{
		VECTOR position;
		position = DataManager::GetInstance().m_MogllStatus.position;
		DXLibMath::ConvertScreenToBlock( position.x, position.y, &position.x, &position.y );
		VECTOR damageData;
		damageData.x = 5.0f;
		damageData.y = DataManager::GetInstance().m_SystemData.equip[43].b * 0.01f;
		TaskSet_AreaUnitBadStatusFriend( position.x, position.y, 0, DataManager::GetInstance().m_SystemData.equip[43].a * 0.01f,
			UnitBase::DAMAGETYPE_SLOW, damageData, false);
	}
}

int EquipmentFunction_45( int value )
{
	if( UsedEquipment( DataManager::EqID_45 ) )
	{
		return DataManager::GetInstance().m_SystemData.equip[44].a;
	}
	return value;
}

bool EquipmentFunction_46( void )
{
	if( UsedEquipment( DataManager::EqID_46 ) )
	{
		DataManager &data = DataManager::GetInstance();
		if( data.m_MogllStatus.resource >= DataManager::GetInstance().m_SystemData.equip[45].a)
		{
			data.m_MogllStatus.resource -= DataManager::GetInstance().m_SystemData.equip[45].a;
			data.m_MogllStatus.life = 1;
			return false;
		}
	}
	return true;
}

int EquipmentFunction_47( int value )
{
	if( UsedEquipment( DataManager::EqID_47 ) )
	{
		if( value == 0 )
		{
			return DataManager::GetInstance().m_SystemData.equip[46].a;
		}
	}
	return value;
}

void EquipmentFunction_48( int frame )
{
	//if( frame % 2 != 0 )	return;
	if( UsedEquipment( DataManager::EqID_48 ) )
	{
		UnitManager &unitManager = UnitManager::GetInstance();
		std::list<UnitBase*> &list = unitManager.GetAll();
		for( std::list<UnitBase*>::iterator i = list.begin(); i != list.end(); i++)
		{
			UnitBase* base = (*i);
			if( base->m_MoveStatus != UnitBase::Enemy )
			{
				base->m_y += 0.001f * DataManager::GetInstance().m_SystemData.equip[47].a;
			}
		}
	}
}

void EquipmentFunction_49( int frame )
{
	if( frame % DataManager::GetInstance().m_SystemData.equip[48].a != 0 )	return;
	if( UsedEquipment( DataManager::EqID_49 ) )
	{
		DataManager &data = DataManager::GetInstance();
		VECTOR startPoint, movePoint;
		DXLibMath::ConvertScreenToBlock( data.m_MogllStatus.position.x, data.m_MogllStatus.position.y,
			&startPoint.x, &startPoint.y );
		int unitID = data.m_MogllStatus.equipUnit[GetRand( 5 )] + 1;
		if( 31 == unitID )
		{
			return;
		}
		movePoint.x = static_cast<float>( GetRand(14) * 1.0f + 0.5f );
		movePoint.y = static_cast<float>( GetRand(6) * 1.0f + 5.5f );

		UnitManager &unitManager = UnitManager::GetInstance();
		unitManager.Add( startPoint, movePoint, unitID, UnitBase::MovePoint );
	}
}

void EquipmentFunction_50( int frame )
{
	if( frame % DataManager::GetInstance().m_SystemData.equip[49].a != 0 )	return;
	if( UsedEquipment( DataManager::EqID_50 ) )
	{
		UnitManager &unitManager = UnitManager::GetInstance();
		std::list<UnitBase*> &list = unitManager.GetAll();
		bool flag = true;
		for(std::list<UnitBase*>::iterator i = list.begin(); i != list.end(); i++)
		{
			if( (*i)->m_MoveStatus == UnitBase::Enemy )
			{
				flag = false;
				break;
			}
		}
		if( flag )
		{
			DataManager &data = DataManager::GetInstance();
			data.m_MogllStatus.life += DataManager::GetInstance().m_SystemData.equip[49].b;
			if( data.m_MogllStatus.life > data.m_MogllStatus.maxLife )
			{
				data.m_MogllStatus.life = data.m_MogllStatus.maxLife;
			}
			data.m_MogllStatus.resource += DataManager::GetInstance().m_SystemData.equip[49].b;
			if( data.m_MogllStatus.resource > data.m_MogllStatus.maxResource )
			{
				data.m_MogllStatus.resource = data.m_MogllStatus.maxResource;
			}
		}
	}
}

void EquipmentFunction_51( int *type, float *time, float *value)
{
	if( UsedEquipment( DataManager::EqID_51 ) )
	{
		if( *type == UnitBase::DAMAGETYPE_NORMAL )
		{
			*type = UnitBase::DAMAGETYPE_SLOW;
			*time = 1.0f * DataManager::GetInstance().m_SystemData.equip[50].a;
			*value = DataManager::GetInstance().m_SystemData.equip[50].b * 0.01f;
		}
	}
}

void EquipmentFunction_52( UnitBase* base )
{
	if( UsedEquipment( DataManager::EqID_52 ) && base->m_MoveStatus == UnitBase::Enemy && base->m_DamageSrc )
	{
		TaskSet_DrawExplod( base->m_x, base->m_y );
		TaskSet_AreaUnitDamage( base->m_x, base->m_y, DataManager::GetInstance().m_SystemData.equip[51].b,
			DataManager::GetInstance().m_SystemData.equip[51].a * 0.01f);
	}
}

void EquipmentFunction_53( void )
{
	if( UsedEquipment( DataManager::EqID_53 ) )
	{
		DataManager &data = DataManager::GetInstance();
		data.m_MogllStatus.life += DataManager::GetInstance().m_SystemData.equip[52].a;
		if( data.m_MogllStatus.life > data.m_MogllStatus.maxLife )
		{
			data.m_MogllStatus.life = data.m_MogllStatus.maxLife;
		}
	}
}

void EquipmentFunction_54( int frame )
{
	if( frame % DataManager::GetInstance().m_SystemData.equip[53].a != 0 )	return;
	if( UsedEquipment( DataManager::EqID_54 ) )
	{
		UnitManager &unitManager = UnitManager::GetInstance();
		VECTOR position;
		position = DataManager::GetInstance().m_MogllStatus.position;
		DXLibMath::ConvertScreenToBlock( position.x, position.y, &position.x, &position.y );
		UnitBase* base = unitManager.GetNearUnit( position, 3.0f, true );
		if( base != NULL)
		{
			TaskSet_Shot( DataManager::GetInstance().m_SystemData.equip[53].b, UnitBase::DAMAGETYPE_NORMAL, position, position.x, position.y,
				base->m_x, base->m_y, false, false, NULL);
		}
	}
}

void EquipmentFunction_55( int *type, float *time, float *x, float *y, float dx, float dy)
{
	if( UsedEquipment( DataManager::EqID_55 ) )
	{
		if( *type == UnitBase::DAMAGETYPE_NORMAL )
		{
			*type = UnitBase::DAMAGETYPE_MOVE;
			*time = 1.0f * DataManager::GetInstance().m_SystemData.equip[54].a;
			*x = dx * 4.0f;
			*y = dy * 4.0f;
		}
	}
}

int EquipmentFunction_56( int value )
{
	if( UsedEquipment( DataManager::EqID_56 ) )
	{
		return static_cast<int>( value * DataManager::GetInstance().m_SystemData.equip[55].a * 0.01f );
	}
	return value;
}

bool EquipmentFunction_57( void )
{
	if( UsedEquipment( DataManager::EqID_57 ) )
	{
		return true;
	}
	return false;
}

void EquipmentFunction_58( int frame )
{
	if( frame % DataManager::GetInstance().m_SystemData.equip[57].a != 0 )	return;
	if( UsedEquipment( DataManager::EqID_58 ) )
	{
		UnitManager &unitManager = UnitManager::GetInstance();
		std::list<UnitBase*> &list = unitManager.GetAll();
		for( std::list<UnitBase*>::iterator i = list.begin(); i != list.end(); i++)
		{
			UnitBase* base = (*i);
			VECTOR damageData;
			if( base->m_MoveStatus != UnitBase::Enemy )
			{
				TaskSet_AreaUnitBadStatusFriend( base->m_x, base->m_y,
					DataManager::GetInstance().m_SystemData.equip[57].b, 1.0f, UnitBase::DAMAGETYPE_NORMAL, damageData, false);
				TaskSet_AreaBlockDamage( base->m_x, base->m_y,
					DataManager::GetInstance().m_SystemData.equip[57].b, 1.0f );
			}
		}
	}
}

void EquipmentFunction_59( int frame )
{
	if( frame % DataManager::GetInstance().m_SystemData.equip[58].a != 0 )	return;
	if( UsedEquipment( DataManager::EqID_59 ) )
	{
		UnitManager &unitManager = UnitManager::GetInstance();
		std::list<UnitBase*> &list = unitManager.GetAll();
		for( std::list<UnitBase*>::iterator i = list.begin(); i != list.end(); i++)
		{
			UnitBase* base = (*i);
			VECTOR data;
			base->AddDamage( DataManager::GetInstance().m_SystemData.equip[58].b, UnitBase::DAMAGETYPE_NORMAL, data, NULL);
		}
	}
}

void EquipmentFunction_60( void )
{
	if( UsedEquipment( DataManager::EqID_60 ) )
	{
		DataManager &data = DataManager::GetInstance();
		data.m_MogllStatus.resource = DataManager::GetInstance().m_SystemData.equip[59].a;
	}
}