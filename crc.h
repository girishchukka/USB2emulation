#pragma once
#include<iostream>
#include"macros.h"

class crc {
public:
	UINT8 getCRC5(UINT32 in);
	UINT16 getCRC16(UINT16 *in);
	UINT32 getCRC32(UINT32 *in);
	UINT8 getHiBit(UINT32 in);
};
