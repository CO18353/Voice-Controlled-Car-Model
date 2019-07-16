#include <Servo.h> 
#include<LiquidCrystal_I2C.h>
#include<SoftwareSerial.h>
String value;
LiquidCrystal_I2C lcd(0x27 ,2 ,1 ,0 ,4 ,5, 6, 7, 3 ,POSITIVE);
int led1=5;
int led2=6;
Servo myservo; 
const int waterSens = A0;
int pos = 0;
int TxD = 11;
int RxD = 10;
int servoposition;
SoftwareSerial bluetooth(TxD, RxD);
void setup() 
{
  
  Serial.begin(9600);
  lcd.begin(16,2);
  myservo.attach(9);
  lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Automatic Rain");
    lcd.setCursor(0,1);
    lcd.print("Sensing CarWiper");
    delay(450);
  
  lcd.clear();
  lcd.setCursor(5,0);
  lcd.print("Rainfall");
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(13,OUTPUT);
  bluetooth.begin(9600);
}
void wiper()
{
  
  lcd.setCursor(10,1);
  int sensorValue = analogRead(waterSens);//read the water sensor value
  Serial.println(value);      
  sensorValue = map(sensorValue, 0, 1023, 0, 180); 
     if (sensorValue <= 45) 
     {
        lcd.setCursor(5,0);
        lcd.print("Rainfall");
        lcd.setCursor(3,1);
        lcd.print("Very high");
        analogWrite(led1,255);
        analogWrite(led2,255);
        for (pos = 0; pos <= 120; pos += 1) 
        {
          myservo.write(pos);              
            delay(5);                       
        }

        
        for (pos = 120; pos >= 0; pos -= 1) 
        { // goes from 180 degrees to 0 degrees
          myservo.write(pos);              
          delay(5);                       
        }
        lcd.clear();

     }
        else if (sensorValue >45 && sensorValue<=90) 
        {
          
        lcd.setCursor(5,0);
        lcd.print("Rainfall");
        lcd.setCursor(3,1);
        lcd.print("High");
        analogWrite(led1,100);
        analogWrite(led2,100);
         for (pos = 0; pos <= 120; pos += 1) 
        { // goes from 0 degrees to 180 degrees
          // in steps of 1 degree
          myservo.write(pos);              
            delay(10);                       
        }
  
        for (pos = 120; pos >= 0; pos -= 1) 
        { // goes from 180 degrees to 0 degrees
          myservo.write(pos);              
          delay(10);                      
        }
        lcd.clear();
     }

      else if (sensorValue >90 && sensorValue<=135) 
        {
          
        lcd.setCursor(5,0);
        lcd.print("Rainfall");
        lcd.setCursor(3,1);
        lcd.print("Moderate");
        analogWrite(led1,50);
        analogWrite(led2,50);
         for (pos = 0; pos <= 120; pos += 1) 
        { // goes from 0 degrees to 180 degrees
          // in steps of 1 degree
          myservo.write(pos);              
            delay(15);                       
        }
  
        for (pos = 120; pos >= 0; pos -= 1) 
        { // goes from 180 degrees to 0 degrees
          myservo.write(pos);              
          delay(15);                       
        }
        lcd.clear();
     }
     
    else
    {
      
       lcd.setCursor(5,0);
       lcd.print("Rainfall");
       lcd.setCursor(3,1);
       lcd.print("NO Rain");
       myservo.write(0);
       analogWrite(led1,0);
       analogWrite(led2,0);
     }

     Serial.println(sensorValue);
  delay(20); 
}
void loop() 
{
    wiper();

    if (bluetooth.available())
   {
    wiper();
    value = bluetooth.readString();

    if (value == "right indicator")
    {
      
      for(int i=0;i<5;i++)
      {
        digitalWrite(3, HIGH);
        delay(500);
        digitalWrite(3,LOW);
        delay(500);  
      }
    }

    if (value == "left indicator")
    {
      for(int i=0;i<5;i++)
      {
        digitalWrite(13, HIGH);
        delay(500);
        digitalWrite(13, LOW);  
        delay(500);
      }
              
    }
    if (value == "parking mode")
    {
      for(int i=0;i<5;i++)
      {
        digitalWrite(3,HIGH);
        digitalWrite(13,HIGH);
        digitalWrite(5,HIGH);
        digitalWrite(6,HIGH);
        delay(500);
        digitalWrite(3,LOW);
        digitalWrite(13,LOW);
        digitalWrite(5,LOW);
        digitalWrite(6,LOW);
        delay(500);
      }
    }

   }
        
}
