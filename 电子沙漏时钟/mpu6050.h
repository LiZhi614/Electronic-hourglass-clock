#ifndef __mpu6050_H_
#define __mpu6050_H_
#include <reg52.h>
#include <math.h>


typedef unsigned char  uchar;
typedef unsigned int   uint;


#define PI  3.1415926535897932


// ����MPU6050�ڲ���ַ
//****************************************
#define        SMPLRT_DIV                0x19        //�����ǲ����ʣ�����ֵ��0x07(125Hz)
#define        CONFIG                        0x1A        //��ͨ�˲�Ƶ�ʣ�����ֵ��0x06(5Hz)
#define        GYRO_CONFIG                0x1B        //�������Լ켰������Χ������ֵ��0x18(���Լ죬2000deg/s)
#define        ACCEL_CONFIG        0x1C        //���ټ��Լ졢������Χ����ͨ�˲�Ƶ�ʣ�����ֵ��0x01(���Լ죬2G��5Hz)
#define        ACCEL_XOUT_H        0x3B
#define        ACCEL_XOUT_L        0x3C
#define        ACCEL_YOUT_H        0x3D
#define        ACCEL_YOUT_L        0x3E
#define        ACCEL_ZOUT_H        0x3F
#define        ACCEL_ZOUT_L        0x40
#define        TEMP_OUT_H                0x41
#define        TEMP_OUT_L                0x42
#define        GYRO_XOUT_H                0x43
#define        GYRO_XOUT_L                0x44
#define        GYRO_YOUT_H                0x45
#define        GYRO_YOUT_L                0x46
#define        GYRO_ZOUT_H                0x47
#define        GYRO_ZOUT_L                0x48
#define        PWR_MGMT_1                0x6B        //��Դ��������ֵ��0x00(��������)
#define        WHO_AM_I                0x75        //IIC��ַ�Ĵ���(Ĭ����ֵ0x68��ֻ��)
#define        SlaveAddress        0xD0        //IICд��ʱ�ĵ�ַ�ֽ����ݣ�+1Ϊ��ȡ






unsigned char I2c_Read(uchar REG_Address);
void I2c_Write(uchar REG_Address,uchar dat);
unsigned int Read_dat(uchar REG_Address);
unsigned int Read_zf(uchar REG_Address);
void printf(uchar *s,  int temp_data);
unsigned int zfp(uchar REG_Address);
//��ʼ��
void InitMPU6050() ;
void Timer2Init();


//ȫ�ֱ��� ��ȡ�����ǲ���
extern char a[6];
extern float ax;
extern int zf;





#endif