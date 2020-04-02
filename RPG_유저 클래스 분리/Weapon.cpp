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
		return false;	//무기 파일이 없을 경우 에러임을 표시하고 메인 화면으로 돌아간다
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

		iYPos += 3;

		gotoxy(24, iYPos);
		cout << "다음 페이지";

		iYPos += 3;

		gotoxy(26, iYPos);
		cout << "돌아간다";

		iSelect = MenuSelectCursor(WeaponNumber + 3, 3, 3, 3);

		//아래는 구매 관련 내용

		if (iSelect == WeaponNumber + 3)
			return 0;	//이전 메뉴로 돌아가게 변수 돌려줌
		else if (iSelect == WeaponNumber + 2)
			return PAGE_NEXT;	//다음 페이지
		else if (iSelect == WeaponNumber + 1)
			return PAGE_PREVIOUS;	//이전 페이지
		else
		{
			if (HaveGold >= TypeWeapon[iSelect -1].iWeaponPrice)
			{
				ChangeWeaponType = TypeWeapon[iSelect - 1].iWeaponType;
				ChangeWeaponIndex = TypeWeapon[iSelect - 1].iWeaponIndex;

				return (TypeWeapon[iSelect - 1].iWeaponPrice);	//구매 완료 및 소지 골드 차감하게끔
			}
			else
				return CANNOT_BUY;	//소지 중인 골드가 무기 가격보다 적으면 구매 못함을 반환
		}
	}
}

void Weapon::BuyWeapon(WeaponStruct *ChangeWeapon, WeaponStruct TargetWeapon)
{
	//지금은 안 쓰는 함수 혹시나 싶어서 남겨 뒀는데 안 쓰는 거 확정 되면 지워야 할 문단
	
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
	SwordStruct = new WeaponStruct[m_iSwordCount];

	InitWeaponInt(SwordStruct, m_iSwordCount, TYPE_SWORD);
}

void Sword::InputSwordData(string WeaponName, int WeaponPrice, int WeaponPower)
{
	//무슨 생각으로 윗놈과 이놈을 만들엇지,,,
	//Weapon 클래스에 담당할 함수 만들었음. 만약을 위해 기존 함수 파트 주석 처리로 보관 
	//Game.cpp에서 읽어들인 문자열, 변수 두개를 각각 이름과 가격 및 공격력으로 대입

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
