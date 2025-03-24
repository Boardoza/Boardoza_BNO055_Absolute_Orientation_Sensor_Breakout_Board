#include "BNO055.h"

BNO055 bnoSensor;

void setup() {
  Serial.begin(115200);
  
  if(!bnoSensor.begin()) {
    Serial.println("BNO055 cannot initialized!");
    while(1);
  }
 
  bnoSensor.accAMThresh(0x10);
  bnoSensor.accNMThresh(0x20);
  bnoSensor.accNMSet(0x03, 0x01);
  bnoSensor.accIntSettings(0x00, 0x07, 0x01);
  bnoSensor.interruptMask(ACC_NM);
  bnoSensor.interruptEnable(ACC_NM);
  bnoSensor.setOperationMode(OPERATION_MODE_AMG);
}

void loop() {  
  float x, y, z, w;
   uint8_t system, gyro, accel, mag = 0;
   uint8_t sys_stat, selftest_stat, sys_error;
  bnoSensor.getAcceleration(x, y, z);
  bnoSensor.setPage(0x01);
  /*Serial.print(bnoSensor.readByte(INT_EN));
  Serial.print("  ");
  Serial.print(bnoSensor.readByte(ACC_INT_SETTINGS));
  Serial.print("  ");
  bnoSensor.setPage(0x00);
  Serial.print(bnoSensor.readByte(INT_STA));
  Serial.print("  ");
  bnoSensor.setPage(0x01);
  Serial.print(bnoSensor.readByte(INT_MSK));
  Serial.print("  ");*/
  //bnoSensor.getEulerAngles(x, y, z);

  //bnoSensor.getSystemStatus(&sys_stat, &selftest_stat, &sys_error);


  Serial.print(x);
  Serial.print("  ");
  Serial.print(y);
  Serial.print("  ");
  Serial.print(z);
  Serial.print("  ");
  /*Serial.print(sys_stat);
  Serial.print("  ");
  Serial.print(selftest_stat);
  Serial.print("  ");
  Serial.print(sys_error);
  Serial.print("  ");*/
  Serial.println("");
  
  
  delay(100); // 1 second delay
}