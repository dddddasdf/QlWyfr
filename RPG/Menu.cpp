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

	string sNewPlayer;
	gotoxy(15, 14);
	cout << "���� �̸� �Է�: ";
	cin >> sNewPlayer;

	RolePlaying.GetName(sNewPlayer);
	if (RolePlaying.InitUserData() == false)
		return;	//���� ���� �ʱ�ȭ �������� �ؽ�Ʈ ������ ���� ��� �� ������ �������� �ʰ� ���� ȭ������ ���ư�

	if (RolePlaying.InitMonsterData() == false)
		return;	//���� ��������

	if (RolePlaying.InitWeaponData() == false)
		return;

	RolePlaying.TownMenu();
}

void Menu::LoadData()
{
	MenuMap.BoxErase(WIDTH, HEIGHT);

	int iSelect;
	for (int i = 1; i <= 10; i++)
	{
		gotoxy(20, 2 + (i * 2));
		cout << "������ �׽�Ʈ�� ����" << i;
	}
	gotoxy(27, 24);
	cout << "���ư���";

	iSelect = MenuMap.MenuSelectCursor(11, 2, 8, 4);

	switch (iSelect)
	{
	default:
		cout << "��";
		break;
	case 11:
		return;
	}
}


Menu::~Menu()
{
}
