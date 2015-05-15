#include "FontManager.h"
#include "DxLib.h"
#include "DxLibMath.h"
#include <mbstring.h>

FontManager::FontManager(void)
{
	memset( m_FontData, 0, sizeof(m_FontData) );
	m_filePath.assign("resource/data/azuki.ttf");
	if(AddFontResourceEx(m_filePath.c_str(), FR_PRIVATE, NULL) > 0)
	{}
	else
	{
		// �t�H���g�Ǎ��G���[����
		MessageBox(NULL,"�t�H���g�Ǎ����s","",MB_OK);
		return;
	}
}

FontManager::~FontManager(void)
{
	// �t�H���g�f�[�^�J��
	InitFontToHandle();
	if ( RemoveFontResourceEx( m_filePath.c_str() ,FR_PRIVATE, NULL))
	{
		PostMessage(HWND_BROADCAST, WM_FONTCHANGE, 0, 0);
	}
	else
	{
		MessageBox(NULL, "remove failure", "", MB_OK);
	}
}

void FontManager::Load(FontSet font)
{
	if( m_FontData[font].handle != 0)	return;
	switch(font)
	{
	case FontSet_MSGothic_Small:
		m_FontData[font].size = 14;
		m_FontData[font].handle = CreateFontToHandle("�l�r�S�V�b�N", m_FontData[font].size, 1);
		break;
	case FontSet_MSGothic_Middle:
		m_FontData[font].size = 24;
		m_FontData[font].handle = CreateFontToHandle("�l�r�S�V�b�N", m_FontData[font].size, 2);
		break;
	case FontSet_AZUKI_25:
		m_FontData[font].size = 25;
		m_FontData[font].handle = CreateFontToHandle("�������t�H���g", m_FontData[font].size, 6);
		break;
	case FontSet_AZUKI_003:
		DXLibMath::ConvertPixcelY(0.03, &m_FontData[font].size);
		m_FontData[font].handle = CreateFontToHandle("�������t�H���g", m_FontData[font].size, 2);
		break;
	case FontSet_AZUKI_W0025:
		DXLibMath::ConvertPixcelX(0.025, &m_FontData[font].size);
		m_FontData[font].handle = CreateFontToHandle("�������t�H���g", m_FontData[font].size, 2);
		break;
	case FontSet_AZUKI_W001875:
		DXLibMath::ConvertPixcelX(0.01875, &m_FontData[font].size);
		m_FontData[font].handle = CreateFontToHandle("�������t�H���g", m_FontData[font].size, 2);
		break;
	case FontSet_AZUKI_W00225:
		DXLibMath::ConvertPixcelX(0.0225, &m_FontData[font].size);
		m_FontData[font].handle = CreateFontToHandle("�������t�H���g", m_FontData[font].size, 2);
		break;
	case FontSet_AZUKI_W001625:
		DXLibMath::ConvertPixcelX(0.01625, &m_FontData[font].size);
		m_FontData[font].handle = CreateFontToHandle("�������t�H���g", m_FontData[font].size, 2);
		break;
	case FontSet_AZUKI_W00375:
		DXLibMath::ConvertPixcelX(0.0375, &m_FontData[font].size);
		m_FontData[font].handle = CreateFontToHandle("�������t�H���g", m_FontData[font].size, 10);
		break;
	case FontSet_AZUKI_W004375:
		DXLibMath::ConvertPixcelX(0.04375, &m_FontData[font].size);
		m_FontData[font].handle = CreateFontToHandle("�������t�H���g", m_FontData[font].size, 20);
		break;
	case FontSet_AZUKI_W005:
		DXLibMath::ConvertPixcelX(0.05, &m_FontData[font].size);
		m_FontData[font].handle = CreateFontToHandle("�������t�H���g", m_FontData[font].size, 20);
		break;
	default:
		break;
	}
	m_FontData[font].halfStringWidth = GetDrawStringWidthToHandle("a", 1, m_FontData[font].handle);
	m_FontData[font].stringWidth = GetDrawStringWidthToHandle("��", 2, m_FontData[font].handle);
}

void FontManager::DrawFontString(FontSet font, float x, float y, char *string, float width, int color)
{
	int pX, pY, pWidth;
	// ��ʃs�N�Z���𑪒�
	DXLibMath::ConvertPixcel(static_cast<double>(x), static_cast<double>(y), &pX, &pY);
	DXLibMath::ConvertPixcelX(static_cast<double>(width), &pWidth);
	DrawFontString(font, pX, pY, string, pWidth, color );
}

