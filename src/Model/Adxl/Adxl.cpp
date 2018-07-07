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

    //initialize the accel to 0 since no readings have been done
    xyz = { 0 };
}


/** 
 * @brief  Adxl destructor
 */
Adxl::~Adxl(void)
{

}

void Adxl::storeAccelXYZ(void)
{
    // adxlLib->get_Gxyz(xyz);
    adxlLib->readAccel(xyz);

    // Serial.print("x = ");
    // Serial.println(xyz[0]);
    // Serial.print("y = ");
    // Serial.println(xyz[1]);
    // Serial.print("z = ");
    // Serial.println(xyz[2]);
}


int Adxl::getX()
{
    return xyz[0];
}


int Adxl::getY()
{
    return xyz[1];
}


int Adxl::getZ()
{
    return xyz[2];
}

