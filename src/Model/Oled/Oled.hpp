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

//The library assumes a reset pin is necessary. The Qwiic OLED has RST hard-wired, so pick an arbitrarty IO pin that is not being used
#define PIN_RESET 9  
//The DC_JUMPER is the I2C Address Select jumper. Set to 1 if the jumper is open (Default), or set to 0 if it's closed.
#define DC_JUMPER 1 


class Oled : public BaseModel
{
public:
    Oled(void);
    ~Oled(void);

    void lineExample();   // Then the line example function
    void shapeExample();  // Then the shape example
    void textExamples();  // Finally the text example

    void printTitle(String title, int font);


private:
    bool dirtyBit = false; //if buffer has been modified

    //private instance of the ST7565 object for our GLCD
    MicroOLED *display;    // I2C declaration


};


#endif  //OLED_HPP
