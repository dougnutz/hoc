#include "hw_esp32s3cam_ctl.h"

static bool Wire_Write_Data_Array(uint8_t addr,
                                  uint8_t reg,
                                  uint8_t *val, 
                                  uint16_t len)
{
   uint16_t i;
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

static bool Wire_Write_Byte(uint8_t val)
{
    Wire.beginTransmission(ESP32S3_ADDR);
    Wire.write(val);
    if( Wire.endTransmission() != 0 ) {
        return false;
    }
    return true;
}

static int Wire_Read_Data_Array(uint8_t reg, 
                                uint8_t *val, 
                                uint16_t len)
{
    uint16_t i = 0;
    
    /* Indicate which register we want to read from */
    if (!Wire_Write_Byte(reg)) {
        return -1;
    }
    
    /* Read block data */
    Wire.requestFrom(ESP32S3_ADDR, len);
    while (Wire.available()) {
        if (i >= len) {
            return -1;
        }
        val[i] = Wire.read();
        i++;
    }   
    return i;
}

void HW_ESP32S3CAM::Init()
{
    Wire.setClock(100000);
    Wire.begin();
}

uint16_t HW_ESP32S3CAM::Linepatrol_Data_Receive(uint8_t reg, uint8_t *buf, uint16_t buf_len)
{
    return Wire_Read_Data_Array(reg, buf, buf_len);
}

uint16_t HW_ESP32S3CAM::Facedetection_Data_Receive(uint8_t reg, uint8_t *buf, uint16_t buf_len)
{
    return Wire_Read_Data_Array(reg, buf, buf_len);
}

uint16_t HW_ESP32S3CAM::Colordetection_Data_Receive(uint8_t reg, uint8_t *buf, uint16_t buf_len)
{
    return Wire_Read_Data_Array(reg, buf, buf_len);
}

