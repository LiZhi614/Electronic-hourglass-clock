#include"reg52.h"
#include "uart.h"
#include "mpu6050.h"
#include "iic.h"
#include "max7219.h"

sbit WIFI = P1^7;

 void main()
{	
	int i;
	/*���ڳ�ʼ��*/
	UsartInit();
	/*�����Ƕ�ʱ��2��ʼ��*/
	InitMPU6050() ;
	Timer2Init();
	 /*�����ʼ��*/
	 Init_MAX7219();  
	 /*��ʱɳ©��ʼ��*/
	 Timer0Init();	 
	/*�ж����ȼ�*/
		WIFI=1;	
	
	 for(i=1;i<9;i++) Write_Max7219(i,0x00),Write_Max7219two(i,0x00);
	jianshao();
   while(1)
   {
  			 if(ax>85&&zf==1) {zhengfu=1;
			 						ES=0;
							
							if(TR0!=1)	duiji(),jianshao();
							TR0=1;}
			else if(ax>80&&zf==0) {zhengfu=0;
										ES=0;
								
								if(TR0!=1)	duiji(),jianshao();
								TR0=1;}
	  	else  {	
			//	if(TR0!=0)	for(i=1;i<9;i++) Write_Max7219(i,0x00),Write_Max7219two(i,0x00);
					if(TR0!=0){	for(i=1;i<9;i++) Write_Max7219(i,0x00),Write_Max7219two(i,0x00);
								TR0=0;
								ES=1;
								zhengfu=0;
									}
				xianshitime();
			
				}
//	send_string(a);
 	} 
}


