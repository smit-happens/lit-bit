/**  I2c controller class
 *
 * #include "I2cController.hpp"
 * Created 05-26-18 By: Smitty
 *
 * A longer description.
 */

#ifndef I2CCONTROLLER_HPP
#define I2CCONTROLLER_HPP

#include "../BaseController/BaseController.hpp"
#include "../../Model/I2c/I2c.hpp"


class I2cController : public BaseController
{
public:
    ~I2cController(void);

    static I2cController*   getInstance();

    void init(void);


private:
    //Private contstructor so that it can't be called
    I2cController() {};

    //copy constructor is private
    I2cController(I2cController const&) {};

    //static instance pointer
    static I2cController* _pInstance;


    //private instance of model
    I2c* i2cModel;
    
};


#endif  //I2CCONTROLLER_HPP
