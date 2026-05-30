# DormMate

## Overview

DormMate is a smart embedded dorm assistant designed to help college students improve time management, reduce missed classes, and stay organized.

The system combines alarms, reminders, scheduling tools, and future attendance-aware features into one embedded productivity system. DormMate is being developed progressively through multiple firmware versions to simulate real engineering iteration and embedded system development.

---

## Problem

Many college students struggle with:

- Missing classes
- Oversleeping
- Poor time management
- Forgetting assignments and routines
- Feeling overwhelmed by busy schedules

DormMate aims to reduce these problems through intelligent reminders, scheduling assistance, and embedded system automation.

---

## Current Features

### Core Features

- Virtual Clock System
- Automatic Night Light (Photoresistor-Based)
- Alarm System
- Reminder System
- LCD User Interface
- IR Remote Navigation
- 12-Hour / 24-Hour Time Mode

### Academic Productivity Features

- Class Scheduling System
- Meeting Day Selection (MWF / TR)
- Class Time Configuration
- Enable / Disable Schedule Logic
- Multi-Reminder Scheduling

### User Interface Features

- Interactive LCD Menu Navigation
- Arrow-Based Menu Selection
- Screen State Navigation
- Dynamic Reminder Notifications

---

## Firmware Evolution

### V1 — Initial Prototype
**Completed:** May 8, 2026

**Features:**
- Timer system
- Photoresistor-based night light

---

### V2
**Completed:** May 13, 2026

**Features:**
- LCD interface
- IR remote navigation
- Menu system
- Sensor monitoring

---

### V3
**Completed:** May 15, 2026

**Features:**
- Improved menu navigation
- Arrow-based UI system
- Better screen interaction

---

### V4
**Completed:** May 18, 2026

**Features:**
- 12-hour / 24-hour clock mode
- Improved time display system

---

### V5
**Completed:** May 19, 2026

**Features:**
- Alarm system
- Piezo buzzer integration

---

### V6
**Completed:** May 19, 2026

**Features:**
- Melody-based alarm
- Alarm screen
- Improved alarm control logic

---

### V6.1
**Completed:** May 19, 2026

**Features:**
- Alarm refinements
- Bug fixes
- System tuning

---

### V7
**Completed:** May 20, 2026

**Features:**
- Reminder system
- Scheduled reminder notifications

---

### V8
**Completed:** May 22, 2026

**Features:**
- Multi-reminder scheduling
- Dynamic reminder tracking

---

### V9
**Completed:** May 22, 2026

**Features:**
- Class schedule manager
- Course navigation system

---

### V10 
**Completed:** May 25, 2026

**Features:**
- Editable class schedules
- Meeting day selection
- Course enable / disable logic
- Academic planner system

---
### V11 — Class Schedule Intelligence

**Completed:** May 27, 2026

**Features:**

* Multi-class schedule management
* Individual class configuration screens
* MWF / TR meeting day logic
* Weekday selection system
* Class enable / disable controls
* Improved academic planner behavior
---
### V12 — Next Class Logic System (Current version)

**Completed:** May 30, 2026

**Features:**

* Smart next-class detection
* Multi-class priority selection
* Closest upcoming class logic
* Dynamic class reminder system
* Reminder integration into clock screen
* Automatic future-class filtering
* Smart class reminder display


## Engineering Challenges & Solutions

### 1. Alarm Sound Conflict

**Problem:**  
The IR remote library conflicted with Arduino's built-in `tone()` function because both relied on timer interrupts, preventing the buzzer from emitting sound.

**Solution:**  
A custom `playTone()` function was developed to manually generate sound frequencies. During debugging, an additional issue was discovered where the speaker pin had not been initialized as an output inside `setup()`.

**Skills Demonstrated:**
- Embedded debugging
- Interrupt conflict troubleshooting
- Hardware/software integration

---

### 2. Alarm Screen Would Not Exit

**Problem:**  
The alarm repeatedly retriggered because the condition:

`H == alarmHour && M == alarmMinute`

remained true for an entire minute, causing behavior similar to a constant interrupt.

**Solution:**  
An `alarmTriggered` flag was implemented so the alarm activates only once and resets after the minute changes. Remote button logic was added to stop the alarm and return to the main screen.

**Skills Demonstrated:**
- Event-driven programming
- State-machine logic
- Embedded debugging

---

### 3. Reminder Display Duplication Bug

**Problem:**  
Stopping reminders caused duplicated reminder text on the LCD display.

**Solution:**  
A dedicated `currentReminder` variable was introduced to dynamically track the active reminder rather than reusing menu navigation variables.

**Skills Demonstrated:**
- LCD debugging
- Variable management
- Embedded UI logic

---

### 4. Shared Input Conflict

**Problem:**  
Remote buttons conflicted because the same button was assigned to multiple functions across different system states.

**Solution:**  
Input assignments were redesigned to separate alarm control and class scheduling interactions.

**Skills Demonstrated:**
- Input management
- Embedded system integration
- Logic debugging

---

### 5. Hardware Grounding Failure

**Problem:**  
During testing, the LCD stopped displaying text while the buzzer emitted continuous noise.

**Solution:**  
The issue was diagnosed as a disconnected ground wire and resolved through circuit troubleshooting.

**Skills Demonstrated:**
- Circuit debugging
- Hardware diagnostics
- Wiring verification

---

## Hardware Used

### Current Hardware

- Arduino Uno
- 16x2 LCD Display
- IR Receiver + Remote
- Piezo Buzzer
- Photoresistor (LDR)
- Breadboard
- Potentiometer
- Yellow LED
- 220Ω Resistors
- 10kΩ Resistor

### Planned Hardware

- HC-SR04 Ultrasonic Sensors
- ESP32 Microcontroller
- Custom PCB

---

## Future Improvements

### Smart Attendance Features

- Dorm exit detection using dual ultrasonic sensors
- Detect if student left for class on time
- Alarm intensification if student remains in dorm

### Connectivity Features

- ESP32 migration
- Wi-Fi integration
- Mobile app communication
- Phone notifications

### Product Development

- PCB version
- Student testing
- Improved enclosure design

---

## Skills Demonstrated

- Embedded Systems Programming
- C/C++ Development
- LCD Interface Programming
- IR Remote Communication
- State Machine Design
- Event-Driven Programming
- Embedded Debugging
- Hardware Troubleshooting
- Sensor Integration
- Alarm and Scheduling Logic
- Firmware Iteration
- Embedded UI Development

---

## Active Development

**Project Started:** May 2026

GitHub documentation was added after development began to organize firmware versions and engineering progress.
