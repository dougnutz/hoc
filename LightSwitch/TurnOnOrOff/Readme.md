#Turn On Or Off
This is the embeded client that will control a relay board. It will send a request to the server and get the response. If the response is "on" then the relay will turn on, if the response is "off" it will turn off.
In any other case we don't change state. We should however emit the reponse to the serial port for debugging.

## prerequisites
You should have completed the following tutorials:
 - [Blink]()
 - [WebRead]()

## Hardware
 - NodeMCU
 - LED
 - 200 -1k Ohm resistor
 - Relay board ideally one capable of taking 3.3 v input. 

 ## Steps
 ### Header files   
- We will begin by making a request to the server and get the response. To do that you will need to include the WebRead library.
```
#include <WebRead.h>
```
- define the ssid and password of your network variable for your network
```
char ssid[] = "network id (SSID)"; 
char pass[] = "netowrk password";
```
- Also define the url of the server
```
char url[]="http://hocfun.azurewebsites.net/api/echo?code=<code>&name=<your name>";
```
- Define the pin that will be used for the LED
```
int ledPin = 2;
```
### setup()
- We need to setup the serial port for communication
```
Serial.begin(9600);
```
- Add an initial print statement
```
Serial.println("Begin loop ... ");
```
- set pin mode
```
pinMode(pin, OUTPUT);
```
- Connect to the network
```
webread.connect(ssid, pass);
``` 

### loop()
- Make a request to the server
```
String response = webread.get(url);
```
- Print the response to the serial port
```
Serial.println(response);
```
- if "on" turn the pin on, if off turn it off. Otherwise do nothing
```
if (response == "on") {
  digitalWrite(ledPin, HIGH);
} else if (response == "off") {
    digitalWrite(ledPin, LOW);
}
```
- wait for 2 seconds
```
delay(2000);
```

### Check point
Proceed to [Read the web](https://dougnutz.github.io/readtheweb) to check setup your server and test your code.

- Validate that "on" turns the LED on and "off" turns it off
- Validate that any other response does not change the state of the LED

## connect the relay
Using a relay board with an opto driver connect the coil to the pin used for the LED. 

- sample relay board
- AEDIKO DC 5V Relay Module 1 Channel Relay Module Optocoupler Isolation High and Low Level Trigger for Arduino Raspberry Pi PIC AVR DSP ARM ARM MCU TTL Logic
![relay board](https://m.media-amazon.com/images/I/711reZZfGXL._SX522_.jpg)

## Next steps
- connect the coil + to 3.3v
- connect the coil - to ground
- connect signal (IN) to the pin defined in the code
- if the relay has a high/low jumper make sure it is set to High

## Check point
- Validate that "on" turns the relay on and "off" turns it off.

## Turn on a light
In this step we will connect the relay control side to a light bulb. The light bulb should have an independant power supply. If using anything other than a basic low voltage light bulb be very careful. Exposure to high voltage can be fatal.

 ## Solution
 The [Solution](/Solution) is one possible solution.