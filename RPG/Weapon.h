#pragma once
#include "Headers.h"
#include "MapDraw.h"

struct WeaponStruct
{
	string sWeaponName;	//무기 이름
	int iWeaponPrice;	//무기 가격
	int iWeaponPower;	//무기 공격력
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
	int m_iBowNumber = 0;
	int m_iDaggerNumber = 0;
	int m_iGunNumber = 0;
	int m_iSwordNumber = 0;
	int m_iWandNumber = 0;
	int m_iHammerNumber = 0;
public:
	Weapon();
	bool InitWeaponList();	//무기 리스트 가져옴
	void InputWeaponData();	//구조체 만들고 데이터 입력
	int PrintWeaponList(int HaveGold, int WeaponType, int WeaponNumber, WeaponStruct *ChangeWeapon, WeaponStruct *TypeWeapon);	//무기 리스트 출력
	void FreeWeaopnList();	//무기 리스트 동적할당 해제
	int ReturnWeaponPower();	//무기 공격력 반환
	void BuyWeapon(WeaponStruct *ChangeWeapon, WeaponStruct TargetWeapon);	//무기 구매
	~Weapon();
};

class Sword: public Weapon
{
private:
	WeaponStruct *SwordArr;
public:
	void CreateSwordArr();
	void InputSwordData(string WeaponName, int WeaponPrice, int WeaponPower);
	int PrintSwordList(int HaveGold, WeaponStruct *ChangeWeapon);
};

class Bow : public Weapon
{
private:
	WeaponStruct *BowStruct;
};

class Dagger : public Weapon
{
private:
	WeaponStruct *DaggerStruct;
};

class Gun : public Weapon
{
private:
	WeaponStruct *GunStruct;
};

class Wand : public Weapon
{
private:
	WeaponStruct *WandStruct;
};

class Hammer : public Weapon
{
private:
	WeaponStruct *HammerStruct;
};