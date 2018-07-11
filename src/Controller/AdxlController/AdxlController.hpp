/**  Adxl controller class
 *
 * #include "AdxlController.hpp"
 * Created 06-02-18 By: Smitty
 *
 * A longer description.
 */

#ifndef ADXLCONTROLLER_HPP
#define ADXLCONTROLLER_HPP

#include "../BaseController/BaseController.hpp"
#include "../../Model/Adxl/Adxl.hpp"


class AdxlController : public BaseController
{
public:
    ~AdxlController(void);
    static AdxlController*   getInstance();

    void init(void);

    void getInterruptSource(void);

    int getMagnitude(void);


private:
    //Private contstructor so that it can't be called
    AdxlController() {};

    //copy constructor is private
    AdxlController(AdxlController const&) {};

    //static instance pointer
    static AdxlController* _pInstance;


    //private instance of model
    Adxl* adxlModel;
    
};


#endif  //ADXLCONTROLLER_HPP
