#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// OLED display settings
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1  // Reset pin not used

// Create the OLED display object
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Team members and project name
String projectName = "PROJECT X";
String teamMembers[] = {
    "Team Member", 
  "Raja", 
  "Purushaan", 
  "Shriyansh", 
  "Hamdan", 
  "Varsha", 
  "Anshul", 
  "Abhay"
};
int teamSize = 7; // Total team members

void setup() {
  // Start serial communication for debugging
  Serial.begin(9600);

  // Initialize the OLED display
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }

  display.clearDisplay();  // Clear the display initially
  display.display();       // Display everything
  delay(2000);             // Wait 2 seconds
}

void loop() {
  // Clear the display to start fresh
  display.clearDisplay();

  // Show the project name at the top in smaller text
  display.setTextSize(1);  // Smaller text size for the project name
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10, 10);  // Position the text
  display.print(projectName);

  // Animate the team member names scrolling one by one
  for (int i = 0; i < teamSize; i++) {
    String memberName = teamMembers[i];
    int nameLength = memberName.length() * 6;  // Approximate width of the name

    // Scroll each team member's name from right to left
    int textXPos = SCREEN_WIDTH;  // Start off-screen

    // Animate scrolling from right to left
    while (textXPos > -nameLength) {
      display.clearDisplay();
      
      // Display the project name at the top in smaller text
      display.setTextSize(2);
      display.setTextColor(SSD1306_WHITE);
      display.setCursor(10, 10);
      display.print(projectName);

      // Display the current team member name at the bottom in larger text
      display.setTextSize(2);  // Larger text for team names
      display.setCursor(textXPos, SCREEN_HEIGHT / 2 + 5);  // Vertically lower the team member name
      display.print(memberName);

      display.display();  // Update the display

      // Move the text to the left (increase speed of scrolling)
      textXPos -= 2;  // Move faster than before (previously `textXPos--`)

      delay(1);  // Lower delay for faster animation (1 ms for speed)
    }
  }

  // After all names have been shown, repeat the animation from the beginning
  delay(500);  // Wait 500 ms before starting the next loop (or adjust if needed)
}
