#include "BNO055.h"
#include <SoftwareSerial.h>

SoftwareSerial mySerial(21, 22);

#define I2C
//#define UART

/**
 * @brief Constructor for BNO055 class.
 * 
 * Initializes the BNO055 object with the sensor's I2C address.
 * 
 */
BNO055::BNO055() {
    address = 0x28; // BNO055 sensor's I2C address
}

/**
 * @brief Initializes the BNO055 sensor.
 * 
 * This function initializes the BNO055 sensor by setting the necessary configurations and modes.
 * 
 * @return True if the sensor is successfully initialized, false otherwise.
 */
bool BNO055::begin() {
    #ifdef I2C
    Wire.begin();
    setPage(0x00);
    writeByte(0x3D, 0x00);
    delay(50);
    setPowerMode(PowerMode::POWERMODE_NORMAL);
    delay(10);
    setOperationMode(OperationMode::OPERATION_MODE_CONFIG);
    delay(50);
    return isReady();
    #endif

    #ifdef UART
    mySerial.begin(115200);
    setPage(0x00);
    writeByte(0x3D, 0x00);
    delay(30);
    setPowerMode(PowerMode::POWERMODE_NORMAL);
    delay(20);
    setOperationMode(OperationMode::OPERATION_MODE_CONFIG);
    delay(30);
    return isReady();
    #endif
}

/**
 * @brief Resets the BNO055 sensor.
 * 
 * This function performs a reset on the BNO055 sensor by triggering a reset sequence.
 * 
 */
void BNO055::reset() {
    setPage(0x00);
    writeByte(SYS_TRIGGER, 0x20);    
    delay(500);
    writeByte(SYS_TRIGGER, 0x00);
    delay(50);
}

/**
 * @brief Checks if the BNO055 sensor is ready.
 * 
 * This function checks the self-test result register to determine if the sensor is ready for operation.
 * 
 * @return True if the sensor is ready, false otherwise.
 */
bool BNO055::isReady() {
    setPage(0x00);
    uint8_t selfTest = readByte(SELFTEST_RESULT);

    return (selfTest & 0x0F);
}

/**
 * @brief Sets the power mode of the BNO055 sensor.
 * 
 * This function sets the power mode of the BNO055 sensor to the specified mode.
 * 
 * @param powermode The power mode to set (NORMAL, LOWPOWER, SUSPEND).
 */
void BNO055::setPowerMode(PowerMode powermode) {
    setPage(0x00);
    writeByte(PWR_MODE, powermode);
}

/**
 * @brief Sets the operation mode of the BNO055 sensor.
 * 
 * This function sets the operation mode of the BNO055 sensor to the specified mode.
 * 
 * @param mode The operation mode to set (CONFIG, ACCONLY, MAGONLY, GYRONLY, etc.).
 */
void BNO055::setOperationMode(OperationMode mode) {
    setPage(0x00);
    writeByte(OPR_MODE, mode);
}

/**
 * @brief Gets the current operation mode of the BNO055 sensor.
 * 
 * This function reads the operation mode register of the BNO055 sensor to get the current operation mode.
 * 
 * @return The current operation mode of the sensor (CONFIG, ACCONLY, MAGONLY, GYRONLY, etc.).
 */
OperationMode BNO055::getMode() {
    setPage(0x00);
    return (OperationMode)readByte(OPR_MODE);
}

/**
 * @brief Sets the page ID of the BNO055 sensor.
 * 
 * This function sets the page ID of the BNO055 sensor to the specified page.
 * 
 * @param page The page ID to set.
 */
void BNO055::setPage(uint8_t page) {
    writeByte(PAGE_ID, page);
}

/**
 * @brief Gets the current page ID of the BNO055 sensor.
 * 
 * This function reads the page ID register of the BNO055 sensor to get the current page ID.
 * 
 * @return The current page ID of the sensor.
 */
void BNO055::getPage() {
    readByte(PAGE_ID);
}

/**
 * @brief Resets the interrupt of the BNO055 sensor.
 * 
 * This function resets the interrupt of the BNO055 sensor by writing a specific value to the SYS_TRIGGER register. 
 */
void BNO055::interruptReset() {
    writeByte(SYS_TRIGGER, 0x40);
}

/**
 * @brief Sets the interrupt mask of the BNO055 sensor.
 * 
 * This function sets the interrupt mask of the BNO055 sensor by writing a specific value to the INT_MSK register.
 * 
 * @param mask The mask value to set for interrupts.
 */
void BNO055::interruptMask(uint8_t mask) {
    setPage(0x01);
    writeByte(INT_MSK, mask);
}

/**
 * @brief Enables specific interrupts on the BNO055 sensor.
 * 
 * This function enables specific interrupts on the BNO055 sensor by writing a specific value to the INT_EN register.
 * 
 * @param regVal The value to enable specific interrupts.
 */
void BNO055::interruptEnable(uint8_t regVal) {
    setPage(0x01);
    writeByte(INT_EN, regVal);
}

/**
 * @brief Disables all interrupts on the BNO055 sensor.
 * 
 * This function disables all interrupts on the BNO055 sensor by writing 0x00 to the INT_EN register.
 */
void BNO055::interruptDisable() {
    setPage(0x01);
    writeByte(INT_EN, 0x00);
}

/**
 * @brief Sets the accelerometer activity detection threshold on the BNO055 sensor.
 * 
 * This function sets the accelerometer activity detection threshold on the BNO055 sensor by writing a specific value to the ACC_AM_THRES register.
 * 
 * @param threshold The threshold value for accelerometer activity detection.
 */
void BNO055::accAMThresh(uint8_t threshold) {
    setPage(0x01);
    writeByte(ACC_AM_THRES, threshold);
}

