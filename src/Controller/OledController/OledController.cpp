/**  Display controller class
 *
 * OledController.cpp
 * Created 05-24-18 By: Smitty
 *
 * A longer description.
 */

#include "OledController.hpp"


//to see if the instance of the class has been initialized yet
OledController* OledController::_pInstance = NULL; 

/** 
 * @brief  Used to maintain the singleton format
 * @note   
 * @retval 
 */
OledController* OledController::getInstance()
{
    // Only allow one instance of class to be generated.
    if (!_pInstance)
        _pInstance = new OledController();

    return _pInstance;
}


/** 
 * @brief  
 * @note   
 * @retval 
 */
OledController::~OledController(void)
{
    delete oledModel;
}


/** 
 * @brief  
 * @note   
 * @retval 
 */
void OledController::init(void)
{
    //Logger::getInstance()->addSubscriber(_pInstance);
    oledModel = new Oled();
}

