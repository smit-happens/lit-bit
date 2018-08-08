/**  Handles the setup and usage of the MCP7940N RTC
 *
 * #include "Rtc.hpp"
 * Created 05-24-18  By: Smitty
 *
 * A longer description.
 */


#ifndef RTC_HPP
#define RTC_HPP

#include <MCP7940.h>
#include "../Constants/Port.hpp"


class Rtc
{
public:
    MCP7940_Class* mcp7940Lib;

    // Enumeration of alarm types
    enum alarmTypes 
    { 
        matchSeconds, 
        matchMinutes, 
        matchHours, 
        matchDayOfWeek,
        matchDayOfMonth, 
        Unused1, 
        Unused2, 
        matchAll, 
        Unknown 
    };

    //FIXME: having it set for one minute for testing
    const uint8_t ALARM0_INTERVAL = 15;

    ~Rtc(void) {};
    static Rtc*   getInstance();
    void init(void);



private:
    //Private contstructor so that it can't be called
    Rtc() {};
    //copy constructor is private
    Rtc(Rtc const&) {};
    //static instance pointer
    static Rtc* _pInstance;    
};


#endif  //RTC_HPP
