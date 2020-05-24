#define _CRT_SECURE_NO_WARNINGS
#include "Header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void InputInformation(NameCard *Array[])
{
	char NameTmp[NAME_LEN];
	char PhoneTmp[PHONE_LEN];

	printf("1. 등록할 이름 입력: ");
	scanf("%s", NameTmp);
	printf("2. 등록할 연락처 입력: ");
	scanf("%s", PhoneTmp);

	for (int i = 0; i < 3; i++)
	{
		if (Array[i]->name == 0)
		{
			Array[i] = MakeNameCard(NameTmp, PhoneTmp);
			break;
		}
	}
}

void SearchInformation(NameCard *Array[])
{
	printf("검색할 이름 입력: ");
	char NameSearch[NAME_LEN];
	scanf("%s", NameSearch);

	for (int i = 0; i < 3; i++)
	{
		if (NameCompare(Array[i], NameSearch) == 0)
		{
			ShowNameCardInfo(Array[i]);
			return;
		}
	}
	printf("해당하는 이름을 가진 사람이 없습니다.\n");
}

void SearchPhoneNumber(NameCard *Array[])
{
	printf("검색할 이름 입력: ");
	char NameSearch[NAME_LEN];
	scanf("%s", NameSearch);

	for (int i = 0; i < 3; i++)
	{
		if (NameCompare(Array[i], NameSearch) == 0)
		{
			char PhoneNumberTmp[PHONE_LEN];
			printf("변경할 전화번호를 입력: ");
			scanf("%s", PhoneNumberTmp);
			ChangePhoneNum(Array[i], PhoneNumberTmp);
			return;
		}
	}
	printf("해당하는 이름을 가진 사람이 없습니다.\n");
}

void DeleteInformation(NameCard *Array[])
{
	printf("검색할 이름 입력: ");
	char NameSearch[NAME_LEN];
	scanf("%s", NameSearch);

	for (int i = 0; i < 3; i++)
	{
		if (NameCompare(Array[i], NameSearch) == 0)
		{
			for (int j = i; j < 3; j++)
			{
				Array[j] = Array[j + 1];
				if (j + 1 == 3)
				{
					Array[j + 1] = 0;
					return;
				}
			}
		}
	}
	printf("해당하는 이름을 가진 사람이 없습니다.\n");
}

void ShowLinear(NameCard *Array[])
{
	for (int i = 0; i < 3; i++)
	{
		if (Array[i] != 0)
			ShowNameCardInfo(Array[i]);
	}
}

int main()
{
	NameCard CardArray[3] = { 0 };
	
	InputInformation(CardArray);
	InputInformation(CardArray);
	InputInformation(CardArray);

	SearchInformation(CardArray);
	SearchPhoneNumber(CardArray);
	DeleteInformation(CardArray);
	ShowLinear(CardArray);

	return 0;
}