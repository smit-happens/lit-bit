/**  MCP7940 RTC controller class
 *
 * #include "RtcController.hpp"
 * Created 05-24-18 By: Smitty
 *
 * A longer description.
 */

#ifndef RTCCONTROLLER_HPP
#define RTCCONTROLLER_HPP

#include "../BaseController/BaseController.hpp"
#include "../../Model/Rtc/Rtc.hpp"


class RtcController : public BaseController
{
public:
    ~RtcController(void);

    static RtcController*   getInstance();

    void init(void);


private:
    //Private contstructor so that it can't be called
    RtcController() {};

    //copy constructor is private
    RtcController(RtcController const&) {};

    //static instance pointer
    static RtcController* _pInstance;


    //private instance of model
    Rtc* rtcModel;
    
};


#endif  //RTCCONTROLLER_HPP
