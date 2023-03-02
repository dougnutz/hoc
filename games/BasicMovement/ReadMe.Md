## Hardware 
- nodemcu 2866
- maker focus (or similar) ssd1306 display
### Wire up the display 
- mount the chip and display to a bread board 
![image](https://user-images.githubusercontent.com/20483619/169121210-d8eda466-2b1d-4b4a-9aca-6b1b6363d88f.png)

- and connect the dispaly as shown

![image](https://user-images.githubusercontent.com/20483619/169120605-9e6c0a78-203f-4a8c-90f0-8fa44f1eb1e5.png)

#### Add libraries
 - click pio Home
 - click add libraries
 - search for 'esp8266 ssd1306'
 - Select "ESP8266 and ESP32 OLED driver for SSD1306 displays by ThingPulse"
 - click add to project
    - select the BasicMovement project
    - click add

#### Add the code
    - open the src/main.cpp file
        - add `#include "SSD1306Wire.h" ` to the top of the file
        - Initialize the display
        - Add the comment '// Initialize the OLED display using Arduino Wire:'
        - add `SSD1306Wire display(0x3c, 5, 4);` to the top of the file
    - in the setup function add the following lines
        - '// initialize com port'
        - `Serial.begin(9600);`
        - `Serial.println("Begin loop...");`
        - `// initialize display`
        - `display.init();`
        - `display.flipScreenVertically();`
        - `display.setFont(ArialMT_Plain_10);`
        - `display.setTextAlignment(TEXT_ALIGN_LEFT);`
        

    - in the loop function add the following lines
        - `display.clear();`
        - `display.drawString(0, 0, "Hello World");`
        - `display.display();`
        - `delay(2000);`

#### Checkpoint 1
- run the program
- the screen should display "hello world"
- see the Checkpoint1.md file for a working solution


### draw a short line at the bottom of the screen
- Delete the hellow world code from the loop function
- add the following line to the loop function
  - `display.drawHorizontalLine(0, 40, 20);`

- run the program
- is the line at the bottom? If not make changes to put the line at the bottom
- hint the display resolution is 128x64

- now extract the line to a function
  - add the following function above the loop function
    - `void drawLine(int x,  int length)`
  - add the following lines to the function
    - `display.drawHorizontalLine(x, 63, length);`
    - `display.display();`

  - call the function from the loop function
    - 'Serial.println("draw line...");'
    - `drawLine(0, 20);`

- run the program


### move the line to the right side of the screen
- How can we move the line to the right side of the screen using math?
- start by adding a variable to track the line width 
- add the line
  - `int lineWidth = 20;`
- hint the display resolution is 128x64
- hint the line starts at x which is the left side of the line
   - `drawLine(128-lineWidth,  lineWidth);`

- run the program


#### Checkpoint 2
- see the Checkpoint2.md file for a working solution

### Create a loop that moves the line from the left to the right side of the screen
- add the following line to the loop function
  - `int linePosition = 0;`
- add the following lines to the loop function
- increase the speed of the loop by changing the delay to 200
    - `delay(200);`
- now if the line is not at the edge of the screen then increment the line position
  - ```
        if(linePosition < 128){}
          drawLine(--linePosition, lineWidth);
          }
    ```
- add the following lines to the bottom loop function above the delay
  - `Serial.println("linePosition: " + String(linePosition));`
 
- run the program
- the line should move from the left to the right side of the screen
- what else happened? Why?

How can we check to see if we are at the edge of the screen?
- change the if statement to check if the line position is less than the line width
  - `if (linePosition < 128-lineWidth){`

- run the program
- did it work as expected

#### Checkpoint 3
- see the Checkpoint3.md file for a working solution

### low lets make the line move back and forth
- add the following line to the file with the other loop variables       
    - `int direction = 1;`      
- modify the code to check the direction and move the line in the correct direction
- add the following lines to the loop function
    - ```
        if (linePosition < 128-lineWidth && direction == 1){
          drawLine(++linePosition, lineWidth);
          Serial.println("linePosition: " + String(linePosition));
        }
        else if (linePosition > 0 && direction == -1){
          drawLine(--linePosition, lineWidth);
          Serial.println("linePosition: " + String(linePosition));
        }
        else{
          direction = direction * -1;
        }
    ```

- run the program
- the line should move back and forth

#### Checkpoint 4
- see the Checkpoint4.md file for a working solution

### add a button to the breadboard
- add a button to the breadboard
  - connect one side of the button to ground
  - connect the other side of the button to pin 16
#### add a debounce library
 click pio Home
 - click add libraries
 - search for 'Bounce2'
 - clickBounce2 by Thomas O Fredericks
  - click add to project
      - select the BasicMovement project
      - click add


- add the following line to the top of the file
  - `#include <Bounce2.h>`  
- add the following lines to the top of the file
    - ```
        Bounce2::Button button = Bounce2::Button();
        int buttonPin = D1;
        ```
- add the following lines to the setup function

    - ```
        button.attach( buttonPin, INPUT_PULLUP); 
        button.interval(5); 
        button.setPressedState(LOW); 
        ```
- add the following lines to the loop function
    - ```
      button.update();
        if (button.isPressed()){
          Serial.println("button pressed");
        }
        ```
- remove 
 ```
    else{
              direction = direction * -1;
      }
  ```
- run the program
- depending on the loop speed the button pressed may not get detected. We are only checking the button state once every loop. How can we check the button state more often?

#### Checkpoint 5

- see the Checkpoint5.md file for a working solution


## Troubleshooting
This exercise was based on initial published libraries for the maker focus board. If the Hellow world project doesn't load try these steps instead
#### Add libraries
 - click pio Home
 - click add libraries
 - search for 'esp8266 ssd1306'
 - Select "ESP8266 and ESP32 OLED driver for SSD1306 displays by ThingPulse"
 - click add to project
  - select the Hellow world project
  - click add