/**
 * @brief Sets the accelerometer interrupt settings on the BNO055 sensor.
 * 
 * This function sets the accelerometer interrupt settings on the BNO055 sensor by writing specific values to the ACC_INT_SETTINGS register.
 * 
 * @param hgAxis The axis for high-g interrupt (X_AXIS, Y_AXIS, Z_AXIS).
 * @param motionAxis The axis for motion interrupt (X_AXIS, Y_AXIS, Z_AXIS).
 * @param duration The duration value for the interrupt.
 */
void BNO055::accIntSettings(uint8_t hgAxis, uint8_t motionAxis, uint8_t duration) {
    setPage(0x01);
    writeByte(ACC_INT_SETTINGS, hgAxis << 5| motionAxis << 2| duration);
}

/**
 * @brief Sets the duration for high-g acceleration interrupt on the BNO055 sensor.
 * 
 * This function sets the duration for high-g acceleration interrupt on the BNO055 sensor by writing a specific value to the ACC_HG_DURATION register.
 * 
 * @param hgDuration The duration value for high-g acceleration interrupt.
 */
void BNO055::accHGSettings(uint8_t hgDuration) {
    setPage(0x01);
    writeByte(ACC_HG_DURATION, hgDuration);
}

/**
 * @brief Sets the threshold for high-g acceleration interrupt on the BNO055 sensor.
 * 
 * This function sets the threshold for high-g acceleration interrupt on the BNO055 sensor by writing a specific value to the ACC_HG_THRES register.
 * 
 * @param threshold The threshold value for high-g acceleration interrupt.
 */
void BNO055::accHGThresh(uint8_t threshold) {
    setPage(0x01);
    writeByte(ACC_HG_THRES, threshold);
}

/**
 * @brief Sets the threshold for no-motion interrupt on the BNO055 sensor.
 * 
 * This function sets the threshold for no-motion interrupt on the BNO055 sensor by writing a specific value to the ACC_NM_THRES register.
 * 
 * @param threshold The threshold value for no-motion interrupt.
 */
void BNO055::accNMThresh(uint8_t threshold) {
    setPage(0x01);
    writeByte(ACC_NM_THRES, threshold);
}

/**
 * @brief Sets the duration and motion flag for no-motion interrupt on the BNO055 sensor.
 * 
 * This function sets the duration and motion flag for the no-motion interrupt on the BNO055 sensor by updating the ACC_NM_SET register.
 * 
 * @param duration The duration value for the no-motion interrupt.
 * @param motion Flag indicating if motion should be considered for no-motion detection.
 */
void BNO055::accNMSet(uint8_t duration, bool motion) {
    setPage(0x01);
    uint8_t temp = readByte(ACC_NM_SET);
    temp = (temp & 0x80) | (duration << 1| motion);
    writeByte(ACC_NM_SET, temp);
}

/**
 * @brief Sets the gyro interrupt settings on the BNO055 sensor.
 * 
 * This function sets the gyro interrupt settings on the BNO055 sensor by writing specific values to the GYR_INT_SETTING register.
 * 
 * @param hrFilter High rate filter setting for gyro interrupt.
 * @param amFilter Any motion filter setting for gyro interrupt.
 * @param hrAxis Axis for high rate gyro interrupt (X_AXIS, Y_AXIS, Z_AXIS).
 * @param amAxis Axis for any motion gyro interrupt (X_AXIS, Y_AXIS, Z_AXIS).
 */
void BNO055::gyrIntSettings(uint8_t hrFilter, uint8_t amFilter, uint8_t hrAxis, uint8_t amAxis) {
    setPage(0x01);
    writeByte(GYR_INT_SETTING, hrFilter << 7 | amFilter << 6 | hrAxis << 3 | amAxis);
}

/**
 * @brief Sets the high rate hysteresis and threshold for X-axis gyro interrupt on the BNO055 sensor.
 * 
 * This function sets the high rate hysteresis and threshold for the X-axis gyro interrupt on the BNO055 sensor by updating the GYR_HR_X_SET register.
 * 
 * @param hrHysteresis The hysteresis value for high rate gyro interrupt.
 * @param threshold The threshold value for X-axis gyro interrupt.
 */
void BNO055::gyrHrXSet(uint8_t hrHysteresis, uint8_t threshold) {
    setPage(0x01);
    uint8_t temp = readByte(GYR_HR_X_SET);
    temp = (temp & 0x80) | (hrHysteresis << 5 | threshold);
    writeByte(GYR_HR_X_SET, temp);
}

/**
 * @brief Sets the duration for X-axis gyro interrupt on the BNO055 sensor.
 * 
 * This function sets the duration for X-axis gyro interrupt on the BNO055 sensor by writing a specific value to the GYR_DUR_X register.
 * 
 * @param duration The duration value for X-axis gyro interrupt.
 */
void BNO055::gyrDurationX(uint8_t duration) {
    setPage(0x01);
    writeByte(GYR_DUR_X, duration);
}

/**
 * @brief Sets the high rate hysteresis and threshold for Y-axis gyro interrupt on the BNO055 sensor.
 * 
 * This function sets the high rate hysteresis and threshold for the Y-axis gyro interrupt on the BNO055 sensor by updating the GYR_HR_Y_SET register.
 * 
 * @param hrHysteresis The hysteresis value for high rate gyro interrupt.
 * @param threshold The threshold value for Y-axis gyro interrupt.
 */
void BNO055::gyrHrYSet(uint8_t hrHysteresis, uint8_t threshold) {
    setPage(0x01);
    uint8_t temp = readByte(GYR_HR_Y_SET);
    temp = (temp & 0x80) | (hrHysteresis << 5 | threshold);
    writeByte(GYR_HR_Y_SET, temp);
}

/**
 * @brief Sets the duration for Y-axis gyro interrupt on the BNO055 sensor.
 * 
 * This function sets the duration for Y-axis gyro interrupt on the BNO055 sensor by writing a specific value to the GYR_DUR_Y register.
 * 
 * @param duration The duration value for Y-axis gyro interrupt.
 */
