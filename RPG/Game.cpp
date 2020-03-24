#include "Game.h"
#define ROCK 1
#define SCISSORS 2
#define PAPER 3
#define OBJECT_Y 13
#define USER_ATTACK 10
#define MONSTER_ATTACK 11
#define WEAPON_OK 1
#define WEAPON_NO 0	//무기 갖고 있으면 1 아님 0

//몹 레벨업 시스템 제거 대신에 패배로 전투 종료시 몹 HP 풀 회복 및 골드 삥 뜯김

Game::Game()
{
	
}

void Game::GetName(string name)
{
	m_sUserName = name;	//새게임 시작할 때 메뉴 클래스 쪽에서 이름 받아옴
}

bool Game::InitUserData()
{
	//디폴트 유저 정보 텍스트 파일 읽어올 때 숫자가 의미하는 순서
	//공격력 최대생명력 렙업하기위한경험치 현재경험치 레벨 소지골드
	//코드에서 추가로 설정해줘야 하는 변수 현재경험치 몹한테 주는 경험치 현재생명력
	
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
		GameMap.BoxErase(WIDTH, HEIGHT);

		RED
		gotoxy(26, 14);
		cout << "에러 발생";
		gotoxy(6, 16);
		cout << "플레이어 정보 텍스트 파일을 읽어올 수 없습니다...";
		ORIGINAL

		system("pause>null");
		return false;	//디폴트 유저 파일이 없을 경우 에러임을 표시하고 메인 화면으로 돌아간다
	}
}

bool Game::InitMonsterData()
{
	//맨 위의 숫자는 등장하는 몬스터의 총 수
	//디폴트 몹 정보 텍스트 파일 읽어올 때 숫자가 의미하는 순서
	//몹이름, 공격력, 생명력, 렙업 하기 위한 경험치, 주는 경험치, 레벨, 주는 골드
	//코드에서 추가로 설정해줘야 하는 변수 현재경험치 몹한테 주는 경험치 현재생명력
	
	ifstream MonsterInfoLoad;
	MonsterInfoLoad.open("DefaultMonsterInfo.txt");
	if (MonsterInfoLoad.is_open())
	{
		MonsterInfoLoad >> m_iMonsterPopulation;
		MonsterArr = new Monster[m_iMonsterPopulation];

		int j = 0;

		while (!MonsterInfoLoad.eof())
		{
			MonsterInfoLoad >> MonsterArr[j].MonsterName;
			MonsterInfoLoad >> MonsterArr[j].MonsterAttck;
			MonsterInfoLoad >> MonsterArr[j].MonsterMaxLife;
			MonsterInfoLoad >> MonsterArr[j].MonsterMaxExp;
			MonsterInfoLoad >> MonsterArr[j].MonsterDropExp;
			MonsterInfoLoad >> MonsterArr[j].MonsterLevel;
			MonsterInfoLoad >> MonsterArr[j].MonsterDropGold;
			MonsterArr[j].MonsterCurrentExp = 0;
			MonsterArr[j].MonsterCurrentLife = MonsterArr[j].MonsterMaxLife;
			j++;
		}

		return true;
	}
	else
	{
		GameMap.BoxErase(WIDTH, HEIGHT);

		RED
		gotoxy(26, 14);
		cout << "에러 발생";
		gotoxy(7, 16);
		cout << "몬스터 정보 텍스트 파일을 읽어올 수 없습니다...";
		ORIGINAL

		system("pause>null");
		return false;	//디폴트 몬스터 파일이 없을 경우 에러임을 표시하고 메인 화면으로 돌아간다
	}
}

