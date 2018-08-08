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
volatile uint8_t globalEventFlags = 0;
uint8_t globalTaskFlags [DEVICE_NUM] = { 0 };


//Start of ISR declarations
void timerISR() {
    globalEventFlags        |= EF_TIMER;
}

//All the adxl interrupts go here
//NOTE: might need logic to grab what interrupt was triggered
void adxlISR() {
    globalEventFlags        |= EF_ADXL;
}

//configure rtc MFP interrupt
void rtcISR() {
    globalEventFlags        |= EF_RTC;
}

//watchdog interrupt
ISR(WDT_vect) {
    globalEventFlags                |= EF_OLED;
    globalTaskFlags[DEVICE_OLED]    |= TF_OLED_TIMEOUT;

    //resetting the Watchdog bit so we don't reset
    WDTCSR |= 0x1 << 6;
}


int main(void)
{
    //initialize board for arduino functionality
    init();

    //attach USB for our processor
    #ifdef USBCON
        USBDevice.attach();
    #endif

    #ifdef DEBUG
        Serial.begin(9600);
        // while (!Serial) {
        //     ; // wait for serial port to connect
        // }
    #endif


    //disabling everything that I don't need
    power_all_disable();
    power_twi_enable();
    power_timer0_enable();
    #ifdef DEBUG
        power_usb_enable();
    #endif

    //setting the clock to full (b/c reasons)
    clock_prescale_set(clock_div_1);

    //controller initialization
    I2c* i2c          = I2c::getInstance();             //start the I2 first
    Eeprom* eeprom    = Eeprom::getInstance();
    Rtc* rtc          = Rtc::getInstance();
    Adxl* adxl        = Adxl::getInstance();
    Oled* oled        = Oled::getInstance();

    i2c->init();       //initialize I2 first
    eeprom->init();
    rtc->init();
    adxl->init();
    oled->init();

    //incase you need to reset stats
    // eeprom->writeByte(0x1FFFF, 0);
    // eeprom->writeByte(0x1FFFD, 0);
    // eeprom->writeByte(0x1FFFB, 0);
    // eeprom->writeByte(0x1FFF9, 0);


    /*
            _   _             _     _                _       _                             _
       __ _| |_| |_ __ _  ___| |__ (_)_ __   __ _   (_)_ __ | |_ ___ _ __ _ __ _   _ _ __ | |_ ___
      / _` | __| __/ _` |/ __| '_ \| | '_ \ / _` |  | | '_ \| __/ _ \ '__| '__| | | | '_ \| __/ __|
     | (_| | |_| || (_| | (__| | | | | | | | (_| |  | | | | | ||  __/ |  | |  | |_| | |_) | |_\__ \
      \__,_|\__|\__\__,_|\___|_| |_|_|_| |_|\__, |  |_|_| |_|\__\___|_|  |_|   \__,_| .__/ \__|___/
                                            |___/                                   |_|
    */
    // Adxl interrupt
    attachInterrupt(LB_ADXL_INT1, adxlISR, RISING);
    attachInterrupt(LB_RTC_MFP, rtcISR, RISING);


    // // set the desired sleep mode
    // set_sleep_mode(SLEEP_MODE_PWR_DOWN);

    // // enable sleep mode by setting the sleep bit
    // sleep_enable();

    // // execute the sleep instruction and actually go to sleep
    // sleep_cpu();

    // clock_prescale_set(clock_div_2);


    //local instance of the Stage manager class
    StageManager localStage = StageManager();

    //initialize the local event flag variable
    uint8_t localEventFlags = 0;

    //initialize task flag array to zero
    uint8_t localTaskFlags[DEVICE_NUM] = { 0 };

    //---------------------------------------------------------------
    // Begin main program Super Loop
    while(true)
    {
        noInterrupts();
        
        //Volatile operation for transferring flags from ISRs to local main
        localEventFlags |= globalEventFlags;
        globalEventFlags = 0;

        //clearing global task flags for every device
        for(int i = 0; i < Device::DEVICE_NUM; i++ )
        {
            localTaskFlags[i] |= globalTaskFlags[i];
            globalTaskFlags[i] = 0;
        }

        interrupts();


        //processing stage returns the next stage
        localStage.processStage(&localEventFlags, localTaskFlags);

    } //end while()

    return 0;
}