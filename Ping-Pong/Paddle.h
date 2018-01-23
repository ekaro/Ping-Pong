#pragma once
#include <windows.h>

class Paddle
{
public:
	void DrawPaddle(const HDC& hdc, int x, int y);
	void MoveUp();
	void MoveDown();
	void SetWidth(int Width);
	void SetHeight(int Height);
	void SetSpeed(float speed);
	int GetWidth() const;
	int GetHeight() const;
	int GetPos() const;
	int GetOldPos() const;
private:
	int x;
	int y;
	int oldy;
	int Width;
	int Height;
	float Speed;
};