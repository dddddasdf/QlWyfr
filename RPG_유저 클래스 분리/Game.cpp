#include "Game.h"
#define ROCK 1
#define SCISSORS 2
#define PAPER 3
#define OBJECT_Y 13
#define USER_ATTACK 10
#define MONSTER_ATTACK 11
#define WEAPON_OK 1
#define WEAPON_NO 0	//���� ���� ������ 1 �ƴ� 0
#define CLOSE -10	//���� ���� �� �ݱ�

//�� ������ �ý��� ���� ��ſ� �й�� ���� ����� �� HP Ǯ ȸ�� �� ��� �� ���
//�ؾ� �ϴ� ��: ���� �����͸� �ٸ� Ŭ������ �и�
//�޸� ���� ��Ҵ�

//����Ʈ ���� ���ϰ� �ʱ�ȭ �ϴ� ���� ���� �Լ� �����ؼ� ���� ���� ��

Game::Game()
{
	
}

void Game::GetName(string name)
{
	Player = new User;

	Player->ChangeName(name);
}

bool Game::LoadDefaultUserData()
{
	bool bIsOpen = Player->LoadDefaultUserData();

	return bIsOpen;
}

bool Game::InitMonsterData()
{
	//�� ���� ���ڴ� �����ϴ� ������ �� ��
	//����Ʈ �� ���� �ؽ�Ʈ ���� �о�� �� ���ڰ� �ǹ��ϴ� ����
	//���̸�, ���ݷ�, �����, ���� �ϱ� ���� ����ġ, �ִ� ����ġ, ����, �ִ� ���
	//�ڵ忡�� �߰��� ��������� �ϴ� ���� �������ġ ������ �ִ� ����ġ ��������
	
	ifstream MonsterInfoLoad;
	MonsterInfoLoad.open("DefaultMonsterInfo.txt");
	if (MonsterInfoLoad.is_open())
	{
		MonsterInfoLoad >> m_iMonsterPopulation;
		MonsterArr = new Monster[m_iMonsterPopulation];

		int j = 0;

		while (!MonsterInfoLoad.eof())
		{
			MonsterInfoLoad >> MonsterArr[j].MonsterName;
			MonsterInfoLoad >> MonsterArr[j].MonsterAttck;
			MonsterInfoLoad >> MonsterArr[j].MonsterMaxLife;
			MonsterInfoLoad >> MonsterArr[j].MonsterMaxExp;
			MonsterInfoLoad >> MonsterArr[j].MonsterDropExp;
			MonsterInfoLoad >> MonsterArr[j].MonsterLevel;
			MonsterInfoLoad >> MonsterArr[j].MonsterDropGold;
			MonsterArr[j].MonsterCurrentExp = 0;
			MonsterArr[j].MonsterCurrentLife = MonsterArr[j].MonsterMaxLife;
			j++;
		}

		return true;
	}
	else
	{
		GameMap.BoxErase(WIDTH, HEIGHT);

		RED
		gotoxy(26, 14);
		cout << "���� �߻�";
		gotoxy(7, 16);
		cout << "���� ���� �ؽ�Ʈ ������ �о�� �� �����ϴ�...";
		ORIGINAL

		system("pause>null");
		return false;	//����Ʈ ���� ������ ���� ��� �������� ǥ���ϰ� ���� ȭ������ ���ư���
	}
}

