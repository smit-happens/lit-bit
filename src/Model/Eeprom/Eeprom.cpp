/**  Model for the EEPROM (24fc1025) chip
 *
 * Eeprom.cpp
 * Created 05-25-18  By: Smitty
 *
 * A longer description.
 */

#include "Eeprom.hpp"

/** 
 * @brief  Eeprom constructor
 */
Eeprom::Eeprom(void)
{

}


/** 
 * @brief  Eeprom destructor
 */
Eeprom::~Eeprom(void)
{

}


int Eeprom::writeByte(uint16_t writeAddress, uint8_t writeData)
{
    int result;
    
    //writing
    Wire.beginTransmission(EEPROM24_ADDR);

    //EEPROM address to write to
    Wire.write( (uint8_t) writeAddress >> 8 );
    Wire.write( (uint8_t) (writeAddress & 0x00FF) );
    Wire.write(writeData);
    
    result = Wire.endTransmission();

    delay(5);       //need to wait for the EEPROM chip to finish writing

    return result;
}


int Eeprom::readByte(uint16_t readAddress)
{
    int readData;
    
    //start comms with EEPROM
    Wire.beginTransmission(EEPROM24_ADDR);

    //EEPROM address to read from
    Wire.write( (uint8_t) readAddress >> 8 );
    Wire.write( (uint8_t) (readAddress & 0x00FF) );
    
    // check status (0 is success)
    if( Wire.endTransmission() == 0 ) 
    {
        //request reading from the address for the MSB
        Wire.requestFrom(EEPROM24_ADDR, 1);

        while( Wire.available() )
            readData = Wire.read();
    }
    else 
    {  
        readData = -1;     //error
    }

    return readData;
}


int Eeprom::readSequential(uint16_t startAddress, uint16_t endAddress, uint8_t* data)
{
    //0 is success
    int result = 0;

    if(endAddress - startAddress < 0)
    {
        //out of range error
        result = -1;
    }
    else
    {
        //start comms with EEPROM
        Wire.beginTransmission(EEPROM24_ADDR);

        //EEPROM address to write to
        Wire.write( (uint8_t) startAddress >> 8 );
        Wire.write( (uint8_t) (startAddress & 0x00FF) );
    }
    
    return result;
}