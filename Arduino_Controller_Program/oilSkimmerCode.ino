#include<LiquidCrystal.h>
LiquidCrystal lcd(13, 12, 11, 10, 9, 8); 
int inPin = 1;
float v2out;
float v1out;
int ucaction1;
int m1a = 6;
int m1b = 5;
int m2a = 4;
int m2b = 3;
 int uctimerf = 0;  
int ucmoist;               
char val = 0;
int GASval;
const int relay = A4 ;
const int buzz = A3 ;
int val2 = 0;
void setup()
{
  
  pinMode(inPin,INPUT); // Configuring pin A1 as input
  pinMode(pwm1,OUTPUT) ;    //we have to set PWM pin as output
  pinMode(pwm2,OUTPUT) ;    //we have to set PWM pin as output
  pinMode(m1a, OUTPUT);  // Digital pin 10 set as output Pin
  pinMode(m1b, OUTPUT);  // Digital pin 11 set as output Pin
  pinMode(m2a, OUTPUT);  // Digital pin 12 set as output Pin
  pinMode(m2b, OUTPUT);  // Digital pin 13 set as output Pin
  pinMode(relay,OUTPUT) ;    //we have to set PWM pin as output
  pinMode(buzz,OUTPUT) ;    //we have to set PWM pin as output
  Serial.begin(9600);
  lcd.begin(16,2);  
  delay(500);
  lcd.setCursor(0,0);
lcd.print("OIL SKIMMER   ");

lcd.setCursor(0,1);
lcd.print("                 ");
  delay(1000);
    delay(1000);
      digitalWrite(relay, HIGH);
        digitalWrite(buzz, HIGH);
     delay(1000);
      digitalWrite(relay, LOW);
        digitalWrite(buzz, LOW);
         lcd.setCursor(0,0);
lcd.print("                 ");

lcd.setCursor(0,1);
lcd.print("                 ");
delay(100);
 uctimerf = 30;
}
void loop() 
{

      analogWrite(pwm1,200) ;
     analogWrite(pwm2,200) ; 
lcd.setCursor(0,1);
lcd.print(uctimerf);
v1out=analogRead(BATTERYPin);
v1out= v1out/40;
lcd.setCursor(0,0);
lcd.print("Battery V=");
lcd.print(v1out);
lcd.print("V");
  if(uctimerf == 1)
  {
    uctimerf = 30;
 
     Serial.print("Battery Voltage = ");
     Serial.print(v1out);
     Serial.println(" V");
  }

  while(Serial.available() > 0)
  {
    val = Serial.read();
   // Serial.println(val);
   

   digitalWrite(buzz, HIGH);
   delay(200);
     digitalWrite(buzz, LOW);

  if( val == '4') // Forward
    {
      digitalWrite(m1a, LOW);
      digitalWrite(m1b, LOW);
 
    }
  else if(val == '3') // Backward
    {
      digitalWrite(m1a, LOW);
      digitalWrite(m1b, HIGH);

    }
  
    else if(val == '2') //Left
    {

         digitalWrite(relay, LOW);
        
    }
    else if(val == '1') //Right
    {
      digitalWrite(relay, HIGH);
    }
    if( val == '5') // Forward
    {
     // uctimerf = 1;
        digitalWrite(m2a, HIGH);
        digitalWrite(m2b, LOW); 
        delay(100);
        digitalWrite(m2a, LOW);
        digitalWrite(m2b, LOW); 
    }
    if( val == '6') // Forward
    {
      // uctimerf = 0;
        digitalWrite(m2a, LOW);
        digitalWrite(m2b, HIGH); 
        delay(100);
         digitalWrite(m2a, LOW);
        digitalWrite(m2b, LOW); 
    }
    if(val == '0') //Stop
    {
      digitalWrite(m1a, LOW);
      digitalWrite(m1b, LOW);
      digitalWrite(m2a, LOW);
      digitalWrite(m2b, LOW); 
     
       analogWrite(pwm1,0) ;
       analogWrite(pwm2,0) ;
       digitalWrite(relay, LOW);
    }
  }
}
