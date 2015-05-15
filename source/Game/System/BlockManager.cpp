#include "BlockManager.h"
#include "UnitManager.h"
#include "DataManager.h"

BlockManager::BlockManager(void)
{
}

void BlockManager::Init(void)
{
	m_Position.x = 0.0f;
	m_Position.y = 0.0f;
	// 表示領域のサイズ
	m_Size.x = 0.75f;
	m_Size.y = 14.0f / 15.0f;
	m_MapUI.SetRect(m_Position.x, m_Position.y, m_Size.x, m_Size.y);
	m_MapUI.SetVisible( true );
	m_BlockSize.x = m_Size.x / WIDTH_NUM_BLOCK;
	m_BlockSize.y = m_Size.y / HEIGHT_NUM_BLOCK;
	m_Depth = 0;
	m_DepthFloat = 0.0f;
	m_AddDepth = 0.0f;
	m_TopLine = 0;
	memset( &m_BlockMap[0][0], NULL, sizeof(m_BlockMap));
	m_EnemyCount = 0;
	m_DepthOffset = 0;
}

void BlockManager::Release(void)
{
	if(m_MapData != NULL)
	{
		delete[] m_MapData;
		m_MapData = NULL;
	}
	for(std::map<int, BlockBase*>::iterator it = m_BlockContainer.begin(); it != m_BlockContainer.end(); it++)
	{
		BlockBase *base = it->second;
		if(base != NULL)
		{
			delete base;
		}
	}
	m_BlockContainer.clear();
	while(m_EnemyData.size() > 0)
	{
		EnemyData* enemy = m_EnemyData.back();
		delete enemy;
		m_EnemyData.pop_back();
	}
	m_AddDepth = 0.0f;
}

BlockManager::~BlockManager(void)
{
}

void BlockManager::LoadBinary(char *fileName)
{
	FILE* fp;
	// mapバイナリ取得
	if(fopen_s(&fp, fileName, "rb") != 0)
	{
		printfDx("マップバイナリファイルがありません\n");
	}
	else
	{
		fread( &m_MapHeader, sizeof( MapHeader ), 1, fp );
		// ヘッダのデータを元にデータ領域を作成
		m_MapData = new char[ m_MapHeader.x * m_MapHeader.y ];
		fread( &m_MapData, m_MapHeader.x * m_MapHeader.y, 1, fp );
		fclose(fp);
	}
}

void BlockManager::LoadGraphic(char *fileName)
{
	int handle = LoadSoftImage( fileName );
	if( handle == -1 )
	{
		printfDx("マップデータが読めません\n");
	}
	else
	{
		struct PalettData
		{
			int r, g, b;
		}palett[30];
		// パレットカラー取得
		for(int i = 0; i < 30; i++)
		{
			GetPaletteSoftImage(handle, i, &palett[i].r, &palett[i].g, &palett[i].b, 0);
		}
		GetSoftImageSize(handle, &m_MapHeader.x, &m_MapHeader.y);
		m_MapData = new char[ m_MapHeader.x * m_MapHeader.y ];
		for(int i = 0; i < m_MapHeader.y; i++)
		{
			for(int j = 0; j < m_MapHeader.x; j++)
			{
				int r, g, b, a;
				GetPixelSoftImage(handle, j, i, &r, &g, &b, &a);
				m_MapData[ i * m_MapHeader.x + j ] = 0;
				for(int k = 0; k < 30; k++)
				{
					if( r == palett[k].r && g == palett[k].g && b == palett[k].b)
					{
						m_MapData[ i * m_MapHeader.x + j ] = k;
						break;
					}
				}
			}
		}
		DeleteSoftImage( handle );
	}
}

