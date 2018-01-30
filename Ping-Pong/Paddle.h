#pragma once
#include <windows.h>
#include <array>

class Paddle
{
public:
	void DrawPaddle(const HDC& hdc, int x, int y);
	void MoveUp();
	void MoveDown();
	void SetWidth(int Width);
	void SetHeight(int Height);
	void SetSpeed(float speed);
	void SetFlag(bool up, bool down);
	int GetWidth() const;
	int GetHeight() const;
	int GetPos() const;
	int GetOldPos() const;
	std::pair<bool, bool> GetFlag() const;
	std::pair<int, int> GetClientDim(const HWND& hWnd);
private:
	int x;
	int y;
	int oldy;
	int Width;
	int Height;
	float Speed;
	bool MoveU;
	bool MoveD;
};