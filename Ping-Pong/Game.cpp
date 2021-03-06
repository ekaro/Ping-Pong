#include "Game.h"

void Game::NewGame(const HWND& hWnd)   // behaviour of the ball on the beginning of game
{
	std::mt19937 rng(rd());
	std::uniform_int_distribution<int> Direction(0, 1);
	int dir = Direction(rng);
	newGame = true;
	if (dir)
	{
		SpawnBall(hWnd, true);
	}
	else
	{
		SpawnBall(hWnd, false);
	}
	newGame = false;
}

void Game::DrawPaddles(const HDC& hdc, const HWND& hWnd)
{
	LeftPaddle.SetWidth(GetClientDim(hWnd).first / 30);
	LeftPaddle.SetHeight(GetClientDim(hWnd).second / 5);
	SelectObject(hdc, GetStockObject(DC_BRUSH));
	
	SetDCBrushColor(hdc, Black);
	LeftPaddle.DrawPaddle(hdc, 0, LeftPaddle.GetOldPos());  // Delete left paddle on old position
	
	SetDCBrushColor(hdc, White);
	LeftPaddle.DrawPaddle(hdc, 0, LeftPaddle.GetPos());     // Draw left paddle on new position

	RightPaddle.SetWidth(GetClientDim(hWnd).first / 30);
	RightPaddle.SetHeight(GetClientDim(hWnd).second / 5);
	SelectObject(hdc, GetStockObject(DC_BRUSH));
	
	SetDCBrushColor(hdc, Black);
	RightPaddle.DrawPaddle(hdc, GetClientDim(hWnd).first - RightPaddle.GetWidth(), RightPaddle.GetOldPos());  // Delete right paddle on old position
	
	SetDCBrushColor(hdc, White);
	RightPaddle.DrawPaddle(hdc, GetClientDim(hWnd).first - RightPaddle.GetWidth(), RightPaddle.GetPos());     // Draw right paddle on new position
}

void Game::DrawBall(const HDC & hdc, const HWND & hWnd)
{
	Ball.SetRadius(GetClientDim(hWnd).first / 40);
	SelectObject(hdc, GetStockObject(DC_BRUSH));
	
	SetDCBrushColor(hdc, Black);	
	Ball.DeleteBall(hdc, (int)Ball.GetOldPos().first, (int)Ball.GetOldPos().second);  // Delete ball on old position

	SetDCBrushColor(hdc, White);
	Ball.DrawBall(hdc, (int)Ball.GetPos().first, (int)Ball.GetPos().second);          // Draw ball on new position
}

void Game::DrawLines(const HDC & hdc, const HWND & hWnd)
{
	for (int i = 0; i < GetClientDim(hWnd).second; i++)
	{
		SetPixel(hdc, LeftPaddle.GetWidth() - 1, i, White);     // Draw left line
	}

	for (int i = 0; i < GetClientDim(hWnd).second; i++)
	{
		SetPixel(hdc, GetClientDim(hWnd).first / 2, i, White);  // Draw middle line
	}

	for (int i = 0; i < GetClientDim(hWnd).second; i++)
	{
		SetPixel(hdc, GetClientDim(hWnd).first - RightPaddle.GetWidth(), i, White);  // Draw right line
	}
}

void Game::DrawScores(const HDC & hdc, const HWND & hWnd)
{
	std::string LSNum = std::to_string(LeftScore);
	std::string RSNum = std::to_string(RightScore);

	int CurrentHeight = GetClientDim(hWnd).second;
	int FontHeight = CurrentHeight / 10;

	memset(&logFont, 0, sizeof(logFont));
	logFont.lfHeight = FontHeight;
	ScoreFont = CreateFontIndirect(&logFont);   // Create font based on height of the window

	SetTextColor(hdc, RGB(255, 255, 255));
	SetBkColor(hdc, RGB(0, 0, 0));
	SelectObject(hdc, ScoreFont);

	TextOut(hdc, GetClientDim(hWnd).first / 4, GetClientDim(hWnd).second / 20, LSNum.c_str(), (int)_tcslen(LSNum.c_str()));        // Draw left score
	TextOut(hdc, GetClientDim(hWnd).first / 4 * 3, GetClientDim(hWnd).second / 20, RSNum.c_str(), (int)_tcslen(RSNum.c_str()));  // Draw right score

	DeleteObject(ScoreFont);    // Delete font after drawing scores to prevent memory leak
}

void Game::SetRightFlag(bool RightUp, bool RightDown)
{
	RightPaddle.SetFlag(RightUp, RightDown);
}

void Game::SetLeftFlag(bool LeftUp, bool LeftDown)
{
	LeftPaddle.SetFlag(LeftUp, LeftDown);
}

void Game::SetSpeed(const HWND& hWnd)
{
	float PaddleSpeed = GetClientDim(hWnd).second / (float)100.0;
	float BallSpeed = (GetClientDim(hWnd).first + GetClientDim(hWnd).second) / (float)1000.0;
	LeftPaddle.SetSpeed(PaddleSpeed);
	RightPaddle.SetSpeed(PaddleSpeed);
	Ball.SetSpeed(BallSpeed);
}

