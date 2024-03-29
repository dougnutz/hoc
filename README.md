# hoc
hoc (or Hour of code) These projects are a collection of beginner level coding experiences I have shared successfully with students ranging from 8-12 years old. Smaller groups have worked well for me. And I always encourage experimentation. So leave time to for them to experiment. 
## Hardware
- on top of the software tooling we need a ESP8266 compatible arduino (eg. ESP8266 NodeMCU CP2102 ESP-12E). Other arduino chips will likely work also.
## pre-requisite (windows setup)
This can be tricky please plan ahead. It's best if you can do these steps yourself before trying to get younger kids through the steps. 
- install git for [windows](https://gitforwindows.org/) 
- install [arduino UI](https://www.arduino.cc/en/software)
  - pick windows store option
  - Open arduino IDE and verify it loads
    - proceed to setup the arduino IDE for use with teh ESP8266 board 
    - https://create.arduino.cc/projecthub/electropeak/getting-started-w-nodemcu-esp8266-on-arduino-ide-28184f
    - try the blink application
      - select your board from Tools > Board > ESP8266
      - select the blink example from File > Examples > ESP8266 >Blink
## Checkpoint
  - With the blink example loaded
  - Make sure your board is connected to your computer with a USB cable
  - If you need a driver [Here](https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers)
  - In the ide upload the blink program by clicking the arrow in the toolbar. The program should compile, upload, and the board led should blink
## Using VSCODE
- install [VS code](https://code.visualstudio.com/Download) 
  - Installation of Arduino Extension
    - Cntrl+Shift+x  
    - search for 'vscode-arduino'
    - click install
    - search for and install 'PlatformIO'
    - Install PlatformIO IDE
      - this enables some enviroment tooling that we will use with these samples
    - close and reopen VS code (just to be sure everything is installed correctly)
- clone the HOC repository
  - press the windows key and type cmd+ enter
  - navigate to c:/ (type cd \ + enter)
  - create a src directory if it doesn't already exist (eg type `md src`)
  - change to that directory ('cd src' + enter)
  - clone the repository type 'git clone https://github.com/dougnutz/hoc.git'

## Checkpoint
  - In VS Code click open folder (or ctrl+k, ctrl+O)
    - in the file window pick the blink2 folder from the hoc directory just cloned (eg 'C:\src\hoc\Blink2')
    - If prompted click trust authors
    - In the explore menu under blink 2, navigate to src > main.cpp
      - Recommend, if prmpted to install extensions for c++
      - Also recommended to configure intellisense (if prompted)
  - [ ] you should see the "Welcome to PlatformIO" home screen once you open the folder. It may take a moment to load the first time. 
  - Setup compiler optsions
    -  To set the serial port that VS Code will communicate with your Arduino Uno we need to open up the Command Palette (Cntrl+Shift+p) and then type “Arduino Select Serial Port”
- [For detailed steps](https://maker.pro/arduino/tutorial/how-to-use-visual-studio-code-for-arduino)
