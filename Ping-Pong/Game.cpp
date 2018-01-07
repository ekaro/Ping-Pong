#include "Game.h"
#include <Gdiplus.h>

void Game::DrawPaddles(const HDC& hdc, const HWND& hWnd)
{
	LeftPaddle.SetWidth(GetClientDim(hWnd).first / 20);
	LeftPaddle.SetHeight(GetClientDim(hWnd).first / 10);
	LeftPaddle.DrawPaddle(hdc, 0, 0);

	RightPaddle.SetWidth(GetClientDim(hWnd).first / 20);
	RightPaddle.SetHeight(GetClientDim(hWnd).first / 10);
	RightPaddle.DrawPaddle(hdc, GetClientDim(hWnd).first - RightPaddle.GetWidth(), 0);
}

void Game::DrawBall(const HDC & hdc, const HWND & hWnd)
{
	Ball.SetWidth(GetClientDim(hWnd).first / 20);
	Ball.SetHeight(GetClientDim(hWnd).first / 20);
	Ball.DrawBall(hdc, (GetClientDim(hWnd).first / 2 - GetClientDim(hWnd).first / 40), (GetClientDim(hWnd).second / 2 - GetClientDim(hWnd).first / 40));
}

void Game::DrawLine(const HDC & hdc, const HWND & hWnd)
{
	for (int i = 0; i < GetClientDim(hWnd).second; i++)
	{
		SetPixel(hdc, GetClientDim(hWnd).first / 2, i, White);
	}	
}

std::pair<int, int> Game::GetClientDim(const HWND& hWnd)
{
	RECT ClientRect;
	::GetClientRect(hWnd, &ClientRect);

	int CurrentWidth = ClientRect.right - ClientRect.left;
	int CurrentHeight = ClientRect.bottom - ClientRect.top;

	return { CurrentWidth, CurrentHeight };
}