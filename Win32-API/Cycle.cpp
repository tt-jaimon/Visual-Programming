#include<Windows.h>
#include<iostream>
#include<math.h>
using namespace std;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
int xint = 200;
int yint = 400;
RECT client_rect;

POINT rect[4][2] = { //////////////Wheel 1//////////////////////////
						{ xint,yint,xint,yint + 40 },
						{ xint,yint,xint,yint - 40 },
						{ xint,yint,xint + 40,yint },
						{ xint,yint,xint - 40,yint }
					};
POINT c = { xint,yint };//wheel 1 Center
int xint2 = 350;
int yint2 = 400;
POINT rect2[4][2] = { ////////////////Wheel 2/////////////////////////
						{ xint2,yint2,xint2,yint2 + 40 },
						{ xint2,yint2,xint2,yint2 - 40 },
						{ xint2,yint2,xint2 + 40,yint2 },
						{ xint2,yint2,xint2 - 40,yint2 }
					};
POINT c2 = { xint2,yint2 };//Wheel 2 center
int bxint = xint - 50;
int bx2int = xint2;
int byint = yint - 70;
int by2int = yint2 - 70;
POINT BIKE[2] = { bxint,byint,bx2int,by2int };
int b2xint = xint - 50;
int b2x2int = xint;
int b2yint = yint - 80;
int b2y2int = yint2 - 80;
POINT BIKE2[2] = { b2xint,b2yint,b2x2int,b2y2int };
int b3xint = xint2 - 50;
int b3x2int = xint2;
int b3yint = yint - 90;
int b3y2int = yint2 - 90;
POINT BIKE3[2] = { b3xint,b3yint,b3x2int,b3y2int };
int b4xint = xint2 - 30;
int b4x2int = xint2;
int b4yint = yint - 95;
int b4y2int = yint2 - 95;
POINT BIKE4[2] = { b4xint,b4yint,b4x2int,b4y2int };
int b5xint = xint2;
int b5x2int = xint2;
int b5yint = yint - 95;
int b5y2int = yint2 - 70;
POINT BIKE5[2] = { b5xint,b5yint,b5x2int,b5y2int };
RECT r;
int k = 0;
int k2 = 0;
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
	MSG msg;
	WNDCLASS wndclass;
	HWND hwnd;

	static TCHAR AppName[] = TEXT("Cycle");

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
		MessageBox(NULL, TEXT("Sorry unable to register the class!!!"), AppName, MB_ICONERROR);
		return 0;
	}

	hwnd = CreateWindow(AppName, TEXT("Cycle!!!"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);
	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}
