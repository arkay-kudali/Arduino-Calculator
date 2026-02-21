# Arduino-Calculator
arduino based calculator project , which uses arduino nano / uno as mcu ,uses 4x4 matrix keypad for input and 1602 i2c lcd display for calculate doutputs 

# Arduino Calculator (UNO / Nano)

A simple calculator built using:

- Arduino UNO / Nano  
- 16x2 I2C LCD Display  
- 4x4 Matrix Keypad  

It performs basic operations: +  −  ×  ÷

If you prefer video guidance, watch the full tutorial here:  
📺 https://youtu.be/s7fe-LROB0o?si=2Rme3poVYnrOcxCS

---

## 📦 How to Use

### 1️⃣ Download the Project
- Click **Code → Download ZIP**
- Extract the folder

---

### 2️⃣ Install the LCD Library

Inside this repo there is a folder named **library**

👉 Copy the entire `LiquidCrystal_I2C` folder  
👉 Paste it into your Arduino libraries folder:

**Windows:**
Documents → Arduino → libraries

If the `libraries` folder does not exist, create it.

After copying, restart Arduino IDE.

---

### 3️⃣ Open the Main File

Open:
calculator_main.ino

Select your board:
- Tools → Board → Arduino UNO (or Nano)
- Select correct COM port
- Click Upload

---

## 🔌 Pin Connections

### 📟 I2C LCD (16x2)

| LCD Pin | Arduino |
|----------|----------|
| VCC      | 5V       |
| GND      | GND      |
| SDA      | A4 (UNO/Nano) |
| SCL      | A5 (UNO/Nano) |

> Default I2C Address: 0x27

---

### 🔢 4x4 Keypad

| Keypad Row Pins | Arduino |
|-----------------|----------|
| R1 | 9 |
| R2 | 8 |
| R3 | 7 |
| R4 | 6 |

| Keypad Column Pins | Arduino |
|--------------------|----------|
| C1 | 5 |
| C2 | 4 |
| C3 | 3 |
| C4 | 2 |

---

### ➕ Extra Buttons

| Button | Arduino Pin |
|---------|-------------|
| = (Equals) | 11 |
| Backspace | 12 |

Both buttons should connect to **GND when pressed**  
(Pins are configured as INPUT_PULLUP internally)

---

## 🧠 How It Works

- Keypad collects input
- Expression is displayed on LCD
- Press `=` to calculate
- Result appears on second row
- Press `C` to clear

---

## 📁 Project Structure
calculator_main.ino
basic/
library/
calc_circuit_diagram.png


---

If something is unclear, please watch the full YouTube tutorial linked above.

---

Made for learning.  
Simple. Clean. Functional.
