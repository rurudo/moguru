#include "PlayUserInterface.h"
#include "../System/GameInput.h"
#include "../System/UnitManager.h"
#include "../System/DataManager.h"
#include "../System/BlockManager.h"
#include "../System/EquipmentFunction.h"

PlayUserInterface::PlayUserInterface(void)
{
	m_FieldRect.x = 0.0f;
	m_FieldRect.y = 0.0f;
	m_FieldRect.width = 0.75f;
	m_FieldRect.height = 12.9f / 15.0f;
	DataManager::GetInstance().m_MogllStatus.currentUnitID = UNIT_NONE;
	m_LinePos = -0.4f;
	m_LineCount = 0;
	memset( m_DrawObject, 0, sizeof( m_DrawObject ) );
	m_NumObject = 0;
	m_CurrentPosition = 0;
	//脱出ボタンパラメータ
	ESC_IN_POS = 0.912f;
	ESC_OUT_POS = 0.96f;
	ESC_BUTTON_WIDTH = 0.08875f;
	ESC_BUTTON_HEIGHT = 0.1167f;
	m_EscButton = ESC_OUT_POS;
	m_GetOut = false;
	ClearButtonSize();	//確認ボタンサイズ初期化
	//フィールドエフェクト位置
	FIELD_EFFECT_WIDTH = 600.0f/ 800.0f;
	FIELD_EFFECT_HEIGHT = 468.0f/ 600.0f;
	for(int i=0; i<2; i++)
	{
		m_FieldEffect[i].x = 0.0f;
		m_FieldEffect[i].y = FIELD_EFFECT_HEIGHT;
		m_FieldEffect[i].z = 1.0f;//α値として使用
		m_EffectAlpha[i]   = 128.0f;
	}	
	m_PrevLife = 1000;
	m_DamageCount = 0;
	m_VisibleFlag = true;
	m_EscapeFlag = false;
	m_Retry = false;
	// 独自フォントを使用
	m_Font.Load( FontManager::FontSet_AZUKI_25 );

	Init();
}


PlayUserInterface::~PlayUserInterface(void)
{
}

void PlayUserInterface::Init(void)
{
	DataManager &data = DataManager::GetInstance();
	for(int i=0;i<3;i++){
		data.m_MogllStatus.equip[i] = data.m_SaveData.equipItem[i];
	}
	for(int i=0;i<6;i++){
		data.m_MogllStatus.equipUnit[i] = data.m_SaveData.equipUnit[i];
	}

	DataManager::GetInstance().m_MogllStatus.currentUnitID = data.m_MogllStatus.equipUnit[m_CurrentPosition]+1;	// Noneの分１増やす
	// 装備なしを選んだ場合は
	if( DataManager::GetInstance().m_MogllStatus.currentUnitID == 31 )
	{
		DataManager::GetInstance().m_MogllStatus.currentUnitID = UNIT_NONE;
	}
}