bool Game::InitWeaponData()
{
	if ((WeaponPtr->InitWeaponCount()) == false)
	{
		GameMap.BoxErase(WIDTH, HEIGHT);

		RED
		gotoxy(26, 14);
		cout << "���� �߻�";
		gotoxy(8, 16);
		cout << "���� ���� �ؽ�Ʈ ������ �о�� �� �����ϴ�...";
		ORIGINAL

		system("pause>null");

		return false;
	}
	else
	{
		//���������� ������ �о��ٸ� �� ���� ������ ����� ī��Ʈ �Ǿ�����
		//�۵� ����: ���� �迭 ���� �Լ�->���� �迭�� ���� ������ �Ű� ������ �־ ������ �Է�
		//SwordPtr->CreateSwordArr();
		BowPtr->CreateBowArr();
		DaggerPtr->CreateDaggerArr();
		GunPtr->CreateGunArr();
		WandPtr->CreateWandArr();
		HammerPtr->CreateHammerArr();

		ifstream WeaponLoad;
		WeaponLoad.open("WeaponList.txt");
		if (WeaponLoad.is_open())
		{
			string sWeaponType;
			string sWeaponName;
			int iWeaponPrice;
			int iWeaponPower;

			while (!WeaponLoad.eof())
			{
				WeaponLoad >> sWeaponType;

				if (sWeaponType == "Sword")
				{
					WeaponLoad >> sWeaponName;
					WeaponLoad >> iWeaponPower;
					WeaponLoad >> iWeaponPrice;
					SwordPtr->InputSwordData(sWeaponName, iWeaponPrice, iWeaponPower);
				}
				else if (sWeaponType == "Bow")
				{
					WeaponLoad >> sWeaponName;
					WeaponLoad >> iWeaponPower;
					WeaponLoad >> iWeaponPrice;
					BowPtr->InputBowData(sWeaponName, iWeaponPrice, iWeaponPower);
				}
				else if (sWeaponType == "Dagger")
				{
					WeaponLoad >> sWeaponName;
					WeaponLoad >> iWeaponPower;
					WeaponLoad >> iWeaponPrice;
					DaggerPtr->InputDaggerData(sWeaponName, iWeaponPrice, iWeaponPower);
				}
				else if (sWeaponType == "Gun")
				{
					WeaponLoad >> sWeaponName;
					WeaponLoad >> iWeaponPower;
					WeaponLoad >> iWeaponPrice;
					GunPtr->InputGunData(sWeaponName, iWeaponPrice, iWeaponPower);
				}
				else if (sWeaponType == "Wand")
				{
					WeaponLoad >> sWeaponName;
					WeaponLoad >> iWeaponPower;
					WeaponLoad >> iWeaponPrice;
					WandPtr->InputWandData(sWeaponName, iWeaponPrice, iWeaponPower);
				}
				else if (sWeaponType == "Hammer")
				{
					WeaponLoad >> sWeaponName;
					WeaponLoad >> iWeaponPower;
					WeaponLoad >> iWeaponPrice;
					HammerPtr->InputHammerData(sWeaponName, iWeaponPrice, iWeaponPower);
				}
			}
		}

		return true;
	}
}

//������� ����Ʈ ���� ������ �ҷ����� ����

bool Game::LoadUserData(int DataNumber)
{
	//���� ����->���� �̸�, ���ݷ�, �ִ� �����, �����ϱ� ���� ����ġ, ����, ���, ���� ����ġ, ���� �����
	//���� ���� ���� ���� ���� ������ 1 ���� Ÿ��, ���� �̸�, ���ݷ�, ���� / ������ 0

	Player = new User;

	bool bIsOpen = Player->LoadUserData(DataNumber);

	return bIsOpen;
}

//�Ʒ����� ���� �޴� ����

void Game::TownMenu()
{
	int iSelect;
	
	while (1)
	{
		GameMap.BoxErase(WIDTH, HEIGHT);
		
		BLUE_GREEN
		gotoxy(23, 8);
		cout << "==== ���� ====";
		ORIGINAL

		gotoxy(26, 11);
		cout << "���� �Ա�";
		gotoxy(26, 13);
		cout << "���� ����";
		gotoxy(25, 15);
		cout << "���� ����";
		gotoxy(26, 17);
		cout << "���� ����";
		gotoxy(26, 19);
		cout << "�����Ѵ�";
		gotoxy(28, 21);
		cout << "����";

		iSelect = GameMap.MenuSelectCursor(6, 2, 10, 11);

		switch (iSelect)
		{
		default:
			break;
		case 1:
			DungeonList();
			break;
		case 2:
			ShowUserInfo();
			break;
		case 3:
			ShowMonsterInfo();
			break;
		case 4:
			WeaponShop();
			break;
		case 5:
			SaveMenu();
			break;
		case 6:
			DeleteInfo();
			return;
		}
	}
}

