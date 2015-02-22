#include "AllAboutEEIRControlButton.h"

#include <std.h>

AllAboutEEIRControlButton::AllAboutEEIRControlButton(ButtonID id)
{
	setId(id);
}


void AllAboutEEIRControlButton::setId(AllAboutEEIRControlButton::ButtonID id)
{
	this->id = id;
}

AllAboutEEIRControlButton::ButtonID AllAboutEEIRControlButton::getId(){
	return this->id;
}

unsigned long AllAboutEEIRControlButton::getHexCode(){
	return this->hexCode;
}

void AllAboutEEIRControlButton::setHexCode(unsigned long hexCode){
	
	this->hexCode = hexCode;
}

void AllAboutEEIRControlButton::setCodeLength(int length){
	this->codeLength = length;
}

int AllAboutEEIRControlButton::getCodeLength(){
	return this->codeLength;
}

unsigned int* AllAboutEEIRControlButton::getRawCode(){
	return rawCode;
}

void AllAboutEEIRControlButton::setRawCode(unsigned int* rawCode,int length){

	setCodeLength(length);
	this->rawCode = rawCode;
}

void AllAboutEEIRControlButton::setProtocol(uint8_t irProtocol){
	this->irProtocol = irProtocol;
}

uint8_t AllAboutEEIRControlButton::getProtocol(){
	return this->irProtocol;
}
