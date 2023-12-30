#ifndef _LIB_ADAFRUIT_INA219_
#define _LIB_ADAFRUIT_INA219_

#include "Arduino.h"
#include <Adafruit_BusIO_Register.h>
#include <Adafruit_I2CDevice.h>
#include <Wire.h>

#define INA219_CALC_ADDRESS(INA_ADDR0, INA_ADDR1)                              \
  (0x40 | (INA_ADDR0 != 0 ? 0x01 : 0x00) | (INA_ADDR1 != 0 ? 0x04 : 0x00))

#define INA219_ADDRESS (0x40)

#define INA219_READ (0x01)

#define INA219_REG_CONFIG (0x00)

#define INA219_CONFIG_RESET (0x8000)

#define INA219_CONFIG_BVOLTAGERANGE_MASK (0x2000)

enum {
  INA219_CONFIG_BVOLTAGERANGE_16V = (0x0000),
  INA219_CONFIG_BVOLTAGERANGE_32V = (0x2000),
};

#define INA219_CONFIG_GAIN_MASK (0x1800)

enum {
  INA219_CONFIG_GAIN_1_40MV = (0x0000),
  INA219_CONFIG_GAIN_2_80MV = (0x0800),
  INA219_CONFIG_GAIN_4_160MV = (0x1000),
  INA219_CONFIG_GAIN_8_320MV = (0x1800),
};

#define INA219_CONFIG_BADCRES_MASK (0x0780)

enum {
  INA219_CONFIG_BADCRES_9BIT = (0x0000),
  INA219_CONFIG_BADCRES_10BIT = (0x0080),
  INA219_CONFIG_BADCRES_11BIT = (0x0100),
  INA219_CONFIG_BADCRES_12BIT = (0x0180),
  INA219_CONFIG_BADCRES_12BIT_2S_1060US = (0x0480),
  INA219_CONFIG_BADCRES_12BIT_4S_2130US = (0x0500),
  INA219_CONFIG_BADCRES_12BIT_8S_4260US = (0x0580),
  INA219_CONFIG_BADCRES_12BIT_16S_8510US = (0x0600),
  INA219_CONFIG_BADCRES_12BIT_32S_17MS = (0x0680),
  INA219_CONFIG_BADCRES_12BIT_64S_34MS = (0x0700),
  INA219_CONFIG_BADCRES_12BIT_128S_69MS = (0x0780),

};

#define INA219_CONFIG_SADCRES_MASK (0x0078)

    enum {
      INA219_CONFIG_SADCRES_9BIT_1S_84US = (0x0000),
      INA219_CONFIG_SADCRES_10BIT_1S_148US = (0x0008),
      INA219_CONFIG_SADCRES_11BIT_1S_276US = (0x0010),
      INA219_CONFIG_SADCRES_12BIT_1S_532US = (0x0018),
      INA219_CONFIG_SADCRES_12BIT_2S_1060US = (0x0048),
      INA219_CONFIG_SADCRES_12BIT_4S_2130US = (0x0050),
      INA219_CONFIG_SADCRES_12BIT_8S_4260US = (0x0058),
      INA219_CONFIG_SADCRES_12BIT_16S_8510US = (0x0060),
      INA219_CONFIG_SADCRES_12BIT_32S_17MS = (0x0068),
      INA219_CONFIG_SADCRES_12BIT_64S_34MS = (0x0070),
      INA219_CONFIG_SADCRES_12BIT_128S_69MS = (0x0078),
    };

#define INA219_CONFIG_MODE_MASK (0x0007)

enum {
  INA219_CONFIG_MODE_POWERDOWN = 0x00,
  INA219_CONFIG_MODE_SVOLT_TRIGGERED = 0x01,
  INA219_CONFIG_MODE_BVOLT_TRIGGERED = 0x02,
  INA219_CONFIG_MODE_SANDBVOLT_TRIGGERED = 0x03,
  INA219_CONFIG_MODE_ADCOFF = 0x04,
  INA219_CONFIG_MODE_SVOLT_CONTINUOUS = 0x05,
  INA219_CONFIG_MODE_BVOLT_CONTINUOUS = 0x06,
  INA219_CONFIG_MODE_SANDBVOLT_CONTINUOUS = 0x07,
};

#define INA219_REG_SHUNTVOLTAGE (0x01)

#define INA219_REG_BUSVOLTAGE (0x02)

#define INA219_REG_POWER (0x03)

#define INA219_REG_CURRENT (0x04)

#define INA219_REG_CALIBRATION (0x05)

class INA219 {
public:
  Adafruit_INA219(uint8_t addr = INA219_ADDRESS);
  ~Adafruit_INA219();
  bool begin(TwoWire *theWire = &Wire);
  void setCalibration_32V_2A();
  void setCalibration_32V_1A();
  void setCalibration_16V_400mA();
  float getBusVoltage_V();
  float getShuntVoltage_mV();
  float getCurrent_mA();
  float getPower_mW();
  void powerSave(bool on);
  bool success();

private:
  Adafruit_I2CDevice *i2c_dev = NULL;

  bool _success;

  uint8_t ina219_i2caddr = -1;
  uint32_t ina219_calValue;

  uint32_t ina219_currentDivider_mA;
  float ina219_powerMultiplier_mW;

  void init();
  int16_t getBusVoltage_raw();
  int16_t getShuntVoltage_raw();
  int16_t getCurrent_raw();
  int16_t getPower_raw();
};

#endif