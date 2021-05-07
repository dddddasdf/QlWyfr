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

		TextOut(hdc, 165, 125, TEXT("���׿�~"), sizeof("���׿�~") - 1);

		/////////////////////////////////////////////////////////////////////////////
		TextOut(hdc, 10, 170, TEXT("No.2"), sizeof("No.2") - 1);

		//�������� 40
		double X, Y;	//���� x, y ��ǥ
		int Radius = 40;	//������

		int XCentre = 80;	//�߽� X��ǥ
		int YCentre = 230;	//�߽� Y��ǥ

		SetPixel(hdc, XCentre, YCentre, RGB(0, 0, 0));

		//���� 5�� ������ ��´�
		for (int Angle = 0; Angle <= 360; Angle += 5)
		{
			X = cos(Angle) * Radius;
			Y = sin(Angle) * Radius;

			SetPixel(hdc, XCentre + X, YCentre + Y, RGB(0, 0, 0));
		}

		/////////////////////////////////////////////////////////////////////////////
		TextOut(hdc, 10, 280, TEXT("No.3"), sizeof("No.3") - 1);

		//���� 40 ���� 20

		XCentre = 80;	//�߽� X��ǥ
		YCentre = 330;	//�߽� Y��ǥ

		SetPixel(hdc, XCentre, YCentre, RGB(0, 0, 0));

		//���� 5�� ������ ��´�
		for (int Angle = 0; Angle <= 360; Angle += 5)
		{
			X = cos(Angle) * Radius;
			Y = (sin(Angle) * Radius) / 2;

			SetPixel(hdc, XCentre + X, YCentre + Y, RGB(0, 0, 0));
		}

		MoveToEx(hdc, 0, 700, NULL);
		LineTo(hdc, 300, 700);	//X��
		
		MoveToEx(hdc, 150, 550, NULL);
		LineTo(hdc, 150, 850);	//Y��

		XCentre = 150;	//�߽� X��ǥ
		YCentre = 700;	//�߽� Y��ǥ

		SetPixel(hdc, XCentre, YCentre, RGB(0, 0, 0));

		//��ﰢ�Լ� ����-�Ķ���
		for (double i = Radius; i >= 0; i -= 0.5)
		{
			for (int Angle = 0; Angle <= 360; Angle++)
			{
				X = cos(Angle) * i;
				Y = (sin(Angle) * i);

				SetPixel(hdc, XCentre + X, YCentre + Y, RGB(0, 0, 255));
			}
		}

		Radius = 30;	//����� ������ ����-���

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
���� ���� ���ؼ� ���� �ϴ� ����,,,
�ϴ� ���� ���� ����
S = R ^ 2 * (���� ���̶�� ��ȣ)
���̴� 3.14�� ���ױ׸���
���� ���� �̿��Ϸ��µ�
���� ����: �߽ɿ��� �Ÿ��� ���� ������ ������ ����
(��)Ÿ���� ����: �� �������� �Ÿ��� ���� ������ ������ ����

��ǥ��� ������ �� ������ �Ÿ� ����,,, (a, b), (c, d)��� ���� ��
(a-c)^2 + (b-d)^2 = i^2
(a, b)�� �����׶��?? c^2 + d^2 = i^2
c^2 = i^2 - d^2
c = sqrt(i^2 - d^2)

�ٵ� �̰Ŷ� ���� ���̶� ���� ����� ����
*/
