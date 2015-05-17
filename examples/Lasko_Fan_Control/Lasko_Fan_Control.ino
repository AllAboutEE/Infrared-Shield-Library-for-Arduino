/** 
 * @brief An infrared remote control for a light bulb.
 */

#include <Wire.h>
#include <Adafruit_MCP23008.h>
#include <AllAboutEE_IRsend.h>
#include <AllAboutEE_IRControl.h>

unsigned int FAN_POWER[] = {1300, 350, 1300, 400, 400, 1250, 1250, 400, 1250, 400, 450, 1250, 400, 1250, 450, 1200, 450, 1250, 400, 1250, 450, 1200, 1250};
unsigned int FAN_TIMER[] = {1250, 400, 1250, 400, 450, 1200, 1250, 400, 1250, 450, 400, 1250, 450, 1200, 450, 1250, 1250, 400, 450, 1200, 450, 1250, 400};
unsigned int FAN_ROTATE[] = {1250, 400, 1250, 400, 450, 1200, 1300, 350, 1250, 450, 400, 1250, 450, 1200, 1300, 400, 400, 1250, 450, 1250, 400, 1250, 450};
unsigned int FAN_SPEED[] = {1250, 400, 1250, 400, 400, 1250, 1250, 400, 1250, 400, 450, 1250, 450, 1200, 450, 1250, 400, 1250, 450, 1200, 1250, 450, 400};


using namespace AllAboutEE;

IRControl irControl;

void setup() 
{

  attachInterrupt(0, IRControl::interrupt, FALLING); // a predefined interrupt detects button presses and sets a flag.

  irControl.begin();
  
  // configure UP button
  irControl.setButtonRawCode(
    IRControl::buttonUP, // button ID
    FAN_ROTATE, // xbox one power
    sizeof(FAN_ROTATE)/sizeof(FAN_ROTATE[0]) // length of ir code
  );
  
    // configure DOWN button
  irControl.setButtonRawCode(
    IRControl::buttonDOWN, // button ID
    FAN_POWER, // xbox one power
    sizeof(FAN_POWER)/sizeof(FAN_POWER[0]) // length of ir code
  );
  
      // configure RIGHT button
  irControl.setButtonRawCode(
    IRControl::buttonRIGHT, // button ID
    FAN_SPEED, // xbox one power
    sizeof(FAN_SPEED)/sizeof(FAN_SPEED[0]) // length of ir code
  );
  
        // configure LEFT button
  irControl.setButtonRawCode(
    IRControl::buttonLEFT, // button ID
    FAN_TIMER, // xbox one power
    sizeof(FAN_TIMER)/sizeof(FAN_TIMER[0]) // length of ir code
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
