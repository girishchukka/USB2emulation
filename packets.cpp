#include"packets.h"

void Token::setCRC5() {
	crc calc;
	UINT32 data;
	UINT8 pid = getPID();
	if ((pid == PID_TOKEN_IN) || (pid == PID_TOKEN_OUT) || (pid == PID_TOKEN_SETUP)) {
		data = (m_pid << 11) | (m_addr << 4) | m_ep;
	}
	else if (pid == PID_TOKEN_SOF) {
		data = (m_pid << 11) | m_frameNo;
	}
	m_crc5 = calc.getCRC5(data) & 0x1F;
}

UINT32 Token::getTokenPkt() {
	UINT8 pid = getPID();
	if ((pid == PID_TOKEN_IN) || (pid == PID_TOKEN_OUT) || (pid == PID_TOKEN_SETUP)) {
		return (m_crc5 | (m_ep << 5) | (m_addr << 9) | (m_pid << 16));
	}
	else if (pid == PID_TOKEN_SOF) {
		return (m_crc5 | (m_frameNo << 5) | (m_pid << 16));
	}
}

void Token::printTokenPkt(UINT32 pkt) {
	if(getPID() == PID_TOKEN_SOF)
		std::printf("\n%.4x   #pid = %x, frameNumber = %x, crc5 = %x\n", pkt, m_pid, getFrameNo(), getCRC5());
	else
		std::printf("\n%.4x   #pid = %x, addr = %x, ep = %x, crc5 = %x\n", pkt, m_pid, getAddr(), getEP(), getCRC5());
}

UINT32 Token::consumeTokenPkt(Token tkn) {
	return 0;
}

UINT8 Handshake::getHandshakePkt() {
	return (m_pid & 0xFF);
}

void Handshake::printHandshakePkt(UINT8 pkt) {
	std::printf("\n%.2x\n", pkt);
}

UINT8 Handshake::consumeHandshakePkt(Handshake pkt) {
	return 0;
}

void Data::setData(UINT32 *dataPtr, UINT32 lenInBytes) {
	m_dataLenInBytes = lenInBytes;
	m_dataSrc = new UINT32[m_dataLenInBytes];
	memcpy(m_dataSrc, dataPtr, m_dataLenInBytes*sizeof(UINT32));
	setCRC16();
}

void Data::setCRC16() {
	UINT32 curr;
	// For USB's CRC16 calculation, polynomial is X^16 + X^15 + X^2 + X^0
	const UINT32 crc16_ply = 0x18005 << 15;
	UINT32 poly = crc16_ply;
	UINT32 len = m_dataLenInBytes;

	curr = get2BytesforCRCcalc(&m_dataSrc[m_dataLenInBytes - len], len);
	while (len != 0) {
		curr = (len == 1) ? (curr << 8) : (curr << 16);
		curr |= get2BytesforCRCcalc(&m_dataSrc[m_dataLenInBytes - len], len);
		for (int j = 31; j > 15; j--) {
			// XOR curr and poly, only if jth bit is set
			if ((curr & (1 << j)))
				curr ^= poly;
			poly >>= 1;
		}
		poly = crc16_ply;
	}

	// Append 16 0s at the end and compute CRC16 again
	curr <<= 16;
	poly = crc16_ply;
	for (int j = 31; j > 15; j--) {
		// XOR curr and poly, only if jth bit is set
		if ((curr & (1 << j)))
			curr ^= poly;
		poly >>= 1;
	}

	m_crc16 = (UINT16)(curr & 0xFFFF);
}

void Data::printData() {
	std::cout << std::endl;
	for (int i = 0; i < m_dataLenInBytes; i++)
		std::printf("%x ", m_dataSrc[i] & 0xFF);
	std::cout << std::endl;
}

UINT32 Data::get2BytesforCRCcalc(UINT32 *data, UINT32 &len) {
	UINT32 curr = 0;
	if (len == 0) {
		curr = 0;
	}
	else if (len == 1) {
		curr = data[0];
		len -= 1;
	}
	else if (len >= 2) {
		curr = (data[0] << 8) | data[1];
		len -= 2;
	}
	return curr;
}

UINT32* Data::getDataPkt() {
	UINT32 *pkt = NULL;
	// PID + CRC16 =>2 and then m_dataLenInBytes
	pkt = new UINT32[m_dataLenInBytes + 2];
	pkt[0] = getPID();
	pkt[m_dataLenInBytes + 1] = getCRC16();
	memcpy(&pkt[1], m_dataSrc, m_dataLenInBytes * sizeof(UINT32));
	return pkt;
}

void Data::printDataPkt(UINT32 *pkt) {
	int i;
	std::cout << std::endl;
	for (i = 0; i < m_dataLenInBytes + 1; i++)
		std::printf("%.2x ", pkt[i]);
	std::printf("%.4x\n", pkt[i]);
	std::cout << std::endl;
}

void Data::consumeDataPkt() {
	// TODO
}