bool Game::InitWeaponData()
{
	WeaponPtr = new Weapon();
	SwordPtr = new Sword();
	if ((WeaponPtr->InitWeaponList()) == false)
	{
		GameMap.BoxErase(WIDTH, HEIGHT);

		RED
		gotoxy(26, 14);
		cout << "에러 발생";
		gotoxy(8, 16);
		cout << "무기 정보 텍스트 파일을 읽어올 수 없습니다...";
		ORIGINAL

		system("pause>null");

		return false;
	}
	else
	{
		//정상적으로 파일을 읽었다면 각 무기 개수가 몇개인지 카운트 되어있음
		//작동 순서: 무기 배열 생성 함수->무기 배열에 지역 변수를 매개 변수로 넣어서 데이터 입력
		SwordPtr->CreateSwordArr();

		ifstream WeaponLoad;
		WeaponLoad.open("WeaponList.txt");
		if (WeaponLoad.is_open())
		{
			string sWeaponType;
			string sWeaponName;
			int iWeaponPrice;
			int iWeaponPower;

			while (!WeaponLoad.eof())
			{
				WeaponLoad >> sWeaponType;

				if (sWeaponType == "Sword")
				{
					WeaponLoad >> sWeaponName;
					WeaponLoad >> iWeaponPower;
					WeaponLoad >> iWeaponPrice;
					SwordPtr->InputSwordData(sWeaponName, iWeaponPrice, iWeaponPower);
				}
			}
		}

		//유저가 갖고 있는 무기 데이터 초기화
		OwnWeapon->iWeaponPower = 0;
		OwnWeapon->iWeaponPrice = 0;
		OwnWeapon->sWeaponName = "";
		return true;
	}
}

//여기까지 디폴트 인포 데이터 불러오기 영역

void Game::TownMenu()
{
	int iSelect;
	
	while (1)
	{
		GameMap.BoxErase(WIDTH, HEIGHT);
		
		BLUE_GREEN
		gotoxy(23, 8);
		cout << "==== 마을 ====";
		ORIGINAL

		gotoxy(26, 11);
		cout << "던전 입구";
		gotoxy(26, 13);
		cout << "유저 정보";
		gotoxy(25, 15);
		cout << "몬스터 정보";
		gotoxy(26, 17);
		cout << "무기 상점";
		gotoxy(26, 19);
		cout << "저장한다";
		gotoxy(28, 21);
		cout << "종료";

		iSelect = GameMap.MenuSelectCursor(6, 2, 10, 11);

		switch (iSelect)
		{
		default:
			break;
		case 1:
			DungeonList();
			break;
		case 2:
			ShowUserInfo();
			break;
		case 3:
			ShowMonsterInfo();
			break;
		case 4:
			WeaponShop();
			break;
		case 5:
			SaveMenu();
			break;
		case 6:
			DeleteInfo();
			return;
		}
	}
}

void Game::DungeonList()
{
	int iSelect;
	int iSumMenuNum = m_iMonsterPopulation + 1;

	while (1)
	{
		GameMap.BoxErase(WIDTH, HEIGHT);
		
		PUPPLE
		gotoxy(20, 7);
		cout << "=====층별 안내=====";

		int i = 10;
		for (int j = 0; j < m_iMonsterPopulation; j++)
		{
			gotoxy(22, i);
			cout << (j + 1) << "층: " << MonsterArr[j].MonsterName;
			i += 2;
		}

		gotoxy(22, i);
		cout << "마을로 돌아간다";

		ORIGINAL

		iSelect = GameMap.MenuSelectCursor(iSumMenuNum, 2, 7, 10);

		if (iSelect == iSumMenuNum)
			return;
		else
		{
			NowBattle(iSelect - 1);
			break;
		}
	}
}

//배틀 관련 함수 시작

