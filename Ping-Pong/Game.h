#pragma once
#include "Paddle.h"
#include "Ball.h"

class Game
{
public:
	std::pair<int, int> GetClientDim(const HWND& hWnd);
	void DrawPaddles(const HDC& hdc, const HWND& hWnd);
private:
	Paddle LeftPaddle;
	Paddle RightPaddle;
	Ball Ball;
};