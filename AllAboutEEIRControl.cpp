#include "AllAboutEEIRControl.h"
#include "AllAboutEEIRControlButton.h"


// IR protocol
const uint8_t AllAboutEE::IRControl::NEC = 0x01;
const uint8_t AllAboutEE::IRControl::SONY = 0x02;
const uint8_t AllAboutEE::IRControl::RC5 = 0x03;
const uint8_t AllAboutEE::IRControl::RC6 = 0x04;
const uint8_t AllAboutEE::IRControl::DISH = 0x05;
const uint8_t AllAboutEE::IRControl::SENDSHARPRAW = 0x06;
const uint8_t AllAboutEE::IRControl::SAMSUNG = 0x07;
const uint8_t AllAboutEE::IRControl::RAW = 0x08;
// button objects
AllAboutEE::IRControlButton AllAboutEEIRControl::buttonX = AllAboutEE::IRControlButton(AllAboutEE::IRControlButton::X);
AllAboutEE::IRControlButton AllAboutEEIRControl::buttonY = AllAboutEE::IRControlButton(AllAboutEE::IRControlButton::Y);
AllAboutEE::IRControlButton AllAboutEEIRControl::buttonZ = AllAboutEE::IRControlButton(AllAboutEE::IRControlButton::Z);
AllAboutEE::IRControlButton AllAboutEEIRControl::buttonUP = AllAboutEE::IRControlButton(AllAboutEE::IRControlButton::UP);
AllAboutEE::IRControlButton AllAboutEEIRControl::buttonDOWN = AllAboutEE::IRControlButton(AllAboutEE::IRControlButton::DOWN);
AllAboutEE::IRControlButton AllAboutEEIRControl::buttonLEFT = AllAboutEE::IRControlButton(AllAboutEE::IRControlButton::LEFT);
AllAboutEE::IRControlButton AllAboutEEIRControl::buttonRIGHT = AllAboutEE::IRControlButton(AllAboutEE::IRControlButton::RIGHT);
AllAboutEE::IRControlButton AllAboutEEIRControl::buttonSELECT = AllAboutEE::IRControlButton(AllAboutEE::IRControlButton::SELECT);
AllAboutEE::IRControlButton AllAboutEEIRControl::buttonNONE = AllAboutEE::IRControlButton(AllAboutEE::IRControlButton::NONE);

const int AllAboutEEIRControl::FLAG_READGPIO = 1;
int AllAboutEEIRControl::flag = 0;

/** 
 *  
 * @brief Configures the MCP23008 .
 * 
 * @author Miguel (5/15/2015)
 */
void AllAboutEE::IRControl::begin()
{
    mcp = Adafruit_MCP23008();
	mcp.begin();

    // enable pull up resistors and interrupt modes.
	for(int i = 0; i<=7; i++)
	{
		mcp.pinMode(i,INPUT); //INPUT = 0
		mcp.pullUp(i,HIGH); //HIGH = 1
		mcp.interruptMode(i,HIGH); //HIGH = 1
	}

	mcp.writeDEFVAL(0xFF); // The default values for the GPIO (the buttons are pulled-up).
                           // When a GPIO values does not match the DEFVAL an interrupt 
                           // will be triggered.
                           
	mcp.writeINTCON(0x00); // Clearing bits compares GPIO values to the DEFVAL
	
}

/**
 * @brief Sets a button's IR code/signal.
 * 
 * @author Miguel (5/15/2015)
 * 
 * @param button 
 * @param signalType 
 * @param IRCode 
 * @param IRCodeLength 
 */
void AllAboutEE::IRControl::setButtonCode(AllAboutEE::IRControlButton &button, uint8_t signalType, unsigned long IRCode, int IRCodeLength)
{
	button.setProtocol(signalType);
	button.setHexCode(IRCode);
	button.setCodeLength(IRCodeLength);		
}

/**
 * @brief Sets a button's RAW code signal. Incase the signal the
 *        users wants to use is not any of the defined
 *        protocols..
 * 
 * @author Miguel (5/15/2015)
 * 
 * @param button 
 * @param IRCode 
 * @param IRCodeLength 
 */
void AllAboutEE::IRControl::setButtonRawCode(AllAboutEE::IRControlButton &button,unsigned int* IRCode, int IRCodeLength)
{
	button.setProtocol(AllAboutEEIRControl::RAW);
	button.setRawCode(IRCode,IRCodeLength);
}

