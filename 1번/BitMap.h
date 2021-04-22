#pragma once
#include <windows.h>
#include <iostream>

class BitMap
{
private:
	HBITMAP m_BitMap;

public:
	BitMap(std::string FileName);
	bool DataNullCheck();	//이미지가 제대로 로드 된 것인가 확인

	HBITMAP ReturnBitMap();	//매니저로 비트맵 정보 넘김
};

//단순히 생성자에서 불러올 것이 아니라...
//예외 처리도 필요하다. ID나 파일을 읽어들이지 못했을 경우 해당 파일을 불러오지 못했다는 경고문
