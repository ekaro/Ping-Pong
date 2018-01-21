#pragma once
#include <windows.h>
#include <array>

class Paddle
{
public:
	void DrawPaddle(const HDC& hdc, int x, int y);
	void SetWidth(int Width);
	void SetHeight(int Height);
	void MoveDown();
	void MoveUp();
	int GetWidth() const;
	int GetHeight() const;
	int GetOldPos() const;
	int GetPos() const;
	void SetSpeed(float speed);
private:
	int x;
	int y;
	int oldy;
	int Width;
	int Height;
	float Speed;
};