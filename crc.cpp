#include<iostream>
#include"crc.h"

UINT8 crc::getHiBit(UINT32 in) {
	for (int i = 31; i >= 0; i--)
		if (in & (1 << i)) {
			return i;
		}
	return 0;
}

UINT8 crc::getCRC5(UINT32 in) {
	// For USB's CRC5 calculation, polynomial is X^5 + X^2 + X^0
	UINT32 ply = 0x25;
	UINT8 bitPos, bitLen;

	in <<= 5;
	bitLen = 1 + getHiBit(in);
	for (UINT8 i = 0; (in & 0xFFFFFFE0); i++) {
		bitPos = getHiBit(in);
		in ^= (ply << (bitPos - 5));
	}
	return in & 0x1F;
}

UINT16 crc::getCRC16(UINT16 *in) {
	// TODO
	return 0;
}

UINT32 crc::getCRC32(UINT32 *in) {
	// TODO
	return 0;
}

