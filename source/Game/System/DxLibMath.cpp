#include "DxLibMath.h"
#include <math.h>

static double windowWidth = 800.0;
static double windowHeight = 600.0;

static float BLOCK_SIZE_WIDTH = 0.75f / 15.0f;
static float BLOCK_SIZE_HEIGHT = 13.0f / 15.0f / 12.0f;

static int screenWidth = 800;
static int screenHeight = 600;

void DXLibMath::SetWindowSizeRate(double width, double height)
{
	//windowWidth = width;
	//windowHeight = height;
	screenWidth = static_cast<int>(width);
	screenHeight = static_cast<int>(height);
}

void DXLibMath::DrawFrontBuffer(int handle)
{
	DrawExtendGraph( 0, 0, screenWidth, screenHeight, handle, FALSE ) ;
}

void DXLibMath::DrawRotaGraphResize(double x, double y, double extend, double rotation, int handle, int transFlag)
{
	// ‰æ–Ê”{—¦
	double rate = windowWidth / defaultWidth;
	DrawRotaGraph(static_cast<int>(x * windowWidth), static_cast<int>(y * windowHeight),
		rate * extend, rotation, handle, transFlag);
}

void DXLibMath::DrawRotaGraphResize(float x, float y, float extend, float rotation, int handle, int transFlag, int turnFlag)
{
	// ‰æ–Ê”{—¦
	double rate = windowWidth / defaultWidth;
	DrawRotaGraph(static_cast<int>(x * windowWidth), static_cast<int>(y * windowHeight),
		rate * extend, rotation, handle, transFlag, turnFlag);
}

void DXLibMath::DrawGraphResize(double x, double y, int handle, int transFlag)
{
	// ‰æ–Ê”{—¦
	double rate = windowWidth / defaultWidth;
	DrawRotaGraph2(static_cast<int>(x * windowWidth), static_cast<int>(y * windowHeight), 0, 0,
		rate, 0.0, handle, transFlag);
}

void DXLibMath::DrawGraphResize(float x, float y, int handle, int transFlag)
{
	// ‰æ–Ê”{—¦
	double rate = windowWidth / defaultWidth;
	DrawRotaGraph2(static_cast<int>(x * windowWidth), static_cast<int>(y * windowHeight), 0, 0,
		rate, 0.0, handle, transFlag);
}

void DXLibMath::DrawExtendGraphResize(double x, double y, double width, double height, int handle, int transFlag)
{
	double rate = windowWidth / defaultWidth;
	int x1, y1, w, h;
	x1 = static_cast<int>(x * windowWidth);
	y1 = static_cast<int>(y * windowHeight);
	w = static_cast<int>(width * windowWidth);
	h = static_cast<int>(height * windowHeight);
	DrawExtendGraph(x1, y1, x1 + w, y1 + h, handle, transFlag);
}

void DXLibMath::DrawExtendGraphResize(float x, float y, float width, float height, int handle, int transFlag)
{
	double rate = windowWidth / defaultWidth;
	int x1, y1, w, h;
	x1 = static_cast<int>(x * windowWidth);
	y1 = static_cast<int>(y * windowHeight);
	w = static_cast<int>(width * windowWidth);
	h = static_cast<int>(height * windowHeight);
	DrawExtendGraph(x1, y1, x1 + w, y1 + h, handle, transFlag);
}

void DXLibMath::DrawBoxResize(float x, float y, float width, float height, int color, int transFlag)
{
	double rate = windowWidth / defaultWidth;
	int x1, y1, w, h;
	x1 = static_cast<int>(x * windowWidth);
	y1 = static_cast<int>(y * windowHeight);
	w = static_cast<int>(width * windowWidth);
	h = static_cast<int>(height * windowHeight);
	DrawBox( x1, y1, x1 + w, y1 + h, color, transFlag);
}

void DXLibMath::GetMousePointResize(double *x, double *y)
{
	int bufX, bufY;
	GetMousePoint(&bufX, &bufY);
	//*x = bufX / windowWidth;
	//*y = bufY / windowHeight;
	*x = bufX / static_cast<double>(screenWidth);
	*y = bufY / static_cast<double>(screenHeight);
}

void DXLibMath::ConverDisplay(const unsigned short x, const unsigned short y, double *out_x, double *out_y)
{
	*out_x = x / windowWidth;
	*out_y = y / windowHeight;
}

void DXLibMath::ConvertPixcel(double x, double y, int *out_x, int *out_y)
{
	*out_x = static_cast<int>( x * windowWidth );
	*out_y = static_cast<int>( y * windowHeight );
}

void DXLibMath::ConvertPixcelX(double x, int *out_x)
{
	*out_x = static_cast<int>( x * windowWidth );
}

void DXLibMath::ConvertPixcelY(double y, int *out_y)
{
	*out_y = static_cast<int>( y * windowHeight );
}

void DXLibMath::ConvertBlockToScreen(float x, float y, float *out_x, float *out_y)
{
	*out_x = x * BLOCK_SIZE_WIDTH;
	*out_y = y * BLOCK_SIZE_HEIGHT;
}

void DXLibMath::ConvertScreenToBlock(float x, float y, float *out_x, float *out_y)
{
	*out_x = x / BLOCK_SIZE_WIDTH;
	*out_y = y / BLOCK_SIZE_HEIGHT;
}

//---------------------------------------------------------------------------
// ”ŠwŠÖ”
//---------------------------------------------------------------------------
void DXLibMath::FacingTarget(const VECTOR &position, const VECTOR &target, VECTOR *facing, float power)
{
	VECTOR vec;
	vec.x = target.x - position.x;
	vec.y = target.y - position.y;
	Normalize(&vec, vec);
	VECTOR vec2 = *facing;
	Normalize(&vec2, vec2);
	facing->x = vec2.x + (vec.x - vec2.x) * power;
	facing->y = vec2.y + (vec.y - vec2.y) * power;
}

float DXLibMath::Length(const VECTOR &vec)
{
	float ans;
	ans = sqrtf(vec.x*vec.x + vec.y*vec.y);
	return ans;
}

void DXLibMath::Normalize(VECTOR *out, const VECTOR &in)
{
	float length = Length(in);
	if(length == 0.0f)
	{
		out->x = 0.0f;
		out->y = 0.0f;
		return;
	}
	out->x = in.x / length;
	out->y = in.y / length;
}

float DXLibMath::CalcRotation(const VECTOR &vec)
{
	VECTOR v = vec;
	Normalize(&v, v);
	return atan2(v.y, v.x) + 3.141592653589793f / 2.0f;
}

bool DXLibMath::CircleOnPoint(const VECTOR &point, const VECTOR &circlePos, float r)
{
	if ((point.x - circlePos.x)*(point.x - circlePos.x) + (point.y - circlePos.y)*(point.y - circlePos.y) <= r*r)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void DXLibMath::Floor(double *width, double *height)
{
	*width *= windowWidth;
	*width = floor(*width);
	*width /= windowWidth;
	*height *= windowHeight;
	*height = floor(*height);
	*height /= windowHeight;
}