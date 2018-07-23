/**  Handles the Bluetooth protocol library
 *
 * Bluetooth.cpp
 * Created 06-13-18 By: Smitty
 *
 * A longer description.
 */

#include "Bluetooth.hpp"

//state when BLE is turning on
aci_evt_opcode_t lastAci = ACI_EVT_DISCONNECTED;

//global b/c libraries issues
void aciCallback(aci_evt_opcode_t event);


//to see if the instance of the class has been initialized yet
Bluetooth* Bluetooth::_pInstance = NULL; 

/** 
 * @brief  Used to maintain the singleton format
 * @note   
 * @retval 
 */
Bluetooth* Bluetooth::getInstance()
{
    // Only allow one instance of class to be generated.
    if (!_pInstance)
        _pInstance = new Bluetooth();

    return _pInstance;
}


/** 
 * @brief  
 * @note   
 * @retval 
 */
void Bluetooth::init(void)
{
    bluetooth = new Adafruit_BLE_UART(LB_BLE_REQ, LB_BLE_RDY, LB_BLE_RST);

    // bluetooth->setRXcallback(rxCallback);
    // bluetooth->setACIcallback(aciCallback); //grabbing the reference of the function
    // bluetooth->setDeviceName("LIT BIT"); /* 7 characters max! */
    // bluetooth->begin();
}


/** 
 * @brief  Bluetooth destructor
 */
Bluetooth::~Bluetooth(void)
{
    // b/c polymorphic class type 'Adafruit_BLE_UART' has non-virtual destructor might cause undefined behaviour
    // delete bluetooth;
}


bool Bluetooth::isAciDiff(void)
{
    //check if the last Aci is the same or different as the current
    return lastAci != bluetooth->getState();
}