void BNO055::gyrDurationY(uint8_t duration) {
    setPage(0x01);
    writeByte(GYR_DUR_Y, duration);
}

/**
 * @brief Sets the high rate hysteresis and threshold for Z-axis gyro interrupt on the BNO055 sensor.
 * 
 * This function sets the high rate hysteresis and threshold for the Z-axis gyro interrupt on the BNO055 sensor by updating the GYR_HR_Z_SET register.
 * 
 * @param hrHysteresis The hysteresis value for high rate gyro interrupt.
 * @param threshold The threshold value for Z-axis gyro interrupt.
 */
void BNO055::gyrHrZSet(uint8_t hrHysteresis, uint8_t threshold) {
    setPage(0x01);
    uint8_t temp = readByte(GYR_HR_Z_SET);
    temp = (temp & 0x80) | (hrHysteresis << 5 | threshold);
    writeByte(GYR_HR_Z_SET, temp);
}

/**
 * @brief Sets the duration for Z-axis gyro interrupt on the BNO055 sensor.
 * 
 * This function sets the duration for Z-axis gyro interrupt on the BNO055 sensor by writing a specific value to the GYR_DUR_Z register.
 * 
 * @param duration The duration value for Z-axis gyro interrupt.
 */
void BNO055::gyrDurationZ(uint8_t duration) {
    setPage(0x01);
    writeByte(GYR_DUR_Z, duration);
}

/**
 * @brief Sets the angular rate threshold for gyro interrupt on the BNO055 sensor.
 * 
 * This function sets the angular rate threshold for gyro interrupt on the BNO055 sensor by writing a specific value to the GYR_AM_THRES register.
 * 
 * @param threshold The threshold value for angular rate gyro interrupt.
 */
void BNO055::gyrAmThresh(uint8_t threshold) {
    setPage(0x01);
    writeByte(GYR_AM_THRES, threshold);
}

/**
 * @brief Sets the duration and number of samples for gyro interrupt on the BNO055 sensor.
 * 
 * This function sets the duration and number of samples for gyro interrupt on the BNO055 sensor by updating the GYR_AM_SET register.
 * 
 * @param duration The duration value for gyro interrupt.
 * @param samples The number of samples for gyro interrupt.
 */
void BNO055::gyrAmSet(uint8_t duration, uint8_t samples) {
    setPage(0x01);
    uint8_t temp = readByte(GYR_AM_SET);
    temp = (temp & 0xF0) | (duration << 2 | samples);
    writeByte(GYR_AM_SET, temp);
}

/**
 * @brief Sets the unit selection for the BNO055 sensor.
 * 
 * This function sets the unit selection for the BNO055 sensor by updating the UNIT_SEL register based on the given unit value.
 * 
 * @param unitValue The unit value to be set. Values greater than 0x20 are used for setting units
 * while values less than or equal to 0x20 are used for clearing units.
 */
void BNO055::setUnit(uint8_t unitValue) {
    setPage(0x00);
    uint8_t tempValue = readByte(UNIT_SEL);
    if (unitValue>0x20)
        {
        tempValue = tempValue & unitValue;
        writeByte(UNIT_SEL, tempValue);
        }
    else
        {
        tempValue = tempValue & ~unitValue;
        writeByte(UNIT_SEL, tempValue | unitValue);
        }

}

/**
 * @brief Sets the accelerometer configuration for the BNO055 sensor.
 * 
 * This function sets the accelerometer configuration for the BNO055 sensor by updating the ACC_CONFIG register based on the provided accelerometer range, bandwidth, and operating mode.
 * 
 * @param accRange The accelerometer range to be set.
 * @param accBW The accelerometer bandwidth to be set.
 * @param accOPmode The accelerometer operating mode to be set.
 */
void BNO055::setAccConfig(AccRange accRange, AccBW accBW, AccOPMode accOPmode) {
    setPage(0x01);
    uint8_t tempValue = (readByte(ACC_CONFIG) & 0x00) | accRange << 5 | accBW << 2 | accOPmode;
    writeByte(ACC_CONFIG, tempValue);
}

/**
 * @brief Sets the gyroscope configuration for the BNO055 sensor.
 * 
 * This function sets the gyroscope configuration for the BNO055 sensor by updating the GYR_CONFIG_0 and GYR_CONFIG_1 registers based on the provided gyroscope range, bandwidth, and operating mode.
 * 
 * @param gyrRange The gyroscope range to be set.
 * @param gyrBW The gyroscope bandwidth to be set.
 * @param gyrOPmode The gyroscope operating mode to be set.
 */
void BNO055::setGyroConfig(GyrRange gyrRange, GyrBW gyrBW, GyrOPMode gyrOPmode) {
    setPage(0x01);
    uint8_t tempValue0 = (readByte(GYR_CONFIG_0) & 0x00) | gyrBW << 3 | gyrRange;
    writeByte(GYR_CONFIG_0, tempValue0);
    uint8_t tempValue1 = (readByte(GYR_CONFIG_1) & 0x00) | gyrOPmode;
    writeByte(GYR_CONFIG_1, tempValue1);
}

/**
 * @brief Sets the magnetometer configuration for the BNO055 sensor.
 * 
 * This function sets the magnetometer configuration for the BNO055 sensor by updating the MAG_CONFIG register based on the provided magnetometer rate, power mode, and operating mode.
 * 
 * @param rate The magnetometer rate to be set.
 * @param Pmode The magnetometer power mode to be set.
 * @param magOPmode The magnetometer operating mode to be set.
 */
void BNO055::setMagConfig(MagRate rate, MagPMode Pmode, MagOPMode magOPmode) {
    setPage(0x01);
    uint8_t tempValue = (readByte(MAG_CONFIG) & 0x00) | Pmode << 5 | magOPmode << 3 | rate;
    writeByte(MAG_CONFIG, tempValue);
}

