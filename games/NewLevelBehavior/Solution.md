``` c++
#include <Arduino.h>
#include "SSD1306Wire.h"   
#include <Bounce2.h>
    

// Initialize the OLED display using Arduino Wire:
 SSD1306Wire display(0x3c, D3, D5);  // ADDRESS, SDA, SCL  
 int lineWidth = 20;
 int linePosition = 64;
 int direction = 1;
 Bounce2::Button button = Bounce2::Button();
 Bounce2::Button button2 = Bounce2::Button();
  int buttonPin = D1;  //D1 is pin 5, or the pin of your choice
  int buttonPin2 = D2;  //D2 is pin 4, or the pin of your choice
  int ballX = 20;
  int frameY = 10;
  int ballY = frameY + 10;
  int ballXDirection = 1;
  int ballYDirection = 1;
  int ballSpeed = 1;
  int score = 0;
  
  struct bar{
  int x;
  int y;
  int width;
  int height;
  bool visible;
};
bar bars[5][10];
int gameSpeed= 1;
int level = 1;
bool autoPlay = false;

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

void resetGame(){
  
  ballX = random(0, 127);
  ballY = frameY+15;
  ballXDirection = 1;
  ballYDirection = 1;
  level = 1;
  gameSpeed = level;
  populateBars(level);
  }



void setup() {
  // initialize com port
  Serial.begin(9600);
  Serial.println("Starting...");

  // initialize display
  display.init();
//  display.flipScreenVertically(); uncomment this line if you want to flip the display
  display.setFont(ArialMT_Plain_10);
  display.setTextAlignment(TEXT_ALIGN_LEFT);  
  button.attach( buttonPin, INPUT_PULLUP); 
  button.interval(5); 
  button.setPressedState(LOW);
  // setup button two
  button2.attach( buttonPin2, INPUT_PULLUP); 
  button2.interval(5); 
  button2.setPressedState(LOW);
  
  resetGame();
  populateBars(level);

  // demo mode
  autoPlay = true;
}

void drawPaddle(int x, int length){
  
  display.drawHorizontalLine(x, 63, length);
  display.display();
}

void drawBall(int x, int y){
  display.setPixel(x, y);
  display.setPixel(x+1, y);
  display.setPixel(x, y+1);
  display.setPixel(x+1, y+1);
}

bool checkBarCollision(){
  bool collision=false;
  for(int ii = 0; ii < 5; ii++)
  for(int i = 0; i < 10; i++){
    if(bars[ii][i].visible){
      if(ballX > bars[ii][i].x && ballX < bars[ii][i].x + bars[ii][i].width && ballY > bars[ii][i].y && ballY < bars[ii][i].y + bars[ii][i].height){
        bars[ii][i].visible = false;
        collision = true;
        score ++;
      }
    }
  }
  return collision;
}

bool checkLevelCleared(){
  bool cleared = true;
  for(int ii = 0; ii < 5; ii++)
  for(int i = 0; i < 10; i++){
    if(bars[ii][i].visible){
      cleared = false;
    }
  }
  return cleared;
}

void nextLevel(){
  gameSpeed++;
  level++;
  populateBars(level);
}

void moveBall(){
  ballX = ballX + ballXDirection * ballSpeed;
  ballY = ballY + ballYDirection * ballSpeed;

  if(checkBarCollision()){
    ballYDirection *= -1;
  }

  if(checkLevelCleared()){
    nextLevel();
  }

  if(ballX > 126){
    ballXDirection = -1;
  }
  if(ballX < 2){
    ballXDirection = 1;
  }
  if(ballY > 63){
    //game over
    Serial.println("Game Over");
    int over = 0;
    while(over++ <1000 ){
      display.clear();
      display.drawString(0, 0, "Game Over");
      display.display();
    }
    // reset the game
    resetGame();
    score = 0;
    gameSpeed = 0;
   }
  if(ballY < frameY + 2){ 
    ballYDirection = 1;
  }
  if(ballY > 62 && ballX > linePosition && ballX < linePosition + lineWidth){
    ballYDirection = -1;
  }
  
  drawBall(ballX, ballY);
}

void drawBars(){
  for(int ii = 0; ii < 5; ii++)
  for(int i = 0; i < 10 ; i++){
    if(bars[ii][i].visible){
      display.fillRect(bars[ii][i].x, bars[ii][i].y, bars[ii][i].width, bars[ii][i].height);
    }
  }
}

void loop() {
  display.clear();

  // draw a frame, we will use a rectangle and start 10 pixels from the top  
  display.drawRect(0,frameY,128,64);
  drawBars();

  // draw the ball
  moveBall();

  display.drawString(0, 0,  "Score: " + String(score));
  display.drawString(80, 0,  "Level: " + String(level));
 
  // update the button state 
  button.update();
  button2.update();

    if(autoPlay){
      linePosition = ballX - lineWidth/2;
    }
  
   // check to see if the button is pressed, if so move the line to the right 10 pixels
    if (button.isPressed()){
      Serial.println("linePosition: " + String(linePosition));
      linePosition = linePosition + lineWidth/4;
      autoPlay= false;
    }

    if(button2.isPressed()){
      Serial.println("linePosition: " + String(linePosition));
      linePosition = linePosition - lineWidth/4;
      autoPlay= false;
    }

    // if the line is off the screen move it back to the left side
    if (linePosition > 128 + lineWidth/2){
      linePosition = 0;
    }
    else if (linePosition < 0 - lineWidth/2){
      linePosition = 128;
    }

    // draw the line
    drawPaddle(linePosition, lineWidth);

   // set the delay time to 50 minus the game speed times 2 with a minimum of 0
  // this will speed up the game as the levels increase
  int delayTime = 50 - gameSpeed*2;
  if(delayTime < 0){
    delayTime = 0;
  }
   delay(delayTime);
 
}
```