/**  Handles the Bluetooth protocol library
 *
 * Bluetooth.cpp
 * Created 06-13-18 By: Smitty
 *
 * A longer description.
 */

#include "Bluetooth.hpp"


// create ble serial instance, see pinouts above
// BLESerial BLESerial(LB_BLE_REQ, LB_BLE_RDY, LB_BLE_RST);


/** 
 * @brief  Bluetooth constructor
 */
Bluetooth::Bluetooth(void)
{
    //initialize the oled library
    bluetooth = new BLESerial(LB_BLE_REQ, LB_BLE_RDY, LB_BLE_RST);

    // custom services and characteristics can be added as well
    bluetooth->setLocalName("UART");

    bluetooth->begin();


    while(1) {
        bluetooth->poll();

        forward();
    }


}


/** 
 * @brief  Bluetooth destructor
 */
Bluetooth::~Bluetooth(void)
{
    delete bluetooth;
}


// forward received from Serial to BLESerial and vice versa
void Bluetooth::forward() {
  if (bluetooth && Serial) {
    int byte;
    while ((byte = bluetooth->read()) > 0) Serial.write((char)byte);
    while ((byte = Serial.read()) > 0) bluetooth->write((char)byte);
  }
}
