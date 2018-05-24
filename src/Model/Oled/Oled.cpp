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

    // display = new U8G2_ST7565_LM6059_F_4W_SW_SPI(U8G2_R0, MB_SCLK, MB_SID, MB_CS, MB_A0, MB_RST);

    // initialize the glcd and set the contrast to 0x18
    // display->begin();
    // display->clearBuffer();
    // display->setContrast(130);
    
}



/** 
 * @brief  Oled destructor
 */
Oled::~Oled(void)
{
    //delete display;
}

