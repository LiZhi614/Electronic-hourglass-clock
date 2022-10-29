#ifndef __mpu6050_H_
#define __mpu6050_H_
#include <reg52.h>
#include <math.h>


typedef unsigned char  uchar;
typedef unsigned int   uint;


#define PI  3.1415926535897932


// 定义MPU6050内部地址
//****************************************
#define        SMPLRT_DIV                0x19        //陀螺仪采样率，典型值：0x07(125Hz)
#define        CONFIG                        0x1A        //低通滤波频率，典型值：0x06(5Hz)
#define        GYRO_CONFIG                0x1B        //陀螺仪自检及测量范围，典型值：0x18(不自检，2000deg/s)
#define        ACCEL_CONFIG        0x1C        //加速计自检、测量范围及高通滤波频率，典型值：0x01(不自检，2G，5Hz)
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
#define        PWR_MGMT_1                0x6B        //电源管理，典型值：0x00(正常启用)
#define        WHO_AM_I                0x75        //IIC地址寄存器(默认数值0x68，只读)
#define        SlaveAddress        0xD0        //IIC写入时的地址字节数据，+1为读取






unsigned char I2c_Read(uchar REG_Address);
void I2c_Write(uchar REG_Address,uchar dat);
unsigned int Read_dat(uchar REG_Address);
unsigned int Read_zf(uchar REG_Address);
void printf(uchar *s,  int temp_data);
unsigned int zfp(uchar REG_Address);
//初始化
void InitMPU6050() ;
void Timer2Init();


//全局变量 读取陀螺仪参数
extern char a[6];
extern float ax;
extern int zf;





#endif