void BlockManager::LoadEnemyGraphic(char *fileName)
{
	int handle = LoadSoftImage( fileName );
	if( handle == -1 )
	{
		printfDx("エネミーデータが読めません\n");
	}
	else
	{
		struct PalettData
		{
			int r, g, b;
		}palett[30];
		// パレットカラー取得
		for(int i = 0; i < 30; i++)
		{
			GetPaletteSoftImage(handle, i, &palett[i].r, &palett[i].g, &palett[i].b, 0);
		}
		int width, height;
		GetSoftImageSize(handle, &width, &height);
		for(int i = 0; i < height; i++)
		{
			for(int j = 0; j < width; j++)
			{
				int r, g, b, a;
				// パレットカラーと比較
				GetPixelSoftImage(handle, j, i, &r, &g, &b, &a);
				for(int k = 0; k < 30; k++)
				{
					if( r == palett[k].r && g == palett[k].g && b == palett[k].b)
					{
						// 黒（敵ユニットなし）ならbreak
						if( k == 0 )
						{
							break;
						}
						EnemyData *dat = new EnemyData();
						dat->x = j;
						dat->y = i;
						dat->id = k;
						m_EnemyData.push_back( dat );
						break;
					}
				}
			}
		}
		DeleteSoftImage( handle );
		// 終端データをつめておく
		EnemyData *dat = new EnemyData();
		dat->x = 0;
		dat->y = 999999999;
		dat->id = -1;
		m_EnemyData.push_back( dat );
	}
}

void BlockManager::AddDepth(float depth)
{
	m_AddDepth += depth;
	m_DepthFloat += depth;
	// 長い距離は掘れない
	if(m_DepthFloat < static_cast<float>(HEIGHT_NUM_BLOCK + 1))
	{
		while( m_DepthFloat >= 1.0f)
		{
			LoadLine( m_Depth );
			// 1.0fにすると遅い時カクつく
			m_DepthFloat -= 1.0f;
		}
	}
	else
	{
		m_DepthFloat = 0.0f;
	}
	m_DepthOffset = static_cast<int>(-m_DepthFloat * 40.0f);
	m_Position.y = -m_DepthFloat * m_BlockSize.y;
	m_MapUI.SetPosition(static_cast<double>(m_Position.x), static_cast<double>(m_Position.y));
	UnitManager::GetInstance().MoveUp( depth );
}

void BlockManager::DrawBlockFrame(char *buf)
{
	DataManager &data = DataManager::GetInstance();
	const double pi = 3.14159;
	for(int i = 1; i < HEIGHT_NUM_BLOCK + 2; i++)
	{
		for(int j = 1; j < WIDTH_NUM_BLOCK + 1; j++)
		{
			char target = buf[ (WIDTH_NUM_BLOCK+2) * i + j ];
			int priority;
			if( target == 0)
			{
				priority = 0;
			}
			else
			{
				priority = data.m_SystemData.block[target-1].priority;
			}
			char u = buf[ (WIDTH_NUM_BLOCK+2) * (i-1) + j ];// 上
			char l = buf[ (WIDTH_NUM_BLOCK+2) * i + (j-1) ];// 左
			char r = buf[ (WIDTH_NUM_BLOCK+2) * i + (j+1) ];// 右
			char d = buf[ (WIDTH_NUM_BLOCK+2) * (i+1) + j ];// 下
			int x = 40*(j-1);
			int y = m_DepthOffset + 40*(i-1);
			int handle;
			if( u && data.m_SystemData.block[u-1].priority != priority)
			{
				handle = (priority > data.m_SystemData.block[u-1].priority)?
					data.GetGraphicGroupData( DataManager::GG_MAPTIP_FRAME_SAND + target - 1):
					data.GetGraphicGroupData( DataManager::GG_MAPTIP_FRAME_SAND + u - 1);
				DrawRotaGraph(20 + x, 20 + y, 1.0, pi * 0.0, handle, TRUE);
			}
			if( r && data.m_SystemData.block[r-1].priority != priority)
			{
				handle = (priority > data.m_SystemData.block[r-1].priority)?
					data.GetGraphicGroupData( DataManager::GG_MAPTIP_FRAME_SAND + target - 1):
					data.GetGraphicGroupData( DataManager::GG_MAPTIP_FRAME_SAND + r - 1);
				DrawRotaGraph(20 + x, 20 + y, 1.0, pi * 0.5, handle, TRUE);
			}
			if( d && data.m_SystemData.block[d-1].priority != priority)
			{
				handle = (priority > data.m_SystemData.block[d-1].priority)?
					data.GetGraphicGroupData( DataManager::GG_MAPTIP_FRAME_SAND + target - 1):
					data.GetGraphicGroupData( DataManager::GG_MAPTIP_FRAME_SAND + d - 1);
				DrawRotaGraph(20 + x, 20 + y, 1.0, pi * 1.0, handle, TRUE);
			}
			if( l && data.m_SystemData.block[l-1].priority != priority)
			{
				handle = (priority > data.m_SystemData.block[l-1].priority)?
					data.GetGraphicGroupData( DataManager::GG_MAPTIP_FRAME_SAND + target - 1):
					data.GetGraphicGroupData( DataManager::GG_MAPTIP_FRAME_SAND + l - 1);
				DrawRotaGraph(20 + x, 20 + y, 1.0, pi * 1.5, handle, TRUE);
			}
		}
	}
}

