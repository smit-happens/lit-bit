/**  Represents the Model of an I2C message
 *
 * I2c.cpp
 * Created 05-24-18  By: Smitty
 *
 * A longer description.
 */

#include "I2c.hpp"

/** 
 * @brief  I2c constructor
 */
I2c::I2c(void)
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


