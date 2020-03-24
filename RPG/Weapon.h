#pragma once
#include "Headers.h"
#include "MapDraw.h"

struct WeaponStruct
{
	string sWeaponName;	//���� �̸�
	int iWeaponPrice;	//���� ����
	int iWeaponPower;	//���� ���ݷ�
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
	bool InitWeaponList();	//���� ����Ʈ ������
	void InputWeaponData();	//����ü ����� ������ �Է�
	int PrintWeaponList(int HaveGold, int WeaponType, int WeaponNumber, WeaponStruct *ChangeWeapon, WeaponStruct *TypeWeapon);	//���� ����Ʈ ���
	void FreeWeaopnList();	//���� ����Ʈ �����Ҵ� ����
	int ReturnWeaponPower();	//���� ���ݷ� ��ȯ
	void BuyWeapon(WeaponStruct *ChangeWeapon, WeaponStruct TargetWeapon);	//���� ����
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