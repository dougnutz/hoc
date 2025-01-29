``` cpp
# Moving in an arc or circle


## What is Drift
Drift is when the robot is moving in an arc and the wheels on one side are moving faster than the other side. This causes the robot to drift to one side. We can correct for this by slowing down the wheels on the side that is moving faster. We can do this by multiplying the velocity of the wheels on the side that is moving faster by a value between 0 and 1. This will slow down the wheels on that side and correct for the drift.

## How to move in an arc
In order to move in an arc we need to set the velocity of the wheels on one side of the robot to be different than the velocity of the wheels on the other side of the robot. We can do this by setting the velocity of the wheels on one side of the robot to be higher than the velocity of the wheels on the other side of the robot. This will cause the robot to move in an arc.

## Modiflying the code
Let's take a look at the starting code in the `main.cpp` file.
We have the previously written functions : 
``` cpp
void Motor_Init(void)
void Motor_Stop(void);
void Motors_Set(int8_t Motor_0, int8_t Motor_1, int8_t Motor_2, int8_t Motor_3);
```

We also have the velocity controller function that we wrote in the previous section. 
``` cpp
void Velocity_Controller(int8_t Target_Velocity, int8_t Current_Velocity, int8_t *Motor_0, int8_t *Motor_1, int8_t *Motor_2, int8_t *Motor_3);
```
Let's focus on the changes needed to the velocity controller function. 

### Velocity_Controller 
We need to start by modifying the function protoype to include two new parameters. `rot` and `drift`.  
- `rot` controls the robot's self-rotation speed, with a value range of -100 to 100. If the value is greater than 0, the robot has a counterclockwise self-rotation speed. If it is less than 0, the robot has a clockwise self-rotation speed. If the value is 0, the robot does not rotate.
- `drift` determines whether the robot enables drift. Value range: 0 or 1. If it is 0, drift is enabled; otherwise, it is disabled

Modify the function prototype to include the new parameters. 
``` cpp
Velocity_Controller(uint16_t angle, uint8_t velocity,int8_t rot,bool drift);
```
Next, we need to modify the function to include the new parameters. 
``` cpp     
Velocity_Controller(uint16_t angle, uint8_t velocity,int8_t rot,bool drift){
}
```
One more change is needed within the Motor_Init function. We need to add a new parameter to the function call. 
``` cpp
Motor_Init(0,0,0,0);
```

#### Checkpoint 1
Does the code compile? 
See [solution 1](#solution-checkpoint_1.md)

The Velocity_Controller function needs a bit more work. We need to utilize the variables in the code. This code is a bit more complex than the previous code. We need to calculate the velocity of each wheel based on the angle, velocity, rotation, and drift. 
Modify the velocity controller by removing the for loop
``` cpp
for(uint8_t i=0; i < 4; ++i) {
    direction[i] = motors[i] < 0 ? !direction[i] : direction[i];
      pwm_set[i] = motors[i] == 0 ? 0 : map(abs(motors[i]), 0, 100, pwm_min, 255);
      Serial.println(pwm_set[i]);
      digitalWrite(motordirectionPin[i], direction[i]);
      analogWrite(motorpwmPin[i], pwm_set[i]);
  }
```

``` cpp
void Velocity_Controller(uint16_t angle, uint8_t velocity,int8_t rot,bool drift) {
  int8_t velocities[4];
  angle += 90;
  float rad = angle * PI / 180;
  
  velocity /= sqrt(2);

  float rotationSpeed = (rot == 0) ? 1 : 0.5;
  if (drift) {
    velocities[0] = (velocity * sin(rad) - velocity * cos(rad)) * rotationSpeed + rot * rotationSpeed;
    velocities[1] = (velocity * sin(rad) + velocity * cos(rad)) * rotationSpeed - rot * rotationSpeed;
    velocities[2] = (velocity * sin(rad) - velocity * cos(rad)) * rotationSpeed - rot * rotationSpeed * 2;
    velocities[3] = (velocity * sin(rad) + velocity * cos(rad)) * rotationSpeed + rot * rotationSpeed * 2;
  } else {
    velocities[0] = (velocity * sin(rad) - velocity * cos(rad)) * rotationSpeed + rot * rotationSpeed;
    velocities[1] = (velocity * sin(rad) + velocity * cos(rad)) * rotationSpeed - rot * rotationSpeed;
    velocities[2] = (velocity * sin(rad) - velocity * cos(rad)) * rotationSpeed - rot * rotationSpeed;
    velocities[3] = (velocity * sin(rad) + velocity * cos(rad)) * rotationSpeed + rot * rotationSpeed;
  }

  Motors_Set(velocities[0], velocities[1], velocities[2], velocities[3]);

}
``` 

Lets add code to the setup() function to spin left in place then spin right in place.

``` cpp 
Velocity_Controller(0, 0,100,0);  ///Turn left in place
delay(1000);
Velocity_Controller(0, 0,-100,0); ///Turn right in place
delay(1000); 
  ```
  
```