#define _CRT_SECURE_NO_WARNINGS
#include "Header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// NameCard 구조체 변수의 동적 할당 및 초기화 후 주소 값 반환
NameCard * MakeNameCard(char * name, char * phone)
{
	NameCard *NewNameCard = (NameCard*)malloc(sizeof(NameCard));
	strcpy(NewNameCard->name, name);
	strcpy(NewNameCard->phone, phone);
	return NewNameCard;
}

// NameCard 구조체 변수의 정보 출력
void ShowNameCardInfo(NameCard * pcard)
{
	printf("이름: %s\n", pcard->name);
	printf("연락처: %s\n", pcard->phone);
}

// 이름이 같으면 0, 다르면 0이 아닌 값 반환
int NameCompare(NameCard * pcard, char * name)
{
	if (strcmp(pcard->name, name) == 0)
		return 0;
	else
		return 1;
}

// 전화번호 정보를 변경
void ChangePhoneNum(NameCard * pcard, char * phone)
{
	strcpy(pcard->phone, phone);
}