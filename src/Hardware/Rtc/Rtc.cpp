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
    mcp7940Lib = new MCP7940_Class();
    
    //start the RTC
    mcp7940Lib->begin();
    // Serial.println(F("MCP7940 initialized."));

    // Turn oscillator on if necessary
    while (!mcp7940Lib->deviceStatus())  //check if it's off
    {
        // Serial.println(F("Oscillator is off, turning it on."));
        mcp7940Lib->deviceStart();

    }

    // Set to library compile Date/Time
    mcp7940Lib->adjust();
    
    //display the time and date
    // Serial.println(mcp7940Lib->now().month());
    // Serial.println(mcp7940Lib->now().day());
    // Serial.println(mcp7940Lib->now().year());  
}


/** 
 * @brief  Rtc destructor
 */
Rtc::~Rtc(void)
{

}
