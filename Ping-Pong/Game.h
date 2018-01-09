#pragma once
#include "Paddle.h"
#include "Ball.h"

class Game
{
public:
	std::pair<int, int> GetClientDim(const HWND& hWnd);
	void DrawPaddles(const HDC& hdc, const HWND& hWnd);
	void DrawBall(const HDC& hdc, const HWND& hWnd);
	void DrawLines(const HDC& hdc, const HWND& hWnd);
	void MoveDown(const HWND& hWnd);
	void MoveUp(const HWND& hWnd);
private:
	static constexpr COLORREF White = (RGB(255, 255, 255));
	static constexpr COLORREF Black = (RGB(0, 0, 0));
	RECT RightPaddleRect;
	Paddle LeftPaddle;
	Paddle RightPaddle;
	Ball Ball;
};