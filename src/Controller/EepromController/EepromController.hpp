/**  Eeprom controller class
 *
 * #include "EepromController.hpp"
 * Created 05-26-18 By: Smitty
 *
 * A longer description.
 */

#ifndef EEPROMCONTROLLER_HPP
#define EEPROMCONTROLLER_HPP

#include "../BaseController/BaseController.hpp"
#include "../../Model/Eeprom/Eeprom.hpp"


class EepromController : public BaseController
{
public:
    ~EepromController(void);
    static EepromController*   getInstance();
    void init(void);

    void read();
    void write();


private:
    //Private contstructor so that it can't be called
    EepromController() {};

    //copy constructor is private
    EepromController(EepromController const&) {};

    //static instance pointer
    static EepromController* _pInstance;


    //private instance of model
    Eeprom* eepromModel;
    
};


#endif  //EEPROMCONTROLLER_HPP
