/**  Model for the EEPROM (24fc1025) chip
 *
 * #include "Eeprom.hpp"
 * Created 05-25-18  By: Smitty
 *
 * A longer description.
 */

#ifndef EEPROM_HPP
#define EEPROM_HPP

#include <Wire.h>
#include <Arduino.h>

const uint8_t EEPROM24_ADDR = B10100000 >> 1;    // seven-bit address of the chip
const uint8_t BYTES_PER_PAGE = 128;


class Eeprom
{
public:
    //TODO: add the EEPROM IDs of the registers

    ~Eeprom(void);
    static Eeprom*   getInstance();
    void init();

    int readByte(uint16_t readAddress);
    int writeByte(uint16_t writeAddress, uint8_t writeData);

    int readSequential(uint16_t startAddress, uint16_t endAddress, uint8_t* data);
    int writeSequential(uint16_t startAddress, uint16_t endAddress, uint8_t* writeData);

    void test();

private:
    //Private contstructor so that it can't be called
    Eeprom() {};
    //copy constructor is private
    Eeprom(Eeprom const&) {};
    //static instance pointer
    static Eeprom* _pInstance;

    uint8_t _lastAddressAccessed;


};


#endif  //I2C_HPP
