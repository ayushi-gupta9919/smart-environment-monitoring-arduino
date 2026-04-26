# smart-environment-monitoring-arduino
Real-time embedded system using Arduino to monitor temperature, humidity, and air quality with OLED display and alert system.
> Designed with focus on real-world challenges like sensor noise, calibration, and reliable alert systems.
## 🧠 System Architecture

Sensors (DHT11, MQ135) → Arduino → Data Processing → OLED Display → Alert System (LED + Buzzer)

<p align="center">
  <img src="circuit.jpg" width="400" alt="Circuit Setup"><br>
  <b>Circuit Setup</b>
</p>

<p align="center">
  <img src="oled-output.jpg" width="400" alt="OLED Output"><br>
  <b>OLED Output Display</b>
</p>


## ⚠️ Engineering Challenges & Solutions

### 1. Sensor Noise & Unstable Readings
- The MQ135 gas sensor produced fluctuating analog values.
- ✅ Solution: Implemented a moving average filter to smooth readings and improve stability.

### 2. False Alerts Due to Improper Threshold
- Initial threshold values caused continuous buzzer triggering.
- ✅ Solution: Calibrated the sensor by observing real-time values and setting an optimized threshold.

### 3. Sensor Warm-Up Issue
- MQ135 required stabilization time before giving accurate readings.
- ✅ Solution: Added warm-up delay during system initialization.

### 4. Real-Time System Design
- Managing multiple tasks (sensing, display, alerts) efficiently was challenging.
- ✅ Solution: Designed modular functions for better structure and real-time performance.

### 5. Hardware-Software Integration
- Ensuring correct communication between sensors and OLED display.
- ✅ Solution: Used I2C protocol and verified connections with step-by-step debugging.

  ## 🌍 Real-World Application

This system can be used in:
- Smart homes
- Industrial safety monitoring
- Pollution detection systems
