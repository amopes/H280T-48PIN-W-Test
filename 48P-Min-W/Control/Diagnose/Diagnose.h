
//���Ⱪ©����
#ifndef __DIAGNOSE_PUB_H__
#define __DIAGNOSE_PUB_H__
#include "Sys_Cofig.h"


//1,3 18,19
typedef struct 
{
	ULL MOS0_ST: 1; //MOS0
	ULL MOS2_ST: 1; //MOS2S
	ULL MOS4_ST: 1; //MOS4
	ULL MOS5_ST: 1; //MOS5
	ULL MOS6_ST: 1; //MOS6
	ULL MOS7_ST: 1; //MOS7
	ULL MOS8_ST: 1; //MOS8
	ULL MOS9_ST: 1; //MOS9
	ULL MOS17_ST: 1; //MOS17
	ULL MOS16_ST: 1; //MOS16
	ULL MOS15_ST: 1; //MOS15
	ULL MOS14_ST: 1; //MOS14
	ULL MOS13_ST: 1; //MOS13
	ULL MOS12_ST: 1; //MOS12
	ULL MOS11_ST: 1; //MOS11
	ULL MOS10_ST: 1; //MOS10

} MOS_ST_PCA_t;


void IO_PCA_ST();	
extern MOS_ST_PCA_t		MOS_ST_PCA;
#endif

