

// // the setup function runs once when you press reset or power the board
// void setup() {
//   // initialize digital pin LED_BUILTIN as an output.
//   
// }

// // the loop function runs over and over again forever
// void loop() {
//   
//   delay(1000);                      // wait for a second
// }

/*
 * Created by ArduinoGetStarted.com
 *
 * This example code is in the public domain
 *
 * Tutorial page: https://arduinogetstarted.com/tutorials/arduino-rfid-nfc
 * 
 * Libraries Needed:
 *    - MFRC522 (by Github Community)
 * 
 */

#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 5
#define GREEN_LED_PIN 8
#define RED_LED_PIN 9

MFRC522 rfid(SS_PIN, RST_PIN);

// Good NFC chip
byte uidToMatch[] = {0xB4, 0x81, 0xE4, 0x03};


void setup() {
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);

  Serial.begin(9600);
  SPI.begin(); // init SPI bus
  rfid.PCD_Init(); // init MFRC522

  Serial.println("Tap RFID/NFC Tag on reader");
}

void loop() {
   // Look for new cards
  if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()) {
    if (memcmp(rfid.uid.uidByte, uidToMatch, rfid.uid.size) == 0) {
      Serial.println("Matching NFC card found");

      // Turn on the Green LED for 1 second
      digitalWrite(GREEN_LED_PIN, HIGH); 
      delay(1000);                      
      digitalWrite(GREEN_LED_PIN, LOW); 
    } else {
      Serial.println("Non-matching NFC card found");
      // Turn on the Red LED for 1 second
      digitalWrite(RED_LED_PIN, HIGH); 
      delay(1000);                      
      digitalWrite(RED_LED_PIN, LOW); 

    }

    // Print UID of card
    Serial.print("Found an NFC card with UID: ");
    for (byte i = 0; i < rfid.uid.size; i++) {
      Serial.print(rfid.uid.uidByte[i], HEX);
      Serial.print(" ");
    }
    Serial.println();
    rfid.PICC_HaltA(); // Halt PICC
    rfid.PCD_StopCrypto1(); // Stop encryption on PCD
    delay(1000); // wait a second before trying to read another card
  }
}
