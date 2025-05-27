# Mecanum Wheel Robot - Sending Serial Commands

This project provides Arduino code to control a mecanum wheel robot using serial commands. The robot can move in any direction and rotate in place, thanks to its mecanum wheels and the implemented velocity controller.
**New:** The robot can also receive commands to control an onboard RGB LED.

## Features

- **Mecanum Wheel Kinematics:** Move forward, backward, sideways, and rotate.
- **Serial Command Interface:** Easily control the robot via serial communication.
- **Drift Mode:** Enable or disable drift for advanced maneuvers.
- **RGB LED Control:** Set the color of the onboard Red-Green-Blue LED via serial commands.
- **Motor Initialization and Safety Stop:** Ensures motors are properly initialized and stopped.

## File Structure

- `src/main.cpp` - Main Arduino code for robot control.

## Lesson Plan Overview

### Objectives

- Understand how to send serial commands to control robot movement (direction, speed, rotation, drift).
- Learn to send serial commands to set the color of the onboard RGB LED.

### Step 1: Listening for Serial Commands in the loop() Function

In this step, we add code to the `loop()` function to listen for commands sent over the serial port. The robot waits for input from the serial monitor (or another serial sender), and collects characters until it sees the special end-of-command character `$`.
Add the following code to the `loop()` function:

```cpp
void loop() {
  while (Serial.available()) {
    String cmd = Serial.readStringUntil('$');
    cmd.trim();
      Serial.print("Received command: ");
      Serial.println(cmd);
      // TODO: Add command parsing and execution here
      cmd = "";
    
  }
}
```

**How it works:**
- The `while (Serial.available())` loop checks if there are any characters available to read from the serial port.
- `Serial.readStringUntil('$')` reads characters from the serial port until it encounters the `$` character, which indicates the end of a command.
- `cmd.trim()` removes any leading or trailing whitespace from the command string.
- `Serial.print("Received command: ");` prints the received command to the Serial Monitor for debugging purposes.
- `Serial.println(cmd);` prints the command to the Serial Monitor.
- `cmd = "";` resets the command string for the next input.

### Checkpoint: Test Serial Communication

Upload the code to your Arduino board and open the Serial Monitor. Follow these steps to test the serial communication:
#### 1. Open the Serial Monitor
- In the Arduino IDE, go to **Tools** > **Serial Monitor** or press `Ctrl + Shift + M`.
- Set the baud rate to **9600**.
#### 2. Set Line Ending
- In the Serial Monitor, set the line ending to **No line ending**. This ensures that the `$` character is sent as part of the command.
  
#### 3. Start the Serial Monitor
- Click the **Start Monitoring** button in the Serial Monitor to start listening for serial input.

#### 4. Send a Test Command
- In the Serial Monitor's input box, at the bottom of the monitor window, type:
  ```
  HelloWorld$
  ```
- Press **Enter** to send the command.

#### 4. Expected Output
You should see the following in the Serial Monitor:
```
Received command: HelloWorld
```

If you see this message, your serial communication is working! You are ready to move on to the next lesson step. Don't forget to stop the Serial Monitor before uploading new code to the Arduino board.

### Step 2: Parsing and Executing Serial Commands

Now, let's extend the `loop()` function to parse commands in the format `X|Y|$`, where `X` is the command type and `Y` is a parameter. We'll start by handling the 'A' command, which sets the RGB LED color:

**Code Added:**
```cpp
void loop() {
  while (Serial.available()) {
    String cmd = Serial.readStringUntil('$');
    cmd.trim();
    Serial.print("Received command: ");
    Serial.println(cmd);
    // Parse command: expected format X|Y|$
    int sepIndex = cmd.indexOf('|');
    if(sepIndex < 0){
      Serial.print("Invalid command");
      Serial.println(cmd);
      continue;
    }
    char commandType = cmd.charAt(0);
    String arg1 = cmd.substring(sepIndex + 1);
    arg1.trim();
    switch (commandType) {
      case 'A': {
        int color = arg1.toInt();
        if (color == 1) RGB_Show(255, 0, 0); // Red
        else if (color == 2) RGB_Show(0, 0, 255); // Blue
        else if (color == 3) RGB_Show(0, 255, 0); // Green
        else {
          RGB_Show(0, 0, 0); // Turn off LED
          Serial.println("Unknown color code");
        }
        break;
      }
      // Add more cases here for other command types
      default:
        Serial.println("Unknown command type");
        break;
    }
    cmd = "";
  }
}
```

**How it works:**
- The code reads a command string ending with `$` and trims whitespace.
- It checks for the presence of a `|` separator to validate the command format.
- The first character before the `|` is treated as the command type (e.g., 'A').
- The value after the `|` is parsed as an argument (e.g., color code).
- A `switch` statement is used to handle different command types. For 'A', the LED color is set as follows:
  - `A|1|$` sets the LED to red.
  - `A|2|$` sets the LED to blue.
  - `A|3|$` sets the LED to green.
  - Any other value turns the LED off and prints an error message.
- If the command or color code is invalid, an error message is printed and the LED is turned off.

**Example:**
- Sending `A|1|$` will turn the LED red.
- Sending `A|2|$` will turn the LED blue.
- Sending `A|3|$` will turn the LED green.

This structure makes it easy to add more command types and parameters in future steps.

### Checkpoint: Test RGB LED Serial Commands

Upload the code and let's test the RGB LED control feature.

#### 2. Send Sample Commands
Try sending the following commands (type each line and press Enter):

```
A|1|$
A|2|$
A|3|$
A|red|$
```

#### 3. Expected Results
- `A|1|$` — The LED turns **red**.
- `A|2|$` — The LED turns **blue**.
- `A|3|$` — The LED turns **green**.
- `A|red|$` — The Serial Monitor prints `Unknown color code` (since only numbers 1, 2, or 3 are valid).

If you see the expected LED colors and error message for the invalid command, your serial command parsing and RGB LED control are working correctly!

### Step 3: Motor Directional Control with Command B

Now, let's add support for moving the robot in a specified direction and speed using serial commands. The format for this command is:

```
B|direction,speed|$
```
- `direction` is the angle in degrees (0-359)
- `speed` is the speed value (0-100)

**Code Added:**
```cpp
case 'B': {
  int commaIndex = arg1.indexOf(',');
  if (commaIndex < 0) {
    Serial.println("Invalid B command format. Use B|direction,speed|$");
    break;
  }
  String dirStr = arg1.substring(0, commaIndex);
  String speedStr = arg1.substring(commaIndex + 1);
  dirStr.trim(); 
  speedStr.trim();
  Velocity_Controller(dirStr.toInt(), speedStr.toInt(), 0, false);
  delay(1000);
  Motor_Stop();
  break;
}
```

**How it works:**
- The code checks for the 'B' command and expects the argument in the format `direction,speed`.
- It splits the argument at the comma, trims whitespace, and converts both parts to integers.
- It calls `Velocity_Controller(direction, speed, 0, false)` to move the robot in the specified direction and speed for 1 second.
- After 1 second, it calls `Motor_Stop()` to stop the robot.
- If the format is invalid, it prints an error message.

**Example:**
- Sending `B|0,50|$` will move the robot at 90° (right) with speed 50 for 1 second, then stop.
- Sending `B|90,100|$` will move the robot forward at full speed for 1 second, then stop.
- Sending `B|badinput|$` will print an error message and not move the robot.

This allows you to control the robot's movement interactively from the serial monitor.

---



