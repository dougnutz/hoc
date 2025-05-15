# Lesson: Color Recognition with ESP32 and FastLED

This lesson will guide you through building a simple color recognition system using an ESP32-S3 camera, an RGB LED, and a buzzer. We'll break the process into logical steps, with checkpoints and code explanations to verify your progress.

---

## Camera Control Implementation Explained

The camera control logic is implemented in the `hw_esp32s3cam_ctl.h` and `hw_esp32s3cam_ctl.cpp` files. These files provide an interface for initializing the ESP32-S3 camera and retrieving color detection data.

**Key Points:**
- The camera is managed through the `HW_ESP32S3CAM` class.
- `hw_cam.Init()` initializes the camera hardware and communication.
- `hw_cam.Colordetection_Data_Receive(ALL_COLOR_INDEX_REG, cam_buffer, sizeof(cam_buffer));` reads color detection data from the camera and stores it in the `cam_buffer` array.
- The buffer values are then used in your main code to determine which color is detected and to control the RGB LED accordingly.

This abstraction allows you to interact with the camera using simple function calls, making your main application code cleaner and easier to maintain.

---

## Step 1: Required Libraries

Before you start, make sure you have the following libraries installed:

- **FastLED**: For controlling the RGB LED.
- **Arduino**: Core library for ESP32 development.
- (Optional) **PID_v1**: If you plan to use PID control in advanced projects.


**Checkpoint 1:**
- Open your `platformio.ini` or Arduino Library Manager and ensure `FastLED` is installed.

---

## Step 2: Pin Definitions and Hardware Setup
Add the include statements and define the pins for your hardware:
```cpp
#include "FastLED.h"    
#include "hw_esp32s3cam_ctl.h"
```

- `#include "FastLED.h"`: Allows you to control addressable RGB LEDs like WS2812.
- `#include "hw_esp32s3cam_ctl.h"`: Custom header for handling the ESP32-S3 camera module.

Define the pins for your hardware:
- `ledPin`: Pin connected to the WS2812 RGB LED (e.g., GPIO 2)
- `buzzerPin`: Pin connected to the buzzer (e.g., GPIO 3)

Example:
```cpp
const static uint8_t ledPin = 2;
const static uint8_t buzzerPin = 3;
```

**Code Explanation:**
- `ledPin` and `buzzerPin` are constants that specify which ESP32 pins are used for the LED and buzzer. Adjust these if your hardware uses different pins.

**Checkpoint 2:**
- Connect your RGB LED and buzzer to the correct pins on your ESP32 board.

---

## Step 3: Global Variables and Object Instantiation

Set up global variables and instantiate the camera and LED objects:
```cpp
static CRGB rgbs[1];
HW_ESP32S3CAM hw_cam;
static uint8_t cam_buffer[COLOR_DETECTION_REG_COUNT];
```

**Code Explanation:**
- `CRGB rgbs[1];` creates an array for one RGB LED using the FastLED library.
- `HW_ESP32S3CAM hw_cam;` instantiates the camera control object.
- `cam_buffer` is a buffer to store color detection data from the camera.

** Function prototype:**
```cpp  
void Rgb_Show(uint8_t rValue,uint8_t gValue,uint8_t bValue);
```
- This function prototype declares a helper function to set the RGB LED color.
- `static uint16_t g_current_point = 0;` and `static uint16_t color_info[4] = { 0, 0, 0, 0};` are placeholders for future use and will insure the code compiles without errors.
- `static uint8_t cam_buffer[COLOR_DETECTION_REG_COUNT];` is a buffer to store color detection data from the camera.

**Checkpoint 3:**
- Make sure your camera module is connected and the `hw_esp32s3cam_ctl.h` header is available.
compile the code and check for errors. You will see some warnings about unused variables, which is normal at this stage.
- If you see errors related to the camera or FastLED, double-check your library installations.
---



## Step 4: The Setup Function