void BlockManager::Draw(void)
{
	DataManager &data = DataManager::GetInstance();

	int handle[ WIDTH_NUM_BLOCK * (HEIGHT_NUM_BLOCK+1) ] = {0};
	char buf[ (WIDTH_NUM_BLOCK+2) * (HEIGHT_NUM_BLOCK+3) ] = {0};
	//memset( buf, 1, sizeof(buf) );
	// 一番上はブロック扱いしない
	for(int i = 0; i < WIDTH_NUM_BLOCK+2; i++)
	{
		buf[i] = 0;
	}
	// 背景描画
	for(int i = 0; i < HEIGHT_NUM_BLOCK + 1; i++)
	{
		for(int j = 0; j < WIDTH_NUM_BLOCK; j++)
		{
			int height = m_TopLine + i;
			if(height >= HEIGHT_NUM_BLOCK + 1)
			{
				height -= HEIGHT_NUM_BLOCK + 1;
			}
			if( !m_BlockMap[j][ height ] && m_Depth + i > 13 )
			{
				DrawGraph( j*40, m_DepthOffset + i*40, DataManager::GetInstance().Get( DataManager::GG_MAPTIP_BACKBLOCK ), TRUE);
			}
		}
	}
	// ハンドルを現在読み込んでいるユニットデータから取得
	for(int i = 0; i < HEIGHT_NUM_BLOCK + 1; i++)
	{
		for(int j = 0; j < WIDTH_NUM_BLOCK; j++)
		{
			int height = m_TopLine + i;
			if(height >= HEIGHT_NUM_BLOCK + 1)
			{
				height -= HEIGHT_NUM_BLOCK + 1;
			}
			if( m_BlockMap[j][ height ] )
			{
				if( m_BlockMap[j][ height ]->IsExist() )
				{
					m_BlockMap[j][ height ]->DrawUnder();
					DrawGraph( j*40, m_DepthOffset + i*40, m_BlockMap[j][ height ]->GetHandle(), TRUE);
					m_BlockMap[j][ height ]->DrawUpper();
					
					//handle[ WIDTH_NUM_BLOCK * i + j ] = m_BlockMap[j][ height ]->GetHandle();
					buf[ (WIDTH_NUM_BLOCK+2) * (i+1) + (j+1) ] = m_BlockMap[j][ height ]->m_ID;
				}
			}
			else
			{
				buf[ (WIDTH_NUM_BLOCK+2) * (i+1) + (j+1) ] = 0;
			}
		}
	}
	// 描画
	//m_MapUI.Draw( WIDTH_NUM_BLOCK, HEIGHT_NUM_BLOCK + 1, handle);
	DrawBlockFrame( buf );
}

