/**  Display controller class
 *
 * #include "OledController.hpp"
 * Created 05-24-18 By: Smitty
 *
 * A longer description.
 */

#ifndef OLEDCONTROLLER_HPP
#define OLEDCONTROLLER_HPP

#include "../BaseController/BaseController.hpp"
#include "../../Model/Oled/Oled.hpp"


class OledController : public BaseController
{
public:
    Oled* oledModel;

    ~OledController(void);
    static OledController*   getInstance();
    void init(void);


private:
    //Private contstructor so that it can't be called
    OledController() {};
    //copy constructor is private
    OledController(OledController const&) {};
    //static instance pointer
    static OledController* _pInstance;
};


#endif  //OLEDCONTROLLER_HPP
