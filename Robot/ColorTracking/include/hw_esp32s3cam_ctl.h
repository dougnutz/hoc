#ifndef __HW_ESP32CAM_CTL_H_
#define __HW_ESP32CAM_CTL_H_

#include <Arduino.h>
#include <Wire.h>

#define ESP32S3_ADDR 0x53

#define IMAGE_WIDTH 160
#define IMAGE_LENGTH 120

#define LINE_PATROL_REG_COUNT 7
#define FACE_DETECTION_REG_COUNT 2
#define COLOR_DETECTION_REG_COUNT 7

/*line patrol data reg*/
#define LINE_PATROL_FIRST_COLOR_REG1 0xA0 
#define LINE_PATROL_FIRST_COLOR_REG2 0xA1
#define LINE_PATROL_SECOND_COLOR_REG1 0xA2 
#define LINE_PATROL_SECOND_COLOR_REG2 0xA3
#define LINE_PATROL_THIRD_COLOR_REG1 0xA4 
#define LINE_PATROL_THIRD_COLOR_REG1 0xA5  // BUG: what should be A5?
#define LINE_PATROL_FOURTH_COLOR_REG1 0xA6 
#define LINE_PATROL_FOURTH_COLOR_REG2 0xA7
#define LINE_PATROL_FIFTH_COLOR_REG1 0xA8 
#define LINE_PATROL_FIFTH_COLOR_REG2 0xA9

/*face detection data reg*/
#define FACE_DETECTION_CENTER_REG 0xB0
#define LEFT_EYE_DETECTION_REG 0xB1
#define RIGHT_EYE_DETECTION_REG 0xB2
#define NOSE_DETECTION_REG 0xB3
#define LEFT_MOUNTH_DETECTION_REG 0xB4
#define RIGHT_MOUNTH_DETECTION_REG 0xB5

/*color detection data reg*/
#define FIRST_COLOR_INFO_REG 0xC0 ///>red
#define SECOND_COLOR_INFO_REG 0xC1 ///>yellow
#define THIRD_COLOR_INFO_REG 0xC2 ///>blue
#define FOURTH_COLOR_INFO_REG 0xC3 ///>green
#define FIFTH_COLOR_INFO_REG 0xC4 ///>black
#define ALL_COLOR_INDEX_REG 0xC5

class HW_ESP32S3CAM
{
public:
    void Init(void);
    uint16_t Linepatrol_Data_Receive(uint8_t reg, uint8_t *buf, uint16_t buf_len);
    uint16_t Facedetection_Data_Receive(uint8_t reg, uint8_t *buf, uint16_t buf_len);
    uint16_t Colordetection_Data_Receive(uint8_t reg, uint8_t *buf, uint16_t buf_len);
};

#endif