void Game::NowBattle(int MonsterNumber)
{
	char iGetKey = 0;	//getch()용
	int iMonsterCard;	//몹이 뭐 냈는지 저장용

	GameMap.BoxErase(WIDTH, HEIGHT);

	ShowUserBattle();
	ShowMonsterBattle(MonsterNumber);

	PrintObject();

	//가위: A    바위: S     보: D

	while (1)
	{
		if (iGetKey == 0)
			iGetKey = _getch();	//최초 입력

		iMonsterCard = (rand() % 3) + 1;

		if (iGetKey == 'S' || iGetKey == 's')
		{
			if (iMonsterCard == ROCK)
				PrintMessage(OUTCOME_DRAW, MonsterNumber);
			else if (iMonsterCard == SCISSORS)
				PrintMessage(OUTCOME_WIN, MonsterNumber);
			else
				PrintMessage(OUTCOME_LOSE, MonsterNumber);

			gotoxy(24, OBJECT_Y - 1);
			cout << "바위";
		}
		else if (iGetKey == 'A' || iGetKey == 'a')
		{
			if (iMonsterCard == SCISSORS)
				PrintMessage(OUTCOME_DRAW, MonsterNumber);
			else if (iMonsterCard == PAPER)
				PrintMessage(OUTCOME_WIN, MonsterNumber);
			else
				PrintMessage(OUTCOME_LOSE, MonsterNumber);

			gotoxy(24, OBJECT_Y - 1);
			cout << "가위";
		}
		else if (iGetKey == 'D' || iGetKey == 'd')
		{
			if (iMonsterCard == PAPER)
				PrintMessage(OUTCOME_DRAW, MonsterNumber);
			else if (iMonsterCard == ROCK)
				PrintMessage(OUTCOME_WIN, MonsterNumber);
			else
				PrintMessage(OUTCOME_LOSE, MonsterNumber);

			gotoxy(25, OBJECT_Y - 1);
			cout << "보";
		}
		else
		{
			GameMap.BoxErase(WIDTH, HEIGHT);

			ShowUserBattle();
			ShowMonsterBattle(MonsterNumber);

			PrintObject();

			gotoxy(23, 16);
			cout << "몹: 집중 안 하냐?";
			gotoxy(20, 17);
			cout << "몬스터에게 한대 맞았다...";

			Attack(MONSTER_ATTACK, MonsterNumber);
			//지정된 키 이외를 입력하면 한대 맞음
		}

		ShowUserBattle();
		ShowMonsterBattle(MonsterNumber);

		//아래 if문은 몬스터가 낸 패가 무엇인지 출력
		if (iMonsterCard == ROCK)
		{
			gotoxy(34, OBJECT_Y - 1);
			cout << "바위";
		}
		else if (iMonsterCard == SCISSORS)
		{
			gotoxy(34, OBJECT_Y - 1);
			cout << "가위";
		}
		else
		{
			gotoxy(35, OBJECT_Y - 1);
			cout << "보";
		}

		//승리 조건식
		if (MonsterArr[MonsterNumber].MonsterCurrentLife == 0)
		{
			BLOOD
			gotoxy(35, OBJECT_Y);
			cout << "몹";
			ORIGINAL

			gotoxy(22, 17);
			cout << "전투에서 승리했다.";
			system("pause>null");

			ShowResult(MonsterNumber);

			return;
		}

		//패배 조건식
		if (m_iUserCurrentLife == 0)
		{
			gotoxy(25, OBJECT_Y);
			BLOOD
			cout << "너";
			gotoxy(8, 17);
			cout << "전투에서 패배했다. 당신은 눈 앞이 깜깜해졌다...";
			gotoxy(20, 18);
			cout << "가진 돈 일부를 빼앗겼다.";
			ORIGINAL

			system("pause>null");

			m_iUserCurrentLife = m_iUserMaxLife;
			MonsterArr[MonsterNumber].MonsterCurrentLife = MonsterArr[MonsterNumber].MonsterMaxLife;
			
			if (m_iUserGold >= 10)
			{
				double dForfeitGold;	//몰수 골드
				dForfeitGold = static_cast<double>(m_iUserGold / 10);
				m_iUserGold -= static_cast<int>(dForfeitGold);	//가진 돈 1/10이 뺏긴다
			}
			else if (m_iUserGold > 0 && m_iUserGold < 10)
			{
				m_iUserGold--;
			}
				
			return;
		}

		iGetKey = _getch();
	}
}

void Game::PrintObject()
{
	gotoxy(25, OBJECT_Y);
	YELLOW
	cout << "너";
	ORIGINAL

	PUPPLE
	gotoxy(35, OBJECT_Y);
	cout << "몹";
	ORIGINAL

	gotoxy(27, 15);
	cout << "<시스템>";

	gotoxy(16, 19);
	cout << "가위: A    바위: S     보: D";
}

