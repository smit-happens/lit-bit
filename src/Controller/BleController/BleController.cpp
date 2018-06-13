/**  bluetooth controller class
 *
 * BleController.cpp
 * Created 06-13-18 By: Smitty
 *
 * A longer description.
 */

#include "BleController.hpp"


//to see if the instance of the class has been initialized yet
BleController* BleController::_pInstance = NULL; 

/** 
 * @brief  Used to maintain the singleton format
 * @note   
 * @retval 
 */
BleController* BleController::getInstance()
{
    // Only allow one instance of class to be generated.
    if (!_pInstance)
        _pInstance = new BleController();

    return _pInstance;
}


/** 
 * @brief  
 * @note   
 * @retval 
 */
BleController::~BleController(void)
{
    delete bluetoothModel;
}


/** 
 * @brief  
 * @note   
 * @retval 
 */
void BleController::init(void)
{
    //Logger::getInstance()->addSubscriber(_pInstance);
    bluetoothModel = new Bluetooth();
}

