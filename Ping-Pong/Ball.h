#pragma once
#include <windows.h>
#include <array>

class Ball
{
public:
	void DrawBall(const HDC& hdc, float x, float y);
	void RemoveBall(const HDC& hdc, float x, float y);
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
	void SetSpeed(float speed);
private:
	int BallRadius;
	float BallVel[2];
	float BallPos[2];
	float OldBallPos[2];
	float Speed = 0.3;
};