/**
 * @brief Sets the accelerometer sleep configuration for the BNO055 sensor.
 * 
 * This function sets the accelerometer sleep configuration for the BNO055 sensor by updating the ACC_SLEEP_CONFIG register based on the provided duration and sleep mode.
 * 
 * @param duration The duration value for accelerometer sleep.
 * @param mode The sleep mode to be set (true for sleep mode enabled, false for sleep mode disabled).
 */
void BNO055::setAccSleepConfig(uint8_t duration, bool mode) {
    setPage(0x01);
    uint8_t tempValue = readByte(ACC_SLEEP_CONFIG);
    tempValue = (tempValue & 0xE0) | duration << 1 | mode;
    writeByte(ACC_SLEEP_CONFIG, tempValue);
}

/**
 * @brief Sets the gyroscope sleep configuration for the BNO055 sensor.
 * 
 * This function sets the gyroscope sleep configuration for the BNO055 sensor by updating the GYR_SLEEP_CONFIG register based on the provided auto sleep duration and sleep duration values.
 * 
 * @param autoSleepDuration The auto sleep duration value for gyroscope.
 * @param sleepDuration The sleep duration value for gyroscope.
 */
void BNO055::setGyrSleepConfig(uint8_t autoSleepDuration, uint8_t sleepDuration) {
    setPage(0x01);
    uint8_t tempValue = readByte(GYR_SLEEP_CONFIG);
    tempValue = (tempValue & 0xC0) | autoSleepDuration << 3 | sleepDuration;
    writeByte(GYR_SLEEP_CONFIG, tempValue);
}

/**
 * @brief Sets the accelerometer X-axis offset for the BNO055 sensor.
 * 
 * This function sets the accelerometer X-axis offset for the BNO055 sensor by writing the provided offset value to the ACC_OFFSET_X_LSB and ACC_OFFSET_X_MSB registers.
 * 
 * @param offset The offset value to be set for the X-axis accelerometer.
 */
void BNO055::accOffsetX(uint16_t offset) {
    setPage(0x00);
    writeByte(ACC_OFFSET_X_LSB, (uint8_t)(offset & 0x00FF));
    writeByte(ACC_OFFSET_X_MSB, (uint8_t)(offset >> 8));
}

/**
 * @brief Sets the accelerometer Y-axis offset for the BNO055 sensor.
 * 
 * This function sets the accelerometer Y-axis offset for the BNO055 sensor by writing the provided offset value to the ACC_OFFSET_Y_LSB and ACC_OFFSET_Y_MSB registers.
 * 
 * @param offset The offset value to be set for the Y-axis accelerometer.
 */
void BNO055::accOffsetY(uint16_t offset) {
    setPage(0x00);
    writeByte(ACC_OFFSET_Y_LSB, (uint8_t)(offset & 0x00FF));
    writeByte(ACC_OFFSET_Y_MSB, (uint8_t)(offset >> 8));
}

/**
 * @brief Sets the accelerometer Z-axis offset for the BNO055 sensor.
 * 
 * This function sets the accelerometer Z-axis offset for the BNO055 sensor by writing the provided offset value to the ACC_OFFSET_Z_LSB and ACC_OFFSET_Z_MSB registers.
 * 
 * @param offset The offset value to be set for the Z-axis accelerometer.
 */
void BNO055::accOffsetZ(uint16_t offset) {
    setPage(0x00);
    writeByte(ACC_OFFSET_Z_LSB, (uint8_t)(offset & 0x00FF));
    writeByte(ACC_OFFSET_Z_MSB, (uint8_t)(offset >> 8));
}

/**
 * @brief Sets the magnetometer X-axis offset for the BNO055 sensor.
 * 
 * This function sets the magnetometer X-axis offset for the BNO055 sensor by writing the provided offset value to the ACC_OFFSET_X_LSB and ACC_OFFSET_X_MSB registers.
 * 
 * @param offset The offset value to be set for the X-axis magnetometer.
 */
void BNO055::magOffsetX(uint16_t offset) {
    setPage(0x00);
    writeByte(MAG_OFFSET_X_LSB, (uint8_t)(offset & 0x00FF));
    writeByte(MAG_OFFSET_X_MSB, (uint8_t)(offset >> 8));
}

/**
 * @brief Sets the magnetometer Y-axis offset for the BNO055 sensor.
 * 
 * This function sets the magnetometer Y-axis offset for the BNO055 sensor by writing the provided offset value to the ACC_OFFSET_Y_LSB and ACC_OFFSET_Y_MSB registers.
 * 
 * @param offset The offset value to be set for the Y-axis magnetometer.
 */
void BNO055::magOffsetY(uint16_t offset) {
    setPage(0x00);
    writeByte(MAG_OFFSET_Y_LSB, (uint8_t)(offset & 0x00FF));
    writeByte(MAG_OFFSET_Y_MSB, (uint8_t)(offset >> 8));
}

/**
 * @brief Sets the magnetometer Z-axis offset for the BNO055 sensor.
 * 
 * This function sets the magnetometer Z-axis offset for the BNO055 sensor by writing the provided offset value to the ACC_OFFSET_Z_LSB and ACC_OFFSET_Z_MSB registers.
 * 
 * @param offset The offset value to be set for the Z-axis magnetometer.
 */
void BNO055::magOffsetZ(uint16_t offset) {
    setPage(0x00);
    writeByte(MAG_OFFSET_Z_LSB, (uint8_t)(offset & 0x00FF));
    writeByte(MAG_OFFSET_Z_MSB, (uint8_t)(offset >> 8));
}

