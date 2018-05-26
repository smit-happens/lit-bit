/** Generic constant to be used across all models and constant
 * 
 * Created 05/24/18 By: Smitty
 * 
 */

#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

//Max analog read value
const int MAX_ANALOGREAD = 8195;    //(2^13)-1
const int MAX_BACKLIGHT_BR = 65535;


//types of log statements we can use
enum msg_type{
    MSG_LOG,
    MSG_DEBUG,
    MSG_WARN,
    MSG_ERR
};


enum Stage
{
    STAGE_BOOTTEST,
    STAGE_STANDBY,
    STAGE_PRECHARGE,
    STAGE_ENERGIZED,
    STAGE_DRIVING,
    STAGE_SHUTDOWN
};


#endif  //CONSTANTS_HPP