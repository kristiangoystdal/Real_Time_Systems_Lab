# Real-Time Systems Laboratory Project:

## Weather Station and Alarm Clock

### Introduction

This project is part of the Real-Time Systems course (IST 2024/2025) and involves designing and implementing a **Weather Station and Alarm Clock** using the **PIC16F18875 microcontroller**. The project is developed on the **Curiosity High Pin Count Development Board** and emphasizes real-time embedded systems programming without an operating system. The implementation uses modular design, state machines, and low-level hardware control to achieve functionality while optimizing power consumption.

---

### Features

#### 1. Clock Functionality
- Displays current time (hh:mm:ss) on the LCD.
- Supports alarm clock functionality with configurable alarm time.

#### 2. Sensor Monitoring
- **Temperature**: Uses the TC74 temperature sensor to read and monitor temperature values.
- **Luminosity**: Reads luminosity levels using the onboard potentiometer, emulating light levels.

#### 3. Alarms
- Generates alarms when:
  - Temperature exceeds a predefined threshold.
  - Luminosity exceeds a predefined threshold.
  - Alarm time is reached.
- Alarm signals:
  - **Visual**: Displays `CTL` on the LCD and toggles corresponding LEDs.
  - **PWM**: Modulates LED brightness for alarms.

#### 4. Data Storage
- Stores sensor readings (temperature, luminosity, timestamp) in non-volatile EEPROM memory.
- Maintains maximum and minimum recorded sensor values.

#### 5. User Interface
- **Inputs**: Two buttons (S1, S2) for configuration and data retrieval.
- **Outputs**: 
  - 4 LEDs for system status indication.
  - LCD (2x16 characters) for displaying current time, sensor data, and alarms.

#### 6. Power Management
- Optimizes energy usage by entering **SLEEP** mode during idle periods.

---

### Repository Structure

#### Source Files
- **Main File**:
  - `main.c`: Entry point for the application.
- **Modules**:
  - `alarm/`: Handles alarm-related functionalities.
  - `clock/`: Implements the clock and timekeeping mechanisms.
  - `controller/`:
    - EEPROM: Manages non-volatile memory storage.
    - LCD: Manages the LCD display using I2C.
    - LED: Handles LED status indications.
    - Luminosity: Monitors and processes light levels.
    - PWM: Implements pulse-width modulation for alarms.
    - Temperature: Interfaces with the TC74 temperature sensor.
  - `mode/`: Defines normal and configuration modes of operation.
  - `state/`: Manages application states and transitions.

#### Generated Files
- **MCC Generated Files**:
  - Contains auto-generated files for ADC, I2C, PWM, timers, and other peripherals.

#### Configuration and Build Files
- **Project Settings**:
  - Located under `nbproject/`.
- **Makefile**:
  - Instructions for building the project.

---

### User Interface

#### Buttons
- **S1 (RB4)**:
  - Clears alarm signals.
  - Enters configuration mode and cycles through editable fields.
- **S2 (RC5)**:
  - Increments values in configuration mode.
  - Cycles through saved maximum/minimum records in normal mode.

#### LCD Display
##### Normal Mode
- Displays:
  - Current time (`hh:mm:ss`).
  - Temperature (`tt°C`) and luminosity (`l`).
  - Alarm statuses (`CTL` if triggered, `A` if enabled).

##### Configuration Mode
- Allows modifying:
  - Clock time.
  - Temperature and luminosity thresholds.
  - Alarm enable/disable status.
  - Reset maximum and minimum records.

#### LEDs
- **D5**: Clock activity (blinks every second).
- **D4**: Alarm signal (PWM-modulated).
- **D3**: Temperature exceeds threshold.
- **D2**: Luminosity exceeds threshold.

---

### How to Build and Run

1. Clone this repository.
2. Open the project in MPLABX IDE.
3. Compile the project using MPLAB XC8 compiler.
4. Program the PIC microcontroller using the generated `pic.hex` file.

---

### Deliverables

- **Source Code**: Organized and modular.
- **Executable File**: `pic.hex` (for demonstrations).
- **Report**: 2-3 pages explaining real-time aspects and interaction design.

---

### References

1. [Microchip PIC16F18875 Data Sheet](https://www.microchip.com/)
2. [Curiosity High Pin Count Development Board User Guide](https://www.microchip.com/)
3. [MPLAB XC8 Compiler Documentation](https://www.microchip.com/)

---

### License

This project is for educational purposes as part of the Real-Time Systems course at IST. Please contact the repository maintainers for inquiries.