void BlockManager::LoadLineCalc( int num )
{
	for(int i = 0; i < WIDTH_NUM_BLOCK; i++)
	{
		// 画面外に出たブロックを削除
		if( m_BlockMap[ i ][ m_TopLine ] != NULL)
		{
			m_BlockMap[ i][ m_TopLine ]->SetExist( false );
		}
		// マップデータからデータを読み込んで適応
		char c;
		// 範囲外ならブロックなしにする
		if( WIDTH_NUM_BLOCK * num + i < m_MapHeader.x * m_MapHeader.y)
		{
			c = m_MapData[ WIDTH_NUM_BLOCK * num + i ];
		}
		else
		{
			c = BLOCK_NONE;
		}
		if( c == BLOCK_NONE)
		{
			m_BlockMap[ i ][ m_TopLine ] = NULL;
		}
		else
		{
			m_BlockMap[ i ][ m_TopLine ] = CreateBlock( c );
			m_BlockMap[ i ][ m_TopLine ]->SetExist( true );
			m_BlockMap[ i ][ m_TopLine ]->SetPosition( static_cast<float>(i) + 0.5f, static_cast<float>(num) + 0.5f );
			m_BlockMap[ i ][ m_TopLine ]->SetTreasureID( -1 );
			int enemy;
			int id = GetTreasureID( i, num, &enemy );
			// 指定IDの宝物をドロップするブロックに設定
			if( id != -1 && enemy == 0 )
			{
				m_BlockMap[ i ][ m_TopLine ]->SetTreasureID( id );
			}
		}
	}
	// 敵を召喚
	while( m_EnemyData[ m_EnemyCount ]->y <= num )
	{
		// ロード行に敵がいたら召喚
		if( num == m_EnemyData[ m_EnemyCount ]->y)
		{
			// 擬態ブロック上にユニットがいたら中に入れる
			if( m_BlockMap[ m_EnemyData[ m_EnemyCount ]->x ][ m_TopLine ] &&
				(m_BlockMap[ m_EnemyData[ m_EnemyCount ]->x ][ m_TopLine ]->m_ID == BLOCK_DUMMY ||
				m_BlockMap[ m_EnemyData[ m_EnemyCount ]->x ][ m_TopLine ]->m_ID == BLOCK_ENEMYICE ))
			{
				m_BlockMap[ m_EnemyData[ m_EnemyCount ]->x ][ m_TopLine ]->m_InEnemyID = m_EnemyData[ m_EnemyCount ]->id;
				m_EnemyCount++;
				continue;
			}
			VECTOR position;
			position.x = m_EnemyData[ m_EnemyCount ]->x * m_BlockSize.x;
			position.y = 1.0f - m_DepthFloat * m_BlockSize.y;
			DXLibMath::ConvertScreenToBlock( position.x, position.y, &position.x, &position.y );
			VECTOR mogllPos;		// モグルの座標
			// モグルの座標が画面座標なので変換
			DataManager &data = DataManager::GetInstance();
			DXLibMath::ConvertScreenToBlock( data.m_MogllStatus.position.x, data.m_MogllStatus.position.y, &mogllPos.x, &mogllPos.y );
			int enemy;
			// 宝を判断して持たせる
			int id = BlockManager::GetInstance().GetTreasureID( m_EnemyData[ m_EnemyCount ]->x, num, &enemy );
			if( id != -1 && enemy == 1 )
			{
				UnitManager::GetInstance().AddTreasureUnit( position, mogllPos, m_EnemyData[ m_EnemyCount ]->id, UnitBase::Enemy, id ); 
			}
			else
			{
				UnitManager::GetInstance().Add( position, mogllPos, m_EnemyData[ m_EnemyCount ]->id, UnitBase::Enemy ); 
			}
		}
		m_EnemyCount++;
	}
	m_TopLine++;
	if( m_TopLine >= HEIGHT_NUM_BLOCK + 1 )
	{
		m_TopLine = 0;
	}
}

void BlockManager::LoadLine(int num)
{
	LoadLineCalc( num );
	m_Depth = num + 1;
}

void BlockManager::LoadLine( void )
{
	LoadLineCalc( m_Depth );
	m_Depth++;
}

