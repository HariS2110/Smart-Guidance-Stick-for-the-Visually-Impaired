# Smart Guidance Stick for the Visually Impaired

## Overview
This project focuses on the development of a Smart Guidance Stick aimed at improving the mobility and safety of visually impaired individuals. The stick is equipped with various sensors and communication modules to provide real-time obstacle detection, wet surface alerts, and emergency location sharing. The project showcases a combination of embedded systems, sensor integration, and user-centric design.

## Features
- **Obstacle Detection:** Uses an ultrasonic sensor to detect obstacles in the user’s path and provides auditory alerts to ensure safe navigation.
- **Wet Surface Alerts:** Equipped with a rain sensor that detects wet surfaces and emits a distinct sound to warn the user of slippery conditions.
- **Emergency Location Sharing:** Integrates GPS and GSM modules to send the user's real-time location to a predefined emergency contact at the press of a button.
- **User-Centric Design:** The stick is lightweight, easy to use, and cost-effective, ensuring accessibility for a broad audience.

## Technologies Used
- **Arduino Uno:** Microcontroller for controlling sensors and managing communication between components.
- **HC-SR04 Ultrasonic Sensor:** Detects obstacles and helps in avoiding collisions.
- **NEO-6M GPS Module:** Provides real-time location tracking for emergency situations.
- **SIM 800L GSM Module:** Facilitates the sending of SMS messages containing the user's location to emergency contacts.
- **Haljia Rain Sensor:** Detects wet surfaces and alerts the user to prevent slips and falls.
- **Piezo Buzzer:** Provides auditory alerts for obstacle detection and wet surface warnings.
- 
## Setup and Usage
1. **Hardware Assembly:** Follow the circuit diagrams in the `/design` folder to assemble the Smart Guidance Stick.
2. **Software Upload:** Upload the Arduino code from the `/code` directory to the Arduino Uno board.
3. **Calibration:** Calibrate the sensors (ultrasonic and rain sensor) as per the guidelines in the `/docs` folder to ensure accurate obstacle and wet surface detection.
4. **Testing:** Conduct tests to verify obstacle detection, wet surface alerts, and emergency location functionality before usage.

## Challenges and Solutions
- **Sensor Accuracy:** Fine-tuned the ultrasonic sensor's range to ensure reliable obstacle detection without false positives.
- **Power Management:** Optimized power consumption to extend battery life while maintaining real-time responsiveness.

## Future Improvements
- **Voice Feedback:** Integrate a voice feedback system to provide more detailed guidance and alerts.
- **Enhanced Connectivity:** Explore Bluetooth or Wi-Fi integration for better communication and tracking features.


