#include <Servo.h> 
#include <LiquidCrystal_I2C.h>

#define Mode 4
#define R 6
#define Y 8
#define G 11

#define servoPin A1

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
Servo servoX;


int pozycja = 0;
int delayPrint = 1000;
unsigned long timerPrint = millis() + delayPrint;
int tempValue = 0;
int angleFromSerial = 90;

const byte numChars = 32;
char receivedInfo[numChars];
String words[numChars];
boolean newData = false;


void setup()
{
  servoX.attach(servoPin);
  Serial.begin(9600);
  configLCD();
  configPins();
}

void loop()
{
  if (Serial.available() > 0)
  {
    angleFromSerial = Serial.parseInt();
  }
  
  if (digitalRead(Mode)) 
  {
    SerialServoOperation();
  } 
  else 
  {
    servoX.write(angleRead(analogRead(servoPin)));
    potStuff();
  }
  LEDReadServo(servoX.read());
}

void SerialServoOperation() 
{
  if ((servoX.read() != angleFromSerial) && (angleFromSerial != 0))
  {
    if (angleFromSerial == -1) angleFromSerial = 0;
    
    
    Serial.print("Zadany kat: ");
    Serial.println(angleFromSerial);
    
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Zadany kat: ");
    lcd.println(angleFromSerial);
    lcd.setCursor(12, 0);

    servoX.write(angleFromSerial);
  }

  if (millis() > timerPrint)
  {
    Serial.print("Serwo znajduje sie w katcie: ");
    Serial.println(servoX.read());
    lcd.setCursor(0, 1);
    lcd.print("Kat servo: ");
    lcd.setCursor(11, 1);
    lcd.println(servoX.read());

    timerPrint = millis() + delayPrint;
  }

}

void configLCD()
{
  lcd.begin(16, 2);
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Hello!");
  delay(500);
  lcd.setCursor(0, 1);
  lcd.print("Test LCD");
  delay(1000);
  lcd.clear();
}

void configPins()
{
  pinMode(R, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(Y, OUTPUT);
  pinMode(Mode, INPUT);
}

void potStuff()
{

  int potValue = analogRead(A1);
  float voltValue = voltRead(analogRead(A1));
  float angleValue = angleRead(analogRead(A1));

  if ((millis() > timerPrint) && (tempValue != potValue))
  {
    tempValue = potValue;
    
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("W:");
    lcd.setCursor(2, 0);
    lcd.print(potValue);
    lcd.setCursor(7, 0);
    lcd.print("V:");
    lcd.setCursor(9, 0);
    lcd.print(voltValue);
    lcd.setCursor(0, 1);
    lcd.print("K:");
    lcd.setCursor(2, 1);
    lcd.print(angleValue);

    Serial.print("Wartosc surowa: ");
    Serial.println(potValue);
    Serial.print("Wartosc napiecia: ");
    Serial.println(voltValue, 2);
    Serial.print("Wartosc kata: ");
    Serial.println(angleValue, 2);
    timerPrint = millis() + delayPrint;
  }
}

void LEDReadServo(int angleValue)
{
  if (angleValue > 120) 
  {
    digitalWrite(G, LOW);
    digitalWrite(Y, LOW);
    digitalWrite(R, HIGH);
  } 
  else if (angleValue < 60) 
  {
    digitalWrite(G, HIGH);
    digitalWrite(Y, LOW);
    digitalWrite(R, LOW);
  } 
  else  
  {
    digitalWrite(G, LOW);
    digitalWrite(R, LOW);
    digitalWrite(Y, HIGH);
  }
}

float voltRead(int value)
{
  return value * 5.0 / 1023;
}

float angleRead(int value)
{
  return value * 180.0 / 1023;
}
