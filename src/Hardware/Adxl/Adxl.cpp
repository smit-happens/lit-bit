/**  Represents the Model of the ADXL345 chip
 *
 * Adxl.cpp
 * Created 06-02-18  By: Smitty
 *
 * A longer description.
 */

#include "Adxl.hpp"


//to see if the instance of the class has been initialized yet
Adxl* Adxl::_pInstance = NULL; 

/** 
 * @brief  Used to maintain the singleton format
 * @note   
 * @retval 
 */
Adxl* Adxl::getInstance()
{
    // Only allow one instance of class to be generated.
    if (!_pInstance)
        _pInstance = new Adxl();

    return _pInstance;
}


/** 
 * @brief  
 * @note   
 * @retval 
 */
void Adxl::init(void)
{
    //setting the interrupt pin as an input
    pinMode(LB_ADXL_INT1, INPUT);

    adxlLib = new ADXL345();

    // Power on the ADXL345
    adxlLib->powerOn();

    //set data rate to 50Hz
    adxlLib->set_bw(ADXL345_BW_25);

    //set measurement range to +- 4G
    adxlLib->setRangeSetting(4);

    //initialize the accel to 0 since no readings have been done
    xyz = new int[3];

    //configure tap detection
    setupTap();

    //map the single tap interrupt to the int1 pin on the adxl
    adxlLib->setInterruptMapping(ADXL345_INT_SINGLE_TAP_BIT, ADXL345_INT2_PIN);
    adxlLib->setInterruptMapping(ADXL345_INT_WATERMARK_BIT, ADXL345_INT2_PIN);

    setupFifo();

    //enable the interrupts
    adxlLib->singleTapINT(true);
    adxlLib->waterMarkINT(true);
}


void Adxl::setupTap()
{
    //enable the single/double tap functionality 625µs/LSB
    adxlLib->setTapDuration(250);
    //set the tap threshold 62.5 mg/LSB
    adxlLib->setTapThreshold(200);
    //detect the taps on the Z axis 
    adxlLib->setTapDetectionOnZ(true);
    //default interupt logic is active high
}


void Adxl::setupFifo()
{
    //enable fifo mode
    adxlLib->enableFIFOMode();

    //write number of samples needed to trigger watermark
    adxlLib->writeWatermarkSamples(WATERMARK_SAMPLE_NUM);
}


void Adxl::readFifo(uint16_t* buffer)
{
    int fifoAmount = adxlLib->getFIFOcounts();

    for(int i = 0; i < fifoAmount; i++ )
    {
        adxlLib->readAccel(xyz);

        int temp =  (*getX() * *getX()) + (*getY() * *getY()) + (*getZ() * *getZ());

        buffer[i] = temp;
    }
}


void Adxl::storeAccelXYZ(void)
{
    // adxlLib->get_Gxyz(xyz);
    adxlLib->readAccel(xyz);
}
