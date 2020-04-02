#pragma once
#include "Headers.h"
#include "MapDraw.h"
#include "Weapon.h"
#include "User.h"

struct Monster
{
	string MonsterName;	//몹 이름
	int MonsterCurrentLife;	//몹 현재 생명력
	int MonsterMaxLife;	//몹 최대 생명력
	int MonsterAttck;	//몹 공격력
	int MonsterDropGold;	//몹이 주는 골드
	int MonsterLevel;	//몹 현재 레벨
	int MonsterCurrentExp;	//몹 현재 경험치
	int MonsterMaxExp;	//다음 레벨 가기 위한 요구 경험치
	int MonsterDropExp;	//몹이 주는 경험치
	int Delay;	//몬스터가 공격을 하기까지 걸리는 시간
};

enum OUTCOME
{
	OUTCOME_DRAW,
	OUTCOME_WIN,
	OUTCOME_LOSE	//승패 출력을 위한 enum
};

class Game
{
private:
	MapDraw GameMap;
	string m_sUserName;	//이름
	int m_iUserCurrentLife;	//현재생명력
	int m_iUserMaxLife;	//최대생명력
	int m_iUserAttack;	//공격력
	int m_iUserCurrentExp;		//현재경험치
	int m_iUserMaxExp;	//다음 레벨로 넘어가기 위한 최대 경험치
	int m_iUserGold;	//소지 골드
	int m_iUserLevel;	//레벨
	int m_iHaveWeapon;	//무기 갖고 있나 아닌가...

	User *Player;
	//여기까지 유저 관련 변수

	int m_iMonsterPopulation;	//몹 개체수
	Monster *MonsterArr;
	Weapon *WeaponPtr;
	Sword *SwordPtr;
	Bow *BowPtr;
	Dagger *DaggerPtr;
	Gun *GunPtr;
	Wand *WandPtr;
	Hammer *HammerPtr;
	WeaponStruct *OwnWeapon;	//유저가 갖고 있는 무기
public:
	Game();
	void GetName(string name);
	bool LoadDefaultUserData();	//디폴트 유저 파일 읽어오기, 텍스트를 성공적으로 읽어들였을 경우 true를 반환 아닐시 false를 반환하고 새게임이 시작되지 못하게 막음
	bool InitMonsterData();	//몹 정보 초기화. InitUserInfo()와 똑같은 매커니즘
	bool InitWeaponData();	//무기 정보 초기화. 저 둘을 베이스로 하지만 조금 다르다
	bool LoadUserData(int DataNumber);	//저장된 유저 정보 불러오기
	void TownMenu();	//마을 목록
	void DungeonList();	//던전 목록
	void NowBattle(int MonsterNumber);	//전투 화면
	void PrintObject();
	void PrintMessage(int Outcome, int MonsterNumber);	//시스템 메시지 출력
	void Attack(int Attacker, int MonsterNumber);	//공격 함수
	void ShowUserBattle();	//전투 중 유저 정보 보여줌
	void ShowMonsterBattle(int MonsterNumber);	//전투 중 몹 정보 보여줌
	void ShowResult(int MonsterNumber);	//몹 잡고 상세 스테이터스 보여줌
	void ShowUserInfo();
	void GetWeaponName();	
	int GetWeaponPower();	//위 둘은 Weapon 클래스로부터 이름과 공격력을 가져오게 한다
	void ShowMonsterInfo();
	void WeaponShop();
	int BuyScript(int iBuyOrNot, int iGetWeaponType, int iGetWeaponIndex);
	void PrintBuyMessage(int YesOrNo);
	void SaveMenu();
	void DeleteInfo();
	inline void gotoxy(int x, int y)
	{
		COORD Pos = { x, y };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
	}
	~Game();
};

