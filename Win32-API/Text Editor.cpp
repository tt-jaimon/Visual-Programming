#include<Windows.h>
#include<iostream>
#include<math.h>
#include<string>
#include<fstream>
using namespace std;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
RECT ClientRect;
string buffer = "";
string temp = "";
int y = 0;
int x = 0;
int gap = 17;
RECT OneLine = { 0,0,500,gap };

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
	MSG msg;
	WNDCLASS wndclass;
	HWND hwnd;

	static TCHAR AppName[] = TEXT("Text Editor");

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

	hwnd = CreateWindow(AppName, TEXT("Text Editor!!!"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);
	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}
/////////// Saving into a Text File////////////////
void SaveFile()
{
	ofstream out;
	out.open("save.txt", ios::out);
	for (int i = 0; i<buffer.size(); i++)
		out << buffer[i];
	out.close();
}
//////////// Loading from a Text File////////////// 
void LoadFile()
{
	ifstream in;
	in.open("save.txt", ios::in);
	char a;
	for (int i = 0; i<buffer.size(); i++)
	{
		in >> a;
		buffer += a;
	}
	in.close();
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	HBRUSH bWhite = CreateSolidBrush(RGB(255, 255, 255));
	HBRUSH bYellow = CreateSolidBrush(RGB(255, 255, 0));
	HPEN pBlack = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));

	switch (message)
	{
	case WM_CREATE: 	break;
	case WM_CHAR: {
		hdc = GetDC(hwnd);
		if ((LOWORD(wParam) > 31 && LOWORD(wParam) < 127) || LOWORD(wParam) == 13 || LOWORD(wParam) == 8)
		{
			if (LOWORD(wParam) == 13)//Enter Key
			{
				y += gap;
				temp = "";
				x = 0;
				buffer += '\n';
			}
			else
			{
				buffer += (char)LOWORD(wParam);
				if (x > 500)
				{
					x = 0;
					y += gap;
				}
				if (LOWORD(wParam) == 8)//Backspace key
				{
					if (x > 0)
					{
						x--;
						temp.erase(temp.size() - 1);
						buffer.erase(buffer.size() - 2);
					}
					else
					{
						if (y / gap>0)
						{
							x = 0;
							y -= gap;
							buffer.erase(buffer.size() - 2);
							string rev_temp = "";
							for (int i = buffer.size() - 2; i>0; i--)
							{
								if (buffer[i] == '\n')
									break;
								rev_temp += buffer[i];
								x++;
							}
							for (int i = rev_temp.size() - 1; i >= 0; i--)
								temp += rev_temp[i];
							buffer.erase(buffer.size() - 2);
						}
					}
				}
				else
				{
					x++;
					temp += (char)LOWORD(wParam);
				}
				OneLine.top = y;
				OneLine.bottom = y + gap;
				FillRect(hdc, &OneLine, bYellow);
				TCHAR *t = new TCHAR[temp.size() + 1];
				t[temp.size()] = '\0';
				copy(temp.begin(), temp.end(), t);
				SetBkColor(hdc, RGB(255, 255, 0));
				TextOut(hdc, 0, y, t, x + 1);
			}

		}
		ReleaseDC(hwnd, hdc);
		break;
	}
	case WM_PAINT: {
		hdc = BeginPaint(hwnd, &ps);
		GetClientRect(hwnd, &ClientRect);
		FillRect(hdc, &ClientRect, bYellow);
		EndPaint(hwnd, &ps);
		break;
	}
	case WM_CLOSE: {
		int a = MessageBox(hwnd, TEXT("Do You Wish To Save your file"), TEXT("Text Editor!!!"), MB_YESNOCANCEL);
		if (a == IDYES)
			SaveFile();
		PostQuitMessage(0);
		break;
	}

	}
	return DefWindowProc(hwnd, message, wParam, lParam);

}