/**
 * @brief Sets the gyroscope X-axis offset for the BNO055 sensor.
 * 
 * This function sets the gyroscope X-axis offset for the BNO055 sensor by writing the provided offset value to the ACC_OFFSET_X_LSB and ACC_OFFSET_X_MSB registers.
 * 
 * @param offset The offset value to be set for the X-axis gyroscope.
 */
void BNO055::gyrOffsetX(uint16_t offset) {
    setPage(0x00);
    writeByte(GYR_OFFSET_X_LSB, (uint8_t)(offset & 0x00FF));
    writeByte(GYR_OFFSET_X_MSB, (uint8_t)(offset >> 8));
}

/**
 * @brief Sets the gyroscope Y-axis offset for the BNO055 sensor.
 * 
 * This function sets the gyroscope Y-axis offset for the BNO055 sensor by writing the provided offset value to the ACC_OFFSET_Y_LSB and ACC_OFFSET_Y_MSB registers.
 * 
 * @param offset The offset value to be set for the Y-axis gyroscope.
 */
void BNO055::gyrOffsetY(uint16_t offset) {
    setPage(0x00);
    writeByte(GYR_OFFSET_Y_LSB, (uint8_t)(offset & 0x00FF));
    writeByte(GYR_OFFSET_Y_MSB, (uint8_t)(offset >> 8));
}

/**
 * @brief Sets the gyroscope Z-axis offset for the BNO055 sensor.
 * 
 * This function sets the gyroscope Z-axis offset for the BNO055 sensor by writing the provided offset value to the ACC_OFFSET_Z_LSB and ACC_OFFSET_Z_MSB registers.
 * 
 * @param offset The offset value to be set for the Z-axis gyroscope.
 */
void BNO055::gyrOffsetZ(uint16_t offset) {
    setPage(0x00);
    writeByte(GYR_OFFSET_Z_LSB, (uint8_t)(offset & 0x00FF));
    writeByte(GYR_OFFSET_Z_MSB, (uint8_t)(offset >> 8));
}

/**
 * @brief Gets the acceleration values in x, y, and z axes from the BNO055 sensor.
 * 
 * This function reads the raw acceleration values in x, y, and z axes from the BNO055 sensor, converts them to floating point values, and stores them in the provided variables.
 * 
 * @param x Reference to a float variable to store the acceleration value in the x-axis.
 * @param y Reference to a float variable to store the acceleration value in the y-axis.
 * @param z Reference to a float variable to store the acceleration value in the z-axis.
 */
void BNO055::getAcceleration(float& x, float& y, float& z) {
    setPage(0x00);
    int16_t rawX, rawY, rawZ;
    readBytes(ACC_X_LSB, (uint8_t*)&rawX, 2);
    readBytes(ACC_Y_LSB, (uint8_t*)&rawY, 2);
    readBytes(ACC_Z_LSB, (uint8_t*)&rawZ, 2);

    x = rawX / 100.0;
    y = rawY / 100.0;
    z = rawZ / 100.0;
}

/**
 * @brief Sets the axis remap configuration for the BNO055 sensor.
 * 
 * This function sets the axis remap configuration for the BNO055 sensor by updating the AXIS_MAP_CONFIG register with the provided remap configuration.
 * 
 * @param remapconfig The axis remap configuration value to be set.
 */
void BNO055::setAxisRemap(axisRemapConfig remapconfig) {
    setPage(0x00);
    OperationMode mode = getMode();

    setOperationMode(OPERATION_MODE_CONFIG);
    delay(25);
    writeByte(AXIS_MAP_CONFIG, remapconfig);
    delay(10);
    setOperationMode(mode);
    delay(20);
}

/**
 * @brief Sets the axis sign configuration for the BNO055 sensor.
 * 
 * This function sets the axis sign configuration for the BNO055 sensor by updating the AXIS_MAP_SIGN register with the provided sign configuration.
 * 
 * @param remapsign The axis sign configuration value to be set.
 */
void BNO055::setAxisSign(axisRemapSign remapsign) {
    setPage(0x00);
    OperationMode mode = getMode();

    setOperationMode(OPERATION_MODE_CONFIG);
    delay(25);
    writeByte(AXIS_MAP_SIGN, remapsign);
    delay(10);
    setOperationMode(mode);

    delay(20);
}

/**
 * @brief Gets the revision information of the BNO055 sensor.
 * 
 * This function reads the revision information of the BNO055 sensor including accelerometer, magnetometer, gyroscope, bootloader, and software revisions.
 * 
 * @param info Pointer to a revInfo struct to store the revision information.
 */
void BNO055::getrevInfo(revInfo *info) {
    setPage(0x00);
    uint8_t a, b;

    memset(info, 0, sizeof(revInfo));
    info->accel_rev = readByte(ACC_ID);
    info->mag_rev = readByte(MAG_ID);
    info->gyro_rev = readByte(GYRO_ID);
    info->bl_rev = readByte(BL_REV_ID);

    a = readByte(SW_REV_ID_LSB);
    b = readByte(SW_REV_ID_MSB);
    info->sw_rev = (((uint16_t)b) << 8) | ((uint16_t)a);
}

/**
 * @brief Gets the gravity values in x, y, and z axes from the BNO055 sensor.
 * 
 * This function reads the raw gravity values in x, y, and z axes from the BNO055 sensor, converts them to floating point values, and stores them in the provided variables.
 * 
 * @param x Reference to a float variable to store the gravity value in the x-axis.
 * @param y Reference to a float variable to store the gravity value in the y-axis.
 * @param z Reference to a float variable to store the gravity value in the z-axis.
 */
void BNO055::getGravity(float& x, float& y, float& z) {
    setPage(0x00);
    int16_t rawX, rawY, rawZ;
    readBytes(GRV_X_LSB, (uint8_t*)&rawX, 2);
    readBytes(GRV_Y_LSB, (uint8_t*)&rawY, 2);
    readBytes(GRV_Z_LSB, (uint8_t*)&rawZ, 2);

    x = rawX / 100.0;
    y = rawY / 100.0;
    z = rawZ / 100.0;
}

