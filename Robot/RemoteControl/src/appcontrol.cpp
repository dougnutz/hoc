/**
 * @file app_control.ino
 * @author Anonymity
 * @brief APP Control
 * @version V1.0
 * @date 2024-04-26
 *
 * @copyright Copyright (c) 2024
 *
 * @attention The main function should not include any blocking operations!
 */

#include <Arduino.h>
#include "FastLED.h"
#include <Servo.h>
#include "Ultrasound.h"

typedef enum {   
  MODE_NULL,
  MODE_ROCKERANDGRAVITY,  /* joystick & gravity control */
  MODE_RGB_ADJUST,        /* RGB adjustment */
  MODE_SPEED_CONTROL,     /* speed control */
  MODE_ULTRASOUND_SEND,   /* send ultrasonic distance to PC software */
  MODE_SERVO_CONTROL,     /* robotic gripper control */
  MODE_VOLTAGE_SEND,      /* send voltage value to app */
  MODE_AVOID              /* obstacle avoidance */
} CarMode;

typedef enum {   
  WARNING_OFF,
  WARNING_BEEP,
  WARNING_RGB,
} VoltageWarning;

typedef enum {   
  READ_VOLTAGE_ON,
  READ_VOLTAGE_OFF
} ReadVoltageState;

Servo myservo;          /* instantiate servo */
Ultrasound ultrasound;  /* instantiate ultrasonic sensor */

static VoltageWarning g_warning = WARNING_OFF; 
static CarMode g_mode = MODE_NULL; 
static ReadVoltageState g_read = READ_VOLTAGE_ON; 

static uint8_t g_state = 8;         /* receive app sub-command */
static uint8_t avoid_flag = 0;      /* obstacle avoidance mode switch flag */
static uint8_t beep_count = 0;      /* number of times of the buzzer sound */

static int car_derection = 0;       /* set the movement angle of the car */
static int8_t car_rot = 0;          /* set the angular velocity of the car */
static uint8_t speed_data = 0;      /* set the linear velocity of the car */
static uint8_t speed_update = 50;   /* the linear velocity updated via the app */

/* parameters related to voltage monitoring */
static float voltage;
static int voltage_send;
static int last_voltage_send;
static int real_voltage_send;
static int error_voltage;

static CRGB rgbs[1];
String rec_data[4];                 /* receive the data sent from the app */

const char *charArray;

/* define pins */
const static uint8_t ledPin = 2;
const static uint8_t buzzerPin = 3;
const static uint8_t servoPin = 5;
const static uint8_t motorpwmPin[4] = { 10, 9, 6, 11} ;
const static uint8_t motordirectionPin[4] = { 12, 8, 7, 13};

const static int pwmFrequency = 500;                /* the PWM frequency in units of Hz */
const static int period = 10000000 / pwmFrequency;  /* the PWM period in units of microseconds */
const static uint32_t interval_us = 20000;          /* the microsecond count interval employed for non-blocking delays */
const static uint32_t interval_ms = 1000;           /* the millisecond count interval employed for non-blocking delays */

static uint32_t previousTime_us = 0;          /* the previous microsecond count interval for non-blocking delays */
static uint32_t previousTime_ms = 0;          /* the previous millisecond count interval for non-blocking delays */ 

static int servo_angle = 0;                   /* set servo angle */
static uint16_t distance = 0;                 /* distance measured by the ultrasonic sensor */

void Aovid(void);
void Rgb_Task(void);
void Motor_Init(void);
void Speed_Task(void);
void Task_Dispatcher(void);
void Servo_Data_Receive(void);
void Rockerandgravity_Task(void);
void Voltage_Detection_Task(void);
void PWM_Out(uint8_t PWM_Pin, int8_t DutyCycle);
void Rgb_Show(uint8_t rValue,uint8_t gValue,uint8_t bValue);
void Velocity_Controller(uint16_t angle, uint8_t velocity,int8_t rot);
void Motors_Set(int8_t Motor_0, int8_t Motor_1, int8_t Motor_2, int8_t Motor_3);

