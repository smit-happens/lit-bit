/**  Display model class
 *
 * #include "Oled.hpp"
 * Created 05-24-18 By: Smitty
 *
 * Controls a graphical LCD from here: https://www.adafruit.com/product/250
 */

#ifndef OLED_HPP
#define OLED_HPP

#include <SFE_MicroOLED.h>
#include "../Constants/Port.hpp"
#include "../Constants/Constants.hpp"


class Oled
{
public:
    MicroOLED *display;

    ~Oled(void) {};

    static Oled*   getInstance();
    void init(void);

    //sleeping functions 
    //Note: the display saves what's in its buffer when it sleeps/wakes up
    void sleep() { display->command(DISPLAYOFF); };
    void wakeUp() { display->command(DISPLAYON); };


private:
    //Private contstructor so that it can't be called
    Oled() {};
    //copy constructor is private
    Oled(Oled const&) {};
    //static instance pointer
    static Oled* _pInstance;
};


#endif  //OLED_HPP