void PlayUserInterface::Input(void)
{
	GameInput &input = GameInput::GetInstance();
	DataManager &data = DataManager::GetInstance();
	m_Mouse.x = input.GetXf();
	m_Mouse.y = input.GetYf();
	// フィールド上をクリックするとユニットを生成する
	if( input.GetMouse( GameInput::MouseLeftTrg ) &&
		m_FieldRect.x <= m_Mouse.x && m_Mouse.x <= m_FieldRect.x + m_FieldRect.width &&
		m_FieldRect.y <= m_Mouse.y && m_Mouse.y <= m_FieldRect.y + m_FieldRect.height &&
		data.m_MogllStatus.currentUnitID != UNIT_NONE )
	{
		int cost = EquipmentFunction_01( data.m_SystemData.unit[ data.m_MogllStatus.currentUnitID - 1].cost );
		int unitCount = data.m_MogllStatus.unitCount[ data.m_MogllStatus.currentUnitID - 1 ];
		//if( data.m_MogllStatus.resource >= cost && unitCount > 0 )
		if( unitCount > 0 )
		{
			data.m_MogllStatus.unitCount[ data.m_MogllStatus.currentUnitID - 1 ]--;
			UnitManager &unitManager = UnitManager::GetInstance();
			VECTOR startPoint;
			DXLibMath::ConvertScreenToBlock( data.m_MogllStatus.position.x, data.m_MogllStatus.position.y,
				&startPoint.x, &startPoint.y );
			VECTOR movePoint;
			DXLibMath::ConvertScreenToBlock( m_Mouse.x, m_Mouse.y, &movePoint.x, &movePoint.y );
			// モグル基準点が左上なので補正
			startPoint.x += 1.0f;
			startPoint.y += 1.0f;
			// 装備分岐
			if( EquipmentFunction_57() )
			{
				unitManager.Add( movePoint, movePoint, DataManager::GetInstance().m_MogllStatus.currentUnitID, UnitBase::Free );
			}
			else
			{
				unitManager.Add( startPoint, movePoint, DataManager::GetInstance().m_MogllStatus.currentUnitID, UnitBase::MovePoint );
			}
			//EquipmentFunction_34( movePoint.x, movePoint.y );
			EquipmentFunction_43( movePoint.x, movePoint.y );
			data.m_MogllStatus.resource -= cost;
			if( data.m_MogllStatus.resource < 0 )
			{
				data.m_MogllStatus.resource = 0;
			}
			PlaySoundMem( data.Get( DataManager::SoundSE20 ), DX_PLAYTYPE_BACK);
		}
	}
	// 下のエリアをクリックすると
	else if( input.GetMouse( GameInput::MouseLeftTrg ) &&
		m_FieldRect.x <= m_Mouse.x && m_Mouse.x <= m_FieldRect.x + m_FieldRect.width &&
		m_FieldRect.height <= m_Mouse.y && m_Mouse.y <= 1.0f )
	{
		for(int i = 0; i < 6; i++)
		{
			float rang = static_cast<float>(i);
			if( m_FieldRect.x + m_FieldRect.width * rang / 6.0f <= m_Mouse.x &&
				m_Mouse.x <= m_FieldRect.x + m_FieldRect.width * (rang + 1.0f) / 6.0f)
			{
				m_CurrentPosition = i;
				DataManager::GetInstance().m_MogllStatus.currentUnitID = data.m_MogllStatus.equipUnit[i] + 1;	// Noneの分１増やす
				// 装備なしを選んだ場合は
				if( DataManager::GetInstance().m_MogllStatus.currentUnitID == 31 )
				{
					DataManager::GetInstance().m_MogllStatus.currentUnitID = UNIT_NONE;
				}
				PlaySoundMem( data.Get( DataManager::SoundSE19 ), DX_PLAYTYPE_BACK);
			}
		}
	}
	// 誘導AI
	VECTOR movePoint;
	DXLibMath::ConvertScreenToBlock( m_Mouse.x, m_Mouse.y, &movePoint.x, &movePoint.y );
	EquipmentFunction_34( movePoint.x, movePoint.y );
	// マウスロール発進ユニット選択
	if( input.GetMouseWheelUp())
	{
		PlaySoundMem( data.Get( DataManager::SoundSE19 ), DX_PLAYTYPE_BACK);
		m_CurrentPosition--;
		if( m_CurrentPosition < 0 )
		{
			m_CurrentPosition = 5;
		}
		DataManager::GetInstance().m_MogllStatus.currentUnitID = data.m_MogllStatus.equipUnit[m_CurrentPosition] + 1;	// Noneの分１増やす
		// 装備なしを選んだ場合は
		if( DataManager::GetInstance().m_MogllStatus.currentUnitID == 31 )
		{
			DataManager::GetInstance().m_MogllStatus.currentUnitID = UNIT_NONE;
		}
	}
	if( input.GetMouseWheelDown())
	{
		PlaySoundMem( data.Get( DataManager::SoundSE19 ), DX_PLAYTYPE_BACK);

		m_CurrentPosition++;
		if( m_CurrentPosition > 5 )
		{
			m_CurrentPosition = 0;
		}
		DataManager::GetInstance().m_MogllStatus.currentUnitID = data.m_MogllStatus.equipUnit[m_CurrentPosition] + 1;	// Noneの分１増やす
		// 装備なしを選んだ場合は
		if( DataManager::GetInstance().m_MogllStatus.currentUnitID == 31 )
		{
			DataManager::GetInstance().m_MogllStatus.currentUnitID = UNIT_NONE;
		}
	}

	////ユニットを選択:数字キー
	if(GameInput::GetInstance().GetKeyTrg(KEY_INPUT_1))
	{
		PlaySoundMem( data.Get( DataManager::SoundSE19 ), DX_PLAYTYPE_BACK);
		m_CurrentPosition = 0;
		DataManager::GetInstance().m_MogllStatus.currentUnitID = data.m_MogllStatus.equipUnit[m_CurrentPosition] + 1;	// Noneの分１増やす
		// 装備なしを選んだ場合は
		if( DataManager::GetInstance().m_MogllStatus.currentUnitID == 31 )
		{
			DataManager::GetInstance().m_MogllStatus.currentUnitID = UNIT_NONE;
		}
	}
	if(GameInput::GetInstance().GetKeyTrg(KEY_INPUT_2))
	{
		PlaySoundMem( data.Get( DataManager::SoundSE19 ), DX_PLAYTYPE_BACK);
		m_CurrentPosition = 1;
		DataManager::GetInstance().m_MogllStatus.currentUnitID = data.m_MogllStatus.equipUnit[m_CurrentPosition] + 1;	// Noneの分１増やす
		// 装備なしを選んだ場合は
		if( DataManager::GetInstance().m_MogllStatus.currentUnitID == 31 )
		{
			DataManager::GetInstance().m_MogllStatus.currentUnitID = UNIT_NONE;
		}
	}
	if(GameInput::GetInstance().GetKeyTrg(KEY_INPUT_3))
	{
		PlaySoundMem( data.Get( DataManager::SoundSE19 ), DX_PLAYTYPE_BACK);
		m_CurrentPosition = 2;
		DataManager::GetInstance().m_MogllStatus.currentUnitID = data.m_MogllStatus.equipUnit[m_CurrentPosition] + 1;	// Noneの分１増やす
		// 装備なしを選んだ場合は
		if( DataManager::GetInstance().m_MogllStatus.currentUnitID == 31 )
		{
			DataManager::GetInstance().m_MogllStatus.currentUnitID = UNIT_NONE;
		}
	}
	if(GameInput::GetInstance().GetKeyTrg(KEY_INPUT_4))
	{
		PlaySoundMem( data.Get( DataManager::SoundSE19 ), DX_PLAYTYPE_BACK);
		m_CurrentPosition = 3;
		DataManager::GetInstance().m_MogllStatus.currentUnitID = data.m_MogllStatus.equipUnit[m_CurrentPosition] + 1;	// Noneの分１増やす
		// 装備なしを選んだ場合は
		if( DataManager::GetInstance().m_MogllStatus.currentUnitID == 31 )
		{
			DataManager::GetInstance().m_MogllStatus.currentUnitID = UNIT_NONE;
		}
	}
	if(GameInput::GetInstance().GetKeyTrg(KEY_INPUT_5))
	{
		PlaySoundMem( data.Get( DataManager::SoundSE19 ), DX_PLAYTYPE_BACK);
		m_CurrentPosition = 4;
		DataManager::GetInstance().m_MogllStatus.currentUnitID = data.m_MogllStatus.equipUnit[m_CurrentPosition] + 1;	// Noneの分１増やす
		// 装備なしを選んだ場合は
		if( DataManager::GetInstance().m_MogllStatus.currentUnitID == 31 )
		{
			DataManager::GetInstance().m_MogllStatus.currentUnitID = UNIT_NONE;
		}
	}
	if(GameInput::GetInstance().GetKeyTrg(KEY_INPUT_6))
	{
		PlaySoundMem( data.Get( DataManager::SoundSE19 ), DX_PLAYTYPE_BACK);
		m_CurrentPosition = 5;
		DataManager::GetInstance().m_MogllStatus.currentUnitID = data.m_MogllStatus.equipUnit[m_CurrentPosition] + 1;	// Noneの分１増やす
		// 装備なしを選んだ場合は
		if( DataManager::GetInstance().m_MogllStatus.currentUnitID == 31 )
		{
			DataManager::GetInstance().m_MogllStatus.currentUnitID = UNIT_NONE;
		}
	}
}