void Game::DungeonList()
{
	int iSelect;
	int iSumMenuNum = m_iMonsterPopulation + 1;

	while (1)
	{
		GameMap.BoxErase(WIDTH, HEIGHT);
		
		PUPPLE
		gotoxy(20, 7);
		cout << "=====���� �ȳ�=====";

		int i = 10;
		for (int j = 0; j < m_iMonsterPopulation; j++)
		{
			gotoxy(22, i);
			cout << (j + 1) << "��: " << MonsterArr[j].MonsterName;
			i += 2;
		}

		gotoxy(22, i);
		cout << "������ ���ư���";

		ORIGINAL

		iSelect = GameMap.MenuSelectCursor(iSumMenuNum, 2, 7, 10);

		if (iSelect == iSumMenuNum)
			return;
		else
		{
			NowBattle(iSelect - 1);
			break;
		}
	}
}

//��Ʋ ���� �Լ� ����

void Game::NowBattle(int MonsterNumber)
{
	char iGetKey = 0;	//getch()��
	int iMonsterCard;	//���� �� �´��� �����

	GameMap.BoxErase(WIDTH, HEIGHT);

	ShowUserBattle();
	ShowMonsterBattle(MonsterNumber);

	PrintObject();

	//����: A    ����: S     ��: D

	while (1)
	{
		if (iGetKey == 0)
			iGetKey = _getch();	//���� �Է�

		iMonsterCard = (rand() % 3) + 1;

		if (iGetKey == 'S' || iGetKey == 's')
		{
			if (iMonsterCard == ROCK)
				PrintMessage(OUTCOME_DRAW, MonsterNumber);
			else if (iMonsterCard == SCISSORS)
				PrintMessage(OUTCOME_WIN, MonsterNumber);
			else
				PrintMessage(OUTCOME_LOSE, MonsterNumber);

			gotoxy(24, OBJECT_Y - 1);
			cout << "����";
		}
		else if (iGetKey == 'A' || iGetKey == 'a')
		{
			if (iMonsterCard == SCISSORS)
				PrintMessage(OUTCOME_DRAW, MonsterNumber);
			else if (iMonsterCard == PAPER)
				PrintMessage(OUTCOME_WIN, MonsterNumber);
			else
				PrintMessage(OUTCOME_LOSE, MonsterNumber);

			gotoxy(24, OBJECT_Y - 1);
			cout << "����";
		}
		else if (iGetKey == 'D' || iGetKey == 'd')
		{
			if (iMonsterCard == PAPER)
				PrintMessage(OUTCOME_DRAW, MonsterNumber);
			else if (iMonsterCard == ROCK)
				PrintMessage(OUTCOME_WIN, MonsterNumber);
			else
				PrintMessage(OUTCOME_LOSE, MonsterNumber);

			gotoxy(25, OBJECT_Y - 1);
			cout << "��";
		}
		else
		{
			GameMap.BoxErase(WIDTH, HEIGHT);

			ShowUserBattle();
			ShowMonsterBattle(MonsterNumber);

			PrintObject();

			gotoxy(23, 16);
			cout << "��: ���� �� �ϳ�?";
			gotoxy(20, 17);
			cout << "���Ϳ��� �Ѵ� �¾Ҵ�...";

			Attack(MONSTER_ATTACK, MonsterNumber);
			//������ Ű �ܸ̿� �Է��ϸ� �Ѵ� ����
		}

		ShowUserBattle();
		ShowMonsterBattle(MonsterNumber);

		//�Ʒ� if���� ���Ͱ� �� �а� �������� ���
		if (iMonsterCard == ROCK)
		{
			gotoxy(34, OBJECT_Y - 1);
			cout << "����";
		}
		else if (iMonsterCard == SCISSORS)
		{
			gotoxy(34, OBJECT_Y - 1);
			cout << "����";
		}
		else
		{
			gotoxy(35, OBJECT_Y - 1);
			cout << "��";
		}

		//�¸� ���ǽ�
		if (MonsterArr[MonsterNumber].MonsterCurrentLife == 0)
		{
			BLOOD
			gotoxy(35, OBJECT_Y);
			cout << "��";
			ORIGINAL

			gotoxy(22, 17);
			cout << "�������� �¸��ߴ�.";
			system("pause>null");

			ShowResult(MonsterNumber);

			return;
		}

		//�й� ���ǽ�
		if (Player->ReturnUserInt(VARIABLE_CURRENTLIFE) == 0)
		{
			gotoxy(25, OBJECT_Y);
			BLOOD
			cout << "��";
			gotoxy(8, 17);
			cout << "�������� �й��ߴ�. ����� �� ���� ����������...";
			gotoxy(20, 18);
			cout << "���� �� �Ϻθ� ���Ѱ��.";
			ORIGINAL

			system("pause>null");

			MonsterArr[MonsterNumber].MonsterCurrentLife = MonsterArr[MonsterNumber].MonsterMaxLife;
			
			Player->ForFeitGold();
			Player->LifeReset();

			return;
		}

		iGetKey = _getch();
	}
}

