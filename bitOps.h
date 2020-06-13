#pragma once
#include"macros.h"
class bitOps
{
public:
	void setBits(UINT32& number, UINT32 val, UINT32 k, UINT32 p) {
		// set bits from val between start and end
		UINT32 mask = ((1 << k) - 1);
		number &= (~(mask << p));
		number |= ((val & mask) << p);
	}
	UINT32 getBits(UINT32 number, UINT32 k, UINT32 p) {
		// get k bits starting from position p in number
		return (((1 << k) - 1) & (number >> (p - 1)));
	}
};

