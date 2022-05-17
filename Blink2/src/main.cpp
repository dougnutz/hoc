#include <Arduino.h>


const int red = 14; 
// const int green = pick a gpio port;
const int on = 400;
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
    printOut("red on");
    analogWrite(red, on);

    // printOut("green on");
    // turn off the green led

 delay(1000);

    printOut("red off");
    analogWrite(red, off);

    // printOut("green on");
    // turn on the green led

 delay(500);


}