/**
 * @brief Gets the linear acceleration values in x, y, and z axes from the BNO055 sensor.
 * 
 * This function reads the raw linear acceleration values in x, y, and z axes from the BNO055 sensor, converts them to floating point values, and stores them in the provided variables.
 * 
 * @param x Reference to a float variable to store the linear acceleration value in the x-axis.
 * @param y Reference to a float variable to store the linear acceleration value in the y-axis.
 * @param z Reference to a float variable to store the linear acceleration value in the z-axis.
 */
void BNO055::getLinearAcceleration(float& x, float& y, float& z) {
    setPage(0x00);
    int16_t rawX, rawY, rawZ;
    readBytes(LIA_X_LSB, (uint8_t*)&rawX, 2);
    readBytes(LIA_Y_LSB, (uint8_t*)&rawY, 2);
    readBytes(LIA_Z_LSB, (uint8_t*)&rawZ, 2);

    x = rawX / 100.0;
    y = rawY / 100.0;
    z = rawZ / 100.0;
}

/**
 * @brief Gets the Euler angles (heading, roll, pitch) from the BNO055 sensor.
 * 
 * This function reads the raw Euler angles (heading, roll, pitch) from the BNO055 sensor, converts them to floating point values, and stores them in the provided variables.
 * 
 * @param heading Reference to a float variable to store the heading angle.
 * @param roll Reference to a float variable to store the roll angle.
 * @param pitch Reference to a float variable to store the pitch angle.
 */
void BNO055::getEulerAngles(float& heading, float& roll, float& pitch) {
    setPage(0x00);
    int16_t rawHeading, rawRoll, rawPitch;
    readBytes(EUL_X_LSB, (uint8_t*)&rawHeading, 2);
    readBytes(EUL_Y_LSB, (uint8_t*)&rawRoll, 2);
    readBytes(EUL_Z_LSB, (uint8_t*)&rawPitch, 2);

    heading = rawHeading / 16.0;
    roll = rawRoll / 16.0;
    pitch = rawPitch / 16.0;
}

/**
 * @brief Gets the quaternion values (w, x, y, z) from the BNO055 sensor.
 * 
 * This function reads the raw quaternion values (w, x, y, z) from the BNO055 sensor, converts them to floating point values, and stores them in the provided variables.
 * 
 * @param w Reference to a float variable to store the w value of the quaternion.
 * @param x Reference to a float variable to store the x value of the quaternion.
 * @param y Reference to a float variable to store the y value of the quaternion.
 * @param z Reference to a float variable to store the z value of the quaternion.
 */
void BNO055::getQuaternions(float& w, float& x, float& y, float& z) {
    setPage(0x00);
    int16_t rawW, rawX, rawY, rawZ;
    readBytes(QUA_W_LSB, (uint8_t*)&rawW, 2);
    readBytes(QUA_X_LSB, (uint8_t*)&rawX, 2);
    readBytes(QUA_Y_LSB, (uint8_t*)&rawY, 2);
    readBytes(QUA_Z_LSB, (uint8_t*)&rawZ, 2);

    w = rawW / 16384.0;
    x = rawX / 16384.0;
    y = rawY / 16384.0;
    z = rawZ / 16384.0;
}

/**
 * @brief Gets the calibration status of the BNO055 sensor for different sensor components.
 * 
 * This function reads the calibration status byte from the BNO055 sensor and extracts the calibration status for system, gyro, accelerometer, and magnetometer components. It then stores the calibration status values in the provided variables.
 * 
 * @param sys Reference to a uint8_t variable to store the calibration status of the system.
 * @param gyro Reference to a uint8_t variable to store the calibration status of the gyro.
 * @param accel Reference to a uint8_t variable to store the calibration status of the accelerometer.
 * @param mag Reference to a uint8_t variable to store the calibration status of the magnetometer.
 */
void BNO055::getCalibrationStatus(uint8_t& sys, uint8_t& gyro, uint8_t& accel, uint8_t& mag) {
    setPage(0x00);
    uint8_t calStatus = readByte(CALIB_STAT);
    if(sys != NULL) {
        sys = (calStatus >> 6) & 0x03;
    }
    if(gyro != NULL) {
        gyro = (calStatus >> 4) & 0x03;
    }
    if(accel != NULL) {
        accel = (calStatus >> 2) & 0x03;
    }
    if(mag != NULL) {
        mag = calStatus & 0x03;
    }
}

/**
 * @brief Gets the magnetometer data (x, y, z) from the BNO055 sensor.
 * 
 * This function reads the raw magnetometer data (x, y, z) from the BNO055 sensor, converts them to floating point values, and stores them in the provided variables.
 * 
 * @param x Reference to a float variable to store the magnetometer data along the x-axis.
 * @param y Reference to a float variable to store the magnetometer data along the y-axis.
 * @param z Reference to a float variable to store the magnetometer data along the z-axis.
 */
void BNO055::getMagnetometer(float& x, float& y, float& z) {
    setPage(0x00);
    int16_t rawX, rawY, rawZ;
    readBytes(MAG_X_LSB, (uint8_t*)&rawX, 2);
    readBytes(MAG_Y_LSB, (uint8_t*)&rawY, 2);
    readBytes(MAG_Z_LSB, (uint8_t*)&rawZ, 2);

    x = rawX / 16.0;
    y = rawY / 16.0;
    z = rawZ / 16.0;
}

/**
 * @brief Gets the gyroscope data (x, y, z) from the BNO055 sensor.
 * 
 * This function reads the raw gyroscope data (x, y, z) from the BNO055 sensor, converts them to floating point values, and stores them in the provided variables.
 * 
 * @param x Reference to a float variable to store the gyroscope data along the x-axis.
 * @param y Reference to a float variable to store the gyroscope data along the y-axis.
 * @param z Reference to a float variable to store the gyroscope data along the z-axis.
 */
