/**  Represents the Model for the adxl345 chip
 *
 * #include "Adxl.hpp"
 * Created 06-02-18  By: Smitty
 *
 * A longer description.
 */

#ifndef ADXL_HPP
#define ADXL_HPP

#include <SparkFun_ADXL345.h>           //Source: https://github.com/shirish47/SparkFun_ADXL345_Arduino_Library
#include "../Constants/Port.hpp"


class Adxl
{
public:
    ADXL345* adxlLib;

    ~Adxl(void) { delete adxlLib; };
    static Adxl*   getInstance();
    void init(void);

    void setupTap(void);
    void setupFifo();

    void storeAccelXYZ(void);
    int* getX(void) { return xyz; };
    int* getY(void) { return xyz +1; };
    int* getZ(void) { return xyz +2; };

    void readFifo(uint16_t* buffer);

    void isStep(uint16_t* buffer);

    int getMagnitude(void);
    void printValues();
    

private:
    //Private contstructor so that it can't be called
    Adxl() {};
    //copy constructor is private
    Adxl(Adxl const&) {};
    //static instance pointer
    static Adxl* _pInstance;
    
    int* xyz;

    const byte WATERMARK_SAMPLE_NUM = 30;

};


#endif  //ADXL_HPP
