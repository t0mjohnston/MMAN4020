
//#include <Servo.h> 
#include <LiquidCrystal.h> 
LiquidCrystal lcd(13,12,7,6,5,4,3); 

int Echo = A1;  // Echo(P2.0)
int Trig =A0;  //  Trig (P2.1)

int Front_Distance = 0;
int Left_Distance = 0;
int Right_Distance = 0;

int Left_motor_go=8;     
int Left_motor_back=9;     

int Right_motor_go=10;    
int Right_motor_back=11;    



int servopin=2;//set servo pin to port2
int myangle;//set angle variable
int pulsewidth;//set pulsewidth
int val;


const int SensorRight = 3;     //right track IR sensor(P3.2 OUT1)
const int SensorLeft = 4;       //left track IR sensor(P3.3 OUT2)

const int SensorRight_2 = 5;    //right IR sensor(P3.4 OUT3)
const int SensorLeft_2 = 6;     //left IR sensor(P3.5 OUT4)

int SL;    //left track IR sensor status
int SR;    //right track IR sensor status
int SL_2;    //left IR sensor
int SR_2;    //right IR sensor status

void setup()
{
  Serial.begin(9600);    
  
  pinMode(Left_motor_go,OUTPUT); // PIN 8 (PWM)
  pinMode(Left_motor_back,OUTPUT); // PIN 9 (PWM)
  pinMode(Right_motor_go,OUTPUT);// PIN 10 (PWM) 
  pinMode(Right_motor_back,OUTPUT);// PIN 11 (PWM)
 
  pinMode(Echo, INPUT);    
  pinMode(Trig, OUTPUT);   
  lcd.begin(16,2);      
 
  pinMode(servopin,OUTPUT);
  pinMode(Left_motor_go,OUTPUT); // PIN 8 (PWM)
  pinMode(Left_motor_back,OUTPUT); // PIN 9 (PWM)
  pinMode(Right_motor_go,OUTPUT);// PIN 10 (PWM) 
  pinMode(Right_motor_back,OUTPUT);// PIN 11 (PWM)
  pinMode(SensorRight, INPUT); 
  pinMode(SensorLeft, INPUT);
  pinMode(SensorRight_2, INPUT); 
  pinMode(SensorLeft_2, INPUT); 
}


void run()     
{
  digitalWrite(Right_motor_go,HIGH);  
  digitalWrite(Right_motor_back,LOW);     
  analogWrite(Right_motor_go,165);
  analogWrite(Right_motor_back,0);
  digitalWrite(Left_motor_go,LOW);  
  digitalWrite(Left_motor_back,HIGH);
  analogWrite(Left_motor_go,0);
  analogWrite(Left_motor_back,160);
  //delay(time * 100);    
}

void brake(int time)  
{
  digitalWrite(Right_motor_go,LOW);
  digitalWrite(Right_motor_back,LOW);
  digitalWrite(Left_motor_go,LOW);
  digitalWrite(Left_motor_back,LOW);
  delay(time * 100); 
}

void left(int time)         
//void left()         
{
  digitalWrite(Right_motor_go,HIGH);	
  digitalWrite(Right_motor_back,LOW);
  analogWrite(Right_motor_go,180); 
  analogWrite(Right_motor_back,0);
  digitalWrite(Left_motor_go,LOW);   
  digitalWrite(Left_motor_back,LOW);
  analogWrite(Left_motor_go,0); 
  analogWrite(Left_motor_back,0);
  delay(time * 100);	 
}

void spin_left(int time)         
{
  digitalWrite(Right_motor_go,HIGH);	
  digitalWrite(Right_motor_back,LOW);
  analogWrite(Right_motor_go,200); 
  analogWrite(Right_motor_back,0);
  digitalWrite(Left_motor_go,HIGH);   
  digitalWrite(Left_motor_back,LOW);
  analogWrite(Left_motor_go,200); 
  analogWrite(Left_motor_back,0);
  delay(time * 100);	  
}

