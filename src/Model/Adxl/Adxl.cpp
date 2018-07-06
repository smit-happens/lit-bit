/**  Represents the Model of the ADXL345 chip
 *
 * Adxl.cpp
 * Created 06-02-18  By: Smitty
 *
 * A longer description.
 */

#include "Adxl.hpp"

/** 
 * @brief  Adxl constructor
 */
Adxl::Adxl(void)
{
    adxlLib = new ADXL345();

    // Power on the ADXL345
    adxlLib->powerOn();

    int xyz[3];

    // adxlLib->get_Gxyz(xyz);
    adxlLib->readAccel(xyz);

    Serial.print("x = ");
    Serial.println(xyz[0]);
    Serial.print("y = ");
    Serial.println(xyz[1]);
    Serial.print("z = ");
    Serial.println(xyz[2]);
}


/** 
 * @brief  Adxl destructor
 */
Adxl::~Adxl(void)
{

}