void Game::PrintMessage(int Outcome, int MonsterNumber)
{
	GameMap.BoxErase(WIDTH, HEIGHT);

	PrintObject();

	switch (Outcome)
	{
	case OUTCOME_DRAW:
		gotoxy(28, 16);
		cout << "비겼다";
		break;
	case OUTCOME_LOSE:
		gotoxy(24, 16);
		cout << "몬스터의 승리";
		Attack(MONSTER_ATTACK, MonsterNumber);
		break;
	case OUTCOME_WIN:
		gotoxy(25, 16);
		cout << "당신의 승리";
		Attack(USER_ATTACK, MonsterNumber);
		break;
	}
}

void Game::Attack(int Attacker, int MonsterNumber)
{
	if (Attacker == USER_ATTACK)
	{
		int iAttackSum;	//무기 공격력과 기존 공격력을 합한 것

		if (m_iHaveWeapon == WEAPON_OK)
		{
			//iAttackSum = m_iUserAttack + (무기공격력);
		}
		else
			iAttackSum = m_iUserAttack;

		if (MonsterArr[MonsterNumber].MonsterCurrentLife - iAttackSum >= 0)
			MonsterArr[MonsterNumber].MonsterCurrentLife = MonsterArr[MonsterNumber].MonsterCurrentLife - iAttackSum;
		else
			MonsterArr[MonsterNumber].MonsterCurrentLife = 0;
	}
	else if (Attacker == MONSTER_ATTACK)
	{
		if (m_iUserCurrentLife - MonsterArr[MonsterNumber].MonsterAttck >= 0)
			m_iUserCurrentLife = m_iUserCurrentLife - MonsterArr[MonsterNumber].MonsterAttck;
		else
			m_iUserCurrentLife = 0;
	}
}

void Game::ShowUserBattle()
{
	YELLOW
	gotoxy(19, 2);
	cout << "=======당신의 정보=======";
	ORIGINAL

	gotoxy(15, 4);
	cout << "이름: " << m_sUserName;
	gotoxy(34, 4);
	cout << "레벨: " << m_iUserLevel;
	gotoxy(15, 5);
	cout << "생명력: " << m_iUserCurrentLife << "/" << m_iUserMaxLife;
	gotoxy(34, 5);
	if (m_iHaveWeapon == WEAPON_OK)
	{
		cout << "공격력: " << m_iUserAttack << " + " << "무기공격력 테스트";
	}
	else
	{
		cout << "공격력: " << m_iUserAttack;
	}
	gotoxy(15, 6);
	cout << "경험치: " << m_iUserCurrentExp << "/" << m_iUserMaxExp;
	gotoxy(34, 6);
	cout << "소지 골드: " << m_iUserGold;
}

void Game::ShowMonsterBattle(int MonsterNumber)
{
	gotoxy(19, 22);
	cout << "=======몬스터 정보=======";

	gotoxy(15, 24);
	cout << "이름: " << MonsterArr[MonsterNumber].MonsterName;
	gotoxy(34, 24);
	cout << "레벨: " << MonsterArr[MonsterNumber].MonsterLevel;
	gotoxy(15, 25);
	cout << "생명력: " << MonsterArr[MonsterNumber].MonsterCurrentLife << "/" << MonsterArr[MonsterNumber].MonsterMaxLife;
	gotoxy(34, 25);
	cout << "공격력: " << MonsterArr[MonsterNumber].MonsterAttck;
	gotoxy(15, 26);
	cout << "경험치: " << MonsterArr[MonsterNumber].MonsterCurrentExp << "/" << MonsterArr[MonsterNumber].MonsterMaxExp;
	gotoxy(34, 26);
	cout << "획득 골드: " << MonsterArr[MonsterNumber].MonsterDropGold;
}

