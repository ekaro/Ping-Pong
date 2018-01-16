#include "Ball.h"

void Ball::DrawBall(const HDC& hdc, int x, int y)
{
	Ellipse(hdc, x, y, x + BallRadius*2, y + BallRadius*2);
}

void Ball::RemoveBall(const HDC& hdc, int x, int y)
{
	Ellipse(hdc, x - 1, y - 1, x + BallRadius * 2 + 1, y + BallRadius * 2 + 1);
}

void Ball::SetPos(int x, int y)
{
    OldBallPos[0] = BallPos[0];
	OldBallPos[1] = BallPos[1];
	BallPos[0] = x;
	BallPos[1] = y;
}

void Ball::SetRadius(int Radius)
{
	BallRadius = Radius;
}

void Ball::MoveBall()
{
	OldBallPos[0] = BallPos[0];
	OldBallPos[1] = BallPos[1];
	BallPos[0] = BallPos[0] - BallVel[0];
	BallPos[1] = BallPos[1] - BallVel[1];
}

std::pair<int, int> Ball::GetPos() const
{
	return {BallPos[0], BallPos[1]};
}

std::pair<int, int> Ball::GetOldPos() const
{
	return {OldBallPos[0], OldBallPos[1]};
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

void Ball::SetVel(int vel)
{
	BallVel[0] = vel;
	BallVel[1] = vel;
}
