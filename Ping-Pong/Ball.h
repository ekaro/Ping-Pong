#pragma once
#include <windows.h>
#include <array>

class Ball
{
public:
	void DrawBall(const HDC& hdc, int x, int y);
	void RemoveBall(const HDC& hdc, int x, int y);
	void SetRadius(int Radius);
	void SetPos(int x, int y);
	void SwitchYVel();
	void SwitchXVel();
	void MoveBall();
	std::pair<int, int> GetPos() const;
	std::pair<int, int> GetOldPos() const;
	int GetRadius() const;
private:
	int BallRadius;
	int BallVel[2];
	int BallPos[2];
	int OldBallPos[2];
};