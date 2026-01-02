# 🎬 COE 718: Embedded Media Center

[![Media Center Demo](https://img.youtube.com/vi/1fpZy3uRcNo/0.jpg)](https://youtube.com/shorts/1fpZy3uRcNo?si=EazBF58WNAbXzIck)  
**Click the image above to watch the Media Center in action!**

---

## 📝 Project Overview

[cite_start]The **Embedded Media Center** is a real-time multimedia system developed for **COE 718: Embedded Systems Design** on the **MCB1700 evaluation board**[cite: 177]. [cite_start]Leveraging the **NXP LPC1768 (ARM Cortex-M3)** microcontroller, this project integrates four distinct subsystems into a single cohesive application: a digital Photo Gallery, a USB-based Audio Player, a Tic-Tac-Toe logic game, and a high-precision Reflex Tester[cite: 178, 182].

[cite_start]The system demonstrates advanced resource optimization by managing concurrent tasks, utilizing the **Nested Vector Interrupt Controller (NVIC)** for low-latency input, and employing **Analog-to-Digital Converters (ADC)** for real-time signal processing[cite: 179, 186].

---

## ⚙️ Key Features

* [cite_start]**Finite State Machine (FSM) Architecture:** A robust software design that guarantees the system occupies exactly one valid state at any time (Menu, Gallery, Audio, or Game)[cite: 226, 227].
* [cite_start]**USB Audio Streaming:** Configures the board as a standard **USB Audio Class** device to stream PCM audio from a PC (e.g., YouTube, Spotify)[cite: 267, 270].
* [cite_start]**Hardware Volume Control:** Utilizes the on-board potentiometer to adjust volume via ADC, providing visual feedback through an expanding LCD bar and a linear LED array[cite: 271, 274, 275].
* [cite_start]**Digital Photo Gallery:** Renders high-resolution bitmap assets serialized into C-arrays directly from on-chip Flash memory[cite: 256].
* [cite_start]**Tic-Tac-Toe Engine:** A full logic engine with real-time input validation, turn-based mechanics, and algorithms to detect wins, losses, or stalemates[cite: 283, 304, 310].
* [cite_start]**Reflex Hunter Game:** A millisecond-precise reaction tester that uses hardware timers to rank user performance (Perfect, Fast, Slow) based on stochastic stimuli[cite: 317, 321, 350].

---

## 🛠 Tools & Technologies

| Technology | Purpose |
| :--- | :--- |
| **NXP LPC1768 (Cortex-M3)** | [cite_start]Main SoC operating at 100 MHz for processing and control logic[cite: 182, 193]. |
| **Keil µVision IDE** | [cite_start]Integrated Development Environment for firmware creation and debugging[cite: 185]. |
| **GLCD (320x240)** | [cite_start]Primary output for the Graphical User Interface (GUI) and game rendering[cite: 213]. |
| **USB Audio Class** | [cite_start]Protocol for isochronous audio data streaming from host PC[cite: 267]. |
| **NVIC & ADC** | [cite_start]Handling low-latency interrupts and analog potentiometer signals[cite: 186]. |

---

## 🚀 System Architecture

**User Input** --> **Microcontroller (LPC1768)** --> **Output Peripherals**

* **Inputs:**
    * [cite_start]**Joystick:** Acts as the primary Human Interface Device (HID) for menu navigation and game control[cite: 218].
    * [cite_start]**Potentiometer:** Provides continuous voltage signals converted by the 12-bit ADC for volume control[cite: 223].
* **Processing:**
    * [cite_start]**FSM Loop:** Manages transitions between the Main Menu, Photo Gallery, Audio Player, and Games[cite: 226].
    * [cite_start]**Interrupt Service Routines (ISRs):** Prioritizes joystick inputs over background tasks for precision timing[cite: 358].
* **Outputs:**
    * [cite_start]**LCD Screen:** Renders dynamic graphics, photos, and real-time scoreboards[cite: 215].
    * [cite_start]**LED Array:** Illuminates sequentially to represent audio volume levels (0dB to silence)[cite: 276].

---

## 📜 License & Copyright

[cite_start]© 2025 **Hamza Malik** – All rights reserved[cite: 173].
