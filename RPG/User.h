#pragma once
#include "Headers.h"
#include "Weapon.h"

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
public:
	User();
	inline void gotoxy(int x, int y)
	{
		COORD Pos = { x, y };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
	}
	~User();
};

