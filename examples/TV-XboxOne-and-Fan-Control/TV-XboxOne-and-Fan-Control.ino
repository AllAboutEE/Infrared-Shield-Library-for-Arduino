#include <Wire.h>
#include <Adafruit_MCP23008.h>
#include <AllAboutEE_IRsend.h>
#include <AllAboutEEIRControl.h>


AllAboutEEIRControl irControl;

unsigned int FAN_POWER[] = {1240, 380, 1260, 400, 420, 1220, 1240, 400, 1240, 400, 420, 1240, 420, 1240, 420, 1220, 440, 1220, 440, 1220, 420, 1240, 1240, 7040, 
                                   1240, 400, 1240, 380, 440, 1220, 1240, 400, 1240, 400, 440, 1220, 420, 1240, 420, 1220, 440,	1220, 440, 1220, 420, 1240, 1240, 7060, 
                                   1240, 400, 1240, 400, 420, 1220, 1240, 400, 1240, 420, 420, 1220, 440, 1220, 420, 1240, 420, 1240, 420, 1220, 440, 1220, 1240, 7040, 
                                   1260, 380, 1240, 400, 420, 1220, 1260, 380, 1260, 400, 420, 1240, 420, 1240, 420, 1220, 420, 1240, 420, 1240, 420, 1220, 1260, 7040, 
                                   1220, 400, 1260, 380, 440, 1220, 1240, 400, 1240, 400, 420, 1240, 420, 1240, 420, 1240, 420, 1220, 440, 1220, 420, 1240};


void setup() 
{

  attachInterrupt(0, AllAboutEEIRControl::interrupt, FALLING);

  irControl.begin();
  
  irControl.setButtonCode(
    AllAboutEEIRControl::buttonX, // button ID
    AllAboutEEIRControl::NEC, // IR protocol
    0x20DF10EF, // ir code to send when this button is pressed
    32 // length of ir code
  );
  
  irControl.setButtonCode(
    AllAboutEEIRControl::buttonY, // button ID
    AllAboutEEIRControl::NEC, // IR protocol
    0x011B26D9, // xbox one power
    32 // length of ir code
  );
  
  irControl.setButtonRawCode(
    AllAboutEEIRControl::buttonZ, // button ID
    FAN_POWER, // xbox one power
    sizeof(FAN_POWER)/sizeof(FAN_POWER[0]) // length of ir code
  );
  
  irControl.setButtonCode(
    AllAboutEEIRControl::buttonUP, // button ID
    AllAboutEEIRControl::NEC, // IR protocol
    0x011B7887, // ir code to send when this button is pressed
    32 // length of ir code
  );
  
  irControl.setButtonCode(
    AllAboutEEIRControl::buttonDOWN, // button ID
    AllAboutEEIRControl::NEC, // IR protocol
    0x011BF807, // ir code to send when this button is pressed
    32 // length of ir code
  );
  
  irControl.setButtonCode(
    AllAboutEEIRControl::buttonLEFT, // button ID
    AllAboutEEIRControl::NEC, // IR protocol
    0x011B04FB, // ir code to send when this button is pressed
    32 // length of ir code
  );
  
  irControl.setButtonCode(
    AllAboutEEIRControl::buttonRIGHT, // button ID
    AllAboutEEIRControl::NEC, // IR protocol
    0x011B847B, // ir code to send when this button is pressed
    32 // length of ir code
  );
  
  irControl.setButtonCode(
    AllAboutEEIRControl::buttonSELECT, // button ID
    AllAboutEEIRControl::NEC, // IR protocol
    0x011B44BB, // ir code to send when this button is pressed
    32 // length of ir code
  );
  
  
  
}

void loop() 
{
  if(AllAboutEEIRControl::getFlagValue() == AllAboutEEIRControl::FLAG_READGPIO)
  {
   AllAboutEEIRControl::setFlagValue(0); // must be cleared asap after if
   irControl.sendSignal();
  }

}
