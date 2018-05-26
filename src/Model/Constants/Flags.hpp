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
const uint32_t EF_TIMER             = 0b1;   //The first event flag (EF) mask
const uint32_t EF_SHUTDOWN          = 0b10;  //Shutdown EF mask
const uint32_t EF_COOLING           = 0b100;  //cooling EF mask
const uint32_t EF_DASH              = 0b1000;  //dash EF mask
const uint32_t EF_CAN               = 0b10000;  //CAN EF mask

//Timer flags (the equivalent of an event flag but triggered by a timer)
const uint32_t TIMER_F_GLCD         = 0b1 << 16;  //Glcd Timer mask
const uint32_t TIMER_F_SDCARD       = 0b10 << 16;  //SdCard Timer mask
const uint32_t TIMER_F_PEDAL        = 0b100 << 16;  //Pedal Timer mask

//this enum is used as an index in the lookup table and specifies each device for the car
enum DeviceName
{
    CAN,
    OLED,
    EEPROM,
    NUM_DEVICES //The number of devices, MAINTAIN AT END OF ENUM
};

#endif //FLAGS_HPP