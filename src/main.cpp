#include <Arduino.h>

// библиотека для работы I²C
#include <Wire.h>
#include <TroykaIMU.h>
#define ADDRESS 0x60

Compass compass; 

//allocate memory
  byte byteHigh, byteLow, fine;
  int bering;
  char pitch, roll;

void setup()
{
  Wire.begin();  
  Serial.begin(9600);
  Serial.println("Begin init...");

  // инициализация компаса
  compass.begin(); 

  // устанавливаем чувствительность компаса
  // ±4 gauss — по умолчанию, ±8 gauss, ±12 gauss, ±16 gauss
  compass.setRange(RANGE_4_GAUSS); 
  
  Serial.println("Initialization completed");
}

void loop()
{
 // выводим азимут относительно оси Z
  Serial.print(compass.readAzimut());
  Serial.println(" Degrees");
  delay(100);
  
//begin communication with CMPS11
Wire.beginTransmission(ADDRESS);
Wire.write(2); //start read
Wire.endTransmission();

// Запрос 4 байта из CMPS11
  Wire.requestFrom(ADDRESS, 4);

// Ожидание поступления байтов
while(Wire.available() < 4);

// Чтение значений
byteHigh = Wire.read();  
byteLow = Wire.read(); 
pitch = Wire.read(); 
roll = Wire.read();

// Calculate full bearing
bearing =((byteHigh<<8)+ byteLow)/10;

// Calculate bearing decimal  
fine =((byteHigh<<8)+ byteLow)%10;

// Print data to Serial Monitor window
Serial.print("\t\t$Compass,");
Serial.print(bearing, DEC);
Serial.print("\n");
/*
Serial.print(pitch, DEC);
Serial.print(",");
Serial.println(roll, DEC);
*/
delay(100);

  Serial.print("\t\t\t\tTime: ");
   Serial.println(millis());
    Serial.println("\n");
  delay(0);
}