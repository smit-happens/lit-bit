/**  Central location of all the times for polling the timer driven devices
 *
 * #include TimeDelay.hpp
 * Created 05-24-18 By: Smitty
 * 
 * All times are in milliSeconds
 */

#ifndef TIMEDELAY_HPP
#define TIMEDELAY_HPP

#include <Arduino.h>


const int TIMER_NUM     = 1;    //number of timers in use

//waiting period for precharging Unitek
const int TIME_PRECHARGE    = 666;

//GLCD polling delay
const int POLL_TIME_GLCD    = 300;


#endif  //TIMEDELAY_HPP
