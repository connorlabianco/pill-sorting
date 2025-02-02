const express = require('express');
const path = require('path');
const bodyParser = require('body-parser');
const SerialPort = require('serialport');

const app = express();
const port = 3000;

// Serve static files from the 'public' directory
app.use(express.static(path.join(__dirname, 'public')));

// Serve pillsort.html when visiting the root URL
app.get('/', (req, res) => {
  res.sendFile(path.join(__dirname, 'public', 'pillsort.html'));
});

// Set up body parser for JSON requests
app.use(bodyParser.json());

// Serial port setup
const serialPortPath = 'COM6';
let arduinoPort = null;

try {
  arduinoPort = new SerialPort(serialPortPath, { baudRate: 9600 });
  const parser = arduinoPort.pipe(new SerialPort.parsers.Readline({ delimiter: '\n' })); // Corrected import

  arduinoPort.on('open', () => {
    console.log('Serial port opened successfully');
  });

  arduinoPort.on('error', (err) => {
    console.error('Error with serial port:', err.message);
  });

  // Read and print data from Arduino
  parser.on('data', (data) => {
    console.log('Arduino says:', data.trim()); // Trim to clean up line breaks
  });

} catch (error) {
  console.error('Error opening serial port:', error.message);
}

// POST endpoint to send data to Arduino
app.post('/send-to-arduino', (req, res) => {
  if (arduinoPort && arduinoPort.isOpen) {
    const pillData = req.body;

    // Ensure a consistent structure with pill1, pill2, and pill3
    const formattedData = {
      pill1: pillData[0] ? pillData[0].days : [false, false, false, false, false, false, false],
      pill2: pillData[1] ? pillData[1].days : [false, false, false, false, false, false, false],
      pill3: pillData[2] ? pillData[2].days : [false, false, false, false, false, false, false]
    };

    console.log('Sending formatted data to Arduino:', formattedData);

    arduinoPort.write(JSON.stringify(formattedData) + '\n', (err) => {
      if (err) {
        console.log('Error sending data to Arduino:', err);
        return res.status(500).send({ success: false, message: 'Error sending data to Arduino' });
      }

      console.log('Data sent to Arduino');
      res.send({ success: true, message: 'Data sent successfully' });
    });
  } else {
    console.log('Arduino is not connected or port is not open');
    res.status(400).send({ success: false, message: 'Arduino is not connected or port is not open.' });
  }
});

// Start the Express server
app.listen(port, () => {
  console.log(`Server running at http://localhost:${port}`);
});
