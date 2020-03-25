/*
 *  Program Written: by Samuel Eastment Davidson
 *  UNSW zid: z5117804
 *  This coded was altered for a pump system in Thesis B
 *  The code takes input from bluetooth to power a pump system
  */

#include <Wire.h> 



const byte numChars = 32;
char serial1Chars[numChars];    // an array to store the received data
char serialChars[numChars];     // an array to store the received data
char vertArray[100];   // Array for vertical walls
char horiArray[100]; // Array for horzontal walls
char lineprint[numChars]; // Array for whats to be printed 

boolean newData  = false;
boolean newData1 = false;

boolean ToBeChecked = false;

boolean vertSet  = false;
boolean horiSet  = false;

char rc;
char rc1;

using namespace std;




void setup() {
  // Serial initlialisation
  Serial.begin(115200); //Tx0 and Rx0  
  Serial1.begin(115200);  //Tx1 and Rx1  

  // Connections for pumps
  pinMode(22, OUTPUT); 
  pinMode(24, OUTPUT); 
  pinMode(26, OUTPUT); 

  //Serial2;  //Tx2 and Rx2
  //Serial3;  //Tx3 and Rx3
  
  // LCD initlialisation
  // initialize the LCD
  
 
  // For testing print to lcd and both serial monitors
  Serial.println("<Arduino is ready to use>");  //To Desktop
  Serial1.println("<Arduino is ready to use>"); //To bluetooth
  
  delay(1000);
  digitalWrite(22, HIGH);  // sets the digital pin 13 off
  Serial.println("Pump Off");  //To Desktop
  Serial1.println("Pump Off"); //To bluetooth

}

void loop() {
  // put your main code here, to run repeatedly:

  //delay(2000);
  //Serial.println(horiSet);
  //Serial.println(horiArray);
  //delay(2000);

  if (Serial.available() > 0) {
    rc = Serial.read();
    Serial.println(rc);
  }
  
  if (Serial1.available() > 0) {
    rc1 = Serial1.read();
    Serial.println(rc1);
  }
  if (rc == '1'){
    
  }
  if (rc == '1' || rc1 == '1') {
    // Use pump 1 -- put power to pump
    Serial.println("Pump 1 Activated");
    digitalWrite(22, LOW);
    Serial.println("Pump on");  //To Desktop
    delay(10000);            // waits for a second
    digitalWrite(22, HIGH);  // sets the digital pin 13 off
    Serial.println("Pump Off");  //To Desktop

    delay(11000);
    rc  = 0;
    rc1 = 0;
     
      }
 
}
