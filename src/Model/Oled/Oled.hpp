/**  Display model class
 *
 * #include "Oled.hpp"
 * Created 05-24-18 By: Smitty
 *
 * Controls a graphical LCD from here: https://www.adafruit.com/product/250
 */

#ifndef OLED_HPP
#define OLED_HPP

// #include <U8g2lib.h>
#include <SFE_MicroOLED.h>
#include "../BaseModel/BaseModel.hpp"
#include "../Constants/Port.hpp"
#include "../Constants/Constants.hpp"




class Oled : public BaseModel
{
public:
    Oled(void);
    ~Oled(void);



private:
    bool dirtyBit = false; //if buffer has been modified

    //private instance of the ST7565 object for our GLCD
    //  U8G2_SSD1306_64X48_ER_F_HW_I2C* display;


};


#endif  //OLED_HPP