void FontManager::DrawFontString(FontSet font, int pX, int pY, char *string, int pWidth, int color)
{
	if( m_FontData[font].handle == 0)
	{
		Load(font);
	}
	char buffer[256];
	int allCount = 0;	// �S�̂̕�����
	int count = 0;		// ���ݕۑ����̕�����
	int length = 0;		// ������̉��s�N�Z��
	// �I�[�����܂Ń��[�v
	while(string[allCount] != '\0')
	{
		char c = string[allCount];
		// �Q�o�C�g�����Ȃ�
		//if((c >= 0x81 && c <= 0x9F) || (c >= 0xE0 && c <= 0xFC))
		if( _mbclen((BYTE*)&string[allCount]) == 2)
		{
			// �w�肵�������𒴂�����`��
			if(length + m_FontData[font].stringWidth >= pWidth)
			{
				buffer[count] = '\0';
				DrawStringToHandle(pX, pY, buffer, color, m_FontData[font].handle);
				pY += m_FontData[font].size;
				length = 0;
				count = 0;
			}
			buffer[count] = c;
			buffer[count + 1] = string[allCount + 1];
			allCount += 2;
			count += 2;
			length += m_FontData[font].stringWidth;
		}
		else
		{
			if(length + m_FontData[font].halfStringWidth >= pWidth)
			{
				buffer[count] = '\0';
				DrawStringToHandle(pX, pY, buffer, color, m_FontData[font].handle);
				pY += m_FontData[font].size;
				length = 0;
				count = 0;
			}
			buffer[count] = c;
			allCount++;
			count++;
			length += m_FontData[font].halfStringWidth;
		}
	}
	buffer[count] = '\0';
	DrawStringToHandle(pX, pY, buffer, color, m_FontData[font].handle);
}

void FontManager::DrawFontStringNumSet(FontSet font, float x, float y, char *string, float width, int charNum, int color)
{
	int pX, pY, pWidth;
	// ��ʃs�N�Z���𑪒�
	DXLibMath::ConvertPixcel(static_cast<double>(x), static_cast<double>(y), &pX, &pY);
	DXLibMath::ConvertPixcelX(static_cast<double>(width), &pWidth);
	DrawFontStringNumSet(font, pX, pY, string, pWidth, charNum, color );
}
void FontManager::DrawFontStringNumSet(FontSet font, int pX, int pY, char *string, int pWidth, int charNum, int color)
{
	if( m_FontData[font].handle == 0)
	{
		Load(font);
	}
	char buffer[256];
	int allCount = 0;			// �S�̂̕�����
	int count = 0;				// ���ݕۑ����̕�����
	int length = 0;				// ������̉��s�N�Z��
	int charNumCount = 0;		// �������J�E���g
	// �I�[�����܂Ń��[�v
	while(string[allCount] != '\0')
	{
		if(charNumCount > charNum-1){
			buffer[count] = '\0';
			DrawStringToHandle(pX, pY, buffer, color, m_FontData[font].handle);
			break;
		}

		char c = string[allCount];
		// �Q�o�C�g�����Ȃ�
		//if((c >= 0x81 && c <= 0x9F) || (c >= 0xE0 && c <= 0xFC))
		if( _mbclen((BYTE*)&string[allCount]) == 2)
		{
			// �w�肵�������𒴂�����`��
			if(length + m_FontData[font].stringWidth >= pWidth)
			{
				buffer[count] = '\0';
				DrawStringToHandle(pX, pY, buffer, color, m_FontData[font].handle);
				pY += m_FontData[font].size;
				length = 0;
				count = 0;
			}
			buffer[count] = c;
			buffer[count + 1] = string[allCount + 1];
			allCount += 2;
			count += 2;
			length += m_FontData[font].stringWidth;
		}
		else
		{
			if(length + m_FontData[font].halfStringWidth >= pWidth)
			{
				buffer[count] = '\0';
				DrawStringToHandle(pX, pY, buffer, color, m_FontData[font].handle);
				pY += m_FontData[font].size;
				length = 0;
				count = 0;
			}
			buffer[count] = c;
			allCount++;
			count++;
			length += m_FontData[font].halfStringWidth;
		}
		charNumCount++;
	}
	buffer[count] = '\0';
	DrawStringToHandle(pX, pY, buffer, color, m_FontData[font].handle);
}

int FontManager::GetHandle(FontSet font)
{
	if( m_FontData[font].handle == 0)
	{
		Load(font);
	}
	return m_FontData[font].handle;
}

void FontManager::DrawCenter(FontSet font, int x, int y, char *string, int color)
{
	// font���܂�����Ă��Ȃ������ꍇ���[�h����
	if( m_FontData[font].handle == 0)
	{
		Load(font);
	}
	char buffer[256];
	int count = 0;				// ���ݕۑ����̕�����
	int length = 0;				// ������̉��s�N�Z��
	// �I�[�����܂Ń��[�v
	while(string[count] != '\0')
	{
		char c = string[count];
		// �Q�o�C�g�����Ȃ�
		//if((c >= 0x81 && c <= 0x9F) || (c >= 0xE0 && c <= 0xFC))
		if( _mbclen((BYTE*)&string[count]) == 2)
		{
			buffer[count] = c;
			buffer[count + 1] = string[count + 1];
			count += 2;
			length += m_FontData[font].stringWidth;
		}
		else
		{
			buffer[count] = c;
			count++;
			length += m_FontData[font].halfStringWidth;
		}
	}
	buffer[count] = '\0';
	DrawStringToHandle(x - length / 2, y, buffer, color, m_FontData[font].handle);
}