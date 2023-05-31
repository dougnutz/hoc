#include <Arduino.h>
#include <Arduboy2.h>

// put function declarations here:
Arduboy2 arduboy;

void setup() {
 // initiate arduboy instance
  arduboy.begin();

  // here we set the framerate to 15, we do not need to run at
  // default 60 and it saves us battery life
  arduboy.setFrameRate(15);
}

void loop() {
  // pause render until it's time for the next frame
   if (!(arduboy.nextFrame()))
     return;

  // first we clear our screen to black
  arduboy.clear();

  // we set our cursor 5 pixels to the right and 10 down from the top
  arduboy.setCursor(4, 9);

  // then we print to screen what is in the Quotation marks ""
  arduboy.print(F("Hello, World!"));

  // then we finaly we tell the arduboy to display what we just wrote to the display
  arduboy.display();
}
