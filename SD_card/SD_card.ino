#include <SPI.h>
#include <SD.h>
#include "i2c_BMP280.h"

BMP280 bmp;
File myFile;

float temperature;
float pressure;
int delayPrint = 1000;
unsigned long timerPrint = millis() + delayPrint;

void setup()
{
  Serial.begin(115200);
  initBMP();
  initSD();
  initTxt();
}

void loop()
{
  readValues();
  showValues();
  saveValuesToTxT();
}

void saveValuesToTxT()
{
  myFile = SD.open("text.txt", FILE_WRITE);
  
  if (myFile)
  {
    myFile.print(temperature);
    myFile.print(",");
    myFile.println(pressure);

    myFile.close();
  }
  else
  {
    Serial.println("Cannot open file");
  }
}

void showValues()
{
  if (millis() > timerPrint)
  {
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" C");
    Serial.print("Pressure: ");
    Serial.print(pressure);
    Serial.println(" Pa");

    timerPrint = millis() + delayPrint;
  }
}

void readValues()
{
  bmp.awaitMeasurement();
  bmp.getTemperature(temperature);
  bmp.getPressure(pressure);
}

void initTxt()
{
  
  myFile = SD.open("text.txt", FILE_WRITE);
  
  if (myFile)
  {
    Serial.println("Writing values to SD");
    myFile.println("Temperature:,Pressure:");

    myFile.close();
  }
  else
  {
    Serial.println("Cannot open file");
  }
}

void initSD()
{
  Serial.print("Initializing SD card...");
  if (!SD.begin(10))
  {
    Serial.println("Init failed!");
    while(1);
  }
}

void initBMP()
{
  Serial.print("Probe BMP280: ");
  if (bmp.initialize()) Serial.println("Sensor found");
  else
  {
    Serial.println("Sensor missing");
    while (1) {}
  }
}
