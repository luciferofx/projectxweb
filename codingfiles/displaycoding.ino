#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Initialize the LCD with I2C address
LiquidCrystal_I2C lcd(0x27, 16, 2);

String mainMembers[] = {"RAJA", "PURUSHAAN", "SHIRYANSH", "HAMDAN"};
String helpers[] = {"SHABDIKA", "ABHAY", "VARSHA"};

void setup() {
  Serial.begin(115200);
  lcd.begin(16, 2);
  lcd.backlight();
  Serial.println("LCD initialized");

  while (true) {
    animateProjectX();   // Show animated "PROJECT X"
    blinkProjectX();     // Blinking effect
    displayMembers("Member", mainMembers, 4);
    displayMembers("Helper", helpers, 3);
  }
}

void loop() {}

// Function to animate "PROJECT X" sliding from left to center
void animateProjectX() {
  lcd.clear();
  for (int i = -8; i <= 4; i++) { // Slide text from left (-8) to center (4)
    lcd.clear();
    lcd.setCursor(i, 0);
    lcd.print("PROJECT");
    lcd.setCursor(i + 2, 1);
    lcd.print("X");
    delay(200);
  }
  delay(1000); // Pause before next animation
}

// Function to make "PROJECT X" blink 3 times
void blinkProjectX() {
  for (int i = 0; i < 3; i++) {
    lcd.clear();
    delay(300);
    lcd.setCursor(4, 0);
    lcd.print("PROJECT");
    lcd.setCursor(7, 1);
    lcd.print("X");
    delay(400);
  }
  delay(1000);
}

// Function to display members with a sliding effect
void displayMembers(String role, String names[], int count) {
  for (int i = 0; i < count; i++) {
    for (int j = 16; j >= 0; j--) { // Slide text from right to left
      lcd.clear();
      lcd.setCursor(4, 0);
      lcd.print("PROJECT X");
      lcd.setCursor(7, 1);
      lcd.print("");

      lcd.setCursor(j, 1);
      lcd.print(role + " " + String(i+1) + ": " + names[i]);

      delay(100);
    }
    delay(2000); // Display for 2 seconds
  }
}
