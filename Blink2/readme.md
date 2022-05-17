## what you will need
- ESP8266 board (preferably NodeMCU)
- usb cable
- breadboard
- two led's
- aproximately 200 ohm resistor (up to 1k ohm should work)
## hardware setup
- Mount the esp8266 board to a bread board.
- ensure the usb is connected from the board to the computer
- bridge the ground pin to the ground strip (-) on the breadboard with the resistor
- connect the led between the ground strip and the D5 pin. This is gpio 14
  - note the led's only work one way. Usually the short leg is ground and is insterted into the ground strip. If it doesn't work try it the other way.
- use the pinout to determine the correct pins
![image](https://user-images.githubusercontent.com/20483619/168912683-4119300e-6e0c-4104-9535-d45b7763dc68.png)

- load the blink 2 program in the VS IDE
- note the const "red" is assigned the value 14. This correlates to gpio 14 or pin d4
## checkpoint
- upload the program to the arduino and verify the led blinks

## try blinking another one
- pick a second led (green) and uncomment the line for the variable. 
- pick a gpio port from the pinout
- assign the port to the variable
- uncomment and impliment the lines to turn the second led off then on, with the opposite patter to the red led. It should flash red, green, red etc.
