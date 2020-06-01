#pragma once

#include<iostream>

#include"fieldDefs.h"
#include"crc_n.h"

/* Token packets = SETUP, OUT, IN, SOF */
class Token {
	UINT32 m_pid;
	UINT32 m_addr;
	UINT32 m_ep;
	UINT32 m_frameNo;
	UINT32 m_crc5;

public:
	Token() {
		m_pid = 0;
		m_addr = 0;
		m_ep = 0;
		m_crc5 = 0;
	}
	Token(UINT8 pid, UINT8 addr, UINT8 ep) {
		setPID(pid);
		setAddr(addr);
		setEP(ep);
	}
	Token(UINT8 pid, UINT16 frameNo) {
		setPID(pid);
		setFrameNo(frameNo);
	}

	/* set functions */
	void setPID(UINT8 pid) { pid &= 0xF; m_pid = pid | pid << 4; setCRC5(); }
	void setAddr(UINT8 addr) { m_addr = (addr & 0x7F); setCRC5(); }
	void setEP(UINT8 ep) { m_ep = (ep & 0xF); setCRC5(); }
	void setFrameNo(UINT16 frameNum) { m_frameNo = (frameNum & 0x7FF); setCRC5(); }
	void setCRC5();

	/* get functions */
	UINT8 getPID() const { return (m_pid & 0xF); }
	UINT8 getAddr() { return (m_addr & 0x7F); }
	UINT8 getEP() { return (m_ep & 0xF); }
	UINT16 getFrameNo() { return (m_frameNo & 0x7FF); }
	UINT8 getCRC5() { return (m_crc5 & 0x1F); }

	/* Other functions */
	UINT32 getTokenPkt();
	UINT32 consumeTokenPkt(Token tkn);
};

/* Handshake packets = ACK, NAK, STALL, NYET */
class Handshake {
	UINT32 m_pid;

public:
	Handshake() { setPID(0); }
	Handshake(UINT8 pid) { setPID(pid); }

	/* set and get functions */
	void setPID(UINT8 pid) { pid &= 0xF; m_pid = pid | pid << 4;}
	UINT8 getPID() const { return (m_pid & 0xF); }

	/* Other functions */
	UINT8 getHandshakePkt();
	UINT8 consumeHandshakePkt(Handshake pkt);
};

/* DATA packets = DATA0, DATA1, DATA2, MDATA */
class Data {
	UINT8 m_pid;
	UINT32 m_dataLenInBytes;
	UINT32 *m_dataSrc;
	UINT16 m_crc16;

public:
	Data() { m_pid = 0; m_dataLenInBytes = 0; m_dataSrc = NULL; m_crc16 = 0; }
	Data(UINT8 pid) {
		setPID(pid);
		m_dataLenInBytes = 0;
		m_dataSrc = NULL;
		m_crc16 = 0;
	}
	~Data() { delete m_dataSrc; }

	/* set and get functions */
	void setPID(UINT8 pid) { pid &= 0xF; m_pid = pid | pid << 4; setCRC16(); }
	void setData(UINT32 *dataPtr, UINT32 lenInBytes);
	void setCRC16();
	UINT8 getPID() const { return (m_pid & 0xF); }
	UINT32 *getDataPtr() const { return m_dataSrc; }
	UINT32 getDataLen() const { return m_dataLenInBytes; }
	UINT32 getCRC16() const { return (m_crc16 & 0xFFFF); }
	/* Print Data */
	void printData();

	UINT32 *getDataPkt();
	void consumeDataPkt();

private:
	UINT32 get2BytesforCRCcalc(UINT32 *data, UINT32 &len);
};

