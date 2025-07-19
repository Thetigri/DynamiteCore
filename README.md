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

- Microcontroller (e.g., Arduino Uno, ESP32, Raspberry Pi Pico)
- 10 push buttons (digits 0–9)
- Buzzer or speaker
- LEDs or display (optional, for feedback)
- Power supply
- Optional enclosure (dynamite-style housing for thematic effect)

## Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/simon-says-dynamite.git
   cd simon-says-dynamite
