#pragma once
#include "Headers.h"
#include "MapDraw.h"

//멤버 변수 반환을 어떻게 하는 게 좋나
//1. 하나하나 정성스럽게 리턴 함수 만들어줌
//2. enum으로 변수 명칭 지정해주고 받으면 해당값 리턴
//일단은 2번으로 해본다 솔직히 함수 너무 많으면 복잡하다

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
	string m_sUserName;	//이름
	int m_iUserCurrentLife;	//현재생명력
	int m_iUserMaxLife;	//최대생명력
	int m_iUserAttack;	//공격력
	int m_iUserCurrentExp;		//현재경험치
	int m_iUserMaxExp;	//다음 레벨로 넘어가기 위한 최대 경험치
	int m_iUserGold;	//소지 골드
	int m_iUserLevel;	//레벨
	int m_iHaveWeapon;	//무기 갖고 있나 아닌가...
	int m_iHaveWeaponIndex;	//갖고 있는 무기의 인덱스 넘버
	int m_iHaveWeaponType;	//갖고 있는 무기의 종류

	MapDraw UserMap;
public:
	User();
	void ChangeName(string Name);
	bool LoadDefaultUserData();	//디폴트 유저 파일 읽어오기, 텍스트를 성공적으로 읽어들였을 경우 true를 반환 아닐시 false를 반환하고 새게임이 시작되지 못하게 막음
	bool LoadUserData(int DataNumber);	//저장된 유저 정보 불러오기
	void SaveUserData(int DataNumber);
	void ChangeWeapon(int WeaponIndex, int iHeaveWeaponType);
	void LifeDamaged(int Damage);	//몹한테 대미지 입으면 피통 변경
	void LifeReset();	//풀피로 회복
	bool AcquireReward(int GetExp, int GetGold);	//보상 획득, 만약 레벨업시 true 반환 아닐시 false 반환
	void LevelUp(int *IncreaseAttack, int *IncreaseLife);	//렙업해서 스탯 랜덤 증가
	void ForFeitGold();	//지면 골드 빼앗김
	void DeductGold(int WeaponPrice);	//무기 구매하면 골드 까야지

	void ReturnUserName()
	{
		cout << m_sUserName;
	}
	int ReturnUserInt(int VariableName);	//매개변수에 따라 유저의 멤버변수 반환

	inline void gotoxy(int x, int y)
	{
		COORD Pos = { x, y };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
	}
	~User();
};

