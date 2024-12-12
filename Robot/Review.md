# C++ and arduino basics


### Variable Definitions
```cpp
uint8_t b = 255; // 0 to 255
short g = 32000; // -32768 to 32767
int a = 10; // -2,147,483,648 to 2,147,483,647
unsigned int h = 40000; // 0 to 65,535
long f = 1234567890; // -2,147,483,648 to 2,147,483,647
float b = 5.5; // 7 decimal places
char c = 'A'; // Single quotes for single characters
bool d = true; // or false
double e = 3.14159; // 15 decimal places

```

### Operators
```cpp
int a = 10, b = 5;
bool isEqual = (a == 10); // true
bool isNotEqual = (a != 5); // true

//AND operator "&&" , returns true if both the operands are true.
bool logicalAnd = (a > 5 && b < 10); // true
bool logicalOr = (a > 5 || b < 10); // true
bool logicalNot = !(a == 5); // true
a += 5; // a = a + 5, a = 15
a++;    // Increment a by 1, a = 16
a--;    // Decrement a by 1, a = 15

// NOT operator "!" , inverts the result. If the result is true, it gives false and vice versa.
bool isNotEqual = !(a == 5); // true

// null coalescing operator "??"
int result = a ?? b; // if a is not null, result = a, else result = b
```

### Conditional Operators
```cpp
if (a > 5) {
    // Do something
} else {
    // Do something else
}

// Ternary operator
int result = (a > 5) ? /* Do something */ : /* Do something else */;

// Switch-case
switch (a) {
    case 1: // If a is 1
        // Do something
        break;
    case 2: // If a is 2
        // Do something
        break;
    case 3: 
    case 4: // If a is 3 or 4
        // Do something
        break;
    default: // anything else
        // Do something 
        break;
}

```

### Loops
```cpp
// For loop
for (int i = 0; i < 10; i++) {
    // Do something
}

// While loop
int i = 0;
while (i < 10) {
    // Do something
    i++;
}

// Do-while loop
i = 0;
do {
    // Do something
    i++;
} while (i < 10);
```

### Function Declarations
```cpp
int add(int x, int y) { // return type, function name, parameters
    return x + y;
}
```

### Array Declaration and Initialization
```cpp
int numbers[5] = {1, 2, 3, 4, 5}; // Array of 5 integers, value assignment is optional
```

### Class Declaration and Usage
```cpp
class Robot {
public:
    void move() {
        // Move the robot
    }
};

Robot myRobot;
myRobot.move();
```

## Arduino Basics

### Pin Writes
```cpp
void setup() {
    pinMode(13, OUTPUT);
}

void loop() {
    digitalWrite(13, HIGH); // Turn the LED on
    delay(1000);            // Wait for a second
    digitalWrite(13, LOW);  // Turn the LED off
    delay(1000);            // Wait for a second
}
```

### Serial Outputs
```cpp
void setup() {
    Serial.begin(9600);
}

void loop() {
    Serial.println("Hello, Arduino!");
    delay(1000); // Wait for a second
}
```
### Additional Variable Types
```cpp
short int si = 100;
unsigned short int usi = 200;
```

### Analog Write
```cpp
void setup() {
    pinMode(9, OUTPUT);
}

void loop() {
    analogWrite(9, 128); // Write a PWM signal with 50% duty cycle
    delay(1000);         // Wait for a second
}
```