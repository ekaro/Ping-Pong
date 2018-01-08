#include "Paddle.h"

void Paddle::DrawPaddle(const HDC& hdc, int xloc, int yloc)
{
	x = xloc;
	y = yloc;
	Rectangle(hdc, x, y, x + Width, y + Height);
}

void Paddle::SetWidth(int CurrentWidth)
{
	Width = CurrentWidth;
}

void Paddle::SetHeight(int CurrentHeight)
{
	Height = CurrentHeight;
}

void Paddle::MoveDown()
{
	y = y + 10;
}

void Paddle::MoveUp()
{
	y = y - 10;		
}

int Paddle::GetPos() const
{
	return y;
}

int Paddle::GetWidth() const
{
	return Width;
}

int Paddle::GetHeight() const
{
	return Height;
}