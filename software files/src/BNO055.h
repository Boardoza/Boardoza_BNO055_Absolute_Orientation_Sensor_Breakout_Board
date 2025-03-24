#ifndef BNO055_h
#define BNO055_h

#include <Arduino.h>
#include <Wire.h>

//PAGE 0 DESCRIPTION
#define CHIP_ID 0x00
#define ACC_ID 0x01
#define MAG_ID 0x02
#define GYRO_ID 0x03
#define SW_REV_ID_LSB 0x04
#define SW_REV_ID_MSB 0x05
#define BL_REV_ID 0x06
#define PAGE_ID 0x07
#define ACC_X_LSB 0x08
#define ACC_X_MSB 0x09
#define ACC_Y_LSB 0x0A
#define ACC_Y_MSB 0x0B
#define ACC_Z_LSB 0x0C
#define ACC_Z_MSB 0x0D
#define MAG_X_LSB 0x0E
#define MAG_X_MSB 0x0F
#define MAG_Y_LSB 0x10
#define MAG_Y_MSB 0x11
#define MAG_Z_LSB 0x12
#define MAG_Z_MSB 0x13
#define GYR_X_LSB 0x14
#define GYR_X_MSB 0x15
#define GYR_Y_LSB 0x16
#define GYR_Y_MSB 0x17
#define GYR_Z_LSB 0x18
#define GYR_Z_MSB 0x19
#define EUL_X_LSB 0x1A
#define EUL_X_MSB 0x1B
#define EUL_Y_LSB 0x1C
#define EUL_Y_MSB 0x1D
#define EUL_Z_LSB 0x1E
#define EUL_Z_MSB 0x1F
#define QUA_W_LSB 0x20
#define QUA_W_MSB 0x21
#define QUA_X_LSB 0x22
#define QUA_X_MSB 0x23
#define QUA_Y_LSB 0x24
#define QUA_Y_MSB 0x25
#define QUA_Z_LSB 0x26
#define QUA_Z_MSB 0x27
#define LIA_X_LSB 0x28
#define LIA_X_MSB 0x29
#define LIA_Y_LSB 0x2A
#define LIA_Y_MSB 0x2B
#define LIA_Z_LSB 0x2C
#define LIA_Z_MSB 0x2D
#define GRV_X_LSB 0x2E
#define GRV_X_MSB 0x2F
#define GRV_Y_LSB 0x30
#define GRV_Y_MSB 0x31
#define GRV_Z_LSB 0x32
#define GRV_Z_MSB 0x33
#define TEMP      0x34
#define CALIB_STAT 0x35
#define SELFTEST_RESULT 0x36
#define INT_STA 0x37
#define SYS_CLK_STATUS 0x38
#define SYS_STATUS 0x39
#define SYS_ERR   0x3A
#define UNIT_SEL 0x3B
#define OPR_MODE  0x3D
#define PWR_MODE  0x3E
#define SYS_TRIGGER 0x3F
#define TEMP_SOURCE 0x40
#define AXIS_MAP_CONFIG 0x41
#define AXIS_MAP_SIGN 0x42
#define ACC_OFFSET_X_LSB 0x55
#define ACC_OFFSET_X_MSB 0x56
#define ACC_OFFSET_Y_LSB 0x57
#define ACC_OFFSET_Y_MSB 0x58
#define ACC_OFFSET_Z_LSB 0x59
#define ACC_OFFSET_Z_MSB 0x5A
#define MAG_OFFSET_X_LSB 0x5B
#define MAG_OFFSET_X_MSB 0x5C
#define MAG_OFFSET_Y_LSB 0x5D
#define MAG_OFFSET_Y_MSB 0x5E
#define MAG_OFFSET_Z_LSB 0x5F
#define MAG_OFFSET_Z_MSB 0x60
#define GYR_OFFSET_X_LSB 0x61
#define GYR_OFFSET_X_MSB 0x62
#define GYR_OFFSET_Y_LSB 0x63
#define GYR_OFFSET_Y_MSB 0x64
#define GYR_OFFSET_Z_LSB 0x65
#define GYR_OFFSET_Z_MSB 0x66
#define ACC_RADIUS_LSB 0x67
#define ACC_RADIUS_MSB 0x68
#define MAG_RADIUS_LSB 0x69
#define MAG_RADIUS_MSB 0x6A

//PAGE 1 DESCRIPTION
#define ACC_CONFIG 0x08
#define MAG_CONFIG 0x09
#define GYR_CONFIG_0 0x0A
#define GYR_CONFIG_1 0x0B
#define ACC_SLEEP_CONFIG 0x0C
#define GYR_SLEEP_CONFIG 0x0D
#define INT_MSK 0x0F
#define INT_EN 0x10
#define ACC_AM_THRES 0x11
#define ACC_INT_SETTINGS 0x12
#define ACC_HG_DURATION 0x13
#define ACC_HG_THRES 0x14
#define ACC_NM_THRES 0x15
#define ACC_NM_SET 0x16
#define GYR_INT_SETTING 0x17
#define GYR_HR_X_SET 0x18
#define GYR_DUR_X 0x19
#define GYR_HR_Y_SET 0x1A
#define GYR_DUR_Y 0x1B
#define GYR_HR_Z_SET 0x1C
#define GYR_DUR_Z 0x1D
#define GYR_AM_THRES 0x1E
#define GYR_AM_SET 0x1F

