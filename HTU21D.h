/* 
  HTU21D Humidity Sensor Library
  By: Nathan Seidle, since modified by bgbnbigben
  SparkFun Electronics
  Date: v1.1.3: September 22nd, 2013
        v1.2: April 12, 2019
  License: This code is public domain but you buy me (Nathan Seidle) a beer if you use this and we meet someday (Beerware license).
 
 Get humidity and temperature from the HTU21D sensor.
 
 This same library should work for the other similar sensors including the Si
*/
 

#if defined(ARDUINO) && ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

#include <I2C.h>

#define HTU21D_ADDRESS 0x40  // Unshifted 7-bit I2C address for the sensor

#define ERROR_BAD_CRC		0xFF

#define TRIGGER_TEMP_MEASURE_HOLD  0xE3
#define TRIGGER_HUMD_MEASURE_HOLD  0xE5
#define TRIGGER_TEMP_MEASURE_NOHOLD  0xF3
#define TRIGGER_HUMD_MEASURE_NOHOLD  0xF5
#define WRITE_USER_REG  0xE6
#define READ_USER_REG  0xE7
#define SOFT_RESET  0xFE

#define USER_REGISTER_RESOLUTION_MASK 0x81
#define USER_REGISTER_RESOLUTION_RH12_TEMP14 0x00
#define USER_REGISTER_RESOLUTION_RH8_TEMP12 0x01
#define USER_REGISTER_RESOLUTION_RH10_TEMP13 0x80
#define USER_REGISTER_RESOLUTION_RH11_TEMP11 0x81
#define USER_REGISTER_END_OF_BATTERY 0x40
#define USER_REGISTER_HEATER_ENABLED 0x04
#define USER_REGISTER_DISABLE_OTP_RELOAD 0x02

class HTU21D {

public:
  HTU21D();

  void begin(const I2C& = I2c);
  void setResolution(byte);

  byte readUserRegister(void);
  void writeUserRegister(byte);

  uint8_t triggerTemperatureReading();
  uint8_t triggerHumidityReading();
  bool isConversionComplete();
  float getHumidity();
  float getTemperature();

private:
  I2C *_i2cPort;
  bool _inFlight;

  uint16_t _wireValue;

  uint8_t triggerReading(byte);
};
