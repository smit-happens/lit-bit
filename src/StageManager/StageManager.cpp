/**  Manages the event handling functions in the superloop
 *
 * StageManager.cpp
 * Created 05-24-18 By: Smitty
 *
 * A longer description.
 */

#include "StageManager.hpp"


/** 
 * @brief  Handles the event and task flags for each device
 * @note   
 * @param  urgencyLevel: 
 * @param  eventFlags: 
 * @param  taskFlags: 
 * @retval 
 */
void StageManager::processStage(uint8_t* eventFlags, uint8_t* taskFlags)
{
    if(*eventFlags & EF_ADXL)
    {
        processAdxl(eventFlags, taskFlags);
        
        //clearing the ADXL EF
        *eventFlags &= ~EF_ADXL;
    }

    if(*eventFlags & EF_RTC)
    {
        processRtc(eventFlags, taskFlags);
        
        //clearing the RTC EF
        *eventFlags &= ~EF_RTC;
    }

    if(*eventFlags & EF_EEPROM)
    {
        processEeprom(taskFlags);
        
        //clearing the EEPROM EF
        *eventFlags &= ~EF_EEPROM;
    }

    if(*eventFlags & EF_OLED)
    {
        processOled(taskFlags);
        
        //clearing the OLED EF
        *eventFlags &= ~EF_OLED;
    }
}


/** 
 * @brief  
 * @note   
 * @retval 
 */
void StageManager::processAdxl(uint8_t* eventFlags, uint8_t* taskFlags)
{
    uint8_t AdxlInterrupts = adxl->adxlLib->getInterruptSource();

    if(adxl->adxlLib->triggered(AdxlInterrupts, ADXL345_SINGLE_TAP))
    {
        //set display EF & TF to go off
        *eventFlags |= EF_OLED;
        taskFlags[DEVICE_OLED] |= TF_OLED_STEP;
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

                if(data[i] > 55000 && (downSwing == 0))
                {
                    upSwing = 1;
                }
                else if (data[i] < 5000 && (upSwing == 1))
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
    }
}


/** 
 * @brief  
 * @note   
 * @retval 
 */
void StageManager::processRtc(uint8_t* eventFlags, uint8_t* taskFlags)
{
    // char inputBuffer[32];
    
    //technically this triggers constantly but we check to actually see if the alarm went off or not
    if(rtc->mcp7940Lib->isAlarm(0))
    {
        DateTime now = rtc->mcp7940Lib->now();
        // sprintf(inputBuffer,"%04d-%02d-%02d %02d:%02d:%02d", now.year(),        // Use sprintf() to pretty print    //
        //         now.month(), now.day(), now.hour(), now.minute(), now.second());// date/time with leading zeroes    //
        // Serial.println(inputBuffer);
        // rtc->mcp7940Lib->clearAlarm(0);
        rtc->mcp7940Lib->setAlarm(0, rtc->matchAll, now + TimeSpan(0, 0, rtc->ALARM0_INTERVAL, 0));

        *eventFlags |= EF_EEPROM;
        taskFlags[DEVICE_EEPROM] |= TF_EEPROM_15MIN_SAVE;

    }
}


/** 
 * @brief  
 * @note   
 * @retval 
 */
void StageManager::processEeprom(uint8_t* taskFlags)
{
    if(taskFlags[DEVICE_EEPROM] & TF_EEPROM_15MIN_SAVE)
    {
        uint32_t nowUnix = rtc->mcp7940Lib->now().unixtime();

        eeprom->writeEntry(&nowUnix, &stepCount);

        eeprom->addTotalSteps(stepCount);

        //reset count for next interval
        stepCount = 0;

        //clear the task flag
        taskFlags[DEVICE_EEPROM] &= ~TF_EEPROM_15MIN_SAVE;
    }
}


/** 
 * @brief  
 * @note   
 * @retval 
 */
void StageManager::processOled(uint8_t* taskFlags)
{
    if(taskFlags[DEVICE_OLED] & TF_OLED_STEP)
    {
        //glcd view display updating
        oled->wakeUp();
        oled->display->setCursor(0, 0);
        oled->display->print("15min: ");
        oled->display->println(stepCount);
        oled->display->print("Total: ");
        oled->display->println(eeprom->getTotalSteps());
        oled->display->display();

        wdt_enable(WDTO_1S);

        WDTCSR |= 0x1 << 6;

        taskFlags[DEVICE_OLED] &= ~TF_OLED_STEP;        
    }

    if(taskFlags[DEVICE_OLED] & TF_OLED_TIMEOUT)
    {
        oled->sleep();

        wdt_disable();

        taskFlags[DEVICE_OLED] &= ~TF_OLED_TIMEOUT;
    }
    
}
