#include "Paddle.h"

void Paddle::DrawPaddle(const HDC& hdc, int x, int y)
{
	Rectangle(hdc, x, y, x + Width, y + Height);
}

void Paddle::MoveUp()
{
	oldy = y;
	y = y - Speed;
}

void Paddle::MoveDown()
{
	oldy = y;
	y = y + Speed;
}

void Paddle::SetWidth(int CurrentWidth)
{
	Width = CurrentWidth;
}

void Paddle::SetHeight(int CurrentHeight)
{
	Height = CurrentHeight;
}

void Paddle::SetSpeed(float speed)
{
	Speed = speed;
}

void Paddle::SetFlag(bool up, bool down)
{
	MoveU = up;
	MoveD = down;
}

int Paddle::GetWidth() const
{
	return Width;
}

int Paddle::GetHeight() const
{
	return Height;
}

float Paddle::GetSpeed() const
{
	return Speed;
}

int Paddle::GetPos() const
{
	return y;
}

int Paddle::GetOldPos() const
{
	return oldy;
}

std::pair<bool, bool> Paddle::GetFlag() const
{
	return {MoveU, MoveD};
}

std::pair<int, int> Paddle::GetClientDim(const HWND& hWnd)         // function for getting current client dimensions
{
	RECT ClientRect;
	::GetClientRect(hWnd, &ClientRect);

	int CurrentWidth = ClientRect.right - ClientRect.left;
	int CurrentHeight = ClientRect.bottom - ClientRect.top;

	return { CurrentWidth, CurrentHeight };
}