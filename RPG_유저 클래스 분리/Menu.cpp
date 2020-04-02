#include "Menu.h"



Menu::Menu()
{
}

void Menu::PrintMainMenu()
{
	MenuMap.BoxDraw(0, 0, WIDTH, HEIGHT);
	

	int iSelect;

	while (1)
	{
		MenuMap.BoxErase(WIDTH, HEIGHT);

		GOLD
			gotoxy(29, 10);
		cout << "RPG";
		ORIGINAL

			gotoxy(27, 13);
		cout << "새　게임";
		gotoxy(27, 16);
		cout << "불러오기";
		gotoxy(27, 19);
		cout << "종료하기";

		iSelect = MenuMap.MenuSelectCursor(3, 3, 11, 13);

		switch (iSelect)
		{
		case 1:
			NewGame();
			break;
		case 2:
			LoadData();
			break;
		case 3:
			return;
		}
	}
}

void Menu::NewGame()
{
	MenuMap.BoxErase(WIDTH, HEIGHT);

	string sNewPlayer;
	gotoxy(15, 14);
	cout << "유저 이름 입력: ";
	cin >> sNewPlayer;

	RolePlaying.GetName(sNewPlayer);
	if (RolePlaying.LoadDefaultUserData() == false)
		return;	//유저 정보 초기화 과정에서 텍스트 파일이 없을 경우 새 게임을 진행하지 않고 메인 화면으로 돌아감

	if (RolePlaying.InitMonsterData() == false)
		return;	//위와 마찬가지

	if (RolePlaying.InitWeaponData() == false)
		return;

	RolePlaying.TownMenu();
}

void Menu::LoadData()
{
	int iSelect;

	while (1)
	{
		MenuMap.BoxErase(WIDTH, HEIGHT);

		int iXPos = 19, iYPos = 4;

		for (int i = 1; i <= 10; i++)
		{
			ifstream DataCheck;	//슬롯의 공란 여부
			string sFileName = "SavePlayer" + to_string(i) + ".txt";

			DataCheck.open(sFileName);

			gotoxy(iXPos, iYPos);

			if (DataCheck.is_open())
				cout << i << "번 슬롯(파일 여부: O)";
			else
				cout << i << "번 슬롯(파일 여부: X)";

			iYPos += 2;

			DataCheck.close();
		}

		gotoxy(26, iYPos);
		cout << "돌아간다";

		iSelect = MenuMap.MenuSelectCursor(11, 2, 7, 4);

		switch (iSelect)
		{
		default:
			break;
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
		case 8:
		case 9:
		case 10:
		{
			MenuMap.BoxErase(WIDTH, HEIGHT);
			ifstream DataCheck;	//슬롯의 공란 여부
			string sFileName = "SavePlayer" + to_string(iSelect) + ".txt";
			DataCheck.open(sFileName);
			if (DataCheck.is_open())
			{
				if (RolePlaying.LoadUserData(iSelect) == false)
					return;	//유저 정보 초기화 과정에서 텍스트 파일이 없을 경우 새 게임을 진행하지 않고 메인 화면으로 돌아감

				if (RolePlaying.InitMonsterData() == false)
					return;	//위와 마찬가지

				if (RolePlaying.InitWeaponData() == false)
					return;

				gotoxy(17, 15);
				YELLOW
				cout << "저장된 데이터 불러오기 성공";
				ORIGINAL

					Sleep(1000);

				RolePlaying.TownMenu();

				return;
			}
			else
			{
				MenuMap.BoxErase(WIDTH, HEIGHT);

				gotoxy(14, 15);
				YELLOW
				cout << "해당 슬롯에 저장된 데이터가 없습니다.";
				ORIGINAL

				system("pause>null");
			}
			break;
		}
		case 11:
			return;
		}
	}
}


Menu::~Menu()
{
}
