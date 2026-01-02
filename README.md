# 🎬 COE 718: Embedded Media Center

[![Media Center Demo](https://img.youtube.com/vi/1fpZy3uRcNo/0.jpg)](https://youtube.com/shorts/1fpZy3uRcNo?si=EazBF58WNAbXzIck)  
**Click the image above to watch the Media Center in action!**

---

## 📝 Project Overview

The **Embedded Media Center** is a comprehensive real-time multimedia system developed for **COE 718: Embedded Systems Design** on the **MCB1700 evaluation board**. Leveraging the **NXP LPC1768 (ARM Cortex-M3)** microcontroller, this project integrates four distinct subsystems into a single cohesive application: a digital Photo Gallery, a USB-based Audio Player, a Tic-Tac-Toe logic game, and a high-precision Reflex Tester.

The system demonstrates advanced resource optimization by managing concurrent tasks, utilizing the **Nested Vector Interrupt Controller (NVIC)** for low-latency input, and employing **Analog-to-Digital Converters (ADC)** for real-time signal processing.

---

## ⚙️ Key Features

* **Finite State Machine (FSM) Architecture:** A robust software design that guarantees the system occupies exactly one valid state at any time (Menu, Gallery, Audio, or Game).
* **USB Audio Streaming:** Configures the board as a standard **USB Audio Class** device to stream PCM audio directly from a PC (e.g., YouTube, Spotify).
* **Hardware Volume Control:** Utilizes the on-board potentiometer to adjust volume via ADC, providing visual feedback through an expanding LCD bar and a linear LED array.
* **Digital Photo Gallery:** Renders high-resolution bitmap assets serialized into C-arrays directly from on-chip Flash memory.
* **Tic-Tac-Toe Engine:** A full logic engine with real-time input validation, turn-based mechanics, and algorithms to detect wins, losses, or stalemates.
* **Reflex Hunter Game:** A millisecond-precise reaction tester that uses hardware timers to rank user performance (Perfect, Fast, Slow) based on stochastic stimuli.

---

## 🛠 Tools & Technologies

| Technology | Purpose |
| :--- | :--- |
| **NXP LPC1768 (Cortex-M3)** | Main SoC operating at 100 MHz for processing and control logic. |
| **Keil µVision IDE** | Integrated Development Environment for firmware creation and debugging. |
| **GLCD (320x240)** | Primary output for the Graphical User Interface (GUI) and game rendering. |
| **USB Audio Class** | Protocol for isochronous audio data streaming from host PC. |
| **NVIC & ADC** | Handling low-latency interrupts and analog potentiometer signals. |

---

## 🚀 System Architecture

**User Input** --> **Microcontroller (LPC1768)** --> **Output Peripherals**

* **Inputs:**
    * **Joystick:** Acts as the primary Human Interface Device (HID) for menu navigation and game control.
    * **Potentiometer:** Provides continuous voltage signals converted by the 12-bit ADC for volume control.
* **Processing:**
    * **FSM Loop:** Manages transitions between the Main Menu, Photo Gallery, Audio Player, and Games.
    * **Interrupt Service Routines (ISRs):** Prioritizes joystick inputs over background tasks for precision timing.
* **Outputs:**
    * **LCD Screen:** Renders dynamic graphics, photos, and real-time scoreboards.
    * **LED Array:** Illuminates sequentially to represent audio volume levels (0dB to silence).

---

## 📜 License & Copyright

© 2025 **Hamza Malik** – All rights reserved.

---

## ⚠️ ACADEMIC INTEGRITY WARNING & DISCLAIMER

**THIS REPOSITORY IS FOR PORTFOLIO DISPLAY PURPOSES ONLY.**

This codebase is published as a demonstration of technical competency in embedded systems design for potential employers and recruiters. It represents the personal work of **Hamza Malik** for the COE 718 curriculum at Toronto Metropolitan University.

**⛔ FOR CURRENT STUDENTS:**
Copying, referencing, or submitting any portion of this code, logic, or report content for your own academic assignments is a **strict violation of Toronto Metropolitan University's Academic Integrity Policy (Senate Policy 60)**.

* **Do not** clone this repository for use in your labs or final projects.
* **Do not** copy the logic, FSM structures, or algorithm implementations.
* **Do not** use the report diagrams or text in your own submissions.

Any suspicion of plagiarism or unauthorized collaboration may result in an investigation of **Academic Misconduct**, leading to a grade of **"0"** on the work, an **"F"** in the course, and a **Disciplinary Notice** on your permanent academic record.

**If you are currently enrolled in COE 718, you are required to implement your own solutions independently.**