void setup() {
  Serial.begin(9600);
  FastLED.addLeds<WS2812, ledPin, RGB>(rgbs, 1);
  Motor_Init();
  pinMode(servoPin, OUTPUT);
  myservo.attach(servoPin);                   /* bind specific servo pin */
  myservo.write(servo_angle);                 /* write servo angle */
  tone(buzzerPin, 1200);                      /* function for inputting tone signal with a frequency of 1200 */ 
  delay(100);
  noTone(buzzerPin);
  voltage_send = analogRead(A3)*0.02989*1000;   /* calculate voltage */ 
  last_voltage_send = voltage_send;
  real_voltage_send = voltage_send;
}

void loop() {
  Velocity_Controller(car_derection, speed_data, car_rot);
  Task_Dispatcher();
  if(g_read == READ_VOLTAGE_ON)
  {
    Voltage_Detection_Task();
  }
}

/**
 * @brief set the color of RGB LED
 * @param rValue;gValue;bValue;
 * @arg the three input parameters range from 0 to 255
 * @retval None
 * @note (255,0,0) green (0,255,0) red (0,0,255) blue (255,255,255) white
 */
void Rgb_Show(uint8_t rValue,uint8_t gValue,uint8_t bValue) 
{
  rgbs[0].r = rValue;
  rgbs[0].g = gValue;
  rgbs[0].b = bValue;
  FastLED.show();
}

/* task dispatcher */
void Task_Dispatcher(void) 
{
  uint8_t index = 0;
  while (Serial.available() > 0) 
  {
    String cmd = Serial.readStringUntil('$');
    while (cmd.indexOf('|') != -1) 
    {
      rec_data[index] = cmd.substring(0, cmd.indexOf('|'));  /* extract the substring from the begining to the bit before the first comma */
      cmd = cmd.substring(cmd.indexOf('|') + 1);             /* update the string by removing the extracted substring and the comma */
      index++;      /* update index */
    }
    charArray = rec_data[0].c_str();      /* convert to c string format */
    if(strcmp(charArray, "A") == 0 && avoid_flag == 0)  /* determine command  */ 
    {
        g_mode = MODE_ROCKERANDGRAVITY;
    }
    if(strcmp(charArray, "B") == 0 && avoid_flag == 0) 
    {
      g_mode = MODE_RGB_ADJUST;
    }
    if(strcmp(charArray, "C") == 0 && avoid_flag == 0) 
    {
      g_mode = MODE_SPEED_CONTROL;
    }
    if(strcmp(charArray, "E") == 0 && avoid_flag == 0) 
    {
      g_mode = MODE_SERVO_CONTROL;
    }
    if(strcmp(charArray, "D") == 0) 
    {
      g_mode = MODE_ULTRASOUND_SEND;
    } 
    if(strcmp(charArray, "F") == 0) 
    {
      g_mode = MODE_AVOID;
      avoid_flag = 1;
      g_state = atoi(rec_data[1].c_str());
    }    
  }
  if(g_mode == MODE_ROCKERANDGRAVITY)
  {
    Rockerandgravity_Task();
    g_mode = MODE_NULL;
  }
  if(g_mode == MODE_RGB_ADJUST)
  {
    Rgb_Task();
    g_mode = MODE_NULL;
  }
  if(g_mode == MODE_SPEED_CONTROL)
  {
    Speed_Task();
    g_mode = MODE_NULL;
  }
  if(g_mode == MODE_SERVO_CONTROL)
  {
    Servo_Data_Receive();
    g_mode = MODE_NULL;
  }
  if(g_mode == MODE_ULTRASOUND_SEND)
  {
    distance = ultrasound.Filter();   /* obtain the output value of the filter */
    if(distance > 5000)
    {
      distance = 5000;
    }
    voltage_send = (int)(voltage*1000);
    if(last_voltage_send - voltage_send >= 500)
    {
      error_voltage = voltage_send;
    }
    if(voltage_send != error_voltage)
    {
      real_voltage_send = voltage_send;
    }
    last_voltage_send = voltage_send;

    /* send ultrasonic distance data and voltage data to the app */
    Serial.print("$");Serial.print(distance);Serial.print(",");
    Serial.print(real_voltage_send);Serial.print("$");
    g_mode = MODE_NULL;
  }
  if(avoid_flag == 1)
  {
    Aovid();
  }
  if(g_state == 8)
  {
    g_read = READ_VOLTAGE_ON;
  }
  else
  {
    g_read = READ_VOLTAGE_OFF;
  }
}

