/**  Represents the Model of an I2C message
 *
 * #include "I2c.hpp"
 * Created 05-24-18  By: Smitty
 *
 * A longer description.
 */

#ifndef I2C_HPP
#define I2C_HPP

#include <Wire.h>


class I2c
{
public:
    ~I2c(void);
    static I2c*   getInstance();
    void init(void);
    

private:
    //Private contstructor so that it can't be called
    I2c() {};
    //copy constructor is private
    I2c(I2c const&) {};
    //static instance pointer
    static I2c* _pInstance;


};


#endif  //I2C_HPP
