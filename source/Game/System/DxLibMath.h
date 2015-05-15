#pragma once
// DXライブラリの関数をラップした関数群
// 画面サイズを変更しても同じ処理で書く事ができる
// その為、座標指定にはピクセルでは無く画面での比率で指定する
#include "DxLib.h"
namespace DXLibMath
{
	const double defaultWidth = 800.0;		// 基準画面サイズ
	const double defaultHeight = 600.0;		// 基準画面サイズ
	const double deltaValue = 0.000000001;	// 誤差対策の微小値
	struct Vector2
	{
		Vector2(): x(0.0), y(0.0){}
		double x, y;
	};

	struct LayOut
	{
		LayOut(): up(0.0), down(0.0), left(0.0), right(0.0){}
		double up, down, left, right;
	};

	// 画面サイズの設定関数
	void SetWindowSizeRate(double width, double height);

	// 画面サイズに合わせた描画関数
	void DrawRotaGraphResize(double x, double y, double extend, double rotation, int handle, int transFlag);
	void DrawRotaGraphResize(float x, float y, float extend, float rotation, int handle, int transFlag, int turnFlag = FALSE);
	// そのまま描画
	void DrawGraphResize(double x, double y, int handle, int transFlag);
	void DrawGraphResize(float x, float y, int handle, int transFlag);
	// 指定の領域に対して描画
	void DrawExtendGraphResize(double x, double y, double width, double height, int handle, int transFlag);
	void DrawExtendGraphResize(float x, float y, float width, float height, int handle, int transFlag);
	// 指定の領域に四角形を描画
	void DrawBoxResize(float x, float y, float width, float height, int color, int transFlag);

	// 画面サイズに合わせた座標の割合を取得する
	void GetMousePointResize(double *x, double *y);
	// unsigned shortの値を座標の割合であるdoubleに変換する
	void ConverDisplay(const unsigned short x, const unsigned short y, double *out_x, double *out_y);
	// double値を実ピクセル位置に変換する
	void ConvertPixcel(double x, double y, int *out_x, int *out_y);
	// double値を実ピクセル位置に変換する:X値のみ
	void ConvertPixcelX(double x, int *out_x);
	// double値を実ピクセル位置に変換する:Y値のみ
	void ConvertPixcelY(double y, int *out_y);

	// ブロック座標系を画面座標系に変換する
	void ConvertBlockToScreen(float x, float y, float *out_x, float *out_y);
	// 画面座標系をブロック座標系に変換する
	void ConvertScreenToBlock(float x, float y, float *out_x, float *out_y);

	// 画面バッファ描画用関数
	void DrawFrontBuffer(int handle);

	//---------------------------------------------------------------------------
	// 数学関数
	//---------------------------------------------------------------------------
	// position位置にいる時、targetの向きに現在の向きfacingをpowerの割合だけ動かすpower=1.0fで即座にtargetの方を向く
	void FacingTarget(const VECTOR &position, const VECTOR &target, VECTOR *facing, float power);
	// ベクトルの長さを返す、zは0として計算する
	float Length(const VECTOR &vector);
	// inベクトルを正規化してoutベクトルに出力する,Zは無視する
	void Normalize(VECTOR *out, const VECTOR &in);
	// inベクトルの角度Rotationを求める
	float CalcRotation(const VECTOR &vector);
	// point位置が半径rのcirclePos位置に中心のある円の内部にあるかどうか（内部にある時true)
	bool CircleOnPoint(const VECTOR &position, const VECTOR &circlePos, float r);
	// ピクセルに満たない端数を切り捨てる
	void Floor(double *width, double *height);
};