void Game::ShowResult(int MonsterNumber)
{
	GameMap.BoxErase(WIDTH, HEIGHT);

	GOLD
	gotoxy(21, 13);
	cout << MonsterArr[MonsterNumber].MonsterName << " 토벌 성공!";

	gotoxy(23, 15);
	cout << "획득 경험치: " << MonsterArr[MonsterNumber].MonsterDropExp;

	gotoxy(24, 17);
	cout << "획득 골드: " << MonsterArr[MonsterNumber].MonsterDropGold;
	ORIGINAL

	m_iUserCurrentExp += MonsterArr[MonsterNumber].MonsterDropExp;
	m_iUserGold += MonsterArr[MonsterNumber].MonsterDropGold;

	system("pause>null");

	if (m_iUserCurrentExp >= m_iUserMaxExp)
	{
		//유저 레벨업
		GameMap.BoxErase(WIDTH, HEIGHT);

		GREEN
		gotoxy(21, 13);
		m_iUserLevel++;
		cout << m_iUserLevel <<"레벨로 레벨 업 했다";

		//공격력은 1~5, 생명력은 1~10 중 랜덤한 숫자로 증가
		int iAttackPlus = (rand() % 4) + 1;
		int iLifePlus = (rand() % 9) + 1;

		gotoxy(24, 15);
		cout << "공격력 "<< iAttackPlus << " 증가";
		gotoxy(21, 17);
		cout << "최대 생명력 "<< iLifePlus << " 증가";
		ORIGINAL

		m_iUserAttack += iAttackPlus;
		m_iUserMaxLife += iLifePlus;
		m_iUserCurrentExp = 0;
		m_iUserMaxExp += 3;
		m_iUserCurrentLife = m_iUserMaxLife;

		system("pause>null");
	}

	MonsterArr[MonsterNumber].MonsterCurrentLife = MonsterArr[MonsterNumber].MonsterMaxLife;
}

//배틀 관련 함수 종료

void Game::ShowUserInfo()
{
	GameMap.BoxErase(WIDTH, HEIGHT);
	
	YELLOW
	gotoxy(18, 10);
	cout << "=======당신의 정보=======";
	ORIGINAL

	gotoxy(19, 13);
	cout << "이름: " << m_sUserName;
	gotoxy(19, 14);
	cout << "레벨: " << m_iUserLevel;
	gotoxy(19, 15);
	cout << "생명력: " << m_iUserCurrentLife << "/" << m_iUserMaxLife;
	gotoxy(19, 16);
	
	if (m_iHaveWeapon == WEAPON_OK)
	{
		cout << "공격력: " << m_iUserAttack << " + " << "무기공격력 테스트";
	}
	else
	{
		cout << "공격력: " << m_iUserAttack;
	}

	gotoxy(19, 17);
	cout << "경험치: " << m_iUserCurrentExp << "/" << m_iUserMaxExp;
	gotoxy(19, 18);
	cout << "소지 골드: " << m_iUserGold;

	if (m_iHaveWeapon == WEAPON_OK)
	{
		gotoxy(19, 19);
		cout << "소지 중인 무기: " << "무기명 테스트" << "(무기 타입)";
	}

	system("pause>null");
}

void Game::ShowMonsterInfo()
{
	GameMap.BoxErase(WIDTH, HEIGHT);

	int i = 3;

	for (int j = 0; j < m_iMonsterPopulation; j++)
	{
		gotoxy(20, i);
		cout << "=====" << MonsterArr[j].MonsterName << "(" << MonsterArr[j].MonsterLevel << "Lv)=====";
		i++;
		gotoxy(14, i);
		cout << "공격력: " << MonsterArr[j].MonsterAttck;
		gotoxy(34, i);
		cout << "생명력: " << MonsterArr[j].MonsterCurrentLife << "/" << MonsterArr[j].MonsterMaxLife;
		i++;
		gotoxy(14, i);
		cout << "경험치: " << MonsterArr[j].MonsterCurrentExp << "/" << MonsterArr[j].MonsterMaxExp;
		gotoxy(34, i);
		cout << "획득 경험치: " << MonsterArr[j].MonsterDropExp;
		i++;
		gotoxy(14, i);
		cout << "획득 골드: " << MonsterArr[j].MonsterDropGold;
		i++;
	}
	
	system("pause>null");
}

void Game::WeaponShop()
{
	int iSelect;

	while (1)
	{
		GameMap.BoxErase(WIDTH, HEIGHT);

		gotoxy(24, 6);
		GREEN
		cout << "◆무기 상점◆";
		ORIGINAL

		gotoxy(27, 9);
		cout << "→단검";
		gotoxy(28, 11);
		cout << "→총";
		gotoxy(28, 13);
		cout << "→칼";
		gotoxy(27, 15);
		cout << "→원드";
		gotoxy(28, 17);
		cout << "→활";
		gotoxy(27, 19);
		cout << "→둔기";
		gotoxy(23, 21);
		cout << "마을로 돌아간다";

		/*gotoxy(53, 27);
		cout << "○";
		gotoxy(52, 28);
		cout << "/ ㅣ";
		gotoxy(35, 27);
		cout << "( 어서옵셔 >";*/

		iSelect = GameMap.MenuSelectCursor(7, 2, 9, 9);

		switch (iSelect)
		{
		default:
			cout << "댕";
			break;
		case 7:
			return;
		}
	}
}

