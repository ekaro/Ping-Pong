#pragma once
#include "Paddle.h"
#include "Ball.h"
#include <random>
#include <string>
#include <tchar.h>

class Game
{
public:
	void NewGame(const HWND& hWnd);
	void DrawPaddles(const HDC& hdc, const HWND& hWnd);
	void DrawBall(const HDC& hdc, const HWND& hWnd);
	void DrawLines(const HDC& hdc, const HWND& hWnd);
	void DrawScores(const HDC& hdc, const HWND& hWnd);
	void SetSpeed(const HWND& hWnd);
	void SetRightFlag(bool RightUp, bool RightDown);
	void SetLeftFlag(bool LeftUp, bool LeftDown);
	void UpdateBall(const HWND& hWnd);
	void UpdatePaddle(const HWND& hWnd);
	void SpawnBall(const HWND& hWnd, bool direction);
	std::pair<int, int> GetClientDim(const HWND& hWnd);
	std::pair<int, int> GetClientDimEx(const HWND& hWnd);
private:
	static constexpr COLORREF White = (RGB(255, 255, 255));
	static constexpr COLORREF Black = (RGB(0, 0, 0));
	static constexpr COLORREF Red = (RGB(255, 0, 0));
	bool newGame;
	int LeftScore;
	int RightScore;
	HFONT ScoreFont;
	LOGFONT logFont;
	std::random_device rd;      // Will be used to obtain a seed for the random number engine
	RECT RightPaddleRect;
	RECT LeftPaddleRect;
	RECT FieldRect;
	Paddle LeftPaddle;
	Paddle RightPaddle;
	Ball Ball;
};