void PlayUserInterface::Update(void)
{
	Input();
	m_LinePos += 0.015f;//0.005f;
	m_LineCount++;
	if( m_LinePos > 0.6f )
	{
		m_LinePos = -0.4f;
		m_LineCount = 0;
	}
	RadarCalc();
}

void PlayUserInterface :: UpdateEffect(void)
{
	
	//データマネージャ取得
	DataManager &data = DataManager::GetInstance();
	//4枚描画
	switch(data.m_SceneInt["StageNo"]){
		case 0:// 地下都市
			//移動
			m_FieldEffect[0].x += 0.001f;
			m_FieldEffect[0].y -= 0.0002f;
			m_FieldEffect[1].x += 0.0006f;
			m_FieldEffect[1].y -= 0.0006f;
			//α値
			m_EffectAlpha[0] += m_FieldEffect[0].z;
			m_EffectAlpha[1] += m_FieldEffect[1].z;
			if(m_EffectAlpha[0] >= 192.0f || m_EffectAlpha[0] < 64.0f) m_FieldEffect[0].z = -m_FieldEffect[0].z;
			break;

		case 1:// 氷河
			//移動
			m_FieldEffect[0].x += 0.0015f;
			m_FieldEffect[0].y -= 0.0018f;
			m_FieldEffect[1].x += 0.0006f;
			m_FieldEffect[1].y -= 0.0006f;
			//α値
			m_EffectAlpha[0] += m_FieldEffect[0].z;
			m_EffectAlpha[1] += m_FieldEffect[1].z;
			if(m_EffectAlpha[0] >= 255.0f || m_EffectAlpha[0] < 0.0f) m_FieldEffect[0].z = -m_FieldEffect[0].z;
			break;

		case 2:// 沼地
			//移動
			m_FieldEffect[0].x -= 0.0015f;
			m_FieldEffect[0].y -= 0.0018f;
			m_FieldEffect[1].x -= 0.0009f;
			m_FieldEffect[1].y -= 0.0006f;
			//α値
			m_EffectAlpha[0] += m_FieldEffect[0].z;
			m_EffectAlpha[1] += m_FieldEffect[1].z;
			if(m_EffectAlpha[0] >= 255.0f) m_FieldEffect[0].z = -m_FieldEffect[0].z;
			break;

		case 3:// 火山
			//移動
			m_FieldEffect[0].x += 0.0015f;
			m_FieldEffect[0].y -= 0.0018f;
			m_FieldEffect[1].x += 0.0006f;
			m_FieldEffect[1].y -= 0.0006f;
			//α値
			m_EffectAlpha[0] += m_FieldEffect[0].z;
			m_EffectAlpha[1] += m_FieldEffect[1].z;
			if(m_EffectAlpha[0] >= 192.0f || m_EffectAlpha[0] < 64.0f) m_FieldEffect[0].z = -m_FieldEffect[0].z;
			break;

		case 4:// 近未来
			//移動
			m_FieldEffect[0].x -= 0.0015f;
			m_FieldEffect[0].y -= 0.0018f;
			m_FieldEffect[1].x -= 0.0006f;
			m_FieldEffect[1].y -= 0.0004f;
			//α値
			break;

		default :
			break;
	}

	for(int i=0; i<2; i++)
	{
		//位置ループ
		if(m_FieldEffect[i].x > FIELD_EFFECT_WIDTH)		m_FieldEffect[i].x = 0.0f;
		if(m_FieldEffect[i].y > FIELD_EFFECT_HEIGHT)	m_FieldEffect[i].y = 0.0f;
		if(m_FieldEffect[i].x < 0.0f)	m_FieldEffect[i].x = FIELD_EFFECT_WIDTH;
		if(m_FieldEffect[i].y < 0.0f)	m_FieldEffect[i].y = FIELD_EFFECT_HEIGHT;
		//α値制限
		if(m_EffectAlpha[i] < 0.0f) m_EffectAlpha[i] = 0.0f;
		if(m_EffectAlpha[i] > 255.0f) m_EffectAlpha[i] = 255.0f;
	}
}

