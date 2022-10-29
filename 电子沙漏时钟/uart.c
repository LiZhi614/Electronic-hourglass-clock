#include"uart.h"
#include "reg52.h"


 char shuju[8]={'0','0','0','0','0','0','0','0'};



 void UsartInit()
{
	SCON=0X50;			//设置为工作方式1
	TMOD=0X20;			//设置计数器工作方式2
	PCON=0X80;			//波特率加倍
	TH1=0XFA;				//计数器初始值设置，注意波特率是4800的
	TL1=0XFA;
	ES=1;						//打开接收中断
	EA=1;						//打开总中断
	TR1=1;					//打开计数器
}

 

 
/*发送一个 字符*/
void send_byte(char dat){

    SBUF = dat;
    while(!TI);
    TI = 0;      
}
/*发送一个字符串*/
void send_string(char *p){

    while(*p!= '\0'){
    
        send_byte(*p);
        p++;

    }
}


void uart_interrupt() interrupt 4
{	 
	static int i;
	char dat;

	 	TR2=0;

	if(RI==1)
	{
	
	dat=SBUF;
	if(dat!='\n')
		{
	 		shuju[i++]=dat;	
		}	
	else{i=0;}

	RI=0;
	}
		TR2=1;
}
