#include "AllAboutEEIRControl.h"
#include "AllAboutEEIRControlButton.h"


// IR protocol
const uint8_t AllAboutEEIRControl::NEC = 0x01;
const uint8_t AllAboutEEIRControl::SONY = 0x02;
const uint8_t AllAboutEEIRControl::RC5 = 0x03;
const uint8_t AllAboutEEIRControl::RC6 = 0x04;
const uint8_t AllAboutEEIRControl::DISH = 0x05;
const uint8_t AllAboutEEIRControl::SENDSHARPRAW = 0x06;
const uint8_t AllAboutEEIRControl::SAMSUNG = 0x07;
const uint8_t AllAboutEEIRControl::RAW = 0x08;

AllAboutEEIRControlButton AllAboutEEIRControl::buttonX = AllAboutEEIRControlButton(AllAboutEEIRControlButton::X);
AllAboutEEIRControlButton AllAboutEEIRControl::buttonY = AllAboutEEIRControlButton(AllAboutEEIRControlButton::Y);
AllAboutEEIRControlButton AllAboutEEIRControl::buttonZ = AllAboutEEIRControlButton(AllAboutEEIRControlButton::Z);
AllAboutEEIRControlButton AllAboutEEIRControl::buttonUP = AllAboutEEIRControlButton(AllAboutEEIRControlButton::UP);
AllAboutEEIRControlButton AllAboutEEIRControl::buttonDOWN = AllAboutEEIRControlButton(AllAboutEEIRControlButton::DOWN);
AllAboutEEIRControlButton AllAboutEEIRControl::buttonLEFT = AllAboutEEIRControlButton(AllAboutEEIRControlButton::LEFT);
AllAboutEEIRControlButton AllAboutEEIRControl::buttonRIGHT = AllAboutEEIRControlButton(AllAboutEEIRControlButton::RIGHT);
AllAboutEEIRControlButton AllAboutEEIRControl::buttonSELECT = AllAboutEEIRControlButton(AllAboutEEIRControlButton::SELECT);
AllAboutEEIRControlButton AllAboutEEIRControl::buttonNONE = AllAboutEEIRControlButton(AllAboutEEIRControlButton::NONE);

const int AllAboutEEIRControl::FLAG_READGPIO = 1;
int AllAboutEEIRControl::flag = 0;
	
void AllAboutEEIRControl::begin()
{
    mcp = Adafruit_MCP23008();
	mcp.begin();

	for(int i = 0; i<=7; i++)
	{
		mcp.pinMode(i,INPUT); //INPUT = 0
		mcp.pullUp(i,HIGH); //HIGH = 1
		mcp.interruptMode(i,HIGH); //HIGH = 1
	}

	mcp.writeDEFVAL(0xFF);
	mcp.writeINTCON(0x00);
	
}

void AllAboutEEIRControl::setButtonCode(AllAboutEEIRControlButton &button, uint8_t signalType, unsigned long IRCode, int IRCodeLength)
{
	button.setProtocol(signalType);
	button.setHexCode(IRCode);
	button.setCodeLength(IRCodeLength);		
}

void AllAboutEEIRControl::setButtonRawCode(AllAboutEEIRControlButton &button,unsigned int* IRCode, int IRCodeLength)
{
	button.setProtocol(AllAboutEEIRControl::RAW);
	button.setRawCode(IRCode,IRCodeLength);
}

void AllAboutEEIRControl::sendSignal()
{
	setFlagValue(0);
	AllAboutEEIRControlButton::ButtonID buttonId = getButtons();
	AllAboutEEIRControlButton button = getButton(buttonId);
		
	if(button.getId() != AllAboutEEIRControlButton::NONE)
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

AllAboutEEIRControlButton AllAboutEEIRControl::getButton(AllAboutEEIRControlButton::ButtonID gpioValue)
{

	if(gpioValue != AllAboutEEIRControlButton::NONE)
	{
		switch(gpioValue)
		{
		case AllAboutEEIRControlButton::X:
			return buttonX;
			break;
		case AllAboutEEIRControlButton::Y:
			return buttonY;
			break;
		case AllAboutEEIRControlButton::Z:
			return buttonZ;
			break;
		case AllAboutEEIRControlButton::UP:
			return buttonUP;
			break;
		case AllAboutEEIRControlButton::LEFT:
			return buttonLEFT;
			break;
		case AllAboutEEIRControlButton::DOWN:
			return buttonDOWN;
			break;
		case AllAboutEEIRControlButton::RIGHT:
			return buttonRIGHT;
			break;
		case AllAboutEEIRControlButton::SELECT:
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


void AllAboutEEIRControl::sendCode(uint8_t signalType, unsigned long IRCode, int IRCodeLength)
{
	switch(signalType)
	{
		case AllAboutEEIRControl::NEC:
			irsend.sendNEC(IRCode, IRCodeLength);
			break;
		case AllAboutEEIRControl::SONY:
			irsend.sendSony(IRCode,IRCodeLength);
			break;
		case AllAboutEEIRControl::RC5:
			irsend.sendRC5(IRCode,IRCodeLength);
			break;
		case AllAboutEEIRControl::RC6:
			irsend.sendRC6(IRCode,IRCodeLength);
			break;
		case AllAboutEEIRControl::DISH:
			irsend.sendDISH(IRCode,IRCodeLength);
			break;
		case AllAboutEEIRControl::SENDSHARPRAW:
			irsend.sendSharpRaw(IRCode,IRCodeLength);
			break;
		case AllAboutEEIRControl::SAMSUNG:
			irsend.sendSAMSUNG(IRCode,IRCodeLength);
			break;
		default:
			break;
	}

}


AllAboutEEIRControlButton::ButtonID AllAboutEEIRControl::getButtons()
{
	return (AllAboutEEIRControlButton::ButtonID)mcp.readINTCAP();

}

void AllAboutEEIRControl::setFlagValue(int newFlagVal)
{
	flag = newFlagVal;
}

int AllAboutEEIRControl::getFlagValue()
{
	return flag;
}

void AllAboutEEIRControl::interrupt()
{
	setFlagValue(FLAG_READGPIO);
}
