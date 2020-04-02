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
		cout << "��������";
		gotoxy(27, 16);
		cout << "�ҷ�����";
		gotoxy(27, 19);
		cout << "�����ϱ�";

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

	RolePlaying = new Game;

	string sNewPlayer;
	gotoxy(15, 14);
	cout << "���� �̸� �Է�: ";
	cin >> sNewPlayer;

	RolePlaying->GetName(sNewPlayer);
	if (RolePlaying->LoadDefaultUserData() == false)
		return;	//���� ���� �ʱ�ȭ �������� �ؽ�Ʈ ������ ���� ��� �� ������ �������� �ʰ� ���� ȭ������ ���ư�

	if (RolePlaying->InitMonsterData() == false)
		return;	//���� ��������

	if (RolePlaying->InitWeaponData() == false)
		return;

	RolePlaying->TownMenu();

	delete RolePlaying;
}

void Menu::LoadData()
{
	int iSelect;

	RolePlaying = new Game;

	while (1)
	{
		MenuMap.BoxErase(WIDTH, HEIGHT);

		int iXPos = 19, iYPos = 4;

		for (int i = 1; i <= 10; i++)
		{
			ifstream DataCheck;	//������ ���� ����
			string sFileName = "SavePlayer" + to_string(i) + ".txt";

			DataCheck.open(sFileName);

			gotoxy(iXPos, iYPos);

			if (DataCheck.is_open())
				cout << i << "�� ����(���� ����: O)";
			else
				cout << i << "�� ����(���� ����: X)";

			iYPos += 2;

			DataCheck.close();
		}

		gotoxy(26, iYPos);
		cout << "���ư���";

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
			ifstream DataCheck;	//������ ���� ����
			string sFileName = "SavePlayer" + to_string(iSelect) + ".txt";
			DataCheck.open(sFileName);
			if (DataCheck.is_open())
			{
				if (RolePlaying->LoadUserData(iSelect) == false)
					return;	//���� ���� �ʱ�ȭ �������� �ؽ�Ʈ ������ ���� ��� �� ������ �������� �ʰ� ���� ȭ������ ���ư�

				if (RolePlaying->InitMonsterData() == false)
					return;	//���� ��������

				if (RolePlaying->InitWeaponData() == false)
					return;

				gotoxy(17, 15);
				YELLOW
				cout << "����� ������ �ҷ����� ����";
				ORIGINAL

					Sleep(1000);

				RolePlaying->TownMenu();

				return;
			}
			else
			{
				MenuMap.BoxErase(WIDTH, HEIGHT);

				gotoxy(14, 15);
				YELLOW
				cout << "�ش� ���Կ� ����� �����Ͱ� �����ϴ�.";
				ORIGINAL

				system("pause>null");
			}
			break;
		}
		case 11:
			return;
		}
	}

	delete RolePlaying;
}


Menu::~Menu()
{
}
