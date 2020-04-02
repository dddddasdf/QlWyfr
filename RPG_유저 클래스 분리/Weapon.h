#pragma once
#include "Headers.h"
#include "MapDraw.h"
#define PAGE_PREVIOUS -5
#define PAGE_NEXT -4
#define CANNOT_BUY -3

struct WeaponStruct
{
	int iWeaponIndex;
	string sWeaponName;	//무기 이름
	int iWeaponPrice;	//무기 가격
	int iWeaponPower;	//무기 공격력
	int iWeaponType;	//무기 타입
};

enum TYPE
{
	TYPE_DAGGER = 1,
	TYPE_GUN = 2,
	TYPE_SWORD = 3,
	TYPE_WAND = 4,
	TYPE_BOW = 5,
	TYPE_HAMMER = 6
};

class Weapon: public MapDraw
{
protected:
	static int m_iBowCount;
	static int m_iDaggerCount;
	static int m_iGunCount;
	static int m_iSwordCount;
	static int m_iWandCount;
	static int m_iHammerCount;
public:
	Weapon();
	bool InitWeaponCount();	//무기 리스트 가져옴
	void InputWeaponData(string WeaponName, int WeaponPrice, int WeaponPower, int WeaponNumber, WeaponStruct *InputWeaponStruct);	//데이터 입력
	void InitWeaponInt(WeaponStruct *MakeWeaponArr, int WeaponNumber, int WeaponType);
	int PrintWeaponList(int HaveGold, int WeaponType, int WeaponNumber, int ChangeWeaponType, int ChangeWeaponIndex, WeaponStruct *TypeWeapon);	//무기 리스트 출력
	void BuyWeapon(WeaponStruct *ChangeWeapon, WeaponStruct TargetWeapon);	//무기 구매
	~Weapon();
};

class Sword: public Weapon
{
private:
	WeaponStruct *SwordStruct;
	int m_iSwordIndex = 0;
public:
	Sword() { }
	void CreateSwordArr();
	void InputSwordData(string WeaponName, int WeaponPrice, int WeaponPower);
	int PrintSwordList(int HaveGold, int *WeaponType, int *WeaponIndex);
	string ReturnSwordName(int Index)
	{
		return SwordStruct[Index].sWeaponName;
	}
	int ReturnSwordPower(int Index)
	{
		return SwordStruct[Index].iWeaponPower;
	}
	~Sword() { delete[] SwordStruct; }
};

class Bow : public Weapon
{
private:
	WeaponStruct *BowStruct;
	int m_iBowIndex = 0;
public:
	Bow() { }
	void CreateBowArr();
	void InputBowData(string WeaponName, int WeaponPrice, int WeaponPower);
	int PrintBowList(int HaveGold, int *WeaponType, int *WeaponIndex);
	string ReturnBowName(int Index)
	{
		return BowStruct[Index].sWeaponName;
	}
	int ReturnBowPower(int Index)
	{
		return BowStruct[Index].iWeaponPower;
	}
	~Bow() { delete[] BowStruct; }
};

class Dagger : public Weapon
{
private:
	WeaponStruct *DaggerStruct;
	int m_iDaggerIndex = 0;
public:
	Dagger() { }
	void CreateDaggerArr();
	void InputDaggerData(string WeaponName, int WeaponPrice, int WeaponPower);
	int PrintDaggerList(int HaveGold, int *WeaponType, int *WeaponIndex);
	string ReturnDaggerName(int Index)
	{
		return DaggerStruct[Index].sWeaponName;
	}
	int ReturnDaggerPower(int Index)
	{
		return DaggerStruct[Index].iWeaponPower;
	}
	~Dagger() { delete[] DaggerStruct; }
};

class Gun : public Weapon
{
private:
	WeaponStruct *GunStruct;
	int m_iGunIndex = 0;
public:
	Gun() { }
	void CreateGunArr();
	void InputGunData(string WeaponName, int WeaponPrice, int WeaponPower);
	int PrintGunList(int HaveGold, int *WeaponType, int *WeaponIndex);
	string ReturnGunName(int Index)
	{
		return GunStruct[Index].sWeaponName;
	}
	int ReturnGunPower(int Index)
	{
		return GunStruct[Index].iWeaponPower;
	}
	~Gun() { delete[] GunStruct; }
};

class Wand : public Weapon
{
private:
	WeaponStruct *WandStruct;
	int m_iWandIndex = 0;
public:
	Wand() { }
	void CreateWandArr();
	void InputWandData(string WeaponName, int WeaponPrice, int WeaponPower);
	int PrintWandList(int HaveGold, int *WeaponType, int *WeaponIndex);
	string ReturnWandName(int Index)
	{
		return WandStruct[Index].sWeaponName;
	}
	int ReturnWandPower(int Index)
	{
		return WandStruct[Index].iWeaponPower;
	}
	~Wand() { delete[] WandStruct; }
};

class Hammer : public Weapon
{
private:
	WeaponStruct *HammerStruct;
	int m_iHammerIndex = 0;
public:
	Hammer() { }
	void CreateHammerArr();
	void InputHammerData(string WeaponName, int WeaponPrice, int WeaponPower);
	int PrintHammerList(int HaveGold, int *WeaponType, int *WeaponIndex);
	string ReturnHammerName(int Index)
	{
		return HammerStruct[Index].sWeaponName;
	}
	int ReturnHammerPower(int Index)
	{
		return HammerStruct[Index].iWeaponPower;
	}
	~Hammer() { delete[] HammerStruct; }
};