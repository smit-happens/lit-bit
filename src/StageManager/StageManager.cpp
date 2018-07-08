/**  Manages the event handling functions in the superloop
 *
 * StageManager.cpp
 * Created 05-24-18 By: Smitty
 *
 * A longer description.
 */

#include "StageManager.hpp"



/** 
 * @brief  StageManager constructor
 */
StageManager::StageManager(void)
{
    //The first step when running is bootup
    currentStage = STAGE_BOOTTEST;
    
    //changing stage if any events trigger it
    changeStage = currentStage;


    timerList = new Timer[TIMER_NUM];
    timerList[0].limit = POLL_TIME_GLCD;
    
    timerList[0].TFmask = TIMER_F_OLED;

    //initializing the variables in the Timer array
    for(int i = 0; i < TIMER_NUM; i++) 
    {
        //creating the individual mask for each timer
        timerList[i].count = 0;
    }
}


/** 
 * @brief  Handles the multiple timers running off of a single 1ms timer from main
 * @note   Might have to be fleshed out more
 * @retval uint32_t with each bit coresponding to which timers went off
 */
uint8_t StageManager::processTimers(void)
{
    //Goes through the array of timers to increment their count and store which ones popped
    for (int i = 0; i < TIMER_NUM; i++)
    {
        timerList[i].count++;
        if(timerList[i].count >= timerList[i].limit)
        {
            //store which timer popped
            timerTF |= timerList[i].TFmask;

            //resetting the count of the timer that just popped
            timerList[i].count = 0;
        }

    }

    return timerTF;
}


/** 
 * @brief  
 * @note   
 * @retval None
 */
void StageManager::bootTest(uint16_t* eventFlags)
{
    //TODO: figure out if this is even needed
    //could be used to grab time from RTC on boot
    currentStage = STAGE_STANDBY;

}


/** 
 * @brief  EXTREMELY CRITICAL FUNCTIONS
 * @note   
 * @retval None
 */
void StageManager::shutdown()
{
    //Halt system 
    while(1) {;}
}


/** 
 * @brief  Contains the initial configuration steps for any stage
 * @note   
 * @retval None
 */
void StageManager::configureStage(void)
{

    switch(currentStage)
    {
        // Entry condition: EVOS finishes subsystem testing
        // Exit condition:  Driver requests Precharging
        case STAGE_STANDBY:
        {
            //check to make sure this hasn't been ran before for this stage
            if(isStandbyConfigured == false)
            {


            }
        }
        break;

        
        // // Entry condition: Driver requests Precharging
        // // Exit condition:  Precharge done signal recieved from Unitek
        // case STAGE_PRECHARGE:
        // {
        //     //check to make sure this hasn't been ran before for this stage
        //     if(isPrechargeConfigured == false)
        //     {

        //     }   
        // }   
        // break;


        // // Entry condition: Precharge done signal recieved from Unitek
        // // Exit condition:  Driver requests ready to drive
        // case STAGE_ENERGIZED:
        // {
        //     //check to make sure this hasn't been ran before for this stage
        //     if(isEnergizedConfigured == false)
        //     {

        //     }
        // }
        // break;


        // // Entry condition: Driver requests ready to drive
        // // Exit condition:  Driver requests standby
        // case STAGE_DRIVING:
        // {
        //     //check to make sure this hasn't been ran before for this stage
        //     if(isDrivingConfigured == false)
        //     {


        //     }
        // }
        // break;


        default:
            //shouldn't get here
        break;
    }

}


/** 
 * @brief  Handles the event and task flags for each device
 * @note   
 * @param  urgencyLevel: 
 * @param  eventFlags: 
 * @param  taskFlags: 
 * @retval 
 */
Stage StageManager::processStage(uint16_t* eventFlags, uint8_t* taskFlags)
{
    configureStage();
    
    //if any of the processing functions change the stage, we don't want it affecting the other processing events
    changeStage = currentStage;


    if(*eventFlags & EF_SHUTDOWN)
    {
        shutdown();
    }

    if(*eventFlags & EF_ADXL)
    {
        processAdxl(taskFlags);
        
        //clearing the EF so we don't trigger this again
        *eventFlags &= ~EF_ADXL;
    }

    if(*eventFlags & EF_RTC)
    {
        processRtc(taskFlags);
        
        //clearing the EF so we don't trigger this again
        *eventFlags &= ~EF_RTC;
    }

    if(*eventFlags & EF_BLE)
    {
        processBle(taskFlags);
        
        //clearing the EF so we don't trigger this again
        *eventFlags &= ~EF_BLE;
    }

    if(*eventFlags & TIMER_F_EEPROM)
    {
        processEeprom(taskFlags);
        
        //clearing the EF so we don't trigger this again
        *eventFlags &= ~TIMER_F_EEPROM;
    }

    if(*eventFlags & TIMER_F_OLED)
    {
        processOled(taskFlags);
        
        //clearing the EF so we don't trigger this again
        *eventFlags &= ~TIMER_F_OLED;
    }


    return changeStage;
}


/** 
 * @brief  
 * @note   
 * @retval 
 */
void StageManager::processAdxl(uint8_t* taskFlags)
{


}


/** 
 * @brief  
 * @note   
 * @retval 
 */
void StageManager::processRtc(uint8_t* taskFlags)
{


}


/** 
 * @brief  
 * @note   
 * @retval 
 */
void StageManager::processBle(uint8_t* taskFlags)
{


}


/** 
 * @brief  
 * @note   
 * @retval 
 */
void StageManager::processEeprom(uint8_t* taskFlags)
{


}


/** 
 * @brief  
 * @note   
 * @retval 
 */
void StageManager::processOled(uint8_t* taskFlags)
{
    //glcd view display updating
    // GlcdController::getInstance()->poll(); //will flush buffer if required.
    return;
}


/** 
 * @brief  
 * @note   
 * @param  currentStage: 
 * @retval None
 */
void StageManager::resetAllStagesExcept(Stage nonResetStage)
{
    //initially setting all the stage configurations to false, then "enabling" the current Stage
    isStandbyConfigured = false;
    isPrechargeConfigured = false;
    isEnergizedConfigured = false;
    isDrivingConfigured = false;


    //checking which stage we're currently in (same as which stage is configured correctly)
    switch(nonResetStage)
    {
        //Standby stage is configured
        case Stage::STAGE_STANDBY:
        {
            // logger->log("STAGE_MGR", "Started configuring STAGE_STANDBY", MSG_LOG);
            isStandbyConfigured = true;
        }
        break;

        
        // //Precharge stage is configured
        // case Stage::STAGE_PRECHARGE:
        // {
        //     // logger->log("STAGE_MGR", "Started configuring STAGE_PRECHARGE", MSG_LOG);
        //     isPrechargeConfigured = true;
        // }
        // break;


        // //Energized stage is configured
        // case Stage::STAGE_ENERGIZED:
        // {
        //     // logger->log("STAGE_MGR", "Started configuring STAGE_ENERGIZED", MSG_LOG);    
        //     isEnergizedConfigured = true;
        // }
        // break;


        // //Driving stage is configured
        // case Stage::STAGE_DRIVING:
        // {
        //     // logger->log("STAGE_MGR", "Started configuring STAGE_DRIVING", MSG_LOG);            
        //     isDrivingConfigured = true;
        // }
        // break;


        default:
            //shouldn't get here
        break;
    }
}
