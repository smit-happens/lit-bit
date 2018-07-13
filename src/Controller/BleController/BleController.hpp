/**  Bluetooth controller class
 *
 * #include "BleController.hpp"
 * Created 06-13-18 By: Smitty
 *
 * A longer description.
 */

#ifndef BLECONTROLLER_HPP
#define BLECONTROLLER_HPP

#include "../BaseController/BaseController.hpp"
#include "../../Model/Bluetooth/Bluetooth.hpp"


class BleController : public BaseController
{
public:
    Bluetooth* bluetoothModel;
    uint8_t* localBleBuffer;
    uint8_t  localBleBufferLength;


    ~BleController(void);

    static BleController*   getInstance();

    void init(void);

    //flesh this out
    int test();


private:
    //Private contstructor so that it can't be called
    BleController() {};

    //copy constructor is private
    BleController(BleController const&) {};

    //static instance pointer
    static BleController* _pInstance;


    // //private instance of model
    // Bluetooth* bluetoothModel;
    
};


#endif  //BLECONTROLLER_HPP
