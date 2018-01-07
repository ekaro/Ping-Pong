#pragma once
#include <windows.h>

class Ball
{
public:
	void DrawBall(const HDC& hdc, int x, int y);
	void SetWidth(int Width);
	void SetHeight(int Height);
	int GetWidth() const;
private:
	int x = 0;
	int y = 0;
	int Width = 50;
	int Height = 100;
	int BallRadius;
	int BallVell;
	int BallPos;
	int BallSpeed;
};