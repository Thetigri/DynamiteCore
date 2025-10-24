# DynamiteCore
# Simon Says: Dynamite Edition

A quick reaction game implemented on a physical interface designed to resemble a dynamite module. The user is challenged to reproduce a sequence of digits under time pressure, with the tempo accelerating at each level.

## Overview

This project is an implementation of a sequence memory game similar to *Simon Says*, with an added time constraint represented through progressively faster beeping. The physical interface includes numeric buttons (0–9), and two option buttons and simulates the tension of defusing a bomb. Failure to reproduce the correct sequence or respond in time results in a simulated "explosion" (visual/auditory feedback only).

## Gameplay

- The game generates a random sequence of digits.
- The player must input the sequence using physical digit buttons.
- Each level decreases the interval between beeps.
- If the input is incorrect you restart the level
- The game ends if the player does not match the sequence before the beep timer expires.

## Features

- Progressive difficulty scaling through timing acceleration.
- Support for 10-digit input (0–9).
- Mute/Unmute option for the timer
- Buzzer and LED feedback for input confirmation and failure state.
- Designed for Arduino.

## Hardware Components

- Microcontroller (Arduinno NANO)
- Buzzer
- 12 Arduino buttons (12x12mm)
- LCD1602 screen with I2C module
- Power supply (5V powerbank)
- Printed parts
- Cable to connect microcontroller to power source

## Installation
Print the 3D printed files in the following orientation
put the 
Download the .ino file and push it to the Arduino Nano via Arduino IDE
