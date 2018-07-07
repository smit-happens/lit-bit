/**  Represents the Model for the adxl345 chip
 *
 * #include "Adxl.hpp"
 * Created 06-02-18  By: Smitty
 *
 * A longer description.
 */

#ifndef ADXL_HPP
#define ADXL_HPP

#include "../BaseModel/BaseModel.hpp"
#include "../Constants/Flags.hpp"
#include <SparkFun_ADXL345.h>           //Source: https://github.com/shirish47/SparkFun_ADXL345_Arduino_Library
#include <Wire.h>


class Adxl : public BaseModel
{
public:
    Adxl(void);
    ~Adxl(void);

    void storeAccelXYZ(void);
    int getX(void);
    int getY(void);
    int getZ(void);
    

private:
    ADXL345* adxlLib;

    int* xyz;

};


#endif  //ADXL_HPP
