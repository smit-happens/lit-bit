/**  Flags that represent various functions of the car's operation
 *
 * #include "Flags.hpp"
 * Created 05-24-18  By: Smitty
 *
 * A longer description.
 */

#ifndef FLAGS_HPP
#define FLAGS_HPP

#include <Arduino.h>


//General Event Flags for devices
const uint8_t EF_TIMER             = 0b1;   //The first event flag (EF) mask
const uint8_t EF_SHUTDOWN          = 0b10;  //Shutdown EF mask
const uint8_t EF_ADXL              = 0b100;  //accelerometer EF mask
const uint8_t EF_RTC               = 0b1000;  //RTC EF mask
const uint8_t EF_BLE               = 0b10000;  //Bluetooth EF mask

//Timer flags (the equivalent of an event flag but triggered by a timer)
const uint8_t TIMER_F_OLED         = 0b1;  //OLED Timer mask
const uint8_t TIMER_F_EEPROM       = 0b10;  //EEPROM Timer mask

//this enum is used as an index in the lookup table
//specifies each device for the lit bit
enum DeviceName
{
    ADXL,
    RTC,
    EEPROM,
    BLE,
    OLED,
    NUM_DEVICES //The number of devices, MAINTAIN AT END OF ENUM
};s

#endif //FLAGS_HPP