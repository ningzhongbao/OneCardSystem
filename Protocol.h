#pragma once
#ifndef __PROTOCOL_H__
#define  __PROTOCOL_H__

struct  OPEN_DOOR_PROTO
{
	byte Begin[4];
	char AddrInfo[4];
	byte Name[9]; //Ãû×Ö
	char FaceLen[3];
	char IdCard[18];
	char End[1];
	char *FaceDate;
};





#endif // !__PROTOCOL_H__
