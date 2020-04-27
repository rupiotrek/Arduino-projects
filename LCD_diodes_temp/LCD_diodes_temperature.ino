#include <dht11.h>
#include <LiquidCrystal_I2C.h> // LCD I2C library


dht11 DHT11;
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

#define DHT11PIN 2
#define G 11
#define Y 8
#define R 6

void setup()
{
  configLCD();
  configPins();
  Serial.begin(115200);
  Serial.println("Program testowy DHT11");
  Serial.println();
}

void loop()
{
  temp_humidity_Function();
  LCD_Temperature();
  delay(1000);
}


void LCD_Temperature()
{
  float tempNow = (float)DHT11.temperature;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp(C): ");
  lcd.println(tempNow, 4);
  lcd.setCursor(0, 1);
  if (tempNow > 40)
  {
    lcd.print("Goraco!!!");
    Serial.println("Goraco!!!");
    digitalWrite(R, HIGH);
    digitalWrite(G, LOW);
    digitalWrite(Y, LOW);
  }
  else if (tempNow < 30)
  {
    lcd.print("Zimno!!!");
    Serial.println("Zimno!!!");
    digitalWrite(R, LOW);
    digitalWrite(G, LOW);
    digitalWrite(Y, HIGH);
  }
  else
  {
    lcd.print("OK");
    Serial.println("OK");
    digitalWrite(R, LOW);
    digitalWrite(G, HIGH);
    digitalWrite(Y, LOW);
  }
}

void temp_humidity_Function()
{
  int chk = DHT11.read(DHT11PIN);

  Serial.print("Stan sensora: ");
  switch (chk)
  {
    case DHTLIB_OK:
      Serial.print("OK ");
      break;
    case DHTLIB_ERROR_CHECKSUM:
      Serial.println("Błąd sumy kontrolnej");
      break;
    case DHTLIB_ERROR_TIMEOUT:
      Serial.println("Koniec czasu oczekiwania - brak odpowiedzi");
      break;
    default:
      Serial.println("Nieznany błąd");
      break;
  }
  Serial.print("Wilgotnosc (%): ");
  Serial.print((float)DHT11.humidity, 2);
  Serial.print("  ");
  Serial.print("Temperatura (C): ");
  Serial.println((float)DHT11.temperature - 10, 2);


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
}
