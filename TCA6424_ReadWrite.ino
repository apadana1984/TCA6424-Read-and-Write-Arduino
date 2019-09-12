/******** TCA6424 on Texas Instrument's IO Expander Board *********/
/*
 * Author: Iman Khademi 2019
 * MIT License
 * 
 * This is a demo for TCA6424 I2C port expander. The IC is on a Texas Instrument IO Expander EVM.
 * This sketch does not use the INT signal. Check the repository for other sketches with the interrupt signal.
 * Instead of reading the interrupt signal, it reads the input ports P00 and P01 (Two push buttons) every millisecond and maps them
 * directly to the LED ports (P02 and P03)
 */

#include <Wire.h>
#include "TCA6424A.h"

#define TCA6424_I2C_ADDR  0x22 // default I2C address

void setup() {

  Wire.begin();// Connect my Arduino to the I2C bus as master
  
  /* setup input-outputs here */
  // WRITE SEQUENCE (See page 20 of the datasheet for TCA2464)
  // 1: Send the Slave Address (I2C Address of the IO Expansion Board)
  Wire.beginTransmission(TCA6424_I2C_ADDR);
  // 2: Send the Command Byte
  Wire.write(CONFIG_P0); // choosing P0 configuration register to write to
  // 3: Send the Data
  Wire.write(0xF3); // Set Pin 2 and 3 as output ports (set to zero), and Pins 1-2 and 4-7 as input ports (set to one)
  // Execute the Sequence
  Wire.endTransmission();
   /******** FINISHED WRITE SEQUENCE **********/
}

void loop() {

  // We read the push buttons to control the LEDs on TI IO Expander EVM

  // READ SEQUENCE (See page 21 of the datasheet for TCA2464)
  // 1: Send the Slave Address (I2C Address of the IO Expansion Board)
  Wire.beginTransmission(TCA6424_I2C_ADDR);
  // 2: Send the Command Byte
  Wire.write(INPUT_P0); // choosing Input P0 register to read from
  // 3: Send the Slave Address (I2C Address of the IO Expansion Board)
  Wire.requestFrom(TCA6424_I2C_ADDR,1);
  // 4: Read the Register
  unsigned int c = Wire.read(); // Set Pin 2 and 3 as output ports (set to zero), and Pins 0-1 and 4-7 as input ports (set to one)
  // Execute the Sequence
  Wire.endTransmission();
  /* Display on the serial port */

  // CONTROL THE LEDs via I2C
  // WRITE SEQUENCE (See page 20 of the datasheet for TCA2464)
  // 1: Send the Slave Address (I2C Address of the IO Expansion Board)
  Wire.beginTransmission(TCA6424_I2C_ADDR);
  // 2: Send the Command Byte
  Wire.write(OUTPUT_P0); // choosing P0 configuration register to write to
  // 3: Send the Data
  Wire.write((byte)((c&0x03)<<2)); // Change the LED status based on the push buttons value
  // Execute the Sequence
  Wire.endTransmission();
  delay(1);
}