//UNIT DEFINES
#define MG 0x01
#define MS2 0xFE
#define RPS 0x02
#define DPS 0xFD
#define RADIANS 0x03
#define DEGREES 0xFB
#define FAHRENHEIT 0x10
#define CELCIUS 0xEF

//INTERRUPT MODES
#define ACC_NM 0x80
#define ACC_AM 0x40
#define ACC_HIGH_G 0x20
#define GYR_DRDY 0x10
#define GYR_HIGH_RATE 0x08
#define GYRO_AM 0x04
#define MAG_DRDY 0x02
#define ACC_BSX_DRDY 0x01

enum PowerMode {
  POWERMODE_NORMAL = 0x00,
  POWERMODE_LOW = 0x01,
  POWERMODE_SUSPEND = 0x02,
  POWERMODE_INVALID = 0x03
};

enum OperationMode {
  OPERATION_MODE_CONFIG = 0x00,
  OPERATION_MODE_ACCONLY = 0x01,
  OPERATION_MODE_MAGONLY = 0x02,
  OPERATION_MODE_GYRONLY = 0x03,
  OPERATION_MODE_ACCMAG = 0x04,
  OPERATION_MODE_ACCGYRO = 0x05,
  OPERATION_MODE_MAGGYRO = 0x06,
  OPERATION_MODE_AMG = 0x07,
  OPERATION_MODE_IMUPLUS = 0x08,
  OPERATION_MODE_COMPASS = 0x09,
  OPERATION_MODE_M4G = 0x0A,
  OPERATION_MODE_NDOF_FMC_OFF = 0x0B,
  OPERATION_MODE_NDOF = 0x0C
};

enum axisRemapConfig {
  REMAP_CONFIG_P0 = 0x21,
  REMAP_CONFIG_P1 = 0x24, // default
  REMAP_CONFIG_P2 = 0x24,
  REMAP_CONFIG_P3 = 0x21,
  REMAP_CONFIG_P4 = 0x24,
  REMAP_CONFIG_P5 = 0x21,
  REMAP_CONFIG_P6 = 0x21,
  REMAP_CONFIG_P7 = 0x24
};

typedef struct {
  uint8_t accel_rev;
  uint8_t mag_rev;
  uint8_t gyro_rev;
  uint16_t sw_rev;
  uint8_t bl_rev;
} revInfo;

enum axisRemapSign {
  REMAP_SIGN_P0 = 0x04,
  REMAP_SIGN_P1 = 0x00, // default
  REMAP_SIGN_P2 = 0x06,
  REMAP_SIGN_P3 = 0x02,
  REMAP_SIGN_P4 = 0x03,
  REMAP_SIGN_P5 = 0x01,
  REMAP_SIGN_P6 = 0x07,
  REMAP_SIGN_P7 = 0x05
};

enum AccRange {
  ACC_RANGE_2G = 0x00,
  ACC_RANGE_4G = 0x01,
  ACC_RANGE_8G = 0x02,
  ACC_RANGE_16G = 0x03
};

enum AccBW {
  ACC_BW_7_81 = 0x00,
  ACC_BW_15_63 = 0x01,
  ACC_BW_31_25 = 0x02,
  ACC_BW_62_5 = 0x03,
  ACC_BW_125 = 0x04,
  ACC_BW_250 = 0x05,
  ACC_BW_500 = 0x06,
  ACC_BW_1000 = 0x07
};

enum AccOPMode {
  ACC_MODE_NORMAL = 0x00,
  ACC_MODE_SUSPEND = 0x01,
  ACC_MODE_LP1 = 0x02,
  ACC_MODE_STANDBY = 0x03,
  ACC_MODE_LP2 = 0x04,
  ACC_MODE_DEEPSUSPEND = 0x05
};

enum GyrRange {
  GYRO_RANGE_2000 = 0x00,
  GYRO_RANGE_1000 = 0x01,
  GYRO_RANGE_500 = 0x02,
  GYRO_RANGE_250 = 0x03,
  GYRO_RANGE_125 = 0x04
};

enum GyrBW {
  GYRO_BW_523 = 0x00,
  GYRO_BW_230 = 0x01,
  GYRO_BW_116 = 0x02,
  GYRO_BW_47 = 0x03,
  GYRO_BW_23 = 0x04,
  GYRO_BW_12 = 0x05,
  GYRO_BW_64 = 0x06,
  GYRO_BW_32 = 0x07
};

enum GyrOPMode {
  GYRO_MODE_NORMAL = 0x00,
  GYRO_MODE_FAST_POWERUP = 0x01,
  GYRO_MODE_DEEPSUSPEND = 0x02,
  GYRO_MODE_SUSPEND = 0x03,
  GYRO_MODE_ADV_POWERSAVE = 0x04
};

