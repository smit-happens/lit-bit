/*  ********************************************* 
 *  SparkFun_ADXL345_Example
 *  Triple Axis Accelerometer Breakout - ADXL345 
 *  Hook Up Guide Example 
 *  
 *  Utilizing Sparkfun's ADXL345 Library
 *  Bildr ADXL345 source file modified to support 
 *  both I2C and SPI Communication
 *  
 *  E.Robert @ SparkFun Electronics
 *  Created: Jul 13, 2016
 *  Updated: Sep 06, 2016
 *  
 *  Development Environment Specifics:
 *  Arduino 1.6.11
 *  
 *  Hardware Specifications:
 *  SparkFun ADXL345
 *  Arduino Uno
 *
 *
 *  Shirish Jadav
 *  Updated: Apr 26, 2018
 *  Added FIFO functionality
 *  *********************************************/

#include <SparkFun_ADXL345.h>         // SparkFun ADXL345 Library

/*********** COMMUNICATION SELECTION ***********/
/*    Comment Out The One You Are Not Using    */
ADXL345 adxl = ADXL345(10);           // USE FOR SPI COMMUNICATION, ADXL345(CS_PIN);
//ADXL345 adxl = ADXL345();             // USE FOR I2C COMMUNICATION

/****************** INTERRUPT ******************/
/*      Uncomment If Attaching Interrupt       */
//int interruptPin = 2;                 // Setup pin 2 to be the interrupt pin (for most Arduino Boards)

bool interrupt_flag=false;
int x,y,z;
/******************** SETUP ********************/
/*          Configure ADXL345 Settings         */
void setup(){
  
  Serial.begin(9600);                 // Start the serial terminal
  Serial.println("SparkFun ADXL345 Accelerometer Hook Up Guide Example");
  Serial.println();
  
  adxl.powerOn();                     // Power on the ADXL345

  adxl.setRangeSetting(16);           // Give the range settings
                                      // Accepted values are 2g, 4g, 8g or 16g
                                      // Higher Values = Wider Measurement Range
                                      // Lower Values = Greater Sensitivity

  adxl.setSpiBit(0);                  // Configure the device to be in 4 wire SPI mode when set to '0' or 3 wire SPI mode when set to 1
                                      // Default: Set to 1
                                      // SPI pins on the ATMega328: 11, 12 and 13 as reference in SPI Library 
 
//attachInterrupt(digitalPinToInterrupt(interruptPin), ADXL_ISR, RISING);   // Attach Interrupt
  
  setupFIFOMode();                    //this sets up required Registers for FIFO
}

/****************** MAIN CODE ******************/
/*     Accelerometer Readings and Interrupt    */
void loop(){
 
 ADXL_ISR();
 if(interrupt_flag){
    while(i<32){
      adxl.readAccel(&x, &y, &z); 
      i++;
      interrupt_flag=false;
    }
    interrupt_flag=false;
   }
}
 
void setupFIFOMode()
{
  adxl.disableAllInterrupts();                          //disable all Interrupts
  adxl.setRate(200);                                    //set output data Rate
  adxl.enableFIFOMode();                               //set ADXL345 in FIFO mode
  adxl.writeWatermarkSamples(20);                      //number of Samples for Watermark 
  adxl.setImportantInterruptMapping(1, 1, 1, 1, 1, 1); //map Interrupt to INT0 INT1
  adxl.waterMarkINT(1);                                //Enable Watermark Interrupt

}
/********************* ISR *********************/
/* Look for Interrupts and Triggered Action    */
void ADXL_ISR() {
  
  // getInterruptSource clears all triggered actions after returning value
  // Do not call again until you need to recheck for triggered actions
  byte interrupts = adxl.getInterruptSource();
  
  // Free Fall Detection
  if(adxl.triggered(interrupts, ADXL345_FREE_FALL)){
    Serial.println("*** FREE FALL ***");
    //add code here to do when free fall is sensed
  } 
  
  // Inactivity
  if(adxl.triggered(interrupts, ADXL345_INACTIVITY)){
    Serial.println("*** INACTIVITY ***");
     //add code here to do when inactivity is sensed
  }
  
  // Activity
  if(adxl.triggered(interrupts, ADXL345_ACTIVITY)){
    Serial.println("*** ACTIVITY ***"); 
     //add code here to do when activity is sensed
  }
  
  // Double Tap Detection
  if(adxl.triggered(interrupts, ADXL345_DOUBLE_TAP)){
    Serial.println("*** DOUBLE TAP ***");
     //add code here to do when a 2X tap is sensed
  }
  
  // Tap Detection
  if(adxl.triggered(interrupts, ADXL345_SINGLE_TAP)){
    Serial.println("*** TAP ***");
     //add code here to do when a tap is sensed
  } 
  if(adxl.triggered(interrupts, ADXL345_WATERMARK)){
    Serial.println("*** WATERMARK ***");
     //add code here to do when a watermark reached
     Serial.print("fifo content Size: ");
     Serial.println(adxl.getFIFOcounts());              //get how many FIFO levels are filled up with sample
     interrupt_flag= true;
  }
}
