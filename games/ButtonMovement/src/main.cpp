#include <Arduino.h>
#include "SSD1306Wire.h"       

// Initialize the OLED display using Arduino Wire:
 SSD1306Wire display(0x3c, D3, D5);  // ADDRESS, SDA, SCL  
 int lineWidth = 20;
 int linePosition = 0;
 int direction = 1;

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

  if (linePosition < 128-lineWidth && direction == 1){
    drawLine(++linePosition, lineWidth);
     
  }
  else if(linePosition >0 && direction == -1){
    drawLine(--linePosition, lineWidth);
  }
  else{
          direction = direction * -1;
  }

  Serial.println("linePosition: " + String(linePosition));
  delay(100);
}