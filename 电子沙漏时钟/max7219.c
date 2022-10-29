#include "max7219.h"
#include"uart.h"


sbit Max7219_pinCLK = P1^4;
sbit Max7219_pinCS  = P1^3;
sbit Max7219_pinDIN = P1^2;

sbit Max7219_pinCLK2 = P2^2;
sbit Max7219_pinCS2  = P2^1;
sbit Max7219_pinDIN2 = P2^0;






char code disp1[10][4]={
{0x00,0x1C,0x22,0x1C}, //0
{0x00,0x24,0x3E,0x20}, //1
{0x00,0x3A,0x2A,0x2E},
{0x00,0x2A,0x2A,0x3E},
{0x00,0x0E,0x08,0x3E},
{0x00,0x2E,0x2A,0x3A}, //5
{0x00,0x3E,0x2A,0x3A},
{0x00,0x02,0x02,0x3E},
{0x00,0x3E,0x2A,0x3E},
{0x00,0x2E,0x2A,0x3E},

};
char code disp2[10][4]={
{0x38,0x44,0x38,0x00}, //0
{0x04,0x7C,0x24,0x00}, //1
{0x74,0x54,0x5C,0x00},
{0x7c,0x54,0x54,0x00},
{0x7c,0x10,0x70,0x00},
{0x5c,0x54,0x74,0x00}, //5
{0x5c,0x54,0x7C,0x00},
{0x7c,0x40,0x40,0x00},
{0x7C,0x54,0x7C,0x00},
{0x7C,0x54,0x74,0x00},
};


int time;//定时时间

/*点阵*/
int hang1, hang2, hang3, hang4, hang5, hang6, hang7, hang8;
int hangtwo1=0x01, hangtwo2, hangtwo3, hangtwo4, hangtwo5, hangtwo6, hangtwo7, hangtwo8;

int code you[28]={1,4,6,9,11,16,18,20,22,25,27,29,31,33,36,38,40,42,44,46,49,51,53,55,57,59,61};

int zhengfu=0;
int liangdu=1;
int num=0,k=8;
int zy=0,zf2=0;//每两次下落的格子减1

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
void Timer0Init();	 






void Timer0Init()
{
	TMOD|=0X01;//选择为定时器0模式，工作方式1，仅用TR0打开启动。
	TH0=0XFC;	//给定时器赋初值，定时1ms
	TL0=0X18;	
	ET0=1;//打开定时器0中断允许
	EA=1;//打开总中断
	TR0=0;//打开定时器			
}
void Timer0() interrupt 1
{
//	static int i;
	int n;
	TH0=0XFC;	//给定时器赋初值，定时1ms
	TL0=0X18;
	time++;
	if(time==500)
	{
		 if(zf2!=zhengfu)
		 {duiji();
		 jianshao();
	
		 zf2=zhengfu;

		 };
		 

		if(num==1||num==4||num==9||num==16||num==25||num==36||num==49||num==64)
		k=8;
		
	
		
		n++;
		switch(n)
		{
			case 1:	if(num<64){Write_Max7219(8,hang8|0x80);}
					Write_Max7219two(8,~hang8&~0x80);					
					break;
			case 2:	if(num<49){Write_Max7219(7,hang7|0x40);Write_Max7219(8,hang8&~0x80);}
					else{
					if(panduanzy(num)){Write_Max7219(8,hang8&~0x80);xialuo(7,num,hang7,hang8);}
					if(panduanyou(num)){xialuozuo(0x40,num);}
					}
					Write_Max7219two(8,~hang8|0x80);	jianshao();	
					break;
			case 3:	if(num<36){Write_Max7219(6,hang6|0x20);Write_Max7219(7,hang7&~0x40);}
					else{
					if(panduanzy(num)){Write_Max7219(7,hang7&~0x40);xialuo(6,num,hang6,hang7);}
					if(panduanyou(num)){xialuozuo(0x20,num);}
					}
				
					break;
			case 4:	if(num<25){Write_Max7219(5,hang5|0x10);Write_Max7219(6,hang6&~0x20);}
					else{
					if(panduanzy(num)){Write_Max7219(6,hang6&~0x20);xialuo(5,num,hang5,hang6);}
					if(panduanyou(num)){xialuozuo(0x10,num);}
					}	
					break;
			case 5:	if(num<16){Write_Max7219(4,hang4|0x08);Write_Max7219(5,hang5&~0x10);}
					else{
					if(panduanzy(num)){Write_Max7219(5,hang5&~0x10);xialuo(4,num,hang4,hang5);}
					if(panduanyou(num)){xialuozuo(0x08,num);}
					
					}	
					break;
			case 6:	if(num<9){Write_Max7219(3,hang3|0x04);Write_Max7219(4,hang4&~0x08);}
					else{
					if(panduanzy(num)){Write_Max7219(4,hang4&~0x08);xialuo(3,num,hang3,hang4);}
					if(panduanyou(num)){xialuozuo(0x04,num);}					
					}	
					break;
			case 7:	if(num<4){Write_Max7219(2,hang2|0x02);Write_Max7219(3,hang3&~0x04);}
					else{	
						if(panduanzy(num)){Write_Max7219(3,hang3&~0x04);xialuo(2,num,hang2,hang3);}
						if(panduanyou(num)){xialuozuo(0x02,num);}
					
					}	
					break;
			case 8:	if(num<1){Write_Max7219(1,0x01);Write_Max7219(2,hang2&~0x02);}	
					break;

			default:	;		
		}
	
		if(n==k)
		{
		 if(num>1&&num!=4&&num!=9&&num!=16&&num!=25&&num!=36&&num!=49&&num!=64)
			zy++;
			num++;
	
		if(zy==2)
		{zy=0;k--;}
	
		
		n=0;
		if(panduan(num,1)) hang1=(hang1<<1)+1;
		if(panduan(num,2)) hang2=(hang2<<1)+1;
		if(panduan(num,3)) hang3=(hang3<<1)+1;
		if(panduan(num,4)) hang4=(hang4<<1)+1;
		if(panduan(num,5)) hang5=(hang5<<1)+1;
		if(panduan(num,6)) hang6=(hang6<<1)+1;
		if(panduan(num,7)) hang7=(hang7<<1)+1;
		if(panduan(num,8)) hang8=(hang8<<1)+1;

		if(panduan(num,1)) hangtwo1=(hangtwo1<<1)+1;
		if(panduan(num,2)) hangtwo2=(hangtwo2<<1)+1;
		if(panduan(num,3)) hangtwo3=(hangtwo3<<1)+1;
		if(panduan(num,4)) hangtwo4=(hangtwo4<<1)+1;
		if(panduan(num,5)) hangtwo5=(hangtwo5<<1)+1;
		if(panduan(num,6)) hangtwo6=(hangtwo6<<1)+1;
		if(panduan(num,7)) hangtwo7=(hangtwo7<<1)+1;
		if(panduan(num,8)) hangtwo8=(hangtwo8<<1)+1;


		
		duiji();

		
		}		
	  	time=0;
	
	  	
	}
} 



