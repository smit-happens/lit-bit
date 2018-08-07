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


class StageManager
{
public:
    StageManager();

    //handles the various timers we'll be using and setting Task Flags (TFs) based on them
    uint8_t processTimers(void);

    void shutdown();

    //handles the excecution of the various stages
    void processStage(uint16_t* eventFlags, uint8_t* taskFlags);


private:
    struct Timer {
        /* add name string field */
        int count;
        int limit;
        uint8_t TFmask;
    };
     
    Timer* timerList;
    uint8_t timerTF = 0;

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
    void processAdxl(uint16_t* eventFlags, uint8_t* taskFlags);
    void processRtc(uint16_t* eventFlags, uint8_t* taskFlags);
    void processEeprom(uint8_t* taskFlags);
    void processOled(uint8_t* taskFlags);

};


#endif  //STAGEMANAGER_HPP