void Game::PrintObject()
{
	gotoxy(25, OBJECT_Y);
	YELLOW
	cout << "��";
	ORIGINAL

	PUPPLE
	gotoxy(35, OBJECT_Y);
	cout << "��";
	ORIGINAL

	gotoxy(27, 15);
	cout << "<�ý���>";

	gotoxy(16, 19);
	cout << "����: A    ����: S     ��: D";
}

void Game::PrintMessage(int Outcome, int MonsterNumber)
{
	GameMap.BoxErase(WIDTH, HEIGHT);

	PrintObject();

	switch (Outcome)
	{
	case OUTCOME_DRAW:
		gotoxy(28, 16);
		cout << "����";
		break;
	case OUTCOME_LOSE:
		gotoxy(24, 16);
		cout << "������ �¸�";
		Attack(MONSTER_ATTACK, MonsterNumber);
		break;
	case OUTCOME_WIN:
		gotoxy(25, 16);
		cout << "����� �¸�";
		Attack(USER_ATTACK, MonsterNumber);
		break;
	}
}

void Game::Attack(int Attacker, int MonsterNumber)
{
	if (Attacker == USER_ATTACK)
	{
		int iAttackSum;	//���� ���ݷ°� ���� ���ݷ��� ���� ��

		if (Player->ReturnUserInt(VARIABLE_HAVEWEAPON) == WEAPON_OK)
		{
			iAttackSum = Player->ReturnUserInt(VARIABLE_ATTACK) + GetWeaponPower();
		}
		else
			iAttackSum = m_iUserAttack;

		if (MonsterArr[MonsterNumber].MonsterCurrentLife - iAttackSum >= 0)
			MonsterArr[MonsterNumber].MonsterCurrentLife = MonsterArr[MonsterNumber].MonsterCurrentLife - iAttackSum;
		else
			MonsterArr[MonsterNumber].MonsterCurrentLife = 0;
	}
	else if (Attacker == MONSTER_ATTACK)
	{
		Player->LifeDamaged(MonsterArr[MonsterNumber].MonsterAttck);
	}
}

