# Review basic controls 
In this exercise we will use the arduino uno board to control and L298n motor driver to control a DC motor.

## Step 1 review the basic controls
To get started with using an Arduino Uno and an L298n motor controller, we will first practice with an LED wired up to a breadboard. This will help us understand the basic control functions before moving on to controlling a DC motor.

### Step 2.1: Using a breadboard to hold the LED, ressister and button
1. Insert one end of a resistor (about 330 ohm) into the same row as the short leg (cathod) of the LED and the other end into the ground (GND) channel on the breadboard. Recommended Column A row 3.
2.  Place the LED on the breadboard, ensuring that the long leg (anode) and short leg (cathode) are on separate rows. Recommend using rows 1 (anode) and 3(cathode) column B.
3. Connect a jumper wire from the anode (row 1) to pin 13 on the Arduino.
4. Use another jumper wire to connect the ground column to the GND pin on the Arduino.

### Step 3: Write basic functional code
Create a new sketch in the Arduino IDE and write the following code to blink the LED:

- Add the following code to the setup function to set pin 13 as an output:

```cpp
void setup() {
    pinMode(13, OUTPUT); // Set pin 13 as an output
}
```
- add the following code to the loop function to turn the LED on and off every second:
```cpp
void loop() {
    digitalWrite(13, HIGH); // Turn the LED on
    delay(1000);            // Wait for 1 second
    digitalWrite(13, LOW);  // Turn the LED off
    delay(1000);            // Wait for 1 second
}
```

### Step 4: Validate the results
Upload the code to the Arduino Uno. The LED should blink on and off every second.

### Step 5: Add a button to control the LED
1. Add a button to the breadboard. Column C row 20 and 23.
2. Connect one side of the button (row 20) to pin 2 on the Arduino.
3. Connect the other side of the button to the ground (GND).
4. Update the code to control the LED with the button:

Add variables for the button and LED pins at the top of the code:
```cpp
const int buttonPin = 2;    // Pin for the button
const int ledPin = 13;      // Pin for the LED
int buttonState = 0;        // Variable for reading the button status
```

Update the setup function to set the button pin as an input and the LED pin as an output:
```cpp
void setup() {
    pinMode(ledPin, OUTPUT);  // Set the LED pin as an output
    pinMode(buttonPin, INPUT_PULLUP); // Set the button pin as an input with internal pull-up resistor
}
```

update the loop function to read the state of the button and turn the LED on or off accordingly:
```cpp
void loop() {
    buttonState = digitalRead(buttonPin); // Read the state of the button

    if (buttonState == LOW) { // If the button is pressed
        digitalWrite(ledPin, HIGH); // Turn the LED on
    } else {
        digitalWrite(ledPin, LOW);  // Turn the LED off
    }
    delay(100); // Short delay to prevent reading the button too quickly
}
```
 #### Optionally enable the serial monitor to print the button state:
Alter the setup code to enable the serial monitor:
```cpp
void setup() {
    Serial.begin(115200); // Initialize the serial port

    pinMode(ledPin, OUTPUT); // Set pin 13 as an output
    pinMode(buttonPin, INPUT_PULLUP); // Set the button pin as an input with internal pull-up resistor

    Serial.println("setup complete");
}
```
Add code to the loop function to print the button state:
```cpp

    Serial.println("Button pressed"); // Print a message to the serial port

```

#### Checkpoint
Upload the code to the Arduino Uno. The LED should turn on when the button is pressed and off when the button is released.

See solution1.md for the full code.

## Add a motor driver to control the motor
Now that we have the basic controls working, we can move on to controlling a DC motor using an L298n motor driver. The L298n motor driver will allow us to control the speed and direction of the motor.

### Step 6: Replace the LED for the motor driver
1. Remove the LED and resistor from the breadboard.
1. Connect the IN1 and IN2 pins of the L298n motor driver to pins 8 and 9 on the Arduino.
2. Connect the ENA pin of the L298n to pin 10 on the Arduino.
3. Connect the motor to the OUT1 and OUT2 pins of the L298n.
    The red wire of the motor should be connected to OUT1 and the black wire to OUT2.
