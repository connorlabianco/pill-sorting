const express = require('express');
const bodyParser = require('body-parser');
const SerialPort = require('serialport');
const path = require('path');  // To help serve static files

const app = express();
const port = 3000;

// Serve static files (HTML, JS, CSS) from the 'public' directory
app.use(express.static(path.join(__dirname, 'public')));

// Serve pillsort.html when visiting the root URL
app.get('/', (req, res) => {
  res.sendFile(path.join(__dirname, 'public', 'pillsort.html'));
});

// Configure Express to parse JSON bodies
app.use(bodyParser.json());

// Define the correct serial port path
let arduinoPort = null;
const serialPortPath = '/dev/tty.usbmodem14201';  // Replace this with your actual port

// Check if the port exists before trying to open it
const fs = require('fs');
if (fs.existsSync(serialPortPath)) {
  // Attempt to open the serial port
  try {
    arduinoPort = new SerialPort({
      path: serialPortPath,
      baudRate: 9600
    });

    arduinoPort.on('open', () => {
      console.log('Serial port opened');
    });

    arduinoPort.on('error', (err) => {
      console.error('Error with serial port:', err);
    });

  } catch (error) {
    console.error('Error opening the serial port:', error.message);
  }
} else {
  console.error(`Serial port path ${serialPortPath} does not exist.`);
}

// POST endpoint to receive data from the web app
app.post('/send-to-arduino', (req, res) => {
  if (arduinoPort && arduinoPort.isOpen) {
    const pillData = req.body;

    console.log('Received data from web app:', pillData);

    arduinoPort.write(JSON.stringify(pillData), (err) => {
      if (err) {
        console.log('Error writing to Arduino:', err);
        return res.status(500).send({ success: false, message: 'Error sending data to Arduino' });
      }

      console.log('Data sent to Arduino');
      res.send({ success: true, message: 'Data sent successfully' });
    });
  } else {
    res.status(400).send({ success: false, message: 'Arduino is not connected or port is not open.' });
  }
});

// Start the Express server
app.listen(port, () => {
  console.log(`Server running at http://localhost:${port}`);
});