void Anti_PointRotate(POINT p[4][2], POINT c, float angle)
{
	POINT pTemp;
	for (int i = 0; i<4; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			pTemp.x = (c.x + (p[i][j].x - c.x)*cos((angle*3.14) / 180) - (p[i][j].y - c.y)*sin((angle*3.14) / 180));
			pTemp.y = (c.y + (p[i][j].x - c.x)*sin((angle*3.14) / 180) + (p[i][j].y - c.y)*cos((angle*3.14) / 180));
			p[i][j] = pTemp;
		}
	}
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	HBRUSH bRed = CreateSolidBrush(RGB(255, 0, 0));
	HBRUSH bWhite = CreateSolidBrush(RGB(255, 255, 255));
	HPEN pBikeRed = CreatePen(PS_SOLID, 10, RGB(255, 0, 0));
	HPEN pBikeWhite = CreatePen(PS_SOLID, 10, RGB(255, 255, 255));
	HPEN pWheelBlack = CreatePen(PS_SOLID, 7, RGB(0, 0, 0));
	HPEN pWheelWhite = CreatePen(PS_SOLID, 15, RGB(255, 255, 255));
	HPEN pRed = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	HPEN pBlack = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	HPEN pWhite = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));


	switch (message)
	{
	case WM_CREATE: 	break;
	case WM_MOUSEMOVE: {
		hdc = GetDC(hwnd);
		TCHAR s[20];
		int x = LOWORD(lParam);
		int y = HIWORD(lParam);
		int size = wsprintf(s, TEXT("x:%i,y:%i"), x, y);
		GetClientRect(hwnd, &client_rect);
		TextOut(hdc, client_rect.right+20, 0, s, size);
		ReleaseDC(hwnd, hdc);
		break;
	}
	case WM_KEYDOWN: {
		hdc = GetDC(hwnd);
		GetClientRect(hwnd, &client_rect);
		FillRect(hdc, &client_rect, bWhite);
		TextOut(hdc, 0, 0, TEXT("Help"), 4);
		TextOut(hdc, 0, 15, TEXT("--------"), 8);
		TextOut(hdc, 0, 25, TEXT("Up Arrow      - Move Front Wheel Up"), 35);
		TextOut(hdc, 0, 40, TEXT("Down Arrow - Move Front Wheel Down"), 35);
		TextOut(hdc, 0, 55, TEXT("Left Arrow    - Move Left"), 25);
		TextOut(hdc, 0, 70, TEXT("Right Arrow - Move Right"), 24);
		if (LOWORD(wParam) == 39)//Right Arrow
		{
			//////////////////Cycle Body///////////////////////
			BIKE[0].x++;
			BIKE[1].x++;
			BIKE2[0].x++;
			BIKE2[1].x++;
			BIKE3[0].x++;
			BIKE3[1].x++;
			BIKE4[0].x++;
			BIKE4[1].x++;
			BIKE5[0].x++;
			BIKE5[1].x++;
			SelectObject(hdc, pBikeRed);
			Polyline(hdc, BIKE, 2);
			Polyline(hdc, BIKE2, 2);
			Polyline(hdc, BIKE3, 2);
			Polyline(hdc, BIKE4, 2);
			Polyline(hdc, BIKE5, 2);			
			/////////////////Wheel 1 //////////////
			k++;
			c.x++;
			Anti_PointRotate(rect, c, 30);
			SelectObject(hdc, pWheelBlack);
			SelectObject(hdc, bWhite);
			Ellipse(hdc, xint - 50 + k, yint - 50, xint + 50 + k, yint + 50);
			SelectObject(hdc, pWhite);
			SelectObject(hdc, bRed);
			Ellipse(hdc, xint - 40 + k, yint - 40, xint + 40 + k, yint + 40);
			SelectObject(hdc, pBlack);
			Polyline(hdc, rect[0], 2);
			Polyline(hdc, rect[1], 2);
			Polyline(hdc, rect[2], 2);
			Polyline(hdc, rect[3], 2);
			////////////////// Wheel 2///////////////
			c2.x++;
			Anti_PointRotate(rect2, c2, 30);
			SelectObject(hdc, pWheelBlack);
			SelectObject(hdc, bWhite);
			Ellipse(hdc, xint2 - 50 + k, yint2 - 50 - k2, xint2 + 50 + k, yint2 + 50 - k2);
			SelectObject(hdc, pWhite);
			SelectObject(hdc, bRed);
			Ellipse(hdc, xint2 - 40 + k, yint2 - 40 - k2, xint2 + 40 + k, yint2 + 40 - k2);
			SelectObject(hdc, pBlack);
			Polyline(hdc, rect2[0], 2);
			Polyline(hdc, rect2[1], 2);
			Polyline(hdc, rect2[2], 2);
			Polyline(hdc, rect2[3], 2);
		}
		if (LOWORD(wParam) == 37)//Left Arrow
		{
			////////////////////Cycle Body////////////////
			BIKE[0].x--;
			BIKE[1].x--;
			BIKE2[0].x--;
			BIKE2[1].x--;
			BIKE3[0].x--;
			BIKE3[1].x--;
			BIKE4[0].x--;
			BIKE4[1].x--;
			BIKE5[0].x--;
			BIKE5[1].x--;
			SelectObject(hdc, pBikeRed);
			Polyline(hdc, BIKE, 2);
			Polyline(hdc, BIKE2, 2);
			Polyline(hdc, BIKE3, 2);
			Polyline(hdc, BIKE4, 2);
			Polyline(hdc, BIKE5, 2);
			/////////////// Wheel 1 ///////////////////
			k--;
			c.x--;
			Anti_PointRotate(rect, c, 30);
			SelectObject(hdc, pWheelBlack);
			SelectObject(hdc, bWhite);
			Ellipse(hdc, xint - 50 + k, yint - 50, xint + 50 + k, yint + 50);
			SelectObject(hdc, pWhite);
			SelectObject(hdc, bRed);
			Ellipse(hdc, xint - 40 + k, yint - 40, xint + 40 + k, yint + 40);
			SelectObject(hdc, pBlack);
			Polyline(hdc, rect[0], 2);
			Polyline(hdc, rect[1], 2);
			Polyline(hdc, rect[2], 2);
			Polyline(hdc, rect[3], 2);
			/////////////// Wheel 2 ///////////////
			c2.x--;
			Anti_PointRotate(rect2, c2, 30);
			SelectObject(hdc, pWheelBlack);
			SelectObject(hdc, bWhite);
			Ellipse(hdc, xint2 - 50 + k, yint2 - 50 - k2, xint2 + 50 + k, yint2 + 50 - k2);
			SelectObject(hdc, pWhite);
			SelectObject(hdc, bRed);
			Ellipse(hdc, xint2 - 40 + k, yint2 - 40 - k2, xint2 + 40 + k, yint2 + 40 - k2);
			SelectObject(hdc, pBlack);
			Polyline(hdc, rect2[0], 2);
			Polyline(hdc, rect2[1], 2);
			Polyline(hdc, rect2[2], 2);
			Polyline(hdc, rect2[3], 2);
		}
		if (LOWORD(wParam) == 38)//Up Arrow 
		{
			/////////////////Cycle Body///////////////////
			BIKE[1].y--;
			BIKE2[1].y--;
			BIKE2[0].y--;
			BIKE3[1].y--;
			BIKE3[0].y--;
			BIKE4[1].y--;
			BIKE4[0].y--;
			BIKE5[1].y--;
			BIKE5[0].y--;
			SelectObject(hdc, pBikeRed);
			Polyline(hdc, BIKE, 2);
			Polyline(hdc, BIKE2, 2);
			Polyline(hdc, BIKE3, 2);
			Polyline(hdc, BIKE4, 2);
			Polyline(hdc, BIKE5, 2);
			/////////////// Wheels 1 & 2 ////////////////
			k2++;
			c2.y--;
			Anti_PointRotate(rect2, c2, 30);
			SelectObject(hdc, pWheelBlack);
			SelectObject(hdc, bWhite);
			Ellipse(hdc, xint2 - 50 + k, yint2 - 50 - k2, xint2 + 50 + k, yint2 + 50 - k2);
			Ellipse(hdc, xint - 50 + k, yint - 50, xint + 50 + k, yint + 50);
			SelectObject(hdc, pWhite);
			SelectObject(hdc, bRed);
			Ellipse(hdc, xint2 - 40 + k, yint2 - 40 - k2, xint2 + 40 + k, yint2 + 40 - k2);
			Ellipse(hdc, xint - 40 + k, yint - 40, xint + 40 + k, yint + 40);
			SelectObject(hdc, pBlack);
			Polyline(hdc, rect2[0], 2);
			Polyline(hdc, rect2[1], 2);
			Polyline(hdc, rect2[2], 2);
			Polyline(hdc, rect2[3], 2);
			Polyline(hdc, rect[0], 2);
			Polyline(hdc, rect[1], 2);
			Polyline(hdc, rect[2], 2);
			Polyline(hdc, rect[3], 2);
		}
		if (LOWORD(wParam) == 40)//Down Arrow
		{
			/////////////////Cycle Body//////////////////////
			BIKE[1].y++;
			BIKE2[1].y++;
			BIKE2[0].y++;
			BIKE3[1].y++;
			BIKE3[0].y++;
			BIKE4[1].y++;
			BIKE4[0].y++;
			BIKE5[1].y++;
			BIKE5[0].y++;
			SelectObject(hdc, pBikeRed);
			Polyline(hdc, BIKE, 2);
			Polyline(hdc, BIKE2, 2);
			Polyline(hdc, BIKE3, 2);
			Polyline(hdc, BIKE4, 2);
			Polyline(hdc, BIKE5, 2);
			/////////////// Wheels 1 & 2 ////////////////
			k2--;
			c2.y++;
			Anti_PointRotate(rect2, c2, 30);
			SelectObject(hdc, pWheelBlack);
			SelectObject(hdc, bWhite);
			Ellipse(hdc, xint2 - 50 + k, yint2 - 50 - k2, xint2 + 50 + k, yint2 + 50 - k2);
			Ellipse(hdc, xint - 50 + k, yint - 50, xint + 50 + k, yint + 50);
			SelectObject(hdc, pWhite);
			SelectObject(hdc, bRed);
			Ellipse(hdc, xint2 - 40 + k, yint2 - 40 - k2, xint2 + 40 + k, yint2 + 40 - k2);
			Ellipse(hdc, xint - 40 + k, yint - 40, xint + 40 + k, yint + 40);
			SelectObject(hdc, pBlack);
			Polyline(hdc, rect2[0], 2);
			Polyline(hdc, rect2[1], 2);
			Polyline(hdc, rect2[2], 2);
			Polyline(hdc, rect2[3], 2);
			Polyline(hdc, rect[0], 2);
			Polyline(hdc, rect[1], 2);
			Polyline(hdc, rect[2], 2);
			Polyline(hdc, rect[3], 2);
		}
		ReleaseDC(hwnd, hdc);
		break;
	}
	case WM_PAINT: {
						hdc = BeginPaint(hwnd, &ps);
						///////////////Cycle Body////////////////////
						GetClientRect(hwnd, &client_rect);
						FillRect(hdc, &client_rect, bWhite);
						TextOut(hdc, 0, 0,TEXT("Help"), 4);
						TextOut(hdc, 0,15,TEXT("--------"),8 );
						TextOut(hdc, 0,25,TEXT("Up Arrow      - Move Front Wheel Up"), 35);
						TextOut(hdc, 0,40,TEXT("Down Arrow - Move Front Wheel Down"), 35);
						TextOut(hdc, 0,55,TEXT("Left Arrow    - Move Left"), 25);
						TextOut(hdc, 0,70,TEXT("Right Arrow - Move Right"), 24);
						SelectObject(hdc, pBikeRed);
						Polyline(hdc, BIKE, 2);
						Polyline(hdc, BIKE2, 2);
						Polyline(hdc, BIKE3, 2);
						Polyline(hdc, BIKE4, 2);
						Polyline(hdc, BIKE5, 2);
						///////////////// Wheel's 1 & 2 //////////////
						Anti_PointRotate(rect2, c2, 30);
						SelectObject(hdc, pWheelBlack);
						SelectObject(hdc, bWhite);
						Ellipse(hdc, xint2 - 50 + k, yint2 - 50 - k2, xint2 + 50 + k, yint2 + 50 - k2);
						Ellipse(hdc, xint - 50 + k, yint - 50, xint + 50 + k, yint + 50);
						SelectObject(hdc, pWhite);
						SelectObject(hdc, bRed);
						Ellipse(hdc, xint2 - 40 + k, yint2 - 40 - k2, xint2 + 40 + k, yint2 + 40 - k2);
						Ellipse(hdc, xint - 40 + k, yint - 40, xint + 40 + k, yint + 40);
						SelectObject(hdc, pBlack);
						Polyline(hdc, rect2[0], 2);
						Polyline(hdc, rect2[1], 2);
						Polyline(hdc, rect2[2], 2);
						Polyline(hdc, rect2[3], 2);
						Polyline(hdc, rect[0], 2);
						Polyline(hdc, rect[1], 2);
						Polyline(hdc, rect[2], 2);
						Polyline(hdc, rect[3], 2);
						EndPaint(hwnd, &ps);
						break;
					}
	case WM_DESTROY: {
						PostQuitMessage(0);
						return 0;
					}
	}
	return DefWindowProc(hwnd, message, wParam, lParam);

}

