#include "Ball.h"
#include <string>

void Ball::DrawBall(const HDC& hdc, float x, float y)
{
	Ellipse(hdc, x, y, x + BallRadius * 2, y + BallRadius * 2);
}

void Ball::DeleteBall(const HDC& hdc, float x, float y)
{
	Ellipse(hdc, x, y, x + BallRadius * 2, y + BallRadius * 2);
}

void Ball::MoveBall()
{
	OldBallPos[0] = BallPos[0];
	OldBallPos[1] = BallPos[1];
	BallPos[0] = BallPos[0] + BallVel[0];
	BallPos[1] = BallPos[1] + BallVel[1];
}

void Ball::IncreaseSpeed()
{
	if (BallVel[0] > 0)
	{
		BallVel[0] += Speed;
	}
	if (BallVel[0] < 0)
	{
		BallVel[0] -= Speed;
	}
}

int Ball::GetRadius() const
{
	return BallRadius;
}

void Ball::SwitchYVel()
{
	BallVel[1] *= -1;
}

void Ball::SwitchXVel()
{
	BallVel[0] *= -1;
}

void Ball::SetVel(float xvel , float yvel)
{
	BallVel[0] = xvel;
	BallVel[1] = yvel;
}

void Ball::SetPos(float x, float y)
{
	BallPos[0] = x;
	BallPos[1] = y;
}

void Ball::SetRadius(int Radius)
{
	BallRadius = Radius;
}

void Ball::SetSpeed(float speed)
{
	Speed = speed;
}

std::pair<float, float> Ball::GetPos() const
{
	return { BallPos[0], BallPos[1] };
}

std::pair<float, float> Ball::GetOldPos() const
{
	return { OldBallPos[0], OldBallPos[1] };
}

void Ball::OutputVel() const    
{
	std::string sx = std::to_string(BallVel[0]);
	std::string sy = std::to_string(BallVel[1]);
	OutputDebugString("X Ball Velocity: ");
	OutputDebugString(sx.c_str());
	OutputDebugString("\n");
	OutputDebugString("Y Ball Velocity:");
	OutputDebugString(sy.c_str());
	OutputDebugString("\n");
}