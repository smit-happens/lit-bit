/**  MCP7940 RTC controller class
 *
 * RtcController.cpp
 * Created 05-24-18 By: Smitty
 *
 * A longer description.
 */

#include "RtcController.hpp"


//to see if the instance of the class has been initialized yet
RtcController* RtcController::_pInstance = NULL; 

/** 
 * @brief  Used to maintain the singleton format
 * @note   
 * @retval 
 */
RtcController* RtcController::getInstance()
{
    // Only allow one instance of class to be generated.
    if (!_pInstance)
        _pInstance = new RtcController();

    return _pInstance;
}


/** 
 * @brief  
 * @note   
 * @retval 
 */
RtcController::~RtcController(void)
{
    delete rtcModel;
}


/** 
 * @brief  
 * @note   
 * @retval 
 */
void RtcController::init(void)
{
    //Logger::getInstance()->addSubscriber(_pInstance);
    rtcModel = new Rtc();
}

