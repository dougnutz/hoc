## Pre-requisites 
- this is a continuation from the MultiObjectDetection  project but can be completed by itself
- nodemcu 2866

### Setup
 Before we start validate the code, upload it to the board and see the results. You should see the single breakout style bar at the top of the screen. You should also see the ball bouncing around the screen, and have a functional paddle.
 Note the button pins may be different on your board, if so update the code to match your board.


# Breakout style game
Note that object collision is tricky. This approach is brute force and not the most efficient. It is however easy to understand and implement. It also introduces the concept of a struct and arrays (collections); It further expands on the idea of loops and conditional checks.

## New concepts, two dimensional arrays 
In this lesson we will expand our game by adding new rows. To track the extra block we will use a two dimensional array. We will need to modify our collision detection to itterate the new array structure. We will use this opportunity to do some code cleanup.

## Step 1: Auto play
Testing this code is getting tedious, fun but tedious. Lets automate the movement so the game plays itself. For this we start with a bool variable. We will start in autoplay mode for now and exit when any button is pressed. Add the following variable to the top of the file.
```C++  
bool autoMove = false;
```
In the setup() function add the following code
```C++
  autoMove = true;
```

In the main loop() add the following code to each button press.
```C++
    autoMove = false;
```
for example
``` C++
if (button.isPressed()){
      Serial.println("linePosition: " + String(linePosition));
      linePosition = linePosition + lineWidth/4;
      autoPlay= false;
    }
```
Now to use autoPlay. At the top of the loop() add the following code
```C++
  if(autoPlay){
      linePosition = ballX - lineWidth/2;
    }
```

## Step 2: Create a second row of bars for level 2
Using the existing struct create a second row of bars. Extract the code that creates the bars into a function. Our function will take a level parameter. The level parameter will be used to determine how many rows of bars are visible.

In the setup() remove the code
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
Create the function populateBars(int level) above the resetGame() function
```C++
void populateBars(int level){
   // populate bar collection
  int offsetX = (128 - (10 * 12))/2 + 1;
  int offsetY =  frameY - 5;
  for(int ii=0; ii<5; ii++){
    //set each row down 2 pixels from the last
    offsetY += 7;
    for(int i = 0; i < 10; i++){
      bars[ii][i].x = i * 12 + offsetX;
      bars[ii][i].y = offsetY;
      bars[ii][i].width = 10;
      bars[ii][i].height = 5;
      bars[ii][i].visible = ii<level;
    }
  }
}
```

Now everywhere we have code to itterate the collection we need to adjust the code. We will take advantage of special syntax and create a nested loop. The outer loop will itterate the rows and the inner loop will itterate the columns. Everywhere we itterate the loop add teh following outer for loop by adding this line above the existing loop.
```C++
  for(int ii=0; ii<5; ii++)
```
It's not enough to just add the extra loop we need to modify the inner loop to loop like our populateBars() function. Everywhere we do 
```C++
  bars[i]
``` 
We will change it to 
```C++
  bars[ii][i]
```
### Hint: you can use the find and replace feature of the editor to make this change quickly.

We end up with code that looks like this
```C++
  for(int ii=0; ii<5; ii++)
    for(int i = 0; i < 10; i++){
      bars[ii][i].x = i * 12 + offsetX;
      bars[ii][i].y = offsetY;
      bars[ii][i].width = 10;
      bars[ii][i].height = 5;
      bars[ii][i].visible = ii<level;
  }
```

Ok we need to fix a few more things. Our resetGame() needs some clean up. Remove the code that sets the bars to visible, we will do that with our populate bars function so we don't need to do it in two places.
remove this code
```C++
  for(int i = 0; i < 10; i++){
    bars[i].visible = true;
  }
```
add the following code to the bottom of the function 
```C++
  gameSpeed = level;
  populateBars(level);
```

We need to do the same thing in the nextLevel() function. Remove the code that sets the bars to visible.
remove this code
```C++
  for(int i = 0; i < 10; i++){
    bars[i].visible = true;
  }
```
Add the following code to the bottom of the function
```C++
  populateBars(level);
```




## Step 3: 



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
