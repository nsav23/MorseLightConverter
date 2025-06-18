# MorseLightConverter
A work-in-progress Morse code converter using light signals, built with Arduino.

**Status:** 🚧 !!!WIP!!! 🚧

This project is an Arduino-based Morse code converter that detects light pulses using a phototransistor, converts them to characters from the latin alphabet and prints them in the serial monitor (for the time being).

## 🔧 Current Features

- Converts light pulses to '.' or '-' char sequences and the to ;etters
- Outputs them to serial monitor

## 🛠️ Planned Improvements

- Add support for additional characters and punctuation
- Output to LCD display

## 🧰 Requirements

- Arduino board 
- Single phototransistor
- 10 kOhm resistor
- Breadboard(Optional)
- Arduino IDE

## 📐 Electrical diagram   

![sch](https://github.com/user-attachments/assets/ceb058f0-fec4-491a-8502-3ea6e6ed1aa5)


## 📦 Project structure

- MorseLightConverter.ino – the main (and only) file

## ⚠️ Note

This is an early version with core functionality in place. The timing for more complex letters and whole words is still in devolopment!!!
