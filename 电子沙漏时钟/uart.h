#ifndef __UART_H_
#define __UART_H_


 



void send_string(char *p);
void send_byte(char dat);
void UsartInit();

//全局变量 读取时间
extern char shuju[8];

#endif