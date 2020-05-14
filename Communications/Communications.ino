#include<SPI.h>
#include<Ethernet.h>
#include <MFRC522.h>


//IP CONFIG
byte mac[] = {0x00, 0xBA, 0x6B, 0xCD, 0xDF, 0x02};
EthernetServer server(80);
String readString;
String firstName;
String LastName; 
String FullName;

//RFID CONFIG
#define RST_PIN         9           // Configurable, see typical pin layout above
#define SS_PIN          10          // Configurable, see typical pin layout above
 
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance
MFRC522::MIFARE_Key key;
MFRC522::StatusCode status;
byte nameBlock =4; 
byte amBlock1=8;
byte pmBlock1=9;


void setup() {
  Serial.begin(9600);
  Ethernet.begin(mac);
  server.begin();
  Serial.print("Server is at");
  Serial.println(Ethernet.localIP());

  SPI.begin();               // Init SPI bus
  mfrc522.PCD_Init();        // Init MFRC522 card



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
  EthernetClient client = server.available();

  if (client) {
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.print(c);

        if (readString.length() < 100) {
          readString += c;
        }

        if (c == '\n') {
          Serial.print(readString);
          client.println("<HTTP/1.1 200 OK>");
          client.println("<Connection-Type: text/html");
          client.println("<Connection: close");
          client.println("");

          client.println("<!DOCTYPE html>");
          client.println("<html>");
          client.println("<head>");
          client.println("<title>ELEC 3907</title>");
          client.println("</head>");
          client.println("<body>");
          client.println("<H1>HTML form GET example</H1>");

          client.println("<FORM ACTION='/' method=get >"); //uses IP/port of web page

          client.println("Patient Name: <INPUT TYPE=TEXT NAME='Name' VALUE='' SIZE='25' MAXLENGTH='50'><BR>");

          client.println("<INPUT TYPE=SUBMIT NAME='submit' VALUE='Upload'>");

          client.println("</FORM>");
          
          client.println("<body style=background-color:powderblue>");

          delay(1);
          client.stop();

        
           if (readString.length()>0){
           Serial.println(readString);
           int pos1=readString.indexOf('=');
           int pos2=readString.indexOf('+');
           int pos3=readString.indexOf('&');
           firstName= readString.substring(pos1+1,pos2);
           LastName= readString.substring(pos2+1,pos3);
           Serial.print("First Name: ");
           Serial.println(firstName);
           Serial.print("Last Name: ");
           Serial.println(LastName);
           FullName = firstName+" "+LastName;
           Serial.println(FullName);
              // Prepare key
  for (byte i = 0; i < 6; i++) key.keyByte[i] = 0xFF;
 
  // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }
  
  Serial.setTimeout(20000L);

//  String TimeAM= "10:50:00 ";
//  String TimePM= "17:20:00 ";
  
 
//  Convert (TimeAM,amBlock1);
//  Convert (TimePM,pmBlock1);
  Convert (FullName,nameBlock);
  
  Serial.println(" ");
  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();
           }
          
    
        }
      }
    }
  }



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
