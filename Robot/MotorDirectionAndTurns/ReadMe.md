# Steering a Robot with Mecanum Wheels

Mecanum wheels allow a robot to move in any direction without changing its orientation. This is achieved by controlling the speed and direction of each wheel independently. In this lesson, we will learn how to steer a robot with mecanum wheels. By writing a function that takes the desired angle and velocity as input.

## Understanding Mecanum Wheels

Mecanum wheels have rollers that are mounted at a 45-degree angle to the wheel's axis. This unique design allows the robot to move forward, backward, sideways, and diagonally. The angle of the robot's movement is determined by the speed and direction of each wheel. The direction of travel can be calculated using the following formulas:

### Working principle of Mecanum wheels
According to the physical kinematics of the Mecanum wheel, when forces are equal and opposite they cancel each other out. Looking at the left side wheels if they are both spinning the same direction and the same speed the angular direction is cancelled out. Leaving only forward and backward motion. The same is true for the right side wheels. The combination of the two sides allows for the robot to move in any direction.

Based on Newton's second law, f=maa, if the force is equal and opposite, the acceleration is also equal and opposite. The front and rear tires produce forward and angular acceleration. Since the angular acceleration is equal and opposite they cancel each other out. However if the front and back wheels are not spinning at the same speed the robot will turn.

For this exercise we will look only at moving the robot on a given angle from 0 to 359 degrees. The degrees are calculated clockwise from Forward being 0 degrees, right being 90 degrees, backward being 180 degrees, and left being 270 degrees. 

We will also supply a velocity from 0 to 100. This will be the speed of the robot. 



## Setting Motor Speeds
The Motors_Set function is designed to control the PWM (Pulse Width Modulation) and direction of four motors. The function takes four parameters, each representing the control value for one motor.

We will start by creating two arrays. One to store the input motor control values. We will also create an array to store the direction of each motor one to store the PWM values for the motors.
Add the following lines to the top of the main.cpp file, before the setup function:

```c++
int8_t motors[4] = { Motor_0, Motor_1, Motor_2, Motor_3};
int8_t pwm_set[4];
```

We will also need to keep track of the direction of each motor. We will create an array to store the direction of each motor. We will set the default direction of each motor to true, which indicates forward.
Add the following line to the top of the main.cpp file, before the setup function:

```c++
bool direction[4] = { 1, 1, 1, 1};
```

#### Direction Handling:
We will need to create a loop that itterates through each of the four motors.
Add the following loop to the Motors_Set function:

```c++
for(uint8_t i=0; i < 4; ++i) {

}
```
Inside the loop we will need to determine the direction of the motor. We will check the sign (+ or -) of the motor value. If the motor control value is negative, the direction is toggled (reversed). If the motor control value is zero or positive, the direction remains as initially set. We will use a ternary operator (conditional) to check the sign of the motor value and set the direction accordingly.
Add the following line to the loop in the Motors_Set function:

```c++
direction[i] = motors[i] < 0 ? !direction[i] : direction[i];
```
Let's break down that code. 
 - We set the value of the direction array at index i 
- We check if the motor value at index i is less than 0
- If the motor value is less than 0, we toggle the direction by by using the NOT operator. 
    - The NOT operator is represented by an exclamation mark (!). It inverts the value of a boolean expression. If the direction was true, it will be set to false. If the direction was false, it will be set to true. In our case the values are 1 for true and 0 for false.

#### PWM Calculation:
With the direction set, we can now set the PWM value for the motor. The pwm_set array is used to store the calculated PWM values for each motor. The PWM value is calculated based on the absolute value of the motor control value, mapped from the range [0, 100] to [pwm_min, 255]. The pwm_min value is not defined in the provided code, but it typically represents the minimum PWM value required to start the motor. This mapping function scales the input value to the desired PWM range, ensuring that the motor speed is set correctly.


```c++
pwm_set[i] = motors[i] == 0 ? 0 : map(abs(motors[i]), 0, 100, pwm_min, 255);
```
Let's break down that code.
- The pwm_set array is used to store the calculated PWM values for each motor.
- We again use the ternary operator to check if the motor control value is zero. If the motor control value is zero, the PWM value is set to 0 (motor stops). If the motor control value is not zero then we calculate it.
- we calculate the PWM value for the motor based on the absolute value of the motor control value. The abs() function returns the absolute value of a number, which is the number's value without regard to its sign. For example, the absolute value of both -4 and 4 is 4.
- Next we map the absolute value of the motor control value from the range [0, 100] to [pwm_min, 255]. The map() function scales a number from one range to another. The first two arguments of the map() function define the input range, while the second two arguments define the output range. The function then calculates the equivalent value in the output range based on the input value. For example, a value of 50 in the input range [0, 100] would be mapped to 128 in the output range [pwm_min, 255]. This mapping function scales the input value to the desired PWM range, ensuring that the motor speed is set correctly.

