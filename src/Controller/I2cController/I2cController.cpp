/**  I2c controller class
 *
 * I2cController.cpp
 * Created 05-26-18 By: Smitty
 *
 * A longer description.
 */

#include "I2cController.hpp"


//to see if the instance of the class has been initialized yet
I2cController* I2cController::_pInstance = NULL; 

/** 
 * @brief  Used to maintain the singleton format
 * @note   
 * @retval 
 */
I2cController* I2cController::getInstance()
{
    // Only allow one instance of class to be generated.
    if (!_pInstance)
        _pInstance = new I2cController();

    return _pInstance;
}


/** 
 * @brief  
 * @note   
 * @retval 
 */
I2cController::~I2cController(void)
{
    delete i2cModel;
}


/** 
 * @brief  
 * @note   
 * @retval 
 */
void I2cController::init(void)
{
    //Logger::getInstance()->addSubscriber(_pInstance);
    i2cModel = new I2c();
}

