// WRITING

#include <SPI.h>
#include <MFRC522.h>
 
#define RST_PIN         9           // Configurable, see typical pin layout above
#define SS_PIN          10          // Configurable, see typical pin layout above
 
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance
MFRC522::MIFARE_Key key;
MFRC522::StatusCode status;
byte nameBlock =4; 
byte amBlock1=8;
byte pmBlock1=9;


const int Green_Led= 2; 
const int Red_Led=3;
void setup() {
  Serial.begin(9600);        // Initialize serial communications with the PC
  SPI.begin();               // Init SPI bus
  mfrc522.PCD_Init();        // Init MFRC522 card
  pinMode(Green_Led,OUTPUT);
  pinMode (Red_Led,OUTPUT);
  Serial.println(F("Write personal data on a MIFARE PICC "));
}

 void Convert(String x,byte y)
      {
//         Serial.println (x);
         byte v[x.length()];
         x.getBytes(v,x.length());
         for (int i=0;i <= x.length();i++){
//          Serial.println(v[i]);
          }
         writeBytesToBlock(y, v);  
      }

void loop() {
 
  // Prepare key - all keys are set to FFFFFFFFFFFFh at chip delivery from the factory.
  for (byte i = 0; i < 6; i++) key.keyByte[i] = 0xFF;
 
  // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }
  
  Serial.setTimeout(20000L);


  String TimeAM= "10:50:00 ";
  String TimePM= "17:20:00 ";
  
  
  String patientName = "Izunna Otiji ";
  Convert (TimeAM,amBlock1);
  Convert (TimePM,pmBlock1);
  Convert (patientName,nameBlock);
  
  Serial.println(" ");
  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();
}
 
void writeBytesToBlock(byte block, byte buff[]) {
    status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, block, &key, &(mfrc522.uid));
    if (status != MFRC522::STATUS_OK) {
      Serial.print(F("PCD_Authenticate() failed: "));
      Serial.println(mfrc522.GetStatusCodeName(status));
      return;
    }
    else Serial.println(F("PCD_Authenticate() success: "));
    // Write block
    status = mfrc522.MIFARE_Write(block, buff, 16);
    if (status != MFRC522::STATUS_OK) {
      Serial.print(F("MIFARE_Write() failed: "));
      Serial.println(mfrc522.GetStatusCodeName(status));
      return;
    }
    else {Serial.println(F("MIFARE_Write() success: "));    
//    digitalWrite (Green_Led,1);
//    delay (2000);
//     digitalWrite (Green_Led,0);
    }   
}
