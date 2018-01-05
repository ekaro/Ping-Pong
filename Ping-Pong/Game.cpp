#include "Game.h"

void Game::DrawPaddles(const HDC& hdc, const HWND& hWnd)
{
	LeftPaddle.SetWidth(GetClientDim(hWnd).first / 20);
	LeftPaddle.SetHeight(GetClientDim(hWnd).first / 10);
	LeftPaddle.DrawPaddle(hdc, 0, 0);

	RightPaddle.SetWidth(GetClientDim(hWnd).first / 20);
	RightPaddle.SetHeight(GetClientDim(hWnd).first / 10);
	RightPaddle.DrawPaddle(hdc, GetClientDim(hWnd).first - RightPaddle.GetWidth(), 0);
}

std::pair<int, int> Game::GetClientDim(const HWND& hWnd)
{
	RECT ClientRect;
	::GetClientRect(hWnd, &ClientRect);

	int CurrentWidth = ClientRect.right - ClientRect.left;
	int CurrentHeight = ClientRect.bottom - ClientRect.top;

	return { CurrentWidth, CurrentHeight };
}