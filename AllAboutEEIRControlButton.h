#ifndef ALLABOUTEEIRCONTROLBUTTON_H_
#define ALLABOUTEEIRCONTROLBUTTON_H_

#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif



class AllAboutEEIRControlButton
{
public:
	typedef enum
	{
		X = 0xfe,
		Y = 0xfd,
		Z = 0xfb,
		UP = 0xf7,
		DOWN = 0x7f,
		LEFT = 0xef,
		RIGHT = 0xbf,
		SELECT = 0xdf,
		NONE = 0xaa
	}ButtonID;
	
	AllAboutEEIRControlButton(ButtonID);

	void setId(ButtonID);
	ButtonID getId();
	
	unsigned long getHexCode();
	void setHexCode(unsigned long);
	
    void setCodeLength(int);
	int getCodeLength();
	
	unsigned int* getRawCode();
	void setRawCode(unsigned int*,int);
	
	void setProtocol(uint8_t);
	uint8_t getProtocol();

private:
	ButtonID id;
	unsigned long hexCode;
	unsigned int* rawCode;
	int codeLength;
	uint8_t irProtocol;
};


#endif
