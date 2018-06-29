/**  Handles the Bluetooth protocol library
 *
 * #include "Bluetooth.hpp"
 * Created 05-24-18 By: Smitty
 *
 * Controls the Nordic nrf8001 breakout from here: https://www.adafruit.com/product/1697
 */

#ifndef BLUETOOTH_HPP
#define BLUETOOTH_HPP

#include <SPI.h>
// #include <BLEPeripheral.h>              //library from: https://github.com/sandeepmistry/arduino-BLEPeripheral
// #include "BLESerial.h"
#include <Adafruit_BLE_UART.h>
#include "../BaseModel/BaseModel.hpp"
#include "../Constants/Port.hpp"
#include "../Constants/Constants.hpp"



class Bluetooth : public BaseModel
{
public:
    Bluetooth(void);
    ~Bluetooth(void);

    void forward();

private:
    //private instance of the bluetooth object
    // BLESerial *bluetooth;
    Adafruit_BLE_UART *bluetooth;

};


#endif  //BLUETOOTH_HPP
