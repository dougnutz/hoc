# Following a line
In this project we will use the led and sensor module to have the robot follow a line. 

## pre-requisites
This projects you have completed the previous movement sections, especially the "MotionInArc" project.

## Code refactoring
We will build upon the code from the "MotionInArc" project. But our main.cpp is getting a little busy, so we will move some of the code to a new file called "Movement.cpp". First we will create the header file "Movement.h" in the "include" folder. 

The `include` folder is used to store header files. Adding a header file is equivalent to copying the header file into each source file that needs it, which would be time-consuming and error-prone. With a header file, related declarations appear in one place. If changes are needed, they can be made in one place, and programs that include the header file will automatically use the new version when recompiled. This eliminates the labor of finding and changing all copies and reduces the risk of inconsistencies within a program.

In C, the convention is to name header files with a `.h` extension. It is most portable to use only letters, digits, dashes, and underscores in header file names, and at most one dot.

In VsCode, right click on the "include" folder and select "New File". Name the file "Movement.h". The ide should automatically open the file you just created. 
Now we will add the following code to the file: Most of this code is copied from the "main.cpp" at the top where we declare our function prototypes. We will also add the `static` keyword to the function names.
```cpp
#include <Arduino.h>
class Movement {
    public:
        static void Motor_Init(void);
        static void Motor_Stop(void);
        static void Motors_Set(int8_t Motor_0, int8_t Motor_1, int8_t Motor_2, int8_t Motor_3);
        static void Velocity_Controller(uint16_t angle, uint8_t velocity,int8_t rot,bool drift);
};

#### Question: What does the static keyword do in C++?


```
Now in main.cpp we will include the "Movement.h" file we just created. Add the following line to the top of the file:

```cpp  
#include "Movement.h"
```


Save and close the file. Now we will create the "Movement.cpp" file in the "src" folder. Right click on the "src" folder and select "New File". Name the file "Movement.cpp". The ide should automatically open the file you just created.
Now we will add the following code to the top file:

```cpp
#include <Arduino.h>
#include "Movement.h"
```

Now we will move all of the code we have written so far from "main.cpp" to "Movement.cpp".  Start with the comments, and constants. Highlight the following code, press Control+X to cut the code, and then paste (control+V) into "Movement.cpp" after the `#include` statements:

```cpp  
Copy the following code from "main.cpp" to "Movement.cpp" after the `#include` statements:

```cpp
/*
* [0]--|||--[1]       motorpwmPin[4] motordirectionPin[4] (The numbers correspond to the index numbers of motorpwmPin[4] and motordirectionPin[4])
*  |         |          (counterclockwise)
*  |         |        
*  |         |        
*  |         |        
* [3]-------[2]
*/
// Constants
const static uint8_t pwm_min = 50;
const static uint8_t motorpwmPin[4] =  { 11,9,6,10 };  ///pins for controlling the motor speed
const static uint8_t motordirectionPin[4] = { 13,8,7,12 };  ///pins for controlling the motor direction
```

Go back to main.ccp and highlight all the code after the void loop() function. Highlight the code, press Control+X to cut the code, and then paste (control+V) into "Movement.cpp" after the `#include` statements:

This functionally moves the code but we need to make a few more changes to the code. We will need to add the class name to the function names. We will also need to add the `static` keyword to the function names. This will make the functions private to the class. This is a good practice as it will prevent other classes from using the functions.   

Add the following in front of each function name in the "Movement.cpp" file: 

```cpp
Movement::
```
We need to do the same in the "main.cpp" file. Do this in front of the functions names called from our setup().

### Checkpoint
Try to compile the code, you should not get any errors.
If it compiles try to upload the code to the robot and make sure it still moves forward for 1 second.

If you have any issues compare your code to the code in the "Solution_1.md" file.

## Following a line
### Import the FastLED library
No that we have refactored our code we can start working on the line following code. For this project we will need to import a library to help us communicate with the LED and sensor module.

Click on the "PlatformIO home" icon on the bottom left side of the ide. It looks like a little house. Click on the "Libraries" tab on the left.
- Then in the search bar type "FastLED" and press enter. Click on the "FastLED by Daniel Garcia" library. Click on the "Add to Project" button.
- When the "add project dependencies" popup appears click the "add to project" field and select the project "Robot\LineFollowing". Then click the "Add" button.

This will add the "FastLED" library to the project.  It will open the platformio.ini file. This file is used to store the project settings. You can see that it has added the following lines to the file:

```cpp 
lib_deps = fastled/FastLED@^3.9.13
```

### Checkpoint
Try to compile the code, you should not get any errors. You should see a lot of output in the terminal. This is because the "FastLED" library is very big. It is used to control a lot of different types of LED's. But we will only use a small part of it.

### Setup a "start pin"
we need a new constant to define our onboard button pin. Add the following line to the "main.cpp" file after the `#include "Movement.h"` line:
```cpp
const static uint8_t startPin = 3;
```
We will also need a variable to store the state of the button. Add the following line to the "main.cpp" file after the constants:
```cpp
bool keyState;  //Detect button status
```

In the setup() function we will need to set the startPin as an input. Add the following line to the setup() function in the "main.cpp" file just above the `Serial.begin("End Setup");` line:
```cpp
pinMode(startPin, INPUT);
```

Now we need to read the state of the button and react to it. Look at the Loop() and uncomment the code that reads the button. 
#### Hint 
Highlight the code and press Control+K,U

Also lets remove the code in the setup() that moves the robot forward. We will move this code to the loop() function.