For debugging purposes, the calculated PWM value is printed to the serial monitor. This allows you to verify that the PWM values are being calculated correctly.
Add the following line to the loop in the Motors_Set function:

```c++
Serial.println(pwm_set[i]);
```

Now we need to write the values to the motor pins. We will use the digitalWrite function to set the direction of the motor. 
Add the following line to the loop in the Motors_Set function:

```c++
digitalWrite(motordirectionPin[i], direction[i]);
```

We also need to use the analogWrite function to set the PWM value for the motor speed.
Add the following line to the loop in the Motors_Set function:

```c++
analogWrite(motorpwmPin[i], pwm_set[i]);
```


Nowe we need to test this code. We will write a simple test program that will set the speed of each motor to 50. This will allow us to test the direction of each motor.
Add the following code to the setup function in the main.cpp file:

```c++
Motors_Set(50, 50, 50, 50);
delay(1000);
```

What do you expect to happen when you run this code?


How would you make the robot move backwards?
Hint :negative values

### Checkpoint 1
Compare your code to Solution1.md. Make sure you have added the following code to the Motors_Set function:

### 


## Velocity Controller
### How do we calculate the speed of each wheel?
We are going to write the Velocity controller function in the code. The fuction is already defined in the main.cpp file. The function takes two arguments, the angle and the velocity. The angle is the direction we want the robot to move in and the velocity is the speed we want the robot to move at.

First, the function needs to initializes an array velocities to store the calculated velocities for each of the four motors. Create an int8_t array called velocities with a size of 4. This array will store the calculated velocities for each of the four motors. 

Add the following line to the top of the velocity_controller function:
```c++
int8_t velocities[4];
```
Then we need to adjust the angle and velocity to ensure that the robot moves in the correct direction at the desired speed. The angle is adjusted by adding 90 degrees to it, which is done to because we are addressing the angular portion of the wheels movelemt. This adjusted angle is converted from degrees to radians by multiplying it by PI / 180, which is necessary because trigonometric functions in C++ use radians.

Degrees are converted to radians in calculating angular movement for Mecanum wheel robots because radians are the standard unit of angular measure in mathematics and physics. Radians provide a direct relationship between the length of an arc and the radius of the circle, which simplifies calculations involving trigonometric functions and rotational kinematics. This makes the math more straightforward and consistent, especially when integrating with other systems and algorithms that use radians.

Add the following lines to the velocity_controller function:
```c++
angle += 90;
float rad = angle * PI / 180;
```

The velocity of the wheel is divided by the square root of 2 in Mecanum wheel robots to account for the unique 45-degree angle at which the wheels are mounted. This division ensures that the robot's movement is correctly calculated in both the x and y directions, allowing for precise control and omnidirectional movement. By dividing by the square root of 2, the combined effect of the wheel's velocity in both directions is accurately represented.

Add the following line to the velocity_controller function:
```c++
velocity /= sqrt(2);
``` 

Next we create a loop that itterates 4 times, once for each motor.
Add
```c++
for (int i = 0; i < 4; i++) {

}
```

Within the loop, a factor is determined based on the loop index i. If the index is even, factor is set to -1; if odd, it is set to 1. This factor is used to alternate the direction of the velocity components for each motor.
Add the following line to the velocity_controller function:
```c++
float factor = (i % 2 == 0) ? -1 : 1;
```
In the unit circle, sine represents the y-coordinate, while cosine represents the x-coordinate of a point on the circle corresponding to a given angle. These functions are fundamental in trigonometry and are used in various applications, including physics, engineering, and computer graphics. In this case, the sine and cosine of the adjusted angle are used to calculate the velocity components for each motor, scaled by the velocity and adjusted by the factor. This results in a set of velocities that are appropriately distributed based on the angle and desired speed.
Add the following line to the velocity_controller function:
```c++
velocities[i] = velocity * (sin(rad) + factor * cos(rad));
```

Finally, the calculated velocities are passed to the Motors_Set function, which presumably handles the actual setting of motor speeds. This function call uses the four elements of the velocities array as arguments, ensuring that each motor receives its corresponding velocity value. This setup allows the robot to move in the desired direction with the specified speed.

Add the following line to the velocity_controller function:
```c++
Motors_Set(velocities[0], velocities[1], velocities[2], velocities[3]);
```

#### Checkpoint 1
Compare your code to Solution1.md. Make sure you have added the following code to the velocity_controller function:

```c++
 int8_t velocities[4];
  angle += 90;
  float rad = angle * PI / 180;
  velocity /= sqrt(2);

  for (int i = 0; i < 4; i++) {
    float factor = (i % 2 == 0) ? -1 : 1;
    velocities[i] = velocity * (sin(rad) + factor * cos(rad));
  }

  Motors_Set(velocities[0], velocities[1], velocities[2], velocities[3]);

```
