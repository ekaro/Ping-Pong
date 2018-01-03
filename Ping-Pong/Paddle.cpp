#include "Paddle.h"
/*
Paddle::Paddle()
{

}*/

void Paddle::DrawPaddle(const HDC& hdc, int PadWidth, int PadHeight)
{
	Rectangle(hdc, x, y, x + PadWidth, y + PadHeight);
}

std::pair<int, int> Paddle::GetClientDimensions(const HWND& hWnd)
{
	RECT ClientRect;
	::GetClientRect(hWnd, &ClientRect);

	int CurrentWidth = ClientRect.right - ClientRect.left;
	int CurrentHeight = ClientRect.bottom - ClientRect.top;

	return { CurrentWidth, CurrentHeight };
}