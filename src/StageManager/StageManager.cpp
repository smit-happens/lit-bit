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

    // if(*eventFlags & EF_ADXL)
    // {
    //     processAdxl(taskFlags);
        
    //     //clearing the ADXL EF
    //     *eventFlags &= ~EF_ADXL;
    // }

    if(*eventFlags & EF_RTC)
    {
        processRtc(taskFlags);
        
        //clearing the RTC EF
        *eventFlags &= ~EF_RTC;
    }

    //FIXME: temp code to allow timers to poll the adxl
    if(*eventFlags & TIMER_F_ADXL << 8)
    {
        processAdxl(taskFlags);
        
        //clearing the Adxl timer EF
        *eventFlags &= ~TIMER_F_ADXL;
    }

    if(*eventFlags & EF_BLE)
    {
        processBle(taskFlags);
        
        //clearing the BLE EF
        *eventFlags &= ~EF_BLE;
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
void StageManager::processAdxl(uint8_t* taskFlags)
{
    // AdxlController::getInstance()->getInterruptSource();
    // int magnitude = AdxlController::getInstance()->getMagnitude();

    // Serial.println(magnitude);
    
    // AdxlController::getInstance()->printValues();
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
    //local bluetooth lib reference
    Adafruit_BLE_UART* BleLib = bleC->bluetoothModel->bluetooth;
    //local oled reference
    MicroOLED* oledLib = oledC->oledModel->display;

    if(taskFlags[BLE] & TF_BLE_ACI)
    {
        aci_evt_opcode_t status = BleLib->getState();

        switch(status)
        {
            case ACI_EVT_DEVICE_STARTED:
                Serial.println(F("Advertising started"));
            break;

            case ACI_EVT_CONNECTED:
                Serial.println(F("Connected!"));
            break;

            case ACI_EVT_DISCONNECTED:
                Serial.println(F("Disconnected or advertising timed out"));
            break;

            case ACI_EVT_DATA_RECEIVED:
                //TODO: see if this ever triggers
            break;

            default:
            break;
        }
        taskFlags[BLE] &= ~TF_BLE_ACI;
    }
    if(taskFlags[BLE] & TF_BLE_RX)
    {
        oledLib->clear(PAGE);
        oledLib->setCursor(0,0);

        while (BleLib->available()) {
            char c = BleLib->read();
            Serial.print(c);
            
            oledLib->write(c);
        }
        Serial.println();

        //update display
        oledLib->display();

        taskFlags[BLE] &= ~TF_BLE_RX;
    }


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