/**
 * @brief Sends the IR signal.
 * 
 * @author Miguel (5/15/2015)
 */
void AllAboutEE::IRControl::sendSignal()
{
	setFlagValue(0);
	AllAboutEE::IRControlButton::ButtonID buttonId = getButtons();
	AllAboutEE::IRControlButton button = getButton(buttonId);
		
	if(button.getId() != AllAboutEE::IRControlButton::NONE)
	{
		if(button.getProtocol()!=RAW)
		{
			sendCode(button.getProtocol(), button.getHexCode(), button.getCodeLength());
		}else{
			irsend.sendRaw(button.getRawCode(),button.getCodeLength(),38);
		}
	}else{
		// don't send anything

	}

}

/**
 * @brief Obtain a button object given a GPIO state.
 * 
 * @author Miguel (5/15/2015)
 * 
 * @param gpioValue 
 * 
 * @return AllAboutEEIRControlButton 
 */
AllAboutEE::IRControlButton AllAboutEEIRControl::getButton(AllAboutEE::IRControlButton::ButtonID gpioValue)
{

	if(gpioValue != AllAboutEE::IRControlButton::NONE)
	{
		switch(gpioValue)
		{
		case AllAboutEE::IRControlButton::X:
			return buttonX;
			break;
		case AllAboutEE::IRControlButton::Y:
			return buttonY;
			break;
		case AllAboutEE::IRControlButton::Z:
			return buttonZ;
			break;
		case AllAboutEE::IRControlButton::UP:
			return buttonUP;
			break;
		case AllAboutEE::IRControlButton::LEFT:
			return buttonLEFT;
			break;
		case AllAboutEE::IRControlButton::DOWN:
			return buttonDOWN;
			break;
		case AllAboutEE::IRControlButton::RIGHT:
			return buttonRIGHT;
			break;
		case AllAboutEE::IRControlButton::SELECT:
			return buttonSELECT;
			break;
		default:
			return buttonNONE;
			break;
		}
	}else{
	 return buttonNONE;
	}

}

/**
 * @brief Sends the IR code/signal.
 * 
 * @author Miguel (5/15/2015)
 * 
 * @param signalType 
 * @param IRCode 
 * @param IRCodeLength 
 */
void AllAboutEE::IRControl::sendCode(uint8_t signalType, unsigned long IRCode, int IRCodeLength)
{
	switch(signalType)
	{
    case AllAboutEE::IRControl::NEC:
			irsend.sendNEC(IRCode, IRCodeLength);
			break;
		case AllAboutEE::IRControl::SONY:
			irsend.sendSony(IRCode,IRCodeLength);
			break;
		case AllAboutEE::IRControl::RC5:
			irsend.sendRC5(IRCode,IRCodeLength);
			break;
		case AllAboutEE::IRControl::RC6:
			irsend.sendRC6(IRCode,IRCodeLength);
			break;
		case AllAboutEE::IRControl::DISH:
			irsend.sendDISH(IRCode,IRCodeLength);
			break;
		case AllAboutEE::IRControl::SENDSHARPRAW:
			irsend.sendSharpRaw(IRCode,IRCodeLength);
			break;
		case AllAboutEE::IRControl::SAMSUNG:
			irsend.sendSAMSUNG(IRCode,IRCodeLength);
			break;
		default:
			break;
	}

}

/**
 * @brief  Read the GPIO states when the GPIO 
 * interrupt in the MCP23008 was triggered i.e. read the INTCAP 
 * register. 
 * 
 * @author Miguel (5/15/2015)
 * 
 * @return AllAboutEEIRControlButton::ButtonID 
 */
AllAboutEE::IRControlButton::ButtonID AllAboutEE::IRControl::getButtons()
{
	return (AllAboutEE::IRControlButton::ButtonID)mcp.readINTCAP();

}

void AllAboutEE::IRControl::setFlagValue(int newFlagVal)
{
	flag = newFlagVal;
}

int AllAboutEE::IRControl::getFlagValue()
{
	return flag;
}

/**
 * @brief Function that will be used as interrupt to set a flag 
 *        when a button on the shield is pressed.
 * 
 * @author Miguel (5/15/2015)
 */
void AllAboutEE::IRControl::interrupt()
{
	setFlagValue(FLAG_READGPIO);
}
