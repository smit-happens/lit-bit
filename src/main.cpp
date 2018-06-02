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
#include <avr/interrupt.h>
#include <avr/power.h>

//External libraries
#include <SparkFun_ADXL345.h>
#include <MCP7940.h>

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

    Serial.begin(9600);
    while (!Serial) {
        ; // wait for serial port to connect
    }

    delay(500);

    //status LED
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);

    //ADXL initialization
    ADXL345 adxl = ADXL345();

    //RTC class init
    MCP7940_Class MCP7940 = MCP7940_Class();


    // Power on the ADXL345
    adxl.powerOn();

    //ADXL testing code

    double xyz[3];

    adxl.get_Gxyz(xyz);

    Serial.print("x = ");
    Serial.println(xyz[0]);
    Serial.print("y = ");
    Serial.println(xyz[1]);
    Serial.print("z = ");
    Serial.println(xyz[2]);
    
    // adxl.printAllRegister();


    //RTC testing code
    //start the RTC
    MCP7940.begin();
    Serial.println(F("MCP7940 initialized."));

    // Turn oscillator on if necessary
    while (!MCP7940.deviceStatus())  //check if it's off
    {
        Serial.println(F("Oscillator is off, turning it on."));
        MCP7940.deviceStart();

    }

    // Set to library compile Date/Time
    MCP7940.adjust();
    
    //display the time and date
    Serial.println(MCP7940.now().month());
    Serial.println(MCP7940.now().day());
    Serial.println(MCP7940.now().year());


    //TODO: EEPROM testing
    

    // power_all_disable();

    //set the desired sleep mode
    // set_sleep_mode(SLEEP_MODE_PWR_DOWN);

    //stop interrupts (execute atomically)
    // cli();

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
    while(1)
    {
        noInterrupts();
        
        //Volatile operation for transferring flags from ISRs to local main
        localEventFlags |= globalEventFlags;
        globalEventFlags = 0;

        interrupts();

        
        //transfering timer event flags to local EF
        localEventFlags |= timerEventFlags << 8;



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