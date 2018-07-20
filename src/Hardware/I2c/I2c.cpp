/**  Represents the Model of an I2C message
 *
 * I2c.cpp
 * Created 05-24-18  By: Smitty
 *
 * A longer description.
 */

#include "I2c.hpp"


//to see if the instance of the class has been initialized yet
I2c* I2c::_pInstance = NULL; 

/** 
 * @brief  Used to maintain the singleton format
 * @note   
 * @retval 
 */
I2c* I2c::getInstance()
{
    // Only allow one instance of class to be generated.
    if (!_pInstance)
        _pInstance = new I2c();

    return _pInstance;
}


/** 
 * @brief  
 * @note   
 * @retval 
 */
void I2c::init(void)
{
    Wire.begin();
    Wire.setClock(400000L); //setting the data rate of I2C to 400kHz
}


/** 
 * @brief  I2c destructor
 */
I2c::~I2c(void)
{
    Wire.end();
}


