// ultrasonic sensor prints distance to lcd 

#include <Wire.h>
//#include "DFRobot_LCD.h"
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display
// lcd variables 
const int colorR = 255;
const int colorG = 0;
const int colorB = 0;
//DFRobot_LCD lcd(16,2);  //16 characters and 2 lines of show

// ultrasonic variables
const int trigPin = 9;
const int echoPin = 10; 
long duration; 
long distance; 

void setup() { 
  // ultrasonic setup
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600); // Starts the serial communication
  
  // lcd setup 
  lcd.init();
  lcd.backlight();
  //lcd.setRGB(colorR, colorG, colorB); //If the module is a monochrome screen, you need to shield it
  
  lcd.clear(); // clear the LCD.
} 

void loop() {
  // ultrasonic 
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2); 
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance= duration*0.034/2;

  // print to serior monitor in arduino ide
  Serial.print("distance: "); 
  Serial.println(distance); //Millisecond  

  // print to lcd 
  lcd.clear();
  lcd.print("distance: ");
  lcd.setCursor(0, 1);
  lcd.print(distance);

  // delay entire process 
  delay(500);
}
