/**  Handles the Bluetooth protocol library
 *
 * Bluetooth.cpp
 * Created 06-13-18 By: Smitty
 *
 * A longer description.
 */

#include "Bluetooth.hpp"


/** 
 * @brief  Bluetooth constructor
 */
Bluetooth::Bluetooth(void)
{
    bluetooth = new Adafruit_BLE_UART(LB_BLE_REQ, LB_BLE_RDY, LB_BLE_RST);

    // bluetooth->setRXcallback(rxCallback);
    // bluetooth->setACIcallback(aciCallback);
    // bluetooth->setDeviceName("NEWNAME"); /* 7 characters max! */
    bluetooth->begin();

    bluetooth->pollACI();

}


/** 
 * @brief  Bluetooth destructor
 */
Bluetooth::~Bluetooth(void)
{
    delete bluetooth;
}


/*!
    This function is called whenever select ACI events happen
*/
void aciCallback(aci_evt_opcode_t event)
{
  switch(event)
  {
    case ACI_EVT_DEVICE_STARTED:
      Serial.println(F("Advertising started"));
      break;
    case ACI_EVT_CONNECTED:
      Serial.println(F("Connected!"));
      break;
    case ACI_EVT_DISCONNECTED:
      Serial.println(F("Disconnected or advertising timed out"));
      break;
    default:
      break;
  }
}


// /*!
//     This function is called whenever data arrives on the RX channel
// */
// void rxCallback(uint8_t *buffer, uint8_t len)
// {
//   Serial.print(F("Received "));
//   Serial.print(len);
//   Serial.print(F(" bytes: "));
//   for(int i=0; i<len; i++)
//    Serial.print((char)buffer[i]); 

//   Serial.print(F(" ["));

//   for(int i=0; i<len; i++)
//   {
//     Serial.print(" 0x"); Serial.print((char)buffer[i], HEX); 
//   }
//   Serial.println(F(" ]"));

//   /* Echo the same data back! */
//   bluetooth.write(buffer, len);
// }
