```cpp
#include <Arduino.h>
#include "Ultrasound.h"  //uncomment this line to add ultrasound functionality
#define FILTER_N 3 // Filter size
int Filter_Value;
int filter_buf[FILTER_N + 1];
Ultrasound ultrasound; 
// Ultrasound prototypes
int Filter(void);
int ultrasonic_distance(void);



void setup() {}

void loop() {
  ultrasonic_distance();
  delay(100);  // Delay for 100ms
}


int Filter() {
  int i;
  int filter_sum = 0;
  filter_buf[FILTER_N] = ultrasound.GetDistance();///Read the ultrasonic ranging value
  for(i = 0; i < FILTER_N; i++) {
    filter_buf[i] = filter_buf[i + 1];///Shift all data to the left, and clear the low bit
    filter_sum += filter_buf[i];
  }
  return (int)(filter_sum / FILTER_N);
}


int ultrasonic_distance(){
  uint8_t s;
  uint16_t distance = Filter();///Get the output value of the filter

  if (distance > 0 && distance <= 80){
    ultrasound.Breathing(1, 0, 0, 1, 0, 0);///Red breathing light mode, in 0.1s
}
else {
    ultrasound.Color(0, 255, 0, 0, 255, 0);///Green
}
  return distance;  
}
```