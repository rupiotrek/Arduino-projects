
#include <Wire.h>   // I2C communication 
#include <LiquidCrystal_I2C.h> // LCD I2C library

#define R 7
#define G 9
#define MoveSensor 12

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

unsigned long timer_LED;
bool OutState;

void setup()
{
  configLCD();
  configPins();
  Serial.begin(9600);
}

void loop()
{
  if (!Move_Check())
  {
    digitalWrite(G, HIGH);
    digitalWrite(R, LOW);
    lcd.clear();
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
  pinMode(MoveSensor,INPUT);
}

bool Move_Check()
{
  bool
  if (digitalRead(MoveSensor))
  {
    timer_LED = millis();
    OutState = HIGH;
    digitalWrite(G, LOW);
    digitalWrite(R, HIGH);
  }

  if (OutState)
  {
    lcd.setCursor(0, 0);
    lcd.print("Wykryto ruch");
    lcd.setCursor(0, 1);
    lcd.print("ALARM !!!");
    Serial.println("Wykryto ruch. ALARM !!!");
  }
  
  if (millis() > timer_LED + 10000) OutState = LOW;
  return OutState;
}
