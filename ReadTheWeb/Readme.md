# Read from the internet and display the content
## setup 
- the api that will be called must be setup a head of time. 
- You will need to add the wifi SSID and password. Make sure you know these
- This build on knowledge from the HellowWorld project
  - Use the same wiring and screen 
## Lesson
- Open the src/main cpp file
- At the top of the file add the ssid and network password
- For this lession the actual connection and crude error handling has been written in a helper class that we will use
### steps
- We want to take a look at the WebRead.cpp file and talk about what it is doing. 
   - What methods are there? 
   - What do they do?
- Now back to the Main.cpp
   - lets include this file in our project by adding 
   -  `#include <Webread.h>` to the top of our file
   - Now create an instance of WebRead along with our other variables
     -  `WebRead webread; `
- In the setup() lets pass the network credentials to our helper class
    - `webRead.SetConnectionInfo(ssid, pass);`
- In the loop() 
    - We are going to call the webRead.GetData method and print the output to our consol window. To do this we need to create a string variable to hold the response and then assign the value we get when we call the api.
    - `String payload = webRead.GetData(gateUrl);`
    - Then use `Serial.println(payload);` to display the value.
## Customize it
- REplace <code> with the api key. Then Change the url to replace hello with the students name with no spaces 
    `char gateUrl[]="http://hocfun.azurewebsites.net/api/echo?code=<code>&name=<your Name>`
## Checkpoint
- Run the program and make sure it works.
    - The output window should display the loop and get the value. At this point the value is probably empty.
### Use our display to display the text to the screen
- We previously used the Display class to write to the screen.
- Back to the top of the file
  - Uncomment or add the #include `SSD1306Wire.h`
- Now declare the screen display variable   
    - `SSD1306Wire display(0x3c, D3, D5);  // ADDRESS, SDA, SCL  `
-  In order to use the screen we need to call the init() function from our setup ()
  - add `display.init(); `
- Now in the loop () we need to perform the following steps in each loop
    - clear the display
    - Write to the display buffer
    - Call display()
    ```
    display.clear();
    display.drawString(0,0,payload);
    display.display();
    ```
## Checkpoint
Run the code and see if the screen displays the empty value

### alter the file and let's see it work
- For best effect disconnect the arduino from the computer and connect it to an external power source. 
- Go to the browser and enter this into the address bar.
`http://hocfun.azurewebsites.net/api/echo?code=isfun&name=<student name>` remember to include the students name
- now add `&value=HelloWorld` to the end of the urls

`http://hocfun.azurewebsites.net/api/echo?code=<code>&name=<student name>&value=HelloWorld`

- Observe the display when you change the value
