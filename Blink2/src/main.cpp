#include <Arduino.h>


const int red = 14; 
const int blue = 12;

void printOut(String s){
  Serial.println(s);
}

void setup() {
  Serial.begin(9600);
}

// the loop function runs over and over again forever
void loop() {

    printOut("begin loop");
    analogWrite(red, PWMRANGE);
    analogWrite(blue, LOW);
    delay(500);

    analogWrite(red, LOW);
    analogWrite(blue, PWMRANGE);
    delay(500);
               
}