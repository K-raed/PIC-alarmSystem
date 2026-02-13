🔐 PIC-Based Smart Alarm System
Keypad Authentication + Temperature-Controlled Automation
📌 Overview

This project implements a password-protected alarm and environmental control system using a PIC microcontroller.

The system integrates:

4x4 Keypad authentication

LCD user interface

Interrupt-driven alarm control

Analog temperature sensing (ADC)

Heating / Cooling automation

Password modification functionality

The project demonstrates low-level embedded programming using C with direct register manipulation and interrupt management.

🎯 Project Objectives

Implement secure PIN-based access control

Manage alarm behavior using hardware interrupts

Display real-time system feedback on LCD

Read analog temperature using ADC

Automate heating and cooling decisions

Allow secure password modification

🏗 System Architecture
🔹 Microcontroller

PIC microcontroller (8-bit architecture)

Direct register configuration (TRIS, PORT, INTCON, OPTION_REG)

Interrupt-driven design

🔹 User Interface

4x4 Keypad for PIN entry

16x2 LCD display

Masked password input using "*"

🔹 Sensors & Actuators

Analog temperature sensor (ADC input)

Alarm buzzer / LED indicators

Heating / Cooling output control

🔄 System Operation
1️⃣ System Startup

LCD displays welcome message

User is prompted to enter 4-digit PIN

2️⃣ Authentication Logic

Each key press is read using Keypad_Key_Click()

Password is compared with stored PIN array

Input is masked on LCD

If correct:

Access granted

Alarm disabled

Environmental control activated

If incorrect:

Access denied

Alarm LED/buzzer activated

System enters alert loop

3️⃣ Interrupt Handling

The system uses hardware interrupts for:

External interrupt (RB0) → Reset conditions

Timer0 interrupt → Alarm timing management

PORTB change interrupt → Password change trigger

Interrupt service routine handles:

Alarm activation timing

LED control

Timer reconfiguration

State switching logic

4️⃣ Temperature-Based Automation

After successful authentication:

ADC reads analog temperature

Conversion to Celsius:

Temp = ADC_value × 0.488

Decision logic:

≤ 15°C → Activate Heating

≥ 28°C → Activate Cooling

This demonstrates embedded control logic based on analog input.

5️⃣ Password Modification Mode

When triggered:

User enters new 4-digit PIN

System verifies authorization condition

Stored password array is updated

System returns to normal mode

⚙️ Key Technical Concepts Demonstrated

Direct register configuration (TRISA, TRISB, OPTION_REG, INTCON)

Interrupt Service Routine implementation

Timer0 configuration and overflow management

ADC configuration and analog-to-digital conversion

Keypad scanning and decoding

LCD 4-bit communication mode

State machine logic using global variables

📁 Core Components in Code

key() → Keypad scanning and ASCII conversion

interrupt() → Interrupt Service Routine

main() → System state machine and control flow

🧠 Embedded Engineering Focus

This project emphasizes:

Low-level hardware control

Interrupt-driven architecture

Real-time event handling

Secure authentication logic

Analog + digital system integration

It demonstrates strong understanding of microcontroller-based system design beyond simple polling-based applications.

🛠 Technologies Used

PIC Microcontroller

Embedded C

ADC peripheral

Timer0

External interrupts

16x2 LCD (4-bit mode)

4x4 Keypad

🚀 Possible Improvements

EEPROM-based password storage

Debounce logic improvement

Low-power mode integration

More robust state machine architecture

Security lockout after multiple failed attempts