void right(int time)
//void right()       
{
  digitalWrite(Right_motor_go,LOW); 
  digitalWrite(Right_motor_back,LOW);
  analogWrite(Right_motor_go,0); 
  analogWrite(Right_motor_back,0);
  digitalWrite(Left_motor_go,LOW);
  digitalWrite(Left_motor_back,HIGH);
  analogWrite(Left_motor_go,0); 
  analogWrite(Left_motor_back,200);
  delay(time * 100);	  
}

void spin_right(int time)       
{
   digitalWrite(Right_motor_go,LOW);  
  digitalWrite(Right_motor_back,HIGH);
  analogWrite(Right_motor_go,0); 
  analogWrite(Right_motor_back,150);
  digitalWrite(Left_motor_go,LOW);
  digitalWrite(Left_motor_back,HIGH);
  analogWrite(Left_motor_go,0); 
  analogWrite(Left_motor_back,150);
  delay(time * 100);	   
}

void back(int time)          
{
   digitalWrite(Right_motor_go,LOW);
  digitalWrite(Right_motor_back,HIGH);
  analogWrite(Right_motor_go,0);
  analogWrite(Right_motor_back,150);
  digitalWrite(Left_motor_go,HIGH);  
  digitalWrite(Left_motor_back,LOW);
  analogWrite(Left_motor_go,150);
  analogWrite(Left_motor_back,0);
  delay(time * 100);       
}




float Distance_test()  
{ 
  digitalWrite(Trig, LOW);   
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);  
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);    
  float Fdistance = pulseIn(Echo, HIGH);  
  Fdistance= Fdistance/58;       

  return Fdistance;
}  

void Distance_display(int Distance)
{
  if((2<Distance)&(Distance<400))
  {
    lcd.home();         
    lcd.print("    Distance: ");       
    lcd.setCursor(6,2);  
    lcd.print(Distance);       
    lcd.print("cm");          
  }
  else
  {
    lcd.home();        
    lcd.print("!!! Out of range");      
  }
  delay(250);
  lcd.clear();
}

void servopulse(int servopin,int myangle)
{
  pulsewidth=(myangle*11)+500;
  digitalWrite(servopin,HIGH);
  delayMicroseconds(pulsewidth);
  digitalWrite(servopin,LOW);
 // delay(20-pulsewidth/1000);
  delay(20-(pulsewidth*0.001));
}

void front_detection()
{
  
  for(int i=0;i<=5;i++) 
  {
    servopulse(servopin,90);
  }
  Front_Distance = Distance_test();
  
}

void left_detection()
{
  for(int i=0;i<=15;i++) 
  {
    servopulse(servopin,175);
  }
  Left_Distance = Distance_test();
  
}

void right_detection()
{
  for(int i=0;i<=15;i++) 
  {
    servopulse(servopin,5);
  }
  Right_Distance = Distance_test();
  
}

void loop()
{
  
  while(1)
  {
    front_detection();//detect front distance
    SR_2 = digitalRead(SensorRight_2);
    SL_2 = digitalRead(SensorLeft_2);
    if(Front_Distance < 30  ||  SL_2 == LOW || SR_2==LOW)//when have obstacles in the front
    {
      
      brake(2);//stop to detect range
      left_detection();//detect left range
      Distance_display(Left_Distance);
      right_detection();//detect right range
      Distance_display(Right_Distance);
      if((Left_Distance < 30 ) &&( Right_Distance < 30 ))
        spin_left(0.7);
      else if(Left_Distance > Right_Distance)
      {      
        left(3);
        brake(1);
        
        run();
        right_detection();
        while(Right_Distance < 30){
          right_detection();
        }
        brake(1);
        right(2);
      }
      else
      {
        right(3);
        brake(1);
        
        run();
        left_detection();
        while(Left_Distance < 30){
          left_detection();
        }
        brake(1);
        left(2);
      }          
    }
    else
    {
      run();   
    }
  } 
}
