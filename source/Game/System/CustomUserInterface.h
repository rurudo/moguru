#pragma once
#include "BoolArray.h"
#include "DxLibMath.h"
class CustomUserInterface
{
private:
	enum InterfaceFlags
	{
		InterfaceFlag_Visible
	};
	BoolArray m_Flags;
	DXLibMath::Vector2 m_Position;
	DXLibMath::Vector2 m_Size;
	DXLibMath::LayOut m_OutSpace;	// フレームの余白
	DXLibMath::LayOut m_InSpace;	// 子要素の余白
	int	m_InSpaceX, m_InSpaceY;
	int m_OutSpaceX, m_OutSpaceY;
	int m_Handle;					// フレームの画像ハンドル
public:
	CustomUserInterface(void);
	~CustomUserInterface(void);
	void Update(void);
	void Draw(int widthNum, int heightNum, int *handle);
	void Draw(	int widthNum, int heightNum, int *handle,
				char judgeList[],int sortList[],int judgeVal[],int judgeNum,int silhouetteVal[],int silhouetteNum);
	void GetPosition(int width, int height, int *x, int *y);
	// 描画フラグの切り替え
	void SetVisible(bool isVisible);
	// 描画領域のサイズ指定
	void SetRect(double x, double y, double width, double height);
	void SetRect(float x, float y, float width, float height);
	void SetPosition(double x, double y);
	void SetGraphicHandle(int handle);
	// 外側のスペースをセットする
	void SetOutSpace(double up, double down, double left, double right);
	// 子要素間のスペースをセットする
	void SetInSpace(double up, double down, double left, double right);
};

