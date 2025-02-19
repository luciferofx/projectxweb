#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>

//made by raja 11thc
#define SS_PIN 53
#define RST_PIN 5
MFRC522 mfrc522(SS_PIN, RST_PIN); 

Servo gateServo;

const int buzzer = 6;
const int redLED = 7;
const int greenLED = 8;

String authorizedUIDs[] = {"a3 80 ef f6", "8 d3 c4 3", "73 90 f2 2f"}; // Add more UIDs as needed

void setup() {
    Serial.begin(9600);
    SPI.begin();
    mfrc522.PCD_Init();

    gateServo.attach(9);
    gateServo.write(0); // Gate Closed

    pinMode(buzzer, OUTPUT);
    pinMode(redLED, OUTPUT);
    pinMode(greenLED, OUTPUT);

    Serial.println("Place your RFID card...");
}

void loop() {
    if (!mfrc522.PICC_IsNewCardPresent()) return;
    if (!mfrc522.PICC_ReadCardSerial()) return;

    String UID = "";
    for (byte i = 0; i < mfrc522.uid.size; i++) {
        UID += String(mfrc522.uid.uidByte[i], HEX) + " ";
    }
    UID.trim(); // Remove extra spaces

    Serial.print("Card UID: ");
    Serial.println(UID);

    bool accessGranted = false;
    for (String authorizedUID : authorizedUIDs) {
        if (UID.equalsIgnoreCase(authorizedUID)) {
            accessGranted = true;
            break;
        }
    }

    if (accessGranted) {
        Serial.println("Access Granted!");
        digitalWrite(greenLED, HIGH);
        digitalWrite(redLED, LOW);
        digitalWrite(buzzer, LOW);
        
        gateServo.write(90); // Open gate
        delay(5000); // Wait 5 seconds
        gateServo.write(0); // Close gate
    } else {
        Serial.println("Access Denied!");
        digitalWrite(greenLED, LOW);
        digitalWrite(redLED, HIGH);
        digitalWrite(buzzer, HIGH);
        delay(1000);
        digitalWrite(buzzer, LOW);
    }

    mfrc522.PICC_HaltA();
    mfrc522.PCD_StopCrypto1();
}
