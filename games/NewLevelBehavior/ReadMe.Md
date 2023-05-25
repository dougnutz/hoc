## Pre-requisites 
- this is a continuation from the MultiObjectDetection  project but can be completed by itself
- nodemcu 2866

### Setup
 Before we start validate the code, upload it to the board and see the results. You should see the single breakout style bar at the top of the screen. You should also see the ball bouncing around the screen, and have a functional paddle.
 Note the button pins may be different on your board, if so update the code to match your board.


# Breakout style game
Reminder Note: that object collision is tricky. This approach is brute force and not the most efficient. It is however easy to understand and implement. It also introduces the concept of a struct and arrays (collections); It further expands on the idea of loops and conditional checks.

## New concepts, two dimensional arrays 
In this lesson we will expand our game by adding new rows. To track the extra block we will use a two dimensional array. We will need to modify our collision detection to itterate the new array structure. We will use this opportunity to do some code cleanup.

## Step 1: Auto play
Testing this code is getting tedious, fun but tedious. Lets automate the movement so the game plays itself. For this we start with a bool variable. We will start in autoplay mode for now and exit when any button is pressed. Add the following variable to the top of the file.
```C++  
bool autoPlay = false;
```
In the setup() function add the following code
```C++
  autoPlay = true;
```

In the main loop() add the following code to each button press.
```C++
    autoPlay = false;
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
Upload the code to the board and test it. The game should play itself. Pressing any button should exit auto play mode.
If you have any issues compare your code to the code in the Checkpoint1.md file.

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
Create the function populateBars(int level) above the resetGame() function. Paste the code into the function. Then add an int offsetY variable which we will use to make each set of bars lower on the screen than the previous set.
```C++
int offsetY =  frameY - 5;
```
Now we need to add an additional loop for dealing with the rows, the extra dimesion in our array. Add this line above the existing for loop.
```C++
  for(int ii=0; ii<5; ii++){
    <existing loop>
  }
```
Inside the outer loop we need to increment our offsetY variable. Then in the inner loop we will use it for the Y value of the bar.
Use the following code inside the outer loop to increment the offsetY variable.
```C++
    offsetY += 7;
```
In the inner loop use the offsetY variable for the Y value of the bar.
```C++
      bars[i].y = offsetY;
```
It should look like this
```C++
void populateBars(int level){
   // populate bar collection
  int offsetX = (128 - (10 * 12))/2 + 1;
  int offsetY =  frameY - 5;
  for(int ii=0; ii<5; ii++){
    //set each row down 2 pixels from the last
    offsetY += 7;
    for(int i = 0; i < 10; i++){
      bars[i].x = i * 12 + offsetX;
      bars[i].y = offsetY;
      bars[i].width = 10;
      bars[i].height = 5;
      bars[i].visible = ii<level;
    }
  }
}
```
## Step 3 Expand the bars array to be two dimensional

Now we need to modify our bars collection to be a two dimensional array. We will use the following code to create the array. Change the existing code to include a second dimension. Set it to 5.
```C++  
bar bars[5][10];
```
Note: now we have a lot of errors in our code. In a few places we can remove the code that itterates the collection and call our populateBars().

In the resetGame() remove
```C++
  for(int i = 0; i < 10; i++){
    bars[i].visible = true;
  }
```
Set ballX to a random start position
```C++
  ballX = random(0, 127);
  ```
  set gameSpeed to be 1
  ```C++
  gameSpeed = 1;
  ```
  Call populateBars() with our level variable
  ```C++  
  populateBars(level);
  ```
In the NextLevel function remove the code to set bars to visible and call populate bars with the level variable.
Remove
```C++
  for(int i = 0; i < 10; i++){
    bars[i].visible = true;
  }
  ```
  Add this to the bottom
  ```C++
  populateBars(level);
  ```
Now to fix the remaining errors.
 Everywhere that we still have code to itterate the collection we need to adjust the code. We will take advantage of special syntax and create a nested loop. The outer loop will itterate the rows and the inner loop will itterate the columns. Everywhere we itterate the loop add the following outer for loop by adding this line above the existing loop. Excluding our new populate bars function.

Add this to the top of the loop in the following places (checkBarCollision(),checkLevelCleared(), and drawBars()). Note we don't need the {}' if we add a loop directly above an existing loop. It's a special case in the syntax.

```C++
  for(int ii=0; ii<5; ii++)
```
One more thig.
It's not enough to just add the extra loop we need to modify the inner loop to loop use the extra dimension. Everywhere we have the following code
```C++
  bars[i]
``` 
We will change it to 
```C++
  bars[ii][i]
```
### Hint: you can use the find and replace feature of the editor to make this change quickly.
click Edict-> Replace. Put bars[i] in the find box and bars[ii][i] in the replace box. Click replace all.

We end up with code that looks like this
```C++
  for(int ii=0; ii<5; ii++)
    for(int i = 0; i < 10; i++){
      bars[ii][i].x = i * 12 + offsetX;
      bars[ii][i].y = offsetY;
      bars[ii][i].width = 10;
      bars[ii][i].height = 5;
      bars[ii][i].visible = true;
  }
```

Compile the code and fix any errors. If you have any issues compare your code to the code in the Checkpoint2.md file.

Deploy the code and validate that we have additional rows.

## Step 3: Make the game behavior change with levels. 
We don't actually want to start with all 5 rows. We need to tweek our populateBars() function to use the level variable to determine how many rows to show. We will use the following code to set the visible property of the bar.
```C++
  bars[ii][i].visible = ii<level;
```

Let's also tweak the game speed by changing the delay in the main loop().
Change.
```C++
  delay(1000 - (gameSpeed * 100));
```
to
```C++
  int delayTime = 50 - gameSpeed*2;
  if(delayTime < 0){
    delayTime = 0;
  }
   delay(delayTime);
```

Upload the code and validate that the game speed increases with each level, and the number of rows increases with each level. Up to 5 rows.

Now lets change up the game a bit so it doesn't always start in the same way. Inside the resetGame() function change the code that sets the ballX from a fixed number to a random value.
```C++
  ballX = random(0, 127);
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