/* joystick control task */
void Rockerandgravity_Task(void) 
{
  g_state = atoi(rec_data[1].c_str());
  switch (g_state) 
  {
    case 0: 
      car_derection = 90;
      car_rot = 0;
      speed_data = speed_update;
      break;
    case 1: 
      car_derection = 45;
      car_rot = 0;
      speed_data = speed_update;
      break;  
    case 2: 
      car_derection = 0;
      car_rot = 0;
      speed_data = speed_update;
      break;  
    case 3: 
      car_derection = 315;
      car_rot = 0;
      speed_data = speed_update;
      break;
    case 4: 
      car_derection = 270;
      car_rot = 0;
      speed_data = speed_update;
      break;  
    case 5: 
      car_derection = 225;
      car_rot = 0;
      speed_data = speed_update;
      break;
    case 6: 
      car_derection = 180;
      car_rot = 0;
      speed_data = speed_update;
      break; 
    case 7: 
      car_derection = 135;
      car_rot = 0;
      speed_data = speed_update;
      break;
    case 8: 
      car_derection = 0;
      car_rot = 0;
      speed_data = 0;
      break;
    case 9: 
      car_derection = 0;
      speed_data = 0;
      car_rot = speed_update;
      break;
    case 10: 
      car_derection = 0;
      speed_data = 0;
      car_rot = -speed_update;
      break; 
    default:
      break;     
  }
}

/* ultrasonic RGB adjustment function */
void Rgb_Task(void) 
{
  uint8_t r_data,g_data,b_data;
  r_data = (uint8_t)atoi(rec_data[1].c_str());  
  g_data = (uint8_t)atoi(rec_data[2].c_str());
  b_data = (uint8_t)atoi(rec_data[3].c_str());
  ultrasound.Color(r_data,g_data,b_data,r_data,g_data,b_data);
}

/* voltage monitoring */
void Voltage_Detection_Task(void)
{
  uint32_t currentTime_ms;
  currentTime_ms = millis();
  voltage = analogRead(A3)*0.02989;   /* calculate voltage */
  if(real_voltage_send <= 7000) 
  {
    if(g_warning != WARNING_RGB)
    {
      g_warning = WARNING_BEEP;
    }
  }
  if(g_warning == WARNING_BEEP)
  {
    if(currentTime_ms - previousTime_ms <= interval_ms/2)
    {
      tone(buzzerPin, 800);  /* If the voltage is less than 7V, the buzzer will alarm */
    }
    else if (currentTime_ms - previousTime_ms > interval_ms/2 && currentTime_ms - previousTime_ms < interval_ms)
    {
      noTone(buzzerPin); 
    }
  }
  if (currentTime_ms - previousTime_ms >= interval_ms)
  {
    if(g_warning == WARNING_BEEP)
    {
      beep_count++;
    }
    
    previousTime_ms = currentTime_ms;
  }
  if(beep_count == 2)
  {
    beep_count = 0;
    noTone(buzzerPin);
    g_warning = WARNING_RGB;
  }
  if(g_warning == WARNING_RGB)
  {
    Rgb_Show(0,10,0);
  }
}

/* robotic gripper control task */
void Servo_Data_Receive(void)
{
  servo_angle = atoi(rec_data[1].c_str());
  myservo.write(servo_angle);
}

