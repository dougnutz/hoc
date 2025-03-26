## Using the ultrasonic sensor to measure distance
### Description
We will modify our code to measure the distance using the ultrasonic sensor. The ultrasonic sensor will send out a sound wave and measure the distance to the object in front of it. We will leverage a new library called Ultrasound to handle the ultrasonic sensor.It will also implement a moving average filter to smooth out the readings from the ultrasonic sensor.Then we will use the distance to control the color of the LED. If the distance is less than 80mm, the red LED will turn on. If the distance is greater than 80mm, the green LED will turn on.

### Start by declaring some variables
In the Ultrasound region we will add in include for the header and we will declare some variables for the prototypes, an instance of the Ultrasound library. We will also declare two new function prototypes.
```cpp
#include "Ultrasound.h"  //uncomment this line to add ultrasound functionality
#define FILTER_N 3 // Filter size
int Filter_Value;
int filter_buf[FILTER_N + 1];
Ultrasound ultrasound; 
// Ultrasount prototypes
int Filter(void);
int ultrasonic_distance(void);
```

In the Loop() make a call to the new function we created called ultrasonic_distance.
```cpp
ultrasonic_distance();
delay(100);  // Delay for 100ms
```

### Now we need to impliment the filter function. 
The Filter() function will implements a moving average filter:

It smooths out noise in the ultrasonic sensor's distance readings by averaging the most recent FILTER_N measurements.
This helps reduce fluctuations in the sensor data and provides a more stable output. 

Add the following code to the bottom of main.cpp
```cpp
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
```
### Now we need to implement the ultrasonic_distance function.
The ultrasonic_distance() function will read the distance from the ultrasonic sensor and print it to the serial monitor. It will also call the Filter() function to get a filtered value.  If the distance is less than 80mm, it will turn on the red LED.
```cpp
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
### Checkpoint

Upload the code and see if the red LED turns on when you put your hand in front of the ultrasonic sensor. If it does, great! If not, check your wiring and make sure you have the correct library installed.
Compare your code to Soulution1.md

### Let's add some more functionality to the ultrasonic sensor.
We will add a gradient effect to the LED based on the distance measured by the ultrasonic sensor. The LED will change color based on the distance. The closer the object is, the more red it will be. The further away it is, the more green it will be.  
We will also add a breathing effect to the LED when the distance is less than 80mm. The LED will breathe red when the object is close and green when it is far away.
#### Note
this code creates a red gradient effect based on the distance value:
When the object is closer (distance near 80), the LED is bright red.
As the object moves farther away (distance near 180), the red fades to off.

### Add the following code to the ultrasonic_distance function.
```cpp
  else if (distance > 80 && distance <= 180){
      s = map(distance,80,180,0,255);
      ultrasound.Color((255-s), 0, 0, (255-s), 0, 0);///Red gradient
  }
    
  else if (distance > 180 && distance <= 320){
      s = map(distance,180,320,0,255);
      ultrasound.Color(0, 0, s, 0, 0, s);///Blue gradient
  }
    
   else if (distance > 320 && distance <= 500){
      s = map(distance,320,500,0,255);
      ultrasound.Color(0, s, 255-s, 0, s, 255-s);///Green gradient
   }
```