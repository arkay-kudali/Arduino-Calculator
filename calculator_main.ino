#include <Keypad.h>
#include <LiquidCrystal_I2C.h>

const byte ROW_NUM    = 4; // four rows
const byte COLUMN_NUM = 4; // four columns

char keys[ROW_NUM][COLUMN_NUM] = {
  {'1', '2', '3', '+'},
  {'4', '5', '6', '-'},
  {'7', '8', '9', '*'},
  {'C', '0', '.', '/'}
};

byte pin_rows[ROW_NUM] = {9, 8, 7, 6}; // connect to the row pinouts of the keypad
byte pin_column[COLUMN_NUM] = {5, 4, 3, 2}; // connect to the column pinouts of the keypad

Keypad keypad = Keypad(makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM);

char inputExpression[100] = "";
int inputIndex = 0;
bool decimalPressed = false;

LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C address 0x27, 16 columns and 2 rows

double evaluateExpression(char expression[]) {
  double numbers[50];
  char operators[50];
  int numIndex = 0;
  int opIndex = 0;

  // Extract numbers and operators from the expression
  for (int i = 0; i < strlen(expression); ++i) {
    if (isdigit(expression[i])) {
      char* endptr;
      numbers[numIndex++] = strtod(&expression[i], &endptr);
      i += endptr - &expression[i] - 1;
    } else if (expression[i] == '+' || expression[i] == '-' || expression[i] == '*' || expression[i] == '/') {
      operators[opIndex++] = expression[i];
    }
  }

  // Perform arithmetic calculations
  for (int i = 0; i < opIndex; ++i) {
    if (operators[i] == '*') {
      numbers[i + 1] *= numbers[i];
    } else if (operators[i] == '/') {
      numbers[i + 1] = numbers[i] / numbers[i + 1];
    }
  }

  for (int i = 0; i < opIndex; ++i) {
    if (operators[i] == '+') {
      numbers[i + 1] += numbers[i];
    } else if (operators[i] == '-') {
      numbers[i + 1] = numbers[i] - numbers[i + 1];
    }
  }

  return numbers[numIndex - 1];
}

void printExpression() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(inputExpression);
}

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  pinMode(11, INPUT_PULLUP); // Set up pin 13 as input with pull-up resistor
  pinMode(12, INPUT_PULLUP); // Set up pin 12 as input with pull-up resistor
}

void loop() {
  char key = keypad.getKey();
  bool equalsButtonPressed = digitalRead(11) == LOW; // Check if '=' button is pressed (grounded)
  bool backButtonPressed = digitalRead(12) == LOW; // Check if backspace button is pressed (grounded)

  if (key) {
    if (key == 'C') {
      inputIndex = 0;
      memset(inputExpression, 0, sizeof(inputExpression));
      printExpression();
      decimalPressed = false; // Reset decimal flag
    } else if (key == '.') {
      if (!decimalPressed) {
        inputExpression[inputIndex++] = key;
        printExpression();
        decimalPressed = true;
      }
    } else {
      inputExpression[inputIndex++] = key;
      printExpression();
      decimalPressed = false; // Reset decimal flag
    }
  }

  if (backButtonPressed && inputIndex > 0) {
    inputExpression[--inputIndex] = '\0'; // Remove the last entered character
    printExpression();
    delay(500); // Add a delay to avoid multiple deletions from a single press
  }

  if (equalsButtonPressed) {
    double result = evaluateExpression(inputExpression);
    lcd.print(" = ");
    lcd.setCursor(0, 1);
    lcd.print(result);
    Serial.print(" = ");
    Serial.println(result);
    inputIndex = 0;
    memset(inputExpression, 0, sizeof(inputExpression));
    decimalPressed = false; // Reset decimal flag
    delay(500); // Add a delay to avoid multiple evaluations from a single press
  }
}