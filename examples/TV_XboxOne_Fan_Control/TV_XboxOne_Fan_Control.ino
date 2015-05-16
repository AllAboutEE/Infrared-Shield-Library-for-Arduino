/** 
 * 
 *  
 * @brief An infrared remote control for an Xbox One, Hisense TV
 *        (EN-33926A), and Lasko fan (model u35102). Three
 *        different buttons are used to power the TV, Xbox One,
 *        and fan. The other 5 buttons are used to navigate the
 *        XboxOne.
 */

#include <Wire.h>
#include <Adafruit_MCP23008.h>
#include <AllAboutEE_IRsend.h>
#include <AllAboutEE_IRControl.h>

using namespace AllAboutEE;

IRControl irControl;

// The lasko fan remote control does ues any particular protcol, so we use raw time data.

unsigned int FAN_POWER[] = {1240, 380, 1260, 400, 420, 1220, 1240, 400, 1240, 400, 420, 1240, 420, 1240, 420, 1220, 440, 1220, 440, 1220, 420, 1240, 1240, 7040, 
                                   1240, 400, 1240, 380, 440, 1220, 1240, 400, 1240, 400, 440, 1220, 420, 1240, 420, 1220, 440,	1220, 440, 1220, 420, 1240, 1240, 7060, 
                                   1240, 400, 1240, 400, 420, 1220, 1240, 400, 1240, 420, 420, 1220, 440, 1220, 420, 1240, 420, 1240, 420, 1220, 440, 1220, 1240, 7040, 
                                   1260, 380, 1240, 400, 420, 1220, 1260, 380, 1260, 400, 420, 1240, 420, 1240, 420, 1220, 420, 1240, 420, 1240, 420, 1220, 1260, 7040, 
                                   1220, 400, 1260, 380, 440, 1220, 1240, 400, 1240, 400, 420, 1240, 420, 1240, 420, 1240, 420, 1220, 440, 1220, 420, 1240};


void setup() 
{

  attachInterrupt(0, IRControl::interrupt, FALLING); // a predefined interrupt detects button presses and sets a flag.

  irControl.begin();
  
  // configure X button
  irControl.setButtonCode(
    IRControl::buttonX, // button ID
    IRControl::NEC, // IR protocol
    0x20DF10EF, // ir code to send when this button is pressed
    32 // length of ir code
  );
  
  // configure Y button
  irControl.setButtonCode(
    IRControl::buttonY, // button ID
    IRControl::NEC, // IR protocol
    0x011B26D9, // xbox one power
    32 // length of ir code
  );
  
  // configure Z button
  irControl.setButtonRawCode(
    IRControl::buttonZ, // button ID
    FAN_POWER, // xbox one power
    sizeof(FAN_POWER)/sizeof(FAN_POWER[0]) // length of ir code
  );
  
  // configure UP button
  irControl.setButtonCode(
    IRControl::buttonUP, // button ID
    IRControl::NEC, // IR protocol
    0x011B7887, // ir code to send when this button is pressed
    32 // length of ir code
  );
  
  // configure DOWN button
  irControl.setButtonCode(
    IRControl::buttonDOWN, // button ID
    IRControl::NEC, // IR protocol
    0x011BF807, // ir code to send when this button is pressed
    32 // length of ir code
  );
  
  // configure the LEFT button
  irControl.setButtonCode(
    IRControl::buttonLEFT, // button ID
    IRControl::NEC, // IR protocol
    0x011B04FB, // ir code to send when this button is pressed
    32 // length of ir code
  );
  
  // configure the RIGHT button
  irControl.setButtonCode(
    IRControl::buttonRIGHT, // button ID
    IRControl::NEC, // IR protocol
    0x011B847B, // ir code to send when this button is pressed
    32 // length of ir code
  );
  
  // configure the SELECT button
  irControl.setButtonCode(
    IRControl::buttonSELECT, // button ID
    IRControl::NEC, // IR protocol
    0x011B44BB, // ir code to send when this button is pressed
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
