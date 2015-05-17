/** 
 * @brief An infrared remote control for a light bulb. 
 *  
 * @author AllAboutEE (Miguel Alvarez) 
 */

#include <Wire.h>
#include <Adafruit_MCP23008.h>
#include <AllAboutEE_IRsend.h>
#include <AllAboutEE_IRControl.h>

#define POWER_ON    0xFFE01F
#define POWER_OFF   0XFF609F
#define STROBE      0xFFE817
#define RED         0xFF906F
#define GREEN       0xFF10EF
#define BLUE        0xFF50AF
#define WHITE       0xFFD02F
#define YELLOW      0xFF8877

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
    POWER_ON, // ir code to send when this button is pressed
    32 // length of ir code
  );
  
  // configure Y button
  irControl.setButtonCode(
    IRControl::buttonY, // button ID
    IRControl::NEC, // IR protocol
    POWER_OFF, // ir code to send when this button is pressed
    32 // length of ir code
  );
  
  // configure Z button
  irControl.setButtonCode(
    IRControl::buttonZ, // button ID
    IRControl::NEC, // IR protocol
    STROBE, // ir code to send when this button is pressed
    32 // length of ir code
  );
  
  // configure UP button
  irControl.setButtonCode(
    IRControl::buttonUP, // button ID
    IRControl::NEC, // IR protocol
    WHITE, // ir code to send when this button is pressed
    32 // length of ir code
  );
  
  // configure DOWN button
  irControl.setButtonCode(
    IRControl::buttonDOWN, // button ID
    IRControl::NEC, // IR protocol
    YELLOW, // ir code to send when this button is pressed
    32 // length of ir code
  );
  
  // configure the LEFT button
  irControl.setButtonCode(
    IRControl::buttonLEFT, // button ID
    IRControl::NEC, // IR protocol
    RED, // ir code to send when this button is pressed
    32 // length of ir code
  );
  
  // configure the RIGHT button
  irControl.setButtonCode(
    IRControl::buttonRIGHT, // button ID
    IRControl::NEC, // IR protocol
    BLUE, // ir code to send when this button is pressed
    32 // length of ir code
  );
  
  // configure the SELECT button
  irControl.setButtonCode(
    IRControl::buttonSELECT, // button ID
    IRControl::NEC, // IR protocol
    GREEN, // ir code to send when this button is pressed
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