void Write_Max7219_byte(char DATA)         
{
    	char i;    
		Max7219_pinCS=0;		
	    for(i=8;i>=1;i--)
          {		  
            Max7219_pinCLK=0;
            Max7219_pinDIN=DATA&0x80;
            DATA=DATA<<1;
            Max7219_pinCLK=1;
           }                                 
}
//：向MAX7219写入数据





void Write_Max7219_bytetwo(char DATA)         
{
    	char i;    
		Max7219_pinCS2=0;		
	    for(i=8;i>=1;i--)
          {		  
            Max7219_pinCLK2=0;
            Max7219_pinDIN2=DATA&0x80;
            DATA=DATA<<1;
            Max7219_pinCLK2=1;
           }                                 
}
///////////////

void Write_Max7219(char address,char dat)
{ 	 
	 if(zhengfu==0)
	 {
     Max7219_pinCS=0;
	 Write_Max7219_byte(address);           //写入地址，即数码管编号
     Write_Max7219_byte(dat);               //写入数据，即数码管显示数字 
	 Max7219_pinCS=1;
	 }else{ Max7219_pinCS2=0;
			 Write_Max7219_bytetwo(address);           //写入地址，即数码管编号
		     Write_Max7219_bytetwo(dat);               //写入数据，即数码管显示数字 
			 Max7219_pinCS2=1;      
			 }                        
}
void Write_Max7219two(char address,char dat)
{ 	 
		if(zhengfu==0)
	 {
     Max7219_pinCS2=0;
	 Write_Max7219_bytetwo(address);           //写入地址，即数码管编号
     Write_Max7219_bytetwo(dat);               //写入数据，即数码管显示数字 
	 Max7219_pinCS2=1; 
	  }else{  Max7219_pinCS=0;
				 Write_Max7219_byte(address);           //写入地址，即数码管编号
			     Write_Max7219_byte(dat);               //写入数据，即数码管显示数字 
				 Max7219_pinCS=1;
				 }                      
}

