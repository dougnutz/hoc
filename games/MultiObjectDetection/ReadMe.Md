## Pre-requisites 
- this is a continuation from the collision detection project but can be completed by itself
- nodemcu 2866

### Checkpoint 1
 Before we start validate the code, upload it to the board and see the results. You should see the line and it should move with button presses. The ball should be moving and bouncing off the walls. There should be a score in the upper left corner. 
 Note the button pins may be different on your board, if so update the code to match your board.


# Breakout style game
Note that object collision is tricky. This approach is brute force and not the most efficient. It is however easy to understand and implement. It also introduces the concept of a struct and arrays (collections); It further expands on the idea of loops and conditional checks.

## Step 1 Draw a collection of bars at the top of the screen
- create a new function called drawBars. The function should populate a collection of bar objects
The visibility or existence of the bar will be determined by a boolean value. Collision of the ball object will toggle the visibility to false.
- add the following code to the top of the file
```c++
struct bar{
  int x;
  int y;
  int width;
  int height;
  bool visible;
};
```
- create a collection of bars
``` c++
bar bars[10];
```
 - populate the collection of bars in the setup function
```c++
for(int i = 0; i < 10; i++){
    bars[i].x = i * 12;
    bars[i].y = 20;
    bars[i].width = 10;
    bars[i].height = 5;
    bars[i].visible = true;
  }
```

- create a function called drawBars
```c++
void drawBars(){
  for(int i = 0; i < 10; i++){
    if(bars[i].visible){
      display.fillRect(bars[i].x, bars[i].y, bars[i].width, bars[i].height);
    }
  }
}
```
- call the drawBars function from the loop function
```c++
drawBars();
```

- deploy the code and validate the bars are drawn at the top of the screen.
- use checkpoint1.MD if you are having trouble

## step 2 center the bars
-Ok so it seems the bars are not positioned correctly on the screen
- update the population of the drawbars to use the frameY variable
change this
```c++  
bars[i].y = 20;
```
to this
```c++
bars[i].y = 20 + frameY;
```

- deploy the code and validate the bars are drawn correctly on the screen.

- now we need to center the bars in the screen using the screen width. To do this we will update the populate bars collection to use the screen width.
add this above the populate bars section of code
```c++
int offsetX = (128 - (10 * 12))/2 + 1;
``` 
 - deploy the code and validate the bars are centered on the screen.

- use checkpoint2.MD if you are having trouble

## Step 3 detect collision with the bars
- create a function called checkBarCollision, add this code above the moveBall function

```c++
bool checkBarCollision(){
  bool collision=false;
  for(int i = 0; i < 10; i++){
    if(bars[i].visible){
      if(ballX > bars[i].x && ballX < bars[i].x + bars[i].width && ballY > bars[i].y && ballY < bars[i].y + bars[i].height){
        bars[i].visible = false;
        collision = true;
      }
    }
  }
  return collision;
}
```
Call the checkBarCollision function from the moveBall function. If there is a collision reverse the ball direction in the Y axis.
```c++
if(checkBarCollision()){
    ballYDirection *= -1;
  }
```

- deploy the code and validate the bars are removed when the ball hits them.

- a Bug? it seems the ball is not bouncing off the top of the bars at the start of the game. Let's update the ballX to start the ball below the bars.
```c++
ballY = frameY+10;
``` 
# Step 4 detect a cleared level
- create a function called checkLevelCleared, add this code above the moveBall function
```c++  
bool checkLevelCleared(){
  bool cleared = true;
  for(int i = 0; i < 10; i++){
    if(bars[i].visible){
      cleared = false;
    }
  }
  return cleared;
}
```
- call the checkLevelCleared function from the moveBall function. If the level is cleared reset the bars to visable.
Add this code below the check for collision.
```c++
if(checkLevelCleared()){
    for(int i = 0; i < 10; i++){
      bars[i].visible = true;
    }
  }
```
- does it work?
### Tip if we start the ball above the row we can clear the bars quickly. How would we do that?

- use checkpoint3.MD if you are having trouble
  
## Bugs, let's do a little cleanup  
- So here are some of the bugs we may have seen
    - Bug the game over screen doesn't reset the bars
    - Bug the ball starts above the bars on game reset
- lets create a resetGame function to address some of these in one place. Add this function above the setUp function. Yep above SetUP. Why would we do that? so we can call it from anywhere in the code, including setup. Then we can remove the code from setup and call the function instead.

```c++
void resetGame(){
  for(int i = 0; i < 10; i++){
    bars[i].visible = true;
  }
  ballX = 64;
  ballY = frameY+10;
  ballXDirection = 1;
  ballYDirection = 1;
}
```
- add resetGame to the bottom of the setup function, and where we display "Game Over"
```c++  
resetGame();
```
change 
```c++
ballX = 2;
ballY = 2;
```
to
```c++
resetGame();
```

- deploy the code and validate the bars are reset on game over and the ball starts below the bars.

- as an enhancement we could add a level counter and increase the speed of the ball as the levels increase.
## Step 5 next level
- create a function called nextLevel, add this code above the moveBall function
```c++
void nextLevel(){
  for(int i = 0; i < 10; i++){
    bars[i].visible = true;
  }
  resetGame();

}
```
- call the nextLevel() when the level is cleared. Change the code below the check for collision from this
```c++
if(checkLevelCleared()){
    for(int i = 0; i < 10; i++){
      bars[i].visible = true;
    }
  }
```
to this
```c++
if(checkLevelCleared()){
    nextLevel();
  }
```
- deploy the code and validate the bars are reset on game over.
- now for the ball speed, if we just increase ballSpeed the ball will skip pixels. We need to make the whole game faster. Let's create a variable called gameSpeed and increase it by 1 each time the level is cleared. Add this code at the top of the file.
```c++
int gameSpeed = 1;
```
- update the loop function to use the gameSpeed variable
```c++
delay(100/gameSpeed);
```

- in the nextLevel function increase the gameSpeed by 1, add this line to the end of the function.
```c++
gameSpeed++;
```
- deploy the code and validate the game speed increases as the levels increase.

- use checkpoint4.MD if you are having trouble

## Step 6 add level and update the score calculation
- create a variable called level and set it to 1. Add this code at the top of the file.
```c++
int level = 1;
```
- update the nextLevel function to increase the level by 1. Add this line to the end of the function.
```c++
level++;
```
- Don't forget to reset the level in the resetGame function.
```c++
level = 1;
```
- update the score display to include the level. Let's display the score on the left side and the level on the right side. The format should look like "score:  1      level:  1". Display the level on the same x axis but start at a position about half way across the screen. Change this line
```c++
display.drawString(0, 0, "Score: " + String(score));
```
to this
```c++
display.drawString(0, 0,  "Score: " + String(score));
display.drawString(50, 0,  "Level: " + String(level));
```
- last lets update the logic to increment the score when a block is hit. Remove this line from the bottom of the moveBall function.
```c++
score++;
```
and add it to the checkBarCollision function.
```c++
bool checkBarCollision(){
  bool collision=false;
  for(int i = 0; i < 10; i++){
    if(bars[i].visible){
      if(ballX > bars[i].x && ballX < bars[i].x + bars[i].width && ballY > bars[i].y && ballY < bars[i].y + bars[i].height){
        bars[i].visible = false;
        collision = true;
        score ++;
      }
    }
  }
  return collision;
}
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
