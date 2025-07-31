# Parking Slot Occupancy Detection with Ultrasonic Sensors

This Arduino project uses multiple ultrasonic sensors to detect the occupancy status of parking slots and two switches to detect vehicle entry and exit events. The system measures distances using ultrasonic sensors to determine whether a parking slot is occupied or free, and prints relevant information via serial communication.

---

## Table of Contents

- [Overview](#overview)  
- [Hardware Components](#hardware-components)  
- [Pin Configuration](#pin-configuration)  
- [Code Structure](#code-structure)  
- [How It Works](#how-it-works)  
- [Usage](#usage)  
- [Customization](#customization)  
- [Troubleshooting](#troubleshooting)  
- [License](#license)  

---

## Overview

The project utilizes the HC-SR04 ultrasonic sensors placed over individual parking slots. Each sensor measures the distance to an obstacle below it (typically a vehicle). If the distance is less than a defined threshold, the slot is considered occupied. Two switches are connected to monitor vehicle entry and exit.

The Arduino continuously monitors all sensors and switches and outputs the status via serial port, which can be read using the Arduino IDE Serial Monitor or any serial terminal.

---

## Hardware Components

- Arduino Uno (or compatible board)  
- Four HC-SR04 Ultrasonic Sensors  
- Two push-button switches (for entry and exit detection)  
- Jumper wires  
- Breadboard or PCB for assembly  

---

## Pin Configuration

| Sensor | Trigger Pin | Echo Pin | Parking Slot |  
|--------|-------------|----------|--------------|  
| 1      | 7           | 9        | Slot 1       |  
| 2      | 2           | 3        | Slot 2       |  
| 3      | 4           | 5        | Slot 3       |  
| 4      | 8           | 6        | Slot 4       |  

| Switch       | Pin | Purpose             |  
|--------------|-----|---------------------|  
| Entry Switch | 10  | Detect vehicle entry |  
| Exit Switch  | 11  | Detect vehicle exit  |  

---

## Code Structure

The code is modular and organized into several functions for clarity and reusability:

- `initializePins()`: Configures all sensor and switch pins as inputs or outputs with proper modes.  
- `measureDistance()`: Sends a trigger pulse to an ultrasonic sensor and measures the echo time to calculate distance. Returns the distance in centimeters or -1 if no echo is detected.  
- `checkSlots()`: Iterates over all sensors to measure distances and prints slot occupancy status if the vehicle is detected (distance below threshold).  
- `checkSwitches()`: Reads the entry and exit switch states and prints corresponding events when switches are pressed.  
- `setup()`: Initializes serial communication and configures all pins.  
- `loop()`: Continuously monitors sensors and switches by calling respective functions.  

---

## How It Works

1. **Ultrasonic Sensors**: Each sensor emits an ultrasonic pulse via its trigger pin. The echo pin listens for the reflected signal. The time taken for the echo to return is proportional to the distance between the sensor and the nearest object below it.  
2. **Occupancy Detection**: If the measured distance is below a configured threshold (15 cm by default), the slot is considered occupied, and a message is printed over the serial interface.  
3. **Switch Detection**: When the entry or exit switch is pressed (pulled LOW), messages "ENTRY" or "EXIT" are sent via serial communication. This can be used to track vehicles entering or leaving the parking area.  

---

## Usage

1. Connect the sensors and switches as per the pin configuration.  
2. Upload the Arduino sketch to your Arduino board using the Arduino IDE.  
3. Open the serial monitor at 9600 baud rate.  
4. Observe the output messages indicating slot occupancy and entry/exit events.  

---

## Customization

- **Add More Slots**: Extend `sensors[]` by adding more sensor structs with appropriate pins and labels.  
- **Adjust Threshold**: Change `occupancyThresholdCm` to modify what distance is considered occupied.  
- **Debounce Timing**: Adjust delays within `checkSwitches()` to minimize switch bounce or tune responsiveness.  
- **Output Interface**: Modify code to output data to an LCD, display, or network module for enhanced monitoring.  

---

## Troubleshooting

- **No readings or -1 distance**: Check sensor wiring and power. Make sure trigger pins are output and echo pins input.  
- **Cross-talk interference**: Ultrasonic sensors emit pulses that may interfere with each other. Slight delay between reading sensors is included but may need adjustment or more advanced timing management.  
- **Switch not registering**: Ensure switches are connected with pull-up resistors or use internal `INPUT_PULLUP` mode as configured in the code.  

---

## License

This project is open source and available under the MIT License. Feel free to use and modify as per your requirements.

---

## Contact

For questions or contributions, please open an issue or pull request on the repository.

---

*Happy parking slot monitoring!* 🚗🅿️
