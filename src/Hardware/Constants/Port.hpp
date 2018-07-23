/**  Correlate port name with the pin number on the Teensy 3.6
 *
 * #include Port.hpp
 * Created 05-24-18 By: Smitty
 * 
 * TODO: update this description
 * The port names correlate to the names given to them in the
 * original Main Brain schematic document
 * 
 * NOTE: The prefix "LB_" stands for "Lit Bit" so there's no conflicts
 *       with any libraries using the same nomenclature for pin definitions
 */

#ifndef PORT_HPP
#define PORT_HPP

#include <Arduino.h>


/*
  ___ ____   ____
 |_ _|___ \ / ___|
  | |  __) | |
  | | / __/| |___
 |___|_____|\____|

*/
const uint8_t LB_I2C_SCL          = 3;  //Expansion port
const uint8_t LB_I2C_SDA          = 2;  //maybe Traction control


/*
  ____  ____ ___ 
 / ___||  _ \_ _|
 \___ \| |_) | | 
  ___) |  __/| | 
 |____/|_|  |___|
                 
*/
const uint8_t LB_SPI_CS0          = 9;  //To be determined
const uint8_t LB_SPI_SCK          = SCK;  //
const uint8_t LB_SPI_MOSI         = MOSI;  //
const uint8_t LB_SPI_MISO         = MISO;  //


// /*
//      _    ______  ___
//     / \  |  _ \ \/ / |
//    / _ \ | | | \  /| |
//   / ___ \| |_| /  \| |___
//  /_/   \_\____/_/\_\_____|

// */
// const uint8_t LB_ADXL_INT1        = 1;
// // const uint8_t LB_ADXL_INT2        = NAN;


// /*
//   ____ _____ ____
//  |  _ \_   _/ ___|
//  | |_) || || |
//  |  _ < | || |___
//  |_| \_\|_| \____|

// */
// const uint8_t LB_RTC_MFP          = 0;


// /*
//   ____  _     _____
//  | __ )| |   | ____|
//  |  _ \| |   |  _|
//  | |_) | |___| |___
//  |____/|_____|_____|

// */
// const uint8_t LB_BLE_RDY          = 7;
// const uint8_t LB_BLE_REQ          = 9;
// const uint8_t LB_BLE_ACT          = 11;
// const uint8_t LB_BLE_RST          = 12;


/** 
 * Accelerometer
 */
const uint8_t LB_ADXL_INT1 = 10;     // uP pin 30, Arduino/ItsyBitsy pin D10
const uint8_t LB_ADXL_INT2 = 9;      // uP pin 29, Arduino/ItsyBitsy pin D9

/** 
 * Bluetooth
 */
const uint8_t LB_BLE_ACT = 11;      // uP pin 12, Arduino/ItsyBitsy pin D11
const uint8_t LB_BLE_REQ = 7;         // uP pin 1, Arduino/ItsyBitsy pin D7
const uint8_t LB_BLE_RDY = 0;         // uP pin 20, Arduino/ItsyBitsy pin D0
//FIXME: commented code should work for PCB, below is for breadboard...
// const uint8_t LB_BLE_RST = 5;
const uint8_t LB_BLE_RST = RXLED0;     // uP pin 8, Arduino/ItsyBitsy pin "RXLED"

// EEPROM (NONE)

/** 
 * RTC
 */
const uint8_t LB_RTC_MFP = 1;          // uP pin 21, Arduino/ItsyBitsy pin D1


#endif  //PORTCONSTANTS_HPP
