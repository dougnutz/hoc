## Pre-requisites 
- this is a continuation from the basic movement project but can be completed by itself
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

### Checkpoint 
Run the program and make sure you have a line that moves back and forth across the screen.

    

### add a button to the breadboard
- add a button to the breadboard
  - connect one side of the button to ground
  - connect the other side of the button to pin 16 (D1)

#### Add the code
 click pio Home
 - click add libraries
 - search for 'Bounce2'
 - clickBounce2 by Thomas O Fredericks
  - click add to project
      - select the BasicMovement project
      - click add

- open the src/main.cpp file

- add the following line to the top of the file
  ```
  #include <Bounce2.h>
- add the following lines to the top of the file above the setup function
  ```
    Bounce2::Button button = Bounce2::Button();
    int buttonPin = D1;  //D1 is pin 16, or the pin of your choice
        
- add the following lines to the setup function

  ```
    button.attach( buttonPin, INPUT_PULLUP); 
    button.interval(5); 
    button.setPressedState(LOW); 
      
- add the following lines to the loop function, below the begin loop and display.clear()
  ```
  button.update();
    if (button.isPressed()){
      Serial.println("button pressed");
      direction = direction * -1;
    }
       
- remove 
  ```
      else{
                direction = direction * -1;
        }
    ```
- run the program
- depending on the loop speed the button pressed may not get detected. We are only checking the button state once every loop. How can we check the button state more often?

Does the program work as expected? 
What happens when you press the button? What happens when you hold the button down?

#### Checkpoint 2

- see the Checkpoint2.md file for a working solution

## lets change the behavior of the button to move the line to the right only
 - remove everything from the loop method
 Add the following code to the loop method
 ```
   display.clear();
   button.update();

   delay(100);
 ```

- add the following code between the button.update() and the printLine()
```
    // check to see if the button is pressed, if so move the line to the right 10 pixels
    if (button.isPressed()){
      Serial.println("button pressed");
      linePosition = linePosition + 10;

    // if the line is off the screen move it back to the left side
    if (linePosition > 128){
      linePosition = 0;
    }

    // draw the line
    drawline(linePosition, lineWidth);
```

### Note to reduce the spam in the console outputmove `Serial.println("linePosition: " + String(linePosition)); ` to the end of the drawLine method

#### Checkpoint 3 
- see the Checkpoint3.md file for a working solution


### lets add a second button
- add a second button to the breadboard
  - connect one side of the button to ground
  - connect the other side of the button to pin 4 (D5)

#### Add the code
- open the src/main.cpp file
 - at the top of the file
   - add a new button variable (example use "button2")
   - add a new pin variable
 - In the setup method add line to setup the new button in the same way as we did for the first button
 - In the loop method
    - add a new button2 update
    - add a new if statement to check the new button2 state
    - add a new line to move the line to the left 10 pixels
    - add an else check to see if the line is off the screen and move it back to the right side

#### Note: further reduce the console spam by moving the linePosition print to inside the button isPressed check

### Checkpoint 4
- see the Checkpoint4.md file for a working solution


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
