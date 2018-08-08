/**  Manages the event handling functions in the superloop
 *
 * #include "StageManager.hpp"
 * Created 05-24-18 By: Smitty
 *
 * A longer description.
 */

#ifndef STAGEMANAGER_HPP
#define STAGEMANAGER_HPP

#include "../Hardware/Hardware.hpp"
#include "../Hardware/Constants/Constants.hpp"
#include <avr/wdt.h>


class StageManager
{
public:
    StageManager() { };

    //handles the excecution of the various stages
    void processStage(uint8_t* eventFlags, uint8_t* taskFlags);


private:
    uint16_t totalCount = 0;

    uint16_t stepCount = 0;
    bool upSwing = false;
    bool downSwing = false;

    //local controller initialization
    I2c* i2c          = I2c::getInstance();
    Eeprom* eeprom    = Eeprom::getInstance();
    Rtc* rtc          = Rtc::getInstance();
    Adxl* adxl        = Adxl::getInstance();
    Oled* oled        = Oled::getInstance();


    //Processing functions for the various devices
    void processAdxl(uint8_t* eventFlags, uint8_t* taskFlags);
    void processRtc(uint8_t* eventFlags, uint8_t* taskFlags);
    void processEeprom(uint8_t* taskFlags);
    void processOled(uint8_t* taskFlags);

};


#endif  //STAGEMANAGER_HPP
