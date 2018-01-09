#include "Game.h"
#include <Gdiplus.h>

void Game::DrawPaddles(const HDC& hdc, const HWND& hWnd)
{
	LeftPaddle.SetWidth(GetClientDim(hWnd).first / 30);
	LeftPaddle.SetHeight(GetClientDim(hWnd).second / 5);
	SelectObject(hdc, GetStockObject(DC_BRUSH));
	SetDCBrushColor(hdc, Black);
	LeftPaddle.DrawPaddle(hdc, 0, LeftPaddle.GetOldPos());
	SetDCBrushColor(hdc, White);
	LeftPaddle.DrawPaddle(hdc, 0, LeftPaddle.GetPos());

	RightPaddle.SetWidth(GetClientDim(hWnd).first / 30);
	RightPaddle.SetHeight(GetClientDim(hWnd).second / 5);
	SelectObject(hdc, GetStockObject(DC_BRUSH));
	SetDCBrushColor(hdc, Black);
	RightPaddle.DrawPaddle(hdc, GetClientDim(hWnd).first - RightPaddle.GetWidth(), RightPaddle.GetOldPos());
	SetDCBrushColor(hdc, White);
	RightPaddle.DrawPaddle(hdc, GetClientDim(hWnd).first - RightPaddle.GetWidth(), RightPaddle.GetPos());
}

void Game::DrawBall(const HDC & hdc, const HWND & hWnd)
{
	Ball.SetWidth(GetClientDim(hWnd).first / 20);
	Ball.SetHeight(GetClientDim(hWnd).first / 20);
	Ball.DrawBall(hdc, (GetClientDim(hWnd).first / 2 - GetClientDim(hWnd).first / 40), (GetClientDim(hWnd).second / 2 - GetClientDim(hWnd).first / 40));
}

void Game::DrawLines(const HDC & hdc, const HWND & hWnd)
{
	for (int i = 0; i < GetClientDim(hWnd).second; i++)
	{
		SetPixel(hdc, LeftPaddle.GetWidth() - 1, i, White);
	}
	
	for (int i = 0; i < GetClientDim(hWnd).second; i++)
	{
		SetPixel(hdc, GetClientDim(hWnd).first / 2, i, White);
	}
	
	for (int i = 0; i < GetClientDim(hWnd).second; i++)
	{
		SetPixel(hdc, GetClientDim(hWnd).first - RightPaddle.GetWidth(), i, White);
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

void Game::MoveRPDown(const HWND& hWnd)
{
	if (RightPaddle.GetPos() <= GetClientDim(hWnd).second - RightPaddle.GetHeight() - 10)
	{
		RightPaddle.MoveDown();

		RightPaddleRect = { GetClientDim(hWnd).first - RightPaddle.GetWidth(), 0, GetClientDim(hWnd).first, GetClientDim(hWnd).second };

		InvalidateRect(hWnd, &RightPaddleRect, false);
	}
}

void Game::MoveRPUp(const HWND& hWnd)
{
	if (RightPaddle.GetPos() >= 10)
	{
		RightPaddle.MoveUp();

		RightPaddleRect = { GetClientDim(hWnd).first - RightPaddle.GetWidth(), 0, GetClientDim(hWnd).first, GetClientDim(hWnd).second };

		InvalidateRect(hWnd, &RightPaddleRect, false);
	}
}

void Game::MoveLPDown(const HWND& hWnd)
{
	if (LeftPaddle.GetPos() <= GetClientDim(hWnd).second - LeftPaddle.GetHeight() - 10)
	{
		LeftPaddle.MoveDown();

		LeftPaddleRect = { 0, 0, LeftPaddle.GetWidth(), GetClientDim(hWnd).second };

		InvalidateRect(hWnd, &LeftPaddleRect, false);
	}
}

void Game::MoveLPUp(const HWND& hWnd)
{
	if (LeftPaddle.GetPos() >= 10)
	{
		LeftPaddle.MoveUp();

		LeftPaddleRect = { 0, 0, LeftPaddle.GetWidth(), GetClientDim(hWnd).second };

		InvalidateRect(hWnd, &LeftPaddleRect, false);
	}
}