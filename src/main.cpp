/**  flora8 board from pio library
 *
 * main.cpp
 * Created 05-24-17 By: Smitty
 *
 * A longer description.
 */

#include <Arduino.h>
#include <Wire.h>

// #include <EEPROM24.h>

#define EEPROM24_ADDR B10100000



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


    //EEPROM read
    uint8_t i2c_addr = EEPROM24_ADDR;
    uint16_t addressToRead = 0;
    uint8_t i2c_status = 0;
    int ee_out = 0;
    uint8_t dataToWrite = 0xBE;
    

    // seven-bit address
    i2c_addr >>= 1;

    Wire.beginTransmission(i2c_addr);
    Wire.write( (uint8_t) addressToRead >> 8 );
    Wire.write( (uint8_t) (addressToRead & 0x00FF) );
    
    // check status
    i2c_status = Wire.endTransmission();

    if( i2c_status == 0 ) 
    {  
        Wire.requestFrom(i2c_addr, 1);

        while( Wire.available() )
            ee_out = Wire.read();
    }
    else 
    {  
        ee_out = -1;
    } 
    //end EEPROM read


    Serial.print("Current data: ");
    Serial.println(ee_out, HEX);


    //EEPROM Write
    // i2c commands
    Wire.beginTransmission(i2c_addr);

    Wire.write( (uint8_t) addressToRead >> 8 );
    Wire.write( (uint8_t) (addressToRead & 0x00FF) );
    Wire.write( dataToWrite );
    
    Wire.endTransmission();
    //end EEPROM Write


    //EEPROM read
    delay(5);
    Wire.beginTransmission(i2c_addr);
    Wire.write( (uint8_t) addressToRead >> 8 );
    Wire.write( (uint8_t) (addressToRead & 0x00FF) );
    
    // check status
    i2c_status = Wire.endTransmission();

    if( i2c_status == 0 ) 
    {  
        Wire.requestFrom(i2c_addr, 1);

        while( Wire.available() )
            ee_out = Wire.read();
    }
    else 
    {  
        ee_out = -1;
    } 
    //end EEPROM read


    Serial.print("new data: ");
    Serial.println(ee_out, HEX);

    while(1)
    {
        // wait before the next loop
        delay(5000);
    }


    return 0;
}