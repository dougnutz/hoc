#include <Arduino.h>


const int green = 14; 
const int blue = 13;
const int on = PWMRANGE;
const int off = LOW;

void printOut(String s){
  Serial.println(s);
}

void setup() {
  Serial.begin(9600);
}

// the loop function runs over and over again forever
void loop() {

    printOut("begin loop");
    printOut("green on");
    analogWrite(green, on);

// delay 1000

    printOut("green off");
analogWrite(green, off);

 delay(500);


}