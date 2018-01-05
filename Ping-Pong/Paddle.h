#pragma once
#include <windows.h>
#include <array>

class Paddle
{
public:
	Paddle() = default;
	void DrawPaddle(const HDC& hdc, int x, int y);
	void SetWidth(int Width);
	void SetHeight(int Height);
	int GetWidth() const;
private:
	int x = 0;
	int y = 0;
	int Width = 50;
	int Height = 100;
	int Speed;
};