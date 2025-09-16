# DynamiteCore
# Simon Says: Dynamite Edition

A memory-based reaction game implemented on a physical interface designed to resemble a dynamite module. The user is challenged to recall and reproduce an increasingly complex sequence of digits under time pressure, with the tempo accelerating at each level.

## Overview

This project is an implementation of a sequence memory game similar to *Simon Says*, with an added time constraint represented through progressively faster beeping. The physical interface includes numeric buttons (0–9) and simulates the tension of defusing a bomb. Failure to reproduce the correct sequence or respond in time results in a simulated "explosion" (visual/auditory feedback only).

## Gameplay

- The game generates a random sequence of digits.
- The player must input the sequence using physical digit buttons.
- Each level adds a new digit and decreases the interval between beeps.
- The game ends if:
  - The input is incorrect.
  - The player does not respond before the beep timer expires.

## Features

- Progressive difficulty scaling through timing acceleration.
- Support for 10-digit input (0–9).
- Configurable timing and level parameters.
- Buzzer and LED feedback for input confirmation and failure state.
- Designed for microcontroller platforms (e.g., Arduino, Raspberry Pi Pico).

## Hardware Requirements

- Microcontroller (either Arduino UNO or Arduinno NANO)
- Buzzer
- LCD1602 screen with I2C module
- Power supply
- Printed parts

## Installation
 Download the .ino file and push it to your Arduino via Arduino IDE