void Game::ShowUserBattle()
{
	//�Ʒ� �������� �������� ���� �����ʹ� �ٸ� �������̽��� �׳� �и���
	YELLOW
	gotoxy(19, 2);
	cout << "=======����� ����=======";
	ORIGINAL

	gotoxy(15, 4);
	cout << "�̸�: "; Player->ReturnUserName();
	gotoxy(34, 4);
	cout << "����: " << Player->ReturnUserInt(VARIABLE_LEVEL);
	gotoxy(15, 5);
	cout << "�����: " << Player->ReturnUserInt(VARIABLE_CURRENTLIFE) << "/" << Player->ReturnUserInt(VARIABLE_MAXLIFE);
	gotoxy(34, 5);
	if (m_iHaveWeapon == WEAPON_OK)
	{
		cout << "���ݷ�: " << Player->ReturnUserInt(VARIABLE_ATTACK) << " + " << GetWeaponPower();
	}
	else
	{
		cout << "���ݷ�: " << Player->ReturnUserInt(VARIABLE_ATTACK);
	}
	gotoxy(15, 6);
	cout << "����ġ: " << Player->ReturnUserInt(VARIABLE_CURRENTEXP) << "/" << Player->ReturnUserInt(VARIABLE_MAXEXP);
	gotoxy(34, 6);
	cout << "���� ���: " << Player->ReturnUserInt(VARIABLE_GOLD);
}

void Game::ShowMonsterBattle(int MonsterNumber)
{
	gotoxy(19, 22);
	cout << "=======���� ����=======";

	gotoxy(15, 24);
	cout << "�̸�: " << MonsterArr[MonsterNumber].MonsterName;
	gotoxy(34, 24);
	cout << "����: " << MonsterArr[MonsterNumber].MonsterLevel;
	gotoxy(15, 25);
	cout << "�����: " << MonsterArr[MonsterNumber].MonsterCurrentLife << "/" << MonsterArr[MonsterNumber].MonsterMaxLife;
	gotoxy(34, 25);
	cout << "���ݷ�: " << MonsterArr[MonsterNumber].MonsterAttck;
	gotoxy(15, 26);
	cout << "����ġ: " << MonsterArr[MonsterNumber].MonsterCurrentExp << "/" << MonsterArr[MonsterNumber].MonsterMaxExp;
	gotoxy(34, 26);
	cout << "ȹ�� ���: " << MonsterArr[MonsterNumber].MonsterDropGold;
}

void Game::ShowResult(int MonsterNumber)
{
	GameMap.BoxErase(WIDTH, HEIGHT);

	GOLD
	gotoxy(21, 13);
	cout << MonsterArr[MonsterNumber].MonsterName << " ��� ����!";

	gotoxy(23, 15);
	cout << "ȹ�� ����ġ: " << MonsterArr[MonsterNumber].MonsterDropExp;

	gotoxy(24, 17);
	cout << "ȹ�� ���: " << MonsterArr[MonsterNumber].MonsterDropGold;
	ORIGINAL

	bool bIsLevelUp = Player->AcquireReward(MonsterArr[MonsterNumber].MonsterDropExp, MonsterArr[MonsterNumber].MonsterDropGold);
	
	system("pause>null");

	if (bIsLevelUp == true)
	{
		//���� ������
		GameMap.BoxErase(WIDTH, HEIGHT);

		int iIncreaseAttack;
		int iIncreaseLife;

		Player->LevelUp(&iIncreaseAttack, &iIncreaseLife);

		GREEN
		gotoxy(21, 13);
		cout << Player->ReturnUserInt(VARIABLE_LEVEL) << "������ ���� �� �ߴ�";
		gotoxy(24, 15);
		cout << "���ݷ� " << iIncreaseAttack << " ����";
		gotoxy(21, 17);
		cout << "�ִ� ����� " << iIncreaseLife << " ����";
		ORIGINAL

		system("pause>null");
	}

	MonsterArr[MonsterNumber].MonsterCurrentLife = MonsterArr[MonsterNumber].MonsterMaxLife;
}

//��Ʋ ���� �Լ� ����

