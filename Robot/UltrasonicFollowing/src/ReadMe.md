# Following an object using the ultrasonic sensor
We will begine where we left off in the ultrasonic sensor tutorial. We will use the ultrasonic sensor to detect the distance to an object and then use the motor to follow the object. If our range is less than 200 we will stop. If greater than 200 but less than 700 we will move forward. If greater than 700 we will also stop.


## Let look at the top of the main.cpp file


You will also notice that we have added back some familiar constants that we use to control the motor.
```cpp
// Constants
const static uint8_t pwm_min = 50;
const static uint8_t motorpwmPin[4] =  { 11,9,6,10 };  ///pins for controlling the motor speed
const static uint8_t motordirectionPin[4] = { 13,8,7,12 };  ///pins for controlling the motor direction
```

Next we look at our prototypes for the distance function. We created a function that get the distance as a return value from the ultrasonic sensor. We will also need a variable to store the distance. We will add the following line of code just above the function prototypes:

```cpp
uint16_t dis;
```
### Setup Function
Next we will take a look at the setup function. We see the familiar motorInit() and MotorStop() functions. 

## Checkpoint 1
We should ba able to compile the code and upload it to the board. We should see the familiar behavior of the previous tutorial. The lights on the ultrasonic sensor will change color based on the distance to the object
See solution1.md for the complete code.


### Loop Function
Lets take a look at the loop function. We see the familiar ultrasonic_distance() function that we created in the previous tutorial. We will need to assign the dis value to the return value of the ultrasonic_distance() function. We will add the following line of code to the loop function:
```cpp
dis = ultrasonic_distance();
```

Next we will add the following if statement to the loop function. We will use the dis value to determine the behavior of the robot. We will use a switch statement to determine the behavior of the robot based on the distance to the object. We will add the following code to the loop function:

```cpp
  switch (dis) {
    case 700 ... UINT16_MAX: // Using UINT16_MAX as the upper bound for distance
      Movement::Velocity_Controller(0, 0, 0, 0);
      break;
    case 300 ... 699:
      Movement::Velocity_Controller(0, 50, 0, 0);
      break;
    case 200 ... 299:
      Movement::Velocity_Controller(0, 0, 0, 0);
      break;
    default: // dis < 200
      Movement::Velocity_Controller(180, 50, 0, 0);
      break;
  }
  ```

  Now before we try this out lets look at the syntax for the switch statement. We are using the ... operator to specify a range of values. This is a feature of C++17. If you are using an older version of C++ you would probably need to use a series of if statements to check the range of values. For example:
    
  ```cpp    
    if (dis >= 700) {
        Movement::Velocity_Controller(0, 0, 0, 0);
    } else if (dis >= 300 && dis <= 699) {
        Movement::Velocity_Controller(0, 50, 0, 0);
    } else if (dis >= 200 && dis <= 299) {
        Movement::Velocity_Controller(0, 0, 0, 0);
    } else {
        Movement::Velocity_Controller(180, 50, 0, 0);
    }
    ```

    ## Checkpoint 2
    Upload the code and test the robot. The robot should stop when the distance is less than 200. It should move forward when the distance is between 300 and 699. It should stop when the distance is greater than 700.
    See solution2.md for the complete code.
    