void PlayUserInterface :: UpdateButton(void)
{
	GameInput &input = GameInput::GetInstance();
	float x = input.GetXf();
	float y = input.GetYf();

	static bool l_SEflag = false;

	// 脱出確認
	if(m_EscapeFlag == true){
		if(input.GetMouse(GameInput::MouseLeftTrg)){
			// ボタンの範囲指定
			if(y >= 0.6f && y <= 0.7f){
				// ステージセレクト
				if(x >= 0.34f && x<= 0.44f){
					PlaySoundMem( DataManager::GetInstance().Get( DataManager::SoundSE28 ), DX_PLAYTYPE_BACK);
					m_GetOut = true;
				}
				// リトライ
				else if(x >= 0.45f && x<= 0.55f){
					PlaySoundMem( DataManager::GetInstance().Get( DataManager::SoundSE28 ), DX_PLAYTYPE_BACK);
					m_Retry = true;
					m_EscapeFlag = false;
				}
				// キャンセル
				else if(x >= 0.56f && x<= 0.66f){
					PlaySoundMem( DataManager::GetInstance().Get( DataManager::SoundSE06 ), DX_PLAYTYPE_BACK);
					m_EscapeFlag = false;
				}
			}
		}
		if(input.GetMouse(GameInput::MouseRightTrg))
		{
			PlaySoundMem( DataManager::GetInstance().Get( DataManager::SoundSE06 ), DX_PLAYTYPE_BACK);
			m_EscapeFlag = false;
		}
	}
	//脱出確認ボタンサイズ更新
	// ボタンの範囲指定
		for(int i=0; i<3; i++){
			if(	x >= 0.34f+((float)i*0.11f) && x<= 0.44f+((float)i*0.11f) &&
				y >= 0.6f && y <= 0.7f && m_EscapeFlag){
				m_EscChkButtonSize[i] += (0.6f - m_EscChkButtonSize[i])*0.2f;
				//SE
				if(!m_EscChkSEFlg[i]){
					PlaySoundMem( DataManager::GetInstance().Get( DataManager::SoundSE07 ), DX_PLAYTYPE_BACK);
					m_EscChkSEFlg[i] = true;
				}

			}
			else{
				m_EscChkButtonSize[i] += (0.5f - m_EscChkButtonSize[i])*0.2f;
				m_EscChkSEFlg[i] = false;
			}
		}

	//脱出ボタン
	//マウス位置判定
	if( y > 0.61f && y < 0.61f+ESC_BUTTON_HEIGHT &&
		x > m_EscButton)
	{
		m_EscButton += (ESC_IN_POS - m_EscButton)*0.1f;

		if(!l_SEflag){
			PlaySoundMem( DataManager::GetInstance().Get( DataManager::SoundSE07 ), DX_PLAYTYPE_BACK);
			l_SEflag = true;
		}

		//ボタンクリック時の処理
		if(input.GetMouse( GameInput::MouseLeftTrg ) && x < (m_EscButton + ESC_BUTTON_WIDTH)){
			m_EscapeFlag = true;
			PlaySoundMem( DataManager::GetInstance().Get( DataManager::SoundSE28 ), DX_PLAYTYPE_BACK);
		}
	}
	else if(!m_EscapeFlag)
	{
		m_EscButton += (ESC_OUT_POS - m_EscButton)*0.1f;
		l_SEflag = false;
	}
}

