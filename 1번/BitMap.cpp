#include "BitMap.h"


BitMap::BitMap(std::string FileName)
{
	FileName += ".bmp";
	std::string FileNametmp = "C:\\Users\\A-12\\source\\repos\\C6No1\\" + FileName;
	const char* FileNameTmp = FileName.c_str();
	

	m_BitMap = (HBITMAP)LoadImage(NULL, FileNameTmp, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);

	DWORD LastError;
	if (m_BitMap == NULL)
	{
		LastError = GetLastError();
	}
}

bool BitMap::DataNullCheck()
{
	if (m_BitMap == NULL)
		return false;
	else
		return true;
}

HBITMAP BitMap::ReturnBitMap()
{
	return m_BitMap;
}

/*
������ ������ ����
LPCWSTR�� char ��¼���� ȣȯ���� �ʴ´�
��� ������ �ڲ� �߻��ϸ� ������Ʈ �Ӽ����� ���� ���������� ��Ƽ����Ʈ�� �ٲ۴�
�̰� ��ġ�µ� �ѳ��� �� ����� �� ��ȯ��?
*/