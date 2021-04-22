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
오늘의 뼈아픈 교훈
LPCWSTR이 char 어쩌구와 호환되지 않는다
라는 오류가 자꾸 발생하면 프로젝트 속성으로 들어가서 문자집합을 멀티바이트로 바꾼다
이거 고치는데 한나절 다 써먹은 게 실환가?
*/