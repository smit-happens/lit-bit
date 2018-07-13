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
#include "../BaseModel/BaseModel.hpp"
#include "../Constants/Port.hpp"
#include "../Constants/Constants.hpp"


class Oled : public BaseModel
{
public:
    MicroOLED *display;

    Oled(void);
    ~Oled(void);


private:

};


#endif  //OLED_HPP
