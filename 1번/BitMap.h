#pragma once
#include <windows.h>
#include <iostream>

class BitMap
{
private:
	HBITMAP m_BitMap;

public:
	BitMap(std::string FileName);
	bool DataNullCheck();	//�̹����� ����� �ε� �� ���ΰ� Ȯ��

	HBITMAP ReturnBitMap();	//�Ŵ����� ��Ʈ�� ���� �ѱ�
};

//�ܼ��� �����ڿ��� �ҷ��� ���� �ƴ϶�...
//���� ó���� �ʿ��ϴ�. ID�� ������ �о������ ������ ��� �ش� ������ �ҷ����� ���ߴٴ� ���
