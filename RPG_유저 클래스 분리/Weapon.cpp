#include "Weapon.h"

Weapon::Weapon()
{
}

int Weapon::m_iBowCount = 0;
int Weapon::m_iDaggerCount = 0;
int Weapon::m_iGunCount = 0;
int Weapon::m_iSwordCount = 0;
int Weapon::m_iWandCount = 0;
int Weapon::m_iHammerCount = 0;

bool Weapon::InitWeaponCount()
{
	ifstream WeaponLoad;
	WeaponLoad.open("WeaponList.txt");
	if (WeaponLoad.is_open())
	{
		string sWeaponType;

		while (!WeaponLoad.eof())
		{
			WeaponLoad >> sWeaponType;

			if (sWeaponType == "Bow")
				m_iBowCount++;
			else if (sWeaponType == "Dagger")
				m_iDaggerCount++;
			else if (sWeaponType == "Gun")
				m_iGunCount++;
			else if (sWeaponType == "Wand")
				m_iWandCount++;
			else if (sWeaponType == "Hammer")
				m_iHammerCount++;
			else if (sWeaponType == "Sword")
				m_iSwordCount++;
		}

		WeaponLoad.close();
		return true;
	}
	else
		return false;	//���� ������ ���� ��� �������� ǥ���ϰ� ���� ȭ������ ���ư���
}

void Weapon::InputWeaponData(string WeaponName, int WeaponPrice, int WeaponPower, int WeaponNumber, WeaponStruct *InputWeaponStruct)
{
	int i = 0;
	for (; i < WeaponNumber; i++)
	{
		if (InputWeaponStruct[i].iWeaponPower == NULL)
			break;
	}

	InputWeaponStruct[i].sWeaponName = WeaponName;
	InputWeaponStruct[i].iWeaponPrice = WeaponPrice;
	InputWeaponStruct[i].iWeaponPower = WeaponPower;
}

void Weapon::InitWeaponInt(WeaponStruct *MakeWeaponArr, int WeaponNumber, int WeaponType)
{
	for (int i = 0; i < WeaponNumber; i++)
	{
		MakeWeaponArr[i].iWeaponPower = NULL;
		MakeWeaponArr[i].iWeaponPrice = NULL;
		MakeWeaponArr[i].iWeaponType = WeaponType;
	}
}

int Weapon::PrintWeaponList(int HaveGold, int WeaponType, int WeaponNumber, int ChangeWeaponType, int ChangeWeaponIndex, WeaponStruct *TypeWeapon)
{
	int iSelect;

	while (1)
	{
		BoxErase(WIDTH, HEIGHT);

		int iYPos = 3;

		for (int i = 0; i < WeaponNumber; i++)
		{
			gotoxy(10, iYPos);
			cout << "����: " << TypeWeapon[i].iWeaponPrice;
			gotoxy(35, iYPos);
			cout << "���� Ÿ��: ";
			if (WeaponType == TYPE_DAGGER)
				cout << "�ܰ�";
			else if (WeaponType == TYPE_GUN)
				cout << "��";
			else if (WeaponType == TYPE_SWORD)
				cout << "Į";
			else if (WeaponType == TYPE_WAND)
				cout << "����";
			else if (WeaponType == TYPE_BOW)
				cout << "Ȱ";
			else if (WeaponType == TYPE_HAMMER)
				cout << "�б�";
			iYPos++;
			gotoxy(10, iYPos);
			cout << "�����: " << TypeWeapon[i].sWeaponName;
			gotoxy(35, iYPos);
			cout << "���ݷ�: " << TypeWeapon[i].iWeaponPower;

			iYPos += 2;
		}

		gotoxy(24, iYPos);
		cout << "���� ������";

		iYPos += 3;

		gotoxy(24, iYPos);
		cout << "���� ������";

		iYPos += 3;

		gotoxy(26, iYPos);
		cout << "���ư���";

		iSelect = MenuSelectCursor(WeaponNumber + 3, 3, 3, 3);

		//�Ʒ��� ���� ���� ����

		if (iSelect == WeaponNumber + 3)
			return 0;	//���� �޴��� ���ư��� ���� ������
		else if (iSelect == WeaponNumber + 2)
			return PAGE_NEXT;	//���� ������
		else if (iSelect == WeaponNumber + 1)
			return PAGE_PREVIOUS;	//���� ������
		else
		{
			if (HaveGold >= TypeWeapon[iSelect -1].iWeaponPrice)
			{
				ChangeWeaponType = TypeWeapon[iSelect - 1].iWeaponType;
				ChangeWeaponIndex = TypeWeapon[iSelect - 1].iWeaponIndex;

				return (TypeWeapon[iSelect - 1].iWeaponPrice);	//���� �Ϸ� �� ���� ��� �����ϰԲ�
			}
			else
				return CANNOT_BUY;	//���� ���� ��尡 ���� ���ݺ��� ������ ���� ������ ��ȯ
		}
	}
}

void Weapon::BuyWeapon(WeaponStruct *ChangeWeapon, WeaponStruct TargetWeapon)
{
	//������ �� ���� �Լ� Ȥ�ó� �; ���� �״µ� �� ���� �� Ȯ�� �Ǹ� ������ �� ����
	
	if (!ChangeWeapon->sWeaponName.empty())
	{
		ChangeWeapon->sWeaponName.clear();	//������ ���⸦ ��� ������ ���ڿ� �ʱ�ȭ�ϰ� ���� �־��...
	}
	ChangeWeapon->sWeaponName = TargetWeapon.sWeaponName;
	ChangeWeapon->iWeaponPower = TargetWeapon.iWeaponPower;
	ChangeWeapon->iWeaponPrice = TargetWeapon.iWeaponPrice;
}

