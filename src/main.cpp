/**  flora8 board from pio library
 *
 * main.cpp
 * Created 05-24-17 By: Smitty
 *
 * A longer description.
 */

#include <Arduino.h>
#include <Wire.h>

#include <EEPROM24.h>




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
  

    Wire.begin();
    Wire.setClock(400000L); //set I2C clock to 400kHz


    //EEPROM class init
    EEPROM24 eeprom = EEPROM24();
    


    uint8_t temp = eeprom.read(0);

    Serial.print("Current data: ");
    Serial.println(temp, HEX);

    temp = 0xDE;

    eeprom.write(0, temp);

    uint8_t newData = eeprom.read(0);

    Serial.print("Current data: ");
    Serial.println(newData, HEX);


    // eeprom.read(0);

    // example: uint8_ts to be read with a single loop
    #define READ_BYTES 32

    // example: using one chip max address is 2^17 => 1024K
    #define ADDR_BOUNDARY 131072

    unsigned int curr_addr = 0;
    

    while(1)
    {
        Serial.print("eeprom[");
        Serial.print(curr_addr, HEX);
        Serial.println("]:");
        
        // eeprom read loop
        for(int i = 0; i < READ_BYTES; i++) {
            uint8_t re = (uint8_t) eeprom.read(curr_addr);
            
            Serial.print(re, HEX);
            Serial.print(' ');
        
            curr_addr += 1;

            if(curr_addr > ADDR_BOUNDARY)
                curr_addr = 0;
        }
        
        Serial.println(' ');

        // wait before the next loop
        delay(5000);
    }


    return 0;
}