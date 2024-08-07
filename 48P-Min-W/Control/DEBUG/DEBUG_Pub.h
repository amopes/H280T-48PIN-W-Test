
//对外暴漏函数
#ifndef __DEBUG_PUB_H__
#define __DEBUG_PUB_H__

void FT_printf(int D1,int D2,int D3,int D4,int D5,int D6);

void MOS_PWM_Test(void);
void TEst_Can(void);
void EEPROM_Test(void);
void PCA_Test(void);
void Functional_Debug(void); //功能性调试 TEST
#endif

