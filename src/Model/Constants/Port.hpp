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
  ____         __      _                      _                   _
 / ___|  __ _ / _| ___| |_ _   _    ___ _   _| |__  ___ _   _ ___| |_ ___ _ __ ___  ___
 \___ \ / _` | |_ / _ \ __| | | |  / __| | | | '_ \/ __| | | / __| __/ _ \ '_ ` _ \/ __|
  ___) | (_| |  _|  __/ |_| |_| |  \__ \ |_| | |_) \__ \ |_| \__ \ ||  __/ | | | | \__ \
 |____/ \__,_|_|  \___|\__|\__, |  |___/\__,_|_.__/|___/\__, |___/\__\___|_| |_| |_|___/
                           |___/                        |___/
*/
const uint8_t LB_IMD_STATUS        = 28;   //[0,1] Digital Input
const uint8_t LB_BMS_STATUS        = 29;   //[0,1] Digital Input


/*
  ___ ____   ____
 |_ _|___ \ / ___|
  | |  __) | |
  | | / __/| |___
 |___|_____|\____|

*/
const uint8_t LB_I2C_SCL           = 57;  //Expansion port
const uint8_t LB_I2C_SDA           = 56;  //maybe Traction control


/*
  ____  ____ ___ 
 / ___||  _ \_ _|
 \___ \| |_) | | 
  ___) |  __/| | 
 |____/|_|  |___|
                 
*/
const uint8_t LB_SPI_CS1           = 43;  //To be determined
const uint8_t LB_SPI_CS0           = 54;  //To be determined
const uint8_t LB_SPI_SCK           = 53;  //
const uint8_t LB_SPI_MOSI          = 52;  //
const uint8_t LB_SPI_MISO          = 51;  //


/*
   ____ _     ____ ____
  / ___| |   / ___|  _ \    ___  ___ _ __ ___  ___ _ __
 | |  _| |  | |   | | | |  / __|/ __| '__/ _ \/ _ \ '_ \
 | |_| | |__| |___| |_| |  \__ \ (__| | |  __/  __/ | | |
  \____|_____\____|____/   |___/\___|_|  \___|\___|_| |_|

*/
//Data lines
// SID:     Serial data out
// SCLK:    Serial clock out
// RS/A0:   Data/Command select
// _RST:    LCD reset
// _CS:     LCD chip select
const uint8_t LB_SID               = 8;   //ST7565 display Output
const uint8_t LB_SCLK              = 9;   //ST7565 display Output
const uint8_t LB_A0                = 10;  //ST7565 display Output
const uint8_t LB_RST               = 11;  //ST7565 display Output
const uint8_t LB_CS                = 12;  //ST7565 display Output

//RGB backlight
const uint8_t LB_R                 = 7;   //[0,1] PWM Output
const uint8_t LB_G                 = 6;   //[0,1] PWM Output
const uint8_t LB_B                 = 4;   //[0,1] PWM Output


#endif  //PORTCONSTANTS_HPP