void Game::ShowUserInfo()
{
	GameMap.BoxErase(WIDTH, HEIGHT);
	int iXPos = 16;
	
	YELLOW
	gotoxy(18, 10);
	cout << "=======����� ����=======";
	ORIGINAL

	gotoxy(iXPos, 13);
	cout << "�̸�: "; Player->ReturnUserName();
	gotoxy(iXPos, 14);
	cout << "����: " << Player->ReturnUserInt(VARIABLE_LEVEL);
	gotoxy(iXPos, 15);
	cout << "�����: " << Player->ReturnUserInt(VARIABLE_CURRENTLIFE) << "/" << Player->ReturnUserInt(VARIABLE_MAXLIFE);
	gotoxy(iXPos, 16);
	
	if (m_iHaveWeapon == WEAPON_OK)
	{
		int iWeaponPower = GetWeaponPower();
		cout << "���ݷ�: " << Player->ReturnUserInt(VARIABLE_ATTACK) << " + " << iWeaponPower;
	}
	else
	{
		cout << "���ݷ�: " << Player->ReturnUserInt(VARIABLE_ATTACK);
	}

	gotoxy(iXPos, 17);
	cout << "����ġ: " << Player->ReturnUserInt(VARIABLE_CURRENTEXP) << "/" << Player->ReturnUserInt(VARIABLE_MAXEXP);
	gotoxy(iXPos, 18);
	cout << "���� ���: " << Player->ReturnUserInt(VARIABLE_GOLD);

	if (m_iHaveWeapon == WEAPON_OK)
	{
		gotoxy(iXPos, 19);
		int iWeaponType = Player->ReturnUserInt(VARIABLE_WEAPONTYPE);
		cout << "���� ���� ����: ";
		GetWeaponName();

		if (iWeaponType == TYPE_BOW)
			cout << "(Ȱ)";
		else if (iWeaponType == TYPE_DAGGER)
			cout << "(�ܰ�)";
		else if (iWeaponType == TYPE_HAMMER)
			cout << "(�б�)";
		else if (iWeaponType == TYPE_SWORD)
			cout << "(Į)";
		else if (iWeaponType == TYPE_WAND)
			cout << "(����)";
		else if (iWeaponType == TYPE_GUN)
			cout << "(��)";
	}

	system("pause>null");
}

void Game::GetWeaponName()
{
	int iWeaponType = Player->ReturnUserInt(VARIABLE_WEAPONTYPE);
	int iWeaponIndex = Player->ReturnUserInt(VARIABLE_WEAPONINDEX);

	string sWeaponName;

	switch (iWeaponType)
	{
	case TYPE_DAGGER:
		sWeaponName = DaggerPtr->ReturnDaggerName(iWeaponIndex);
		break;
	case TYPE_GUN:
		sWeaponName = GunPtr->ReturnGunName(iWeaponIndex);
		break;
	case TYPE_WAND:
		sWeaponName = WandPtr->ReturnWandName(iWeaponIndex);
		break;
	case TYPE_SWORD:
		sWeaponName = SwordPtr->ReturnSwordName(iWeaponIndex);
		break;
	case TYPE_HAMMER:
		sWeaponName = HammerPtr->ReturnHammerName(iWeaponIndex);
		break;
	case TYPE_BOW:
		sWeaponName = BowPtr->ReturnBowName(iWeaponIndex);
		break;
	}

	cout << sWeaponName;
}

int Game::GetWeaponPower()
{
	int iWeaponType = Player->ReturnUserInt(VARIABLE_WEAPONTYPE);
	int iWeaponIndex = Player->ReturnUserInt(VARIABLE_WEAPONINDEX);

	switch (iWeaponType)
	{
	case TYPE_DAGGER:
		return DaggerPtr->ReturnDaggerPower(iWeaponIndex);
	case TYPE_GUN:
		return GunPtr->ReturnGunPower(iWeaponIndex);
	case TYPE_WAND:
		return WandPtr->ReturnWandPower(iWeaponIndex);
	case TYPE_SWORD:
		return SwordPtr->ReturnSwordPower(iWeaponIndex);
	case TYPE_HAMMER:
		return HammerPtr->ReturnHammerPower(iWeaponIndex);
	case TYPE_BOW:
		return BowPtr->ReturnBowPower(iWeaponIndex);
	}
}