BlockBase* BlockManager::CreateBlock(int id)
{
	BlockBase* base = NULL;
	for(int i = 0; i < BLOCK_ID_OFFSET; i++)
	{
		// 指定のIDのブロックが足りなければ追加
		base = m_BlockContainer[id * BLOCK_ID_OFFSET + i];
		if( base == NULL)
		{
			base = sp_CreateBlockTable[id]();
			m_BlockContainer[id * BLOCK_ID_OFFSET + i] = base;
			base->m_ID = id;
			base->Init();
			//base->m_ID = id;
			break;
		}
		// 空いてるなら有効にして使いまわす
		else if( !base->IsExist() )
		{
			base->Init();
			break;
		}
	}
	return base;
}

void BlockManager::Update(void)
{
	m_AddDepth = 0.0f;
	for(int i = 0; i < HEIGHT_NUM_BLOCK + 1; i++)
	{
		for(int j = 0; j < WIDTH_NUM_BLOCK; j++)
		{
			int height = m_TopLine + i;
			if(height >= HEIGHT_NUM_BLOCK + 1)
			{
				height -= HEIGHT_NUM_BLOCK + 1;
			}
			if( m_BlockMap[j][ height ])
			{
				// 存在しているブロックのみ更新
				if( m_BlockMap[j][ height ]->IsExist() )
				{
					m_BlockMap[j][ height ]->Update();
				}
				// 存在しなくなったブロックは空白にする
				if(!m_BlockMap[j][ height ]->IsExist())
				{
					m_pBreakBlock->Add(m_BlockMap[j][height]->GetPosition(),10,m_BlockMap[j][height]->GetHandle());
					m_BlockMap[j][ height ] = NULL;
				}
			}
			// 存在しないなら空白にする
			else
			{
				m_BlockMap[j][ height ] = NULL;
			}
		}
	}
	//printfDx( " %d, %d,\n", m_BlockContainer.size(), m_Depth);
}

std::list<BlockBase*>& BlockManager::GetAreaBlock(float x, float y, float r)
{
	m_ReturnBuffer.clear();
	VECTOR position;
	position.x = x;
	position.y = y;
	position.z = r;
	for(int i = 0; i < HEIGHT_NUM_BLOCK + 1; i++)
	{
		for(int j = 0; j < WIDTH_NUM_BLOCK; j++)
		{
			BlockBase* base = m_BlockMap[j][i];
			if( base != NULL)
			{
				VECTOR block;
				block.x = base->m_x;
				block.y = base->m_y - static_cast<float>(m_Depth - HEIGHT_NUM_BLOCK - 1) - m_DepthFloat;
				if( DXLibMath::CircleOnPoint( block, position, position.z ) )
				{
					m_ReturnBuffer.push_back( base );
				}
			}
		}
	}
	return m_ReturnBuffer;
}

BlockBase* BlockManager::GetBlock(float x, float y)
{
	// スクリーン座標系→ブロック座標系
	//x /= m_BlockSize.x;
	//y /= m_BlockSize.y;
	int height = m_TopLine + static_cast<int>(y + m_DepthFloat);
	if(height >= HEIGHT_NUM_BLOCK + 1)
	{
		height -= HEIGHT_NUM_BLOCK + 1;
	}
	int width = static_cast<int>(x);
	if( width < 0 || WIDTH_NUM_BLOCK <= width || height < 0 )
	{
		return NULL;
	}
	return m_BlockMap[ width ][ height ];
}

BlockBase* BlockManager::GetNearBlock(const VECTOR &position, float r)
{
	BlockBase *base = NULL;
	float nearRang = r;
	for(int i = 0; i < HEIGHT_NUM_BLOCK + 1; i++)
	{
		for(int j = 0; j < WIDTH_NUM_BLOCK; j++)
		{
			BlockBase* block = m_BlockMap[j][i];
			if( block != NULL && block->m_ID != BLOCK_WATER && block->m_ID != BLOCK_FIRE)
			{
				VECTOR blockPos;
				blockPos.x = block->m_x - position.x;
				blockPos.y = block->m_y - position.y - m_DepthFloat - static_cast<float>(m_Depth - HEIGHT_NUM_BLOCK - 1);
				float length = DXLibMath::Length( blockPos );
				if( nearRang > length )
				{
					base = block;
					nearRang = length;
				}
			}
		}
	}
	return base;
}

