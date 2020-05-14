#include <SPI.h>
#include <MFRC522.h>
 
#define RST_PIN         9           // Configurable, see typical pin layout above
#define SS_PIN          10          // Configurable, see typical pin layout above
 
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance
MFRC522::MIFARE_Key key;
MFRC522::StatusCode status;
 
//*****************************************************************************************//
void setup() {
  Serial.begin(9600);                                           // Initialize serial communications with the PC
  SPI.begin();                                                  // Init SPI bus
  mfrc522.PCD_Init();                                              // Init MFRC522 card
  Serial.println(F("Read personal data on a MIFARE PICC:"));    //shows in serial that it is ready to read
}

void ReadFromBlock (byte block, byte buff[] ){
  byte len=18;
    status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, block, &key, &(mfrc522.uid));
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("Authentication failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }
 
  status = mfrc522.MIFARE_Read(block, buff, &len);
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("Reading failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }
  
  }
//*****************************************************************************************//
void loop() {
 
  // Prepare key - all keys are set to FFFFFFFFFFFFh at chip delivery from the factory.
  for (byte i = 0; i < 6; i++) key.keyByte[i] = 0xFF;
 
  byte block;
  byte len;
  //-------------------------------------------
 
  // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }
 
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }
 
  Serial.println(F("**Card Detected:**"));
 
  byte buffer1[18];
  byte buffer2[18];
  
    byte buffer5[18];

        
  block = 4;
  byte  block2 = 8;
  byte  block5 = 9;
  
  ReadFromBlock (block, buffer1);
  ReadFromBlock (block2,buffer2);
  
   ReadFromBlock (block5,buffer5);
 
  
  uint8_t stop_val;

  for (uint8_t i = 0; i < 16; i++)
  {
     if (buffer1[i] == 00){
      stop_val=i;
      }
      
  }
  String value = "";
  String value2 = "";
 
  String value5 = "";
  
  for (uint8_t i = 0; i < stop_val; i++)
  {
      value += (char)buffer1[i];
  }

  for (uint8_t i = 0; i < 8; i++)
  {
      value2 += (char)buffer2[i];
   
      value5 += (char)buffer5[i];
   
  }
  value.trim();
  Serial.println("Patient Name: "+value);
  Serial.println("Time AM: "+value2);
    Serial.println("Time PM: "+value5);

  Serial.println(F("\n**End Reading**\n"));
 
  delay(1000);
 
  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();
}
