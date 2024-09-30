# SmartParkingSystem

## Overview

The Smart Parking System is an innovative solution designed to monitor and manage parking spaces in real-time. Utilizing an ESP32 microcontroller, various sensors (IR and ultrasonic), a servo motor, and an OLED display, this system provides immediate feedback on parking availability, enhancing the urban parking experience for users.

## Features

- *Real-Time Parking Availability*: Detects and displays the status of parking spots.
- *User-Friendly Interface*: OLED display provides clear information about available parking.
- *Automated Access Control*: Servo motor controls a flap mechanism to allow entry based on availability.
- *Efficient Space Utilization*: Reduces the time spent searching for parking, minimizing traffic congestion.

## Components Used

- *Microcontroller*: ESP32
- *Sensors*:
  - IR Sensors (2 units for individual parking spots)
  - Ultrasonic Sensor (for vehicle detection)
- *Actuator*: Servo Motor (for controlling the flap)
- *Display*: 0.96-inch OLED Display (for user interface)
- *Additional*: Jumper wires, breadboard, power supply

## Pin Configuration

Component               ESP32 Pin   
IR Sensor 1             GPIO 2     
IR Sensor 2             GPIO 3     
Ultrasonic Trigger      GPIO 4     
Ultrasonic Echo         GPIO 5     
Servo Control           GPIO 17    
OLED SDA                GPIO 21    
OLED SCL                GPIO 22    

## Installation

1. *Clone the Repository*:
   git clone https://github.com/mukundchavan251/SmartParkingSystem.git

