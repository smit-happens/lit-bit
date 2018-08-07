/**  Handles the setup and usage of the MCP7940N RTC
 *
 * Rtc.cpp
 * Created 05-24-18  By: Smitty
 *
 * A longer description.
 */

#include "Rtc.hpp"


//to see if the instance of the class has been initialized yet
Rtc* Rtc::_pInstance = NULL; 

/** 
 * @brief  Used to maintain the singleton format
 * @note   
 * @retval 
 */
Rtc* Rtc::getInstance()
{
    // Only allow one instance of class to be generated.
    if (!_pInstance)
        _pInstance = new Rtc();

    return _pInstance;
}


/** 
 * @brief  
 * @note   
 * @retval 
 */
void Rtc::init(void)
{
    pinMode(LB_RTC_MFP, INPUT);

    mcp7940Lib = new MCP7940_Class();
    
    //start the RTC
    mcp7940Lib->begin();

    // Turn oscillator on if necessary
    while (!mcp7940Lib->deviceStatus())  //check if it's off
    {
        // Oscillator is off, turning it on.
        mcp7940Lib->deviceStart();
    }

    // Set to library compile Date/Time
    mcp7940Lib->adjust();

    //configuring Alarm0
    byte alarm0 = mcp7940Lib->readByte(MCP7940_ALM0WKDAY);

    alarm0 |= B10001000;

    mcp7940Lib->writeByte(MCP7940_ALM0WKDAY, alarm0);

    DateTime now = mcp7940Lib->now();

    //configure Alarn0 to go off 15 minutes in the future
    mcp7940Lib->setAlarm(0, matchAll, now + TimeSpan(0,0,ALARM0_INTERVAL,0));
 
}
