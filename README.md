🎮 Gesture-Controlled Rock-Paper-Scissors Game
- This project is an Arduino-based Rock-Paper-Scissors game that uses an MPU6050 accelerometer to detect hand gestures and determine the player's move. The game translates specific hand motions into Rock, Paper, or Scissors based on real-time accelerometer data.
---
🚀 Features
- Uses MPU6050 accelerometer for gesture detection.
- Maps hand gestures to Rock, Paper, or Scissors.
- Prints the detected move via serial communication.
- Works with Arduino-compatible boards.
---
🛠️ Hardware Requirements
- Arduino Uno/Nano/ESP32 (or any compatible microcontroller)
- MPU6050 Accelerometer
- Jumper Wires
- USB Cable for programming
---
📜 How It Works
- The MPU6050 reads acceleration values along the X, Y, and Z axes.
- The Arduino processes these values to detect specific gestures:
- **X-axis high → Rock**
- Y-axis high → Paper**
- Z-axis high → Scissors

- The detected gesture is printed via the Serial Monitor.
---
🔧 Setup and Usage
- Connect the MPU6050 to your Arduino:
- VCC → 3.3V/5V
- GND → GND
- SDA → A4 (Arduino Uno)
- SCL → A5 (Arduino Uno)
- Upload the Arduino code from this repository.
- Open the Serial Monitor to see the detected gestures.

