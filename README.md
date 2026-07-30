# Arduino Parking Sensor

This project is an Arduino-based parking sensor that uses an ultrasonic distance sensor to measure how far an object is from the sensor. The system displays the distance on an LCD screen and uses LED indicators plus buzzer alerts to show how close the object is.

The project is designed to act like a simple parking assist system with Safe, Caution, Warning, and STOP zones.

## Features

- Ultrasonic distance sensing
- Distance displayed in centimeters
- LCD1602 display output
- Safe, Caution, Warning, and STOP proximity zones
- Green LED indicator for Safe distance
- Yellow LED indicator for Caution distance
- Red LED indicator for Warning and STOP distance
- Buzzer alerts with different tones based on distance
- Flashing red LED in STOP zone
- Non-blocking alert timing using `millis()`
- Missed-reading filtering to reduce false "No object found" messages
- No-object detection for missed ultrasonic readings
- Serial Monitor output available for debugging

## Hardware Used

- Arduino Uno
- Ultrasonic distance sensor
- LCD1602 display
- Potentiometer for LCD contrast
- Green LED
- Yellow LED
- Red LED
- Buzzer
- Breadboard
- Jumper wires
- LED resistors
- USB power source or computer connection

## Wiring Setup

### Full Wiring Setup

![Full Wiring Setup](images/parking-wiring-setup-1.jpeg)

### Additional Wiring Angle

![Additional Wiring Angle](images/parking-wiring-setup-2.jpeg)

### Ultrasonic Sensor Close-Up

![Ultrasonic Sensor Close-Up](images/parking-ultrasonic-sensor.jpeg)

### LCD and Alert Wiring

![LCD and Alert Wiring](images/parking-lcd-led-buzzer.jpeg)

### Final Demo Setup

![Final Demo Setup](images/parking-final-demo.jpeg)

## Pin Connections

| Component | Arduino Pin / Connection |
|---|---|
| Ultrasonic sensor Trig | Digital pin 9 |
| Ultrasonic sensor Echo | Digital pin 10 |
| Ultrasonic sensor VCC | 5V |
| Ultrasonic sensor GND | GND |
| Green LED | Digital pin 8 |
| Yellow LED | Digital pin 7 |
| Red LED | Digital pin 6 |
| Buzzer | Digital pin 13 and GND |
| LCD RS | Digital pin 12 |
| LCD E | Digital pin 11 |
| LCD D4 | Digital pin 5 |
| LCD D5 | Digital pin 4 |
| LCD D6 | Digital pin 3 |
| LCD D7 | Digital pin 2 |
| LCD VSS | GND |
| LCD VDD | 5V |
| LCD VO | Middle pin of potentiometer |
| LCD RW | GND |
| LCD A | 5V through resistor if needed |
| LCD K | GND |
| Potentiometer outside pins | 5V and GND |

## Distance Zones

The parking sensor uses distance thresholds to classify how close an object is.

| Zone | Distance Range | Output |
|---|---|---|
| Safe | 260 cm or farther | Green LED, no buzzer |
| Caution | 143–259 cm | Yellow LED, caution buzzer |
| Warning | 50–142 cm | Red LED, warning buzzer |
| STOP | Under 50 cm | Flashing red LED and urgent buzzer |

## How It Works

The ultrasonic sensor measures distance by sending out a short ultrasonic pulse from the Trig pin. When the sound wave bounces off an object and returns to the sensor, the Echo pin measures how long the return signal took.

The Arduino uses this echo duration to calculate distance in centimeters. Since the sound wave travels to the object and back, the calculation divides by 2 to get the one-way distance.

The LCD displays the measured distance on the first row and the current distance zone on the second row.

The system uses different alerts based on distance:

- **Safe:** object is far away, green LED turns on
- **Caution:** object is getting closer, yellow LED turns on and buzzer sounds
- **Warning:** object is close, red LED turns on and buzzer becomes more urgent
- **STOP:** object is very close, red LED flashes and buzzer pulses urgently

The final version uses `millis()` instead of a long `delay()` so the distance updates and STOP flashing can happen without freezing the system.

## Missed-Reading Filtering

Ultrasonic sensors can sometimes miss an echo because of object angle, surface material, distance, or sensor alignment.

To reduce false "No object found" messages, the final version uses missed-reading filtering. Instead of showing "No object found" after one bad reading, the system waits for multiple missed readings in a row before changing the display.

This makes the parking sensor more stable and prevents the LCD from flashing between a real distance and "No object found."

## Skills Practiced

- Arduino C++ programming
- Ultrasonic distance sensing
- Digital input and output
- LCD1602 display wiring and programming
- Potentiometer contrast control
- Distance calculation using echo duration
- LED proximity indicators
- Buzzer alerts using `tone()`
- Non-blocking timing with `millis()`
- Sensor noise handling and missed-reading filtering
- Conditional logic with distance thresholds
- Breadboard wiring
- GitHub project documentation

## Versions

- Version 1: Tested ultrasonic distance readings and printed distance to the Serial Monitor
- Version 2: Added LCD display output and Safe/Caution/Warning/STOP distance zones
- Version 3: Added green, yellow, and red LED indicators plus buzzer alerts
- Version 4: Added non-blocking STOP flashing with `millis()` timing and missed-reading filtering

## Future Improvements

- Build a cleaner enclosure for the sensor and display
- Improve wire management for a more finished build
- Add adjustable distance thresholds using buttons or a potentiometer
- Add smoother buzzer timing for each distance zone
- Test with different object materials and angles
- Mount the sensor to a small model car or cardboard parking setup
