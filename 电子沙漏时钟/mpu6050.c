#include "mpu6050.h"
#include "iic.h"
#include "reg52.h"
#include "math.h"

float ax;
char a[6];
int zf;

void I2c_Write(uchar REG_Address,uchar dat)
{
 	I2cStart();
	I2c_SendByte(SlaveAddress);
	I2c_SendByte(REG_Address);
	I2c_SendByte(dat);
	I2cStop();
	
}
unsigned char I2c_Read(uchar REG_Address)
{
	uchar REG_dat;
 	I2cStart();
	I2c_SendByte(SlaveAddress);
	I2c_SendByte(REG_Address);
	I2cStart();
	I2c_SendByte(SlaveAddress+1	);
	REG_dat=I2c_ReadByte();	
	I2cStop();
	return 	REG_dat;
	
}

void InitMPU6050() 	
{
	I2c_Write(SMPLRT_DIV,0x07);	
	I2c_Write(CONFIG,0x06);	
	I2c_Write(GYRO_CONFIG,0x18);	
	I2c_Write(ACCEL_CONFIG,0x01);	
	I2c_Write(PWR_MGMT_1,0x00);	
}

unsigned int Read_dat(uchar REG_Address)
{
        char H,L;
        H=I2c_Read(REG_Address);
        L=I2c_Read(REG_Address+1);
	return (H<<8)+L; 
//		if((H<<8)+L<0)	  
//        return -(H<<8)+L;   //合成数据
//		else  return (H<<8)+L; 
	 
}



 void printf(uchar *s,  int temp_data)
{	
	
		temp_data=temp_data/10;
        if(temp_data<0)
        {
                temp_data=-temp_data;
                *s='-';
			
        }
        else 
		*s=' ';
	
		temp_data=temp_data%1000000;
        *++s =temp_data/100000+0x30;
		 temp_data=temp_data%100000;      //取余运算
        *++s =temp_data/10000+0x30;
		temp_data=temp_data%10000;      //取余运算
        *++s =temp_data/1000+0x30;
		temp_data=temp_data%1000;      //取余运算
        *++s =temp_data/100+0x30;
			temp_data=temp_data%100;      //取余运算
        *++s =temp_data/10+0x30;
			temp_data=temp_data%10;      //取余运算
        *++s =temp_data+0x30;
}
unsigned int zfp(uchar REG_Address)
{
        char H,L;
        H=I2c_Read(REG_Address);
        L=I2c_Read(REG_Address+1);
		if((H<<8)+L<0)	  
        return 0;   //合成数据
		else  return 1; 
//	 
}



void Timer2Init()
{
	T2MOD|=0X10;//选择为定时器0模式，工作方式1，仅用TR0打开启动。

	RCAP2H=TH2=0XFC;	//给定时器赋初值，定时1ms
	RCAP2L=TL2=0X18;	
	ET2=1;//打开定时器0中断允许
	EA=1;//打开总中断
	TR2=1;//打开定时器			
}

void Timer2() interrupt 5
{

	static int i;
	TF2=0;
	RCAP2H=TH2=0XFC;	//给定时器赋初值，定时1ms
	RCAP2L=TL2=0X18;
	i++;
	if(i==100)
	{
	ax=Read_dat(ACCEL_XOUT_H)/180;
	zf=zfp( ACCEL_XOUT_H);
//	printf(a,ax);
	i=0;		
	}	
}
