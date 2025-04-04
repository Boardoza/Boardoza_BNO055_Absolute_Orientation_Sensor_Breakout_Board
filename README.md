# Boardoza BNO055 Breakout Board

The **Boardoza BNO055 Breakout Board** is an advanced **9-axis absolute orientation sensor** that combines a triaxial 14-bit accelerometer, a triaxial 16-bit gyroscope with a range of ±2000 degrees per second, and a triaxial geomagnetic sensor. This integration provides accurate and reliable orientation data for applications such as robotics, augmented reality, gaming, and personal navigation.

This module operates with **3.3V or 5V**, ensuring compatibility with a wide range of microcontrollers. By default, it communicates via **I<sup>2</sup>C**, but can be configured to **UART mode** using the **PS0 and PS1 pins**. The **PS0, PS1, INT, and ADR pins operate at 3.3V**, facilitating seamless interfacing with low-power MCUs.

## [Click here to purchase!](https://www.ozdisan.com/maker-ve-iot-urunleri/boardoza/boardoza-modulleri/BOARDOZA-BNO055/1206508)

| Front Side | Back Side |
|:---:|:---:|
| ![Front](./assets/BNO055%20Front.png) | ![Back](./assets/BNO055%20Back.png) |

---

## **Key Features**

- **Integrated 9-Axis Sensor:** Combines accelerometer, gyroscope, and magnetometer for comprehensive motion sensing.
- **Sensor Fusion Algorithms:** Built-in 32-bit microcontroller running Bosch Sensortec sensor fusion software for accurate orientation data.
- **Flexible Communication Interfaces:** Supports both **I<sup>2</sup>C** (default) and **UART**, selectable via **PS0 and PS1 pins**.
- **Wide Voltage Range:** Operates with **3.3V or 5V**, suitable for various MCUs.
- **Compact Design:** Small form factor (20mm x 40mm) for easy integration into space-constrained projects.

---

## **Technical Specifications**  

**Model:** Bosch BNO055  
**Input Voltage:** 3.3V - 5.5V  
**Voltage Input Type:** 4-pin 2.50mm header  
**Interface:** I<sup>2</sup>C (default), UART (configurable)  
**Functions:** 9-Axis IMU sensor (3-axis accelerometer, 3-axis gyroscope, 3-axis magnetometer, temperature sensor)  
**Gyroscope Range:** ±2000 degrees per second  
**Accelerometer Resolution:** 14-bit  
**Magnetic Field Range:** ±1300μT (X/Y-axis), ±2500μT (Z-axis)  
**Operating Temperature:** -40°C ~ +85°C  
**Board Dimensions:** 20mm x 40mm

> Note: Magnetic field values are given in microtesla (μT), where 1 μT = 10⁻⁶ tesla.

---

## **Board Pinout**

### **( J1 ) I<sup>2</sup>C Communication Pins**

| Pin Number | Pin Name | Description |
|:---:|:---:|---|
| 1 | VCC | Power Supply (3.3V - 5.5V) |
| 2 | SCL | I<sup>2</sup>C Serial Clock Pin |
| 3 | SDA | I<sup>2</sup>C Serial Data Pin |
| 4 | GND | Ground |

### **( J2 ) Additional Function Pins**

| Pin Number | Pin Name | Description |
|:---:|:---:|---|
| 1 | BOOT_LOAD (I) | Bootloader mode select pin (active low) |
| 2 | BL_IND (O) | Bootloader indicator pin |
| 3 | ADR (I) | I<sup>2</sup>C address select pin |
| 4 | INT (O) | Interrupt output pin |
| 5 | PS1 (I) | Protocol select pin 1 |
| 6 | PS0 (I) | Protocol select pin 0 |

### **Protocol Selection Table (PS1 / PS0)**

| PS1 | PS0 | Functionality             |
|:---:|:---:|---------------------------|
| 0   | 0   | Standard/Fast I<sup>2</sup>C Interface |
| 0   | 1   | HID over I<sup>2</sup>C              |
| 1   | 0   | UART Interface              |
| 1   | 1   | Reserved                    |

> For detailed configuration, see the [BNO055 Datasheet](./assets/BNO055%20Datasheet.pdf)


---

## **Board Dimensions**

<img src="./assets/BNO055 Dimension.png" alt="Board Dimensions" width="450"/>

---

## **Step Files**

[Boardoza BNO055.step](./assets/BNO055%20Step.step)

---

## **Datasheet**

[Boardoza BNO055 Datasheet.pdf](./assets/BNO055%20Datasheet.pdf)

---

## **Version History**

- V1.0.0 - Initial Release

---

## **Support**

- If you have any questions or need support, please contact **<support@boardoza.com>**

---

## **License**

Shield: [![CC BY-SA 4.0][cc-by-sa-shield]][cc-by-sa]

This work is licensed under a [Creative Commons Attribution-ShareAlike 4.0 International License][cc-by-sa].

[![CC BY-SA 4.0][cc-by-sa-image]][cc-by-sa]

[cc-by-sa]: http://creativecommons.org/licenses/by-sa/4.0/  
[cc-by-sa-image]: https://licensebuttons.net/l/by-sa/4.0/88x31.png  
[cc-by-sa-shield]: https://img.shields.io/badge/License-CC%20BY--SA%204.0-lightgrey.svg
