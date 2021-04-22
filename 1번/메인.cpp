#include <windows.h>
#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <ctime>
#include "BitMapManager.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("C6No1");

/////////////////////////////////////////////////////////////////////

struct CardInformation
{
	bool IsRevealed;	//false�̸� ī�尡 �������� �ִ� ����
	int CardNumbering;	//ī�� �׸� �ѹ���
	int XLocation;
	int YLocation;
};


/////////////////////////////////////////////////////////////////////

void InitCardOrder(std::vector<CardInformation> *CardVector);
void PrintCards(HDC* hdc, BitMapManager NewBitMapManager, std::vector<CardInformation> CardVector);

/////////////////////////////////////////////////////////////////////

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPervlnstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;

	srand(unsigned(time(NULL)));

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

	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, (HMENU)NULL, hInstance, NULL);
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
	static HDC hdc, MemDC;
	static PAINTSTRUCT ps;
	static BitMapManager NewBitMapManager(hdc, g_hInst);
	static std::vector <CardInformation> CardVector = std::vector <CardInformation> ();
	static int NumberOfRevealed = 0;

	switch (iMessage)
	{
	case WM_CREATE:
		//���� ���۽� �ʿ��� �̹����� ���� �ε��ص�
		NewBitMapManager.LoadNewImage("Blank");	//ī�� �޸���
		NewBitMapManager.LoadNewImage("00");
		NewBitMapManager.LoadNewImage("01");
		NewBitMapManager.LoadNewImage("02");
		NewBitMapManager.LoadNewImage("03");
		NewBitMapManager.LoadNewImage("04");

		InitCardOrder(&CardVector);	//ī�� ������ ������ ���� �ʱ�ȭ
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		NewBitMapManager.PrintBitMap(hdc, 0, CARD_LOCATION_FIRST_X, CARD_LOCATION_FIRST_Y);
		NewBitMapManager.PrintBitMap(hdc, 1, CARD_LOCATION_SIXTH_X, CARD_LOCATION_SIXTH_Y);

		NewBitMapManager.PrintBitMap(hdc, 2, 50, 450);
		NewBitMapManager.PrintBitMap(hdc, 3, 350, 450);
		NewBitMapManager.PrintBitMap(hdc, 4, 450, 450);
		NewBitMapManager.PrintBitMap(hdc, 5, 550, 450);

		NewBitMapManager.PrintBitMap(hdc, CardVector[1].CardNumbering, CardVector[1].XLocation, CardVector[1].YLocation);
		NewBitMapManager.PrintBitMap(hdc, CardVector[2].CardNumbering, CardVector[2].XLocation, CardVector[2].YLocation);
		NewBitMapManager.PrintBitMap(hdc, CardVector[3].CardNumbering, CardVector[3].XLocation, CardVector[3].YLocation);
		NewBitMapManager.PrintBitMap(hdc, CardVector[4].CardNumbering, CardVector[4].XLocation, CardVector[4].YLocation);
		
		{
			for (int i = 0; i < 10; i++)
			{
				if (CardVector[i].IsRevealed == false)
				{
					NewBitMapManager.PrintBitMap(hdc, 0, CardVector[i].XLocation, CardVector[i].YLocation);
				}
				else
				{
					NewBitMapManager.PrintBitMap(hdc, CardVector[i].CardNumbering, CardVector[i].XLocation, CardVector[i].YLocation);
				}
			}
		}

		EndPaint(hWnd, &ps);
		return 0;
	case WM_LBUTTONDOWN:

		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}