void Game::ShowMonsterInfo()
{
	GameMap.BoxErase(WIDTH, HEIGHT);

	int i = 3;

	for (int j = 0; j < m_iMonsterPopulation; j++)
	{
		gotoxy(20, i);
		cout << "=====" << MonsterArr[j].MonsterName << "(" << MonsterArr[j].MonsterLevel << "Lv)=====";
		i++;

		gotoxy(14, i);
		cout << "���ݷ�: " << MonsterArr[j].MonsterAttck;
		gotoxy(34, i);
		cout << "�����: " << MonsterArr[j].MonsterCurrentLife << "/" << MonsterArr[j].MonsterMaxLife;
		i++;
		gotoxy(14, i);
		cout << "����ġ: " << MonsterArr[j].MonsterCurrentExp << "/" << MonsterArr[j].MonsterMaxExp;
		gotoxy(34, i);
		cout << "ȹ�� ����ġ: " << MonsterArr[j].MonsterDropExp;
		i++;
		gotoxy(14, i);
		cout << "ȹ�� ���: " << MonsterArr[j].MonsterDropGold;
		i++;
	}
	
	system("pause>null");
}

//���� ���� �Լ� ����

void Game::WeaponShop()
{
	int iSelect;

	while (1)
	{
		GameMap.BoxErase(WIDTH, HEIGHT);

		gotoxy(24, 6);
		GREEN
		cout << "�߹��� ������";
		ORIGINAL

		gotoxy(27, 9);
		cout << "��ܰ�";
		gotoxy(28, 11);
		cout << "����";
		gotoxy(28, 13);
		cout << "��Į";
		gotoxy(27, 15);
		cout << "�����";
		gotoxy(28, 17);
		cout << "��Ȱ";
		gotoxy(27, 19);
		cout << "��б�";
		gotoxy(23, 21);
		cout << "������ ���ư���";

		iSelect = GameMap.MenuSelectCursor(7, 2, 9, 9);

		int iBuyOrNot;
		int iGesture = NULL;

		int iGetWeaponIndex = 0;
		int iGetWeaponType = 0;	//Weapon.cpp���� ���� �ε����� Ÿ���� ������ ���

		int iUserGold = Player->ReturnUserInt(VARIABLE_GOLD);	//�������� ���̱� ���� ���� ���� ���� ����

		while (iGesture != CLOSE)
		{
			switch (iSelect)
			{
			case 1:
				iBuyOrNot = DaggerPtr->PrintDaggerList(iUserGold, &iGetWeaponType, &iGetWeaponIndex);
				iGesture = BuyScript(iBuyOrNot, iGetWeaponType, iGetWeaponIndex);
				if (iGesture == PAGE_NEXT)
					iSelect = 2;
				else if (iGesture == PAGE_PREVIOUS)
					iSelect = 6;
				break;
			case 2:
				iBuyOrNot = GunPtr->PrintGunList(iUserGold, &iGetWeaponType, &iGetWeaponIndex);
				iGesture = BuyScript(iBuyOrNot, iGetWeaponType, iGetWeaponIndex);
				if (iGesture == PAGE_NEXT)
					iSelect = 3;
				else if (iGesture == PAGE_PREVIOUS)
					iSelect = 1;
				break;
			case 3:
				iBuyOrNot = SwordPtr->PrintSwordList(iUserGold, &iGetWeaponType, &iGetWeaponIndex);
				iGesture = BuyScript(iBuyOrNot, iGetWeaponType, iGetWeaponIndex);
				if (iGesture == PAGE_NEXT)
					iSelect = 4;
				else if (iGesture == PAGE_PREVIOUS)
					iSelect = 2;
				break;
			case 4:
				iBuyOrNot = WandPtr->PrintWandList(iUserGold, &iGetWeaponType, &iGetWeaponIndex);
				iGesture = BuyScript(iBuyOrNot, iGetWeaponType, iGetWeaponIndex);
				if (iGesture == PAGE_NEXT)
					iSelect = 5;
				else if (iGesture == PAGE_PREVIOUS)
					iSelect = 3;
				break;
			case 5:
				iBuyOrNot = BowPtr->PrintBowList(iUserGold, &iGetWeaponType, &iGetWeaponIndex);
				iGesture = BuyScript(iBuyOrNot, iGetWeaponType, iGetWeaponIndex);
				if (iGesture == PAGE_NEXT)
					iSelect = 6;
				else if (iGesture == PAGE_PREVIOUS)
					iSelect = 4;
				break;
			case 6:
				iBuyOrNot = HammerPtr->PrintHammerList(iUserGold, &iGetWeaponType, &iGetWeaponIndex);
				iGesture = BuyScript(iBuyOrNot, iGetWeaponType, iGetWeaponIndex);
				if (iGesture == PAGE_NEXT)
					iSelect = 1;
				else if (iGesture == PAGE_PREVIOUS)
					iSelect = 5;
				break;
			case 7:
				return;
			}
		}
	}
}

