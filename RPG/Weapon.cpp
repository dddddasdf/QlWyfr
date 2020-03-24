#include "Weapon.h"
#define PURCHASE_NOT -5


Weapon::Weapon()
{
}

bool Weapon::InitWeaponList()
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
				m_iBowNumber++;
			else if (sWeaponType == "Dagger")
				m_iDaggerNumber++;
			else if (sWeaponType == "Gun")
				m_iGunNumber++;
			else if (sWeaponType == "Wand")
				m_iWandNumber++;
			else if (sWeaponType == "Hammer")
				m_iHammerNumber++;
			else if (sWeaponType == "Sword")
				m_iSwordNumber++;
		}

		WeaponLoad.close();
		return true;
	}
	else
		return false;	//���� ������ ���� ��� �������� ǥ���ϰ� ���� ȭ������ ���ư���
}

void Weapon::InputWeaponData()
{
	
}

int Weapon::PrintWeaponList(int HaveGold, int WeaponType, int WeaponNumber, WeaponStruct *ChangeWeapon, WeaponStruct *TypeWeapon)
{
	int iSelect;

	while (1)
	{
		BoxErase(WIDTH, HEIGHT);

		int iYPos = 6;

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

		iYPos += 2;

		gotoxy(24, iYPos);
		cout << "���� ������";

		iYPos += 2;

		gotoxy(26, iYPos);
		cout << "���ư���";

		iSelect = MenuSelectCursor(WeaponNumber + 3, 2, 3, 6);

		if (iSelect == WeaponNumber + 3)
			return 0;
		else if (iSelect == WeaponNumber + 2)
			return (WeaponType + 1);
		else if (iSelect == WeaponNumber + 1)
			return (WeaponType - 1);
		else
		{
			if (HaveGold >= TypeWeapon[iSelect].iWeaponPrice)
			{
				if (!ChangeWeapon->sWeaponName.empty())
				{
					ChangeWeapon->sWeaponName.clear();	//������ ���⸦ ��� ������ ���ڿ� �ʱ�ȭ�ϰ� ���� �־��...
				}
				ChangeWeapon->sWeaponName = TypeWeapon[iSelect].sWeaponName;
				ChangeWeapon->iWeaponPower = TypeWeapon[iSelect].iWeaponPower;
				ChangeWeapon->iWeaponPrice = TypeWeapon[iSelect].iWeaponPrice;
			}
			else
				return PURCHASE_NOT;
		}
	}
}

void Weapon::BuyWeapon(WeaponStruct *ChangeWeapon, WeaponStruct TargetWeapon)
{
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
	SwordArr = new WeaponStruct[m_iSwordNumber];

	for (int i = 0; i < m_iSwordNumber; i++)
	{
		SwordArr[i].iWeaponPower = NULL;
		SwordArr[i].iWeaponPrice = NULL;
	}
}

void Sword::InputSwordData(string WeaponName, int WeaponPrice, int WeaponPower)
{
	//���� �������� ����� �̳��� �������,,,
	//�Ƹ��� Game �ҽ� ���Ͽ��� �迭 ���� ����� ���� ���� ������� �������� �����Ϸ� �߳��� �ٵ� �� ���� ����� ���°�?

	int i = 0;
	for (; i < m_iSwordNumber; i++)
	{
		if (SwordArr[i].iWeaponPower == NULL)
			break;
	}

	SwordArr[i].sWeaponName = WeaponName;
	SwordArr[i].iWeaponPrice = WeaponPrice;
	SwordArr[i].iWeaponPower = WeaponPower;
}

int Sword::PrintSwordList(int HaveGold, WeaponStruct *ChangeWeapon)
{
	int iReturnConstant;
	iReturnConstant = PrintWeaponList(HaveGold, TYPE_SWORD, m_iSwordNumber, ChangeWeapon, SwordArr);

	return iReturnConstant;
}

Weapon::~Weapon()
{
}
