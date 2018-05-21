//flora8 board from pio library

#include <Arduino.h>


int main(void)
{
    //initialize board for arduino functionality
    init();

    //attach USB for our processor
    #ifdef USBCON
        USBDevice.attach();
    #endif

    pinMode(LED_BUILTIN, OUTPUT);

    while(1)
    {
        digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
        delay(100);                       // wait for a second
        digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
        delay(100);                       // wait for a second
    }

    return 0;
}