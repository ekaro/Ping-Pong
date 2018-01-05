#include "Paddle.h"

void Paddle::DrawPaddle(const HDC& hdc, int x, int y)
{
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

int Paddle::GetWidth() const
{
	return Width;
}