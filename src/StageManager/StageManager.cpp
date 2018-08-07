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
    timerList = new Timer[TIMER_NUM];
    timerList[0].limit = POLL_TIME_OLED;
    timerList[1].limit = POLL_TIME_ADXL;
    
    
    timerList[0].TFmask = TIMER_F_OLED;
    timerList[1].TFmask = TIMER_F_ADXL;

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
 * @brief  Handles the event and task flags for each device
 * @note   
 * @param  urgencyLevel: 
 * @param  eventFlags: 
 * @param  taskFlags: 
 * @retval 
 */
void StageManager::processStage(uint16_t* eventFlags, uint8_t* taskFlags)
{
    if(*eventFlags & EF_SHUTDOWN)
    {
        shutdown();
    }

    if(*eventFlags & EF_ADXL)
    {
        processAdxl(eventFlags, taskFlags);
        
        //clearing the ADXL EF
        *eventFlags &= ~EF_ADXL;
    }

    if(*eventFlags & EF_RTC)
    {
        processRtc(taskFlags);
        
        //clearing the RTC EF
        *eventFlags &= ~EF_RTC;
    }

    if(*eventFlags & TIMER_F_EEPROM)
    {
        processEeprom(taskFlags);
        
        //clearing the EEPROM EF
        *eventFlags &= ~TIMER_F_EEPROM;
    }

    if(*eventFlags & TIMER_F_OLED << 8)
    {
        processOled(taskFlags);
        
        //clearing the OLED EF
        *eventFlags &= ~TIMER_F_OLED;
    }
}


/** 
 * @brief  
 * @note   
 * @retval 
 */
void StageManager::processAdxl(uint16_t* eventFlags, uint8_t* taskFlags)
{
    uint8_t AdxlInterrupts = adxl->adxlLib->getInterruptSource();

    if(adxl->adxlLib->triggered(AdxlInterrupts, ADXL345_SINGLE_TAP))
    {
        // Serial.println("single tap");
        Serial.println(stepCount);
    }

    if(adxl->adxlLib->triggered(AdxlInterrupts, ADXL345_WATERMARK))
    {
        uint16_t data[32] = { 0 };

        //read all the values in the fifo
        adxl->readFifo(data);

        for(int i = 0; i < 32; i++)
        {
            if(data[i] != 0)
            {
                // Serial.println(data[i]);

                if(data[i] > 175)
                {
                    upSwing = 1;
                    // stepCount++;
                }
                else if (data[i] < 40)
                {
                    downSwing = 1;
                }

                
                if (upSwing == 1 && downSwing == 1) 
                {
                    stepCount++;
                    upSwing = 0, downSwing = 0;
                }
                
            }


        }

        // adxl->isStep(data);

    }
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
    // Serial.println("oled function");
}
