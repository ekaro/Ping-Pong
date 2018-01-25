#pragma once
#include "Paddle.h"
#include "Ball.h"
#include <random>

class Game
{
public:
	void NewGame(const HWND& hWnd);
	void DrawPaddles(const HDC& hdc, const HWND& hWnd);
	void DrawBall(const HDC& hdc, const HWND& hWnd);
	void DrawLines(const HDC& hdc, const HWND& hWnd);
	void DrawScores(const HDC& hdc, const HWND& hWnd);
	void MoveRPDown(const HWND& hWnd);
	void MoveRPUp(const HWND& hWnd);
	void MoveLPDown(const HWND& hWnd);
	void MoveLPUp(const HWND& hWnd);
	void MoveBall(const HWND& hWnd);
	void SpawnBall(const HWND& hWnd, bool direction);
	void SetSpeed(const HWND& hWnd);
	void SetRightFlag(bool RightUp, bool RightDown);
	void SetLeftFlag(bool LeftUp, bool LeftDown);
	std::pair<int, int> GetClientDim(const HWND& hWnd);
	std::pair<int, int> GetClientDimEx(const HWND& hWnd);
private:
	static constexpr COLORREF White = (RGB(255, 255, 255));
	static constexpr COLORREF Black = (RGB(0, 0, 0));
	static constexpr COLORREF Red = (RGB(255, 0, 0));
	bool newGame;
	bool LPD;
	bool LPU;
	bool RPD;
	bool RPU;
	int LeftScore;
	int RightScore;
	HFONT ScoreFont;
	LOGFONT logFont;
	std::string LeftScoreNumber;
	std::string RightScoreNumber;
	std::random_device rd;      // Will be used to obtain a seed for the random number engine
	RECT RightPaddleRect;
	RECT LeftPaddleRect;
	RECT BallRect;
	RECT OldBallRect;
	Paddle LeftPaddle;
	Paddle RightPaddle;
	Ball Ball;
};