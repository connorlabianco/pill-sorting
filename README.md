# Automated Pill Sorting System

## Project Overview  
The Automated Pill Sorting System is a web-based application that automates pill dispensing for the week. Users can input pill types, select the days they need the pills, and export the data to an Arduino-controlled machine that dispenses them.

## Features:  
- **User Input**: Input up to three pill types and select days for each pill.  
- **Interactive Front-End**: Built with HTML, CSS, and JavaScript for a clean and responsive interface.  
- **Automated Dispensing**: The Arduino-controlled machine dispenses pills for each day automatically.  
- **Data Export**: User selection is exported in JSON format to the Arduino via Node.js for smooth integration.

## Technologies Used:  
- **Frontend**: HTML, CSS, JavaScript  
- **Backend**: C++, Arduino, Node.js  
- **Data Format**: JSON

## Setup Instructions

## Prerequisites  
Before running the project, ensure you have the following installed:  
- Node.js  
- C++ Compiler  
- Arduino IDE  
- VSCode (optional, but recommended for code editing)  
- ArduinoJson library for Arduino IDE  

## macOS Setup (using Homebrew)  
1. **Install Homebrew** (if you don’t have it):  
   [phb] `/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"`

2. **Install Node.js**:  
   [phb] `brew install node`

3. **Install C++ Compiler**:  
   [phb] `brew install gcc`

4. **Install VSCode** (optional):  
   [phb] `brew install --cask visual-studio-code`

5. **Install Arduino IDE**: Download from the [official website](https://www.arduino.cc/en/software).  

6. **Install ArduinoJson Library**:  
   - Open Arduino IDE > Sketch > Include Library > Manage Libraries.  
   - Search for `ArduinoJson` and click **Install**.

## Windows Setup (using Git)  
1. **Install Git**: Download from [here](https://git-scm.com/).

2. **Install Node.js**: Download from [here](https://nodejs.org/).

3. **Install Visual Studio**: Download from [here](https://visualstudio.microsoft.com/).

4. **Install Arduino IDE**: Download from [here](https://www.arduino.cc/en/software).

5. **Install ArduinoJson Library**:  
   - In the Arduino IDE, go to [Sketch > Include Library > Manage Libraries](https://www.arduino.cc/en/Guide/Libraries).  
   - Search for `ArduinoJson` and click **Install**.

## Running the Project  

1. **Upload Arduino Code**:  
   - Open the Arduino IDE and load the `.ino` file from the project directory.  
   - Select the correct COM port via **Tools > Port**.  
   - Click **Upload** to upload the code to the Arduino.

2. **Run the Node.js Server**:  
   - Open the terminal (macOS) or command prompt (Windows).  
   - Navigate to the project directory and run:  
     [phb] `node server.js`  
   This starts the Node.js server, enabling communication between the front-end and the Arduino.

## Using the System  
1. Open the HTML front-end file in your browser.  
2. Input the pill types and select the days of the week.  
3. Click **Export Data** to send the data to the Arduino.  
4. Press the button on the Arduino-controlled pill sorter to begin dispensing pills.  
   The system will:
   - Dispense pills for Monday, wait for 5 seconds.  
   - Move to the next day and dispense pills for that day.  
   - Repeat until Sunday, where the plate returns to its default position.

## License  
This project is licensed under the [MIT License](https://opensource.org/licenses/MIT).
