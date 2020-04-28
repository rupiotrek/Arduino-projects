#include <LiquidCrystal_I2C.h>

#define POT A0
#define ENC_1 2
#define ENC_2 3

#define R 9
#define Y 10
#define G 4
#define IN_1 6
#define IN_2 8
#define Direct 12


LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

int potValue, duration;
float voltValue;
boolean Direction, enc1_lastState;

int delayPrint = 1000;
unsigned long timerPrint = millis() + delayPrint;

void setup()
{
  definePins();
  Serial.begin(9600);
  configLCD();
}

void loop()
{
  readValues();
  printStuff();
  writeValues();
}

void writeValues()
{

  digitalWrite(IN_1, digitalRead(Direct));
  digitalWrite(IN_2, !digitalRead(Direct));
  
  if (voltValue < 1.8)
  {
    digitalWrite(R, 1);
    digitalWrite(Y, 0);
    digitalWrite(G, 0);
  }
  else
  {
    digitalWrite(R, 0);
    digitalWrite(Y, Direction);
    digitalWrite(G, !Direction);
  }

}


void definePins()
{

  Direction = true;
  attachInterrupt(0, wheelSpeed, CHANGE);

  pinMode(POT, INPUT);
  pinMode(ENC_2, INPUT);
  pinMode(Direct, INPUT);
  
  pinMode(IN_1, OUTPUT);
  pinMode(IN_2, OUTPUT);
  pinMode(R, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(Y, OUTPUT);
}

void wheelSpeed()
{
  boolean Lstate = digitalRead(ENC_1);
  boolean val = digitalRead(ENC_2);
  if (!enc1_lastState && Lstate)
  {
    if (!val && Direction)
    {
      Direction = false;
    }
    else if (val && !Direction)
    {
      Direction = true;
    }
  }
  enc1_lastState = Lstate;
  if (!Direction) duration++;
  else duration--;
}

void configLCD()
{
  lcd.begin(16, 2);
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Hello!");
  delay(500);
  lcd.setCursor(0, 1);
  lcd.print("Prog DC Motor");
  delay(1000);
  lcd.clear();
}

float voltRead(int value)
{
  return value * 5.0 / 1023;
}

void printStuff() {
  if (millis() > timerPrint)
  {
    Serial.print("Napiecie sterowania: ");
    Serial.println(voltValue);

    Serial.print("Predkosc: ");
    Serial.print(duration);
    Serial.print("/");
    Serial.print(delayPrint/1000);
    Serial.println("  [puls/s]");

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("V ster: ");
    lcd.setCursor(8, 0);
    lcd.print(voltValue);

    duration = 0;

    timerPrint = millis() + delayPrint;
  }
}

void readValues()
{
  potValue = analogRead(POT);
  voltValue = voltRead(potValue);

}
