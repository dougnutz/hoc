## Hardware 
- nodemcu 2866
- maker focus (or similar) ssd1306 display
### Wire up the display 
- mount the chip and display to a bread board 
![image](https://user-images.githubusercontent.com/20483619/169121210-d8eda466-2b1d-4b4a-9aca-6b1b6363d88f.png)

- and connect the dispaly as shown

![image](https://user-images.githubusercontent.com/20483619/169120605-9e6c0a78-203f-4a8c-90f0-8fa44f1eb1e5.png)

## Checkpoint Run the program
- the screen should display "hello world"
 - try changing the font size 
  - in the "setFont()" try using `ArialMT_Plain_16` or `ArialMT_Plain_24`
 - try changing the first two coordinates to 0, what do you think will happen
### How do you draw a line?
- remove the text lines and type
  - `display.drawHorizontalLine(0, 40, 20);`
- try changing the numbers, what will happen?
### How about shapes?
- `display.drawRect(1, 1, 20, 40);` 
 - what will this do? Try and see
 - now change one of the first two number and see what happens
 - what happens if we change the second two numbers? 
 or
 `display.drawCircle(32, 32, 10);` 
 - try changing the last number to 20

### How about some animation?
- `display.drawProgressBar(0, 32, 120, 10, counter);`
 - what makes the progress bar move? how can we change that?

### Troubleshooting
This exercise was based on initial published libraries for the maker focus board. If the Hellow world project doesn't load try these steps instead
#### Add libraries
 - click pio Home
 - click add libraries
 - search for 'esp8266 ssd1306'
 - Select "ESP8266 and ESP32 OLED driver for SSD1306 displays by ThingPulse"
 - click add to project
  - select the Hellow world project
  - click add
