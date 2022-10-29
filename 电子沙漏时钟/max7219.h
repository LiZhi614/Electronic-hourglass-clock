#ifndef __MAX7219_H_

#define __MAX7219_H_

 #include <reg52.h>

extern int zhengfu;
extern int time;//定时时间

/*点阵函数*/
void Write_Max7219(char address,char dat);
void Write_Max7219two(char address,char dat);
void Init_MAX7219(void);
void Write_Max7219_byte(char DATA);
void Write_Max7219_bytetwo(char DATA);

void duiji();
void jianshao();
int panduan(int a,int n);
int panduanzy(int a);
int panduanyou(int a);
void xialuo(int n,int num,int hang,int hang2);
void xialuozuo(int l,int num);
 
void xianshitime();

void Timer0Init();	
#endif