# Smart Energy Meter with LCD Display and SMS Notification

This Arduino project implements a smart energy meter that counts energy consumption pulses from a pulse output (e.g., from an energy meter sensor), calculates the consumed units and cost, displays this information on a 16x2 LCD, and sends periodic SMS updates via a GSM module.

---

## Table of Contents

- [Overview](#overview)  
- [Hardware Requirements](#hardware-requirements)  
- [Pin Configuration](#pin-configuration)  
- [Code Explanation](#code-explanation)  
- [Installation and Usage](#installation-and-usage)  
- [Customization](#customization)  
- [Troubleshooting](#troubleshooting)  
- [License](#license)  

---

## Overview

This project monitors energy pulses from a meter through a digital input pin. It accumulates pulses, computes the equivalent energy consumption units and the cost based on predefined constants, then displays these values on an LCD screen. Every three pulses counted, the system sends an SMS with the updated energy usage details using AT commands over a serial connection to a GSM module.

---

## Hardware Requirements

- Arduino Uno (or compatible board)  
- 16x2 LCD display (with compatible pin wiring)  
- Energy meter pulse output connected to Arduino digital input pin (configured as `PULSE_PIN`)  
- GSM module capable of sending SMS, connected to Arduino Serial pins  
- Appropriate power supply and connecting wires  

---

## Pin Configuration

| Component       | Pin Number | Purpose                 |  
|-----------------|------------|-------------------------|  
| Energy Meter Pulse Input (Pulse Pin) | 13         | Reads meter pulses        |  
| LCD RS          | 12         | LCD register select      |  
| LCD Enable      | 11         | LCD enable               |  
| LCD D4          | 5          | LCD data 4               |  
| LCD D5          | 4          | LCD data 5               |  
| LCD D6          | 3          | LCD data 6               |  
| LCD D7          | 2          | LCD data 7               |  

---

## Code Explanation

### Core Constants

- `PULSES_PER_UNIT`: Number of pulses correspond to one energy unit (e.g., kWh).  
- `COST_PER_UNIT`: Cost in currency per unit of energy consumed.  
- `PULSE_VALUE`: Energy per pulse in suitable units (e.g., watt-seconds).

### Pulse Counting

- The code monitors a digital input pin for rising edges indicating an energy pulse.  
- The total pulse count (`pulseCount`) increments each time a rising edge is detected.

### Calculations

- **Units consumed** = (total pulses × energy per pulse) ÷ pulses per unit.  
- **Cost calculated** = units consumed × cost per unit.

### LCD Display

- The LCD displays the current cost and units in two lines.  
- The display refreshes continuously in the main loop with updated values.

### SMS Notifications

- After every 3 pulses counted, the device sends an SMS with the current energy consumption and cost details.  
- GSM commands (`AT+CMGF`, `AT+CMGS`) are sent over Serial to control the GSM module.  
- The phone number in the code should be replaced with the actual destination number.

---

## Installation and Usage

1. **Wiring**: Connect the hardware components according to the pin configuration above.  
2. **Modify Code**: Update the phone number in the function `sendEnergyUsageSMS()` replacing the placeholder `*phone_number*` with your actual number in international format.  
3. **Upload Sketch**: Use the Arduino IDE to upload the provided code to your Arduino board.  
4. **Monitoring**:  
    - View energy cost/units in real time on the LCD.  
    - Receive SMS updates every 3 pulses detected.

---

## Customization

- **Adjust Constants**: Modify `PULSES_PER_UNIT`, `COST_PER_UNIT`, or `PULSE_VALUE` to fit your meter's specifications and tariff.  
- **SMS Frequency**: Change the pulse count threshold in the code to send SMS messages more or less frequently.  
- **LCD Interface**: Adapt LCD pins or upgrade to other display types as needed.  
- **Pulse Counting Method**: For improved performance, implement interrupt-based pulse counting instead of polling.

---

## Troubleshooting

- **LCD Display Not Working**: Verify wiring and contrast adjustment. Confirm LCD initialization.  
- **No Pulses Being Counted**: Ensure the pulse signal is connected correctly and pulses are present. Test pulse input signal with a multimeter or oscilloscope.  
- **SMS Not Sent**: Check GSM module wiring and SIM card status. Confirm AT command compatibility and baud rate.  
- **Incorrect Units or Cost**: Recheck constants and calculations for accuracy.

---

## License

This project is licensed under the MIT License. Contributions and modifications are welcome.

---

## Contact

For questions, issues, or contributions, please open an issue or pull request in this repository.

---

*Happy Energy Monitoring!* ⚡📟
