#include "Game.h"
#include <Gdiplus.h>
#include <tchar.h>
#include <windows.h>
#include <vector>
#include <random>
#include <string> 
#include <array>


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
	Ball.SetRadius(GetClientDim(hWnd).first / 40);
	SelectObject(hdc, GetStockObject(DC_BRUSH));
	SetDCBrushColor(hdc, Black);
	Ball.RemoveBall(hdc, Ball.GetOldPos().first, Ball.GetOldPos().second);
	SetDCBrushColor(hdc, White);
	Ball.DrawBall(hdc, Ball.GetPos().first, Ball.GetPos().second);
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

void Game::DrawScores(const HDC & hdc, const HWND & hWnd)
{
	LeftScoreNumber = std::to_string(LeftScore);
	RightScoreNumber = std::to_string(RightScore);

	int CurrentHeight = GetClientDim(hWnd).second;
	int FontHeight = CurrentHeight / 10;

	memset(&logFont, 0, sizeof(logFont));
	logFont.lfHeight = FontHeight;
	ScoreFont = CreateFontIndirect(&logFont);

	SetTextColor(hdc, RGB(255, 255, 255));
	SetBkColor(hdc, RGB(0, 0, 0));
	SelectObject(hdc, ScoreFont);
	TextOut(hdc, GetClientDim(hWnd).first / 4, GetClientDim(hWnd).second / 20, LeftScoreNumber.c_str(), _tcslen(LeftScoreNumber.c_str()));
	TextOut(hdc, GetClientDim(hWnd).first / 4 * 3, GetClientDim(hWnd).second / 20, RightScoreNumber.c_str(), _tcslen(RightScoreNumber.c_str()));

	DeleteObject(ScoreFont);
}

std::pair<int, int> Game::GetClientDim(const HWND& hWnd)
{
	RECT ClientRect;
	::GetClientRect(hWnd, &ClientRect);

	int CurrentWidth = ClientRect.right - ClientRect.left;
	int CurrentHeight = ClientRect.bottom - ClientRect.top;

	return { CurrentWidth, CurrentHeight };
}

std::pair<int, int> Game::GetClientDimEx(const HWND& hWnd)
{
	RECT ClientRect;
	::GetClientRect(hWnd, &ClientRect);

	DWORD dwStyle = GetWindowLongPtr(hWnd, GWL_STYLE);
	DWORD dwExStyle = GetWindowLongPtr(hWnd, GWL_EXSTYLE);

	AdjustWindowRectEx(&ClientRect, dwStyle, FALSE, dwExStyle);

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

void Game::MoveBall(const HWND& hWnd)
{
	Ball.MoveBall();
	//BallRect = { Ball.GetPos().first, Ball.GetPos().second, Ball.GetPos().first + Ball.GetRadius()*2, Ball.GetPos().second + Ball.GetRadius()*2 };
	BallRect = { LeftPaddle.GetWidth(), 0, GetClientDim(hWnd).first - RightPaddle.GetWidth(), GetClientDim(hWnd).second };
	InvalidateRect(hWnd, &BallRect, false);

	if (Ball.GetPos().second <= 0)
	{
		Ball.SwitchYVel();
    }
	if (Ball.GetPos().second + Ball.GetRadius() * 2 >= GetClientDim(hWnd).second)
	{
		Ball.SwitchYVel();
	}

	if (Ball.GetPos().first <= LeftPaddle.GetWidth())
	{
		if (LeftPaddle.GetPos() <= (Ball.GetPos().second + Ball.GetRadius()) && (Ball.GetPos().second + Ball.GetRadius()) <= (LeftPaddle.GetPos() + LeftPaddle.GetHeight()))
		{
			Ball.SwitchXVel();
		}
		else
		{
			SpawnBall(hWnd);
			RightScore++;
		}
	}

	if (Ball.GetPos().first + Ball.GetRadius() * 2 >= GetClientDim(hWnd).first - RightPaddle.GetWidth())
	{
		if (RightPaddle.GetPos() <= (Ball.GetPos().second + Ball.GetRadius()) && (Ball.GetPos().second + Ball.GetRadius()) <= (RightPaddle.GetPos() + RightPaddle.GetHeight()))
		{
			Ball.SwitchXVel();
		}
		else
		{
			SpawnBall(hWnd);
			LeftScore++;
		}
	}
}

void Game::SpawnBall(const HWND& hWnd)
{
	int posx = (GetClientDimEx(hWnd).first / 2 - GetClientDimEx(hWnd).first / 40);  // GetClientDimEx(hWnd).first / 40 is ball radius
	int posy = (GetClientDimEx(hWnd).second / 2 - GetClientDimEx(hWnd).first / 40);
	Ball.SetPos(posx, posy);
	int dim = GetClientDimEx(hWnd).first + GetClientDimEx(hWnd).second;
	int vel = (dim / 1800);
	Ball.SetVel(vel);
}