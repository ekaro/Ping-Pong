#include <stdlib.h>
#include <Windowsx.h>
#include <windows.h>
#include <tchar.h>
#include "Game.h"


// Forward declaration of functions included in this module:
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// Window properties
int WindowWidth = 1200;
int WindowHeight = 800;

int xPos;
int yPos;

Game PingPong;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	static TCHAR szWindowClass[] = _T("WinApp");
	static TCHAR szTitle[] = _T("Ping-Pong");

	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = CreateSolidBrush(RGB(0, 0, 0));  // wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL,
			_T("Call to RegisterClassEx failed!"),
			_T("Windows Desktop Guided Tour"),
			NULL);

		return 1;
	}

	HWND hWnd = CreateWindow(
		szWindowClass,
		szTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		WindowWidth, WindowHeight,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	if (IsWindow(hWnd))
	{
		DWORD dwStyle = GetWindowLongPtr(hWnd, GWL_STYLE);
		DWORD dwExStyle = GetWindowLongPtr(hWnd, GWL_EXSTYLE);
		HMENU menu = GetMenu(hWnd);

		RECT rc = { 0, 0, WindowWidth, WindowHeight };

		AdjustWindowRectEx(&rc, dwStyle, menu ? TRUE : FALSE, dwExStyle);

		SetWindowPos(hWnd, NULL, 0, 0, rc.right - rc.left, rc.bottom - rc.top, SWP_NOZORDER | SWP_NOMOVE);
	}

	if (!hWnd)
	{
		MessageBox(NULL,
			_T("Call to CreateWindow failed!"),
			_T("Windows Desktop Guided Tour"),
			NULL);

		return 1;
	}
	
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}


#define ID_BUTTON 1

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	TCHAR display_msg[] = _T("Message in window");

	switch (message)
	{
	case WM_CREATE:

		PingPong.NewGame(hWnd);

	case WM_COMMAND:

		break;

	case WM_PAINT:

		hdc = BeginPaint(hWnd, &ps);

		PingPong.DrawBall(hdc, hWnd);
		PingPong.DrawPaddles(hdc, hWnd);
		PingPong.DrawLines(hdc, hWnd);		
		PingPong.MoveBall(hWnd);
		PingPong.DrawScores(hdc, hWnd);
		
		EndPaint(hWnd, &ps);
		break;

	case WM_LBUTTONDOWN:
		xPos = GET_X_LPARAM(lParam);
		yPos = GET_Y_LPARAM(lParam);

		break;

	case WM_SIZE:

		PingPong.SetSpeed(hWnd);
		break;

	case WM_KEYDOWN:

		switch (wParam)
		{
			case 0x28:
				
				PingPong.MoveRPDown(hWnd);
				break;

			case 0x26:

				PingPong.MoveRPUp(hWnd);
				break;

			case 0x57:

				PingPong.MoveLPUp(hWnd);
				break;

			case 0x53:
				
				PingPong.MoveLPDown(hWnd);
				break;
		}
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}
	return 0;
}