/**  Handles the setup and usage of the MCP7940N RTC
 *
 * #include "Rtc.hpp"
 * Created 05-24-18  By: Smitty
 *
 * A longer description.
 */


#ifndef RTC_HPP
#define RTC_HPP

#include "../BaseModel/BaseModel.hpp"
#include <MCP7940.h>


class Rtc : public BaseModel
{
public:
    Rtc(void);
    ~Rtc(void);

    /** 
     * Drafting up possible functions
     * 
     * getDate()
     * getTime()
     * getDateTime()
     */

    //TODO: make alarm handling functions for the RTC

private:
    MCP7940_Class* mcp7940Lib;
    
};


#endif  //RTC_HPP
