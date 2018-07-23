/**  Display model class
 *
 * Oled.cpp
 * Created 05-24-18 By: Smitty
 *
 * A longer description.
 */

#include "Oled.hpp"


//to see if the instance of the class has been initialized yet
Oled* Oled::_pInstance = NULL; 

/** 
 * @brief  Used to maintain the singleton format
 * @note   
 * @retval 
 */
Oled* Oled::getInstance()
{
    // Only allow one instance of class to be generated.
    if (!_pInstance)
        _pInstance = new Oled();

    return _pInstance;
}


/** 
 * @brief  
 * @note   
 * @retval 
 */
void Oled::init(void)
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
