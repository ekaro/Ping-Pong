#include "Ball.h"

void Ball::DrawBall(const HDC& hdc, int x, int y)
{
	Ellipse(hdc, x, y, x + Width, y + Height);
}

void Ball::SetWidth(int CurrentWidth)
{
	Width = CurrentWidth;
}

void Ball::SetHeight(int CurrentHeight)
{
	Height = CurrentHeight;
}

int Ball::GetWidth() const
{
	return Width;
}