void BNO055::getGyroscope(float& x, float& y, float& z) {
    setPage(0x00);
    int16_t rawX, rawY, rawZ;
    readBytes(GYR_X_LSB, (uint8_t*)&rawX, 2);
    readBytes(GYR_Y_LSB, (uint8_t*)&rawY, 2);
    readBytes(GYR_Z_LSB, (uint8_t*)&rawZ, 2);
    
    x = rawX / 900.0;
    y = rawY / 900.0;
    z = rawZ / 900.0;
}

/**
 * @brief Gets the temperature data from the BNO055 sensor.
 * 
 * This function reads the raw temperature data from the BNO055 sensor, converts it to a floating point value representing the temperature in degrees Celsius, and stores it in the provided variable.
 * 
 * @param temperature Reference to a float variable to store the temperature data in degrees Celsius.
 */
void BNO055::getTemperature(float& temperature) {
    setPage(0x00);
    int8_t rawTemperature, tempTemperature;
    readBytes(TEMP, (uint8_t*)&rawTemperature, 1);

    temperature = rawTemperature;
}

/**
 * @brief Gets the accuracy values for each quaternion component from the BNO055 sensor.
 * 
 * This function reads the raw accuracy byte from the BNO055 sensor and extracts the accuracy values for each quaternion component (w, x, y, z). It then stores the accuracy values in the provided variables as floating point values.
 * 
 * @param w Reference to a float variable to store the accuracy value for the w component of the quaternion.
 * @param x Reference to a float variable to store the accuracy value for the x component of the quaternion.
 * @param y Reference to a float variable to store the accuracy value for the y component of the quaternion.
 * @param z Reference to a float variable to store the accuracy value for the z component of the quaternion.
 */
void BNO055::getQuaternionAccuracy(float& w, float& x, float& y, float& z) {
    setPage(0x00);
    uint8_t rawAccuracy;
    readBytes(0x3A, &rawAccuracy, 1);

    w = (rawAccuracy >> 6) & 0x03;
    x = (rawAccuracy >> 4) & 0x03;
    y = (rawAccuracy >> 2) & 0x03;
    z = rawAccuracy & 0x03;
}

/**
 * @brief Gets the angular velocity data (x, y, z) from the BNO055 sensor.
 * 
 * This function reads the raw angular velocity data (x, y, z) from the BNO055 sensor, converts them to floating point values, and stores them in the provided variables.
 * 
 * @param x Reference to a float variable to store the angular velocity data along the x-axis.
 * @param y Reference to a float variable to store the angular velocity data along the y-axis.
 * @param z Reference to a float variable to store the angular velocity data along the z-axis.
 */
void BNO055::getAngularVelocity(float& x, float& y, float& z) {
    setPage(0x00);
    int16_t rawX, rawY, rawZ;
    readBytes(GYR_X_LSB, (uint8_t*)&rawX, 2); // Angular velocity değerleri datasheet üzerinde yazana göre 
    readBytes(GYR_Y_LSB, (uint8_t*)&rawY, 2); // GYR_X/Y/Z_LSB registerlarından okunabiliyor.
    readBytes(GYR_Z_LSB, (uint8_t*)&rawZ, 2);

    x = rawX / 16.0;
    y = rawY / 16.0;
    z = rawZ / 16.0;
}

/**
 * @brief Gets the system status, self-test results, and system errors from the BNO055 sensor.
 * 
 * This function reads the system status, self-test results, and system errors from the BNO055 sensor and stores them in the provided variables.
 * 
 * @param system_status Pointer to a uint8_t variable to store the system status.
 * @param self_test_result Pointer to a uint8_t variable to store the self-test results.
 * @param system_error Pointer to a uint8_t variable to store the system errors.
 */
void BNO055::getSystemStatus(uint8_t *system_status, uint8_t *self_test_result, uint8_t *system_error) {
    writeByte(PAGE_ID, 0x00);
      /* System Status
     0 = Idle
     1 = System Error
     2 = Initializing Peripherals
     3 = System Iniitalization
     4 = Executing Self-Test
     5 = Sensor fusio algorithm running
     6 = System running without fusion algorithms
   */
    if(system_status != 0) {
        *system_status = readByte(SYS_STATUS);
    }
      /* Self Test Results
     1 = test passed, 0 = test failed

     Bit 0 = Accelerometer self test
     Bit 1 = Magnetometer self test
     Bit 2 = Gyroscope self test
     Bit 3 = MCU self test

     0x0F = all good!
   */
    if(self_test_result != 0) {
        *self_test_result = readByte(SELFTEST_RESULT);
    }
      /* System Error (see section 4.3.59)
     0 = No error
     1 = Peripheral initialization error
     2 = System initialization error
     3 = Self test result failed
     4 = Register map value out of range
     5 = Register map address out of range
     6 = Register map write error
     7 = BNO low power mode not available for selected operat ion mode
     8 = Accelerometer power mode not available
     9 = Fusion algorithm configuration error
     A = Sensor configuration error
   */
    if(system_error != 0) {
        *system_error = readByte(SYS_ERR);
    }
    delay(200);
}

/**
 * @brief Checks if the BNO055 sensor is fully calibrated based on the current operation mode.
 * 
 * This function checks if the BNO055 sensor is fully calibrated based on the current operation mode. It reads the calibration status of the system, gyroscope, accelerometer, and magnetometer and compares them with the required calibration values for the specific operation mode.
 * 
 * @return True if the sensor is fully calibrated for the current operation mode, false otherwise.
 */
