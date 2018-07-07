/**  flora8 board from pio library
 *
 * main.cpp
 * Created 05-24-17 By: Smitty
 *
 * A longer description.
 */

#include <Arduino.h>

//AVR library imports
#include <avr/sleep.h>
#include <avr/power.h>      //reference: https://www.nongnu.org/avr-libc/user-manual/group__avr__power.html

#include "StageManager/StageManager.hpp"


//global variable that all the ISRs will flag for their respective event to run
volatile uint32_t globalEventFlags = 0;
uint8_t globalTaskFlags [NUM_DEVICES] = { 0 };


//Start of ISR declarations
void timerISR() {
    globalEventFlags        |= EF_TIMER;
}


int main(void)
{
    //initialize board for arduino functionality
    init();

    //attach USB for our processor
    #ifdef USBCON
        USBDevice.attach();
    #endif

    Serial.begin(115200);
    while (!Serial) {
        ; // wait for serial port to connect
    }

    delay(500);

    //status LED
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);

    power_all_disable();
    power_spi_enable();
    power_twi_enable();
    power_timer0_enable();
    #ifdef DEBUG
        power_usb_enable();
    #endif

    //controller initialization
    I2cController* i2cC          = I2cController::getInstance();             //start the I2C first
    EepromController* eepromC    = EepromController::getInstance();
    RtcController* rtcC          = RtcController::getInstance();
    AdxlController* adxlC        = AdxlController::getInstance();
    OledController* oledC        = OledController::getInstance();
    BleController* bleC          = BleController::getInstance();

    i2cC->init();       //initialize I2C first
    eepromC->init();
    rtcC->init();
    adxlC->init();
    oledC->init();
    bleC->init();


    //set the desired sleep mode
    // set_sleep_mode(SLEEP_MODE_PWR_DOWN);

    //enable sleep mode by setting the sleep bit
    // sleep_enable();

    //execute the sleep instruction and actually go to sleep
    // sleep_cpu();

    // clock_prescale_set(clock_div_2);


    //local instance of the Stage manager class
    StageManager localStage = StageManager();

    //initialize the local and timer event flag variables
    uint16_t localEventFlags = 0;
    uint8_t timerEventFlags = 0;

    //initialize task flag array to zero
    uint8_t localTaskFlags[NUM_DEVICES] = { 0 };

    //---------------------------------------------------------------
    // Begin main program Super Loop
    while(true)
    {
        noInterrupts();
        
        //Volatile operation for transferring flags from ISRs to local main
        localEventFlags |= globalEventFlags;
        globalEventFlags = 0;

        interrupts();

        
        //transfering timer event flags to local EF
        localEventFlags |= timerEventFlags << 8;


        //processing stage returns the next stage
        localStage.currentStage = localStage.processStage(&localEventFlags, localTaskFlags);

        //checking if we need to update the timers
        if(localEventFlags & EF_TIMER)
        {
            //bit shifting the timer Task Flags (TFs) to the upper half of the localEF var
            timerEventFlags |= localStage.processTimers();
            
            //clearing the EF so we don't trigger this again
            localEventFlags &= ~EF_TIMER;
        }

    } //end while()

    return 0;
}