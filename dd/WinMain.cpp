#include<windows.h>
#include <cmath>
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("TextOut");

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPervlnstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = lpszClass;
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW, 50, 20, 1800, 1000, NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);

	while (GetMessage(&Message, NULL, 0, 0))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return (int)Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	switch (iMessage)
	{
	case WM_PAINT:
	{
		hdc = BeginPaint(hWnd, &ps);

		SetTextAlign(hdc, TA_LEFT);
		TextOut(hdc, 10, 10, TEXT("No.1"), sizeof("No.1") - 1);

		MoveToEx(hdc, 160, 50, NULL);
		LineTo(hdc, 120, 100);

		MoveToEx(hdc, 187, 45, NULL);
		LineTo(hdc, 147, 95);

		MoveToEx(hdc, 195, 65, NULL);
		LineTo(hdc, 155, 115);

		Ellipse(hdc, 110, 110, 150, 150);

		TextOut(hdc, 165, 125, TEXT("메테오~"), sizeof("메테오~") - 1);

		/////////////////////////////////////////////////////////////////////////////
		TextOut(hdc, 10, 170, TEXT("No.2"), sizeof("No.2") - 1);

		//반지름은 40
		double X, Y;	//각각 x, y 좌표
		int Radius = 40;	//반지름

		int XCentre = 80;	//중심 X좌표
		int YCentre = 230;	//중심 Y좌표

		SetPixel(hdc, XCentre, YCentre, RGB(0, 0, 0));

		//점은 5도 단위로 찍는다
		for (int Angle = 0; Angle <= 360; Angle += 5)
		{
			X = cos(Angle) * Radius;
			Y = sin(Angle) * Radius;

			SetPixel(hdc, XCentre + X, YCentre + Y, RGB(0, 0, 0));
		}

		/////////////////////////////////////////////////////////////////////////////
		TextOut(hdc, 10, 280, TEXT("No.3"), sizeof("No.3") - 1);

		//장축 40 단축 20

		XCentre = 80;	//중심 X좌표
		YCentre = 330;	//중심 Y좌표

		SetPixel(hdc, XCentre, YCentre, RGB(0, 0, 0));

		//점은 5도 단위로 찍는다
		for (int Angle = 0; Angle <= 360; Angle += 5)
		{
			X = cos(Angle) * Radius;
			Y = (sin(Angle) * Radius) / 2;

			SetPixel(hdc, XCentre + X, YCentre + Y, RGB(0, 0, 0));
		}

		MoveToEx(hdc, 0, 700, NULL);
		LineTo(hdc, 300, 700);	//X축
		
		MoveToEx(hdc, 150, 550, NULL);
		LineTo(hdc, 150, 850);	//Y축

		XCentre = 150;	//중심 X좌표
		YCentre = 700;	//중심 Y좌표

		SetPixel(hdc, XCentre, YCentre, RGB(0, 0, 0));

		//↓삼각함수 버전-파란색
		for (double i = Radius; i >= 0; i -= 0.5)
		{
			for (int Angle = 0; Angle <= 360; Angle++)
			{
				X = cos(Angle) * i;
				Y = (sin(Angle) * i);

				SetPixel(hdc, XCentre + X, YCentre + Y, RGB(0, 0, 255));
			}
		}

		Radius = 30;	//↓원의 방정식 버전-흰색

		for (double i = Radius; i >= 0; i -= 0.02)
		{
			for (Y = 35; Y >= -35; Y -= 1)
			{
				X = sqrt(pow(i, 2) - pow(Y, 2));

				SetPixel(hdc, XCentre + X, YCentre + Y, RGB(255, 255, 255));
				SetPixel(hdc, XCentre - X, YCentre + Y, RGB(255, 255, 255));
			}
		}
	}
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_LBUTTONDOWN:
		hdc = GetDC(hWnd);

		ReleaseDC(hWnd, hdc);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}

/*
원의 넓이 구해서 어케 하는 거지,,,
일단 원의 넓이 공식
S = R ^ 2 * (대충 파이라는 기호)
파이는 3.14로 뭉뚱그리자
원의 정의 이용하랫는데
원의 정의: 중심에서 거리가 같은 무수한 점들의 집합
(덤)타원의 정의: 두 정점에서 거리가 같은 무수한 점들의 집합

좌표평면 위에서 두 점간의 거리 공식,,, (a, b), (c, d)라고 쳤을 떄
(a-c)^2 + (b-d)^2 = i^2
(a, b)가 원점잉라면?? c^2 + d^2 = i^2
c^2 = i^2 - d^2
c = sqrt(i^2 - d^2)

근데 이거랑 원의 넓이랑 무슨 상관이 잇음
*/
