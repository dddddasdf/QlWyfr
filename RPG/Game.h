#pragma once
#include "Headers.h"
#include "MapDraw.h"
#include "Weapon.h"

struct Monster
{
	string MonsterName;	//�� �̸�
	int MonsterCurrentLife;	//�� ���� �����
	int MonsterMaxLife;	//�� �ִ� �����
	int MonsterAttck;	//�� ���ݷ�
	int MonsterDropGold;	//���� �ִ� ���
	int MonsterLevel;	//�� ���� ����
	int MonsterCurrentExp;	//�� ���� ����ġ
	int MonsterMaxExp;	//���� ���� ���� ���� �䱸 ����ġ
	int MonsterDropExp;	//���� �ִ� ����ġ
	int Delay;	//���Ͱ� ������ �ϱ���� �ɸ��� �ð�
};

enum OUTCOME
{
	OUTCOME_DRAW,
	OUTCOME_WIN,
	OUTCOME_LOSE
};

class Game
{
private:
	MapDraw GameMap;
	string m_sUserName;	//�̸�
	int m_iUserCurrentLife;	//��������
	int m_iUserMaxLife;	//�ִ�����
	int m_iUserAttack;	//���ݷ�
	int m_iUserCurrentExp;		//�������ġ
	int m_iUserMaxExp;	//���� ������ �Ѿ�� ���� �ִ� ����ġ
	int m_iUserGold;	//���� ���
	int m_iUserLevel;	//����
	int m_iHaveWeapon;	//���� ���� �ֳ� �ƴѰ�...
	//������� ���� ���� ����
	int m_iMonsterPopulation;	//�� ��ü��
	Monster *MonsterArr;
	Weapon *WeaponPtr;
	Sword *SwordPtr;
	WeaponStruct *OwnWeapon;	//������ ���� �ִ� ����
public:
	Game();
	void GetName(string name);
	bool InitUserData();	//���� ���� �ʱ�ȭ, �ؽ�Ʈ�� ���������� �о�鿴�� ��� true�� ��ȯ�ϰ� ������ ���� �ƴҽ� false�� ��ȯ�ϰ� �������� ���۵��� ���ϰ� ����
	bool InitMonsterData();	//�� ���� �ʱ�ȭ. InitUserInfo()�� �Ȱ��� ��Ŀ����
	bool InitWeaponData();	//���� ���� �ʱ�ȭ. �� ���� ���̽��� ������ ���� �ٸ���
	void LoadUserData();	//����� ���� ���� �ҷ�����
	void LoadMonsterData();	//����� �� ���� �ҷ�����
	void TownMenu();	//���� ���
	void DungeonList();	//���� ���
	void NowBattle(int MonsterNumber);	//���� ȭ��
	void PrintObject();
	void PrintMessage(int Outcome, int MonsterNumber);	//�ý��� �޽��� ���
	void Attack(int Attacker, int MonsterNumber);	//���� �Լ�
	void ShowUserBattle();	//���� �� ���� ���� ������
	void ShowMonsterBattle(int MonsterNumber);	//���� �� �� ���� ������
	void ShowResult(int MonsterNumber);	//�� ��� �� �������ͽ� ������
	void ShowUserInfo();
	void ShowMonsterInfo();
	void WeaponShop();
	void CallMenu(int PageNumber);
	void SaveMenu();
	void SaveData(int DataNumber);	//������ ����
	void DeleteInfo();
	inline void gotoxy(int x, int y)
	{
		COORD Pos = { x, y };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
	}
	~Game();
};

