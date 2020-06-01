#pragma once

typedef unsigned int UINT32;
typedef short int UINT16;
typedef char UINT8;

#define PID_TOKEN_OUT		0x1
#define PID_TOKEN_IN		0x9
#define PID_TOKEN_SOF		0x5
#define PID_TOKEN_SETUP		0xD

#define PID_DATA_DATA0		0x3
#define PID_DATA_DATA1		0xB
#define PID_DATA_DATA2		0x7
#define PID_DATA_MDATA		0xF

#define PID_HANDSHAKE_ACK	0x2
#define PID_HANDSHAKE_NAK	0xA
#define PID_HANDSHAKE_STALL	0xE
#define PID_HANDSHAKE_NYET	0x6

#define PID_SPECIAL_PRE		0xC
#define PID_SPECIAL_ERR		0xC
#define PID_SPECIAL_SPLIT	0x8
#define PID_SPECIAL_PING	0x4
#define PID_SPECIAL_RSVD	0x0