void Sword::CreateSwordArr()
{
	SwordStruct = new WeaponStruct[m_iSwordCount];

	InitWeaponInt(SwordStruct, m_iSwordCount, TYPE_SWORD);
}

void Sword::InputSwordData(string WeaponName, int WeaponPrice, int WeaponPower)
{
	//���� �������� ����� �̳��� �������,,,
	//Weapon Ŭ������ ����� �Լ� �������. ������ ���� ���� �Լ� ��Ʈ �ּ� ó���� ���� 
	//Game.cpp���� �о���� ���ڿ�, ���� �ΰ��� ���� �̸��� ���� �� ���ݷ����� ����

	/*int i = 0;
	for (; i < m_iSwordNumber; i++)
	{
		if (SwordArr[i].iWeaponPower == NULL)
			break;
	}

	SwordArr[i].sWeaponName = WeaponName;
	SwordArr[i].iWeaponPrice = WeaponPrice;
	SwordArr[i].iWeaponPower = WeaponPower;*/

	SwordStruct[m_iSwordIndex].iWeaponIndex = m_iSwordIndex;
	m_iSwordIndex++;

	InputWeaponData(WeaponName, WeaponPrice, WeaponPower, m_iSwordCount, SwordStruct);
}

int Sword::PrintSwordList(int HaveGold, int *WeaponType, int *WeaponIndex)
{
	int iReturnConstant;
	iReturnConstant = PrintWeaponList(HaveGold, TYPE_SWORD, m_iSwordCount, *WeaponType, *WeaponIndex, SwordStruct);

	return iReturnConstant;
}

void Bow::CreateBowArr()
{
	BowStruct = new WeaponStruct[m_iBowCount];

	InitWeaponInt(BowStruct, m_iBowCount, TYPE_BOW);
}

void Bow::InputBowData(string WeaponName, int WeaponPrice, int WeaponPower)
{
	InputWeaponData(WeaponName, WeaponPrice, WeaponPower, m_iBowCount, BowStruct);
}

int Bow::PrintBowList(int HaveGold, int *WeaponType, int *WeaponIndex)
{
	int iReturnConstant;
	iReturnConstant = PrintWeaponList(HaveGold, TYPE_BOW, m_iBowCount, *WeaponType, *WeaponIndex, BowStruct);

	return iReturnConstant;
}

void Dagger::CreateDaggerArr()
{
	DaggerStruct = new WeaponStruct[m_iDaggerCount];
	
	InitWeaponInt(DaggerStruct, m_iDaggerCount, TYPE_DAGGER);

	/*DaggerStruct = new WeaponStruct[m_iDaggerNumber];

	for (int i = 0; i < m_iDaggerNumber; i++)
	{
		DaggerStruct[i].iWeaponPower = NULL;
		DaggerStruct[i].iWeaponPrice = NULL;
		DaggerStruct[i].iWeaponType = TYPE_DAGGER;
	}*/
}

void Dagger::InputDaggerData(string WeaponName, int WeaponPrice, int WeaponPower)
{
	InputWeaponData(WeaponName, WeaponPrice, WeaponPower, m_iDaggerCount, DaggerStruct);
}

int Dagger::PrintDaggerList(int HaveGold, int *WeaponType, int *WeaponIndex)
{
	int iReturnConstant;
	iReturnConstant = PrintWeaponList(HaveGold, TYPE_DAGGER, m_iDaggerCount, *WeaponType, *WeaponIndex, DaggerStruct);

	return iReturnConstant;
}

void Gun::CreateGunArr()
{
	GunStruct = new WeaponStruct[m_iGunCount];

	InitWeaponInt(GunStruct, m_iGunCount, TYPE_GUN);
}

void Gun::InputGunData(string WeaponName, int WeaponPrice, int WeaponPower)
{
	InputWeaponData(WeaponName, WeaponPrice, WeaponPower, m_iGunCount, GunStruct);
}

int Gun::PrintGunList(int HaveGold, int *WeaponType, int *WeaponIndex)
{
	int iReturnConstant;
	iReturnConstant = PrintWeaponList(HaveGold, TYPE_GUN, m_iGunCount, *WeaponType, *WeaponIndex, GunStruct);

	return iReturnConstant;
}

void Wand::CreateWandArr()
{
	WandStruct = new WeaponStruct[m_iWandCount];

	InitWeaponInt(WandStruct, m_iWandCount, TYPE_WAND);
}

void Wand::InputWandData(string WeaponName, int WeaponPrice, int WeaponPower)
{
	InputWeaponData(WeaponName, WeaponPrice, WeaponPower, m_iWandCount, WandStruct);
}

int Wand::PrintWandList(int HaveGold, int *WeaponType, int *WeaponIndex)
{
	int iReturnConstant;
	iReturnConstant = PrintWeaponList(HaveGold, TYPE_WAND, m_iWandCount, *WeaponType, *WeaponIndex, WandStruct);

	return iReturnConstant;
}

void Hammer::CreateHammerArr()
{
	HammerStruct = new WeaponStruct[m_iHammerCount];

	InitWeaponInt(HammerStruct, m_iHammerCount, TYPE_HAMMER);
}

void Hammer::InputHammerData(string WeaponName, int WeaponPrice, int WeaponPower)
{
	InputWeaponData(WeaponName, WeaponPrice, WeaponPower, m_iHammerCount, HammerStruct);
}

int Hammer::PrintHammerList(int HaveGold, int *WeaponType, int *WeaponIndex)
{
	int iReturnConstant;
	iReturnConstant = PrintWeaponList(HaveGold, TYPE_HAMMER, m_iHammerCount, *WeaponType, *WeaponIndex, HammerStruct);

	return iReturnConstant;
}

Weapon::~Weapon()
{
}
