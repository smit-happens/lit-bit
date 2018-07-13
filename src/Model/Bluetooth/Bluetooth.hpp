/**  Handles the Bluetooth protocol library
 *
 * #include "Bluetooth.hpp"
 * Created 05-24-18 By: Smitty
 *
 * Controls the Nordic nrf8001 breakout from here: https://www.adafruit.com/product/1697
 */

#ifndef BLUETOOTH_HPP
#define BLUETOOTH_HPP

#include <Adafruit_BLE_UART.h>              //library from https://github.com/adafruit/Adafruit_nRF8001
#include "../BaseModel/BaseModel.hpp"
#include "../Constants/Port.hpp"
#include "../Constants/Constants.hpp"



class Bluetooth : public BaseModel
{
public:
    Adafruit_BLE_UART *bluetooth;

    Bluetooth(void);
    ~Bluetooth(void);

    void forward();

    bool isAciDiff();

private:
};


#endif  //BLUETOOTH_HPP