void InitCardOrder(std::vector<CardInformation> *CardVector)
{
	//���⼭ ī�� ���ڸ� 2���� �������� ���Ϳ� �ִ� �Լ��� ¥�� �Ѵ�....
	//ī�� �׸� �ѹ����� © �Ӹ��� �ƴ϶� IsRevealed�� false�� �ʱ�ȭ
	//���ڸ� �������� �ִ� �� �����ϴ� ���� ��� ������ © ���ΰ�

	int NumberingOne = 0, NumberingTwo = 0, NumberingThree = 0, NumberingFour = 0, NumberingFive = 0;

	int i = 0;
	
	for (int i = 0; i < 10; i++)
	{
		CardInformation NewCardInformation;
		NewCardInformation.IsRevealed = false;

		while (1)
		{
			int RandomNumber = rand() % 5;

			if (RandomNumber == 0)
			{
				if (NumberingOne != 2)
				{
					NewCardInformation.CardNumbering = RandomNumber + 1;
					NumberingOne++;

					break;
				}
			}
			else if (RandomNumber == 1)
			{
				if (NumberingTwo != 2)
				{
					NewCardInformation.CardNumbering = RandomNumber + 1;
					NumberingTwo++;

					break;
				}
			}
			else if (RandomNumber == 2)
			{
				if (NumberingThree != 2)
				{
					NewCardInformation.CardNumbering = RandomNumber + 1;
					NumberingThree++;

					break;
				}
			}
			else if (RandomNumber == 3)
			{
				if (NumberingFour != 2)
				{
					NewCardInformation.CardNumbering = RandomNumber + 1;
					NumberingFour++;

					break;
				}
			}
			else if (RandomNumber == 4)
			{
				if (NumberingFive != 2)
				{
					NewCardInformation.CardNumbering = RandomNumber + 1;
					NumberingFive++;

					break;
				}
			}
		}

		switch (i)
		{
		case 0:
			NewCardInformation.XLocation = CARD_LOCATION_FIRST_X;
			NewCardInformation.YLocation = CARD_LOCATION_FIRST_Y;
			break;
		case 1:
			NewCardInformation.XLocation = CARD_LOCATION_SECOND_X;
			NewCardInformation.YLocation = CARD_LOCATION_SECOND_Y;
			break;
		case 2:
			NewCardInformation.XLocation = CARD_LOCATION_THIRD_X;
			NewCardInformation.YLocation = CARD_LOCATION_THIRD_Y;
			break;
		case 3:
			NewCardInformation.XLocation = CARD_LOCATION_FOURTH_X;
			NewCardInformation.YLocation = CARD_LOCATION_FOURTH_Y;
			break;
		case 4:
			NewCardInformation.XLocation = CARD_LOCATION_FIFTH_X;
			NewCardInformation.YLocation = CARD_LOCATION_FIFTH_Y;
			break;
		case 5:
			NewCardInformation.XLocation = CARD_LOCATION_SIXTH_X;
			NewCardInformation.YLocation = CARD_LOCATION_SIXTH_Y;
			break;
		case 6:
			NewCardInformation.XLocation = CARD_LOCATION_SEVENTH_X;
			NewCardInformation.YLocation = CARD_LOCATION_SEVENTH_Y;
			break;
		case 7:
			NewCardInformation.XLocation = CARD_LOCATION_EIGHTH_X;
			NewCardInformation.YLocation = CARD_LOCATION_EIGHTH_Y;
			break;
		case 8:
			NewCardInformation.XLocation = CARD_LOCATION_NINETH_X;
			NewCardInformation.YLocation = CARD_LOCATION_NINETH_Y;
			break;
		case 9:
			NewCardInformation.XLocation = CARD_LOCATION_TENTH_X;
			NewCardInformation.YLocation = CARD_LOCATION_TENTH_Y;
			break;
		}

		CardVector->push_back(NewCardInformation);
	}
}

void PrintCards(HDC* hdc, BitMapManager NewBitMapManager, std::vector<CardInformation> CardVector)
{
	for (int i = 0; i < 10; i++)
	{
		if (CardVector[i].IsRevealed == false)
		{
			NewBitMapManager.PrintBitMap(*hdc, 0, CardVector[i].XLocation, CardVector[i].YLocation);
		}
		else
		{
			NewBitMapManager.PrintBitMap(*hdc, CardVector[i].CardNumbering, CardVector[i].XLocation, CardVector[i].YLocation);
		}
	}
}

/*
�����غ��ϱ� ���� �׸����� ���� �Ǻ���
��Ʈ�� �̸��̶� �����ص־� �ϳ� ��� ������???????
����ü �Ἥ �ѹ��� �����صα�??????????

���ϰ� ���� ���� ����ȭ �ʼ�
*/

/*
����ü �迭�� ����
����ü �ȿ� ������������ �ƴ���, ī�尡 ���� �ִ� �ѹ����� �޾Ƶδ� �� ���� ��
����ü �������
bool IsRevealed = false �� ��� ���������ִ� ��
int CardNumbering = 0���� 4����
int �ƹ�ư ��ǥ<-����� �� ���ϰ� ����ü �ȿ��ٰ� ��ǥ�� �ھƳִ� �� ���� ��

*/

/*
������ ī�带 Ŭ������ �� ��ǥ ���� �� Ư�� ī�带 Ŭ���ߴٰ� ġ��
IsRealved�� ��� true�� �ٲپ �׸��� Ȱ��ȭ ��Ų��
¦�� ���� ��� true ����, �ƴ� ��� �ٽ� false

��ǥ �����ؼ� �´��� �ƴ��� ������ ��� ¥�� ����ȭ�� �ɱ�

*/

/*
��� ��: static ���͸� ���� �ҽ��� �Լ��� �Ű������� �Ἥ ���� �����ϰ� ������ �����ͷ� �Ѱܶ�
���͸� �׷� �� �ƴ϶� �� �׷�����...
*/