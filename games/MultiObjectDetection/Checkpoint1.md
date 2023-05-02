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
  int ballX = 5; // ball start point
  int frameY = 10;
  int ballY = frameY + 1;
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
bar bars[10];

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

// populate bar collection
  for(int i = 0; i < 10; i++){
    bars[i].x = i * 12 
    bars[i].y = 5;
    bars[i].width = 10;
    bars[i].height = 5;
    bars[i].visible = true;
  }

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

void moveBall(){
  ballX = ballX + ballXDirection * ballSpeed;
  ballY = ballY + ballYDirection * ballSpeed;



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
    ballX = 2;
    ballY = 2;
    score = 0;
   }
  if(ballY < frameY + 2){ 
    ballYDirection = 1;
  }
  if(ballY > 62 && ballX > linePosition && ballX < linePosition + lineWidth){
    ballYDirection = -1;
    score++;
  }
  
  drawBall(ballX, ballY);
}

void loop() {
  display.clear();

  // draw a frame, we will use a rectangle and start 10 pixels from the top  
  display.drawRect(0,frameY,128,64);

  // draw the ball
  moveBall();

  display.drawString(0, 0, "Score: "+ String(score));
 
  // update the button state 
  button.update();
  button2.update();
  
   // check to see if the button is pressed, if so move the line to the right 10 pixels
    if (button.isPressed()){
      Serial.println("linePosition: " + String(linePosition));
      linePosition = linePosition + 10;
    }

    if(button2.isPressed()){
      Serial.println("linePosition: " + String(linePosition));
      linePosition = linePosition - 10;
    }

    // if the line is off the screen move it back to the left side
    if (linePosition > 128){
      linePosition = 0;
    }
    else if (linePosition < 0){
      linePosition = 128;
    }

    // draw the line
    drawPaddle(linePosition, lineWidth);

   
   delay(100);
 
}
```