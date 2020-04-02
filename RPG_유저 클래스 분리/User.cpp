#include "User.h"
#define WEAPON_OK 1
#define WEAPON_NO 0	//���� ���� ������ 1 �ƴ� 0

//4�� 1�� ��ô��: ���� Ŭ���� �и� �� ���� �����͸� Game ���� ó������ User���� ó���ؾ� ���� ��� �ʿ�


User::User()
{
	m_sUserName = "";
	m_iUserCurrentLife = NULL;
	m_iUserMaxLife = NULL;
	m_iUserAttack = NULL;
	m_iUserCurrentExp = NULL;
	m_iUserMaxExp = NULL;
	m_iUserGold = NULL;
	m_iUserLevel = NULL;
	m_iHaveWeapon = NULL;
	m_iHaveWeaponIndex = -1;	//�� ���� ������ -1
	m_iHaveWeaponType = -1;	//��������
}

void User::ChangeName(string Name)
{
	m_sUserName = Name;
}

bool User::LoadDefaultUserData()
{
	//����Ʈ ���� ���� �ؽ�Ʈ ���� �о�� �� ���ڰ� �ǹ��ϴ� ����
	//���ݷ� �ִ����� �����ϱ����Ѱ���ġ �������ġ ���� �������
	//�ڵ忡�� �߰��� ��������� �ϴ� ���� �������ġ ������ �ִ� ����ġ ��������

	ifstream InfoLoad;
	InfoLoad.open("DefaultUserInfo.txt");
	if (InfoLoad.is_open())
	{
		InfoLoad >> m_iUserAttack;
		InfoLoad >> m_iUserMaxLife;
		InfoLoad >> m_iUserMaxExp;
		InfoLoad >> m_iUserCurrentExp;
		InfoLoad >> m_iUserLevel;
		InfoLoad >> m_iUserGold;
		m_iUserCurrentLife = m_iUserMaxLife;
		m_iHaveWeapon = WEAPON_NO;
		return true;
	}
	else
	{
		UserMap.BoxErase(WIDTH, HEIGHT);

		RED
			gotoxy(26, 14);
		cout << "���� �߻�";
		gotoxy(6, 16);
		cout << "�÷��̾� ���� �ؽ�Ʈ ������ �о�� �� �����ϴ�...";
		ORIGINAL

		system("pause>null");
		return false;	//����Ʈ ���� ������ ���� ��� �������� ǥ���ϰ� ���� ȭ������ ���ư���
	}
}

bool User::LoadUserData(int DataNumber)
{
	//���� ����->���� �̸�, ���ݷ�, �ִ� �����, �����ϱ� ���� ����ġ, ����, ���, ���� ����ġ, ���� �����
	//���� ���� ���� ���� ���� ������ 1 ���� Ÿ��, ���� Ÿ��, ���� �ε��� / ������ 0

	ifstream InfoLoad;
	string sFileName = "SavePlayer" + to_string(DataNumber) + ".txt";
	InfoLoad.open(sFileName);
	if (InfoLoad.is_open())
	{
		InfoLoad >> m_sUserName;
		InfoLoad >> m_iUserAttack;
		InfoLoad >> m_iUserMaxLife;
		InfoLoad >> m_iUserMaxExp;
		InfoLoad >> m_iUserLevel;
		InfoLoad >> m_iUserGold;
		InfoLoad >> m_iUserCurrentExp;
		InfoLoad >> m_iUserCurrentLife;
		InfoLoad >> m_iHaveWeapon;
		if (m_iHaveWeapon == WEAPON_NO)
			InfoLoad.close();
		else if (m_iHaveWeapon == WEAPON_OK)
		{
			InfoLoad >> m_iHaveWeaponType;
			InfoLoad >> m_iHaveWeaponIndex;
		}
		return true;
	}
	else
	{
		UserMap.BoxErase(WIDTH, HEIGHT);

		RED
		gotoxy(26, 14);
		cout << "���� �߻�";
		gotoxy(6, 16);
		cout << "�÷��̾� ���� �ؽ�Ʈ ������ �о�� �� �����ϴ�...";
		ORIGINAL

		system("pause>null");
		return false;	//����Ʈ ���� ������ ���� ��� �������� ǥ���ϰ� ���� ȭ������ ���ư���
	}
}

