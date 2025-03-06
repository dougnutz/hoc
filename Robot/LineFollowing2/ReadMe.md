# Line Following with intersection detection
In this lesson we will build on the Line Following code from the previous lesson and add the ability to detect intersections. The robot will be able to follow a line and stop at intersections, where it can then make a decision on which direction to go next.

## Sensors
In the previous lesson we used two of the sensors out of the 4 available on the robot. In this lesson we will use all 4 sensors to detect intersections. 

### The code
To start with we will modify the `Tracking_Line_Task` to use the outer most sensors to detect an intersection and stop at the intersection. Turn the LED blue when the intersection is detected. 
```cpp
 if (rec_data[0] == 1 && rec_data[3] == 1) {  // Detect intersection
    Serial.println("Intersection detected");
    Movement::Motor_Stop();
    delay(1000); // Stop for 1 second
  }
```

## Checkpoint 1
Upload the code and make sure the robot stops at the intersection and the LED turns blue.

### Turn right and continue
Next up, now that we detected the intersection we need to turn the robot to the right to align with the new line
```cpp
  // turn right until we find the line
  do {
    delay(50);   Sensor_Receive();
    Movement::Velocity_Controller(0,Speed,-50,1);  Serial.println("Turning right");
  }
  while (rec_data[0] == 1 || rec_data[3] == 1);
```