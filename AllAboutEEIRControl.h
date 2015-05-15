#ifndef ALLABOUTEEIRCONTROL_H_
#define ALLABOUTEEIRCONTROL_H_

#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

#include "Adafruit_MCP23008.h"
#include "AllAboutEE_IRsend.h"
#include "AllAboutEEIRControlButton.h"

namespace
{

    class IRControl
    {
    public:
    	void setButtonCode(AllAboutEE::IRControlButton&, uint8_t, unsigned long, int);
    	void setButtonRawCode(AllAboutEE::IRControlButton&,unsigned int*, int);
    	void sendSignal();
    	void begin();
    	
    	static void setFlagValue(int);
    	static int getFlagValue();
        static void interrupt();

    	
    	// buttons
    	static AllAboutEE::IRControlButton buttonX;
    	static AllAboutEE::IRControlButton buttonY;
    	static AllAboutEE::IRControlButton buttonZ;
    	static AllAboutEE::IRControlButton buttonUP;
    	static AllAboutEE::IRControlButton buttonLEFT;
    	static AllAboutEE::IRControlButton buttonDOWN;
    	static AllAboutEE::IRControlButton buttonRIGHT;
    	static AllAboutEE::IRControlButton buttonSELECT;
    	static AllAboutEE::IRControlButton buttonNONE;
    	
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
    	AllAboutEE::IRsend irsend;

    	AllAboutEE::IRControlButton::ButtonID getButtons();
    	void sendCode(uint8_t, unsigned long, int);
    	AllAboutEE::IRControlButton getButton(AllAboutEE::IRControlButton::ButtonID);

    	static int flag;

    };

}


#endif
