//---------------------------------------------------------------------------------
//
//								  W25X80测试程序（.C）
//				 功能：在某些地址写入一些数字，再读出来并在数码管上显示出来		
//				 连接：J3的3和5短接											
//						 	    2011年2月24日
//---------------------------------------------------------------------------------

#include "W25X80Driver.h"
#include "SMGDriver.h"
#include <C8051F320.H>

//=================================================================================
//                                   内部函数定义
//=================================================================================
//---------------------------------------------------
//函数功能：设置系统时钟
//---------------------------------------------------
void SYSCLK_Init ()
{  
	OSCICN = 0x83; 
}
//---------------------------------------------------
//函数功能：配置交叉开关，设置输入输出方式
//---------------------------------------------------    
void Port_Init()
{                   
	W25X80_Port_Init();
	SMG_Port_Init();				 
}
//---------------------------------------------------
//函数功能：延时函数
//---------------------------------------------------
void delay(long n)                 
{
   	long i;
   	while(n--)
   		for (i=0;i<12000;i++);
}
//------------------------------------------------------------------------------------------

//=================================================================================
//                                   主函数定义
//=================================================================================
void main()
{
	unsigned char count,dat;
	PCA0MD &= ~0x40;
	SYSCLK_Init();
	Port_Init();
	while(1)
	{
		ChipErase();
		while(1)
			for(count=0;count<16;count++)
			{
				ProgramFlash(count,&count,1);
				ReadFlash(count,&dat,1);
				lightSMG(0x01,dat);
				delay(10);
			}
	}	
}