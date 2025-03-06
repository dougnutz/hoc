#include <Arduino.h>
#include "Movement.h"
#include "Helper.h"


const static uint8_t keyPin = 3;  // Define the keyPin as 3
const static uint8_t TRACKING = 4;
const static uint8_t Speed=60; // robot line tracking speed

bool keyState;  //Detect button status
bool taskStart = 0;
uint8_t data;
uint8_t rec_data[4];
static uint8_t modestate = TRACKING;

// Function prototypes
void Task_Dispatcher(void);
void Tracking_Line_Task(void);
void Sensor_Receive(void);

void setup() {
  Serial.println("Mecanum wheel robot setup begin");
  Serial.begin(9600);  // Open serial port at 9600 bps

  Movement::Motor_Init();  // Initialize the motors
  Movement::Motor_Stop();

  pinMode(keyPin, INPUT);
  Helper::Init();
  Serial.println("End Setup");
}

void loop() {
  keyState = analogRead(keyPin);  // Read the keyPin and assign the value to keyState

  keyState = analogRead(keyPin);

    if (keyState == LOW && !taskStart) {
      Helper::Rgb_Show(255,255,255);
      taskStart = 1;
      delay(1000);
    } else if (keyState == LOW && taskStart) {
      taskStart = 0;
      Helper::Rgb_Show(0, 0, 0);  // Turn off the LED
      Movement::Motor_Stop();  // Stop the robot
      delay(1000);
    }


  if (taskStart) {
      Sensor_Receive();
      Task_Dispatcher();
  }
}

void Task_Dispatcher() {
  switch (modestate) {
    case TRACKING:
      Tracking_Line_Task();
      break;
  }
}

void Sensor_Receive(void) {
  Helper::ReadBytes(1, data);
  rec_data[0] = data & 0x01;
  rec_data[1] = (data >> 1) & 0x01;
  rec_data[2] = (data >> 2) & 0x01;
  rec_data[3] = (data >> 3) & 0x01;
}

void Tracking_Line_Task(void) {
  Helper::Rgb_Show(0, 100, 0);
  if (rec_data[1] == 1 && rec_data[2] == 1) {
    Movement::Velocity_Controller(0, Speed, 0, 0);
    Serial.println("Forward");
  }
  if (rec_data[1] == 1 && rec_data[2] == 0) {
    Movement::Velocity_Controller(0, Speed, 65, 0);
    Serial.println("Right");
  }
  if (rec_data[1] == 0 && rec_data[2] == 1) {
    Movement::Velocity_Controller(0, Speed, -65, 0);
    Serial.println("Left");
  }
  if (rec_data[1] == 0 && rec_data[2] == 0) {
    Sensor_Receive();
    Movement::Motor_Stop();
    delay(500);
    Helper::Rgb_Show(255, 0, 0);
    Serial.println("No line detected");
  }
}