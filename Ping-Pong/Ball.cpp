#include "Ball.h"

void Ball::DrawBall(const HDC& hdc, int x, int y)
{
	BallPos[0] = x;
	BallPos[1] = y;
	Ellipse(hdc, BallPos[0], BallPos[1], BallPos[0] + BallRadius*2, BallPos[1] + BallRadius*2);
}

void Ball::SetPos(int x, int y)
{
	BallPos[0] = x;
	BallPos[1] = y;
	OldBallPos[0] = x;
	OldBallPos[1] = y;
}

void Ball::SetRadius(int Radius)
{
	BallRadius = Radius;
}

void Ball::MoveBall()
{
	OldBallPos[0] = BallPos[0];
	OldBallPos[1] = BallPos[1];
	BallPos[0] = BallPos[0] - 10;
	BallPos[1] = BallPos[1] - 10;
}

std::pair<int, int> Ball::GetPos() const
{
	return {BallPos[0], BallPos[1]};
}

std::pair<int, int> Ball::GetOldPos() const
{
	return { OldBallPos[0], OldBallPos[1] };
}

int Ball::GetRadius() const
{
	return BallRadius;
}