bool BNO055::isFullyCalibrated() {
    setPage(0x00);
    uint8_t sys, gyro, accel, mag;
    getCalibrationStatus(sys, gyro, accel, mag);

    switch(mode) {
    case OPERATION_MODE_ACCONLY:
        return(accel == 3);
    case OPERATION_MODE_MAGONLY:
        return(mag == 3);
    case OPERATION_MODE_GYRONLY:
    case OPERATION_MODE_M4G:
        return(gyro == 3);
    case OPERATION_MODE_ACCMAG:
    case OPERATION_MODE_COMPASS:
        return(accel == 3 && mag == 3);
    case OPERATION_MODE_ACCGYRO:
    case OPERATION_MODE_IMUPLUS:
        return(accel == 3 && gyro == 3);
    case OPERATION_MODE_MAGGYRO:
        return(mag == 3 && gyro == 3);
    default:
        return(sys == 3 && gyro == 3 && accel == 3 && mag == 3);
    }
}

/**
 * @brief Writes a byte of data to a register in the BNO055 sensor.
 * 
 * This function starts a transmission with the BNO055 sensor, writes a byte of data to the specified register, and checks if the transmission was successful.
 * 
 * @param reg The register address to write the data to.
 * @param value The byte of data to write to the register.
 * @return True if the data was successfully written to the register, false otherwise.
 */
bool BNO055::writeByte(uint8_t reg, uint8_t value) {
    #ifdef I2C
    Wire.beginTransmission(address);
    Wire.write(reg);
    Wire.write(value);
    return Wire.endTransmission() == 0;
    #endif

    #ifdef UART
    uint8_t buffer[5];
    buffer[0] = 0xAA;
    buffer[1] = 0x00;
    buffer[2] = reg;
    buffer[3] = 0x01;
    buffer[4] = value;
    for (int i = 0; i < 5; i++) {
    mySerial.write(buffer[i]);
    }

    uint8_t response = mySerial.read();
    if (response == 0xEE) {
        Serial.println("Yazma işlemi başarili.");
    } else {
        Serial.print("Beklenmeyen yanit: 0x");
        Serial.println(response, HEX);  // Beklenmeyen yanıtı ekrana yazdır
    }

    return 1;
    #endif
}

/**
 * @brief Reads a byte of data from a register in the BNO055 sensor.
 * 
 * This function starts a transmission with the BNO055 sensor, requests a byte of data from the specified register, and returns the read data.
 * 
 * @param reg The register address to read the data from.
 * @return The byte of data read from the register.
 */
uint8_t BNO055::readByte(uint8_t reg) {
    #ifdef I2C
    uint8_t value = 0;

    Wire.beginTransmission(address);
    Wire.write(reg);
    Wire.endTransmission();

    Wire.requestFrom(address, 1);
    if(Wire.available()) {
        value = Wire.read();
    }

    return value;
    #endif

    #ifdef UART
    uint8_t buffer[4];
    uint8_t response = 0;
    uint8_t count = 0;
    uint8_t value = 0; 

    buffer[0] = 0xAA;
    buffer[1] = 0x01;
    buffer[2] = 0x02;
    buffer[3] = 0x01;

    for (int i = 0; i < 4; i++) {
        mySerial.write(buffer[i]);
    }

    unsigned long startMillis = millis();
    while (mySerial.available() < 1) {
        if (millis() - startMillis > 1000) {
        Serial.println("Response cannot received.");
        return 0;
        }
    }

    response=mySerial.read();
    if (response==0xBB);
        {
        count=mySerial.read();
        for(int i = 0; i < count; i++){ 
            value = mySerial.read(); 
        }

        }
    if (response==0xEE)
        {
        Serial.print(mySerial.read(), HEX);    
        }  
    return value;
    #endif
}

uint8_t rx_buffer[255];

/**
 * @brief Reads multiple bytes of data from consecutive registers in the BNO055 sensor.
 * 
 * This function starts a transmission with the BNO055 sensor, requests multiple bytes of data starting from the specified register, and stores the read data in the provided buffer.
 * 
 * @param reg The starting register address to read the data from.
 * @param buffer Pointer to a uint8_t array to store the read data.
 * @param length The number of bytes to read from consecutive registers.
 * @return True if the data was successfully read and stored in the buffer, false otherwise.
 */
void BNO055::readBytes(uint8_t reg, uint8_t* buffer, uint8_t length) {
    #ifdef I2C
    Wire.beginTransmission(address);
    Wire.write(reg);
    Wire.endTransmission();

    Wire.requestFrom(address, length);
    for (uint8_t i = 0; i < length; i++)
    {
        if(Wire.available()) {
            buffer[i] = Wire.read();
        }
    }
    #endif

    #ifdef UART
    uint8_t array[4];
    uint8_t response = 0;
    uint8_t count = 0;

    array[0] = 0xAA;
    array[1] = 0x01;
    array[2] = reg;
    array[3] = length;

    for (int i = 0; i < 4; i++) {
        mySerial.write(array[i]);
    }

    unsigned long startMillis = millis();
    while (mySerial.available() < length) {
        if (millis() - startMillis > 1000) {
        Serial.println("Response cannot received.");
        }
    }

    response = mySerial.read();
    if (response == 0xBB);
        {
        count = mySerial.read();
        for(int i = 0; i < count ; i++){
            buffer[i]=mySerial.read();
        }

        }
    if (response == 0xEE)
        {
        Serial.print(mySerial.read(), HEX);    
        }  
    #endif
}

bool BNO055::writeByteUART(uint8_t reg, uint8_t value) {
    Serial.write(0xAA);
    Serial.write(0x00);
    Serial.write(reg);
    Serial.write(0x01);
    Serial.write(value);
 
    Serial.flush();
    return value;
}

uint8_t BNO055::readByteUART(uint8_t reg) {
    Serial.write(0xAA);
    Serial.write(0x01);
    Serial.write(reg);
    Serial.write(0x01);
    Serial.write(0xBB);
    Serial.write(0x01);
    uint8_t data = Serial.read();
    return data;
}