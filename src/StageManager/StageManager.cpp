/**  Manages the event handling functions in the superloop
 *
 * StageManager.cpp
 * Created 1-28-18 By: Smitty
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
    timerList[1].limit = POLL_TIME_SDCARD;
    timerList[2].limit = POLL_TIME_PEDAL;
    timerList[3].limit = POLL_TIME_ORION;
    
    timerList[0].TFmask = TIMER_F_GLCD;
    timerList[1].TFmask = TIMER_F_SDCARD;
    timerList[2].TFmask = TIMER_F_PEDAL;
    timerList[3].TFmask = TIMER_F_ORION;

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
uint32_t StageManager::processTimers(void)
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
void StageManager::bootTest(uint32_t* eventFlags)
{

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

        
        // Entry condition: Driver requests Precharging
        // Exit condition:  Precharge done signal recieved from Unitek
        case STAGE_PRECHARGE:
        {
            //check to make sure this hasn't been ran before for this stage
            if(isPrechargeConfigured == false)
            {
             

            }   
        }   
        break;


        // Entry condition: Precharge done signal recieved from Unitek
        // Exit condition:  Driver requests ready to drive
        case STAGE_ENERGIZED:
        {
            //check to make sure this hasn't been ran before for this stage
            if(isEnergizedConfigured == false)
            {

            }
        }
        break;


        // Entry condition: Driver requests ready to drive
        // Exit condition:  Driver requests standby
        case STAGE_DRIVING:
        {
            //check to make sure this hasn't been ran before for this stage
            if(isDrivingConfigured == false)
            {


            }
        }
        break;


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
Stage StageManager::processStage(Priority urgencyLevel, uint32_t* eventFlags, uint8_t* taskFlags)
{
    configureStage();
    
    //if any of the processing functions change the stage, we don't want it affecting the other processing events
    changeStage = currentStage;

    switch(urgencyLevel)
    {
        case PRIORITY_CRITICAL:
        {
            if(*eventFlags & EF_SHUTDOWN)
            {
                shutdown();
            }
        }
        break;

        
        case PRIORITY_HIGH:
        {
            if(*eventFlags & EF_CAN)
            {
                processCan(taskFlags);
                
                //clearing the EF so we don't trigger this again
                *eventFlags &= ~EF_CAN;
            }
        }
        break;


        case PRIORITY_MEDIUM:
        {
            if(*eventFlags & EF_COOLING)
            {
                processCooling(taskFlags);
                
                //clearing the EF so we don't trigger this again
                *eventFlags &= ~EF_COOLING;
            }


            if(*eventFlags & EF_DASH)
            {
                processDash(taskFlags);

                //clearing the EF so we don't trigger this again
                *eventFlags &= ~EF_DASH;
            }
        }
        break;


        case PRIORITY_LOW:
        {
            if(*eventFlags & TIMER_F_PEDAL)
            {
                processPedal(eventFlags, taskFlags);

                *eventFlags &= ~TIMER_F_PEDAL;
            }


            if(*eventFlags & TIMER_F_GLCD)
            {
                processGlcd(taskFlags);
                
                //clearing the EF so we don't trigger this again
                *eventFlags &= ~TIMER_F_GLCD;
            }
        }
        break;


        default:
            //shouldn't get here (for NUM_PRIORITY ENUM)
        break;

    } //End switch

    return changeStage;
}


/** 
 * @brief  
 * @note   
 * @retval 
 */
void StageManager::processCan(uint8_t* taskFlags)
{


}


/** 
 * @brief  
 * @note   
 * @retval 
 */
void StageManager::processCooling(uint8_t* taskFlags)
{
    //insert code here that executes for any stage


}


/** 
 * @brief  
 * @note   
 * @retval 
 */
void StageManager::processGlcd(uint8_t* taskFlags)
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

        
        //Precharge stage is configured
        case Stage::STAGE_PRECHARGE:
        {
            // logger->log("STAGE_MGR", "Started configuring STAGE_PRECHARGE", MSG_LOG);
            isPrechargeConfigured = true;
        }
        break;


        //Energized stage is configured
        case Stage::STAGE_ENERGIZED:
        {
            // logger->log("STAGE_MGR", "Started configuring STAGE_ENERGIZED", MSG_LOG);    
            isEnergizedConfigured = true;
        }
        break;


        //Driving stage is configured
        case Stage::STAGE_DRIVING:
        {
            // logger->log("STAGE_MGR", "Started configuring STAGE_DRIVING", MSG_LOG);            
            isDrivingConfigured = true;
        }
        break;


        default:
            //shouldn't get here
        break;
    }
}
