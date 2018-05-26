//flora8 board from pio library

#include <Arduino.h>

//AVR library imports
#include <avr/sleep.h>
#include <avr/interrupt.h>
#include <avr/power.h>


int main(void)
{
    //initialize board for arduino functionality
    init();

    //attach USB for our processor
    #ifdef USBCON
        USBDevice.attach();
    #endif

    Serial.begin(9600);
    while (!Serial) {
        ; // wait for serial port to connect
    }


    pinMode(LED_BUILTIN, OUTPUT);

    digitalWrite(LED_BUILTIN, HIGH);

    Serial.println("Hello Smitty!");

    delay(5);


    while(1)
    {
        // power_all_disable();

        //set the desired sleep mode
        set_sleep_mode(SLEEP_MODE_PWR_DOWN);

        //stop interrupts (execute atomically)
        cli();

        //enable sleep mode by setting the sleep bit
        sleep_enable();

        //execute the sleep instruction and actually go to sleep
        sleep_cpu();

        // clock_prescale_set(clock_div_2);
    }

    return 0;
}