void PlayUserInterface::AddObject(int x, int y, int id)
{
	for(int i = 0; i < OBJECT_MAX; i++)
	{
		if( !m_DrawObject[i].exist )
		{
			m_DrawObject[i].exist = true;
			m_DrawObject[i].alpha = 255;
			m_DrawObject[i].x = 638 + 8 * x;
			m_DrawObject[i].y = 20 + 12 * y;
			m_DrawObject[i].id = id;
			m_DrawObject[i].size = 0.1;
			break;
		}
	}
}

void PlayUserInterface::RadarCalc(void)
{
	BlockManager &blockManager = BlockManager::GetInstance();

	if( m_LineCount < 24 && m_LineCount % 4 == 0 )
	{
		int height = m_LineCount / 2;
		std::list<UnitBase*> &list = UnitManager::GetInstance().GetAll();
		for(std::list<UnitBase*>::iterator i= list.begin(); i != list.end(); i++)
		{
			int x, y;
			x = static_cast<int>((*i)->m_x);
			y = static_cast<int>((*i)->m_y);
			if( (*i)->m_MoveStatus == UnitBase::Enemy && y - 1 <= height && height <= y + 1 )
			{
				if((*i)->m_TreasureID != -1 )
				{
					AddObject( x, y + 2, 0);
				}
				else
				{
					AddObject( x, y + 2, 1);
				}
			}
		}
	}
	else if( m_LinePos < 0.3f && m_LineCount % 2== 0)
	{
		int depth = static_cast<int>( blockManager.GetDepth() + 12);
		int height = (m_LineCount - 24 ) / 2;
		depth += height;
		for(int i = 0; i < 15; i++)
		{
			// 敵が見つかったらレーダー表示物に加える
			int id = blockManager.GetEnemyID( i, depth );
			if( id != -1 )
			{
				AddObject( i, height + 12, 1 );
			}
		}
	}
	if( m_LinePos < 0.3f && m_LineCount % 2== 0)
	{
		int depth = static_cast<int>( blockManager.GetDepth() + 12);
		int height = (m_LineCount - 24 ) / 2;
		depth += height;
		for(int i = 0; i < 15; i++)
		{
			// 宝が見つかったらレーダー表示物に加える
			int enemy;
			int id = blockManager.GetTreasureID( i, depth, &enemy );
			if( id != -1 )
			{
				AddObject( i, height + 12, 0 );
			}
		}
	}
	for( int i = 0; i < OBJECT_MAX; i++)
	{
		if( m_DrawObject[i].exist )
		{
			m_DrawObject[i].alpha -= 7;
			m_DrawObject[i].size *= 1.03;
			if( m_DrawObject[i].alpha <= 0 )
			{
				m_DrawObject[i].exist = false;
			}
		}
	}
}

void PlayUserInterface::UpdateLife(void)
{
	DataManager &data = DataManager::GetInstance();
	if( data.m_MogllStatus.life < 0 )
	{
		data.m_MogllStatus.life = 0;
	}
	double targetRot = 3.1415 * (0.75 + 1.5 * data.m_MogllStatus.life / data.m_MogllStatus.maxLife);
	m_LifeRot = targetRot;
	if( data.m_MogllStatus.resource > data.m_MogllStatus.maxResource )
	{
		targetRot = 3.1415 * (1.25 - 1.5);
	}
	else
	{
		targetRot = 3.1415 * (1.25 - 1.5 * data.m_MogllStatus.resource / data.m_MogllStatus.maxResource);
	}
	m_ResourceRot = targetRot;
	if( m_PrevLife > data.m_MogllStatus.life )
	{
		m_DamageCount = 30;
	}
	m_PrevLife = data.m_MogllStatus.life;
}

void PlayUserInterface::DrawMogll(void)
{
	DataManager &data = DataManager::GetInstance();
	int frame = GameInput::GetInstance().GetFrame();
	float depth = BlockManager::GetInstance().GetDepth() + data.m_MogllStatus.position.y * 600.0f / 40.0f;
	float offset = 0.0f;
	// 振動させる
	//if( frame % 4 < 2)
	//{
	//	offset = 0.01f;
	//}
	int index = data.m_MogllStatus.life / 250;
	if( index > 3 )
	{
		index = 3;
	}
	index = (1 + 3 - index) + 5 * (( frame / 8 ) % 4);
	index += DataManager::GG_MOGLL_BODY_1_1;
	DXLibMath::DrawExtendGraphResize( data.m_MogllStatus.position.x,
		data.m_MogllStatus.position.y - 0.08f + offset, 0.07f, 0.1f,
		data.GetGraphicGroupData( index ), TRUE );
	int drillHandle = data.GetGraphicGroupData( DataManager::GG_PLAYER_Drill01 + (frame / 4) % 4);
	if( depth <= -0.7f )// 0.8fはモグルの高さ分
	{
		drillHandle = data.Get( DataManager::GG_PLAYER_Drill01 );
	}
	DXLibMath::DrawExtendGraphResize(
		data.m_MogllStatus.position.x,
		data.m_MogllStatus.position.y + offset,
		0.07f, 0.1f,
		drillHandle, TRUE );
}