Delete the following lines from the setup() function in the "main.cpp" file:
```cpp
  // move the robot forward
  Velocity_Controller(0, 100, 0, 0);
  delay(1000);
```

### Checkpoint 
Upload the code and verify that the robot wheels turn when the button is pressed.
See Solution_2.md for the complete code.

## Lets start using the LED and sensor module
We will need to include the header for the helper class. Add the following line to the top of the "main.cpp" file:

```cpp
#include "Helper.h"
``` 

In the setup() add the following lines under the `pinMode(startPin, INPUT);` line:
```cpp
  Helper::Init();
```

In the loop() function we will turn on the led when the button if the button is pressed and turn it off when the button is released. Add the following code to the loop() function in the "main.cpp" file:
Let's use White for the LED. The function we will use is:
```cpp
Helper::Rgb_Show();
```
Helper::SetLed() takes three arguments, the first is the red value, the second is the green value, and the third is the blue value. The values range from 0 to 255. So, for white, we will use 255, 255, 255. The function will look like this:

```cpp
  keyState = digitalRead(startPin);  // Read the keyPin and assign the value to keyState
  if (keyState == 0) {  // If the key is pressed, the keyState is 0
    Helper::Rgb_Show(0, 255, 0);  // Set the LED to green
  } else {  // If the key is not pressed, the keyState is 1
    Helper::Rgb_Show(0, 0, 0);  // Set the LED to off
  }
```

### Checkpoint
Upload the code and verify that the LED turns on when the button is pressed and turns off when the button is released.
See Solution_3.md for the complete code.


### Communicating with the FASTLed library
We will need to write bytes, and read bytes from the LED and sensor module. We have a helper class that will help us do this. Take a look at the class called helper.cpp in the "src" folder. This class has a few helper functions that will help us write and read bytes from the LED and sensor module.


### Following a line
Lets add a few new variables to track the state of our following task, and store data from the LED and sensor module.
Add the following variable to the top of main.cpp below the constants:
```cpp
bool taskStart = 0;
uint8_t data;
uint8_t rec_data[4];
static uint8_t modestate = TRACKING;
const static uint8_t TRACKING = 4;
```

We will also need some new function prototypes. Add the following lines to the "main.cpp" file after the `#include "Movement.h"` line:
```cpp
void Task_Dispatcher(void);
void Tracking_Line_Task(void);
void Sensor_Receive(void);
```


Next, we will delete all of our test code in side the loop() except the "keyState = analogRead(keyPin);"

Then, Under that line we will add the following code:
```cpp
  keyState = analogRead(keyPin);  // Read the keyPin and assign the value to keyState
    if (keyState == LOW && !taskStart) {
        taskStart = 1;
    } else if (keyState == LOW && taskStart) {
        taskStart = 0;
    }
  
    if (taskStart) {
        Sensor_Receive();
        Task_Dispatcher();
    }
```
This will add a new state to the robot. When the button is pressed, the robot will start following the line. When the button is pressed again, the robot will stop following the line. We need a little delay in here to debounce the button. Add the following line after each taskStart line:
```cpp
  delay(100);
```
Now that we detected button state lets turn on the led to indicate the button was pressed. Add the following line to the first if statement:
```cpp
  Helper::Rgb_Show(255, 255, 255);  // Turn the LED white
```
And add the following line to the second statement to stop the robot and turn off the LED, indicating the task ended:
```cpp
  Helper::Rgb_Show(0, 0, 0);  // Turn off the LED
  Movement::Motor_Stop();  // Stop the robot
``

Your loop() function should look like this:
```cpp
void loop() {
  keyState = analogRead(keyPin);  // Read the keyPin and assign the value to keyState
    if (keyState == LOW && !taskStart) {
        taskStart = 1;
        Helper::Rgb_Show(255, 255, 255);  // Turn the LED white
        delay(1000);
        Movement::Velocity_Controller(0, 80, 0, 0);  // Move the robot forward
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
```


Lets add write the `Sensor_Receive()` and `Task_Dispatcher()` functions. Add the following code to the "main.cpp" file after the Loop():
```cpp
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
```

### Checkpoint
Let's make sure everything still compiles. If it does, we can move on to the next step. If you have any issues, compare your code to the code in the "Solution_4.md" file.

## making it all work
The last step is the actual line following code. We will impliment the function called `Tracking_Line_Task()`. This function will be called repeatedly to track the line.
```cpp
void Tracking_Line_Task(void) {
  Helper::Rgb_Show(0, 255, 0);
  if (rec_data[1] == 1 && rec_data[2] == 1) {
    Movement::Velocity_Controller(0, 80, 0, 0);
    Serial.println("Forward");
  }
  if (rec_data[1] == 1 && rec_data[2] == 0) {
    Movement::Velocity_Controller(0, 80, 65, 0);
    Serial.println("Right");
  }
  if (rec_data[1] == 0 && rec_data[2] == 1) {
    Movement::Velocity_Controller(0, 80, -65, 0);
    Serial.println("Left");
  }
  while (rec_data[1] == 0 && rec_data[2] == 0) {
    Sensor_Receive();
    Movement::Velocity_Controller(0, 0, 0, 0);
    Serial.println("No line detected");
  }
}```

### Debugging
If the robot is not detecting the line or lack of a line, then you can adjust the potentiometer located on the sensor. Turning the knob clockwise will increase the detection distance, while turning it counterclockwise will shorten the detection distance.


![image](https://github.com/user-attachments/assets/b7a98a78-08fe-4994-9f51-43aeba6a3a74)



