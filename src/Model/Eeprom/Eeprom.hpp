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


class Eeprom : public BaseModel
{
public:
    //TODO: add the EEPROM IDs of the registers

    Eeprom(void);
    ~Eeprom(void);
    

private:



};


#endif  //I2C_HPP
