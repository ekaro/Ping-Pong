#pragma once
#include "Paddle.h"
#include "Ball.h"

class Game
{
public:
	std::pair<int, int> GetClientDim(const HWND& hWnd);
	void DrawPaddles(const HDC& hdc, const HWND& hWnd);
	void DrawBall(const HDC& hdc, const HWND& hWnd);
	void DrawLine(const HDC& hdc, const HWND& hWnd);
private:
	static constexpr COLORREF White = (RGB(255, 255, 255));
	Paddle LeftPaddle;
	Paddle RightPaddle;
	Ball Ball;
};