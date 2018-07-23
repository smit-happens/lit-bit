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

    ~Adxl(void);
    static Adxl*   getInstance();
    void init(void);

    void setupTap(void);
    void setupDataRate();

    void storeAccelXYZ(void);
    int getX(void);
    int getY(void);
    int getZ(void);

    void getInterruptSource(void);

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

};


#endif  //ADXL_HPP
