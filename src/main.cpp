/*******************************************************************************
 *
 *  File:          main.cpp
 * 
 * 
 *  License:       MIT License. See accompanying LICENSE file.
 * 
 *  Author:        Adam Karacsony
 * 
 *  Description:   To test the hardware futures of Mini-Lora Node v1.2
 *                 (Based on hallard's board https://github.com/hallard/Mini-LoRa)
 *                 On D3 pin a DS18B20 is mounted for Quick and Dirty temp measurement. 
 *  Dependencies:  External libraries:
 *                  Wire
 *                  robtillaart/DS18B20
 *                  SPI
 *                  
 *                 
 *                 
 *
 ******************************************************************************/

#include <Arduino.h>
#include <Wire.h> 
#include "DS18B20.h"


#define ONE_WIRE_BUS 3
OneWire oneWire(ONE_WIRE_BUS);
DS18B20 sensor(&oneWire);

// Microchip 24AA02E64T EUID
void readEEPROM_MAC(int deviceaddress, byte eeaddress)
{
  Wire.beginTransmission(deviceaddress);
  Wire.write(eeaddress); // LSB 
  Wire.endTransmission();
  Wire.requestFrom(deviceaddress, 8); //request 8 bytes from the device

  while (Wire.available()){
    Serial.print("0x");
    Serial.print(Wire.read(), HEX);
    Serial.print(" ");
  }
  Serial.println();
}

void setup(void)
{
  Serial.begin(115200);
  Serial.print("wire init...");
  Wire.begin();
  Serial.println("done");
  sensor.begin();
// Get Device Unique ID
  Serial.println("DeviceID:");
  readEEPROM_MAC(0x50, 0xF8);  //0x50 is the I2c address, 0xF8 is the memory address where the read-only MAC value is
// Get Board Temperature
  sensor.requestTemperatures();
  while (!sensor.isConversionComplete());  // wait until sensor is ready
  Serial.print("Temp: ");
  Serial.println(sensor.getTempC());
}

void loop(void)
{

}