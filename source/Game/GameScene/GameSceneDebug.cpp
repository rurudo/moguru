#include "GameSceneDebug.h"
#include "../System/DataManager.h"
#include "../System/GameInput.h"

//====================================================
//�@�����֐�
GameScene* GameSceneDebug_CreateScene()
{
	return new GameSceneDebug();
}

//====================================================
// �N���X���\�b�h
GameSceneDebug::GameSceneDebug(void)
{
	//FILE* fp;
	// �V�X�e���f�[�^���ǂݍ���
	//if(fopen_s(&fp, "resource/data/system.dat", "rb") != 0)
	//{
	//	ConvertBinary();
	//}
	//else
	//{
	//	fclose(fp);
	//}
	ConvertBinary();
	m_FontManager.Load(FontManager::FontSet_AZUKI_003);
}

GameSceneDebug::~GameSceneDebug(void)
{
	clsDx();
}

int GameSceneDebug::Update(void)
{
	ClearDrawScreen(); // �`���N���A

	GameInput &input = GameInput::GetInstance();
	if(input.GetMouse(GameInput::MouseLeftTrg))
	{
		return GAME_SCENE_TITLE;
	}
	clsDx();
	// �Z�[�u�f�[�^
	StoreData *save = &DataManager::GetInstance().m_SaveData;
	printfDx("Header:%s\n", save->header);
	printfDx("Item:");
	for(int i = 0; i < 60; i++)
	{
		printfDx("%d,", save->itemStatus[i]);
	}
	printfDx("\n");
	printfDx("Unit:");
	for(int i = 0; i < 30; i++)
	{
		printfDx("%d,", save->unitStatus[i]);
	}
	printfDx("\n");
	for(int i = 0; i < 5; i++)
	{
		printfDx("%d�X�e�[�W:%d, ��擾��:", i+1, save->stageDepth[i]);
		for(int j = 0; j < 10; j++)
		{
			printfDx("%d,", save->stageItemStatus[i * 10 + j]);
		}
		printfDx("\n");
	}
	printfDx("\n");

	// ���j�b�g�A����
	DataManager::GameSystemData *sys = &DataManager::GetInstance().m_SystemData;
	int eqID = 0;
	int unitID = 0;
	int blockID = 0;
	printfDx("%s:%s\n", sys->equip[eqID].name, sys->equip[eqID].text);
	printfDx("%s:%s, %d, %d, %f, %f, %f, %f\n", sys->unit[unitID].name,
		sys->unit[unitID].text, sys->unit[unitID].cost, sys->unit[unitID].hp, sys->unit[unitID].aSpd,
		sys->unit[unitID].power, sys->unit[unitID].rang, sys->unit[unitID].spd);
	printfDx("%s:life = %d,%s\n", sys->block[blockID].name, sys->block[blockID].hp, sys->block[blockID].text);

	m_FontManager.DrawFontString(FontManager::FontSet_AZUKI_003,
		0.8f, 0.7f, "Hello World �t�H���g�e�X�g�A���̃e�L�X�g�͎����ŉ��s����܂�", 0.2f, GetColor(255, 255, 255));

	//ScreenFlip();//�X���b�v
	return GAME_SCENE_THIS;
}

