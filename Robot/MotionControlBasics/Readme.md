# Mecanum wheel robot basic movements
For this project we will use a basic Mecanum wheel robot. There are lots of kits available we will use one based on the arduino uno. Specificially this [one](https://www.hiwonder.com/products/miniauto-1?variant=41259314577495). 

For the first part we only need the basic chassis, motors, wheels, arduino, expansion shield, and battery 
![image](https://github.com/user-attachments/assets/41edf6ea-6728-45e7-afd5-11172de82dd8)


## Setup
We will start by defining the pins and the functions that will be used to control the motors. The pins are defined as static const arrays. The first array is used to define the pins that will be used to control the direction of the motors. The second array is used to define the pins that will be used to control the speed of the motors.

```cpp
const static uint8_t motordirectionPin[4] = { 13,8,7,12 };  ///pins for controlling the motor direction
const static uint8_t motorpwmPin[4] = { 3,5,6,11 };  ///pins for controlling the motor speed
```

We will need to define an initialization function that will set the pins as outputs. The function will loop through each of the pins and set them as outputs. We will also declare the function prototypes for the functions that will be used to control the motors.   
At the top of the file, below the constants add the following function prototypes.
```cpp
// Function prototypes
void Motor_Init(void);
void Motor_Stop(void);
void Motor_Forward(void);
```

```cpp
void Motor_Init(void) {
  for (uint8_t i = 0; i < 4; i++) {
    pinMode(motordirectionPin[i], OUTPUT);
    pinMode(motorpwmPin[i], OUTPUT);
  }
}
```
We will also need a function to stop the motors. The function will loop through each of the motors and set the speed to 0. This will stop the motors from spinning.
```cpp
void Motor_Stop(void) {
  for (uint8_t i = 0; i < 4; i++) {
    analogWrite(motorpwmPin[i], 0); // Set speed to 0
  }
  Serial.println("Stop motors");
}
```

### now the setup
Lets call the init function and the stop function in the setup function. The stop function will be used to stop the motors after each movement. The init function will be used to set the pins as outputs. We will also initialize the serial output to print debug messages.
```cpp
void setup() {
  Serial.begin(9600);  // Open serial port at 9600 bps
  Motor_Init(); ///Initialize the motors
  Motor_Move(); ///Move forward
  delay(1000);
  Motor_Stop();
}
```

## test the motors and pin values
Loop through all the motors and set the speed to 125. This will make the motors spin at half speed. We will also print a message to the serial output to indicate that the motors are spinning.
```cpp
void Motor_Move(void) {
  for (uint8_t i = 0; i < 4; i++) {
    Serial.println("Motor " + i + " moving");
    digitalWrite(motordirectionPin[i], HIGH); // Set direction to forward
    analogWrite(motorpwmPin[i], 125); // Set speed to 125
    delay(1000);
    analogWrite(motorpwmPin[i], 0); // Set speed to 0
  }
}
```

### checkpoint 1
Upload the code and validate that each motor spins and stops after 1 second.

See the [Solution](Solution_1.md) for the complete code.

## Move forward
What will happen if we set all the motors to move, instead of doing one at a time?
Modify the move function to move all the motors at the same time. 
- Move the delay outside the loop to make the motors move for 1 second. 
- Then call the stop function to stop the motors.
- Delete the analogWrite() where we set speed to 0


```cpp
void Motor_Move(void) {
  for (uint8_t i = 0; i < 4; i++) {
    digitalWrite(motordirectionPin[i], HIGH); // Set direction to forward
    analogWrite(motorpwmPin[i], 125); // Set speed to 125
  }
  Serial.println("Move forward");
}
```

### Did that work?
Upload the code and validate that all the motors spin and stop after 1 second. 
- What did you expect to happen?
- What did you observe?
- What do you think is happening?

### Modify the motor move function to move the left side motors forward and the right side motors backward.
To move the robot forward we need to set the left side motors to move forward and the right side motors to move backward. We will modify the move function to set the direction of the motors based on their position. The left side motors will move forward and the right side motors will move backward.

We will keep a list of motors that need to move forward and motors that need to move backwards. We will use a binary flag to represent the direction of the motors. If the flag is true the motors will move forward, if the flag is false the motors will move backward.

#### Modify the motor move function to set the direction of the motors based on the flag.
Add this line to the top of the motor move function to define the direction of the motors.
Add the following code to the motor move function to set the direction of the motors based on their position.
```cpp  
  bool direction[4] = { 1, 0, 0, 1};///forward, left 1, right 0
```

Delete the code that outputs the motor number 
```cpp
    Serial.println("Motor " + i + " moving");
```

Next modify the loop to set the direction of the motors based on the flag.
If the loop index matches the flag for the motor, set the direction to forward. If the loop index does not match the flag for the motor, set the direction to backward. Use a conditional statement to set the direction of the motor based on the flag.
- Just inside the loop add the following code to set the direction of the motor based on the flag.
```cpp
    if (direction[i]) {
      digitalWrite(motordirectionPin[i], HIGH); // Set direction to forward
    } else {
      digitalWrite(motordirectionPin[i], LOW); // Set direction to backward
    }
```

Keep the motor speed code outside of the conditional statement but inside the loop.
```cpp
    analogWrite(motorpwmPin[i], 125); // Set speed to 125
```

It's recommended to add a debugging serial output to the bottom of the function to indicate that the function has completed.
```cpp
  Serial.println("Move forward");
  delay(1000);
  Motor_Stop();
````

### Checkpoint 2
Upload the code and validate that the robot moves forward.

See the [Solution](Solution_2.md) for the complete code.

## Modify the Move function to take a parameter

The move function is currently hardcoded to move the robot forward. We will modify the function to take a parameter that will determine the direction of the movement. We will use a boolean value to determine the direction. If the value is true the robot will move forward, if the value is false the robot will move backward.


Modify the function prototype and the function to take a boolean parameter that will determine the direction of the movement. Change void to bool in the function prototype.
```cpp
void Motor_Move(bool isForward);
```

Modify the code to check the the value of the parameter and set the direction of the motors based on the value of the parameter. If the parameter is true the motors will move forward, if the parameter is false the motors will move backward.

One solution is to use a conditional operator to set the direction of the motors based on the parameter. The conditional operator is a shorthand way to write an if-else statement. The conditional operator takes three operands: a condition, a value to return if the condition is true, and a value to return if the condition is false. The conditional operator is written as a question mark followed by a colon. The conditional operator is used to set the direction of the motors based on the value of the parameter.


Change the code inside the loop to use the conditional operator to set the direction of the motors based on the value of the parameter.
```cpp
digitalWrite(motordirectionPin[i], (isForward == direction[i]) ? HIGH : LOW);
```

Do not forget to update the function call in the setup function to pass the parameter to the move function. While we are at it lets add a call to reverse ase well


```cpp
  Motor_Move(true); ///Move forward
  delay(1000);
  Motor_Move(false); ///Move backward
  delay(1000);
```

Checkpoint 3
Upload the code and validate that the robot moves forward and backward.

See the [Solution](Solution_3.md) for the complete code.


## Move left and right
To move the robot left and right we need to set the left side motors to move backward and the right side motors to move forward. We will modify the move function to set the direction of the motors based on their position. The left side motors will move backward and the right side motors will move forward.

We can basically copy the Motor Move function and create a Motor_MoveSideways function.
- Copy the Motor_Move function and paste it below the Motor_Move function.
- Rename the function to Motor_MoveSideways.
- Create a function prototype for the Motor_MoveSideways function.
```cpp
void Motor_Spin(bool isRight);
```
- Change the code to set the direction of the motors based on the position of the motor. The left side motors will move backward and the right side motors will move forward. The direction variables need to represent the direction we want the motors to rotate in order to move right
```cpp
  bool direction[4] = { 0, 1, 1, 0};/// right 1, left 0
``` 
### Call the function from the setup function
- Call the Motor_MoveSideways function from the setup function to move the robot left and right.
```cpp
  Motor_MoveSideways(true); ///Move left
  delay(1000);
  Motor_MoveSideways(false); ///Move right
  delay(1000);
```

### Checkpoint 4
Upload the code and validate that the robot moves left and right.

See the [Solution](Solution_4.md) for the complete code.
