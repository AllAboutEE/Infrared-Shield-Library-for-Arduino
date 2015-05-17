/** 
 * @brief An infrared remote control for an Xbox One.
 */

#include <Wire.h>
#include <Adafruit_MCP23008.h>
#include <AllAboutEE_IRsend.h>
#include <AllAboutEE_IRControl.h>

#define XBOX_ONE_POWER   0x011B26D9
#define XBOX_ONE_VIEW    0x011B7689
#define XBOX_ONE_GUIDE   0x011BF609
#define XBOX_ONE_UP      0x011B7887
#define XBOX_ONE_DOWN    0x011BF807
#define XBOX_ONE_RIGHT   0x011B847B
#define XBOX_ONE_LEFT    0x011B04FB
#define XBOX_ONE_SELECT  0x011B44BB

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
    XBOX_ONE_POWER, // ir code to send when this button is pressed
    32 // length of ir code
  );
  
  // configure Y button
  irControl.setButtonCode(
    IRControl::buttonY, // button ID
    IRControl::NEC, // IR protocol
    XBOX_ONE_VIEW, // ir code to send when this button is pressed
    32 // length of ir code
  );
  
    // configure Z button
  irControl.setButtonCode(
    IRControl::buttonZ, // button ID
    IRControl::NEC, // IR protocol
    XBOX_ONE_GUIDE, // ir code to send when this button is pressed
    32 // length of ir code
  );
  
  // configure UP button
  irControl.setButtonCode(
    IRControl::buttonUP, // button ID
    IRControl::NEC, // IR protocol
    XBOX_ONE_UP, // ir code to send when this button is pressed
    32 // length of ir code
  );
  
  // configure DOWN button
  irControl.setButtonCode(
    IRControl::buttonDOWN, // button ID
    IRControl::NEC, // IR protocol
    XBOX_ONE_DOWN, // ir code to send when this button is pressed
    32 // length of ir code
  );
  
  // configure the LEFT button
  irControl.setButtonCode(
    IRControl::buttonLEFT, // button ID
    IRControl::NEC, // IR protocol
    XBOX_ONE_LEFT, // ir code to send when this button is pressed
    32 // length of ir code
  );
  
  // configure the RIGHT button
  irControl.setButtonCode(
    IRControl::buttonRIGHT, // button ID
    IRControl::NEC, // IR protocol
    XBOX_ONE_RIGHT, // ir code to send when this button is pressed
    32 // length of ir code
  );
  
  // configure the SELECT button
  irControl.setButtonCode(
    IRControl::buttonSELECT, // button ID
    IRControl::NEC, // IR protocol
    XBOX_ONE_SELECT, // ir code to send when this button is pressed
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
