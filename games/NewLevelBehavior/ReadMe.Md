## Pre-requisites 
- this is a continuation from the MultiObjectDetection  project but can be completed by itself
- nodemcu 2866

### Setup
 Before we start validate the code, upload it to the board and see the results. You should see the single breakout style bar at the top of the screen. You should also see the ball bouncing around the screen, and have a functional paddle.
 Note the button pins may be different on your board, if so update the code to match your board.


# Breakout style game
Note that object collision is tricky. This approach is brute force and not the most efficient. It is however easy to understand and implement. It also introduces the concept of a struct and arrays (collections); It further expands on the idea of loops and conditional checks.

## Step 1: Create a second row of bars for level 2
- Using the existing struct create a second row of bars. Extract the code that creates the bars into a function. Call the function from setup pass in the current level.
In the setup() extract the code
```C++
 // populate bar collection
  int offsetX = (128 - (10 * 12))/2 + 1;
  for(int i = 0; i < 10; i++){
    bars[i].x = i * 12 + offsetX;
    bars[i].y = 5 + frameY;
    bars[i].width = 10;
    bars[i].height = 5;
    bars[i].visible = true;
  }
```
Create the function populateBars(int level)
```C++
void populateBars(int level){
  // populate bar collection
  int offsetX = (128 - (10 * 12))/2 + 1;
  for(int i = 0; i < 10; i++){
    bars[i].x = i * 12 + offsetX;
    bars[i].y = 5 + frameY;
    bars[i].width = 10;
    bars[i].height = 5;
    bars[i].visible = true;
  }
}
```
into a function called populateBars(int level). Call the function from setup() passing in the current level. 
```C++  
  populateBars(level);
```



# Troubleshooting
This exercise was based on initial published libraries for the maker focus board. If the Hellow world project doesn't load try these steps instead
#### Add libraries
 - click pio Home
 - click add libraries
 - search for 'esp8266 ssd1306'
 - Select "ESP8266 and ESP32 OLED driver for SSD1306 displays by ThingPulse"
 - click add to project
  - select the Hellow world project
  - click add
