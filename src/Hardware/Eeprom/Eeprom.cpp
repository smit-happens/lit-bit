/**  Model for the EEPROM (24fc1025) chip
 *
 * Eeprom.cpp
 * Created 05-25-18  By: Smitty
 *
 * A longer description.
 */

#include "Eeprom.hpp"


//to see if the instance of the class has been initialized yet
Eeprom* Eeprom::_pInstance = NULL; 

/** 
 * @brief  Used to maintain the singleton format
 * @note   
 * @retval 
 */
Eeprom* Eeprom::getInstance()
{
    // Only allow one instance of class to be generated.
    if (!_pInstance)
        _pInstance = new Eeprom();

    return _pInstance;
}


/** 
 * @brief  
 * @note   
 * @retval 
 */
void Eeprom::init(void)
{
    //retreive address of teh last entry written to EEPROM
    _lastAddressAccessed = (readByte(0x1FFFF) << 8) | readByte(0x1FFFD);
    
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


uint8_t Eeprom::readByte(uint16_t readAddress)
{
    uint8_t readData;
    
    //start comms with EEPROM
    Wire.beginTransmission(EEPROM24_ADDR);

    //EEPROM address to read from
    Wire.write( (uint8_t) readAddress >> 8 );
    Wire.write( (uint8_t) (readAddress & 0x00FF) );
    
    // check status (0 is success)
    if( Wire.endTransmission() == 0 ) 
    {
        //request reading from the address for the data we want
        Wire.requestFrom(EEPROM24_ADDR, 1);

        while( Wire.available() )
            readData = Wire.read();
    }

    return readData;
}


int Eeprom::readSequential(uint16_t startAddress, uint16_t endAddress, uint8_t* data)
{
    //0 is success
    int error = 0;
    int rangeAmount = endAddress - startAddress +1;

    //don't progress if there's a range of zero or lower
    if(rangeAmount <= 0)
    {
        //out of range error
        error = -1;
    }
    else
    {
        //start comms with EEPROM
        Wire.beginTransmission(EEPROM24_ADDR);

        //EEPROM address to write to
        Wire.write( (uint8_t) startAddress >> 8 );
        Wire.write( (uint8_t) (startAddress & 0x00FF) );
    }

    // check status (0 is success)
    if( Wire.endTransmission() == 0 ) 
    {
        //request reading from the addresses in our range
        Wire.requestFrom(EEPROM24_ADDR, rangeAmount);

        for(int i = 0; i < rangeAmount; i++)
        {
            //read byte
            data[i] = Wire.read();
        }
    }
    else 
    {  
        error = -1;
    }

    return error;
}


int Eeprom::writeSequential(uint16_t startAddress, uint16_t endAddress, uint8_t* writeData)
{
    //0 is success
    int error = 0;
    int rangeAmount = endAddress - startAddress +1;

    //don't progress if there's a range of zero or lower or more than a page (128 bytes)
    if(rangeAmount <= 0 || rangeAmount > 128)
    {
        //out of range error
        error = -1;
    }
    else
    {
        //start comms with EEPROM
        Wire.beginTransmission(EEPROM24_ADDR);

        //EEPROM address to write to
        Wire.write( (uint8_t) startAddress >> 8 );
        Wire.write( (uint8_t) (startAddress & 0x00FF) );
    }

    //send data to the page buffer in the Eeprom
    for(int i = 0; i < rangeAmount; i++)
    {
        Wire.write(writeData[i]);
    }

    error = Wire.endTransmission();

    delay(5);       //need to wait for the EEPROM chip to finish writing

    return error;
}


void Eeprom::writeEntry(uint32_t* unixtime, uint16_t* steps)
{
    //zero initialize data array
    uint8_t data[6] = { 0 };

    data[0] = *unixtime >> 24;
    data[1] = *unixtime >> 16;
    data[2] = *unixtime >> 8;
    data[3] = *unixtime;

    data[4] = *steps >> 8;
    data[5] = *steps;

    uint16_t startAddress = _lastAddressAccessed + 1;
    uint16_t endAddress = startAddress + 6;

    writeSequential(startAddress, endAddress, data);

    _lastAddressAccessed = endAddress;

    //store last address accessed to EEPROM
    writeByte(0x1FFFF, _lastAddressAccessed >> 8);
    writeByte(0x1FFFD, _lastAddressAccessed);

}


void Eeprom::printEntry(int entry)
{
    //zero initialize data array
    uint8_t data[6] = { 0 };

    uint8_t start = 0 + entry;
    uint8_t end = 5 + entry;

    readSequential(start, end, data);

    uint32_t unixNow = data[0] << 24 | data[1] << 16 | data[2] << 8 | data[3];

    uint16_t steps = data[4] << 8 | data[5];

    Serial.print("time: ");
    Serial.println(unixNow);

    Serial.print("steps: ");
    Serial.println(steps);

}


uint16_t Eeprom::getTotalSteps()
{
    uint16_t totalSteps = (readByte(0x1FFFB) << 8) | readByte(0x1FFF9);

    return totalSteps;
}


void Eeprom::setTotalSteps(uint16_t steps)
{
    writeByte(0x1FFFB, steps >> 8);
    writeByte(0x1FFF9, steps);
}


void Eeprom::addTotalSteps(uint16_t steps)
{
    setTotalSteps(getTotalSteps() + steps);
}


void Eeprom::test(void)
{
    uint8_t array[5], buffer[5];
    for(int i = 0; i < 5; i++)
    {
        array[i] = random();
    }

    writeSequential(0, 4, array);

    readSequential(0, 4, buffer);

    bool testPass = true;
    for(int i = 0; i < 5; i++)
    {
        Serial.println(array[i]);
        Serial.println(buffer[i]);
        
        if(buffer[i] != array[i])
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
}