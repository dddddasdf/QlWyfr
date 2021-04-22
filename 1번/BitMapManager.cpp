#include "BitMapManager.h"

BitMapManager::BitMapManager(HDC hdc, HINSTANCE g_hInst) : m_hInst(g_hInst)
{

}

bool BitMapManager::LoadNewImage(std::string FileName)
{
	BitMap *NewBitMap = new BitMap(FileName);

	if (NewBitMap->ReturnBitMap() != NULL)
	{
		m_BitMapVector.push_back(NewBitMap);
		return true;
	}
	else
	{
		return false;
	}
}

void BitMapManager::PrintBitMap(HDC hdc, int BitMapNumber, int xLocation, int yLocation)
{
	HBITMAP OldBitMap;
	HBITMAP BitMapTmp;
	//BITMAP BitMapSize;	//사진 크기 구하는 용
	HDC MemDC = CreateCompatibleDC(hdc);
	//int PictureSizeX, PictureSizeY;	//사진 크기 저장할 변수

	BitMapTmp = m_BitMapVector[BitMapNumber]->ReturnBitMap();
	OldBitMap = (HBITMAP)SelectObject(MemDC, BitMapTmp);

	DWORD LastError;
	if (OldBitMap == NULL)
	{
		LastError = GetLastError();	//작업을 완료했습니다라고 하는데 뭐가 문제야 ㅅㅂ
	}

	BitBlt(hdc, xLocation, yLocation, IMAGESIZE_X, IMAGESIZE_Y, MemDC, 0, 0, SRCCOPY);

	SelectObject(MemDC, OldBitMap);

	DeleteObject(BitMapTmp);
	DeleteDC(MemDC);
}