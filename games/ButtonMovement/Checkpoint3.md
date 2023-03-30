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
  int buttonPin = D1;  //D1 is pin 5, or the pin of your choice

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
}

void drawLine(int x, int length){
  Serial.println("linePosition: " + String(linePosition));
  display.drawHorizontalLine(x, 63, length);
  display.display();
}

void loop() {
  display.clear();
  button.update();
  
   // check to see if the button is pressed, if so move the line to the right 10 pixels
    if (button.isPressed()){
      Serial.println("button pressed");
      linePosition = linePosition + 10;
    }

    // if the line is off the screen move it back to the left side
    if (linePosition > 128){
      linePosition = 0;
    }

    // draw the line
    drawLine(linePosition, lineWidth);

   
   delay(100);
 
}
```