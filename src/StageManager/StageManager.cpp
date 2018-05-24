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
    //LCD (boot logo)
    //GlcdController::getInstance()->setNewState(); //should be handled by init now. 

    //Teensy SelfTest (internal functions if any)
    
    //SdCard check (read data, check if good)

    
    
    //Cooling check if working
    

    //GLV batlog level check
    
    
    //assuming everything is okay
        //Notification: All systens go. Ready to Precharge

    //checking if the shutdown EF triggered
    if(*eventFlags & EF_SHUTDOWN)
    {
        shutdown(ERR_NONE);
    }
    else {
        currentStage = STAGE_STANDBY;
    }
}


/** 
 * @brief  EXTREMELY CRITICAL FUNCTIONS
 * @note   
 * @retval None
 */
void StageManager::shutdown(err_type err)
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
                shutdown(ERR_NONE);
            }


            if(*eventFlags & EF_IMD)
            {
                processImd(taskFlags);
                
                //clearing the EF so we don't trigger this again
                *eventFlags &= ~EF_IMD;
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


            if(*eventFlags & EF_UNITEK)
            {
                processUnitek(taskFlags);
                
                //clearing the EF so we don't trigger this again
                *eventFlags &= ~EF_UNITEK;
            }


            if(*eventFlags & EF_ORION)
            {
                processOrion(taskFlags);
                
                //clearing the EF so we don't trigger this again
                *eventFlags &= ~EF_ORION;
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


            if(*eventFlags & EF_BATLOG)
            {
                processBatlog(taskFlags);
                
                //clearing the EF so we don't trigger this again
                *eventFlags &= ~EF_BATLOG;
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
            if(*eventFlags & TIMER_F_ORION)
            {
                processOrion(taskFlags);

                *eventFlags &= ~TIMER_F_ORION;
            }


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


            if(*eventFlags & TIMER_F_SDCARD)
            {
                processSdCard(taskFlags);
                
                //clearing the EF so we don't trigger this again
                *eventFlags &= ~TIMER_F_SDCARD;
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
    if(taskFlags[CAN] & TF_CAN_NEW_MAIL)
    {
        // CanController::getInstance()->distributeMail();

        // taskFlags[CAN] &= ~TF_CAN_NEW_MAIL;
    }

    //checks in driving stage
    if(currentStage == STAGE_DRIVING)
    {
        //send pedal value over CAN if the timer popped
        if(taskFlags[CAN] & TF_CAN_SEND_PEDAL)
        {
            // //set RPM Setpoint in MC
            // float pedalPercent = PedalController::getInstance()->getPercentageGas();  //get percentage that the gas pedal is pressed
            // uint16_t numericSpeedSetPoint = UnitekController::getInstance()->calculateSpeedSetPoint(pedalPercent);   //calculates speed to send to MC from 0-32767

            // //this is called 50 times every second, have this code execute once a second
            // if(logCanPedalInterval % 50 == 0)
            // {
            //     //interval reset
            //     logCanPedalInterval = 0;

            //     //for sprintf
            //     char buf[80];

            //     sprintf(buf, "Calculated numericSpeedSetPoint %d, pedalPercent: %.5f", numericSpeedSetPoint, pedalPercent);
            //     logger->log("PEDAL", buf, MSG_DEBUG);
            // }

            // //send the speed over CAN to the MC (param: speed value register, upper 8 bits of numeric speed, lower 8 bits of numeric speed)
            // CanController::getInstance()->sendUnitekWrite(REG_SPEEDVAL, (uint8_t)(numericSpeedSetPoint >> 8), numericSpeedSetPoint);

            // //clearing the TF for sending pedal values
            // taskFlags[CAN] &= ~TF_CAN_SEND_PEDAL;
        }

        //TODO: add function to poll unitek so we update our local pedal value
    }

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
 * @param  currentStage: 
 * @param  tasks: 
 * @retval 
 */
void StageManager::processDash(uint8_t* taskFlags)
{
    //shutdown check performed for any stage
    if(taskFlags[DASH] & TF_DASH_SHUTDOWN)
    {
        //user wants to halt the system
        shutdown(ERR_NONE);
    }

    if(taskFlags[DASH] & TF_DASH_ENCODER)
    {
        // logger->log("STAGE_MGR", "Dash - TF_DASH_ENCODER", MSG_DEBUG);
        
        // GlcdController::getInstance()->advanceMode();
    
        taskFlags[DASH] &= ~TF_DASH_ENCODER;
    }


    //checks in standby stage
    if(currentStage == STAGE_STANDBY)
    {
        //precharge button is pressed
        if(taskFlags[DASH] & TF_DASH_PRECHARGE)
        {
            // logger->log("DASH", "Dash - TF_DASH_PRECHARGE", MSG_DEBUG);

            //change stage to precharging
            changeStage = STAGE_PRECHARGE;
        
            taskFlags[DASH] &= ~TF_DASH_PRECHARGE;
        }
    }

    //checks in energized stage
    if(currentStage == STAGE_ENERGIZED)
    {
        if(taskFlags[DASH] & TF_DASH_RTD)
        {
            // logger->log("DASH", "Dash - TF_DASH_RTD", MSG_DEBUG);
            
            //Changing the stage
            changeStage = STAGE_DRIVING;

            //Clearing event flag
            taskFlags[DASH] &= ~TF_DASH_RTD;
        }
    }

    //checks in everything but standby stage
    if(currentStage != STAGE_STANDBY)
    {
        if(taskFlags[DASH] & TF_DASH_STANDBY)
        {
            // logger->log("DASH", "Dash - TF_DASH_STANDBY", MSG_DEBUG);
            
            //Changing the stage
            changeStage = STAGE_STANDBY;

            //Clearing event flag
            taskFlags[DASH] &= ~TF_DASH_STANDBY;
        }
    }

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
 * @retval 
 */
void StageManager::processImd(uint8_t* taskFlags)
{
    //TODO: have this drop to standby rather than shutdown, but that's TBD
    // logger->log("IMD", "IMD Error", MSG_ERR);

    //activate the error light
    // LightController::getInstance()->turnOn(LightController::LIGHT_ERR_IMD);

    //required to shutdown based on error
    shutdown(ERR_IMD);

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
