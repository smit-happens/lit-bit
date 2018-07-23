/**  flora8 board from pio library
 *
 * main.cpp
 * Created 05-24-17 By: Smitty
 *
 * A longer description.
 */

#include <Arduino.h>
#include <TimerOne.h>

//AVR library imports
#include <avr/sleep.h>
#include <avr/power.h>      //reference: https://www.nongnu.org/avr-libc/user-manual/group__avr__power.html

#include "StageManager/StageManager.hpp"


//global variable that all the ISRs will flag for their respective event to run
volatile uint16_t globalEventFlags = 0;
uint8_t globalTaskFlags [DEVICE_NUM] = { 0 };

//BLE global transfer variables
//possible to do this with ACI as well
uint8_t* globalBleBuffer;
uint8_t globalBleBufferLength;


//Start of ISR declarations
void timerISR() {
    globalEventFlags        |= EF_TIMER;
}

//All the adxl interrupts go here
//NOTE: might need logic to grab what interrupt was triggered
void adxlISR() {
    globalEventFlags        |= EF_ADXL;
}

//BLE ACI change handler (ignore the aci event, we'll grab that later)
void BleAciISR(aci_evt_opcode_t) {
    globalEventFlags                |= EF_BLE;
    globalTaskFlags[DEVICE_BLE]     |= TF_BLE_ACI;
}

//BLE RX handler
void BleRxISR(uint8_t *buffer, uint8_t len) {
    globalEventFlags                |= EF_BLE;
    globalTaskFlags[DEVICE_BLE]     |= TF_BLE_RX;

    //storing data
    globalBleBuffer = buffer;
    globalBleBufferLength = len;
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
    // while (!Serial) {
    //     ; // wait for serial port to connect
    // }

    delay(500);

    //status LED
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);

    power_all_disable();
    power_spi_enable();
    power_twi_enable();
    power_timer0_enable();
    power_timer1_enable();
    #ifdef DEBUG
        power_usb_enable();
    #endif

    //controller initialization
    I2c* i2c          = I2c::getInstance();             //start the I2 first
    Eeprom* eeprom    = Eeprom::getInstance();
    Rtc* rtc          = Rtc::getInstance();
    Adxl* adxl        = Adxl::getInstance();
    Oled* oled        = Oled::getInstance();
    Bluetooth* ble    = Bluetooth::getInstance();

    i2c->init();       //initialize I2 first
    eeprom->init();
    rtc->init();
    adxl->init();
    oled->init();
    ble->init();

    //setup BLE
    ble->bluetooth->setRXcallback(BleRxISR);
    ble->bluetooth->setACIcallback(BleAciISR); //grabbing the reference of the function
    ble->bluetooth->setDeviceName("LIT BIT"); /* 7 characters max! */
    ble->bluetooth->begin();


    /*
            _   _             _     _                _       _                             _
       __ _| |_| |_ __ _  ___| |__ (_)_ __   __ _   (_)_ __ | |_ ___ _ __ _ __ _   _ _ __ | |_ ___
      / _` | __| __/ _` |/ __| '_ \| | '_ \ / _` |  | | '_ \| __/ _ \ '__| '__| | | | '_ \| __/ __|
     | (_| | |_| || (_| | (__| | | | | | | | (_| |  | | | | | ||  __/ |  | |  | |_| | |_) | |_\__ \
      \__,_|\__|\__\__,_|\___|_| |_|_|_| |_|\__, |  |_|_| |_|\__\___|_|  |_|   \__,_| .__/ \__|___/
                                            |___/                                   |_|
    */
    //Adxl interrupt
    // attachInterrupt(LB_ADXL_INT1, adxlISR, RISING);

    //start timer
    Timer1.initialize(1000);    //in usec
    Timer1.attachInterrupt(timerISR);

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
    uint8_t localTaskFlags[DEVICE_NUM] = { 0 };

    //---------------------------------------------------------------
    // Begin main program Super Loop
    while(true)
    {
        noInterrupts();
        
        //Volatile operation for transferring flags from ISRs to local main
        localEventFlags |= globalEventFlags;
        globalEventFlags = 0;

        // Tell the nRF8001 to do whatever it should be working on.
        // AKA update the bluetooth ACI state
        ble->bluetooth->pollACI();

        //check if we have new data in the BLE buffer
        if((globalEventFlags & EF_BLE) && (globalTaskFlags[DEVICE_BLE] & TF_BLE_RX))
        {
            ble->localBleBuffer = globalBleBuffer;
            ble->localBleBufferLength = globalBleBufferLength;
        }

        //clearing global task flags for every device
        for(int i = 0; i < Device::DEVICE_NUM; i++ )
        {
            localTaskFlags[i] |= globalTaskFlags[i];
            globalTaskFlags[i] = 0;
        }

        interrupts();

        //transfering timer event flags to local EF
        localEventFlags |= timerEventFlags << 8;


        //processing stage returns the next stage
        localStage.processStage(&localEventFlags, localTaskFlags);

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