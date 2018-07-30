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


class Rtc
{
public:
    ~Rtc(void);
    static Rtc*   getInstance();
    void init(void);

    /** 
     * Drafting up possible functions
     * 
     * getDate()
     * getTime()
     * getDateTime()
     */

    //TODO: make alarm handling functions for the RTC

private:
    //Private contstructor so that it can't be called
    Rtc() {};
    //copy constructor is private
    Rtc(Rtc const&) {};
    //static instance pointer
    static Rtc* _pInstance;

    MCP7940_Class* mcp7940Lib;
    
};


#endif  //RTC_HPP