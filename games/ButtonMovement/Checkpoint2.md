```
#include <Arduino.h>
#include "SSD1306Wire.h"    
#include <Bounce2.h>   

// Initialize the OLED display using Arduino Wire:
 SSD1306Wire display(0x3c, D3, D5);  // ADDRESS, SDA, SCL  
 int lineWidth = 20;
 int linePosition = 0;
 int direction = 1;
 Bounce2::Button button = Bounce2::Button();
 int buttonPin = D1;

void setup() {
  // initialize com port
  Serial.begin(9600);
  Serial.println("Starting...");

  // initialize display
  display.init();

  button.attach( buttonPin, INPUT_PULLUP ); 
  button.interval(5); 
  button.setPressedState(LOW); 
}

void drawLine(  int x, int length){
  Serial.println("draw line...");
  display.drawHorizontalLine(x, 63, length);
  display.display();
}

void loop() {
 
  Serial.println("Begin loop...");
  display.clear();

  button.update();
    if (button.pressed()){
      Serial.println("button pressed");
      direction = direction * -1;
    }

  if (linePosition < 128-lineWidth && direction == 1){
    drawLine(++linePosition, lineWidth);
     
  }
  else if(linePosition >0 && direction == -1){
    drawLine(--linePosition, lineWidth);
  }
  

  Serial.println("linePosition: " + String(linePosition));
  delay(100);
}
```