void GameSceneDebug::ConvertBinary(void)
{
	int fp;
	fp = FileRead_open("equip.txt");//�t�@�C���ǂݍ���
	DataManager::GameSystemData *data = &DataManager::GetInstance().m_SystemData;
	if(fp == NULL)
	{
		// �t�@�C���������������̏���
		return;
	}
	else
	{
		// ������
		memset(data, 0, sizeof( DataManager::GameSystemData ));
		// �ǂݍ���
		for(int i = 0; i < 60; i++)
		{
			int type = 0;
			int count = 0;
			char word[256];
			for(;;)
			{
				char c = word[count] = FileRead_getc(fp);
				if(c == ',' || c == '\n')
				{
					word[count] = '\0';
					switch(type)
					{
					case 0: data->equip[i].name[count] = '\0'; break;
					case 1: data->equip[i].text[count] = '\0'; break;
					case 2: data->equip[i].a = atoi(word); break;
					case 3: data->equip[i].b = atoi(word); break;
					case 4: data->equip[i].shortText[count] = '\0'; break;
					default: break;
					}
					type++;
					count = 0;
					if(c == '\n')
					{
						break;
					}
					continue;
				}
				switch(type)
				{
				case 0: data->equip[i].name[count] = c; break;
				case 1: data->equip[i].text[count] = c; break;
				case 4: data->equip[i].shortText[count] = c; break;
				default: break;
				}
				count++;
			}
		}
		FileRead_close(fp);
	}
	// �u���b�N
	fp = FileRead_open("block.txt");//�t�@�C���ǂݍ���
	if(fp == NULL)
	{
		// �t�@�C���������������̏���
		return;
	}
	else
	{
		// �ǂݍ���
		for(int i = 0; i < 23; i++)
		{
			int type = 0;
			int count = 0;
			char word[256];
			for(;;)
			{
				char c = word[count] = FileRead_getc(fp);
				if(c == ',' || c == '\n')
				{
					word[count] = '\0';
					switch(type)
					{
					case 0: data->block[i].name[count] = '\0'; break;
					case 1: data->block[i].hp = atoi(word); break;
					case 2: data->block[i].resource = atoi(word); break;
					case 3: data->block[i].moveType = atoi(word); break;
					case 4: data->block[i].priority = atoi(word); break;
					case 5: data->block[i].damage = atoi(word); break;
					case 6: data->block[i].text[count] = '\0'; break;
					default: break;
					}
					type++;
					count = 0;
					if(c == '\n')
					{
						break;
					}
					continue;
				}
				switch(type)
				{
				case 0: data->block[i].name[count] = c; break;
				case 6: data->block[i].text[count] = c; break;
				default: break;
				}
				count++;
			}
		}
		FileRead_close(fp);
	}
	// ��
	fp = FileRead_open("treasure.txt");//�t�@�C���ǂݍ���
	if(fp == NULL)
	{
		// �t�@�C���������������̏���
		return;
	}
	else
	{
		// �ǂݍ���
		for(int i = 0; i < 54; i++)
		{
			int type = 0;
			int count = 0;
			char word[256];
			for(;;)
			{
				char c = word[count] = FileRead_getc(fp);
				if(c == ',' || c == '\n')
				{
					word[count] = '\0';
					switch(type)
					{
					case 0: data->treasure[i].id = atoi(word); break;
					case 1: data->treasure[i].x = atoi(word); break;
					case 2: data->treasure[i].y = atoi(word); break;
					case 3: data->treasure[i].isEnemy = atoi(word); break;
					case 4: data->treasure[i].life = atoi(word); break;
					default: break;
					}
					type++;
					count = 0;
					if(c == '\n')
					{
						break;
					}
					continue;
				}
				count++;
			}
		}
		FileRead_close(fp);
	}
	// �`�������W
	fp = FileRead_open("challenge.txt");//�t�@�C���ǂݍ���
	if(fp == NULL)
	{
		// �t�@�C���������������̏���
		return;
	}
	else
	{
		// �ǂݍ���
		for(int i = 0; i < 100; i++)
		{
			int type = 0;
			int count = 0;
			char word[256];
			for(;;)
			{
				char c = word[count] = FileRead_getc(fp);
				if(c == ',' || c == '\n')
				{
					word[count] = '\0';
					switch(type)
					{
					case 0: data->unit[i].text[count] = '\0'; break;
					default: break;
					}
					type++;
					count = 0;
					if(c == '\n')
					{
						break;
					}
					continue;
				}
				switch(type)
				{
				case 0: data->challenge[i].text[count] = c; break;
				default: break;
				}
				count++;
			}
		}
		FileRead_close(fp);
	}
	// ���j�b�g
	fp = FileRead_open("unit.txt");//�t�@�C���ǂݍ���
	if(fp == NULL)
	{
		// �t�@�C���������������̏���
		return;
	}
	else
	{
		// �ǂݍ���
		for(int i = 0; i < 30; i++)
		{
			int type = 0;
			int count = 0;
			char word[256];
			for(;;)
			{
				char c = word[count] = FileRead_getc(fp);
				if(c == ',' || c == '\n')
				{
					word[count] = '\0';
					switch(type)
					{
					case 0: data->unit[i].name[count] = '\0'; break;
					case 1: data->unit[i].text[count] = '\0'; break;
					case 2: data->unit[i].cost = atoi(word); break;
					case 3: data->unit[i].rang = static_cast<float>( atoi(word) ); break;
					case 4: data->unit[i].power = atoi(word); break;
					case 5: data->unit[i].aSpd = static_cast<float>( atoi(word) ); break;
					case 6: data->unit[i].hp = atoi(word); break;
					case 7: data->unit[i].spd = static_cast<float>( atoi(word) ); break;
					default: break;
					}
					type++;
					count = 0;
					if(c == '\n')
					{
						break;
					}
					continue;
				}
				switch(type)
				{
				case 0: data->unit[i].name[count] = c; break;
				case 1: data->unit[i].text[count] = c; break;
				default: break;
				}
				count++;
			}
		}

		FileRead_close(fp);
		// �o�C�i����
		FILE *fpData;
		fopen_s( &fpData, "resource/data/system.dat" , "wb" );
		fwrite( data , sizeof( DataManager::GameSystemData ), 1, fpData );
		fclose( fpData );
	}
}

void GameSceneDebug::Draw(void)
{
}

void GameSceneDebug::BitmapToBinary(char *fileName)
{
	// �摜���������ɒu���֐����p�ӂ��Ă������̂ŕۗ�
}