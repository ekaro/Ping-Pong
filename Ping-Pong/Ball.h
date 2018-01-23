#pragma once
#include <windows.h>
#include <array>

class Ball
{
public:
	void MoveBall();
	void DrawBall(const HDC& hdc, float x, float y);
	void DeleteBall(const HDC& hdc, float x, float y);
	void IncreaseSpeed();
	void OutputVel() const;  // function for debugging
	void SwitchYVel();
	void SwitchXVel();
	void SetVel(float xvel, float yvel);
	void SetPos(float x, float y);
	void SetRadius(int Radius);
	void SetSpeed(float speed);
	int GetRadius() const;
	std::pair<float, float> GetPos() const;
	std::pair<float, float> GetOldPos() const;   
private:
	int BallRadius;
	float BallVel[2];
	float BallPos[2];
	float OldBallPos[2];
	float Speed;
};