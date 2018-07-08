/**  Adxl controller class
 *
 * AdxlController.cpp
 * Created 06-02-18 By: Smitty
 *
 * A longer description.
 */

#include "AdxlController.hpp"


//to see if the instance of the class has been initialized yet
AdxlController* AdxlController::_pInstance = NULL; 

/** 
 * @brief  Used to maintain the singleton format
 * @note   
 * @retval 
 */
AdxlController* AdxlController::getInstance()
{
    // Only allow one instance of class to be generated.
    if (!_pInstance)
        _pInstance = new AdxlController();

    return _pInstance;
}


/** 
 * @brief  
 * @note   
 * @retval 
 */
AdxlController::~AdxlController(void)
{
    delete adxlModel;
}


/** 
 * @brief  
 * @note   
 * @retval 
 */
void AdxlController::init(void)
{
    adxlModel = new Adxl();
    adxlModel->setupTap();
}

