/** Generic constant to be used across all models and constant
 * 
 * Created 05/24/18 By: Smitty
 * 
 */

#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <Arduino.h>


//The OLED library assumes a reset pin is necessary. The Qwiic OLED has RST hard-wired, so pick an arbitrarty IO pin that is not being used
#define PIN_RESET 9  
//The OLED DC_JUMPER is the I2C Address Select jumper. Set to 1 if the jumper is open (Default), or set to 0 if it's closed.
#define DC_JUMPER 1 


//number of timers in use
const int TIMER_NUM     = 1;

//polling delays
const int POLL_TIME_OLED    = 300;


//General Event Flags for devices
const uint8_t EF_TIMER             = 0b1;   //The first event flag (EF) mask
const uint8_t EF_SHUTDOWN          = 0b10;  //Shutdown EF mask
const uint8_t EF_ADXL              = 0b100;  //accelerometer EF mask
const uint8_t EF_RTC               = 0b1000;  //RTC EF mask
const uint8_t EF_EEPROM            = 0b10000;  //EEPROM EF mask
const uint8_t EF_OLED              = 0b100000;  //OLED EF mask


//task flags for eeprom
const uint8_t TF_EEPROM_15MIN_SAVE      = 0b1;  //saving step entry TF

//OLED TFs
const uint8_t TF_OLED_STEP              = 0b1; //displaying steps
const uint8_t TF_OLED_TIMEOUT           = 0b10; //sleeping display


//this enum is used as an index in the lookup table
//specifies each device for the lit bit
enum Device
{
    DEVICE_ADXL,
    DEVICE_RTC,
    DEVICE_EEPROM,
    DEVICE_OLED,
    DEVICE_NUM //The number of devices, MAINTAIN AT END OF ENUM
};


#endif  //CONSTANTS_HPP