void Game::UpdateBall(const HWND& hWnd)        // ball movement logic
{
	Ball.MoveBall();
	//Ball.OutputVel();
	FieldRect = { LeftPaddle.GetWidth(), 0, GetClientDim(hWnd).first - RightPaddle.GetWidth(), GetClientDim(hWnd).second };
	InvalidateRect(hWnd, &FieldRect, false);

	if (Ball.GetPos().second <= 0)
	{
		Ball.SwitchYVel();
    }
	if (Ball.GetPos().second + Ball.GetRadius() * 2 >= GetClientDim(hWnd).second)
	{
		Ball.SwitchYVel();
	}

	if (Ball.GetPos().first <= LeftPaddle.GetWidth())
	{
		if (LeftPaddle.GetPos() <= (Ball.GetPos().second + Ball.GetRadius()) && (Ball.GetPos().second + Ball.GetRadius()) <= (LeftPaddle.GetPos() + LeftPaddle.GetHeight()))
		{
			Ball.SwitchXVel();
			Ball.IncreaseSpeed();
		}
		else
		{
			Sleep(2000);
			SpawnBall(hWnd, true);
			RightScore++;
		}
	}

	if (Ball.GetPos().first + Ball.GetRadius() * 2 >= GetClientDim(hWnd).first - RightPaddle.GetWidth())
	{
		if (RightPaddle.GetPos() <= (Ball.GetPos().second + Ball.GetRadius()) && (Ball.GetPos().second + Ball.GetRadius()) <= (RightPaddle.GetPos() + RightPaddle.GetHeight()))
		{
			Ball.SwitchXVel();
			Ball.IncreaseSpeed();
		}
		else
		{
			Sleep(2000);
			SpawnBall(hWnd, false);
			LeftScore++;	
		}
	}
}

void Game::UpdatePaddle(const HWND& hWnd)
{
	if (LeftPaddle.GetFlag().first)
	{
		if (LeftPaddle.GetPos() >= 1)
		{
			LeftPaddle.MoveUp();

			LeftPaddleRect = { 0, 0, LeftPaddle.GetWidth(), GetClientDim(hWnd).second };

			InvalidateRect(hWnd, &LeftPaddleRect, false);
		}
	}
	
	if (LeftPaddle.GetFlag().second)
	{
		if (LeftPaddle.GetPos() <= GetClientDim(hWnd).second - LeftPaddle.GetHeight())
		{
			LeftPaddle.MoveDown();

			LeftPaddleRect = { 0, 0, LeftPaddle.GetWidth(), GetClientDim(hWnd).second };

			InvalidateRect(hWnd, &LeftPaddleRect, false);
		}
	}

	if (RightPaddle.GetFlag().first)
	{
		if (RightPaddle.GetPos() >= 1)
		{
			RightPaddle.MoveUp();

			RightPaddleRect = { GetClientDim(hWnd).first - RightPaddle.GetWidth(), 0, GetClientDim(hWnd).first, GetClientDim(hWnd).second };

			InvalidateRect(hWnd, &RightPaddleRect, false);
		}
	}

	if (RightPaddle.GetFlag().second)
	{
		if (RightPaddle.GetPos() <= GetClientDim(hWnd).second - RightPaddle.GetHeight())
		{
			RightPaddle.MoveDown();

			RightPaddleRect = { GetClientDim(hWnd).first - RightPaddle.GetWidth(), 0, GetClientDim(hWnd).first, GetClientDim(hWnd).second };

			InvalidateRect(hWnd, &RightPaddleRect, false);
		}
	}
}

void Game::SpawnBall(const HWND& hWnd, bool direction)   // function for spawning ball in the center
{
	int CurrentClientWidth = GetClientDimEx(hWnd).first;
	int CurrentClientHeight = GetClientDimEx(hWnd).second;

	if (newGame)    // if it is new game use extend GetClientDim function for precise measurement
	{
		float posx = (CurrentClientWidth / (float)2.0 - CurrentClientWidth / (float)40.0);  // GetClientDimEx(hWnd).first / 40 is ball radius
		float posy = (CurrentClientHeight / (float)2.0 - CurrentClientWidth / (float)40.0);
		Ball.SetPos(posx, posy);  // Setting ball postion to the middle of the screen
	}
	else
	{
		float posx = (CurrentClientWidth / (float)2 - CurrentClientWidth / (float)40);  // GetClientDimEx(hWnd).first / 40 is ball radius
		float posy = (CurrentClientHeight / (float)2 - CurrentClientWidth / (float)40);
		Ball.SetPos(posx, posy);  // Setting ball postion to the middle of the screen
	}
	
	std::mt19937 rng(rd());    // Standard mersenne_twister_engine seeded with rd()
	std::uniform_int_distribution<int> GenerateXVel(CurrentClientWidth/10, CurrentClientWidth/10*2);
	std::uniform_int_distribution<int> GenerateYVel(CurrentClientHeight/10, CurrentClientHeight/10*2);

	float XVel = -(GenerateXVel(rng) / (float)100.0);
	float YVel = -(GenerateYVel(rng) / (float)100.0);
	
	if (direction == true)
	{
		XVel *= -1;
	}
	
	Ball.SetVel(XVel, YVel);
}

std::pair<int, int> Game::GetClientDim(const HWND& hWnd)         // function for getting current client dimensions
{
	RECT ClientRect;
	::GetClientRect(hWnd, &ClientRect);

	int CurrentWidth = ClientRect.right - ClientRect.left;
	int CurrentHeight = ClientRect.bottom - ClientRect.top;

	return { CurrentWidth, CurrentHeight };
}

std::pair<int, int> Game::GetClientDimEx(const HWND& hWnd)       // extended function for precise measurement of current client dimensions
{
	RECT ClientRect;
	::GetClientRect(hWnd, &ClientRect);

	DWORD dwStyle = (DWORD)GetWindowLongPtr(hWnd, GWL_STYLE);
	DWORD dwExStyle = (DWORD)GetWindowLongPtr(hWnd, GWL_EXSTYLE);

	AdjustWindowRectEx(&ClientRect, dwStyle, FALSE, dwExStyle);

	int CurrentWidth = ClientRect.right - ClientRect.left;
	int CurrentHeight = ClientRect.bottom - ClientRect.top;

	return { CurrentWidth, CurrentHeight };
}