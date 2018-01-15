#pragma once
#include "Paddle.h"
#include "Ball.h"
#include <tchar.h>

class Game
{
public:
	std::pair<int, int> GetClientDim(const HWND& hWnd);
	void DrawPaddles(const HDC& hdc, const HWND& hWnd);
	void DrawBall(const HDC& hdc, const HWND& hWnd);
	void DrawLines(const HDC& hdc, const HWND& hWnd);
	void DrawScores(const HDC& hdc, const HWND& hWnd);
	void MoveRPDown(const HWND& hWnd);
	void MoveRPUp(const HWND& hWnd);
	void MoveLPDown(const HWND& hWnd);
	void MoveLPUp(const HWND& hWnd);
	void MoveBall(const HWND& hWnd);
	void SpawnBall(const HWND& hWnd);
private:
	static constexpr COLORREF White = (RGB(255, 255, 255));
	static constexpr COLORREF Black = (RGB(0, 0, 0));
	static constexpr COLORREF Red = (RGB(255, 0, 0));
	int LeftScore;
	int RightScore;
	HFONT ScoreFont;
	LOGFONT logFont;
	std::wstring ScoreNumber;
	static constexpr TCHAR ScoreMsg[] = _T("10");
	RECT RightPaddleRect;
	RECT LeftPaddleRect;
	RECT BallRect;
	RECT OldBallRect;
	Paddle LeftPaddle;
	Paddle RightPaddle;
	Ball Ball;
};