Add the follow ing code to your `setup()` function below the `Serial.println("setup");` line:
```cpp
void setup() {

  FastLED.addLeds<WS2812, ledPin, RGB>(rgbs, 1);
  hw_cam.Init();
  pinMode(buzzerPin,OUTPUT);
  tone(buzzerPin, 1200);
  delay(100);
  noTone(buzzerPin);
}
```

**Code Explanation:**
- `Serial.begin(9600);` starts serial communication for debugging.
- `Serial.setTimeout(500);` sets a timeout for serial reads.
- `Serial.write("setup");` sends a message to indicate setup has started.
- `FastLED.addLeds<WS2812, ledPin, RGB>(rgbs, 1);` initializes the FastLED library for one WS2812 LED.
- `Rgb_Show(255,255,255);` turns the LED white as a startup indicator.
- `hw_cam.Init();` initializes the camera module.
- `pinMode(buzzerPin,OUTPUT);` sets the buzzer pin as output.
- `tone(buzzerPin, 1200); delay(100); noTone(buzzerPin);` beeps the buzzer for 100 ms as a startup sound.




**Checkpoint 4:**
- Compile and check for errors.

## Step 5: RGB LED Control Function

Define a helper function to set the RGB LED color: Add this code to the bottom of your file:
```cpp
void Rgb_Show(uint8_t rValue,uint8_t gValue,uint8_t bValue) {
  rgbs[0].r = rValue;
  rgbs[0].g = gValue;
  rgbs[0].b = bValue;
  FastLED.show();
}
```
** Code Explanation:**
- This function sets the color of the RGB LED by updating the `rgbs` array and calling `FastLED.show()` to apply the change.
- The parameters `rValue`, `gValue`, and `bValue` are the RGB color values (0-255) to set the LED color.
- The `rgbs[0]` array holds the color values for the LED.

**Checkpoint 5:**
- compile the code and check for errors. Upload the code and check that the RGB LED turns white and the buzzer beeps briefly at startup.
---

## Step 6: The Loop Function (Color Recognition)

Continuously read color data from the camera and update the LED color:
Add this code to your `loop()` function:
```cpp
void loop() {
  hw_cam.Colordetection_Data_Receive(ALL_COLOR_INDEX_REG, cam_buffer, sizeof(cam_buffer));
  delay(10);
Serial.println();
  if(cam_buffer[0] == 0) Rgb_Show(0,10,0);      // Green for green detection
  else if(cam_buffer[3] == 3) Rgb_Show(0,0,10); // Blue for blue detection
  else if(cam_buffer[2] == 2) Rgb_Show(10,0,0); // Red for red detection
  else Rgb_Show(0,0,0); // Off for no detection
  delay(100);
}
```

**Code Explanation:**
- `hw_cam.Colordetection_Data_Receive(...)` reads color data from the camera into `cam_buffer`.
- The `Serial.print` lines output the buffer values for debugging.
- The `if`/`else if` statements check the buffer for detected colors and set the LED color accordingly:
  - Green if red is detected
  - Blue if blue is detected
  - Red if green is detected
- `delay(100);` slows the loop for stability.

**Checkpoint 5:**
- Compile and upload the code, move colored objects in front of the camera and observe the LED color and serial output.

---
## debugging
- IfSerial output to observe the buffer values and LED color changes.
```cpp
String bufStr;
for (int i = 0; i < sizeof(cam_buffer); i++) {
    bufStr += String(cam_buffer[i]);
    if (i < sizeof(cam_buffer) - 1) bufStr += ",";
}
Serial.println(bufStr);
```
## Summary

You have now built a basic color recognition system using ESP32, a camera, and an RGB LED. You learned how to:
- Set up hardware and libraries
- Initialize and use the camera
- Read color data and control an RGB LED
- Use serial output for debugging

Feel free to expand this project by adding more color logic, sound feedback, or integrating with other sensors!
