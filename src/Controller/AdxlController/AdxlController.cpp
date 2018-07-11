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
    // adxlModel->setupTap();
}


void AdxlController::getInterruptSource(void)
{
    //storing the interrupts that triggered in the adxl
    uint8_t interruptStatus = adxlModel->adxlLib->getInterruptSource();

    if(adxlModel->adxlLib->triggered(interruptStatus, ADXL345_SINGLE_TAP))
    {
        Serial.println("single tap");
    }

    if(adxlModel->adxlLib->triggered(interruptStatus, ADXL345_DATA_READY))
    {
        //trying to read the data in the data registers to clear the interrupt
        adxlModel->storeAccelXYZ();
    }

}


int AdxlController::getMagnitude(void)
{
    int magnitude = 0;
    
    //update the xyz data
    adxlModel->storeAccelXYZ();

    int x = adxlModel->getX();
    int y = adxlModel->getY();
    int z = adxlModel->getZ();

    //square all the axis and add them up
    magnitude = x * x + y * y + z * z;

    magnitude = sqrt(magnitude);

    return magnitude;
}