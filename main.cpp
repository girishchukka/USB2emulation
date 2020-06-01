#include <iostream>

#include"packetFormats.h"

using namespace std;

int main()
{
	Token setup(PID_TOKEN_SETUP, 0x7E, 0xA);
	UINT32 data = 0;
	UINT32 crc5 = 0;

	data = setup.getTokenPkt();
	crc5 = data & 0x1F;
	data >>= 5;

	std::printf("CRC5 (%x) is (%x)\n", data, crc5);
	std::printf("Token is: %x\n", setup.getTokenPkt());

	UINT32 *dat;
	//UINT32 d[] = { 0x12, 0x41, 0x33, 0x97, 0x88, 0x99, 0x47, 0x50 };
	UINT32 d[] = { 0xFF, 0x80, 0xEA };
	dat = &d[0];
	Data testD;
	testD.setData(dat, sizeof(d)/sizeof(UINT32));
	testD.printData();
	std::printf("CRC16 of the above data is : %x", testD.getCRC16());

	return 0;
}