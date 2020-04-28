#include <LiquidCrystal_I2C.h>

#define progValue 3
#define G 4
#define R 9
#define Y 10

#define gasValue A0

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

int delayPrint = 1000;
unsigned long timerPrint = millis() + delayPrint;

byte pollutionValue;

void setup()
{
  definePins();
  configLCD();
  Serial.begin(9600);
}

void loop()
{
  readValues();
  printStuff();
  writeValues();
}

void writeValues()
{
  digitalWrite(R, !digitalRead(progValue));
  if (pollutionValue < 10)
  {
    digitalWrite(G, 1);
    digitalWrite(Y, 0);
    digitalWrite(R, 0);
  }
  else if ((pollutionValue > 9) && (pollutionValue < 50))
  {
    digitalWrite(G, 0);
    digitalWrite(Y, 1);
    digitalWrite(R, 0);
  }
  else
  {
    digitalWrite(G, 0);
    digitalWrite(Y, 0);
    digitalWrite(R, 1);
  }


}


void definePins()
{
  pinMode(progValue, INPUT);
  pinMode(gasValue, INPUT);

  pinMode(R, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(Y, OUTPUT);
}



void configLCD()
{
  lcd.begin(16, 2);
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Hello!");
  delay(500);
  lcd.setCursor(0, 1);
  lcd.print("Gas sensor prog");
  delay(1000);
  lcd.clear();
}



void printStuff() {
  if (millis() > timerPrint)
  {

    Serial.print("Procent gazu/dymu: ");
    Serial.print(pollutionValue);
    Serial.println("%");

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("% gazu/dymu: ");
    lcd.setCursor(0, 1);
    lcd.print(pollutionValue);
    lcd.setCursor(5, 1);
    lcd.print("%");


    timerPrint = millis() + delayPrint;
  }
}

void readValues()
{
  pollutionValue = map(analogRead(gasValue), 0, 1023, 0, 100);
}
