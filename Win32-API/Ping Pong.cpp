#include<windows.h>
#include<iostream>
#include<string.h>
#include<math.h>
#include<ctime>
using namespace std;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
////////////////////Game Board////////////////////////////////
int xint = 40;
int yint = 40;
int xsize = 920;
int ysize = 420;
int BoardSize = 50;
RECT UpBoard = { xint - 30,yint - 30, xint + xsize + 40, yint + ysize + 40 };
RECT DownBoard = { xint - 10,yint - 10,xint + xsize + 20,yint + ysize + 20 };
RECT LeftBoard = { DownBoard.left,(yint + ysize) / 2 - BoardSize, DownBoard.left + 10, (yint + ysize) / 2 + BoardSize };
RECT RightBoard = { DownBoard.right - 10,(yint + ysize) / 2 - BoardSize, DownBoard.right, (yint + ysize) / 2 + BoardSize };
POINT Ground[8] = { xint,yint,xint + xsize,yint,xint + xsize,yint + ysize,(xint + xsize) / 2,yint + ysize,(xint + xsize) / 2,yint,(xint + xsize) / 2,yint + ysize,xint,yint + ysize,xint,yint };
POINT BallCenter = { (xint + xsize) / 2,(yint + ysize) / 2 };
bool PlayX = true;
bool PlayY = true;
bool play = false;
bool angle = true;
int Player1 = 0;
int Player2 = 0;
int speed1 = 5;
int speed2 = 7;
int TimeDiff = 20;
////////////////////Brushes& Pens///////////////////////////
HBRUSH bMaroon = (HBRUSH)CreateSolidBrush(RGB(128, 0, 0));
HBRUSH bBlack = (HBRUSH)CreateSolidBrush(RGB(0, 0, 0));
HBRUSH bWhite = (HBRUSH)CreateSolidBrush(RGB(255, 255, 255));
HBRUSH bGreen = (HBRUSH)CreateSolidBrush(RGB(0, 255, 0));
HBRUSH bBlue = (HBRUSH)CreateSolidBrush(RGB(0, 0, 255));
HBRUSH bRed = (HBRUSH)CreateSolidBrush(RGB(255, 0, 0));
HPEN pWhite = (HPEN)CreatePen(PS_SOLID, 5, RGB(255, 255, 255));
HPEN pBlue = (HPEN)CreatePen(PS_SOLID, 5, RGB(0, 0, 255));
HPEN pBlack = (HPEN)CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
/////////////////////////// Initializing Values ////////////////////////////////////
void GameReset()
{
	UpBoard = { xint - 30,yint - 30, xint + xsize + 40, yint + ysize + 40 };
	DownBoard = { xint - 10,yint - 10,xint + xsize + 20,yint + ysize + 20 };
	LeftBoard = { DownBoard.left,(yint + ysize) / 2 - 50, DownBoard.left + 10, (yint + ysize) / 2 + 50 };
	RightBoard = { DownBoard.right - 10,(yint + ysize) / 2 - 50, DownBoard.right, (yint + ysize) / 2 + 50 };
	BallCenter = { (xint + xsize) / 2,(yint + ysize) / 2 };

}
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR szCmdLine, int iCmdShow)
{
	MSG msg;
	WNDCLASS wndclass;
	HWND hwnd;

	static TCHAR AppName[] = TEXT("Wheel");

	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hInstance = hInstance;
	wndclass.lpfnWndProc = WndProc;
	wndclass.lpszClassName = AppName;
	wndclass.lpszMenuName = TEXT("MENU");
	wndclass.style = CS_VREDRAW | CS_HREDRAW;

	if (!RegisterClass(&wndclass))
	{
		MessageBox(NULL, TEXT("Panni palli mone!!!"), AppName, MB_ICONERROR);
		return 0;
	}

	hwnd = CreateWindow(AppName, TEXT("Wheel!!!"), WS_OVERLAPPEDWINDOW, 100, 100, 1030, 550, NULL, NULL, hInstance, NULL);
	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);
	RECT rect;
	DWORD time_count;
	while (1)
	{
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			if (msg.message == WM_QUIT)
			{
				exit(0);
			}
			DispatchMessage(&msg);
		}
		//////////////////Ball Movement & angle///////////
		GetClientRect(hwnd, &rect);
		if (play == true)
		{
			if (PlayX == true)
			{
				if(angle==true)
					BallCenter.x+=speed1;
				else
					BallCenter.x+=speed2;
			}
			if (PlayY == true)
			{
				if (angle == true)
					BallCenter.y +=speed1;
				else
					BallCenter.y +=speed2;
			}
			if (PlayX == false)
			{
				if (angle == true)
					BallCenter.x -=speed1;
				else
					BallCenter.x -= speed2;
			}
			if (PlayY == false)
			{
				if (angle == true)
					BallCenter.y -=speed1;
				else
					BallCenter.y -=speed2;
			}
			///////////Collision with the Board////////////////////
			if (BallCenter.x - 10 <= LeftBoard.right&&BallCenter.y >= LeftBoard.top&&BallCenter.y <= LeftBoard.bottom)
			{
				cout << "\nBallCenter.y: " << BallCenter.y << "RightBoard.top: " << RightBoard.top << "RightBoard.top+BoardSize/2: " << RightBoard.top + BoardSize / 2;
				if (BallCenter.y+10>= LeftBoard.top&&BallCenter.y-10<=( LeftBoard.top + (BoardSize / 2)))
					PlayY = false;
				if (BallCenter.y-10<= LeftBoard.bottom&&BallCenter.y+10 > (LeftBoard.top + (BoardSize / 2)))
					PlayY = true;
				if (BallCenter.y <= (LeftBoard.top + (BoardSize * 2 / 3)) && BallCenter.y >= (LeftBoard.top + (BoardSize * 1 / 3)))
					angle = true;
				else
					angle = false;
				PlayX = true;
			}
			if (BallCenter.y - 10 <= DownBoard.top)
				PlayY = true;
			if (BallCenter.x + 10 >= RightBoard.left&&BallCenter.y >= RightBoard.top&&BallCenter.y <= RightBoard.bottom)
			{
				cout << "\nBallCenter.y: " << BallCenter.y << "RightBoard.top: " << RightBoard.top << "RightBoard.top+BoardSize/2: " << RightBoard.top + BoardSize / 2;
				if (BallCenter.y+10>= RightBoard.top&&BallCenter.y +10<= (RightBoard.top + BoardSize / 2))
					PlayY = false;
				if (BallCenter.y+10<= RightBoard.bottom&&BallCenter.y+10> (RightBoard.top + BoardSize / 2))
					PlayY = true;
				if (BallCenter.y <= (RightBoard.top + (BoardSize * 2 / 3)) && BallCenter.y >= (RightBoard.top + (BoardSize * 1 / 3)))
					angle = true;
				else
					angle = false;
				PlayX = false;
			}
			if (BallCenter.y + 10 >= DownBoard.bottom)
				PlayY = false;
			if (BallCenter.x <= DownBoard.left)
			{
				GameReset();
				play = false;
				Player2++;
			}
			if (BallCenter.x >= DownBoard.right)
			{
				GameReset();
				play = false;
				Player1++;
			}
		}
		
		time_count = GetTickCount();
		while (GetTickCount() - time_count<TimeDiff);
		InvalidateRect(hwnd, &rect, true);
	}
	return msg.wParam;
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	switch (message)
	{
	case WM_CREATE:break;
	case WM_KEYDOWN: {
		////////////Board Movement//////////////
		if (LOWORD(wParam) == 38)//Up Arrow
		{
			if (RightBoard.top - 20 >= DownBoard.top)
			{
				RightBoard.top -= 20;
				RightBoard.bottom -= 20;
			}
		}
		if (LOWORD(wParam) == 40)//Down Arrow
		{
			if (RightBoard.bottom + 20 <= DownBoard.bottom)
			{
				RightBoard.top += 20;
				RightBoard.bottom += 20;
			}
		}
		if (LOWORD(wParam) == 87)//W Key
		{
			if (LeftBoard.top - 20 >= DownBoard.top)
			{
				LeftBoard.top -= 20;
				LeftBoard.bottom -= 20;
			}
		}
		if (LOWORD(wParam) == 83)//S Key
		{
			if (LeftBoard.bottom +20 <= DownBoard.bottom)
			{
				LeftBoard.top += 20;
				LeftBoard.bottom += 20;
			}
		}
		if (LOWORD(wParam) == 32)//space
		{
			play = true;
		}

	}
	case WM_PAINT: {
		hdc = BeginPaint(hwnd, &ps);
		TCHAR s1[20], s2[20];
		int size1 = wsprintf(s1, TEXT("Player 1 : %i"), Player1);
		int size2 = wsprintf(s2, TEXT("Player 2 : %i"), Player2);
		FillRect(hdc, &UpBoard, bBlack);
		FillRect(hdc, &DownBoard, bGreen);
		FillRect(hdc, &LeftBoard, bBlue);
		FillRect(hdc, &RightBoard, bBlue);
		SelectObject(hdc, pWhite);
		SelectObject(hdc, bGreen);
		Polyline(hdc, Ground, 8);
		Ellipse(hdc, (xint + xsize) / 2 - 50, (yint + ysize) / 2 - 50, (xint + xsize) / 2 + 50, (yint + ysize) / 2 + 50);
		SelectObject(hdc, bWhite);
		Ellipse(hdc, (xint + xsize) / 2 - 5, (yint + ysize) / 2 - 5, (xint + xsize) / 2 + 5, (yint + ysize) / 2 + 5);
		SelectObject(hdc, bBlack);
		SelectObject(hdc, pBlue);
		Ellipse(hdc, BallCenter.x - 10, BallCenter.y - 10, BallCenter.x + 10, BallCenter.y + 10);
		SetBkColor(hdc, RGB(0, 255, 0));
		TextOut(hdc, 100, 100, s1, size1);
		TextOut(hdc, 800, 100, s2, size2);
		EndPaint(hwnd, &ps);
		break;
	}
	case WM_DESTROY: {PostQuitMessage(0); break; }
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}