void PlayUserInterface::Draw( float depth)
{
	DataManager &data = DataManager::GetInstance();

	// 下の板
	DXLibMath::DrawBoxResize( m_FieldRect.x, m_FieldRect.height, 0.75f, 1.0f - m_FieldRect.height, GetColor( 64, 64, 64), TRUE);
	// 右の板
	DXLibMath::DrawBoxResize( 0.75f, 0.0f, 0.25f, 1.0f, GetColor( 0, 0, 0), TRUE);
	// ユニットを描画
	for(int i = 0; i < 6; i++)
	{
		if( data.m_MogllStatus.equipUnit[i] != 30 )
		{
			DrawExtendGraph( 32 + 92*i, 522, 32 - 15 + 92*(i+1), 600,
				data.GetGraphicGroupData( data.m_MogllStatus.equipUnit[i] + DataManager::GG_UNIT_Treasure ), TRUE);
		}
		if( i == m_CurrentPosition )
		{
			DrawExtendGraph( 32 + 92*i, 522, 32 - 15 + 92*(i+1), 600,
				data.Get( DataManager::Equipment_sin ), TRUE);
		}
	}
	// 下UI
	DXLibMath::DrawGraphResize( m_FieldRect.x, m_FieldRect.height, data.Get( DataManager::Play_UnitCreate_Frame ), TRUE );
	for( int i = 0; i < 6; i++ )
	{
		// 装備無しの時はコストを表示しない
		if( data.m_MogllStatus.equipUnit[i] != 30 )
		{
			//DrawFormatString( 80 + 92 * i, 580, GetColor( 0, 0, 0), "%d", data.m_SystemData.unit[ data.m_MogllStatus.equipUnit[i] ].cost );
			DrawFormatString( 80 + 92 * i, 580, GetColor( 0, 0, 0), "%d", data.m_MogllStatus.unitCount[ data.m_MogllStatus.equipUnit[i] ] );
		}
	}
	// 右UI
	DXLibMath::DrawGraphResize( 0.75f, 0.0f, data.Get( DataManager::Play_UI_Rader ), TRUE );
	DXLibMath::DrawGraphResize( 0.75f, m_LinePos, data.Get( DataManager::Play_UI_Line ), TRUE );
	// レーダー発見物
	for(int i = 0; i < OBJECT_MAX; i++)
	{
		if( m_DrawObject[i].exist )
		{
			SetDrawBlendMode( DX_BLENDMODE_ALPHA , m_DrawObject[i].alpha) ;
			int handle;
			if( m_DrawObject[i].id )
			{
				handle = data.Get( DataManager::Play_UI_Radar_enemy_marker);
				DrawGraph( m_DrawObject[i].x, m_DrawObject[i].y, handle, TRUE );
			}
			else
			{
				handle = data.Get( DataManager::Play_UI_Radar_treasure_marker );
				DrawRotaGraph( m_DrawObject[i].x + 4 , m_DrawObject[i].y + 4,
					m_DrawObject[i].size, 0.0, handle, TRUE );
			}
		}
	}
	// フィールド上にマウスがある時だけマウス先にユニット
	if( m_FieldRect.x <= m_Mouse.x && m_Mouse.x <= m_FieldRect.x + m_FieldRect.width &&
		m_FieldRect.y <= m_Mouse.y && m_Mouse.y <= m_FieldRect.y + m_FieldRect.height &&
		DataManager::GetInstance().m_MogllStatus.currentUnitID != UNIT_NONE)
	{
		SetDrawBlendMode( DX_BLENDMODE_ALPHA , 64 ) ;
		DXLibMath::DrawGraphResize( m_Mouse.x, m_Mouse.y, data.GetGraphicGroupData( DataManager::GG_UNIT_Treasure + DataManager::GetInstance().m_MogllStatus.currentUnitID - 1 ), TRUE);
	}

	if( m_DamageCount > 0 )
	{
		SetDrawBlendMode( DX_BLENDMODE_ALPHA, m_DamageCount * 8 );
		DrawGraph( 0, 0, data.Get( DataManager::Play_UI_Damage ), TRUE );
		m_DamageCount--;
	}

	SetDrawBlendMode( DX_BLENDMODE_NOBLEND , 0 ) ;
	// 上UI
	DrawGraph( 0, 0, data.Get( DataManager::Play_UI_Meter_Panel ), TRUE );
	DrawRotaGraph( 50, 50, 1.0, m_LifeRot, data.Get( DataManager::Play_UI_Meter_RedArrow ), TRUE );
	DrawRotaGraph( 550, 50, 1.0, m_ResourceRot, data.Get( DataManager::Play_UI_Meter_GreenArrow ), TRUE );
	// レーダー深度
	char buf[256];
	float depth = BlockManager::GetInstance().GetDepth() + data.m_MogllStatus.position.y * 600.0f / 40.0f;
	if( depth < 0.0f )
{
		depth = 0.0f;
	}
	sprintf_s(buf, "%.1fm", depth );
	m_Font.DrawFontString( FontManager::FontSet_AZUKI_25, 640, 70, buf, 100, GetColor( 0, 192, 0 ));
	DrawGraph( 600, 92, data.Get( DataManager::Play_UI_Rader_GreenLine ), TRUE );
	float maxDepth = static_cast<float>(data.m_SaveData.stageDepth[data.m_SceneInt["StageNo"]]);
	float length = maxDepth - depth;
	if( length < 18.5f )
	{
		if( length < 0.0f )
		{
			length = 0.0f;
		}
		int posY = 97 + static_cast<int>(length * 12.0f);
		DrawGraph( 600, posY, data.Get( DataManager::Play_UI_Rader_RedLine ), TRUE );
		if( maxDepth <= depth )
		{
			sprintf_s(buf, "%.1fm", depth);
		}
		else
		{
			sprintf_s(buf, "%.1fm", maxDepth);
		}
		m_Font.DrawFontString( FontManager::FontSet_AZUKI_25, 680, posY + 3, buf, 100, GetColor( 192, 0, 0 ));
	}
	else
	{
		DrawGraph( 600, 318, data.Get( DataManager::Play_UI_Rader_RedLine ), TRUE );
		sprintf_s(buf, "%.1fm", maxDepth);
		m_Font.DrawFontString( FontManager::FontSet_AZUKI_25, 680, 321, buf, 100, GetColor( 192, 0, 0 ));
	}

	DXLibMath::DrawBoxResize( 0.75f, 0.6f, 0.25f, 0.4f, GetColor( 0, 0, 0), TRUE);
	DXLibMath::DrawGraphResize( 0.75f, 0.0f, data.Get( DataManager::Play_Playmode_UI ), TRUE );

	//脱出ボタン表示
	DXLibMath::DrawGraphResize( m_EscButton, 0.607f, data.Get( DataManager::Play_UI_Escape_Button ), TRUE );
	// 装備
	if( m_VisibleFlag )
	{
		DrawBox( 616, 440, 616 + 170, 440 + 135, GetColor(0,0,0), TRUE );
		DrawGraph( 616, 440, data.Get( DataManager::Equipment_Font_Frame ), TRUE );
		for( int i = 0; i < 3; i++ )
		{
			int id = data.m_MogllStatus.equip[i];
			if( id != -1 )
			{
				id = (id/10)*30 + id%10;
				if( data.m_MogllStatus.equipStatus[i] == 0 )
				{
					DrawGraph( 627, 450 + i*45, data.GetGraphicGroupData(
						DataManager::GG_STRING01_BLUE + id + 20 ), TRUE);
				}
				else
				{
					DrawGraph( 627, 450 + i*45, data.GetGraphicGroupData(
						DataManager::GG_STRING01_BLUE + id ), TRUE);
				}
			}
		}
	}
	for( int i = 0; i< 3; i++)
	{
		if( data.m_MogllStatus.equipStatus[i] > 0 )
		{
			data.m_MogllStatus.equipStatus[i]--;
		}
	}

	//文字表示
	DrawFormatStringToHandle( 67, 44, GetColor(0,255,0), m_Font.GetHandle( FontManager::FontSet_MSGothic_Small ),
		"%04d", data.m_MogllStatus.life);
	DrawFormatStringToHandle( 507, 44, GetColor(0,255,0), m_Font.GetHandle( FontManager::FontSet_MSGothic_Small ),
		"%03d%%", data.m_MogllStatus.resource / 10);
	//DrawFormatString( 500, 50, GetColor(0, 255, 0), "%d", data.m_MogllStatus.resource);
}

