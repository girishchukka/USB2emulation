#include <iostream>

#include"packets.h"

using namespace std;

int main()
{
	Token setup(PID_TOKEN_SETUP, 0x7E, 0xA);
	std::printf("\nTOKEN PKT: SETUP");
	setup.printTokenPkt(setup.getTokenPkt());

	Handshake hdshk(PID_HANDSHAKE_ACK);
	std::printf("\nHANDSHAKE PKT: ACK");
	hdshk.printHandshakePkt(hdshk.getHandshakePkt());

	Data testD(PID_DATA_DATA0);
	UINT32 *dat;
	//UINT32 d[] = { 0x12, 0x41, 0x33, 0x97, 0x88, 0x99, 0x47, 0x50 };
	UINT32 d[] = { 0xFF, 0x80, 0xEA };
	dat = &d[0];
	testD.setData(dat, sizeof(d)/sizeof(UINT32));
	std::printf("\nDATA PKT: DATA0");
	testD.printDataPkt(testD.getDataPkt());

	return 0;
}