#include "iwdg.h"


//�������Ź�
//Tout=((4��2^prer) ��rlr) /40

void Iwdg_Init(u8 prer,u16 rlr)
{
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);//�ԼĴ���IWDG_PR��IWDG_RLR ��д����:ʹ��
	IWDG_SetPrescaler(prer);//����IWDGԤ��Ƶ��4��8��16...256
	IWDG_SetReload(rlr);		//���� IWDG ��װ��ֵ����ΧΪ 0 �C 0x0FFF
	IWDG_ReloadCounter();		//���� IWDG ��װ�ؼĴ�����ֵ��װ�� IWDG ������
	IWDG_Enable();

}
//Feed IWDG ;
void IWDG_Feed(void)
{ 
IWDG_ReloadCounter();//reload 
}