void PlayUserInterface :: DrawEscape( void )
{
	DataManager &data = DataManager::GetInstance();
	// 脱出確認
	if(m_EscapeFlag == true){
		DXLibMath::DrawRotaGraphResize(0.5f, 0.5f,0.8f, 0.0f, data.Get( DataManager::Confirmation_Frame ), FALSE);
		//ボタン①
		DXLibMath::DrawRotaGraphResize(0.34f + 0.05f, 0.65f,m_EscChkButtonSize[0], 0.0f, data.Get( DataManager::Play_UI_Escape_Button_Red ), FALSE);
		DXLibMath::DrawRotaGraphResize(0.45f + 0.05f, 0.65f,m_EscChkButtonSize[1], 0.0f, data.Get( DataManager::Play_UI_Escape_Button_Yellow ), FALSE);
		DXLibMath::DrawRotaGraphResize(0.56f + 0.05f, 0.65f,m_EscChkButtonSize[2], 0.0f, data.Get( DataManager::Play_UI_Escape_Button_Blue ), FALSE);
		// 文字表示
		m_Font.DrawFontString(FontManager::FontSet_AZUKI_25 , 290, 230, "発掘を中断して　　ステージを出ます。", 250, GetColor(255,0,0));
		m_Font.DrawFontString(FontManager::FontSet_AZUKI_W001875 , 280, 375, "ステージ  選択へ", 80, GetColor(0,0,0));
		m_Font.DrawFontString(FontManager::FontSet_AZUKI_W001875 , 368, 385, "リトライ", 100, GetColor(0,0,0));
		m_Font.DrawFontString(FontManager::FontSet_AZUKI_W001875 , 472, 385, "戻る", 100, GetColor(0,0,0));
	}
}

