/**  Represents the Model of a CAN message
 *
 * #include "I2c.hpp"
 * Created 05-24-18  By: Smitty
 *
 * A longer description.
 */

#ifndef I2C_HPP
#define I2C_HPP

#include "../BaseModel/BaseModel.hpp"
#include "../Constants/Flags.hpp"


class I2c : public BaseModel
{
public:
    //TODO: change these to the I2C IDs of the chips
    const uint32_t UNITEKREADID = 0x181;
    const uint32_t UNITEKSENDID = 0x201;

    const uint32_t ORIONID1 = 0x420;
    const uint32_t ORIONID2 = 0x421;

    I2c(void);
    ~I2c(void);
    

private:



};


#endif  //I2C_HPP
