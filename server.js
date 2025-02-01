const express = require('express');
const bodyParser = require('body-parser');
const SerialPort = require('serialport');

const app = express();
const port = 3000;

// Configure Express to parse JSON bodies
app.use(bodyParser.json());

// Create a SerialPort object to communicate with the Arduino
const arduinoPort = new SerialPort('/dev/ttyACM0', { baudRate: 9600 }); // Adjust to your port

// Open the port
arduinoPort.on('open', () => {
    console.log('Serial port opened');
});

// POST endpoint to receive data from the web app
app.post('/send-to-arduino', (req, res) => {
    const pillData = req.body;
    
    // Log the data to the console for debugging
    console.log('Received data from web app:', pillData);

    // Send the data to the Arduino (we can send it as a JSON string or a simplified format)
    arduinoPort.write(JSON.stringify(pillData), (err) => {
        if (err) {
            console.log('Error writing to Arduino:', err);
            return res.status(500).send({ success: false, message: 'Error sending data to Arduino' });
        }

        console.log('Data sent to Arduino');
        res.send({ success: true, message: 'Data sent successfully' });
    });
});

// Start the Express server
app.listen(port, () => {
    console.log(`Server running at http://localhost:${port}`);
});
