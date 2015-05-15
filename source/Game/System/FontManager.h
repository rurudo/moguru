#pragma once
#include<string>
class FontManager
{
public:
	enum FontSet
	{
		FontSet_AZUKI_003,		// �������t�H���g
		FontSet_AZUKI_25,
		FontSet_AZUKI_W0025,	// ��0.025
		FontSet_AZUKI_W001875,	// ��0.01875
		FontSet_AZUKI_W00225,	// ���j�b�g���Ƃ�
		FontSet_AZUKI_W001625,	// ���j�b�g�̐����Ƃ�
		FontSet_AZUKI_W00375,
		FontSet_AZUKI_W004375,
		FontSet_AZUKI_W005,
		FontSet_MSGothic_Small,
		FontSet_MSGothic_Middle,
		FONTSET_MAX				// �K���Ō�
	};
private:
	struct FontData
	{
		int handle;
		int halfStringWidth;	// ���p������
		int stringWidth;		// �S�p������
		int size;				// �w�肵���t�H���g�T�C�Y�i�����j
	};
	FontData m_FontData[FONTSET_MAX];
	std::string m_filePath;	// �t�H���g�p�X

public:
	FontManager(void);
	~FontManager(void);
	// �t�H���g�f�[�^�����[�h����
	int GetHandle(FontSet font);
	void Load(FontSet font);
	void DrawFontString(FontSet font, float x, float y, char *string, float width, int color);
	void DrawFontStringNumSet(FontSet font, float x, float y, char *string, float width, int charNum, int color);
	void DrawFontString(FontSet font, int x, int y, char *string, int width, int color);
	void DrawFontStringNumSet(FontSet font, int pX, int pY, char *string, int pWidth, int charNum, int color);
	// �w�肵��x���W�𒆉��Ƃ��ĕ������`�悷��
	void DrawCenter(FontSet font, int x, int y, char *string, int color);
};

