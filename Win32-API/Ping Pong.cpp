#include<windows.h>
#include<iostream>
#include<string.h>
#include<math.h>
using namespace std;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);


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

	hwnd = CreateWindow(AppName, TEXT("Wheel!!!"), WS_OVERLAPPEDWINDOW,100,100,1030,550,NULL,NULL,hInstance,NULL);
	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	RECT UpBoard =  {10,10, 1000, 500};
	RECT DownBoard = { 30,30, 980, 480 };
	RECT LeftBoard = { 30,225, 40, 300};
	RECT RightBoard = { 970,225, 980, 300 };
	HBRUSH Maroon = (HBRUSH)CreateSolidBrush(RGB(128, 0, 0));
	HBRUSH Green = (HBRUSH)CreateSolidBrush(RGB(0,255,0));
	HBRUSH Blue = (HBRUSH)CreateSolidBrush(RGB(0, 0, 255));
	HPEN pwhite = (HPEN)CreatePen(PS_SOLID,1,RGB(255, 255, 255));
	switch (message)
	{
	case WM_CREATE:break;
	case WM_PAINT: {
		hdc = BeginPaint(hwnd, &ps);
		FillRect(hdc, &UpBoard, Maroon);
		FillRect(hdc, &DownBoard, Green);
		FillRect(hdc, &LeftBoard, Blue);
		FillRect(hdc, &RightBoard, Blue);
		SelectObject(hdc, pwhite);
		SelectObject(hdc, Green );
		Ellipse(hdc, (DownBoard.right + DownBoard.left) / 2 - 50, (DownBoard.top + DownBoard.bottom) / 2 - 50,(DownBoard.right + DownBoard.left) / 2 + 50, (DownBoard.top + DownBoard.bottom) / 2 + 50 );
		EndPaint(hwnd, &ps);
		break;
	}
	case WM_DESTROY: {PostQuitMessage(0); break; }
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}
