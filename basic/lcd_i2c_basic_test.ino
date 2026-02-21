#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Create LCD object
LiquidCrystal_I2C lcd(0x27, 16, 2);  // Address 0x27, 16 columns, 2 rows

void setup() {
  lcd.init();          // Initialize LCD
  lcd.backlight();     // Turn on backlight
  
  lcd.setCursor(0, 0);
  lcd.print("Hello, World!");
  
  lcd.setCursor(0, 1);
  lcd.print("I2C LCD Working");
}

void loop() {
  // Nothing required here
}
