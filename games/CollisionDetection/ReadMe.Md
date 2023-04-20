## Pre-requisites 
- this is a continuation from the button movement project but can be completed by itself
- nodemcu 2866

### Checkpoint 1
 Before we start validate the code, upload it to the board and see the results. You should see the line and it should move with button presses.
 Note the button pins may be different on your board, if so update the code to match your board.


## Step 1 the frame
### Modify the loop() function
- add a rectangle on the perimeter of the screen
- use the following code
```c++
  display.drawRect(0, 0, 128, 64);
```

#### checkpoint 2
- upload the code to the board and see the results

## Step 2 the ball
### Modify the loop() function
- add a pixel to the screen
- use the following code
```c++
  display.setPixel(64, 32);
```
- run the code and see the results
- the ball seems small, lets make it bigger
- use the following code
```c++
  display.setPixel(64, 32);
  display.setPixel(65, 32);
  display.setPixel(64, 33);
  display.setPixel(65, 33);
```
- run the code and see the results

## Make the ball move
First lets refactor the draw ball code into a function
- Above the loop() add a new method called drawBall() which takes two parameters x and y
- use the following code
```c++
void drawBall(int x, int y){
  display.setPixel(x, y);
  display.setPixel(x+1, y);
  display.setPixel(x, y+1);
  display.setPixel(x+1, y+1);
}
```
- now call the drawBall() method from the loop() method
- replace the Display.setPixel() code block with the following code
```c++
  drawBall(64, 32);
```
- run the code and see the results validate the ball is still there
- now lets make the ball move
- add a new variable called ballX to the top of the file and set it to 64, this will be the x position of the ball.
- use the following code
```c++
int ballX = 0;
```
- now add a new variable called ballY to the top of the file and set it to 32, this will be the y position of the ball.
- use the following code
```c++  
int ballY = 0;
```
- change your drawBall() function call to use the ballX and ballY variables

```c++
  drawBall(ballX, ballY);
```

- add a new variable called ballXDirection to the top of the file and set it to 1, this will be the direction of the ball in the x direction.
- use the following code
```c++
int ballXDirection = 1;
```
- add a new variable called ballYDirection to the top of the file and set it to 1, this will be the direction of the ball in the y direction.
- use the following code
```c++
int ballYDirection = 1;
```
- add a new variable called ballSpeed to the top of the file and set it to 1, this will be the speed of the ball.
- use the following code
```c++
int ballSpeed = 1;
```
- lets make the ball move
- add the following code to the loop() method
```c++
  ballX = ballX + ballXDirection * ballSpeed;
  ballY = ballY + ballYDirection * ballSpeed;
```
- RUN the code and see the results

- NOW lets make the ball bounce off the walls
- add the following code to the loop() method
```c++
  if(ballX > 126){
    ballXDirection = -1;
  }
  if(ballX < 2){
    ballXDirection = 1;
  }
  if(ballY > 62){
    ballYDirection = -1;
  }
  if(ballY < 2){
    ballYDirection = 1;
  }
```
- RUN the code and see the results

- lets refactor the ball movement code into a function
- Above the loop() add a new method called moveBall() which takes no parameters
- use the following code
```c++
void moveBall(){

}
```
- move the following code from the loop() method into the moveBall() method
```c++
    ballX = ballX + ballXDirection * ballSpeed;
  ballY = ballY + ballYDirection * ballSpeed;

  if(ballX > 126){
    ballXDirection = -1;
  }
  if(ballX < 2){
    ballXDirection = 1;
  }
  if(ballY > 62){
    ballYDirection = -1;
  }
  if(ballY < 2){
    ballYDirection = 1;
  }
  drawBall(ballX, ballY);
```
- now call the moveBall() method from the loop() method
- use the following code
```c++
  moveBall();
```

- run the code and verify the ball still moves properly

#### checkpoint 3
- The ball should move around the screen and bounce off the walls. If there are issues check the code against the solution checkpoint3.md

## Step 3 move the frame down
- now move the rectangle down 10 pixels
- we will also need a new variable to keep track of the frame position. Add a new variable called frameY to the top of the file and set it to 10, this will be the y position of the frame.
- add the following code
```c++
int frameY = 10;
```
- also change the ballY variable to the frameY variable +1;
- use the following code
```c++
int ballY = frameY + 1;
```
- now change the drawRect() method call to use the frameY variable
- use the following code
```c++
  display.drawRect(frameX, 0, 128, 64);
```
- we also need to change the limit detection of the ball
- change the following code
```c++
  if(ballY < 2){ 
    ballYDirection = 1;
  }
```
- to the following code
```c++
  if(ballY < frameY + 2){ 
    ballYDirection = 1;
  }
```
- run the code and verify the results
#### checkpoint 4
- The ball should move around the screen and bounce off the walls in the new position. If there are issues check the code against the solution checkpoint4.md

## Step 4 lets detect the collision
- if the ball encounters the paddle we want to change the direction of the ball
- we know the position of the paddle based on the variable linePosition. We also know the position of the ball based on the variables ballX and ballY
- we can detect the collision by checking if the ball is at the bottom of the screen and within the paddle
- add the following code to the moveBall() method above the drawBall() method call
```c++
  if(ballY > 62 && ballX > linePosition && ballX < linePosition + lineWidth){ 
    ballYDirection = -1;
  }
```
- if the ball is at the bottom of the screen and not within the paddle we want to end the game
  - replace the following code
  ```c++
  if(ballY > 62){
    ballYDirection = -1;
  }
  ```
  - with the  code
```c++
   if(ballY > 63){
    //game over
    Serial.println("Game Over");
    int over = 0;
    while(over++ <1000 ){
      display.clear();
      display.drawString(0, 0, "Game Over");
      display.display();
      delay(100);
    }
    // reset the game
    ballX = 2;
    ballY = 2;
   }


## Step 3 the score
- Ok we want to keep
- add a new variable called score to the top of the file and set it to 0, this will be the score.
- use the following code
```c++
int score = 0;
```
- now add the word score to the top of the screen
- use the following code inside the loop() method
```c++
  display.drawString(0, 0, "Score: "+ String(score));
```


- everytime the ball touches the paddle add 1 to the score, iside the collision detection code add the following code.
```c++
    score++;
```

## WOW that is a lot of code
Verify the code works and if it doesn't verify it against the checkpoint5.md file

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
