#define _CRT_SECURE_NO_WARNINGS
#include "Header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void InputInformation(NameCard *Array[])
{
	char NameTmp[NAME_LEN];
	char PhoneTmp[PHONE_LEN];

	printf("1. ����� �̸� �Է�: ");
	scanf("%s", NameTmp);
	printf("2. ����� ����ó �Է�: ");
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
	printf("�˻��� �̸� �Է�: ");
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
	printf("�ش��ϴ� �̸��� ���� ����� �����ϴ�.\n");
}

void SearchPhoneNumber(NameCard *Array[])
{
	printf("�˻��� �̸� �Է�: ");
	char NameSearch[NAME_LEN];
	scanf("%s", NameSearch);

	for (int i = 0; i < 3; i++)
	{
		if (NameCompare(Array[i], NameSearch) == 0)
		{
			char PhoneNumberTmp[PHONE_LEN];
			printf("������ ��ȭ��ȣ�� �Է�: ");
			scanf("%s", PhoneNumberTmp);
			ChangePhoneNum(Array[i], PhoneNumberTmp);
			return;
		}
	}
	printf("�ش��ϴ� �̸��� ���� ����� �����ϴ�.\n");
}

void DeleteInformation(NameCard *Array[])
{
	printf("�˻��� �̸� �Է�: ");
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
	printf("�ش��ϴ� �̸��� ���� ����� �����ϴ�.\n");
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