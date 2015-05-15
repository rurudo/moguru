#pragma once
#include<string>
class FontManager
{
public:
	enum FontSet
	{
		FontSet_AZUKI_003,		// あずきフォント
		FontSet_AZUKI_25,
		FontSet_AZUKI_W0025,	// 横0.025
		FontSet_AZUKI_W001875,	// 横0.01875
		FontSet_AZUKI_W00225,	// ユニット名とか
		FontSet_AZUKI_W001625,	// ユニットの説明とか
		FontSet_AZUKI_W00375,
		FontSet_AZUKI_W004375,
		FontSet_AZUKI_W005,
		FontSet_MSGothic_Small,
		FontSet_MSGothic_Middle,
		FONTSET_MAX				// 必ず最後
	};
private:
	struct FontData
	{
		int handle;
		int halfStringWidth;	// 半角文字幅
		int stringWidth;		// 全角文字幅
		int size;				// 指定したフォントサイズ（高さ）
	};
	FontData m_FontData[FONTSET_MAX];
	std::string m_filePath;	// フォントパス

public:
	FontManager(void);
	~FontManager(void);
	// フォントデータをロードする
	int GetHandle(FontSet font);
	void Load(FontSet font);
	void DrawFontString(FontSet font, float x, float y, char *string, float width, int color);
	void DrawFontStringNumSet(FontSet font, float x, float y, char *string, float width, int charNum, int color);
	void DrawFontString(FontSet font, int x, int y, char *string, int width, int color);
	void DrawFontStringNumSet(FontSet font, int pX, int pY, char *string, int pWidth, int charNum, int color);
	// 指定したx座標を中央として文字列を描画する
	void DrawCenter(FontSet font, int x, int y, char *string, int color);
};

