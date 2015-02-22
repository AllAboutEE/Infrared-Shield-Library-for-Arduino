#ifndef ALLABOUTEEIRCONTROL_H_
#define ALLABOUTEEIRCONTROL_H_

#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

#include <Adafruit_MCP23008.h>
#include <AllAboutEE_IRsend.h>
#include "AllAboutEEIRControlButton.h"

class AllAboutEEIRControl
{
public:
	void setButtonCode(AllAboutEEIRControlButton&, uint8_t, unsigned long, int);
	void setButtonRawCode(AllAboutEEIRControlButton&,unsigned int*, int);
	void sendSignal();
	void begin();
	
	static void setFlagValue(int);
	static int getFlagValue();
    static void interrupt();

	
	// buttons
	static AllAboutEEIRControlButton buttonX;
	static AllAboutEEIRControlButton buttonY;
	static AllAboutEEIRControlButton buttonZ;
	static AllAboutEEIRControlButton buttonUP;
	static AllAboutEEIRControlButton buttonLEFT;
	static AllAboutEEIRControlButton buttonDOWN;
	static AllAboutEEIRControlButton buttonRIGHT;
	static AllAboutEEIRControlButton buttonSELECT;
	static AllAboutEEIRControlButton buttonNONE;
	
	// IR protocols
	static const uint8_t NEC;
	static const uint8_t SONY;
	static const uint8_t RC5;
	static const uint8_t RC6;
	static const uint8_t DISH;
	static const uint8_t SENDSHARPRAW;
	static const uint8_t SAMSUNG;
	static const uint8_t RAW;
    
    static const int FLAG_READGPIO;
	
private:
	Adafruit_MCP23008 mcp;
	AllAboutEE_IRsend irsend;

	AllAboutEEIRControlButton::ButtonID getButtons();
	void sendCode(uint8_t, unsigned long, int);
	AllAboutEEIRControlButton getButton(AllAboutEEIRControlButton::ButtonID);

	static int flag;

};



#endif
