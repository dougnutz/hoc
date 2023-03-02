```
#include <Arduino.h>
#include "SSD1306Wire.h"       

// Initialize the OLED display using Arduino Wire:
 SSD1306Wire display(0x3c, D3, D5);  // ADDRESS, SDA, SCL  

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
  display.drawHorizontalLine(x, 63, length);
  display.display();
}

void loop() {
  int lineWidth = 20;
  Serial.println("Begin loop...");
  display.clear();

  Serial.println("draw line...");
  drawLine(128-lineWidth,  lineWidth);
  delay(2000);
}
```