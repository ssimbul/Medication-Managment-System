/*
Medication Sorter Code
*/
 #include <Servo.h> 
 int MED1_Pin = 8; 
 int MED2_Pin = 9;
 int MED3_Pin =10; 
 int dayServoPin = 2;
 int timeServoPin = 3;
 const int startButton = 4; 
 int flag = 0;
 int flag2= 0; 
 int buttonState = 0;  
 Servo dayServo;
 Servo timeServo;
 int MED1[14]={1,2,1,2,1,1,1,1,1,1,1,1,1,1};
 int MED2[14]={1,2,1,2,1,1,1,1,1,1,1,1,1,1};
 int MED3[14]={1,2,1,2,1,1,1,1,1,1,1,1,1,1};

 String Day[14] = {"SUN_AM","MON_AM","TUES_AM","WED_AM","THURS_AM","FRI_AM","SAT_AM","SUN_PM","MON_PM","TUES_PM","WED_PM","THURS_PM","FRI_PM","SAT_PM"};
void setup(){
Serial.begin(9600);
pinMode(MED1_Pin, OUTPUT);
pinMode(MED2_Pin, OUTPUT);
pinMode(MED3_Pin, OUTPUT);
Serial.println ("Medication Management System Dev");
dayServo.attach(dayServoPin); 
timeServo.attach(timeServoPin); 
 digitalWrite(MED1_Pin, HIGH);      //Switch Solenoid ON
 digitalWrite(MED2_Pin, HIGH);
 digitalWrite(MED3_Pin, HIGH);
   dayServo.write (180);
   timeServo.write (45);
 pinMode(startButton, INPUT_PULLUP);    
}
 
void loop()
{
  buttonState = digitalRead(startButton);
   
  //If button pressed...
  if (buttonState == HIGH) {
      Serial.println("BUTTON PRESSED");
      flag=1; //change flag variable
    }

    if (flag == 1){
  //Dispense Loop 
  for (int i =0; i<3;i++){
      Dispense(i);
    }
    }
}

void Dispense (int x){
if (x==0){  
     Serial.println("Dispensing Medication 1");
     delay (2000);
     
       for (int i =0; i<14;i++){ // WHAT DAY? 
        delay (1000);
         changeDay(i);

         if (i > 6){
         changeTime(1); 
             delay(1000);
         }  //Wait
            
         else if (i <= 6 ) {
            changeTime(0); 
          }
      delay (1000);
        
       Serial.println("Dispensing Medication for: "+ Day[i]);
       // SOLENOID PUSHES OUT MED
       for (int j=0; j<MED1[i];j++){ // AMOUNT TO DISPENSE? 
        Serial.println (j);
        digitalWrite(MED1_Pin, LOW);      //Switch Solenoid ON
        delay(1000);                          //Wait 1 Second
        digitalWrite(MED1_Pin, HIGH);       //Switch Solenoid OFF
        delay(1000);
       }
 
    }
  
}
else if (x==1){  
     Serial.println("Dispensing Medication 2");
     delay (2000);
     
       for (int i =0; i<14;i++){ // WHAT DAY? 
        delay (1000);
         changeDay(i);
         delay (1000);

              if (i > 6){
         changeTime(1); 
             delay(1000);
         }  //Wait
            
         else if (i <= 6 ) {
            changeTime(0); 
          }

           delay (1000);
       Serial.println("Dispensing Medication for: "+ Day[i]);
       // SOLENOID PUSHES OUT MED
       for (int j=0; j<MED2[i];j++){ // AMOUNT TO DISPENSE? 
        Serial.println (j);
        digitalWrite(MED2_Pin, LOW);      //Switch Solenoid ON
        delay(1000);                          //Wait 1 Second
        digitalWrite(MED2_Pin, HIGH);       //Switch Solenoid OFF
    
       }
   
      delay (1000);
}
}
else if (x==2){  
     Serial.println("Dispensing Medication 3");

     delay (2000);
       for (int i =0; i<14;i++){ // WHAT DAY? 
        delay (1000);
       Serial.println("Dispensing Medication for: "+ Day[i]);
       // SOLENOID PUSHES OUT MED
        changeDay(i);

        if (i > 6){
         changeTime(1); 
             delay(1000);
         }  //Wait
            
         else if (i <= 6 ) {
            changeTime(0); 
          }
      delay (1000);

      
         delay (1000);
       for (int j=0; j<MED3[i];j++){ // AMOUNT TO DISPENSE? 

        Serial.println (j);
        digitalWrite(MED3_Pin, LOW);      //Switch Solenoid ON
        delay(1000);                          //Wait 1 Second
        digitalWrite(MED3_Pin, HIGH);       //Switch Solenoid OFF
        delay(1000); 
    
       }
    
      delay (1000);
}
}
}


void changeDay(int day) {
  if (day == 0 || day ==7){
    dayServo.write (180);
    Serial.println("Changing to SUN");
  }
  else if (day == 1 || day ==8){
    dayServo.write (150);
    Serial.println("Changing to MON");
  }
  else if (day == 2 || day ==9){
    dayServo.write (120);
      Serial.println("Changing to TUES");
  }
    else if (day == 3 || day ==10){
    dayServo.write (90);
      Serial.println("Changing to WED");
  }
  else if (day == 4 || day ==11){
    dayServo.write (60);
      Serial.println("Changing to THURS");
  }
   else if (day == 5 || day ==12){
    dayServo.write (30);
      Serial.println("Changing to FRI");
  }
    else if (day == 6 || day ==13){
    dayServo.write (0);
      Serial.println("Changing to SAT");
  }
}

void changeTime(int Time){
 if (Time == 0){
  timeServo.write (45);
  }
   else if (Time == 1){
  timeServo.write (135);
  }
  }