int Game::BuyScript(int iBuyOrNot, int iGetWeaponType, int iGetWeaponIndex)
{
	//���Կ��� ���� �춧 ����... ���� ������ ���� ������ ������ ���� �������
	if (iBuyOrNot == PAGE_NEXT)
		return PAGE_NEXT;
	else if (iBuyOrNot == PAGE_PREVIOUS)
		return PAGE_PREVIOUS;
	else if (iBuyOrNot == 0)	//���ư��� ��ư ������
		return CLOSE;
	else if (iBuyOrNot == CANNOT_BUY)
	{
		PrintBuyMessage(false);
		return CLOSE;
	}
	else
	{
		PrintBuyMessage(true);
		Player->DeductGold(iBuyOrNot);
		Player->ChangeWeapon(iGetWeaponType, iGetWeaponIndex);
		return CLOSE;
	}
}

void Game::PrintBuyMessage(int YesOrNo)
{
	if (YesOrNo == true)
	{
		gotoxy(26, 28);
		YELLOW
			cout << "���� ����";
		ORIGINAL
	}
	else if (YesOrNo == false)
	{
		gotoxy(17, 28);
		YELLOW
			cout << "���� ���� ��尡 �����մϴ�.";
		ORIGINAL
	}
	Sleep(1000);

	//������ ���� ���� ���� ���ο� ���� �޽��� ���
}

void Game::SaveMenu()
{
	int iSelect;
	
	while (1)
	{
		GameMap.BoxErase(WIDTH, HEIGHT);

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

		iSelect = GameMap.MenuSelectCursor(11, 2, 7, 4);

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
			GameMap.BoxErase(WIDTH, HEIGHT);
			ifstream DataCheck;	//������ ���� ����
			string sFileName = "SavePlayer" + to_string(iSelect) + ".txt";
			DataCheck.open(sFileName);
			if (DataCheck.is_open())
			{
				int iAnotherSelect;

				YELLOW
				gotoxy(8,11);
				cout << "�̹� �ش� ���Կ� �����Ͱ� ����Ǿ� �ֽ��ϴ�.";
				gotoxy(22, 13);
				cout << "�����ðڽ��ϱ�?";
				ORIGINAL

				gotoxy(29, 16);
				cout << "��";
				gotoxy(27, 18);
				cout << "�ƴϿ�";

				iAnotherSelect = GameMap.MenuSelectCursor(2, 2, 11, 16);

				if (iAnotherSelect == 1)
				{
					DataCheck.close();
					Player->SaveUserData(iSelect);
				}
				else
					break;
			}
			else
			{
				DataCheck.close();
				Player->SaveUserData(iSelect);
			}
			return;
		}
		case 11:
			return;
		}
	}
}

void Game::DeleteInfo()
{
	delete[] MonsterArr;

	delete OwnWeapon;

	delete WeaponPtr;
	delete SwordPtr;
	delete BowPtr;
	delete DaggerPtr;
	delete GunPtr;
	delete WandPtr;
	delete HammerPtr;

	delete Player;

	//���� �Ҵ�� ��� ����
	//�����Ҵ� �� Ŭ������ �������� �ϸ� �˾Ƽ� �Ҹ��ڰ� ȣ��Ǳ� ������ ���� �Ҹ��ڸ� ������ �ҷ���� �� �ʿ䰡 ������
}

Game::~Game()
{
}
