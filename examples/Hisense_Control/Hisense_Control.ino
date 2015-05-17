/** 
 * @brief An infrared remote control for an Xbox One.
 */

#include <Wire.h>
#include <Adafruit_MCP23008.h>
#include <AllAboutEE_IRsend.h>
#include <AllAboutEE_IRControl.h>

#define POWER         0x20DF10EF
#define VOLUME_UP     0x20DF40BF
#define VOLUME_DOWN   0x20DFC03F
#define CHANNEL_UP    0x20DF00FF
#define CHANNEL_DOWN  0x20DF807F
#define INPUT_BTN     0x20DFD02F
#define SELECT        0x20DF5AA5

using namespace AllAboutEE;

IRControl irControl;

void setup() 
{

  attachInterrupt(0, IRControl::interrupt, FALLING); // a predefined interrupt detects button presses and sets a flag.

  irControl.begin();
  
  // configure X button
  irControl.setButtonCode(
    IRControl::buttonX, // button ID
    IRControl::NEC, // IR protocol
    POWER, // ir code to send when this button is pressed
    32 // length of ir code
  );
  
    // configure Z button
  irControl.setButtonCode(
    IRControl::buttonZ, // button ID
    IRControl::NEC, // IR protocol
    INPUT_BTN, // ir code to send when this button is pressed
    32 // length of ir code
  );
  
  // configure UP button
  irControl.setButtonCode(
    IRControl::buttonUP, // button ID
    IRControl::NEC, // IR protocol
    VOLUME_UP, // ir code to send when this button is pressed
    32 // length of ir code
  );
  
  // configure DOWN button
  irControl.setButtonCode(
    IRControl::buttonDOWN, // button ID
    IRControl::NEC, // IR protocol
    VOLUME_DOWN, // ir code to send when this button is pressed
    32 // length of ir code
  );
  
  // configure the LEFT button
  irControl.setButtonCode(
    IRControl::buttonLEFT, // button ID
    IRControl::NEC, // IR protocol
    CHANNEL_DOWN, // ir code to send when this button is pressed
    32 // length of ir code
  );
  
  // configure the RIGHT button
  irControl.setButtonCode(
    IRControl::buttonRIGHT, // button ID
    IRControl::NEC, // IR protocol
    CHANNEL_UP, // ir code to send when this button is pressed
    32 // length of ir code
  );
  
  // configure the SELECT button
  irControl.setButtonCode(
    IRControl::buttonSELECT, // button ID
    IRControl::NEC, // IR protocol
    SELECT, // ir code to send when this button is pressed
    32 // length of ir code
  );
}

void loop() 
{
  if(IRControl::getFlagValue() == IRControl::FLAG_READGPIO) // check if the user has pressed a button
  {
   // the user has pressed a button
   IRControl::setFlagValue(0); // clear the flag so that further presses are recognized.
   // send the signal of the button that was pressed.
   irControl.sendSignal();
  }
}