void User::SaveUserData(int DataNumber)
{
	string sFileName = "SavePlayer" + to_string(DataNumber) + ".txt";
	ofstream DataSave(sFileName);
	DataSave << m_sUserName << " " << m_iUserAttack << " " << m_iUserMaxLife << " " << m_iUserMaxExp << " " << m_iUserLevel << " "
		<< m_iUserGold << " " << m_iUserCurrentExp << " " << m_iUserCurrentLife << "\n";

	if (m_iHaveWeapon == WEAPON_NO)
		DataSave << m_iHaveWeapon;
	else if (m_iHaveWeapon == WEAPON_OK)
		DataSave << m_iHaveWeapon << " " << m_iHaveWeaponType << " " << m_iHaveWeaponIndex;

	DataSave.close();
}

void User::ChangeWeapon(int WeaponType, int WeaponIndex)
{
	m_iHaveWeaponIndex = WeaponIndex;
	m_iHaveWeaponType = WeaponType;
}

void User::LifeDamaged(int Damage)
{
	if (m_iUserCurrentLife - Damage >= 0)
		m_iUserCurrentLife -= Damage;
	else
		m_iUserCurrentLife = 0;
}

void User::LifeReset()
{
	m_iUserCurrentLife = m_iUserMaxLife;
}

bool User::AcquireReward(int GetExp, int GetGold)
{
	m_iUserCurrentExp += GetExp;
	m_iUserGold += GetGold;

	if (m_iUserCurrentExp >= m_iUserMaxExp)
		return true;
	
	return false;
}

void User::LevelUp(int *IncreaseAttack, int *IncreaseLife)
{
	m_iUserLevel++;
	cout << m_iUserLevel << "������ ���� �� �ߴ�";

	//���ݷ��� 1~5, ������� 1~10 �� ������ ���ڷ� ����
	int iAttackPlus = (rand() % 4) + 1;
	int iLifePlus = (rand() % 9) + 1;

	m_iUserAttack += iAttackPlus;
	m_iUserMaxLife += iLifePlus;
	m_iUserCurrentExp = 0;
	m_iUserMaxExp += 3;
	m_iUserCurrentLife = m_iUserMaxLife;

	IncreaseAttack = &iAttackPlus;
	IncreaseLife = &iLifePlus;
}

void User::ForFeitGold()
{
	if (m_iUserGold >= 10)
	{
		double dForfeitGold;	//���� ���
		dForfeitGold = static_cast<double>(m_iUserGold / 10);
		m_iUserGold -= static_cast<int>(dForfeitGold);	//���� �� 1/10�� �����
	}
	else if (m_iUserGold > 0 && m_iUserGold < 10)
	{
		m_iUserGold--;
	}
}

void User::DeductGold(int WeaponPrice)
{
	m_iUserGold -= WeaponPrice;

	if (m_iHaveWeapon == WEAPON_NO)
		m_iHaveWeapon = WEAPON_OK;	//����� ���� ���� ���� ������ ��۵ǰ� ����
}

int User::ReturnUserInt(int VariableName)
{
	switch (VariableName)
	{
	case VARIABLE_ATTACK:
		return m_iUserAttack;
	case VARIABLE_CURRENTLIFE:
		return m_iUserCurrentLife;
	case VARIABLE_MAXLIFE:
		return m_iUserMaxLife;
	case VARIABLE_GOLD:
		return m_iUserGold;
	case VARIABLE_HAVEWEAPON:
		return m_iHaveWeapon;
	case VARIABLE_LEVEL:
		return m_iUserLevel;
	case VARIABLE_MAXEXP:
		return m_iUserMaxExp;
	case VARIABLE_WEAPONINDEX:
		return m_iHaveWeaponIndex;
	case VARIABLE_WEAPONTYPE:
		return m_iHaveWeaponType;
	case VARIABLE_CURRENTEXP:
		return m_iUserCurrentExp;
	}
}

User::~User()
{
}