BlockBase* BlockManager::GetNearHardBlock(const VECTOR &position, float r)
{
	BlockBase *base = NULL;
	float nearRang = r;
	DataManager &data = DataManager::GetInstance();
	for(int i = 0; i < HEIGHT_NUM_BLOCK + 1; i++)
	{
		for(int j = 0; j < WIDTH_NUM_BLOCK; j++)
		{
			BlockBase* block = m_BlockMap[j][i];
			if( block != NULL && data.m_SystemData.block[ block->m_ID - 1 ].moveType )
			{
				VECTOR blockPos;
				blockPos.x = block->m_x - position.x;
				blockPos.y = block->m_y - position.y - m_DepthFloat - static_cast<float>(m_Depth - HEIGHT_NUM_BLOCK - 1);
				float length = DXLibMath::Length( blockPos );
				if( nearRang > length )
				{
					base = block;
					nearRang = length;
				}
			}
		}
	}
	return base;
}

void BlockManager::ConvertScreen( BlockBase* block, float *x, float *y )
{
	VECTOR blockPos;
	blockPos.x = block->m_x;
	blockPos.y = block->m_y - static_cast<float>(m_Depth) - m_DepthFloat;
	DXLibMath::ConvertBlockToScreen( blockPos.x, blockPos.y, x, y );
}

float BlockManager::GetDepth( void )
{
	return static_cast<float>(m_Depth - HEIGHT_NUM_BLOCK - 1) + m_DepthFloat;
}

float BlockManager::GetOneFrameDepth(void)
{
	return m_AddDepth;
}

int BlockManager::GetDepthOffset(void)
{
	return (m_Depth * 40 - m_DepthOffset);
}

int BlockManager::GetTreasureID( int x, int y, int* enemy )
{
	DataManager &data = DataManager::GetInstance();

	int stage = data.m_SceneInt["StageNo"];
	// その他の秘宝
	for(int i = stage * 10; i < (stage + 1) * 10; i++)
	{
		if( y == data.m_SystemData.treasure[i].y && x == data.m_SystemData.treasure[i].x && !data.m_SaveData.stageItemStatus[ i ] ){
			*enemy = data.m_SystemData.treasure[i].isEnemy;
			return data.m_SystemData.treasure[i].id;
		}
	}
	// マップ
	for(int i = 0; i < 4; i++)
	{
		if( stage != 0 )
		{
			break;
		}
		if( y == data.m_SystemData.treasure[50+i].y && x == data.m_SystemData.treasure[50+i].x &&
			data.m_SaveData.stageDepth[1+i] == -1 )
		{
			*enemy = data.m_SystemData.treasure[50+i].isEnemy;
			return data.m_SystemData.treasure[50+i].id;
		}
	}
	// 虹色の宝石
	if( stage == 0 && y == 1078 && x == 7 && data.m_SaveData.stageItemStatus[50] == 0)
	{
		for(int i = 0; i < 50; i++)
		{
			if( data.m_SaveData.stageItemStatus[i] == 0 )
			{
				return -1;
			}
		}
		*enemy = 0;
		return 59;
	}
	return -1;
}

int BlockManager::GetEnemyID( int x, int y )
{
	int count = 0;
	while( m_EnemyData[ m_EnemyCount + count ]->y <= y )
	{
		if( y == m_EnemyData[ m_EnemyCount + count ]->y && x == m_EnemyData[ m_EnemyCount + count ]->x )
		{
			return m_EnemyData[ m_EnemyCount + count ]->id;
		}
		count++;
	}
	return -1;
}