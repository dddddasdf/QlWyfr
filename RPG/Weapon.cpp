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
		return false;	//무기 파일이 없을 경우 에러임을 표시하고 메인 화면으로 돌아간다
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
			cout << "가격: " << TypeWeapon[i].iWeaponPrice;
			gotoxy(35, iYPos);
			cout << "무기 타입: ";
			if (WeaponType == TYPE_DAGGER)
				cout << "단검";
			else if (WeaponType == TYPE_GUN)
				cout << "총";
			else if (WeaponType == TYPE_SWORD)
				cout << "칼";
			else if (WeaponType == TYPE_WAND)
				cout << "원드";
			else if (WeaponType == TYPE_BOW)
				cout << "활";
			else if (WeaponType == TYPE_HAMMER)
				cout << "둔기";
			iYPos++;
			gotoxy(10, iYPos);
			cout << "무기명: " << TypeWeapon[i].sWeaponName;
			gotoxy(35, iYPos);
			cout << "공격력: " << TypeWeapon[i].iWeaponPower;

			iYPos += 2;
		}

		gotoxy(24, iYPos);
		cout << "이전 페이지";

		iYPos += 2;

		gotoxy(24, iYPos);
		cout << "다음 페이지";

		iYPos += 2;

		gotoxy(26, iYPos);
		cout << "돌아간다";

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
					ChangeWeapon->sWeaponName.clear();	//유저가 무기를 들고 있으면 문자열 초기화하고 집어 넣어야...
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
		ChangeWeapon->sWeaponName.clear();	//유저가 무기를 들고 있으면 문자열 초기화하고 집어 넣어야...
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
	//무슨 생각으로 윗놈과 이놈을 만들엇지,,,
	//아마도 Game 소스 파일에서 배열 먼저 만들고 그쪽 지역 변수들로 차례차례 대입하려 했나봄 근데 더 나은 방법은 없는가?

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
