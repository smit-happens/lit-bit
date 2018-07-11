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
    //setting the interrupt pin as an input
    pinMode(LB_ADXL_INT1, INPUT);

    adxlLib = new ADXL345();

    // Power on the ADXL345
    adxlLib->powerOn();

    //set range to +- 4G
    adxlLib->setRangeSetting(4); 

    //initialize the accel to 0 since no readings have been done
    xyz = new int[3];

    //FIXME: testing code
    // adxlLib->disableAllInterrupts();

    // adxlLib->enableFIFOMode();
    
}


/** 
 * @brief  Adxl destructor
 */
Adxl::~Adxl(void)
{
    delete adxlLib;
}


void Adxl::setupTap()
{
    //enable the single/double tap functionality
    adxlLib->setTapDuration(5);
    //set the tap threshold
    adxlLib->setTapThreshold(5);
    //detect the taps on the Z axis 
    adxlLib->setTapDetectionOnZ(true);
    //enable the interrupt for single tap
    adxlLib->singleTapINT(true);
    //map the single tap interrupt to the int1 pin on the adxl
    adxlLib->setInterruptMapping(ADXL345_INT_SINGLE_TAP_BIT, ADXL345_INT1_PIN);
    //default interupt logic is active high
}

void Adxl::setupDataRate()
{
    
}


void Adxl::storeAccelXYZ(void)
{
    // adxlLib->get_Gxyz(xyz);
    adxlLib->readAccel(xyz);
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

