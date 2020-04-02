#pragma once
#include "Headers.h"
#include "MapDraw.h"

//��� ���� ��ȯ�� ��� �ϴ� �� ����
//1. �ϳ��ϳ� ���������� ���� �Լ� �������
//2. enum���� ���� ��Ī �������ְ� ������ �ش簪 ����
//�ϴ��� 2������ �غ��� ������ �Լ� �ʹ� ������ �����ϴ�

enum VARIABLE
{
	VARIABLE_CURRENTLIFE,
	VARIABLE_MAXLIFE,
	VARIABLE_ATTACK,
	VARIABLE_MAXEXP,
	VARIABLE_GOLD,
	VARIABLE_LEVEL,
	VARIABLE_HAVEWEAPON,
	VARIABLE_WEAPONINDEX,
	VARIABLE_WEAPONTYPE,
	VARIABLE_CURRENTEXP
};

class User
{
private:
	string m_sUserName;	//�̸�
	int m_iUserCurrentLife;	//��������
	int m_iUserMaxLife;	//�ִ�����
	int m_iUserAttack;	//���ݷ�
	int m_iUserCurrentExp;		//�������ġ
	int m_iUserMaxExp;	//���� ������ �Ѿ�� ���� �ִ� ����ġ
	int m_iUserGold;	//���� ���
	int m_iUserLevel;	//����
	int m_iHaveWeapon;	//���� ���� �ֳ� �ƴѰ�...
	int m_iHaveWeaponIndex;	//���� �ִ� ������ �ε��� �ѹ�
	int m_iHaveWeaponType;	//���� �ִ� ������ ����

	MapDraw UserMap;
public:
	User();
	void ChangeName(string Name);
	bool LoadDefaultUserData();	//����Ʈ ���� ���� �о����, �ؽ�Ʈ�� ���������� �о�鿴�� ��� true�� ��ȯ �ƴҽ� false�� ��ȯ�ϰ� �������� ���۵��� ���ϰ� ����
	bool LoadUserData(int DataNumber);	//����� ���� ���� �ҷ�����
	void SaveUserData(int DataNumber);
	void ChangeWeapon(int WeaponIndex, int iHeaveWeaponType);
	void LifeDamaged(int Damage);	//������ ����� ������ ���� ����
	void LifeReset();	//Ǯ�Ƿ� ȸ��
	bool AcquireReward(int GetExp, int GetGold);	//���� ȹ��, ���� �������� true ��ȯ �ƴҽ� false ��ȯ
	void LevelUp(int *IncreaseAttack, int *IncreaseLife);	//�����ؼ� ���� ���� ����
	void ForFeitGold();	//���� ��� ���ѱ�
	void DeductGold(int WeaponPrice);	//���� �����ϸ� ��� �����

	void ReturnUserName()
	{
		cout << m_sUserName;
	}
	int ReturnUserInt(int VariableName);	//�Ű������� ���� ������ ������� ��ȯ

	inline void gotoxy(int x, int y)
	{
		COORD Pos = { x, y };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
	}
	~User();
};

