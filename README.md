
# Smart Home Automation System

This project demonstrates a multi-functional smart home system controlled by an Arduino. The system integrates security features with environmental controls, including an automatic door, keypad access, temperature regulation, and light-dependent brightness control.

## Components

* **Arduino:** The central microcontroller.
* **Two IR Sensors:** Used to detect presence and open the front door.
* **Keypad (2x2):** For entering a security password.
* **Servo Motor:** Controls the opening and closing of the main door.
* **Buzzer:** Used for both the security alarm and the high-temperature alarm.
* **Green LED:** Indicates a correct password.
* **LCD (Liquid Crystal Display):** Displays messages, temperature, and brightness levels.
* **Temperature Sensor (DHT11):** Measures the ambient temperature.
* **DC Motor:** Acts as a fan to cool the room.
* **Push Button:** Manually turns off the high-temperature alarm.
* **LDR (Light-Dependent Resistor):** Measures ambient light levels.
* **LEDs (x2):** Their brightness is controlled by the LDR.

## System Features and Operation

### 1. Automatic Garden Door

* **Function:** Controls the opening and closing of a main door using two IR sensors.
* **Mechanism:**
  * One IR sensor is placed outside the door (`OutIRSensor`).
  * The other is placed inside (`inIRSensor`).
  * When the outside sensor is triggered, the **servo motor** opens the door, and the `LCD` displays "Open Door." After a delay, the door closes.
  * When the inside sensor is triggered, the servo motor opens the door, and the `LCD` displays "Open Door." After a delay, the door closes.
* **Logic:** The door opens in the opposite direction of the person's approach, which is handled by adjusting the servo motor's angle.

### 2. Home Security and Access Control

* **Function:** Grants access to the home via a keypad and a password.
* **Mechanism:**
  * A **keypad** is used to enter a four-digit password. The password is `'5','5','5','5'`.
  * If a **wrong password** is entered, a **buzzer** alarm sounds, and the `LCD` prints "Wrong password."
  * If the **correct password** is entered, the buzzer alarm stops, a **green LED** turns on, and the `LCD` prints "Welcome Home." The system then proceeds to the next functions.

### 3. Temperature Regulation

* **Function:** Maintains the room temperature below a set threshold.
* **Mechanism:**
  * A **DHT11 temperature sensor** continuously measures the temperature.
  * The current temperature is always displayed on the `LCD`.
  * **Normal Control:** If the temperature rises above **28°C**, a **DC motor** (fan) turns on. It will stay on until the temperature drops below the threshold.
  * **High-Temperature Alarm:** If the temperature exceeds **30.1°C**, a second **buzzer** turns on, sounding an alarm. This alarm can only be turned off manually by pressing a **push button**.

### 4. Ambient Light Control

* **Function:** Adjusts the brightness of two LEDs based on the surrounding light.
* **Mechanism:**
  * An **LDR (Light-Dependent Resistor)** measures the amount of light in the room.
  * The `ldrValue` is read and then mapped to a brightness level (0-255).
  * The mapped brightness level is used to control the brightness of the LEDs via `analogWrite()`.
  * The brightness level is also displayed on the `LCD`.