void Init_MAX7219(void)
{

	 Write_Max7219(0x09, 0x00);       //译码方式：BCD码
	 Write_Max7219(0x0a, 0x03);       //亮度 
	 Write_Max7219(0x0b, 0x07);       //扫描界限；8个数码管显示
	 Write_Max7219(0x0c, 0x01);       //掉电模式：0，普通模式：1
	 Write_Max7219(0x0f, 0x00);       //显示测试：1；测试结束，正常显示：0
	
	 Write_Max7219two(0x09, 0x00);       //译码方式：BCD码
	 Write_Max7219two(0x0a, 0x03);       //亮度 
	 Write_Max7219two(0x0b, 0x07);       //扫描界限；8个数码管显示
	 Write_Max7219two(0x0c, 0x01);       //掉电模式：0，普通模式：1
	 Write_Max7219two(0x0f, 0x00);       //显示测试：1；测试结束，正常显示：0



}
void duiji()										 
{												     
	 Write_Max7219(1,hang1);						 
	 Write_Max7219(2,hang2);				 
	 Write_Max7219(3,hang3);
	 Write_Max7219(4,hang4);
	 Write_Max7219(5,hang5);
	 Write_Max7219(6,hang6);
	 Write_Max7219(7,hang7);
	 Write_Max7219(8,hang8);
}
void jianshao()
{

	 Write_Max7219two(1,~hangtwo1);
	 Write_Max7219two(2,~hangtwo2);
	 Write_Max7219two(3,~hangtwo3);
	 Write_Max7219two(4,~hangtwo4);
	 Write_Max7219two(5,~hangtwo5);
	 Write_Max7219two(6,~hangtwo6);
	 Write_Max7219two(7,~hangtwo7);
	 Write_Max7219two(8,~hangtwo8);
}

int panduan(int a,int n)
{

	int t=0;
	switch(n)
	{
	case 1:	if(a==1||a==2||a==5||a==10||a==17||a==26||a==37||a==50)
			t=1;
			break;
	case 2:	if(a==3||a==4||a==7||a==12||a==19||a==28||a==39||a==52)
			t=1;
			break;
	case 3:	if(a==6||a==8||a==9||a==14||a==21||a==30||a==41||a==54)
			t=1;
			break;
	case 4:	if(a==11||a==13||a==15||a==16||a==23||a==32||a==43||a==56)
			t=1;
			break;
	case 5:	if(a==18||a==20||a==22||a==24||a==25||a==34||a==45||a==58)
			t=1;
			break;
	case 6:	if(a==27||a==29||a==31||a==33||a==35||a==36||a==47||a==60)
			t=1;
			break;
	case 7:	if(a==38||a==40||a==42||a==44||a==46||a==48||a==49||a==62)
			t=1;
			break;
	case 8:	if(a==51||a==53||a==55||a==57||a==59||a==61||a==63||a==64)
			t=1;
			break;

	default:	t=0;
		}
	return t;
}
int panduanzy(int a)
{
 	int i;
	int t=0;
	for(i=0;i<28;i++)
	{
		if(a==you[i])
		t=1;
	}
	return t;

}
int panduanyou(int a)
{
 	int i;
	int t=0;
	for(i=0;i<28;i++)
	{
		if(a==you[i]+1)
		t=1;
	}
	return t;

}
void xialuo(int n,int num,int hang,int hang2)
{
	if(num>=49&&num<64)	Write_Max7219(n,hang|0x80),Write_Max7219(n+1,hang2&~0x80);	
	if(num>=36&&num<49)	Write_Max7219(n,hang|0x40),Write_Max7219(n+1,hang2&~0x40);
	if(num>=25&&num<36)	Write_Max7219(n,hang|0x20),Write_Max7219(n+1,hang2&~0x20);
	if(num>=16&&num<25)	Write_Max7219(n,hang|0x10),Write_Max7219(n+1,hang2&~0x10);
	if(num>=9&&num<16)	Write_Max7219(n,hang|0x08),Write_Max7219(n+1,hang2&~0x08);
	if(num>3&&num<9)	Write_Max7219(n,hang|0x04),Write_Max7219(n+1,hang2&~0x04);

}
void xialuozuo(int l,int num)
{
	if(num>=49&&num<64)	Write_Max7219(8,hang8|l);	
	if(num>=36&&num<49)	Write_Max7219(7,hang7|l);//Write_Max7219(7,hang7&~l<<1);
	if(num>=25&&num<36)	Write_Max7219(6,hang6|l);//Write_Max7219(6,hang6&~l<<1);
	if(num>=16&&num<25)	Write_Max7219(5,hang5|l);//Write_Max7219(5,hang5&~l<<1);
	if(num>=9&&num<16)	Write_Max7219(4,hang4|l);//Write_Max7219(4,hang4&~l<<1);
	if(num>3&&num<9)	Write_Max7219(3,hang3|l);//Write_Max7219(3,hang3&~l<<1);

}
void xianshitime()
{
	
	int i;


	if(shuju[2]==':')
	{


	for(i=1;i<5;i++) Write_Max7219two(i,(disp1[shuju[0]-0x30][i-1])); //十位  小时
	for(i=5;i<9;i++) Write_Max7219two(i,(disp1[shuju[1]-0x30][i-5]));	//个位


	for(i=5;i<9;i++)  Write_Max7219(i,(disp2[shuju[3]-0x30][i-5]));	//十位			分钟
	for(i=1;i<5;i++)  Write_Max7219(i,(disp2[shuju[4]-0x30][i-1])); //个位

	}

}



