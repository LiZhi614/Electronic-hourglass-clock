#include "iic.h"


//��ʱ10us
void Delay10us()
{
	unsigned char a,b;
	for(b=1;b>0;b--)
		for(a=2;a>0;a--);

}
//��ʼ�źţ���SCLʱ�źŲ���һ���½���
//��ʼ֮��SDA��SCL��Ϊ0
void I2cStart()
{
	SDA=1;
	Delay10us();
	SCL=1;
	Delay10us();//����ʱ����SDA����ʱ��>4.7us
	SDA=0;
	Delay10us();//����ʱ����>4us
	SCL=0;			
	Delay10us();		
}
//��ֹ�źţ���SCLʱ���źŸߵ�ƽ�ڼ�SDA�źŲ���һ��������
// ����֮�󱣳�SDA��SCL��Ϊ1����ʾ���߿���
void I2cStop()
{
	SDA=0;
	Delay10us();
	SCL=1;
	Delay10us();//����ʱ�����4.7us
	SDA=1;
	Delay10us();		
}

//ͨ��I2C����һ���ֽڡ���SCLʱ���źŸߵ�ƽ�ڼ䣬���ַ����ź�SDA�����ȶ�
//0��1�����ͳɹ�����1������ʧ�ܷ���0
//������һ���ֽ�SCL=0,SDA=1
unsigned char I2c_SendByte(unsigned char dat)
{
	unsigned char a=0,b=0;//���255��һ����������Ϊ1us�������ʱ255us��		
	for(a=0;a<8;a++)//Ҫ����8λ�������λ��ʼ
	{
		SDA=dat>>7;	 //��ʼ�ź�֮��SCL=0�����Կ���ֱ�Ӹı�SDA�ź�
		dat=dat<<1;
		Delay10us();
		SCL=1;
		Delay10us();//����ʱ��>4.7us
		SCL=0;
		Delay10us();//ʱ�����4us		
	}
		SDA=1;
		Delay10us();
		SCL=1;
		while(SDA)//�ȴ�Ӧ��Ҳ���ǵȴ����豸��SDA����
		{
			b++;
			if(b>200)	 //�������2000usû��Ӧ����ʧ�ܣ�����Ϊ��Ӧ�𣬱�ʾ���ս���
			{
				SCL=0;
				Delay10us();
				return 0;
			}
		}
		SCL=0;
		Delay10us();
 		return 1;		
}

// ʹ��I2c��ȡһ���ֽ�
//������һ���ֽ�SCL=0,SDA=1.

unsigned char I2c_ReadByte()
{
	unsigned char a=0,dat=0;
	SDA=1;			//��ʼ�ͷ���һ���ֽ�֮��SCL����0
	Delay10us();
	for(a=0;a<8;a++)//����8���ֽ�
	{
		SCL=1;
		Delay10us();
		dat<<=1;
		dat|=SDA;
		Delay10us();
		SCL=0;
		Delay10us();
	}
	return dat;		
}