enum MagRate {
  MAG_RATE_2 = 0x00,
  MAG_RATE_6 = 0x01,
  MAG_RATE_8 = 0x02,
  MAG_RATE_10 = 0x03,
  MAG_RATE_15 = 0x04,
  MAG_RATE_20 = 0x05,
  MAG_RATE_25 = 0x06,
  MAG_RATE_30 = 0x07,
};

enum MagPMode {
  MAG_MODE_NORMAL = 0x00,
  MAG_MODE_SLEEP = 0x01,
  MAG_MODE_SUSPEND = 0x02,
  MAG_MODE_FORCE_MODE = 0x03
};

enum MagOPMode {
  MAG_MODE_LP = 0x00,
  MAG_MODE_REGULAR = 0x01,
  MAG_MODE_ENH_REGULAR = 0x02,
  MAG_MODE_HIGH_ACCURACY = 0x03
};

class BNO055 {
  public:
      BNO055();
      bool begin();
      void reset();
      bool isReady();
      void setPowerMode(PowerMode powermode);
      void setOperationMode(OperationMode mode);
      OperationMode getMode();
      void setPage(uint8_t page);
      void getPage();
      void interruptReset();
      void interruptMask(uint8_t mask);
      void interruptEnable(uint8_t regVal);
      void interruptDisable();
      void accAMThresh(uint8_t threshold);
      void accIntSettings(uint8_t hgAxis, uint8_t motionAxis, uint8_t duration);
      void accHGSettings(uint8_t hgDuration);
      void accHGThresh(uint8_t threshold);
      void accNMThresh(uint8_t threshold);
      void accNMSet(uint8_t duration, bool motion);
      void gyrIntSettings(uint8_t hrFilter, uint8_t amFilter, uint8_t hrAxis, uint8_t amAxis);
      void gyrHrXSet(uint8_t hrHysteresis, uint8_t threshold);
      void gyrDurationX(uint8_t duration);
      void gyrHrYSet(uint8_t hrHysteresis, uint8_t threshold);
      void gyrDurationY(uint8_t duration);
      void gyrHrZSet(uint8_t hrHysteresis, uint8_t threshold);
      void gyrDurationZ(uint8_t duration);
      void gyrAmThresh(uint8_t threshold);
      void gyrAmSet(uint8_t duration, uint8_t samples);
      void setUnit(uint8_t unitValue);
      void setAccConfig(AccRange accRange, AccBW accBW, AccOPMode accOPmode);
      void setGyroConfig(GyrRange gyrRange, GyrBW gyrBW, GyrOPMode gyrOPmode);
      void setMagConfig(MagRate rate, MagPMode Pmode, MagOPMode magOPmode);
      void setAccSleepConfig(uint8_t duration, bool mode);
      void setGyrSleepConfig(uint8_t autoSleepDuration, uint8_t sleepDuration);
      void accOffsetX(uint16_t offset);
      void accOffsetY(uint16_t offset);
      void accOffsetZ(uint16_t offset);
      void magOffsetX(uint16_t offset);
      void magOffsetY(uint16_t offset);
      void magOffsetZ(uint16_t offset);
      void gyrOffsetX(uint16_t offset);
      void gyrOffsetY(uint16_t offset);
      void gyrOffsetZ(uint16_t offset);
      void getAcceleration(float& x, float& y, float& z);
      void setAxisRemap(axisRemapConfig remapconfig);
      void setAxisSign(axisRemapSign remapsign);
      void getrevInfo(revInfo *);
      void getGravity(float& x, float& y, float& z);
      void getLinearAcceleration(float& x, float& y, float& z);
      void getEulerAngles(float& heading, float& roll, float& pitch);
      void getQuaternions(float& w, float& x, float& y, float& z);
      void getCalibrationStatus(uint8_t& sys, uint8_t& gyro, uint8_t& accel, uint8_t& mag);
      void getMagnetometer(float& x, float& y, float& z);
      void getGyroscope(float &x, float &y, float &z);
      void getTemperature(float& temperature);
      void getQuaternionAccuracy(float& w, float& x, float& y, float& z);
      void getAngularVelocity(float& x, float& y, float& z);
      void getSystemStatus(uint8_t *system_status, uint8_t *self_test_result, uint8_t *system_error);
      bool isFullyCalibrated();
      bool writeByte(uint8_t reg, uint8_t value);
      uint8_t readByte(uint8_t reg);
      void readBytes(uint8_t reg, uint8_t* buffer, uint8_t length);
      bool writeByteUART(uint8_t reg, uint8_t value);
      uint8_t readByteUART(uint8_t reg);
  private:
      uint8_t address;

      OperationMode mode;
      PowerMode powermode;
      AccRange accRange;
      AccBW accBW;
      AccOPMode accOPmode;
      GyrRange gyrRange;
      GyrBW gyrBW;
      GyrOPMode gyrOPmode;
      MagRate rate;
      MagOPMode magOPmode;
      MagPMode Pmode;
      axisRemapConfig remapconfig;
      axisRemapSign remapsign;
};
#endif