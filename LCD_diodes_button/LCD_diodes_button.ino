
#include <Wire.h>   // I2C communication 
#include <LiquidCrystal_I2C.h> // LCD I2C library

#define R 7
#define Y 8
#define G 9

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  

const byte numChars = 32;
char receivedInfo[numChars];
boolean newData = false;

void setup()
{
  configLCD();
  configPins();
  Serial.begin(9600);
}

void loop()
{
  readWithEndMarker();
  if (newData == true) {
    LED_Blink(receivedInfo[0]-48, receivedInfo[2]-48);
     newData = false;
  }
}


void readWithEndMarker() {
  static byte n_message_char = 0;
  char endMarker = '\n';
  char temp_message;

  while (Serial.available() > 0 && newData == false) 
  {
    temp_message = Serial.read();
    if (temp_message != endMarker) 
    {
      receivedInfo[n_message_char] = temp_message;
      n_message_char++;
      if (n_message_char >= numChars) 
      {
        n_message_char = numChars - 1;
      }
    }
    else 
    {
      receivedInfo[n_message_char] = '\0'; // terminate the string
      n_message_char = 0;
      newData = true;
    }
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
  pinMode(Y, OUTPUT);
  pinMode(G, OUTPUT);
}


int LED_Blink(int LED_nr, int LED_state)
{

  digitalWrite(LED_nr, LED_state);

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