void PlayUserInterface :: DrawFieldEffect(void)
{
	//データマネージャ取得
	DataManager &data = DataManager::GetInstance();

	float x[2][4] = 
	{
		{
			m_FieldEffect[0].x,
			m_FieldEffect[0].x,
			m_FieldEffect[0].x - FIELD_EFFECT_WIDTH,
			m_FieldEffect[0].x - FIELD_EFFECT_WIDTH,
		},
		{
			m_FieldEffect[1].x,
			m_FieldEffect[1].x,
			m_FieldEffect[1].x - FIELD_EFFECT_WIDTH,
			m_FieldEffect[1].x - FIELD_EFFECT_WIDTH,
		}
	};
	float y[2][4] = 
	{
		{
			m_FieldEffect[0].y,
			m_FieldEffect[0].y - FIELD_EFFECT_HEIGHT,
			m_FieldEffect[0].y,
			m_FieldEffect[0].y - FIELD_EFFECT_HEIGHT,
		},
		{
			m_FieldEffect[1].y,
			m_FieldEffect[1].y - FIELD_EFFECT_HEIGHT,
			m_FieldEffect[1].y,
			m_FieldEffect[1].y - FIELD_EFFECT_HEIGHT,
		}
	};

	//4枚描画
	for(int i=0; i<4; i++){
		switch(data.m_SceneInt["StageNo"]){
		case 0:// 地下都市
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)m_EffectAlpha[0]);
			DXLibMath::DrawGraphResize(x[0][i], y[0][i], data.Get(DataManager::Stage_Chikatoshi_Effect) , TRUE);
			break;
		case 1:// 氷河
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)m_EffectAlpha[0]);
			DXLibMath::DrawGraphResize(x[0][i], y[0][i], data.Get(DataManager::Stage_Hyoukai_Effect1) , TRUE);
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)m_EffectAlpha[1]);
			DXLibMath::DrawGraphResize(x[1][i], y[1][i], data.Get(DataManager::Stage_Hyoukai_Effect2) , TRUE);
			break;
		case 2:// 沼地
		//	SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)m_EffectAlpha[0]);
			DXLibMath::DrawGraphResize(x[0][i], y[0][i], data.Get(DataManager::Stage_Numachi_Effect1) , TRUE);
		//	SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)m_EffectAlpha[1]);
			DXLibMath::DrawGraphResize(x[1][i], y[1][i], data.Get(DataManager::Stage_Numachi_Effect2) , TRUE);
			break;
		case 3:// 火山
			SetDrawBlendMode(DX_BLENDMODE_ADD, (int)m_EffectAlpha[0]);
			DXLibMath::DrawGraphResize(x[0][i], y[0][i], data.Get(DataManager::Stage_Maguma_Effect1) , TRUE);
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)m_EffectAlpha[1]);
			DXLibMath::DrawGraphResize(x[1][i], y[1][i], data.Get(DataManager::Stage_Maguma_Effect2) , TRUE);
			break;
		case 4:// 近未来
			DXLibMath::DrawGraphResize(x[0][i], y[0][i], data.Get(DataManager::Stage_Kinmirai_Effect1) , TRUE);
			DXLibMath::DrawGraphResize(x[1][i], y[1][i], data.Get(DataManager::Stage_Kinmirai_Effect2) , TRUE);
			break;
		}
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void PlayUserInterface :: CheckCurrentSlot(void){
	DataManager::GetInstance().m_MogllStatus.currentUnitID = DataManager::GetInstance().m_MogllStatus.equipUnit[m_CurrentPosition] + 1;	// Noneの分１増やす
	// 装備なしを選んだ場合は
	if( DataManager::GetInstance().m_MogllStatus.currentUnitID == 31 )
	{
		DataManager::GetInstance().m_MogllStatus.currentUnitID = UNIT_NONE;
	}
}