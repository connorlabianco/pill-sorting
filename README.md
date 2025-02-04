# Automated Pill Sorting System

## Project Overview  
The Automated Pill Sorting System is a web-based application that allows users to manage and automate the dispensing of pills for the week. With an easy-to-use front-end interface built in HTML, CSS, and JavaScript, users can input pill types, select the days they need the pills, and export the data to an Arduino-controlled machine that dispenses the pills automatically.

## Features:  
- User Input: Input up to three pill types and select the days for each pill.  
- Interactive Front-End: Built with HTML, CSS, and JavaScript for a clean and responsive interface.  
- Automated Pill Dispensing: Once the user selects their pill schedule, the Arduino-controlled machine dispenses the pills for each day automatically.  
- Data Export: The user's selection is exported in JSON format to the Arduino via Node.js, ensuring smooth integration between front-end and hardware.

## Technologies Used:  
- Frontend: HTML, CSS, JavaScript  
- Backend: C++, Arduino, Node.js  
- Data Format: JSON

## Setup Instructions

## Prerequisites  
Before running the project, ensure you have the following dependencies installed on your system:  
- Node.js  
- C++ Compiler  
- Arduino IDE  
- VSCode (Optional, but recommended for code editing)  
- ArduinoJson library for Arduino IDE  

## macOS Setup (using Homebrew)  
 Install Homebrew: If you don’t already have Homebrew, you can install it by running the following command in the terminal:  
 `/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"`

 Install Node.js: Use Homebrew to install Node.js:  
 `brew install node`

 Install C++ Compiler: Install the GCC C++ compiler with Homebrew:  
 `brew install gcc`

 Install VSCode (optional): You can also install Visual Studio Code (VSCode) using Homebrew:  
 `brew install --cask visual-studio-code`

 Install Arduino IDE: Download and install the Arduino IDE from their official website.  

 Install ArduinoJson Library: In the Arduino IDE:  
 Open Sketch > Include Library > Manage Libraries.  
 Search for ArduinoJson and click Install.

## Windows Setup (using Git)  
 Install Git: Download and install Git from [here](https://git-scm.com/).
 Install Node.js: Download and install Node.js from [here](https://nodejs.org/).
 Install Visual Studio: Download and install Visual Studio from [here](https://visualstudio.microsoft.com/).
 Install Arduino IDE: Download and install the Arduino IDE from [here](https://www.arduino.cc/en/software).
 Install ArduinoJson Library: In the Arduino IDE, open [Sketch > Include Library > Manage Libraries](https://www.arduino.cc/en/Guide/Libraries) and search for ArduinoJson to install it.

## Running the Project  
 Upload Arduino Code:  
 Open the Arduino IDE and open the .ino file from the project directory.  
 Select the correct COM port by navigating to Tools > Port.  
 Click the Upload button to upload the code to the Arduino device.

 Run the Node.js Server:  
 Open your terminal (macOS) or command prompt (Windows).  
 Navigate to the project directory and run the following command:  
 `node server.js`  
This will start the Node.js server, allowing communication between the front-end and the Arduino.

## Using the System  
 Open the HTML front-end file in your browser.  
 Input the three pill types in the form provided and select the days of the week when you need each pill.  
 Click the Export Data button to send the data to the Arduino device.  
 Press the Button on the Arduino-controlled pill sorter to begin dispensing pills. The system will:  
- Dispense pills for Monday, wait for 5 seconds.  
- Move to the next day and dispense pills for that day.  
- Repeat the process until Sunday, where the plate returns to its default position.

## License  
This project is licensed under the MIT License.
