#include <Wire.h>   // I2C communication 
#include <LiquidCrystal_I2C.h> // LCD I2C library

#define R 7
#define Y 8
#define G 9
#define ARD_Led 13

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  

int LED_nr = 7;
bool LEDstate;
unsigned long timer_Ard_LED = millis() + 1000;
unsigned long timer_LED = millis() + 100;

void setup()
{
  configLCD();
  configPins();
  Serial.begin(9600);
}

void loop()
{

 Ard_LED_Blink();
 LED_nr = LEDBlinks(LED_nr);
 
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
  pinMode(Y, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(ARD_Led, OUTPUT);
}

void Ard_LED_Blink()
{
  if (millis() > timer_Ard_LED) 
  {
    digitalWrite(ARD_Led, !digitalRead(ARD_Led));
    timer_Ard_LED = millis() + 1000;
  }
  lcd.setCursor(0, 0);
  lcd.print("Arduino_LED:");
  lcd.setCursor(12, 0);
  lcd.print(digitalRead(ARD_Led));
}

int LEDBlinks(int LED_nr)
{
  if (millis() > timer_LED) {
    digitalWrite(LED_nr - 1, LOW);
    digitalWrite(LED_nr, HIGH);
    LED_nr++;
    timer_LED = millis() + 500;
    if (i > 9) LED_nr = 7;
    return LED_nr;
    
  }
  lcd.setCursor(0, 1);
  lcd.print("G:");
  lcd.setCursor(2, 1);
  lcd.print(digitalRead(G));
  lcd.setCursor(6, 1);
  lcd.print("Y:");
  lcd.setCursor(8, 1);
  lcd.print(digitalRead(Y));
  lcd.setCursor(12, 1);
  lcd.print("R:");
  lcd.setCursor(14, 1);
  lcd.print(digitalRead(R));
}
