/**  I2c controller class
 *
 * EepromController.cpp
 * Created 05-26-18 By: Smitty
 *
 * A longer description.
 */

#include "EepromController.hpp"


//to see if the instance of the class has been initialized yet
EepromController* EepromController::_pInstance = NULL; 

/** 
 * @brief  Used to maintain the singleton format
 * @note   
 * @retval 
 */
EepromController* EepromController::getInstance()
{
    // Only allow one instance of class to be generated.
    if (!_pInstance)
        _pInstance = new EepromController();

    return _pInstance;
}


/** 
 * @brief  
 * @note   
 * @retval 
 */
EepromController::~EepromController(void)
{
    delete eepromModel;
}


/** 
 * @brief  
 * @note   
 * @retval 
 */
void EepromController::init(void)
{
    eepromModel = new Eeprom();
}