/* obstacle avoidance mode */
void Aovid(void)
{
  distance = ultrasound.Filter();
  if(g_state == 1)
  {
    if(distance < 400)
    {
      car_derection = 0;
      car_rot = 100;
      speed_data = 0;
    }
    if(distance >= 500)
    {
      car_derection = 0;
      car_rot = 0;
      speed_data = 60;
    }
  }
  else if(g_state == 0)
  {
    car_derection = 0;
    car_rot = 0;
    speed_data = 0;
    g_mode = NULL;
    avoid_flag = 0;
  }
}
/* speed control function */
void Speed_Task(void) 
{
  speed_update = (uint8_t)atoi(rec_data[1].c_str());
  Serial.print("C|");Serial.print(speed_update); Serial.print("|$");
}

/* servo initialization function */
void Motor_Init(void)
{
  for(uint8_t i = 0; i < 4; i++) {
    pinMode(motordirectionPin[i], OUTPUT);
    pinMode(motorpwmPin[i], OUTPUT);
  }
  Velocity_Controller( 0, 0, 0);
}

/**
 * @brief speed control function
 * @param angle   Controls the movement direction of the car, with 0 degrees being the direction of the front of the car, and counter-clockwise as the positive direction
 *                ranging from 0 to 359
 * @param velocity   Controls the speed of the car, ranging from 0 to 100
 * @param rot     Controls the rotational speed of the car, ranging from -100 to 100
 *                 If it is greater than 0, the car has a rotational speed in counter-clockwise direction; if it is less than 0, the car has a rotational speed in clockwise direction
 * @param drift   Determines whether to enable the drift function with the value 0 or 1.  If it is 0, enable the function; if not, disable the function
 * @retval None
 */
void Velocity_Controller(uint16_t angle, uint8_t velocity,int8_t rot) 
{
  int8_t velocity_0, velocity_1, velocity_2, velocity_3;
  float speed = 1;
  angle += 90;
  float rad = angle * PI / 180;
  if (rot == 0) speed = 1;///< speed factor
  else speed = 0.5; 
  velocity /= sqrt(2);
  velocity_0 = (velocity * sin(rad) - velocity * cos(rad)) * speed + rot * speed;
  velocity_1 = (velocity * sin(rad) + velocity * cos(rad)) * speed - rot * speed;
  velocity_2 = (velocity * sin(rad) - velocity * cos(rad)) * speed - rot * speed;
  velocity_3 = (velocity * sin(rad) + velocity * cos(rad)) * speed + rot * speed;
  Motors_Set(velocity_0, velocity_1, velocity_2, velocity_3);
}
 
/**
 * @brief the function for setting PWM and wheel direction
 * @param Motor_x   The control value for PWM and motor direction. It is calculated based on the kinematic analysis of the Mecanum wheels
 * @retval None
 */
void Motors_Set(int8_t Motor_0, int8_t Motor_1, int8_t Motor_2, int8_t Motor_3) 
{
  int8_t pwm_set[4];
  int8_t motors[4] = { Motor_0, Motor_1, Motor_2, Motor_3};
  bool direction[4] = { 1, 0, 0, 1};///< forward, left 1, and right 0
  for(uint8_t i; i < 4; ++i) 
  {
    if(motors[i] < 0) direction[i] = !direction[i];
    else direction[i] = direction[i];

    if(motors[i] == 0) pwm_set[i] = 0;
    else pwm_set[i] = abs(motors[i]);

    digitalWrite(motordirectionPin[i], direction[i]); 
    PWM_Out(motorpwmPin[i], pwm_set[i]);
  }
}

/* simulate PWM output */
void PWM_Out(uint8_t PWM_Pin, int8_t DutyCycle)
{ 
  uint32_t currentTime_us = micros();
  int highTime = (period/100) * DutyCycle;


  if ((currentTime_us - previousTime_us) <= highTime) 
  {  
    digitalWrite(PWM_Pin, HIGH);
  }
  else digitalWrite(PWM_Pin, LOW);
  if (currentTime_us - previousTime_us >= period) 
  {
    previousTime_us = currentTime_us;
  }
}