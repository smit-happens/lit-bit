/**  Manages the event handling functions in the superloop
 *
 * #include "StageManager.hpp"
 * Created 05-24-18 By: Smitty
 *
 * A longer description.
 */

#ifndef STAGEMANAGER_HPP
#define STAGEMANAGER_HPP

#include "../Controller/Controller.hpp"
#include "../Model/Constants/TimeDelay.hpp"
#include "../Model/Constants/Flags.hpp"
#include "../Model/Constants/Constants.hpp"


class StageManager
{
public:

    //current stage that we're processing
    Stage currentStage;

    //used to determine if a stage needs to be configured or not
    bool isStandbyConfigured = false;
    bool isPrechargeConfigured = false;
    bool isEnergizedConfigured = false;
    bool isDrivingConfigured = false;

    StageManager();

    //handles the various timers we'll be using and setting Task Flags (TFs) based on them
    uint8_t processTimers(void);

    //Boot for each device
    void bootTest(uint16_t* eventFlags);

    void shutdown();

    //contains code that is executed once at the beginning of a stage
    void configureStage(void);

    //handles the excecution of the various stages
    Stage processStage(uint16_t* eventFlags, uint8_t* taskFlags);


private:
    struct Timer {
        /* add name string field */
        int count;
        int limit;
        uint8_t TFmask;
    };
     
    Timer* timerList;
    uint8_t timerTF = 0;

    Stage changeStage;


    //Processing functions for the various devices
    void processAdxl(uint8_t* taskFlags);
    void processRtc(uint8_t* taskFlags);
    void processBle(uint8_t* taskFlags);
    void processEeprom(uint8_t* taskFlags);
    void processOled(uint8_t* taskFlags);
    // void processPedal(uint8_t* eventFlags, uint8_t* taskFlags);


    //for making sure that all the stages except the currently executing one needs to be reconfigured
    void resetAllStagesExcept(Stage nonResetStage);

};


#endif  //STAGEMANAGER_HPP