4. Connect the power supply to the motor driver. The power supply should be between 6V and 12V on the 12v pin of the L298n and ground on the GND pin of the L298n. The ground of the power supply should also be connected to the ground of the Arduino via the breadboard.
5. Make sure the 5v pin of the L298n is connected to the 5v pin of the Arduino and the built-in 5v regulator of the L298n is disabled any time the arduino is connected to the USB port.

### Important
- The ground of the power supply should also be connected to the ground of the Arduino via the breadboard.
- <span style="color:red">Anytime the Arduino is connected to the USB port, the 5V regulator of the L298n should be disabled. This can be done by removing the jumper on the L298n labeled "EN".</span>

Update the code to control the motor:

```cpp
const int in1Pin = 8; // IN1 pin of the L298N motor driver uses digital pin 8 on the Arduino
const int in2Pin = 9; // IN2 pin of the L298N motor driver uses digital pin 9 on the Arduino
const int enaPin = 10; // Enable pin for motor A uses PWM to control the speed of the motor
const int buttonPin = 2;
int buttonState = 0;
```

```cpp
void setup() {
    pinMode(in1Pin, OUTPUT);
    pinMode(in2Pin, OUTPUT);
    pinMode(enaPin, OUTPUT); 
    pinMode(buttonPin, INPUT_PULLUP);
}
```

```cpp
void loop() {
    buttonState = digitalRead(buttonPin);

    if (buttonState == LOW) {
        digitalWrite(in1Pin, HIGH);
        digitalWrite(in2Pin, LOW);
        analogWrite(enaPin, 255); // Set motor speed to maximum
        Serial.println("Button pressed");
    } else {
        digitalWrite(in1Pin, LOW);
        digitalWrite(in2Pin, LOW);
        analogWrite(enaPin, 0); // Stop the motor
    }
    delay(100); // Short delay to prevent reading the button too quickly
}
```

### Step 7: Validate the results
Upload the code to the Arduino Uno. The motor should turn on and off when the button is pressed and released.

## Solution
Compare your code to the solution2.md file. If your code is not working, copy the solution2.md code to your sketch and try again.

## Lets add a second button to run the motor in reverse

### Step 8: Add a second button to the breadboard
1. Add a second button to the breadboard. Column C row 10 and 13.
2. Connect one side of the button (row 10) to pin 3 on the Arduino.
3. Connect the other side of the button to the ground (GND) column on the breadboard.

### Step 9: Update the code to control the motor in reverse

Add variables for the second button pin at the top of the code:
```cpp
const int buttonPin2 = 3;    // Pin for the second button
int buttonState2 = 0;        // Variable for reading the second button status
```

Update the setup function to set the second button pin as an input:
```cpp
void setup() {
    pinMode(in1Pin, OUTPUT);
    pinMode(in2Pin, OUTPUT);
    pinMode(enaPin, OUTPUT); 
    pinMode(buttonPin, INPUT_PULLUP);
    pinMode(buttonPin2, INPUT_PULLUP);
}
```

Update the loop function to read the state of the second button and run the motor in reverse when the second button is pressed:
```cpp
void loop() {
    buttonState = digitalRead(buttonPin);
    buttonState2 = digitalRead(buttonPin2);

    if (buttonState == LOW) {
        digitalWrite(in1Pin, HIGH);
        digitalWrite(in2Pin, LOW);
        analogWrite(enaPin, 255); // Set motor speed to maximum
        serial.println("Button 1 pressed");
    } else if (buttonState2 == LOW) {
        digitalWrite(in1Pin, LOW);
        digitalWrite(in2Pin, HIGH);
        analogWrite(enaPin, 255); // Set motor speed to maximum
        serial.println("Button 2 pressed");
    } else {
        digitalWrite(in1Pin, LOW);
        digitalWrite(in2Pin, LOW);
        analogWrite(enaPin, 0); // Stop the motor
    }
    delay(100); // Short delay to prevent reading the button too quickly
}
```

