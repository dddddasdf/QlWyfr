#define _CRT_SECURE_NO_WARNINGS
#include "Header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// NameCard ����ü ������ ���� �Ҵ� �� �ʱ�ȭ �� �ּ� �� ��ȯ
NameCard * MakeNameCard(char * name, char * phone)
{
	NameCard *NewNameCard = (NameCard*)malloc(sizeof(NameCard));
	strcpy(NewNameCard->name, name);
	strcpy(NewNameCard->phone, phone);
	return NewNameCard;
}

// NameCard ����ü ������ ���� ���
void ShowNameCardInfo(NameCard * pcard)
{
	printf("�̸�: %s\n", pcard->name);
	printf("����ó: %s\n", pcard->phone);
}

// �̸��� ������ 0, �ٸ��� 0�� �ƴ� �� ��ȯ
int NameCompare(NameCard * pcard, char * name)
{
	if (strcmp(pcard->name, name) == 0)
		return 0;
	else
		return 1;
}

// ��ȭ��ȣ ������ ����
void ChangePhoneNum(NameCard * pcard, char * phone)
{
	strcpy(pcard->phone, phone);
}