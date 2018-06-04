/**  Model for the EEPROM (24fc1025) chip
 *
 * #include "Eeprom.hpp"
 * Created 05-25-18  By: Smitty
 *
 * A longer description.
 */

#ifndef EEPROM_HPP
#define EEPROM_HPP

#include "../BaseModel/BaseModel.hpp"
#include "../Constants/Flags.hpp"
#include <Wire.h>


const uint8_t EEPROM24_ADDR = B10100000 >> 1;    // seven-bit address of the chip
const uint8_t BYTES_PER_PAGE = 128;


class Eeprom : public BaseModel
{
public:
    //TODO: add the EEPROM IDs of the registers

    Eeprom(void);
    ~Eeprom(void);

    int readByte(uint16_t readAddress);
    int writeByte(uint16_t writeAddress, uint8_t writeData);

    int readPage();
    int writePage();

    int readCurrent();
    int readSequential(uint16_t startAddress, uint16_t endAddress, uint8_t* data);
    int readRandom(uint16_t readAddress);    

private:
    uint8_t _lastAddressAccessed;


};


#endif  //I2C_HPP