### Step 10: Validate the results
Upload the code to the Arduino Uno. The motor should turn on and off when the button is pressed and released. The motor should also turn in reverse when the second button is pressed.

## Solution
Compare your code to the solution3.md file. If your code is not working, copy the solution3.md code to your sketch and try again.

### Step 11 Lets add a timer to turn the motor off after 2 seconds
Modify the code to turn the motor off after 2 seconds. 

Add a variable to track the start time of the motor at the top of the code:
```cpp
unsigned long motorStartTime = 0; // Variable to store the start time of the motor
```

Update the loop function to turn the motor off after 2 seconds:
```cpp
void loop() {
    buttonState = digitalRead(buttonPin);
    buttonState2 = digitalRead(buttonPin2);

    if (buttonState == LOW) {
        digitalWrite(in1Pin, HIGH);
        digitalWrite(in2Pin, LOW);
        analogWrite(enaPin, 255); // Set motor speed to maximum
        digitalWrite(ledPin, HIGH); // Turn the LED on
        motorStartTime = millis(); // Save the start time of the motor
    } else if (buttonState2 == LOW) {
        digitalWrite(in1Pin, LOW);
        digitalWrite(in2Pin, HIGH);
        analogWrite(enaPin, 255); // Set motor speed to maximum
        digitalWrite(ledPin, HIGH); // Turn the LED on
        motorStartTime = millis(); // Save the start time of the motor
    }

    // Check if 2 seconds have elapsed
    if (millis() - motorStartTime >= 2000) {
        digitalWrite(in1Pin, LOW);
        digitalWrite(in2Pin, LOW);
        analogWrite(enaPin, 0); // Stop the motor
    }

    delay(100); // Short delay to prevent reading the button too quickly
}
```

### Step 12: Validate the results
Upload the code to the Arduino Uno. The motor should turn on and off when the button is pressed and released. The motor should also turn in reverse when the second button is pressed. The motor should turn off after 2 seconds.

## Solution
Compare your code to the solution4.md file. If your code is not working, copy the solution4.md code to your sketch and try again.

### Step 8: Questions
1. What is the purpose of the L298n motor driver?
- [ ] To provide power to the motor
- [ ] To control the speed of the motor
- [ ] To control the direction of the motor
- [ ] To convert the PWM signal to an analog signal
- [ ] All of the above

2. What is the purpose of the ENA pin on the L298n motor driver?
- [ ] To provide power to the motor
- [ ] To control the speed of the motor
- [ ] To control the direction of the motor
- [ ] To convert the PWM signal to an analog signal

3. What is the purpose of the IN1 and IN2 pins on the L298n motor driver?
- [ ] To provide power to the motor
- [ ] To control the speed of the motor
- [ ] To control the direction of the motor
- [ ] To convert the PWM signal to an analog signal

4. What is the purpose of the button in this circuit?
- [ ] To turn the motor on and off
- [ ] To change the direction of the motor
- [ ] To change the speed of the motor
- [ ] To control the LED

5. What is the purpose of the pull-up resistor on the button pin?
- [ ] To limit the current flowing through the button
- [ ] To protect the button from short circuits
- [ ] To ensure that the button reads a high signal when not pressed
- [ ] To ensure that the button reads a low signal when not pressed
- [ ] To ensure that the button reads an analog signal

6. What is the purpose of the delay function in the code?
- [ ] To ensure that the button is not read too quickly
- [ ] To ensure that the LED blinks at the correct speed
- [ ] To ensure that the motor does not turn on too quickly
- [ ] To ensure that the motor turns off at the correct time
- [ ] To ensure that the setup function is not called too quickly

7. What would happen if the pull-up resistor on the button pin was removed?
- [ ] The LED would not turn on
- [ ] The LED would turn on and off rapidly
- [ ] The LED would turn on and stay on
- [ ] The LED would turn on and off slowly




