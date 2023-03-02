```
#include <Arduino.h>
#include "SSD1306Wire.h"       

// Initialize the OLED display using Arduino Wire:
 SSD1306Wire display(0x3c, D3, D5);  // ADDRESS, SDA, SCL  
 int lineWidth = 20;
 int linePosition = 0;

void setup() {
  // initialize com port
  Serial.begin(9600);
  Serial.println("Starting...");

  // initialize display
  display.init();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);
  display.setTextAlignment(TEXT_ALIGN_LEFT);  
}

void drawLine(int x, int length){
  Serial.println("draw line...");
  display.drawHorizontalLine(x, 63, length);
  display.display();
}

void loop() {
 
  Serial.println("Begin loop...");
  display.clear();

  if (linePosition < 128-lineWidth){
    drawLine(++linePosition, lineWidth);
     Serial.println("linePosition: " + String(linePosition));
  }
  else if(linePosition >= 128-lineWidth){
    linePosition = 0;
  }

  delay(100);
}
```