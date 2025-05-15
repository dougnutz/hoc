#include <Wire.h>
#include "Ultrasound.h"

#define FILTER_N 3                //递推平均滤波法(recursive averaging filter)
int filter_buf[FILTER_N + 1];

Ultrasound::Ultrasound()
{
  Wire.begin();
}

//写字节(write a byte)
bool Ultrasound::wireWriteByte(uint8_t addr, uint8_t val)
{
    Wire.beginTransmission(addr);
    Wire.write(val);
    if( Wire.endTransmission() != 0 ) 
    {
        return false;
    }
    return true;
}

//写多个字节(write multiple bytes)
bool Ultrasound::wireWriteDataArray(uint8_t addr, uint8_t reg,uint8_t *val,unsigned int len)
{
    unsigned int i;

    Wire.beginTransmission(addr);
    Wire.write(reg);
    for(i = 0; i < len; i++) 
    {
        Wire.write(val[i]);
    }
    if( Wire.endTransmission() != 0 ) 
    {
        return false;
    }
    return true;
}



//读指定长度字节(read bytes of specific length)
int Ultrasound::wireReadDataArray(uint8_t addr, uint8_t reg, uint8_t *val, unsigned int len)
{
    unsigned char i = 0;  
    /* Indicate which register we want to read from */
    if (!wireWriteByte(addr, reg)) 
    {
        return -1;
    }
    Wire.requestFrom(addr, len);
    while (Wire.available()) 
    {
        if (i >= len) 
        {
            return -1;
        }
        val[i] = Wire.read();
        i++;
    }
    /* Read block data */    
    return i;
}

//设置超声波rgb为呼吸灯模式(configure the RGB lights on the ultrasonic sensor in a breathing mode)
//r1，g1，b1表示右边rgb灯的呼吸周期，例如20，20，20，表示2s一个周期(r1, g1, and b1 represent the breathing period of the right RGB light; for example, 20, 20, 20, indicating a 2-second cycle)
//r2，g2，b2表示左边rgb灯的呼吸周期(r2, g2, and b2 denote the breathing period of the left RGB light)
void Ultrasound::Breathing(uint8_t r1, uint8_t g1, uint8_t b1, uint8_t r2, uint8_t g2, uint8_t b2)
{
  uint8_t breathing[6]; 
  uint8_t value = RGB_WORK_BREATHING_MODE;
  
  wireWriteDataArray(ULTRASOUND_I2C_ADDR, RGB_WORK_MODE, &value, 1);
  breathing[0] = r1;breathing[1] = g1;breathing[2] = b1;//RGB1 蓝色(blue)
  breathing[3] = r2;breathing[4] = g2;breathing[5] = b2;//RGB2
  wireWriteDataArray(ULTRASOUND_I2C_ADDR, RGB1_R_BREATHING_CYCLE,breathing,6); //发送颜色值(send color value)
}

//设置超声波rgb灯的颜色(set the color of the RGB lights on the ultrasonic sensor)
//r1，g1，b1表示右边rgb灯的三原色的比例，范围0-255(r1, g1, and b1 represent the proportions of the primary colors for the right RGB light, ranging from 0 to 255)
//r2，g2，b2表示左边rgb灯的三原色的比例，范围0-255(r2, g2, and b2 represent the proportions of the primary colors for the left RGB light, ranging from 0 to 255)
void Ultrasound::Color(uint8_t r1, uint8_t g1, uint8_t b1, uint8_t r2, uint8_t g2, uint8_t b2)
{
  uint8_t RGB[6]; 
  uint8_t value = RGB_WORK_SIMPLE_MODE;
  
  wireWriteDataArray(ULTRASOUND_I2C_ADDR, RGB_WORK_MODE,&value,1);
  RGB[0] = r1;RGB[1] = g1;RGB[2] = b1;//RGB1
  RGB[3] = r2;RGB[4] = g2;RGB[5] = b2;//RGB2
  wireWriteDataArray(ULTRASOUND_I2C_ADDR, RGB1_R,RGB,6);
}

//获取超声波测得的距离单位mm(obtain the detected distance from the ultrasonic sensor in units of mm)
u16 Ultrasound::GetDistance()
{
  u16 distance;
  wireReadDataArray(ULTRASOUND_I2C_ADDR, 0,(uint8_t *)&distance,2);
  return distance;
}

int Ultrasound::Filter() {
  int i;
  int filter_sum = 0;
  filter_buf[FILTER_N] = GetDistance();/* 读取超声波测值(read ultrasonic detection value) */
  for(i = 0; i < FILTER_N; i++) {
    filter_buf[i] = filter_buf[i + 1];/* 所有数据左移，低位扔掉(shift all data to the left and remove the low bits) */
    filter_sum += filter_buf[i];
  }
  return (int)(filter_sum / FILTER_N);
}
