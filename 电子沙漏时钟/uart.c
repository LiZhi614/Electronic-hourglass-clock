#include"uart.h"
#include "reg52.h"


 char shuju[8]={'0','0','0','0','0','0','0','0'};



 void UsartInit()
{
	SCON=0X50;			//����Ϊ������ʽ1
	TMOD=0X20;			//���ü�����������ʽ2
	PCON=0X80;			//�����ʼӱ�
	TH1=0XFA;				//��������ʼֵ���ã�ע�Ⲩ������4800��
	TL1=0XFA;
	ES=1;						//�򿪽����ж�
	EA=1;						//�����ж�
	TR1=1;					//�򿪼�����
}

 

 
/*����һ�� �ַ�*/
void send_byte(char dat){

    SBUF = dat;
    while(!TI);
    TI = 0;      
}
/*����һ���ַ���*/
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
