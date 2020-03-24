#pragma once
#include "Headers.h"

class User
{
private:
	string m_sUserName;	//이름
	int m_iUserCurrentLife;	//현재생명력
	int m_iUserMaxLife;	//최대생명력
	int m_iUserAttack;	//공격력
	int m_iUserCurrentExp;		//현재경험치
	int m_iUserMaxExp;	//다음 레벨로 넘어가기 위한 최대 경험치
	int m_iUserGold;	//소지 골드
	int m_iUserLevel;	//레벨
	int m_iHaveWeapon;	//무기 갖고 있나 아닌가...
public:
	User();
	~User();
};

