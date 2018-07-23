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
#include "../Constants/Port.hpp"
#include "../Constants/Constants.hpp"



class Bluetooth
{
public:
    Adafruit_BLE_UART *bluetooth;
    uint8_t* localBleBuffer;
    uint8_t  localBleBufferLength;
    
    ~Bluetooth(void);
    static Bluetooth*   getInstance();
    void init(void);

    void forward();

    bool isAciDiff();

private:
    //Private contstructor so that it can't be called
    Bluetooth() {};
    //copy constructor is private
    Bluetooth(Bluetooth const&) {};
    //static instance pointer
    static Bluetooth* _pInstance;
};


#endif  //BLUETOOTH_HPP
