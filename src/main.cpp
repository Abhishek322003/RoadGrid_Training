#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 5
#define RST_PIN 22

// Initialize objects
MFRC522 rfid(SS_PIN, RST_PIN);
LiquidCrystal_I2C lcd(0x27, 20, 4);

void setup() {
  Serial.begin(115200);   // UART output
  SPI.begin();             // SPI bus for RFID
  rfid.PCD_Init();         // Initialize RFID

  lcd.init();              // Initialize LCD
  lcd.backlight();         // Turn on backlight
  lcd.setCursor(0, 0);
  lcd.print("Scan RFID Card...");
}

void loop() {
  // Check for a new card
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) {
    delay(50);
    return;
  }
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Card UID:");
  byte a[4]={0x42,0x52,0x29,0x03};
  // Print UID to LCD and Serial
  lcd.setCursor(0, 1);
  Serial.print("Card UID: ");
  int flag=1;
  for (byte i = 0; i < rfid.uid.size; i++)
    if (rfid.uid.uidByte[i]!=a[i]) { 
      flag=0;
      break;
    }
  for(byte i = 0; i < rfid.uid.size; i++){
     lcd.print(rfid.uid.uidByte[i], HEX);
     lcd.print(" ");
     Serial.print(rfid.uid.uidByte[i], HEX);
     Serial.print(" ");
  }
  lcd.setCursor(0,2);
  if(flag){
  lcd.print("Access denied"); 
  Serial.print("Aceess denied");}
  else{
    lcd.print("Access granted"); 
    Serial.print("Aceess granted");
  }
  Serial.println();
  // Optional: display timestamp or message on LCD
  lcd.setCursor(0, 3);
  lcd.print("Scan next card...");

  rfid.PICC_HaltA(); // Stop reading current card
  delay(1010);       // small delay before next read
}
