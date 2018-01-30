#pragma once
#include <windows.h>
#include <array>

class Ball
{
public:
	void DrawBall(const HDC& hdc, float x, float y);
	void DeleteBall(const HDC& hdc, float x, float y);
	void MoveBall();
	void IncreaseSpeed();
	void SwitchYVel();
	void SwitchXVel();
	int GetRadius() const;
	void SetVel(float xvel, float yvel);
	void SetPos(float x, float y);
	void SetRadius(int Radius);
	void SetSpeed(float speed);
	std::pair<float, float> GetPos() const;
	std::pair<float, float> GetOldPos() const; 
	void OutputVel() const;  // function for debugging  
private:
	int BallRadius;
	float BallVel[2];
	float BallPos[2];
	float OldBallPos[2];
	float Speed;
};