void Game::CallMenu(int PageNumber)
{
	//무기 페이지 불러올 때 보다 편리하게 하기 위해서
	//댕대댕ㄷㅇ댕댕 씨발 죽고 싶다

	switch (PageNumber)
	{
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
		break;
	}
}

void Game::SaveMenu()
{
	int iSelect;
	
	while (1)
	{
		GameMap.BoxErase(WIDTH, HEIGHT);

		int iXPos = 19, iYPos = 4;

		for (int i = 1; i <= 10; i++)
		{
			ifstream DataCheck;	//슬롯의 공란 여부
			string sFileName = "SavePlayer" + to_string(i) + ".txt";

			DataCheck.open(sFileName);
			
			gotoxy(iXPos, iYPos);
			
			if (DataCheck.is_open())
				cout << i << "번 슬롯(파일 여부: O)";
			else
				cout << i << "번 슬롯(파일 여부: X)";

			iYPos += 2;

			DataCheck.close();
		}
		
		gotoxy(26, iYPos);
		cout << "돌아간다";

		iSelect = GameMap.MenuSelectCursor(11, 2, 7, 4);

		switch (iSelect)
		{
		default:
			break;
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
		case 8:
		case 9:
		case 10:
		{
			GameMap.BoxErase(WIDTH, HEIGHT);
			ifstream DataCheck;	//슬롯의 공란 여부
			string sFileName = "SavePlayer" + to_string(iSelect) + ".txt";
			DataCheck.open(sFileName);
			if (DataCheck.is_open())
			{
				int iAnotherSelect;

				YELLOW
				gotoxy(8,11);
				cout << "이미 해당 슬롯에 데이터가 저장되어 있습니다.";
				gotoxy(22, 13);
				cout << "덮어씌우시겠습니까?";
				ORIGINAL

				gotoxy(29, 16);
				cout << "예";
				gotoxy(27, 18);
				cout << "아니오";

				iAnotherSelect = GameMap.MenuSelectCursor(2, 2, 11, 16);

				if (iAnotherSelect == 1)
				{
					DataCheck.close();
					SaveData(iSelect);
				}
				else
					break;
			}
			else
			{
				DataCheck.close();
				SaveData(iSelect);
			}
			return;
		}
		case 11:
			return;
		}
	}
}

void Game::SaveData(int DataNumber)
{
	//파일 저장할 때 변수 순서->유저 이름, 공격력, 최대 생명력, 렙업하기 위한 경험치, 레벨, 골드, 현재 경험치, 현재 생명력
	//다음 줄은 무기 여부 무기 있으면 1 쓰고 무기 타입, 무기 이름, 공격력, 골드 없으면 0 쓰고 파일 닫기
	//몹 상태를 저장해야 할 필요가 있을까??

	GameMap.BoxErase(WIDTH, HEIGHT);

	string sFileName  = "SavePlayer" + to_string(DataNumber) + ".txt";
	ofstream DataSave(sFileName);
	DataSave << m_sUserName << " " << m_iUserAttack << " " << m_iUserMaxLife << " " << m_iUserMaxExp << " " << m_iUserLevel << " "
		<< m_iUserGold << " " << m_iUserCurrentExp << " " << m_iUserCurrentLife << "\n";

	if (m_iHaveWeapon == WEAPON_NO)
		DataSave << m_iHaveWeapon;
	else if (m_iHaveWeapon == WEAPON_OK)
		DataSave << m_iHaveWeapon;

	DataSave.close();

	gotoxy(27, 15);
	cout << "저장 완료";

	system("pause>null");
}

void Game::DeleteInfo()
{
	delete[] MonsterArr;
}

Game::~Game()
{
}
