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
#include <SparkFun_ADXL345.h>
#include <Wire.h>


class Adxl : public BaseModel
{
public:
    Adxl(void);
    ~Adxl(void);
    

private:
    ADXL345* adxlLib;


};


#endif  //ADXL_HPP
