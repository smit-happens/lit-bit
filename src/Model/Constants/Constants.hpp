/** Generic constant to be used across all models and constant
 * 
 * Created 05/24/18 By: Smitty
 * 
 */

#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

//Max analog read value
// const int MAX_ANALOGREAD = 8195;    //(2^13)-1
// const int MAX_BACKLIGHT_BR = 65535;

//The OLED library assumes a reset pin is necessary. The Qwiic OLED has RST hard-wired, so pick an arbitrarty IO pin that is not being used
#define PIN_RESET 9  
//The OLED DC_JUMPER is the I2C Address Select jumper. Set to 1 if the jumper is open (Default), or set to 0 if it's closed.
#define DC_JUMPER 1 

//types of log statements we can use
enum I2cDevices{
    DEVICE_ADXL,
    DEVICE_RTC,
    DEVICE_EEPROM,
    DEVICE_OLED
};


enum Stage
{
    STAGE_BOOTTEST,
    STAGE_STANDBY,
    STAGE_SHUTDOWN
};



#endif  //CONSTANTS_HPP