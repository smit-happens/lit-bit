/*
  EEPROM_24X1025.cpp - Library for interfacing 24XX1025 EEPROM chips.
  Created by Valerio De Carolis, January, 2013.
  Licensed under MIT license, see LICENSE.md
 */

#include "Arduino.h"
#include "EEPROM24.h"
#include <Wire.h>

// TWI clock frequency (400 kHz)
#define TWI_FREQ_FAST 400000L

// default config (address & speed)
#define EEPROM24_ADDR B10100000
#define EEPROM24_FAST false

/**
 * Default constructor (using default address and low speed)
 */
EEPROM24::EEPROM24() 
{
  EEPROM24::EEPROM24(EEPROM24_ADDR, false);
}

/**
 * Standard constructor using address and fast flag.
 * It initializes the Wire library.
 */
EEPROM24::EEPROM24(uint8_t address, bool fast)
{
  _address = address;
  _fast = fast;

  // init Wire library
  // Wire.begin();

  // change TWI base clock
  if(fast) {
    TWBR = ((F_CPU / TWI_FREQ_FAST) - 16) / 2;
  }
}

/**
 * [EEPROM24::read description]
 * @param  eeprom_addr [description]
 * @return             [description]
 */
int EEPROM24::read(uint16_t eeprom_addr)
{
  uint8_t i2c_status = 0;
  int i2c_addr = (int) _address;
  int ee_out = 0;
  
  // swap chip (for daisy-chained eeproms)
  if( eeprom_addr > 65535 )
    i2c_addr = i2c_addr | B00001000;    
 
  // seven-bit address
  i2c_addr = i2c_addr >> 1;
  
  // i2c commands
  Wire.beginTransmission(i2c_addr);
  Wire.write( (uint8_t) eeprom_addr >> 8 );
  Wire.write( (uint8_t) (eeprom_addr & 0x00FF) );
  
  // check status
  i2c_status = Wire.endTransmission();
  
  if( i2c_status == 0 ) {  
    Wire.requestFrom(i2c_addr, 1);

    while( Wire.available() )
      ee_out = Wire.read();    

    return ee_out;
  } else {  
    return -1;
  } 
}

/**
 * [EEPROM24::write description]
 * @param  eeprom_addr [description]
 * @param  data        [description]
 * @return             [description]
 */
int EEPROM24::write(uint16_t eeprom_addr, uint8_t data)
{
  uint8_t i2c_addr = _address;
  
  if( eeprom_addr > 65535 )
    i2c_addr |= B00001000;    
 
  // seven-bit address
  i2c_addr = i2c_addr >> 1;
  
  // i2c commands
  Wire.beginTransmission(i2c_addr);

  Serial.println("EEPROM library");
  Serial.println(Wire.write( (uint8_t) eeprom_addr >> 8 ));
  Serial.println(Wire.write( (uint8_t) (eeprom_addr & 0x00FF) ));
  Serial.println(Wire.write( data ));
  
  return Wire.endTransmission();  
}
