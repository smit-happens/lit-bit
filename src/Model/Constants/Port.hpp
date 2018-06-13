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


/*
     _    ______  ___
    / \  |  _ \ \/ / |
   / _ \ | | | \  /| |
  / ___ \| |_| /  \| |___
 /_/   \_\____/_/\_\_____|

*/
const uint8_t LB_ADXL_INT1        = 1;
// const uint8_t LB_ADXL_INT2        = NAN;


/*
  ____ _____ ____
 |  _ \_   _/ ___|
 | |_) || || |
 |  _ < | || |___
 |_| \_\|_| \____|

*/
const uint8_t LB_RTC_MFP          = 0;


/*
  ____  _     _____
 | __ )| |   | ____|
 |  _ \| |   |  _|
 | |_) | |___| |___
 |____/|_____|_____|

*/
const uint8_t LB_BLE_RDY          = 7;
const uint8_t LB_BLE_REQ          = 9;
const uint8_t LB_BLE_ACT          = 11;
const uint8_t LB_BLE_RST          = 12;


/*
   ___  _     _____ ____
  / _ \| |   | ____|  _ \
 | | | | |   |  _| | | | |
 | |_| | |___| |___| |_| |
  \___/|_____|_____|____/
*/
//Data lines
// SID:     Serial data out
// SCLK:    Serial clock out
// RS/A0:   Data/Command select
// _RST:    LCD reset
// _CS:     LCD chip select
// const uint8_t LB_OLED_SID          = 8;   //ST7565 display Output
// const uint8_t LB_OLED_SCLK         = 9;   //ST7565 display Output
// const uint8_t LB_OLED_A0           = 10;  //ST7565 display Output
// const uint8_t LB_OLED_RST          = 11;  //ST7565 display Output
// const uint8_t LB_OLED_CS           = 12;  //ST7565 display Output


#endif  //PORTCONSTANTS_HPP
