/**  Display model class
 *
 * Oled.cpp
 * Created 05-24-18 By: Smitty
 *
 * A longer description.
 */

#include "Oled.hpp"


/** 
 * @brief  Oled constructor
 */
Oled::Oled(void)
{
    //initialize the oled library
    display = new MicroOLED(PIN_RESET, DC_JUMPER);

    // initialize the glcd and set the contrast to 0x18
    display->begin();       // Initialize the OLED
    display->clear(ALL);    // Clear the display's internal memory
    display->display();     // Display what's in the buffer (splashscreen)
    delay(1000);            // Delay 1000 ms
    display->clear(PAGE);   // Clear the buffer.
}


/** 
 * @brief  Oled destructor
 */
Oled::~Oled(void)
{
    // delete display;      //deleting object of polymorphic class type warning
}
