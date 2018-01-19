#pragma once
#include <windows.h>
#include <array>

class Ball
{
public:
	void DrawBall(const HDC& hdc, int x, int y);
	void RemoveBall(const HDC& hdc, int x, int y);
	void SetRadius(int Radius);
	void SetPos(float x, float y);
	void SwitchYVel();
	void SwitchXVel();
	void IncreaseSpeed();
	void SetVel(float xvel, float yvel);
	void MoveBall();
	std::pair<float, float> GetPos() const;
	std::pair<float, float> GetOldPos() const;
	void OutputVel() const;
	int GetRadius() const;
private:
	int BallRadius;
	float BallVel[2] = {1.0, 1.0};
	float BallPos[2];
	float OldBallPos[2];
};