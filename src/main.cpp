/**  flora8 board from pio library
 *
 * main.cpp
 * Created 05-24-17 By: Smitty
 *
 * A longer description.
 */

#include <Arduino.h>

//External libraries
#include <SparkFun_ADXL345.h>
#include <MCP7940.h>
#include <EEPROM24.h>


/**
 * Function writes a series of uint16_t values to the EEPROM
 * from the data array. Length of array is specified by the len parameter.
 * All writing is assumed to occur at EEPROM storage address 0x0.
 * Any existing data should be overwritten.
 */
void writeDataToEEPROM(EEPROM24* eeprom, uint16_t* data, uint16_t len)
{
    for(uint16_t i = 0; i < len; i++)
    {
        eeprom->write(i, data[i]); 
        Serial.println();
    }
}

/**
 * Function reads a sequence of uint16_t values from the EEPROM
 * and stores the result in the buffer array. Length of buffer is
 * specified by the len parameter. All reads are assumed to begin at EEPROM storage
 * address 0x0.
 */
void readDataFromEEPROM(EEPROM24* eeprom, uint16_t* buffer, uint16_t len)
{
    for(uint16_t i = 0; i < len; i++)
        buffer[i] = eeprom->read(i);
}


int main(void)
{
    //initialize board for arduino functionality
    init();

    //attach USB for our processor
    #ifdef USBCON
        USBDevice.attach();
    #endif

    //start the USB serial connection speed
    Serial.begin(9600);
    while (!Serial) {
        ; // wait for serial port to connect
    }

    //status LED
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);
  

    /**
     * Configure the ADXL345
     */
    
    //ADXL initialization
    ADXL345 adxl = ADXL345();
    
    // Power on the ADXL345
    adxl.powerOn();

    //array to store x/y/z readings
    int xyz[3];


    /**
     * Initialize configuration data for the RTC. Modify
     * the contents of the initConfig object such that the
     * RTC will begin with the correct values
     */
    //RTC class init
    MCP7940_Class MCP7940 = MCP7940_Class();

    //start the RTC
    MCP7940.begin();
    Serial.println(F("MCP7940 initialized."));

    // Turn oscillator on if necessary
    while (!MCP7940.deviceStatus()) {
        Serial.println(F("Oscillator is off, turning it on."));
        MCP7940.deviceStart();
    }

    // Set to library compile Date/Time
    MCP7940.adjust();


    /**
     * Initialize the EEPROM
     */
    //EEPROM class init
    EEPROM24 eeprom = EEPROM24();
    

    //---------------------------------------------------------------
    // Begin main program Super Loop
    while(1)
    {
        /**
         * Test #1: Try to read from the ADXL345 and
         * print out the results
         */
        // readADXL(&currentReading);

        //polling the Accelerometer for the x/y/z data
        adxl.readAccel(xyz);

        Serial.print(xyz[0]);
        Serial.print("\t");
        Serial.print(xyz[1]);
        Serial.print("\t");
        Serial.println(xyz[2]);


        /**
         * Test #2: Try to read out the time of day and
         * print out the results
         */
        // readRTC(&currentDateTime);
        DateTime rightNow = MCP7940.now();      //reading the current time from the RTC
        Serial.print(rightNow.month());
        Serial.print("/");
        Serial.print(rightNow.day());
        Serial.print("/");
        Serial.print(rightNow.year());
        Serial.print("\t");
        Serial.print(rightNow.hour());
        Serial.print(":");
        Serial.print(rightNow.minute());
        Serial.print(":");
        Serial.println(rightNow.second());

        /**
        * Test #3: Try to write and read back some
        * random data
        */
        uint16_t array[5];
        for(int i=0;i<5;i++)
        {
            array[i] = random();
        }
        writeDataToEEPROM(&eeprom, array, 5);

        uint16_t buffer[5];

        readDataFromEEPROM(&eeprom, buffer, 5);
        
        bool testPass = true;
        for(int i=0;i<5;i++)
        {
            if(buffer[i]!=array[i])
            {
                testPass=false;
            }
        }
        
        if(testPass)
        {
            Serial.println("EEPROM Test Passed.");
        }
        else
        {
            Serial.println("EEPROM Test Failed.");
        }

        delay(1000);
        
    } //end while()

    return 0;
}